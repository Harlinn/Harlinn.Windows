/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef DDLTileHelper_DEFINED
#define DDLTileHelper_DEFINED

#include "skia/core/SkDeferredDisplayList.h"
#include "skia/core/SkRect.h"
#include "skia/core/SkRefCnt.h"
#include "skia/core/SkSpan.h"
#include "skia/core/SkSurfaceCharacterization.h"

class DDLPromiseImageHelper;
class PromiseImageCallbackContext;
class SkCanvas;
class SkData;
class SkDeferredDisplayListRecorder;
class SkPicture;
class SkSurface;
class SkSurfaceCharacterization;
class SkTaskGroup;

class DDLTileHelper {
public:
    // The TileData class encapsulates the information and behavior of a single tile when
    // rendering with DDLs.
    class TileData {
    public:
        SK_API TileData();
        SK_API ~TileData();

        bool initialized() const { return fID != -1; }

        SK_API void init(int id,
                  GrDirectContext*,
                  const SkSurfaceCharacterization& dstChar,
                  const SkIRect& clip,
                  const SkIRect& paddingOutsets);

        // Create the DDL for this tile (i.e., fill in 'fDisplayList').
        SK_API void createDDL(const SkPicture*);

        void dropDDL() { fDisplayList.reset(); }

        // Precompile all the programs required to draw this tile's DDL
        SK_API void precompile(GrDirectContext*);

        // Just draw the re-inflated per-tile SKP directly into this tile w/o going through a DDL
        // first. This is used for determining the overhead of using DDLs (i.e., it replaces
        // a 'createDDL' and 'draw' pair.
        SK_API void drawSKPDirectly(GrDirectContext*, const SkPicture*);

        // Replay the recorded DDL into the tile surface - filling in 'fBackendTexture'.
        SK_API void draw(GrDirectContext*);

        SK_API void reset();

        int id() const { return fID; }
        SkIRect clipRect() const { return fClip; }
        SkISize paddedRectSize() const {
            return { fClip.width() + fPaddingOutsets.fLeft + fPaddingOutsets.fRight,
                     fClip.height() + fPaddingOutsets.fTop + fPaddingOutsets.fBottom };
        }
        SkIVector padOffset() const { return { fPaddingOutsets.fLeft, fPaddingOutsets.fTop }; }

        SkDeferredDisplayList* ddl() { return fDisplayList.get(); }

        SK_API sk_sp<SkImage> makePromiseImageForDst(sk_sp<GrContextThreadSafeProxy>);
        SK_API void dropCallbackContext() { fCallbackContext.reset(); }

        SK_API static void CreateBackendTexture(GrDirectContext*, TileData*);
        SK_API static void DeleteBackendTexture(GrDirectContext*, TileData*);

    private:
        SK_API sk_sp<SkSurface> makeWrappedTileDest(GrRecordingContext* context);

        sk_sp<PromiseImageCallbackContext> refCallbackContext() { return fCallbackContext; }

        int                       fID = -1;
        SkIRect                   fClip;             // in the device space of the final SkSurface
        SkIRect                   fPaddingOutsets;   // random padding for the output surface
        SkSurfaceCharacterization fPlaybackChar;     // characterization for the tile's dst surface

        // The callback context holds (via its SkPromiseImageTexture) the backend texture
        // that is both wrapped in 'fTileSurface' and backs this tile's promise image
        // (i.e., the one returned by 'makePromiseImage').
        sk_sp<PromiseImageCallbackContext> fCallbackContext;
        // 'fTileSurface' wraps the backend texture in 'fCallbackContext' and must exist until
        // after 'fDisplayList' has been flushed (bc it owns the proxy the DDL's destination
        // trampoline points at).
        // TODO: fix the ref-order so we don't need 'fTileSurface' here
        sk_sp<SkSurface>              fTileSurface;

        sk_sp<SkDeferredDisplayList>  fDisplayList;
    };

    SK_API DDLTileHelper(GrDirectContext*,
                  const SkSurfaceCharacterization& dstChar,
                  const SkIRect& viewport,
                  int numXDivisions, int numYDivisions,
                  bool addRandomPaddingToDst);

    SK_API void kickOffThreadedWork(SkTaskGroup* recordingTaskGroup,
                             SkTaskGroup* gpuTaskGroup,
                             GrDirectContext*,
                             SkPicture*);

    SK_API void createDDLsInParallel(SkPicture*);

    // Create the DDL that will compose all the tile images into a final result.
    SK_API void createComposeDDL();
    const sk_sp<SkDeferredDisplayList>& composeDDL() const { return fComposeDDL; }

    // For each tile, create its DDL and then draw it - all on a single thread. This is to allow
    // comparison w/ just drawing the SKP directly (i.e., drawAllTilesDirectly). The
    // DDL creations and draws are interleaved to prevent starvation of the GPU.
    // Note: this is somewhat of a misuse/pessimistic-use of DDLs since they are supposed to
    // be created on a separate thread.
    SK_API void interleaveDDLCreationAndDraw(GrDirectContext*, SkPicture*);

    // This draws all the per-tile SKPs directly into all of the tiles w/o converting them to
    // DDLs first - all on a single thread.
    SK_API void drawAllTilesDirectly(GrDirectContext*, SkPicture*);

    SK_API void dropCallbackContexts();
    SK_API void resetAllTiles();

    int numTiles() const { return fNumXDivisions * fNumYDivisions; }

    SK_API void createBackendTextures(SkTaskGroup*, GrDirectContext*);
    SK_API void deleteBackendTextures(SkTaskGroup*, GrDirectContext*);

private:
    int                                    fNumXDivisions; // number of tiles horizontally
    int                                    fNumYDivisions; // number of tiles vertically
    SkAutoTArray<TileData>                 fTiles;        // 'fNumXDivisions' x 'fNumYDivisions'

    sk_sp<SkDeferredDisplayList>           fComposeDDL;

    const SkSurfaceCharacterization        fDstCharacterization;
};

#endif

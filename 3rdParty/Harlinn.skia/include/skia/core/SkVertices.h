#pragma once
/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkVertices_DEFINED
#define SkVertices_DEFINED

#include <skia/core/SkColor.h>
#include <skia/core/SkRect.h>
#include <skia/core/SkRefCnt.h>

class SkData;
struct SkPoint;
class SkVerticesPriv;

/**
 * An immutable set of vertex data that can be used with SkCanvas::drawVertices.
 */
class SkVertices : public SkNVRefCnt<SkVertices> {
    struct Desc;
    struct Sizes;
public:
    enum VertexMode {
        kTriangles_VertexMode,
        kTriangleStrip_VertexMode,
        kTriangleFan_VertexMode,

        kLast_VertexMode = kTriangleFan_VertexMode,
    };

    /**
     *  Create a vertices by copying the specified arrays. texs, colors may be nullptr,
     *  and indices is ignored if indexCount == 0.
     */
    SK_API static sk_sp<SkVertices> MakeCopy(VertexMode mode, int vertexCount,
                                      const SkPoint positions[],
                                      const SkPoint texs[],
                                      const SkColor colors[],
                                      int indexCount,
                                      const uint16_t indices[]);

    SK_API static sk_sp<SkVertices> MakeCopy(VertexMode mode, int vertexCount,
                                      const SkPoint positions[],
                                      const SkPoint texs[],
                                      const SkColor colors[]) {
        return MakeCopy(mode,
                        vertexCount,
                        positions,
                        texs,
                        colors,
                        0,
                        nullptr);
    }

    enum BuilderFlags {
        kHasTexCoords_BuilderFlag   = 1 << 0,
        kHasColors_BuilderFlag      = 1 << 1,
    };
    class Builder {
    public:
        SK_API Builder(VertexMode mode, int vertexCount, int indexCount, uint32_t flags);

        bool isValid() const { return fVertices != nullptr; }

        SK_API SkPoint* positions();
        SK_API uint16_t* indices();        // returns null if there are no indices

        // If we have custom attributes, these will always be null
        SK_API SkPoint* texCoords();       // returns null if there are no texCoords
        SK_API SkColor* colors();          // returns null if there are no colors

        // Detach the built vertices object. After the first call, this will always return null.
        SK_API sk_sp<SkVertices> detach();

    private:
        SK_API Builder(const Desc&);

        SK_API void init(const Desc&);

        // holds a partially complete object. only completed in detach()
        sk_sp<SkVertices> fVertices;
        // Extra storage for intermediate vertices in the case where the client specifies indexed
        // triangle fans. These get converted to indexed triangles when the Builder is finalized.
        std::unique_ptr<uint8_t[]> fIntermediateFanIndices;

        friend class SkVertices;
        friend class SkVerticesPriv;
    };

    uint32_t uniqueID() const { return fUniqueID; }
    const SkRect& bounds() const { return fBounds; }

    // returns approximate byte size of the vertices object
    SK_API size_t approximateSize() const;

    // Provides access to functions that aren't part of the public API.
    SkVerticesPriv priv();
    const SkVerticesPriv priv() const;  // NOLINT(readability-const-return-type)

private:
    SkVertices() {}

    friend class SkVerticesPriv;

    // these are needed since we've manually sized our allocation (see Builder::init)
    friend class SkNVRefCnt<SkVertices>;
    SK_API void operator delete(void* p);

    SK_API Sizes getSizes() const;

    // we store this first, to pair with the refcnt in our base-class, so we don't have an
    // unnecessary pad between it and the (possibly 8-byte aligned) ptrs.
    uint32_t fUniqueID;

    // these point inside our allocation, so none of these can be "freed"
    SkPoint*     fPositions;        // [vertexCount]
    uint16_t*    fIndices;          // [indexCount] or null
    SkPoint*     fTexs;             // [vertexCount] or null
    SkColor*     fColors;           // [vertexCount] or null

    SkRect  fBounds;    // computed to be the union of the fPositions[]
    int     fVertexCount;
    int     fIndexCount;

    VertexMode fMode;
    // below here is where the actual array data is stored.
};

#endif

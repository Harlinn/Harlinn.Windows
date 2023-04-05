#pragma once
/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

//  Inspired by Rob Johnson's most excellent QuickDraw GX sample code

#ifndef SkCamera_DEFINED
#define SkCamera_DEFINED

#include <skia/core/SkM44.h>
#include <skia/core/SkMatrix.h>
#include <skia/private/SkNoncopyable.h>

// NOTE -- This entire header / impl is deprecated, and will be removed from Skia soon.
//
// Skia now has support for a 4x matrix (SkM44) in SkCanvas.
//

class SkCanvas;

// DEPRECATED
class SkPatch3D {
public:
    SK_API SkPatch3D();

    SK_API void    reset();
    SK_API void    transform(const SkM44&, SkPatch3D* dst = nullptr) const;

    // dot a unit vector with the patch's normal
    SK_API SkScalar dotWith(SkScalar dx, SkScalar dy, SkScalar dz) const;
    SkScalar dotWith(const SkV3& v) const {
        return this->dotWith(v.x, v.y, v.z);
    }

    // deprecated, but still here for animator (for now)
    void rotate(SkScalar /*x*/, SkScalar /*y*/, SkScalar /*z*/) {}
    void rotateDegrees(SkScalar /*x*/, SkScalar /*y*/, SkScalar /*z*/) {}

private:
public: // make public for SkDraw3D for now
    SkV3  fU, fV;
    SkV3  fOrigin;

    friend class SkCamera3D;
};

// DEPRECATED
class SkCamera3D {
public:
    SK_API SkCamera3D();

    SK_API void reset();
    SK_API void update();
    SK_API void patchToMatrix(const SkPatch3D&, SkMatrix* matrix) const;

    SkV3   fLocation;   // origin of the camera's space
    SkV3   fAxis;       // view direction
    SkV3   fZenith;     // up direction
    SkV3   fObserver;   // eye position (may not be the same as the origin)

private:
    mutable SkMatrix    fOrientation;
    mutable bool        fNeedToUpdate;

    SK_API void doUpdate() const;
};

// DEPRECATED
class Sk3DView : SkNoncopyable {
public:
    SK_API Sk3DView();
    SK_API ~Sk3DView();

    SK_API void save();
    SK_API void restore();

    SK_API void translate(SkScalar x, SkScalar y, SkScalar z);
    SK_API void rotateX(SkScalar deg);
    SK_API void rotateY(SkScalar deg);
    SK_API void rotateZ(SkScalar deg);

#ifdef SK_BUILD_FOR_ANDROID_FRAMEWORK
    void setCameraLocation(SkScalar x, SkScalar y, SkScalar z);
    SkScalar getCameraLocationX() const;
    SkScalar getCameraLocationY() const;
    SkScalar getCameraLocationZ() const;
#endif

    SK_API void getMatrix(SkMatrix*) const;
    SK_API void applyToCanvas(SkCanvas*) const;

    SK_API SkScalar dotWithNormal(SkScalar dx, SkScalar dy, SkScalar dz) const;

private:
    struct Rec {
        Rec*    fNext;
        SkM44   fMatrix;
    };
    Rec*        fRec;
    Rec         fInitialRec;
    SkCamera3D  fCamera;
};

#endif

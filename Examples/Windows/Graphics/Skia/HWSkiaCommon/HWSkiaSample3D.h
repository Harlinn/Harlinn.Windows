#pragma once
#ifndef HARLINN_HWSKIACOMMON_HWSKIASAMPLE3D_H_
#define HARLINN_HWSKIACOMMON_HWSKIASAMPLE3D_H_
/*
   Copyright 2024-2026 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#include <HWSkiaSample.h>

#include "skia/core/SkM44.h"
#include "skia/core/SkPaint.h"
#include "skia/core/SkRRect.h"
#include "skia/core/SkVertices.h"
#include "skia/utils/SkRandom.h"
#include "skia/tools/Resources.h"

#include "skia/effects/SkRuntimeEffect.h"
#include "skia/core/SkTime.h"

struct VSphere
{
    SkV2     fCenter;
    SkScalar fRadius;

    VSphere( SkV2 center, SkScalar radius ) : fCenter( center ), fRadius( radius ) {}

    bool contains( SkV2 v ) const
    {
        return ( v - fCenter ).length( ) <= fRadius;
    }

    SkV2 pinLoc( SkV2 p ) const
    {
        auto v = p - fCenter;
        if ( v.length( ) > fRadius )
        {
            v *= ( fRadius / v.length( ) );
        }
        return fCenter + v;
    }

    SkV3 computeUnitV3( SkV2 v ) const
    {
        v = ( v - fCenter ) * ( 1 / fRadius );
        SkScalar len2 = v.lengthSquared( );
        if ( len2 > 1 )
        {
            v = v.normalize( );
            len2 = 1;
        }
        SkScalar z = SkScalarSqrt( 1 - len2 );
        return { v.x, v.y, z };
    }

    struct RotateInfo
    {
        SkV3    fAxis;
        SkScalar fAngle;
    };

    RotateInfo computeRotationInfo( SkV2 a, SkV2 b ) const
    {
        SkV3 u = this->computeUnitV3( a );
        SkV3 v = this->computeUnitV3( b );
        SkV3 axis = u.cross( v );
        SkScalar length = axis.length( );

        if ( !SkScalarNearlyZero( length ) )
        {
            return { axis * ( 1.0f / length ), acos( u.dot( v ) ) };
        }
        return { {0, 0, 0}, 0 };
    }

    SkM44 computeRotation( SkV2 a, SkV2 b ) const
    {
        auto [axis, angle] = this->computeRotationInfo( a, b );
        return SkM44::Rotate( axis, angle );
    }
};

static SkM44 inv( const SkM44& m )
{
    SkM44 inverse;
    SkAssertResult( m.invert( &inverse ) );
    return inverse;
}

// Compute the inverse transpose (of the upper-left 3x3) of a matrix, used to transform vectors
static SkM44 normals( SkM44 m )
{
    m.setRow( 3, { 0, 0, 0, 1 } );
    m.setCol( 3, { 0, 0, 0, 1 } );
    SkAssertResult( m.invert( &m ) );
    return m.transpose( );
}

class Sample3DView : public Harlinn::Windows::Skia::Sample
{
protected:
    float   fNear = 0.05f;
    float   fFar = 4;
    float   fAngle = SK_ScalarPI / 12;

    SkV3    fEye{ 0, 0, 1.0f / tan( fAngle / 2 ) - 1 };
    SkV3    fCOA{ 0, 0, 0 };
    SkV3    fUp{ 0, 1, 0 };

public:
    void concatCamera( SkCanvas* canvas, const SkRect& area, SkScalar zscale )
    {
        SkM44 camera = SkM44::LookAt( fEye, fCOA, fUp ),
            perspective = SkM44::Perspective( fNear, fFar, fAngle ),
            viewport = SkM44::Translate( area.centerX( ), area.centerY( ), 0 ) *
            SkM44::Scale( area.width( ) * 0.5f, area.height( ) * 0.5f, zscale );

        canvas->concat( viewport * perspective * camera * inv( viewport ) );
    }
};

struct Face
{
    SkScalar fRx, fRy;
    SkColor  fColor;

    static SkM44 T( SkScalar x, SkScalar y, SkScalar z )
    {
        return SkM44::Translate( x, y, z );
    }

    static SkM44 R( SkV3 axis, SkScalar rad )
    {
        return SkM44::Rotate( axis, rad );
    }

    SkM44 asM44( SkScalar scale ) const
    {
        return R( { 0,1,0 }, fRy ) * R( { 1,0,0 }, fRx ) * T( 0, 0, scale );
    }
};

static bool front( const SkM44& m )
{
    SkM44 m2( SkM44::kUninitialized_Constructor );
    if ( !m.invert( &m2 ) )
    {
        m2.setIdentity( );
    }
    /*
     *  Classically we want to dot the transpose(inverse(ctm)) with our surface normal.
     *  In this case, the normal is known to be {0, 0, 1}, so we only actually need to look
     *  at the z-scale of the inverse (the transpose doesn't change the main diagonal, so
     *  no need to actually transpose).
     */
    return m2.rc( 2, 2 ) > 0;
}

const Face faces[] = {
    {             0,             0,  SK_ColorRED }, // front
    {             0,   SK_ScalarPI,  SK_ColorGREEN }, // back

    { SK_ScalarPI / 2,             0,  SK_ColorBLUE }, // top
    {-SK_ScalarPI / 2,             0,  SK_ColorCYAN }, // bottom

    {             0, SK_ScalarPI / 2,  SK_ColorMAGENTA }, // left
    {             0,-SK_ScalarPI / 2,  SK_ColorYELLOW }, // right
};


struct LightOnSphere
{
    SkV2     fLoc;
    SkScalar fDistance;
    SkScalar fRadius;

    SkV3 computeWorldPos( const VSphere& s ) const
    {
        return s.computeUnitV3( fLoc ) * fDistance;
    }

    void draw( SkCanvas* canvas ) const
    {
        SkPaint paint;
        paint.setAntiAlias( true );
        paint.setColor( SK_ColorWHITE );
        canvas->drawCircle( fLoc.x, fLoc.y, fRadius + 2, paint );
        paint.setColor( SK_ColorBLACK );
        canvas->drawCircle( fLoc.x, fLoc.y, fRadius, paint );
    }
};


class RotateAnimator
{
    SkV3        fAxis = { 0, 0, 0 };
    SkScalar    fAngle = 0,
        fPrevAngle = 1234567;
    double      fNow = 0,
        fPrevNow = 0;

    SkScalar    fAngleSpeed = 0,
        fAngleSign = 1;

    static constexpr double kSlowDown = 4;
    static constexpr SkScalar kMaxSpeed = 16;

public:
    void update( SkV3 axis, SkScalar angle )
    {
        if ( angle != fPrevAngle )
        {
            fPrevAngle = fAngle;
            fAngle = angle;

            fPrevNow = fNow;
            fNow = SkTime::GetSecs( );

            fAxis = axis;
        }
    }

    SkM44 rotation( )
    {
        if ( fAngleSpeed > 0 )
        {
            double now = SkTime::GetSecs( );
            double dtime = now - fPrevNow;
            fPrevNow = now;
            double delta = fAngleSign * fAngleSpeed * dtime;
            fAngle += delta;
            fAngleSpeed -= kSlowDown * dtime;
            if ( fAngleSpeed < 0 )
            {
                fAngleSpeed = 0;
            }
        }
        return SkM44::Rotate( fAxis, fAngle );

    }

    void start( )
    {
        if ( fPrevNow != fNow )
        {
            fAngleSpeed = ( fAngle - fPrevAngle ) / ( fNow - fPrevNow );
            fAngleSign = fAngleSpeed < 0 ? -1 : 1;
            fAngleSpeed = std::min( kMaxSpeed, std::abs( fAngleSpeed ) );
        }
        else
        {
            fAngleSpeed = 0;
        }
        fPrevNow = SkTime::GetSecs( );
        fAngle = 0;
    }

    void reset( )
    {
        fAngleSpeed = 0;
        fAngle = 0;
        fPrevAngle = 1234567;
    }

    bool isAnimating( ) const { return fAngleSpeed != 0; }
};

class SampleCubeBase : public Sample3DView
{
    enum
    {
        DX = 400,
        DY = 300
    };

    SkM44 fRotation;        // part of model

    RotateAnimator fRotateAnimator;

protected:
    enum Flags
    {
        kCanRunOnCPU = 1 << 0,
        kShowLightDome = 1 << 1,
    };

    LightOnSphere fLight = { {200 + DX, 200 + DY}, 800, 12 };

    VSphere fSphere;
    Flags   fFlags;

public:
    SampleCubeBase( Flags flags )
        : fSphere( { 200 + DX, 200 + DY }, 400 )
        , fFlags( flags )
    {
    }

    bool onChar( SkUnichar uni ) override
    {
        switch ( uni )
        {
            case 'Z': fLight.fDistance += 10; return true;
            case 'z': fLight.fDistance -= 10; return true;
        }
        return this->Sample3DView::onChar( uni );
    }

    virtual void drawContent(
        SkCanvas* canvas, SkColor, int index, bool drawFront, const SkM44& localToWorld ) = 0;

    void onDrawContent( SkCanvas* canvas ) override
    {
        if ( !canvas->recordingContext( ) && !( fFlags & kCanRunOnCPU ) )
        {
            return;
        }

        canvas->save( );
        canvas->translate( DX, DY );

        this->concatCamera( canvas, { 0, 0, 400, 400 }, 200 );

        for ( bool drawFront : {false, true} )
        {
            int index = 0;
            for ( auto f : faces )
            {
                SkAutoCanvasRestore acr( canvas, true );

                SkM44 trans = SkM44::Translate( 200, 200, 0 );   // center of the rotation
                SkM44 m = fRotateAnimator.rotation( ) * fRotation * f.asM44( 200 );

                canvas->concat( trans );

                // "World" space - content is centered at the origin, in device scale (+-200)
                SkM44 localToWorld = m * inv( trans );

                canvas->concat( localToWorld );
                this->drawContent( canvas, f.fColor, index++, drawFront, localToWorld );
            }
        }

        canvas->restore( );  // camera & center the content in the window

        if ( fFlags & kShowLightDome )
        {
            fLight.draw( canvas );

            SkPaint paint;
            paint.setAntiAlias( true );
            paint.setStyle( SkPaint::kStroke_Style );
            paint.setColor( 0x40FF0000 );
            canvas->drawCircle( fSphere.fCenter.x, fSphere.fCenter.y, fSphere.fRadius, paint );
            canvas->drawLine( fSphere.fCenter.x, fSphere.fCenter.y - fSphere.fRadius,
                fSphere.fCenter.x, fSphere.fCenter.y + fSphere.fRadius, paint );
            canvas->drawLine( fSphere.fCenter.x - fSphere.fRadius, fSphere.fCenter.y,
                fSphere.fCenter.x + fSphere.fRadius, fSphere.fCenter.y, paint );
        }
    }

    Click* onFindClickHandler( SkScalar x, SkScalar y, skui::ModifierKey modi ) override
    {
        SkV2 p = fLight.fLoc - SkV2{ x, y };
        if ( p.length( ) <= fLight.fRadius )
        {
            Click* c = new Click( );
            c->fMeta.setS32( "type", 0 );
            return c;
        }
        if ( fSphere.contains( { x, y } ) )
        {
            Click* c = new Click( );
            c->fMeta.setS32( "type", 1 );

            fRotation = fRotateAnimator.rotation( ) * fRotation;
            fRotateAnimator.reset( );
            return c;
        }
        return nullptr;
    }
    bool onClick( Click* click ) override
    {
        if ( click->fMeta.hasS32( "type", 0 ) )
        {
            fLight.fLoc = fSphere.pinLoc( { click->fCurr.fX, click->fCurr.fY } );
            return true;
        }
        if ( click->fMeta.hasS32( "type", 1 ) )
        {
            if ( click->fState == skui::InputState::kUp )
            {
                fRotation = fRotateAnimator.rotation( ) * fRotation;
                fRotateAnimator.start( );
            }
            else
            {
                auto [axis, angle] = fSphere.computeRotationInfo(
                    { click->fOrig.fX, click->fOrig.fY },
                    { click->fCurr.fX, click->fCurr.fY } );
                fRotateAnimator.update( axis, angle );
            }
            return true;
        }
        return true;
    }

    bool onAnimate( double nanos ) override
    {
        return fRotateAnimator.isAnimating( );
    }

private:
    using INHERITED = Sample3DView;
};


#endif

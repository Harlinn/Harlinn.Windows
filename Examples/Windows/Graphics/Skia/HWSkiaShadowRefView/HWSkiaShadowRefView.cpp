/*
   Copyright 2024-2025 Espen Harlinn

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
#include "skia/core/SkImage.h"
#include "skia/core/SkPath.h"
#include "skia/core/SkPoint3.h"
#include "skia/utils/SkShadowUtils.h"
#include "skia/tools/Resources.h"

using namespace Harlinn::Windows::Skia;

////////////////////////////////////////////////////////////////////////////
// Sample to compare the Material Design shadow reference to our results

class ShadowRefView : public Sample
{
    SkPath         fRRectPath;
    sk_sp<SkImage> fReferenceImage;

    bool      fShowAmbient;
    bool      fShowSpot;
    bool      fUseAlt;
    bool      fShowObject;

public:
    ShadowRefView( )
        : fShowAmbient( true )
        , fShowSpot( true )
        , fUseAlt( false )
        , fShowObject( true )
    {
    }

protected:
    void onOnceBeforeDraw( ) override
    {
        fRRectPath.addRRect( SkRRect::MakeRectXY( SkRect::MakeXYWH( -130, -128.5, 130, 128.5 ), 4, 4 ) );
        fReferenceImage = GetResourceAsImage( "images/shadowreference.png" );
    }

    SkString name( ) override { return SkString( "ShadowReference" ); }

    bool onChar( SkUnichar uni ) override
    {
        bool handled = false;
        switch ( uni )
        {
            case 'W':
                fShowAmbient = !fShowAmbient;
                handled = true;
                break;
            case 'S':
                fShowSpot = !fShowSpot;
                handled = true;
                break;
            case 'T':
                fUseAlt = !fUseAlt;
                handled = true;
                break;
            case 'O':
                fShowObject = !fShowObject;
                handled = true;
                break;
            default:
                break;
        }
        if ( handled )
        {
            return true;
        }
        return false;
    }

    void drawBG( SkCanvas* canvas )
    {
        canvas->drawColor( 0xFFFFFFFF );
        canvas->drawImage( fReferenceImage, 10, 30 );
    }

    void drawShadowedPath( SkCanvas* canvas, const SkPath& path,
        const SkPoint3& zPlaneParams,
        const SkPaint& paint, SkScalar ambientAlpha,
        const SkPoint3& lightPos, SkScalar lightWidth, SkScalar spotAlpha )
    {
        if ( !fShowAmbient )
        {
            ambientAlpha = 0;
        }
        if ( !fShowSpot )
        {
            spotAlpha = 0;
        }
        uint32_t flags = 0;
        if ( fUseAlt )
        {
            flags |= SkShadowFlags::kGeometricOnly_ShadowFlag;
        }

        SkColor ambientColor = SkColorSetARGB( ambientAlpha * 255, 0, 0, 0 );
        SkColor spotColor = SkColorSetARGB( spotAlpha * 255, 0, 0, 0 );
        SkShadowUtils::DrawShadow( canvas, path, zPlaneParams,
            lightPos, lightWidth,
            ambientColor, spotColor, flags );

        if ( fShowObject )
        {
            canvas->drawPath( path, paint );
        }
        else
        {
            SkPaint strokePaint;

            strokePaint.setColor( paint.getColor( ) );
            strokePaint.setStyle( SkPaint::kStroke_Style );

            canvas->drawPath( path, strokePaint );
        }
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        this->drawBG( canvas );
        const SkScalar kDP = 4;  // the reference image is 4x bigger than it is displayed on
                                 // on the web page, so we need to reflect that here and
                                 // multiply the heights and light params accordingly
        const SkScalar kLightWidth = kDP * 400;
        const SkScalar kAmbientAlpha = 0.03f;
        const SkScalar kSpotAlpha = 0.35f;

        SkPaint paint;
        paint.setAntiAlias( true );
        paint.setColor( SK_ColorWHITE );

        SkPoint3 lightPos = { 175, -800, kDP * 600 };
        SkScalar xPos = 230;
        SkScalar yPos = 254.25f;
        SkRect clipRect = SkRect::MakeXYWH( 45, 75, 122, 250 );
        SkPoint clipDelta = SkPoint::Make( 320, 0 );
        SkPoint3 zPlaneParams = SkPoint3::Make( 0, 0, kDP * 2 );

        canvas->save( );
        canvas->clipRect( clipRect );
        canvas->translate( xPos, yPos );
        this->drawShadowedPath( canvas, fRRectPath, zPlaneParams, paint, kAmbientAlpha,
            lightPos, kLightWidth, kSpotAlpha );
        canvas->restore( );

        lightPos.fX += 320;
        xPos += 320;
        clipRect.offset( clipDelta );
        zPlaneParams.fZ = kDP * 3;
        canvas->save( );
        canvas->clipRect( clipRect );
        canvas->translate( xPos, yPos );
        this->drawShadowedPath( canvas, fRRectPath, zPlaneParams, paint, kAmbientAlpha,
            lightPos, kLightWidth, kSpotAlpha );
        canvas->restore( );

        lightPos.fX += 320;
        xPos += 320;
        clipRect.offset( clipDelta );
        zPlaneParams.fZ = kDP * 4;
        canvas->save( );
        canvas->clipRect( clipRect );
        canvas->translate( xPos, yPos );
        this->drawShadowedPath( canvas, fRRectPath, zPlaneParams, paint, kAmbientAlpha,
            lightPos, kLightWidth, kSpotAlpha );
        canvas->restore( );

        lightPos.fX += 320;
        xPos += 320;
        clipRect.offset( clipDelta );
        zPlaneParams.fZ = kDP * 6;
        canvas->save( );
        canvas->clipRect( clipRect );
        canvas->translate( xPos, yPos );
        this->drawShadowedPath( canvas, fRRectPath, zPlaneParams, paint, kAmbientAlpha,
            lightPos, kLightWidth, kSpotAlpha );
        canvas->restore( );

        lightPos.fX += 320;
        xPos += 320;
        clipRect.offset( clipDelta );
        zPlaneParams.fZ = kDP * 8;
        canvas->save( );
        canvas->clipRect( clipRect );
        canvas->translate( xPos, yPos );
        this->drawShadowedPath( canvas, fRRectPath, zPlaneParams, paint, kAmbientAlpha,
            lightPos, kLightWidth, kSpotAlpha );
        canvas->restore( );

        lightPos.fX += 320;
        xPos += 320;
        clipRect.offset( clipDelta );
        zPlaneParams.fZ = kDP * 16;
        canvas->save( );
        canvas->clipRect( clipRect );
        canvas->translate( xPos, yPos );
        this->drawShadowedPath( canvas, fRRectPath, zPlaneParams, paint, kAmbientAlpha,
            lightPos, kLightWidth, kSpotAlpha );
        canvas->restore( );

    }

private:
    using INHERITED = Sample;
};

int main()
{
    int result = SampleApplication<ShadowRefView>::Run( );
    return result;
}


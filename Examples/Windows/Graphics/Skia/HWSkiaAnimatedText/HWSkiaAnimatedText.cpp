/*
   Copyright 2024 Espen Harlinn

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

#include "skia/core/SkColorFilter.h"
#include "skia/core/SkColorPriv.h"
#include "skia/core/SkFont.h"
#include "skia/core/SkImage.h"
#include "skia/core/SkTime.h"
#include "skia/core/SkTypeface.h"
#include "skia/utils/SkRandom.h"
#include "src/utils/SkUTF.h"

#if SK_SUPPORT_GPU
#include "skia/gpu/GrDirectContext.h"
#include "src/gpu/GrDirectContextPriv.h"
#endif

SkRandom gRand;

static void DrawTheText( SkCanvas* canvas, const char text[], size_t length, SkScalar x, SkScalar y,
    const SkFont& font, const SkPaint& paint )
{
    SkFont f( font );
    f.setSubpixel( true );
    canvas->drawSimpleText( text, length, SkTextEncoding::kUTF8, x, y, f, paint );
}

// This sample demonstrates the cache behavior of bitmap vs. distance field text
// It renders variously sized text with an animated scale and rotation.
// Specifically one should:
//   use 'D' to toggle between bitmap and distance field fonts
//   use '2' to toggle between scaling the image by 2x
//            -- this feature boosts the rendering out of the small point-size
//               SDF-text special case (which falls back to bitmap fonts for small points)

class AnimatedTextView : public Harlinn::Windows::Skia::Sample
{
    float fScale = 1;
    float fScaleInc = 0.1f;
    float fRotation = 0;
    int   fSizeScale = 1;

    SkString name( ) override { return SkString( "AnimatedText" ); }

    bool onChar( SkUnichar uni ) override
    {
        if ( '2' == uni )
        {
            if ( fSizeScale == 2 )
            {
                fSizeScale = 1;
            }
            else
            {
                fSizeScale = 2;
            }
            return true;
        }
        return false;
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        SkFont font( SkTypeface::MakeFromFile( "/skimages/samplefont.ttf" ) );

        SkPaint paint;
        paint.setAntiAlias( true );

        canvas->save( );

#if SK_SUPPORT_GPU
        auto direct = GrAsDirectContext( canvas->recordingContext( ) );
        if ( direct )
        {
            SkSamplingOptions sampling( SkFilterMode::kLinear, SkMipmapMode::kNearest );
            sk_sp<SkImage> image = direct->priv( ).testingOnly_getFontAtlasImage(
                GrMaskFormat::kA8_GrMaskFormat );
            const SkRect rect = SkRect::MakeXYWH( 512.0f, 10.0f, 512.0f, 512.0f );
            canvas->drawImageRect( image.get( ), rect, rect, sampling, &paint,
                SkCanvas::kFast_SrcRectConstraint );
        }
#endif
        canvas->translate( 180, 180 );
        canvas->rotate( fRotation );
        canvas->scale( fScale, fScale );
        canvas->translate( -180, -180 );

        const char* text = "Hamburgefons";
        size_t length = strlen( text );

        SkScalar y = SkIntToScalar( 0 );
        for ( int i = 12; i <= 26; i++ )
        {
            font.setSize( SkIntToScalar( i * fSizeScale ) );
            y += font.getSpacing( );
            DrawTheText( canvas, text, length, SkIntToScalar( 110 ), y, font, paint );
        }
        canvas->restore( );

        font.setSize( 16 );
    }

    bool onAnimate( double nanos ) override
    {
        // TODO: use nanos
        // We add noise to the scale and rotation animations to
        // keep the font atlas from falling into a steady state
        fRotation += ( 1.0f + gRand.nextRangeF( -0.1f, 0.1f ) );
        fScale += ( fScaleInc + gRand.nextRangeF( -0.025f, 0.025f ) );
        if ( fScale >= 2.0f )
        {
            fScaleInc = -0.1f;
        }
        else if ( fScale <= 1.0f )
        {
            fScaleInc = 0.1f;
        }
        return true;
    }
};

int main()
{
    using namespace Harlinn::Windows::Skia;
    int result = SampleApplication<AnimatedTextView>::Run( );
    return result;
}


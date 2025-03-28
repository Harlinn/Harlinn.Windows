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
#include "skia/core/SkBitmap.h"
#include "skia/core/SkCanvas.h"
#include "skia/core/SkColorPriv.h"
#include "skia/core/SkShader.h"

using namespace Harlinn::Windows::Skia;


static const SkBlendMode gModes[] = {
    SkBlendMode::kClear,
    SkBlendMode::kSrc,
    SkBlendMode::kDst,
    SkBlendMode::kSrcOver,
    SkBlendMode::kDstOver,
    SkBlendMode::kSrcIn,
    SkBlendMode::kDstIn,
    SkBlendMode::kSrcOut,
    SkBlendMode::kDstOut,
    SkBlendMode::kSrcATop,
    SkBlendMode::kDstATop,
    SkBlendMode::kXor,
};

const int gWidth = 64;
const int gHeight = 64;
const SkScalar W = SkIntToScalar( gWidth );
const SkScalar H = SkIntToScalar( gHeight );

static SkScalar drawCell( SkCanvas* canvas, SkBlendMode mode, SkAlpha a0, SkAlpha a1 )
{
    SkPaint paint;
    paint.setAntiAlias( true );

    SkRect r = SkRect::MakeWH( W, H );
    r.inset( W / 10, H / 10 );

    paint.setColor( SK_ColorBLUE );
    paint.setAlpha( a0 );
    canvas->drawOval( r, paint );

    paint.setColor( SK_ColorRED );
    paint.setAlpha( a1 );
    paint.setBlendMode( mode );
    for ( int angle = 0; angle < 24; ++angle )
    {
        SkScalar x = SkScalarCos( SkIntToScalar( angle ) * ( SK_ScalarPI * 2 ) / 24 ) * gWidth;
        SkScalar y = SkScalarSin( SkIntToScalar( angle ) * ( SK_ScalarPI * 2 ) / 24 ) * gHeight;
        paint.setStrokeWidth( SK_Scalar1 * angle * 2 / 24 );
        canvas->drawLine( W / 2, H / 2, W / 2 + x, H / 2 + y, paint );
    }

    return H;
}

static sk_sp<SkShader> make_bg_shader( )
{
    SkBitmap bm;
    bm.allocN32Pixels( 2, 2 );
    *bm.getAddr32( 0, 0 ) = *bm.getAddr32( 1, 1 ) = 0xFFFFFFFF;
    *bm.getAddr32( 1, 0 ) = *bm.getAddr32( 0, 1 ) = SkPackARGB32( 0xFF, 0xCC, 0xCC, 0xCC );

    return bm.makeShader( SkTileMode::kRepeat, SkTileMode::kRepeat, SkSamplingOptions( ),
        SkMatrix::Scale( 6, 6 ) );
}

class HairModesView : public Sample
{
    SkPaint fBGPaint;
public:
    HairModesView( )
    {
        fBGPaint.setShader( make_bg_shader( ) );
    }

protected:
    SkString name( ) override { return SkString( "HairlineModes" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        const SkRect bounds = SkRect::MakeWH( W, H );
        static const SkAlpha gAlphaValue[] = { 0xFF, 0x88, 0x88 };

        canvas->translate( SkIntToScalar( 4 ), SkIntToScalar( 4 ) );

        for ( int alpha = 0; alpha < 4; ++alpha )
        {
            canvas->save( );
            canvas->save( );
            for ( size_t i = 0; i < SK_ARRAY_COUNT( gModes ); ++i )
            {
                if ( 6 == i )
                {
                    canvas->restore( );
                    canvas->translate( W * 5, 0 );
                    canvas->save( );
                }
                canvas->drawRect( bounds, fBGPaint );
                canvas->saveLayer( &bounds, nullptr );
                SkScalar dy = drawCell( canvas, gModes[i],
                    gAlphaValue[alpha & 1],
                    gAlphaValue[alpha & 2] );
                canvas->restore( );

                canvas->translate( 0, dy * 5 / 4 );
            }
            canvas->restore( );
            canvas->restore( );
            canvas->translate( W * 5 / 4, 0 );
        }
    }

private:
    using INHERITED = Sample;
};




int main()
{
    int result = SampleApplication<HairModesView>::Run( );
    return result;
}


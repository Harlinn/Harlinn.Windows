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
#include "skia/core/SkBitmap.h"
#include "skia/core/SkCanvas.h"
#include "skia/core/SkShader.h"

using namespace Harlinn::Windows::Skia;


static void make_bitmap( SkBitmap* bm )
{
    const int W = 100;
    const int H = 100;
    bm->allocN32Pixels( W, H );

    SkPaint paint;
    SkCanvas canvas( *bm );
    canvas.drawColor( SK_ColorWHITE );

    const SkColor colors[] = {
        SK_ColorRED, SK_ColorGREEN, SK_ColorBLUE, SK_ColorWHITE
    };

    for ( int ix = 0; ix < W; ix += 1 )
    {
        SkScalar x = SkIntToScalar( ix ) + SK_ScalarHalf;
        paint.setColor( colors[ix & 3] );
        canvas.drawLine( x, 0, x, SkIntToScalar( H - 1 ), paint );
    }
    paint.setColor( SK_ColorGRAY );
    canvas.drawLine( 0, 0, SkIntToScalar( W ), 0, paint );
}

static void make_paint( SkPaint* paint, SkTileMode tm )
{
    SkBitmap bm;
    make_bitmap( &bm );

    paint->setShader( bm.makeShader( tm, tm, SkSamplingOptions( ) ) );
}

class RepeatTileView : public Sample
{
public:
    RepeatTileView( )
    {
        this->setBGColor( SK_ColorGRAY );
    }

protected:
    SkString name( ) override { return SkString( "RepeatTile" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        SkPaint paint;
        make_paint( &paint, SkTileMode::kRepeat );

        //        canvas->scale(SK_Scalar1*2, SK_Scalar1);
        canvas->translate( SkIntToScalar( 100 ), SkIntToScalar( 100 ) );
        canvas->drawPaint( paint );
    }

private:
    using INHERITED = Sample;
};


int main()
{
    int result = SampleApplication<RepeatTileView>::Run( );
    return result;
}


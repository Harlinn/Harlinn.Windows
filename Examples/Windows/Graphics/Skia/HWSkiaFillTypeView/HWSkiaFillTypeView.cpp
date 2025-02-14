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
#include "skia/core/SkCanvas.h"
#include "skia/core/SkPath.h"
#include "skia/core/SkRegion.h"
#include "skia/core/SkShader.h"
#include "skia/effects/SkCornerPathEffect.h"
#include "skia/effects/SkGradientShader.h"
#include "src/utils/SkUTF.h"

using namespace Harlinn::Windows::Skia;

class FillTypeView : public Sample
{
    SkPath fPath;
public:
    FillTypeView( )
    {
        const SkScalar radius = SkIntToScalar( 45 );
        fPath.addCircle( SkIntToScalar( 50 ), SkIntToScalar( 50 ), radius );
        fPath.addCircle( SkIntToScalar( 100 ), SkIntToScalar( 100 ), radius );

        this->setBGColor( 0xFFDDDDDD );
    }

protected:
    SkString name( ) override { return SkString( "FillType" ); }

    void showPath( SkCanvas* canvas, int x, int y, SkPathFillType ft,
        SkScalar scale, const SkPaint& paint )
    {

        const SkRect r = { 0, 0, SkIntToScalar( 150 ), SkIntToScalar( 150 ) };

        canvas->save( );
        canvas->translate( SkIntToScalar( x ), SkIntToScalar( y ) );
        canvas->clipRect( r );
        canvas->drawColor( SK_ColorWHITE );
        fPath.setFillType( ft );
        canvas->translate( r.centerX( ), r.centerY( ) );
        canvas->scale( scale, scale );
        canvas->translate( -r.centerX( ), -r.centerY( ) );
        canvas->drawPath( fPath, paint );
        canvas->restore( );
    }

    void showFour( SkCanvas* canvas, SkScalar scale, const SkPaint& paint )
    {
        showPath( canvas, 0, 0, SkPathFillType::kWinding,
            scale, paint );
        showPath( canvas, 200, 0, SkPathFillType::kEvenOdd,
            scale, paint );
        showPath( canvas, 00, 200, SkPathFillType::kInverseWinding,
            scale, paint );
        showPath( canvas, 200, 200, SkPathFillType::kInverseEvenOdd,
            scale, paint );
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        canvas->translate( SkIntToScalar( 20 ), SkIntToScalar( 20 ) );

        SkPaint paint;
        const SkScalar scale = SkIntToScalar( 5 ) / 4;

        paint.setAntiAlias( false );
        paint.setColor( 0x8000FF00 );

        showFour( canvas, SK_Scalar1, paint );
        canvas->translate( SkIntToScalar( 450 ), 0 );
        showFour( canvas, scale, paint );

        paint.setAntiAlias( true );

        canvas->translate( SkIntToScalar( -450 ), SkIntToScalar( 450 ) );
        showFour( canvas, SK_Scalar1, paint );
        canvas->translate( SkIntToScalar( 450 ), 0 );
        showFour( canvas, scale, paint );
    }

private:
    using INHERITED = Sample;
};

int main()
{
    int result = SampleApplication<FillTypeView>::Run( );
    return result;
}


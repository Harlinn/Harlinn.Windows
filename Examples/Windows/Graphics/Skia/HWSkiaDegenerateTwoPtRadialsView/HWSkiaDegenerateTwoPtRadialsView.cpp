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
#include "skia/core/SkFont.h"
#include "skia/core/SkString.h"
#include "skia/effects/SkGradientShader.h"

using namespace Harlinn::Windows::Skia;

static void draw_gradient2( SkCanvas* canvas, const SkRect& rect, SkScalar delta )
{
    SkColor colors[] = { SK_ColorRED, SK_ColorGREEN, SK_ColorBLUE, SK_ColorMAGENTA };
    SkScalar pos[] = { 0, 0.25f, 0.75f, SK_Scalar1 };

    SkScalar l = rect.fLeft;
    SkScalar t = rect.fTop;
    SkScalar w = rect.width( );
    SkScalar h = rect.height( );

    SkASSERT( 0 == SkScalarMod( w, SK_Scalar1 * 5 ) );

    SkPoint c0 = { l + 2 * w / 5 + delta, t + h / 2 };
    SkPoint c1 = { l + 3 * w / 5, t + h / 2 };
    SkScalar r0 = w / 5;
    SkScalar r1 = 2 * w / 5;
    SkPaint paint;
    paint.setShader( SkGradientShader::MakeTwoPointConical( c0, r0, c1, r1, colors,
        pos, SK_ARRAY_COUNT( pos ),
        SkTileMode::kClamp ) );
    canvas->drawRect( rect, paint );
}


class DegenerateTwoPtRadialsView : public Sample
{
public:
    DegenerateTwoPtRadialsView( )
    {
        fTime = 0;
        this->setBGColor( 0xFFDDDDDD );
    }

protected:
    SkString name( ) override { return SkString( "DegenerateTwoPtRadials" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        SkScalar delta = fTime / 15.f;
        int intPart = SkScalarFloorToInt( delta );
        delta = delta - SK_Scalar1 * intPart;
        if ( intPart % 2 )
        {
            delta = SK_Scalar1 - delta;
        }
        delta -= SK_ScalarHalf;
        static const int DELTA_SCALE = 500;
        delta /= DELTA_SCALE;

        SkScalar w = SK_Scalar1 * 500;
        SkScalar h = SK_Scalar1 * 500;
        SkScalar l = SK_Scalar1 * 100;
        SkScalar t = SK_Scalar1 * 100;
        draw_gradient2( canvas, SkRect::MakeXYWH( l, t, w, h ), delta );
        SkString txt;
        txt.appendf( "gap at \"tangent\" pt = %f", SkScalarToFloat( delta ) );
        canvas->drawString( txt, l + w / 2 + w * DELTA_SCALE * delta, t + h + SK_Scalar1 * 10,
            SkFont( ), SkPaint( ) );
    }

    bool onAnimate( double nanos ) override
    {
        fTime = SkDoubleToScalar( 1e-9 * nanos / 15 );
        return true;
    }

private:
    SkScalar           fTime;
    using INHERITED = Sample;
};


int main( )
{
    int result = SampleApplication<DegenerateTwoPtRadialsView>::Run( );
    return result;
}


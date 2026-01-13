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
#include "skia/effects/SkGradientShader.h"

using namespace Harlinn::Windows::Skia;

class TwoPtConicalView : public Sample
{
public:
    TwoPtConicalView( ) {}

protected:
    SkString name( ) override { return SkString( "2PtConical" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        canvas->translate( SkIntToScalar( 10 ), SkIntToScalar( 20 ) );

        SkColor colors[] = { SK_ColorRED, SK_ColorBLUE };
        SkPoint c0 = { 0, 0 };
        SkScalar r0 = 100;
        SkPoint c1 = { 100, 100 };
        SkScalar r1 = 100;
        SkPaint paint;
        paint.setShader( SkGradientShader::MakeTwoPointConical( c0, r0, c1, r1, colors,
            nullptr, 2,
            SkTileMode::kClamp ) );
        canvas->drawPaint( paint );
    }

private:
    using INHERITED = Sample;
};

int main()
{
    int result = SampleApplication<TwoPtConicalView>::Run( );
    return result;
}


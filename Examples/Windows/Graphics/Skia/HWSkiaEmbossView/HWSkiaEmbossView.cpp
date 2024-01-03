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
#include "skia/core/SkGraphics.h"
#include "skia/core/SkPath.h"
#include "skia/core/SkRegion.h"
#include "skia/core/SkShader.h"
#include "skia/core/SkTime.h"
#include "skia/core/SkTypeface.h"
#include "skia/effects/SkGradientShader.h"
#include "skia/utils/SkRandom.h"
#include "src/core/SkBlurMask.h"
#include "src/effects/SkEmbossMaskFilter.h"
#include "src/utils/SkUTF.h"

using namespace Harlinn::Windows::Skia;


class EmbossView : public Sample
{
    SkEmbossMaskFilter::Light   fLight;
public:
    EmbossView( )
    {
        fLight.fDirection[0] = SK_Scalar1;
        fLight.fDirection[1] = SK_Scalar1;
        fLight.fDirection[2] = SK_Scalar1;
        fLight.fAmbient = 128;
        fLight.fSpecular = 16 * 2;
    }

protected:
    SkString name( ) override { return SkString( "Emboss" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        SkPaint paint;

        paint.setAntiAlias( true );
        paint.setStyle( SkPaint::kStroke_Style );
        paint.setStrokeWidth( SkIntToScalar( 10 ) );
        paint.setMaskFilter( SkEmbossMaskFilter::Make( SkBlurMask::ConvertRadiusToSigma( 4 ), fLight ) );
        paint.setShader( SkShaders::Color( SK_ColorBLUE ) );
        paint.setDither( true );

        canvas->drawCircle( SkIntToScalar( 50 ), SkIntToScalar( 50 ),
            SkIntToScalar( 30 ), paint );
    }

private:

    using INHERITED = Sample;
};


int main( )
{
    int result = SampleApplication<EmbossView>::Run( );
    return result;
}


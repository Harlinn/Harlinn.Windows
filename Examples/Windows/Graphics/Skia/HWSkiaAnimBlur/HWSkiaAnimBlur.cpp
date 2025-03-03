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
#include "skia/core/SkColorPriv.h"
#include "skia/core/SkMaskFilter.h"
#include "skia/utils/SkRandom.h"

SkScalar get_anim_sin( double secs, SkScalar amplitude, SkScalar periodInSec, SkScalar phaseInSec )
{
    if ( !periodInSec )
    {
        return 0;
    }
    double t = secs + phaseInSec;
    t *= SkScalarToFloat( 2 * SK_ScalarPI ) / periodInSec;
    amplitude = SK_ScalarHalf * amplitude;
    return amplitude * SkDoubleToScalar( sin( t ) ) + amplitude;
}

class AnimBlurView : public Harlinn::Windows::Skia::Sample
{
    SkScalar fBlurSigma = 0;
    SkScalar fCircleRadius = 100;

    SkString name( ) override { return SkString( "AnimBlur" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        static const SkBlurStyle gStyles[] = {
            kNormal_SkBlurStyle,
            kInner_SkBlurStyle,
            kSolid_SkBlurStyle,
            kOuter_SkBlurStyle,
        };
        SkRandom random;

        for ( size_t i = 0; i < SK_ARRAY_COUNT( gStyles ); ++i )
        {
            SkPaint paint;
            paint.setMaskFilter( SkMaskFilter::MakeBlur( gStyles[i],
                fBlurSigma ) );
            paint.setColor( random.nextU( ) | 0xff000000 );
            canvas->drawCircle( 200 * SK_Scalar1 + 400 * ( i % 2 ) * SK_Scalar1,
                200 * SK_Scalar1 + i / 2 * 400 * SK_Scalar1,
                fCircleRadius, paint );
        }
    }

    bool onAnimate( double nanos ) override
    {
        fBlurSigma = get_anim_sin( 1e-9 * nanos, 100, 4, 5 );
        fCircleRadius = 3 + get_anim_sin( 1e-9 * nanos, 150, 25, 3 );
        return true;
    }
};

int main()
{
    using namespace Harlinn::Windows::Skia;
    int result = SampleApplication<AnimBlurView>::Run( );
    return result;
}

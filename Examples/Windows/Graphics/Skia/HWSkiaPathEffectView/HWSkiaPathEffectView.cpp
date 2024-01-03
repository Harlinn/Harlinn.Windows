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

#include "skia/core/SkCanvas.h"
#include "skia/core/SkColorPriv.h"
#include "skia/core/SkPath.h"
#include "skia/core/SkPathMeasure.h"
#include "skia/core/SkRegion.h"
#include "skia/core/SkShader.h"
#include "skia/core/SkColorFilter.h"
#include "skia/effects/Sk1DPathEffect.h"
#include "skia/effects/SkCornerPathEffect.h"
#include "skia/effects/SkGradientShader.h"
#include "skia/utils/SkRandom.h"
#include "src/utils/SkUTF.h"
#include "skia/tools/timer/TimeUtils.h"

using namespace Harlinn::Windows::Skia;



#define CORNER_RADIUS   12

static const int gXY[] = {
    4, 0, 0, -4, 8, -4, 12, 0, 8, 4, 0, 4
};

static sk_sp<SkPathEffect> make_pe( int flags, SkScalar phase )
{
    if ( flags == 1 )
    {
        return SkCornerPathEffect::Make( SkIntToScalar( CORNER_RADIUS ) );
    }

    SkPath  path;
    path.moveTo( SkIntToScalar( gXY[0] ), SkIntToScalar( gXY[1] ) );
    for ( unsigned i = 2; i < SK_ARRAY_COUNT( gXY ); i += 2 )
        path.lineTo( SkIntToScalar( gXY[i] ), SkIntToScalar( gXY[i + 1] ) );
    path.close( );
    path.offset( SkIntToScalar( -6 ), 0 );

    auto outer = SkPath1DPathEffect::Make( path, 12, phase, SkPath1DPathEffect::kRotate_Style );

    if ( flags == 2 )
        return outer;

    auto inner = SkCornerPathEffect::Make( SkIntToScalar( CORNER_RADIUS ) );

    return SkPathEffect::MakeCompose( outer, inner );
}

static sk_sp<SkPathEffect> make_warp_pe( SkScalar phase )
{
    SkPath  path;
    path.moveTo( SkIntToScalar( gXY[0] ), SkIntToScalar( gXY[1] ) );
    for ( unsigned i = 2; i < SK_ARRAY_COUNT( gXY ); i += 2 )
    {
        path.lineTo( SkIntToScalar( gXY[i] ), SkIntToScalar( gXY[i + 1] ) );
    }
    path.close( );
    path.offset( SkIntToScalar( -6 ), 0 );

    auto outer = SkPath1DPathEffect::Make(
        path, 12, phase, SkPath1DPathEffect::kMorph_Style );
    auto inner = SkCornerPathEffect::Make( SkIntToScalar( CORNER_RADIUS ) );

    return SkPathEffect::MakeCompose( outer, inner );
}

///////////////////////////////////////////////////////////



class PathEffectView : public Sample
{
    SkPath  fPath;
    SkPoint fClickPt;
    SkScalar fPhase;

public:
    PathEffectView( ) : fPhase( 0 )
    {
    }

protected:
    void onOnceBeforeDraw( ) override
    {
        SkRandom    rand;
        int         steps = 20;
        SkScalar    dist = SkIntToScalar( 400 );
        SkScalar    x = SkIntToScalar( 20 );
        SkScalar    y = SkIntToScalar( 50 );

        fPath.moveTo( x, y );
        for ( int i = 0; i < steps; i++ )
        {
            x += dist / steps;
            SkScalar tmpY = y + SkIntToScalar( rand.nextS( ) % 25 );
            if ( i == steps / 2 )
            {
                fPath.moveTo( x, tmpY );
            }
            else
            {
                fPath.lineTo( x, tmpY );
            }
        }

        {
            SkRect  oval;
            oval.setLTRB( 20, 30, 100, 60 );
            oval.offset( x, 0 );
            fPath.addRoundRect( oval, SkIntToScalar( 8 ), SkIntToScalar( 8 ) );
        }

        fClickPt.set( SkIntToScalar( 200 ), SkIntToScalar( 200 ) );

        this->setBGColor( 0xFFDDDDDD );
    }

    SkString name( ) override { return SkString( "PathEffects" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        SkPaint paint;

        canvas->translate( 0, 50 );

        paint.setColor( SK_ColorBLUE );
        paint.setPathEffect( make_pe( 2, fPhase ) );
        canvas->drawPath( fPath, paint );

        canvas->translate( 0, 50 );

        paint.setARGB( 0xFF, 0, 0xBB, 0 );
        paint.setPathEffect( make_pe( 3, fPhase ) );
        canvas->drawPath( fPath, paint );

        canvas->translate( 0, 50 );

        paint.setARGB( 0xFF, 0, 0, 0 );
        paint.setPathEffect( make_warp_pe( fPhase ) );
        canvas->drawPath( fPath, paint );
    }

    bool onAnimate( double nanos ) override
    {
        fPhase = TimeUtils::Scaled( 1e-9 * nanos, 40 );
        return true;
    }

private:
    using INHERITED = Sample;
};



int main()
{
    int result = SampleApplication<PathEffectView>::Run( );
    return result;
}


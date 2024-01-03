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
#include "skia/core/SkColorFilter.h"
#include "skia/core/SkColorPriv.h"
#include "skia/core/SkFont.h"
#include "skia/core/SkImage.h"
#include "skia/core/SkTime.h"
#include "skia/core/SkTypeface.h"
#include "skia/utils/SkRandom.h"
#include "skia/tools/timer/Timer.h"


using namespace Harlinn::Windows::Skia;


// Create an animation of a bunch of letters that rotate in place. This is intended to stress
// the glyph atlas and test that we don't see corruption or bad slowdowns.
class FlutterAnimateView : public Sample
{
public:
    FlutterAnimateView( ) : fCurrTime( 0 ), fResetTime( 0 ) {}

protected:
    void onOnceBeforeDraw( ) override
    {
        fTypeface = SkTypeface::MakeFromFile( "/skimages/samplefont.ttf" );
        initChars( );
    }

    SkString name( ) override { return SkString( "FlutterAnimate" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        SkFont font( fTypeface, 50 );
        SkPaint paint;

        // rough center of each glyph
        static constexpr auto kMidX = 35;
        static constexpr auto kMidY = 50;

        canvas->clear( SK_ColorWHITE );
        for ( int i = 0; i < kNumChars; ++i )
        {
            canvas->save( );
            double rot = SkScalarInterp( fChars[i].fStartRotation, fChars[i].fEndRotation,
                fCurrTime / kDuration );
            canvas->translate( fChars[i].fPosition.fX + kMidX, fChars[i].fPosition.fY - kMidY );
            canvas->rotate( SkRadiansToDegrees( rot ) );
            canvas->translate( -35, +50 );
            canvas->drawString( fChars[i].fChar, 0, 0, font, paint );
            canvas->restore( );
        }
    }

    bool onAnimate( double nanos ) override
    {
        fCurrTime = 1e-9 * nanos - fResetTime;
        if ( fCurrTime > kDuration )
        {
            this->initChars( );
            fResetTime = 1e-9 * nanos;
            fCurrTime = 0;
        }

        return true;
    }

private:
    void initChars( )
    {
        for ( int i = 0; i < kNumChars; ++i )
        {
            char c = fRand.nextULessThan( 26 ) + 65;
            fChars[i].fChar[0] = c;
            fChars[i].fChar[1] = '\0';
            fChars[i].fPosition = SkPoint::Make( fRand.nextF( ) * 748 + 10, fRand.nextF( ) * 1004 + 10 );
            fChars[i].fStartRotation = fRand.nextF( );
            fChars[i].fEndRotation = fRand.nextF( ) * 20 - 10;
        }
    }

    static constexpr double kDuration = 5.0;
    double fCurrTime;
    double fResetTime;
    SkRandom fRand;

    struct AnimatedChar
    {
        char fChar[2];
        SkPoint  fPosition;
        SkScalar fStartRotation;
        SkScalar fEndRotation;
    };
    sk_sp<SkTypeface> fTypeface;
    static constexpr int kNumChars = 40;
    AnimatedChar fChars[kNumChars];

    using INHERITED = Sample;
};



int main()
{
    int result = SampleApplication<FlutterAnimateView>::Run( );
    return result;
}


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

#include "skia/android/SkAnimatedImage.h"
#include "skia/codec/SkAndroidCodec.h"
#include "skia/core/SkCanvas.h"
#include "skia/core/SkFont.h"
#include "skia/core/SkPaint.h"
#include "skia/core/SkPictureRecorder.h"
#include "skia/core/SkRect.h"
#include "skia/core/SkScalar.h"
#include "skia/core/SkString.h"
#include "skia/tools/timer/TimeUtils.h"
#include "skia/tools/Resources.h"


static constexpr char kPauseKey = 'p';
static constexpr char kResetKey = 'r';

class SampleAnimatedImage : public Harlinn::Windows::Skia::Sample
{
    sk_sp<SkAnimatedImage>  fImage;
    sk_sp<SkDrawable>       fDrawable;
    SkScalar                fYOffset = 0;
    bool                    fRunning = false;
    double                  fCurrentTime = 0.0;
    double                  fLastWallTime = 0.0;
    double                  fTimeToShowNextFrame = 0.0;

    void onDrawBackground( SkCanvas* canvas ) override
    {
        canvas->clear( SK_ColorWHITE );
        SkFont font;
        font.setSize( 20 );

        SkString str = SkStringPrintf( "Press '%c' to start/pause; '%c' to reset.",
            kPauseKey, kResetKey );
        const char* text = str.c_str( );
        SkRect bounds;
        font.measureText( text, strlen( text ), SkTextEncoding::kUTF8, &bounds );
        fYOffset = bounds.height( );

        canvas->drawSimpleText( text, strlen( text ), SkTextEncoding::kUTF8, 5, fYOffset, font, SkPaint( ) );
        fYOffset *= 2;
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        if ( !fImage )
        {
            return;
        }

        canvas->translate( 0, fYOffset );

        canvas->drawDrawable( fImage.get( ) );
        canvas->drawDrawable( fDrawable.get( ), fImage->getBounds( ).width( ), 0 );
    }

    bool onAnimate( double nanos ) override
    {
        if ( !fImage )
        {
            return false;
        }

        const double lastWallTime = fLastWallTime;
        fLastWallTime = TimeUtils::NanosToMSec( nanos );

        if ( fRunning )
        {
            fCurrentTime += fLastWallTime - lastWallTime;
            if ( fCurrentTime > fTimeToShowNextFrame )
            {
                fTimeToShowNextFrame += fImage->decodeNextFrame( );
                if ( fImage->isFinished( ) )
                {
                    fRunning = false;
                }
            }
        }

        return true;
    }

    void onOnceBeforeDraw( ) override
    {
        sk_sp<SkData> file( GetResourceAsData( "images/alphabetAnim.gif" ) );
        std::unique_ptr<SkCodec> codec( SkCodec::MakeFromData( file ) );
        if ( !codec )
        {
            return;
        }

        fImage = SkAnimatedImage::Make( SkAndroidCodec::MakeFromCodec( std::move( codec ) ) );
        if ( !fImage )
        {
            return;
        }

        fTimeToShowNextFrame = fImage->currentFrameDuration( );
        SkPictureRecorder recorder;
        auto canvas = recorder.beginRecording( fImage->getBounds( ) );
        canvas->drawDrawable( fImage.get( ) );
        fDrawable = recorder.finishRecordingAsDrawable( );
    }

    SkString name( ) override { return SkString( "AnimatedImage" ); }

    bool onChar( SkUnichar uni ) override
    {
        if ( fImage )
        {
            switch ( uni )
            {
                case kPauseKey:
                    fRunning = !fRunning;
                    if ( !fImage->isFinished( ) )
                    {
                        return true;
                    }
                    [[fallthrough]];
                case kResetKey:
                    fImage->reset( );
                    fCurrentTime = fLastWallTime;
                    fTimeToShowNextFrame = fCurrentTime + fImage->currentFrameDuration( );
                    return true;
                default:
                    break;
            }
        }
        return false;
    }
};


int main()
{
    using namespace Harlinn::Windows::Skia;
    int result = SampleApplication<SampleAnimatedImage>::Run( );
    return result;
}

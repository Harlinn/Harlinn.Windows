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


/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <HWSkiaSample.h>

#include "skia/tools/ToolUtils.h"

#include "skia/core/SkCanvas.h"
#include "skia/core/SkPath.h"
#include "skia/core/SkRRect.h"
#include "skia/core/SkTypeface.h"
#include "skia/utils/SkRandom.h"
#include "skia/tools/timer/TimeUtils.h"

#include <cmath>

using namespace Harlinn::Windows::Skia;


// Implementation in C++ of Animated Emoji
// See https://t.d3fc.io/status/705212795936247808
// See https://crbug.com/848616

class GlyphTransformView : public Sample
{
public:
    GlyphTransformView( ) {}

protected:
    void onOnceBeforeDraw( ) override
    {
        fEmojiFont.fTypeface = ToolUtils::emoji_typeface( );
        fEmojiFont.fText = ToolUtils::emoji_sample_text( );
    }

    SkString name( ) override { return SkString( "Glyph Transform" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        SkPaint paint;

        SkFont font( fEmojiFont.fTypeface );
        const char* text = fEmojiFont.fText;

        double baseline = this->height( ) / 2;
        canvas->drawLine( 0, baseline, this->width( ), baseline, paint );

        SkMatrix ctm;
        ctm.setRotate( fRotate ); // d3 rotate takes degrees
        ctm.postScale( fScale * 4, fScale * 4 );
        ctm.postTranslate( fTranslate.fX + this->width( ) * 0.8, fTranslate.fY + baseline );
        canvas->concat( ctm );

        // d3 by default anchors text around the middle
        SkRect bounds;
        font.measureText( text, strlen( text ), SkTextEncoding::kUTF8, &bounds );
        canvas->drawSimpleText( text, strlen( text ), SkTextEncoding::kUTF8, -bounds.centerX( ), -bounds.centerY( ),
            font, paint );
    }

    bool onAnimate( double nanos ) override
    {
        constexpr SkScalar maxt = 100000;
        double t = TimeUtils::PingPong( 1e-9 * nanos, 20, 0, 0, maxt ); // d3 t is in milliseconds

        fTranslate.set( sin( t / 3000 ) - t * this->width( ) * 0.7 / maxt, sin( t / 999 ) / t );
        fScale = 4.5 - std::sqrt( t ) / 99;
        fRotate = sin( t / 734 );

        return true;
    }

private:
    struct EmojiFont
    {
        sk_sp<SkTypeface> fTypeface;
        const char* fText;
    } fEmojiFont;

    SkVector fTranslate;
    SkScalar fScale;
    SkScalar fRotate;

    using INHERITED = Sample;
};


int main()
{
    int result = SampleApplication<GlyphTransformView>::Run( );
    return result;
}


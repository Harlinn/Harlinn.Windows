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

#include "skia/tools/Resources.h"
#include "skia/tools/ToolUtils.h"

#include "skia/core/SkCanvas.h"
#include "skia/core/SkFontMetrics.h"
#include "skia/core/SkFontMgr.h"
#include "skia/core/SkTextBlob.h"
#include "skia/core/SkTypeface.h"
#include "skia/utils/SkRandom.h"

#if SK_SUPPORT_GPU
#include "skia/gpu/GrDirectContext.h"
#include "src/gpu/GrDirectContextPriv.h"
#endif

using namespace Harlinn::Windows::Skia;


static sk_sp<SkTypeface> chinese_typeface( )
{
    return SkTypeface::MakeFromName( "SimSun", SkFontStyle( ) );
}

class ChineseFlingView : public Sample
{
    static constexpr int kNumBlobs = 200;
    static constexpr int kWordLength = 16;

    sk_sp<SkTypeface>    fTypeface;
    SkFontMetrics        fMetrics;
    sk_sp<SkTextBlob>    fBlobs[kNumBlobs];
    SkRandom             fRand;
    int                  fIndex = 0;

    SkString name( ) override { return SkString( "chinese-fling" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        canvas->clear( 0xFFDDDDDD );

        SkPaint paint;
        paint.setColor( 0xDE000000 );

        // draw a consistent run of the 'words' - one word per line
        int index = fIndex;
        for ( SkScalar y = 0.0f; y < 1024.0f; )
        {

            y += -fMetrics.fAscent;
            canvas->drawTextBlob( fBlobs[index], 0, y, paint );

            y += fMetrics.fDescent + fMetrics.fLeading;
            ++index;
            index %= kNumBlobs;
        }
        // now "fling" a random amount
        fIndex += fRand.nextRangeU( 5, 20 );
        fIndex %= kNumBlobs;
    }

    void onOnceBeforeDraw( ) override
    {
        fTypeface = chinese_typeface( );

        SkFont font( fTypeface, 56 );
        font.getMetrics( &fMetrics );

        SkUnichar glyphs[kWordLength];
        for ( int32_t i = 0; i < kNumBlobs; ++i )
        {
            this->createRandomWord( glyphs );

            SkTextBlobBuilder builder;
            ToolUtils::add_to_text_blob_w_len( &builder,
                (const char*)glyphs,
                kWordLength * 4,
                SkTextEncoding::kUTF32,
                font,
                0,
                0 );

            fBlobs[i] = builder.make( );
        }
    }

    // Construct a random kWordLength character 'word' drawing from the full Chinese set
    void createRandomWord( SkUnichar glyphs[kWordLength] )
    {
        for ( int i = 0; i < kWordLength; ++i )
        {
            glyphs[i] = fRand.nextRangeU( 0x4F00, 0x9FA0 );
        }
    }
};

int main()
{
    int result = SampleApplication<ChineseFlingView>::Run( );
    return result;
}


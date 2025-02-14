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

class ChineseZoomView : public Sample
{
    static constexpr int kNumBlobs = 8;
    static constexpr int kParagraphLength = 175;

    bool                 fAfterFirstFrame = false;
    sk_sp<SkTypeface>    fTypeface;
    SkFontMetrics        fMetrics;
    sk_sp<SkTextBlob>    fBlobs[kNumBlobs];
    SkRandom             fRand;
    SkScalar             fScale = 15;
    SkScalar             fTranslate = 0;

    SkString name( ) override { return SkString( "chinese-zoom" ); }

    bool onChar( SkUnichar uni ) override
    {
        if ( '>' == uni )
        {
            fScale += 0.125f;
            return true;
        }
        if ( '<' == uni )
        {
            fScale -= 0.125f;
            return true;
        }
        return false;
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        canvas->clear( 0xFFDDDDDD );

        SkPaint paint;
        paint.setAntiAlias( true );
        paint.setColor( 0xDE000000 );

        if ( fAfterFirstFrame )
        {
#if SK_SUPPORT_GPU
            auto direct = GrAsDirectContext( canvas->recordingContext( ) );
            if ( direct )
            {
                sk_sp<SkImage> image = direct->priv( ).testingOnly_getFontAtlasImage(
                    GrMaskFormat::kA8_GrMaskFormat, 0 );
                canvas->drawImageRect( image,
                    SkRect::MakeXYWH( 10.0f, 10.0f, 512.0f, 512.0 ),
                    SkSamplingOptions( ), &paint );
                image = direct->priv( ).testingOnly_getFontAtlasImage(
                    GrMaskFormat::kA8_GrMaskFormat, 1 );
                canvas->drawImageRect( image,
                    SkRect::MakeXYWH( 522.0f, 10.0f, 512.f, 512.0f ),
                    SkSamplingOptions( ), &paint );
                image = direct->priv( ).testingOnly_getFontAtlasImage(
                    GrMaskFormat::kA8_GrMaskFormat, 2 );
                canvas->drawImageRect( image,
                    SkRect::MakeXYWH( 10.0f, 522.0f, 512.0f, 512.0f ),
                    SkSamplingOptions( ), &paint );
                image = direct->priv( ).testingOnly_getFontAtlasImage(
                    GrMaskFormat::kA8_GrMaskFormat, 3 );
                canvas->drawImageRect( image,
                    SkRect::MakeXYWH( 522.0f, 522.0f, 512.0f, 512.0f ),
                    SkSamplingOptions( ), &paint );
            }
#endif
        }

        canvas->scale( fScale, fScale );
        canvas->translate( 0, fTranslate );
        fTranslate -= 0.5f;

        // draw a consistent run of the 'words' - one word per line
        SkScalar y = 0;
        for ( int index = 0; index < kNumBlobs; ++index )
        {
            y += -fMetrics.fAscent;
            canvas->drawTextBlob( fBlobs[index], 0, y, paint );

            y += 3 * ( fMetrics.fDescent - fMetrics.fAscent + fMetrics.fLeading );
        }
        if ( !fAfterFirstFrame )
        {
            fAfterFirstFrame = true;
        }
    }

    void onOnceBeforeDraw( ) override
    {
        fTypeface = chinese_typeface( );

        SkFont font( fTypeface, 11 );
        font.getMetrics( &fMetrics );

        SkPaint paint;
        paint.setColor( 0xDE000000 );

        SkUnichar glyphs[45];
        for ( int32_t i = 0; i < kNumBlobs; ++i )
        {
            SkTextBlobBuilder builder;
            auto paragraphLength = kParagraphLength;
            SkScalar y = 0;
            while ( paragraphLength - 45 > 0 )
            {
                auto currentLineLength = std::min( 45, paragraphLength - 45 );
                this->createRandomLine( glyphs, currentLineLength );

                ToolUtils::add_to_text_blob_w_len( &builder,
                    (const char*)glyphs,
                    currentLineLength * 4,
                    SkTextEncoding::kUTF32,
                    font,
                    0,
                    y );
                y += fMetrics.fDescent - fMetrics.fAscent + fMetrics.fLeading;
                paragraphLength -= 45;
            }
            fBlobs[i] = builder.make( );
        }
    }

    // Construct a random kWordLength character 'word' drawing from the full Chinese set
    void createRandomLine( SkUnichar glyphs[45], int lineLength )
    {
        for ( auto i = 0; i < lineLength; ++i )
        {
            glyphs[i] = fRand.nextRangeU( 0x4F00, 0x9FA0 );
        }
    }
};


int main( )
{
    int result = SampleApplication<ChineseZoomView>::Run( );
    return result;
}


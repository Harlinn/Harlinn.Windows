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
#include "skia/core/SkCanvas.h"
#include "skia/core/SkColorFilter.h"
#include "skia/core/SkImage.h"
#include "skia/core/SkPath.h"
#include "skia/core/SkRegion.h"
#include "skia/core/SkShader.h"
#include "skia/effects/SkGradientShader.h"
#include "src/core/SkUtils.h"
#include "skia/tools/Resources.h"

using namespace Harlinn::Windows::Skia;


const float gMat[] = {
    .3f, .6f, .1f, 0, 0,
    .3f, .6f, .1f, 0, 0,
    .3f, .6f, .1f, 0, 0,
      0,   0,   0, 1, 0,
};

class MixerView : public Sample
{
    sk_sp<SkImage>          fImg;
    sk_sp<SkColorFilter>    fCF0;
    sk_sp<SkColorFilter>    fCF1;

    float fWeight = 0;
    float fDW = 0.02f;

public:
    MixerView( ) {}

protected:
    SkString name( ) override { return SkString( "Mixer" ); }

    void dodraw( SkCanvas* canvas, sk_sp<SkColorFilter> cf0, sk_sp<SkColorFilter> cf1, float gap )
    {
        SkPaint paint;
        paint.setColorFilter( cf0 );
        canvas->drawImage( fImg, 0, 0, SkSamplingOptions( ), &paint );

        paint.setColorFilter( SkColorFilters::Lerp( fWeight, cf0, cf1 ) );
        canvas->drawImage( fImg, fImg->width( ) + gap * fWeight, 0,
            SkSamplingOptions( ), &paint );

        paint.setColorFilter( cf1 );
        canvas->drawImage( fImg, 2 * fImg->width( ) + gap, 0, SkSamplingOptions( ), &paint );
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        if ( !fImg )
        {
            fImg = GetResourceAsImage( "images/mandrill_256.png" );
            fCF0 = SkColorFilters::Matrix( gMat );
            fCF1 = SkColorFilters::Blend( 0xFF44CC88, SkBlendMode::kScreen );
        }

        float gap = fImg->width( ) * 3;

        canvas->translate( 10, 10 );
        dodraw( canvas, nullptr, fCF1, gap );
        canvas->translate( 0, fImg->height( ) + 10 );
        dodraw( canvas, fCF0, nullptr, gap );
        canvas->translate( 0, fImg->height( ) + 10 );
        dodraw( canvas, fCF0, fCF1, gap );

        fWeight += fDW;
        if ( fWeight > 1 || fWeight < 0 )
        {
            fDW = -fDW;
        }
    }

    Click* onFindClickHandler( SkScalar x, SkScalar y, skui::ModifierKey ) override
    {
        return fRect.contains( SkScalarRoundToInt( x ),
            SkScalarRoundToInt( y ) ) ? new Click( ) : nullptr;
    }

    bool onClick( Click* click ) override
    {
        fRect.offset( click->fCurr.fX - click->fPrev.fX,
            click->fCurr.fY - click->fPrev.fY );
        return true;
    }

private:
    SkIRect fRect;

    using INHERITED = Sample;
};

int main()
{
    int result = SampleApplication<MixerView>::Run( );
    return result;
}


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
#include "skia/core/SkPaint.h"
#include "skia/effects/SkColorMatrixFilter.h"
#include "skia/effects/SkDiscretePathEffect.h"
#include "skia/effects/SkGradientShader.h"
#include "src/core/SkBlurMask.h"
#include "src/effects/SkEmbossMaskFilter.h"

using namespace Harlinn::Windows::Skia;

//#define COLOR 0xFFFF8844
#define COLOR 0xFF888888

static void paint_proc0( SkPaint* )
{
}

static void paint_proc1( SkPaint* paint )
{
    paint->setMaskFilter( SkMaskFilter::MakeBlur(
        kNormal_SkBlurStyle,
        SkBlurMask::ConvertRadiusToSigma( 2 ) ) );
}

static void paint_proc2( SkPaint* paint )
{
    paint->setMaskFilter( SkEmbossMaskFilter::Make(
        SkBlurMask::ConvertRadiusToSigma( SkIntToScalar( 1 ) ),
        { { SK_Scalar1, SK_Scalar1, SK_Scalar1 }, 0, 64, 16 } ) );
}

static void paint_proc3( SkPaint* paint )
{
    SkColor colors[] = { SK_ColorRED, COLOR, SK_ColorBLUE };
    SkPoint pts[] = { { 3, 0 }, { 7, 5 } };
    paint->setShader( SkGradientShader::MakeLinear( pts, colors, nullptr, SK_ARRAY_COUNT( colors ),
        SkTileMode::kMirror ) );
}

static void paint_proc5( SkPaint* paint )
{
    paint_proc3( paint );
    paint_proc2( paint );
}

typedef void ( *PaintProc )( SkPaint* );
const PaintProc gPaintProcs[] = {
    paint_proc0,
    paint_proc1,
    paint_proc2,
    paint_proc3,
    paint_proc5,
};

///////////////////////////////////////////////////////////////////////////////

class EffectsView : public Sample
{
public:
    SkPath fPath;
    SkPaint fPaint[SK_ARRAY_COUNT( gPaintProcs )];

    EffectsView( )
    {
        size_t i;
        const float pts[] = {
            0, 0,
            10, 0,
            10, 5,
            20, -5,
            10, -15,
            10, -10,
            0, -10
        };
        fPath.moveTo( pts[0], pts[1] );
        for ( i = 2; i < SK_ARRAY_COUNT( pts ); i += 2 )
        {
            fPath.lineTo( pts[i], pts[i + 1] );
        }

        for ( i = 0; i < SK_ARRAY_COUNT( gPaintProcs ); i++ )
        {
            fPaint[i].setAntiAlias( true );
            fPaint[i].setColor( COLOR );
            gPaintProcs[i]( &fPaint[i] );
        }

        this->setBGColor( 0xFFDDDDDD );
    }

protected:
    SkString name( ) override { return SkString( "Effects" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        canvas->scale( 3, 3 );
        canvas->translate( 10, 30 );
        for ( size_t i = 0; i < SK_ARRAY_COUNT( fPaint ); i++ )
        {
            canvas->drawPath( fPath, fPaint[i] );
            canvas->translate( 32, 0 );
        }
    }

private:
    using INHERITED = Sample;
};


int main( )
{
    int result = SampleApplication<EffectsView>::Run( );
    return result;
}


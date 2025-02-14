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

#include "skia/core/SkPaint.h"
#include "skia/core/SkPathBuilder.h"
#include "skia/utils/SkRandom.h"

using namespace Harlinn::Windows::Skia;

// Generates y values for the chart plots.
static void gen_data( SkScalar yAvg, SkScalar ySpread, int count, SkTDArray<SkScalar>* dataPts )
{
    dataPts->setCount( count );
    static SkRandom gRandom;
    for ( int i = 0; i < count; ++i )
    {
        ( *dataPts )[i] = gRandom.nextRangeScalar( yAvg - SkScalarHalf( ySpread ),
            yAvg + SkScalarHalf( ySpread ) );
    }
}

// Generates a path to stroke along the top of each plot and a fill path for the area below each
// plot. The fill path is bounded below by the bottomData plot points or a horizontal line at
// yBase if bottomData == nullptr.
// The plots are animated by rotating the data points by leftShift.
static void gen_paths( const SkTDArray<SkScalar>& topData,
    const SkTDArray<SkScalar>* bottomData,
    SkScalar yBase,
    SkScalar xLeft, SkScalar xDelta,
    int leftShift,
    SkPathBuilder* plot, SkPathBuilder* fill )
{
    plot->incReserve( topData.count( ) );
    if ( nullptr == bottomData )
    {
        fill->incReserve( topData.count( ) + 2 );
    }
    else
    {
        fill->incReserve( 2 * topData.count( ) );
    }

    leftShift %= topData.count( );
    SkScalar x = xLeft;

    // Account for the leftShift using two loops
    int shiftToEndCount = topData.count( ) - leftShift;
    plot->moveTo( x, topData[leftShift] );
    fill->moveTo( x, topData[leftShift] );

    for ( int i = 1; i < shiftToEndCount; ++i )
    {
        plot->lineTo( x, topData[i + leftShift] );
        fill->lineTo( x, topData[i + leftShift] );
        x += xDelta;
    }

    for ( int i = 0; i < leftShift; ++i )
    {
        plot->lineTo( x, topData[i] );
        fill->lineTo( x, topData[i] );
        x += xDelta;
    }

    if ( bottomData )
    {
        SkASSERT( bottomData->count( ) == topData.count( ) );
        // iterate backwards over the previous graph's data to generate the bottom of the filled
        // area (and account for leftShift).
        for ( int i = 0; i < leftShift; ++i )
        {
            x -= xDelta;
            fill->lineTo( x, ( *bottomData )[leftShift - 1 - i] );
        }
        for ( int i = 0; i < shiftToEndCount; ++i )
        {
            x -= xDelta;
            fill->lineTo( x, ( *bottomData )[bottomData->count( ) - 1 - i] );
        }
    }
    else
    {
        fill->lineTo( x - xDelta, yBase );
        fill->lineTo( xLeft, yBase );
    }
}

// A set of scrolling line plots with the area between each plot filled. Stresses out GPU path
// filling
class ChartView : public Sample
{
    static constexpr int kNumGraphs = 5;
    static constexpr int kPixelsPerTick = 3;
    static constexpr int kShiftPerFrame = 1;
    int                 fShift = 0;
    SkISize             fSize = { -1, -1 };
    SkTDArray<SkScalar> fData[kNumGraphs];

    SkString name( ) override { return SkString( "Chart" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        bool sizeChanged = false;
        if ( canvas->getBaseLayerSize( ) != fSize )
        {
            fSize = canvas->getBaseLayerSize( );
            sizeChanged = true;
        }

        SkScalar ySpread = SkIntToScalar( fSize.fHeight / 20 );

        SkScalar height = SkIntToScalar( fSize.fHeight );

        if ( sizeChanged )
        {
            int dataPointCount = std::max( fSize.fWidth / kPixelsPerTick + 1, 2 );

            for ( int i = 0; i < kNumGraphs; ++i )
            {
                SkScalar y = ( kNumGraphs - i ) * ( height - ySpread ) / ( kNumGraphs + 1 );
                fData[i].reset( );
                gen_data( y, ySpread, dataPointCount, fData + i );
            }
        }

        canvas->clear( 0xFFE0F0E0 );

        static SkRandom colorRand;
        static SkColor gColors[kNumGraphs] = { 0x0 };
        if ( 0 == gColors[0] )
        {
            for ( int i = 0; i < kNumGraphs; ++i )
            {
                gColors[i] = colorRand.nextU( ) | 0xff000000;
            }
        }

        static const SkScalar kStrokeWidth = SkIntToScalar( 2 );
        SkPaint plotPaint;
        SkPaint fillPaint;
        plotPaint.setAntiAlias( true );
        plotPaint.setStyle( SkPaint::kStroke_Style );
        plotPaint.setStrokeWidth( kStrokeWidth );
        plotPaint.setStrokeCap( SkPaint::kRound_Cap );
        plotPaint.setStrokeJoin( SkPaint::kRound_Join );
        fillPaint.setAntiAlias( true );
        fillPaint.setStyle( SkPaint::kFill_Style );

        SkPathBuilder plotPath, fillPath;
        SkTDArray<SkScalar>* prevData = nullptr;

        for ( int i = 0; i < kNumGraphs; ++i )
        {
            gen_paths( fData[i],
                prevData,
                height,
                0,
                SkIntToScalar( kPixelsPerTick ),
                fShift,
                &plotPath,
                &fillPath );

            // Make the fills partially transparent
            fillPaint.setColor( ( gColors[i] & 0x00ffffff ) | 0x80000000 );
            canvas->drawPath( fillPath.detach( ), fillPaint );

            plotPaint.setColor( gColors[i] );
            canvas->drawPath( plotPath.detach( ), plotPaint );

            prevData = fData + i;
        }

        fShift += kShiftPerFrame;
    }
};

int main()
{
    int result = SampleApplication<ChartView>::Run( );
    return result;
}


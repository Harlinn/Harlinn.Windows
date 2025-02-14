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
#include "skia/core/SkShader.h"
#include "skia/utils/SkRandom.h"

using namespace Harlinn::Windows::Skia;

/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


/**
 * Animated sample used to develop a predecessor of GrDrawOp combining.
 */
class ManyRectsView : public Sample
{
private:
    enum
    {
        N = 1000,
    };

public:
    ManyRectsView( ) {}

protected:
    SkString name( ) override { return SkString( "ManyRects" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        SkISize dsize = canvas->getBaseLayerSize( );
        canvas->clear( 0xFFF0E0F0 );

        for ( int i = 0; i < N; ++i )
        {
            SkRect rect = SkRect::MakeWH( SkIntToScalar( fRandom.nextRangeU( 10, 100 ) ),
                SkIntToScalar( fRandom.nextRangeU( 10, 100 ) ) );
            int x = fRandom.nextRangeU( 0, dsize.fWidth );
            int y = fRandom.nextRangeU( 0, dsize.fHeight );
            canvas->save( );

            canvas->translate( SkIntToScalar( x ), SkIntToScalar( y ) );
            // Uncomment to test rotated rect draw combining.
            if ( false )
            {
                SkMatrix rotate;
                rotate.setRotate( fRandom.nextUScalar1( ) * 360,
                    SkIntToScalar( x ) + SkScalarHalf( rect.fRight ),
                    SkIntToScalar( y ) + SkScalarHalf( rect.fBottom ) );
                canvas->concat( rotate );
            }
            SkRect clipRect = rect;
            // This clip will always contain the entire rect. It's here to give the GPU op combining
            // code a little more challenge.
            clipRect.outset( 10, 10 );
            canvas->clipRect( clipRect );
            SkPaint paint;
            paint.setColor( fRandom.nextU( ) );
            canvas->drawRect( rect, paint );
            canvas->restore( );
        }
    }

private:
    SkRandom fRandom;
    using INHERITED = Sample;
};



int main()
{
    int result = SampleApplication<ManyRectsView>::Run( );
    return result;
}


#pragma once
#ifndef HARLINN_HWSKIACOMMON_HWSKIASAMPLELAYERS_H_
#define HARLINN_HWSKIACOMMON_HWSKIASAMPLELAYERS_H_
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
#include "skia/core/SkImage.h"
#include "skia/core/SkMaskFilter.h"
#include "skia/core/SkPath.h"
#include "skia/core/SkRegion.h"
#include "skia/core/SkShader.h"
#include "skia/core/SkTime.h"
#include "skia/core/SkTypeface.h"
#include "skia/effects/SkGradientShader.h"
#include "skia/utils/SkCamera.h"
#include "src/utils/SkUTF.h"


namespace Harlinn::Windows::Skia
{

    static void make_paint( SkPaint* paint, const SkMatrix& localMatrix )
    {
        SkColor colors[] = { 0, SK_ColorWHITE };
        SkPoint pts[] = { { 0, 0 }, { 0, SK_Scalar1 * 20 } };
        paint->setShader( SkGradientShader::MakeLinear( pts, colors, nullptr, 2,
            SkTileMode::kClamp, 0, &localMatrix ) );
        paint->setBlendMode( SkBlendMode::kDstIn );
    }

    // test drawing with strips of fading gradient above and below
    static void test_fade( SkCanvas* canvas )
    {
        SkAutoCanvasRestore ar( canvas, true );

        SkRect r;

        SkAutoCanvasRestore ar2( canvas, false );

        // create the layers

        r.setWH( 100, 100 );
        canvas->clipRect( r );

        r.fBottom = SkIntToScalar( 20 );
        canvas->saveLayer( &r, nullptr );

        r.fTop = SkIntToScalar( 80 );
        r.fBottom = SkIntToScalar( 100 );
        canvas->saveLayer( &r, nullptr );

        // now draw the "content"

        if ( true )
        {
            r.setWH( 100, 100 );

            canvas->saveLayerAlpha( &r, 0x80 );

            SkPaint p;
            p.setColor( SK_ColorRED );
            p.setAntiAlias( true );
            canvas->drawOval( r, p );

            canvas->restore( );
        }
        else
        {
            r.setWH( 100, 100 );

            SkPaint p;
            p.setColor( SK_ColorRED );
            p.setAntiAlias( true );
            canvas->drawOval( r, p );
        }

        //    return;

            // now apply an effect
        SkMatrix m;
        m.setScale( SK_Scalar1, -SK_Scalar1 );
        m.postTranslate( 0, SkIntToScalar( 100 ) );

        SkPaint paint;
        make_paint( &paint, m );
        r.setWH( 100, 20 );
        //    SkDebugf("--------- draw top grad\n");
        canvas->drawRect( r, paint );

        r.fTop = SkIntToScalar( 80 );
        r.fBottom = SkIntToScalar( 100 );
        //    SkDebugf("--------- draw bot grad\n");
        canvas->drawRect( r, paint );
    }

}
#endif

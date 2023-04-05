#pragma once
#ifndef HARLINN_HWSKIACOMMON_HWSKIASAMPLEPATCH_H_
#define HARLINN_HWSKIACOMMON_HWSKIASAMPLEPATCH_H_

#include <HWSkiaSample.h>

#include "skia/core/SkCanvas.h"
#include "skia/core/SkColorFilter.h"
#include "skia/core/SkColorPriv.h"
#include "skia/core/SkContourMeasure.h"
#include "skia/core/SkGraphics.h"
#include "skia/core/SkPath.h"
#include "skia/core/SkRegion.h"
#include "skia/core/SkShader.h"
#include "skia/core/SkStream.h"
#include "skia/core/SkTime.h"
#include "skia/core/SkTypeface.h"
#include "skia/core/SkVertices.h"
#include "skia/effects/SkGradientShader.h"
#include "skia/effects/SkOpPathEffect.h"
#include "skia/private/SkTDArray.h"
#include "skia/utils/SkRandom.h"
#include "DecodeFile.h"
#include "src/core/SkGeometry.h"
#include "src/core/SkOSFile.h"
#include "src/utils/SkUTF.h"
#include "skia/tools/Resources.h"
#include "skia/tools/timer/TimeUtils.h"

namespace Harlinn::Windows::Skia
{
    static sk_sp<SkShader> make_shader0( SkIPoint* size )
    {
        SkBitmap bm;
        decode_file( GetResourceAsData( "images/dog.jpg" ), &bm );
        *size = SkIPoint{ bm.width( ), bm.height( ) };
        return bm.makeShader( SkSamplingOptions( SkFilterMode::kLinear ) );
    }

    static sk_sp<SkShader> make_shader1( const SkIPoint& size )
    {
        SkPoint pts[] = { { 0, 0, },
                          { SkIntToScalar( size.fX ), SkIntToScalar( size.fY ) } };
        SkColor colors[] = { SK_ColorRED, SK_ColorGREEN, SK_ColorBLUE, SK_ColorRED };
        return SkGradientShader::MakeLinear( pts, colors, nullptr,
            SK_ARRAY_COUNT( colors ), SkTileMode::kMirror );
    }

    class Patch
    {
    public:
        Patch( ) { sk_bzero( fPts, sizeof( fPts ) ); }
        ~Patch( ) {}

        void setPatch( const SkPoint pts[12] )
        {
            memcpy( fPts, pts, 12 * sizeof( SkPoint ) );
            fPts[12] = pts[0];  // the last shall be first
        }
        void setBounds( int w, int h ) { fW = w; fH = h; }

        void draw( SkCanvas*, const SkPaint&, int segsU, int segsV,
            bool doTextures, bool doColors );

    private:
        SkPoint fPts[13];
        int     fW, fH;
    };

    static void eval_patch_edge( const SkPoint cubic[], SkPoint samples[], int segs )
    {
        SkScalar t = 0;
        SkScalar dt = SK_Scalar1 / segs;

        samples[0] = cubic[0];
        for ( int i = 1; i < segs; i++ )
        {
            t += dt;
            SkEvalCubicAt( cubic, t, &samples[i], nullptr, nullptr );
        }
    }

    static void eval_sheet( const SkPoint edge[], int nu, int nv, int iu, int iv,
        SkPoint* pt )
    {
        const int TL = 0;
        const int TR = nu;
        const int BR = TR + nv;
        const int BL = BR + nu;

        SkScalar u = SkIntToScalar( iu ) / nu;
        SkScalar v = SkIntToScalar( iv ) / nv;

        SkScalar uv = u * v;
        SkScalar Uv = ( 1 - u ) * v;
        SkScalar uV = u * ( 1 - v );
        SkScalar UV = ( 1 - u ) * ( 1 - v );

        SkScalar x0 = UV * edge[TL].fX + uV * edge[TR].fX + Uv * edge[BL].fX + uv * edge[BR].fX;
        SkScalar y0 = UV * edge[TL].fY + uV * edge[TR].fY + Uv * edge[BL].fY + uv * edge[BR].fY;

        SkScalar x = ( 1 - v ) * edge[TL + iu].fX + u * edge[TR + iv].fX +
            v * edge[BR + nu - iu].fX + ( 1 - u ) * edge[BL + nv - iv].fX - x0;
        SkScalar y = ( 1 - v ) * edge[TL + iu].fY + u * edge[TR + iv].fY +
            v * edge[BR + nu - iu].fY + ( 1 - u ) * edge[BL + nv - iv].fY - y0;
        pt->set( x, y );
    }

    static SkColor make_color( SkScalar s, SkScalar t )
    {
        return SkColorSetARGB( 0xFF, SkUnitScalarClampToByte( s ), SkUnitScalarClampToByte( t ), 0 );
    }

    void Patch::draw( SkCanvas* canvas, const SkPaint& paint, int nu, int nv,
        bool doTextures, bool doColors )
    {
        if ( nu < 1 || nv < 1 )
        {
            return;
        }

        int i, npts = ( nu + nv ) * 2;
        SkAutoSTMalloc<16, SkPoint> storage( npts + 1 );
        SkPoint* edge0 = storage.get( );
        SkPoint* edge1 = edge0 + nu;
        SkPoint* edge2 = edge1 + nv;
        SkPoint* edge3 = edge2 + nu;

        // evaluate the edge points
        eval_patch_edge( fPts + 0, edge0, nu );
        eval_patch_edge( fPts + 3, edge1, nv );
        eval_patch_edge( fPts + 6, edge2, nu );
        eval_patch_edge( fPts + 9, edge3, nv );
        edge3[nv] = edge0[0];   // the last shall be first

        for ( i = 0; i < npts; i++ )
        {
            //        canvas->drawLine(edge0[i].fX, edge0[i].fY, edge0[i+1].fX, edge0[i+1].fY, paint);
        }

        int row, vertCount = ( nu + 1 ) * ( nv + 1 );
        SkAutoTMalloc<SkPoint>  vertStorage( vertCount );
        SkPoint* verts = vertStorage.get( );

        // first row
        memcpy( verts, edge0, ( nu + 1 ) * sizeof( SkPoint ) );
        // rows
        SkPoint* r = verts;
        for ( row = 1; row < nv; row++ )
        {
            r += nu + 1;
            r[0] = edge3[nv - row];
            for ( int col = 1; col < nu; col++ )
            {
                eval_sheet( edge0, nu, nv, col, row, &r[col] );
            }
            r[nu] = edge1[row];
        }
        // last row
        SkPoint* last = verts + nv * ( nu + 1 );
        for ( i = 0; i <= nu; i++ )
        {
            last[i] = edge2[nu - i];
        }

        //    canvas->drawPoints(verts, vertCount, paint);

        int stripCount = ( nu + 1 ) * 2;
        SkAutoTMalloc<SkPoint>  stripStorage( stripCount * 2 );
        SkAutoTMalloc<SkColor>  colorStorage( stripCount );
        SkPoint* strip = stripStorage.get( );
        SkPoint* tex = strip + stripCount;
        SkColor* colors = colorStorage.get( );
        SkScalar t = 0;
        const SkScalar ds = SK_Scalar1 * fW / nu;
        const SkScalar dt = SK_Scalar1 * fH / nv;
        r = verts;
        for ( row = 0; row < nv; row++ )
        {
            SkPoint* upper = r;
            SkPoint* lower = r + nu + 1;
            r = lower;
            SkScalar s = 0;
            for ( i = 0; i <= nu; i++ )
            {
                strip[i * 2 + 0] = *upper++;
                strip[i * 2 + 1] = *lower++;
                tex[i * 2 + 0].set( s, t );
                tex[i * 2 + 1].set( s, t + dt );
                colors[i * 2 + 0] = make_color( s / fW, t / fH );
                colors[i * 2 + 1] = make_color( s / fW, ( t + dt ) / fH );
                s += ds;
            }
            t += dt;
            canvas->drawVertices( SkVertices::MakeCopy( SkVertices::kTriangleStrip_VertexMode, stripCount,
                strip, doTextures ? tex : nullptr,
                doColors ? colors : nullptr ),
                SkBlendMode::kModulate, paint );
        }
    }

    static void drawpatches( SkCanvas* canvas, const SkPaint& paint, int nu, int nv,
        Patch* patch )
    {
        SkAutoCanvasRestore ar( canvas, true );

        patch->draw( canvas, paint, nu, nv, false, false );
        canvas->translate( SkIntToScalar( 180 ), 0 );
        patch->draw( canvas, paint, nu, nv, true, false );
        canvas->translate( SkIntToScalar( 180 ), 0 );
        patch->draw( canvas, paint, nu, nv, false, true );
        canvas->translate( SkIntToScalar( 180 ), 0 );
        patch->draw( canvas, paint, nu, nv, true, true );
    }

    static constexpr SkScalar DX = 20;
    static constexpr SkScalar DY = 0;
    static constexpr SkScalar kS = 50;
    static constexpr SkScalar kT = 40;

    static sk_sp<SkVertices> make_verts( const SkPath& path, SkScalar width )
    {
        auto meas = SkContourMeasureIter( path, false ).next( );
        if ( !meas )
        {
            return nullptr;
        }

        const SkPoint src[2] = {
            { 0, -width / 2 }, { 0, width / 2 },
        };
        SkTDArray<SkPoint> pts;

        const SkScalar step = 2;
        for ( SkScalar distance = 0; distance < meas->length( ); distance += step )
        {
            SkMatrix mx;
            if ( !meas->getMatrix( distance, &mx ) )
            {
                continue;
            }
            SkPoint* dst = pts.append( 2 );
            mx.mapPoints( dst, src, 2 );
        }

        int vertCount = pts.count( );
        int indexCount = 0; // no texture
        unsigned flags = SkVertices::kHasColors_BuilderFlag;
        SkVertices::Builder builder( SkVertices::kTriangleStrip_VertexMode,
            vertCount, indexCount, flags );
        memcpy( builder.positions( ), pts.begin( ), vertCount * sizeof( SkPoint ) );
        SkRandom rand;
        for ( int i = 0; i < vertCount; ++i )
        {
            builder.colors( )[i] = rand.nextU( ) | 0xFF000000;
        }
        SkDebugf( "vert count = %d\n", vertCount );

        return builder.detach( );
    }

}


#endif

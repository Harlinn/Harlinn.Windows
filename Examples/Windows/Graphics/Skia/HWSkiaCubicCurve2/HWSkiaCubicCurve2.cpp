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


#include <HWSkiaSamplePath.h>
#include "skia/utils/SkRandom.h"

using namespace Harlinn::Windows::Skia;


static SkPoint lerp( SkPoint a, SkPoint b, float t )
{
    return a * ( 1 - t ) + b * t;
}

static int find_max_deviation_cubic( const SkPoint src[4], SkScalar ts[2] )
{
    // deviation = F' x (d - a) == 0, solve for t(s)
    // F = At^3 + Bt^2 + Ct + D
    // F' = 3At^2 + 2Bt + C
    // Z = d - a
    // F' x Z = 3(A x Z)t^2 + 2(B x Z)t + (C x Z)
    //
    SkVector A = src[3] + ( src[1] - src[2] ) * 3 - src[0];
    SkVector B = ( src[2] - src[1] - src[1] + src[0] ) * 3;
    SkVector C = ( src[1] - src[0] ) * 3;
    SkVector Z = src[3] - src[0];
    // now forumlate the quadratic coefficients we need to solve for t : F' x Z
    return SkFindUnitQuadRoots( 3 * A.cross( Z ), 2 * B.cross( Z ), C.cross( Z ), ts );
}

class CubicCurve2 : public Sample
{
public:
    enum
    {
        N = 7
    };
    SkPoint fPts[N];
    SkPoint* fQuad = fPts + 4;
    SkScalar fT = 0.5f;
    bool fShowSub = false;
    bool fShowFlatness = false;
    bool fShowInnerQuads = false;
    SkScalar fScale = 0.75;

    CubicCurve2( )
    {
        fPts[0] = { 90, 300 };
        fPts[1] = { 30, 60 };
        fPts[2] = { 250, 30 };
        fPts[3] = { 350, 200 };

        fQuad[0] = fPts[0] + SkVector{ 300, 0 };
        fQuad[1] = fPts[1] + SkVector{ 300, 0 };
        fQuad[2] = fPts[2] + SkVector{ 300, 0 };
    }

protected:
    SkString name( ) override { return SkString( "CubicCurve2" ); }

    bool onChar( SkUnichar uni ) override
    {
        switch ( uni )
        {
            case 's': fShowSub = !fShowSub; break;
            case 'f': fShowFlatness = !fShowFlatness; break;
            case '-': fT -= 1.0f / 32; break;
            case '=': fT += 1.0f / 32; break;
            case 'q': fShowInnerQuads = !fShowInnerQuads; break;
            default: return false;
        }
        fT = std::min( 1.0f, std::max( 0.0f, fT ) );
        return true;
    }

    static void Dot( SkCanvas* canvas, SkPoint p, SkScalar radius, SkColor c )
    {
        SkPaint paint;
        paint.setAntiAlias( true );
        paint.setColor( c );
        canvas->drawCircle( p.fX, p.fY, radius, paint );
    }

    void showFrame( SkCanvas* canvas, const SkPoint pts[], int count, const SkPaint& p )
    {
        SkPaint paint( p );
        SkPoint storage[3 + 2 + 1];
        SkPoint* tmp = storage;
        const SkPoint* prev = pts;
        for ( int n = count; n > 0; --n )
        {
            for ( int i = 0; i < n; ++i )
            {
                canvas->drawLine( prev[i], prev[i + 1], paint );
                tmp[i] = lerp( prev[i], prev[i + 1], fT );
            }
            prev = tmp;
            tmp += n;
        }

        paint.setColor( SK_ColorBLUE );
        paint.setStyle( SkPaint::kFill_Style );
        int n = tmp - storage;
        for ( int i = 0; i < n; ++i )
        {
            Dot( canvas, storage[i], 4, SK_ColorBLUE );
        }
    }

    void showFlattness( SkCanvas* canvas )
    {
        SkPaint paint;
        paint.setStyle( SkPaint::kStroke_Style );
        paint.setAntiAlias( true );

        SkPaint paint2( paint );
        paint2.setColor( 0xFF008800 );

        paint.setColor( 0xFF888888 );
        canvas->drawLine( fPts[0], fPts[3], paint );
        canvas->drawLine( fQuad[0], fQuad[2], paint );

        paint.setColor( 0xFF0000FF );
        SkPoint pts[2];
        pts[0] = ( fQuad[0] + fQuad[1] + fQuad[1] + fQuad[2] ) * 0.25;
        pts[1] = ( fQuad[0] + fQuad[2] ) * 0.5;
        canvas->drawLine( pts[0], pts[1], paint );

        // cubic

        SkVector v0 = ( fPts[0] - fPts[1] - fPts[1] + fPts[2] ) * fScale;
        SkVector v1 = ( fPts[1] - fPts[2] - fPts[2] + fPts[3] ) * fScale;
        SkVector v = ( v0 + v1 ) * 0.5f;

        SkPoint anchor;
        SkScalar ts[2];
        int n = find_max_deviation_cubic( fPts, ts );
        if ( n > 0 )
        {
            SkEvalCubicAt( fPts, ts[0], &anchor, nullptr, nullptr );
            canvas->drawLine( anchor, anchor + v, paint2 );
            canvas->drawLine( anchor, anchor + v0, paint );
            if ( n == 2 )
            {
                SkEvalCubicAt( fPts, ts[1], &anchor, nullptr, nullptr );
                canvas->drawLine( anchor, anchor + v, paint2 );
            }
            canvas->drawLine( anchor, anchor + v1, paint );
        }
        // not sure we can get here
    }

    void showInnerQuads( SkCanvas* canvas )
    {
        auto draw_quad = [canvas]( SkPoint a, SkPoint b, SkPoint c, SkColor color ) {
            SkPaint paint;
            paint.setAntiAlias( true );
            paint.setStroke( true );
            paint.setColor( color );

            canvas->drawPath( SkPathBuilder( ).moveTo( a ).quadTo( b, c ).detach( ), paint );
        };

        SkPoint p0 = SkEvalQuadAt( &fPts[0], fT ),
            p1 = SkEvalQuadAt( &fPts[1], fT ),
            p2 = lerp( p0, p1, fT );

        draw_quad( fPts[0], fPts[1], fPts[2], SK_ColorRED );
        Dot( canvas, p0, 4, SK_ColorRED );

        draw_quad( fPts[1], fPts[2], fPts[3], SK_ColorBLUE );
        Dot( canvas, p1, 4, SK_ColorBLUE );

        SkPaint paint;
        paint.setAntiAlias( true );
        paint.setColor( 0xFF008800 );
        canvas->drawLine( p0, p1, paint );
        Dot( canvas, p2, 4, 0xFF00AA00 );
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        SkPaint paint;
        paint.setAntiAlias( true );

        {
            paint.setStyle( SkPaint::kStroke_Style );
            SkPath path;
            path.moveTo( fPts[0] );
            path.cubicTo( fPts[1], fPts[2], fPts[3] );
            path.moveTo( fQuad[0] );
            path.quadTo( fQuad[1], fQuad[2] );
            canvas->drawPath( path, paint );
        }

        if ( fShowSub )
        {
            paint.setColor( SK_ColorRED );
            paint.setStrokeWidth( 1.7f );
            this->showFrame( canvas, fPts, 3, paint );
            this->showFrame( canvas, fQuad, 2, paint );

            paint.setColor( SK_ColorBLACK );
            paint.setStyle( SkPaint::kFill_Style );
            SkFont font( nullptr, 20 );
            canvas->drawString( SkStringPrintf( "t = %g", fT ), 20, 20, font, paint );
        }

        if ( fShowFlatness )
        {
            this->showFlattness( canvas );
        }

        if ( fShowInnerQuads )
        {
            this->showInnerQuads( canvas );
        }

        paint.setColor( SK_ColorGRAY );
        paint.setStroke( true );
        canvas->drawPath( SkPathBuilder( ).addPolygon( fPts, 4, false ).detach( ), paint );
        canvas->drawPath( SkPathBuilder( ).addPolygon( fQuad, 3, false ).detach( ), paint );

        for ( SkPoint p : fPts )
        {
            Dot( canvas, p, 7, SK_ColorBLACK );
        }

        if ( false )
        {
            SkScalar ts[2];
            int n = SkFindCubicInflections( fPts, ts );
            for ( int i = 0; i < n; ++i )
            {
                SkPoint p;
                SkEvalCubicAt( fPts, ts[i], &p, nullptr, nullptr );
                canvas->drawCircle( p.fX, p.fY, 3, paint );
            }
        }

    }

    Sample::Click* onFindClickHandler( SkScalar x, SkScalar y, skui::ModifierKey modi ) override
    {
        const SkScalar tol = 8;
        const SkRect r = SkRect::MakeXYWH( x - tol, y - tol, tol * 2, tol * 2 );
        for ( int i = 0; i < N; ++i )
        {
            if ( r.intersects( SkRect::MakeXYWH( fPts[i].fX, fPts[i].fY, 1, 1 ) ) )
            {
                return new Click( [this, i]( Click* c ) {
                    fPts[i] = c->fCurr;
                    return true;
                } );
            }
        }
        return this->INHERITED::onFindClickHandler( x, y, modi );
    }

private:
    using INHERITED = Sample;
};

int main()
{
    int result = SampleApplication<CubicCurve2>::Run( );
    return result;
}


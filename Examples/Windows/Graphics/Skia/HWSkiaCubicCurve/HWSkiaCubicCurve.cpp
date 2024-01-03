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

static int compute_parallel_to_base( const SkPoint pts[4], SkScalar t[2] )
{
    // F = At^3 + Bt^2 + Ct + D
    SkVector A = pts[3] - pts[0] + ( pts[1] - pts[2] ) * 3.0f;
    SkVector B = ( pts[0] - pts[1] - pts[1] + pts[2] ) * 3.0f;
    SkVector C = ( pts[1] - pts[0] ) * 3.0f;
    SkVector DA = pts[3] - pts[0];

    // F' = 3At^2 + 2Bt + C
    SkScalar a = 3 * A.cross( DA );
    SkScalar b = 2 * B.cross( DA );
    SkScalar c = C.cross( DA );

    int n = SkFindUnitQuadRoots( a, b, c, t );
    SkString str;
    for ( int i = 0; i < n; ++i )
    {
        str.appendf( " %g", t[i] );
    }
    SkDebugf( "roots %s\n", str.c_str( ) );
    return n;
}

class CubicCurve : public Sample
{
public:
    enum
    {
        N = 4
    };
    SkPoint fPts[N];

    CubicCurve( )
    {
        SkRandom rand;
        for ( int i = 0; i < N; ++i )
        {
            fPts[i].fX = 20 + rand.nextUScalar1( ) * 640;
            fPts[i].fY = 20 + rand.nextUScalar1( ) * 480;
        }
    }

protected:
    SkString name( ) override { return SkString( "CubicCurve" ); }

    void onDrawContent( SkCanvas* canvas ) override
    {
        SkPaint paint;
        paint.setAntiAlias( true );

        {
            SkPath path;
            path.moveTo( fPts[0] );
            path.cubicTo( fPts[1], fPts[2], fPts[3] );
            paint.setStyle( SkPaint::kStroke_Style );
            canvas->drawPath( path, paint );
        }

        {
            paint.setColor( SK_ColorRED );
            SkScalar t[2];
            int n = compute_parallel_to_base( fPts, t );
            SkPoint loc;
            SkVector tan;
            for ( int i = 0; i < n; ++i )
            {
                SkEvalCubicAt( fPts, t[i], &loc, &tan, nullptr );
                tan.setLength( 30 );
                canvas->drawLine( loc - tan, loc + tan, paint );
            }
            paint.setStrokeWidth( 0.5f );
            canvas->drawLine( fPts[0], fPts[3], paint );

            paint.setColor( SK_ColorBLUE );
            paint.setStrokeWidth( 6 );
            SkEvalCubicAt( fPts, 0.5f, &loc, nullptr, nullptr );
            canvas->drawPoint( loc, paint );

            paint.setColor( 0xFF008800 );
            SkEvalCubicAt( fPts, 1.0f / 3, &loc, nullptr, nullptr );
            canvas->drawPoint( loc, paint );
            SkEvalCubicAt( fPts, 2.0f / 3, &loc, nullptr, nullptr );
            canvas->drawPoint( loc, paint );

            //     n = SkFindCubicInflections(fPts, t);
            //     printf("inflections %d %g %g\n", n, t[0], t[1]);
        }

        {
            paint.setStyle( SkPaint::kFill_Style );
            paint.setColor( SK_ColorRED );
            for ( SkPoint p : fPts )
            {
                canvas->drawCircle( p.fX, p.fY, 8, paint );
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
    int result = SampleApplication<CubicCurve>::Run( );
    return result;
}


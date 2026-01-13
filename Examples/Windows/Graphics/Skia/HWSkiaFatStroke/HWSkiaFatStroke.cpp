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

#include <HWSkiaSamplePath.h>
#include "skia/utils/SkRandom.h"

using namespace Harlinn::Windows::Skia;

class FatStroke : public Sample
{
    bool fClosed, fShowStroke, fShowHidden, fShowSkeleton, fAsCurves = false;
    int  fJoinType, fCapType;
    float fWidth = 30;
    SkPaint fPtsPaint, fHiddenPaint, fSkeletonPaint, fStrokePaint;
public:
    enum
    {
        N = 4
    };
    SkPoint fPts[N];

    FatStroke( ) : fClosed( false ), fShowStroke( true ), fShowHidden( false ), fShowSkeleton( true ),
        fJoinType( 0 ), fCapType( 0 )
    {
        SkRandom rand;
        for ( int i = 0; i < N; ++i )
        {
            fPts[i].fX = 20 + rand.nextUScalar1( ) * 640;
            fPts[i].fY = 20 + rand.nextUScalar1( ) * 480;
        }

        fPtsPaint.setAntiAlias( true );
        fPtsPaint.setStrokeWidth( 10 );
        fPtsPaint.setStrokeCap( SkPaint::kRound_Cap );

        fHiddenPaint.setAntiAlias( true );
        fHiddenPaint.setStyle( SkPaint::kStroke_Style );
        fHiddenPaint.setColor( 0xFF0000FF );

        fStrokePaint.setAntiAlias( true );
        fStrokePaint.setStyle( SkPaint::kStroke_Style );
        fStrokePaint.setStrokeWidth( 50 );
        fStrokePaint.setColor( 0x8000FF00 );

        fSkeletonPaint.setAntiAlias( true );
        fSkeletonPaint.setStyle( SkPaint::kStroke_Style );
        fSkeletonPaint.setColor( SK_ColorRED );
    }

    void toggle( bool& value )
    {
        value = !value;
    }

    void toggle3( int& value )
    {
        value = ( value + 1 ) % 3;
    }

protected:
    SkString name( ) override { return SkString( "FatStroke" ); }

    bool onChar( SkUnichar uni ) override
    {
        switch ( uni )
        {
            case '1': this->toggle( fShowSkeleton ); return true;
            case '2': this->toggle( fShowStroke ); return true;
            case '3': this->toggle( fShowHidden ); return true;
            case '4': this->toggle3( fJoinType ); return true;
            case '5': this->toggle3( fCapType ); return true;
            case '6': this->toggle( fClosed ); return true;
            case 'c': this->toggle( fAsCurves ); return true;
            case '-': fWidth -= 5; return true;
            case '=': fWidth += 5; return true;
            default: break;
        }
        return false;
    }

    void makePath( SkPath* path )
    {
        path->moveTo( fPts[0] );
        if ( fAsCurves )
        {
            for ( int i = 1; i < N - 2; ++i )
            {
                path->quadTo( fPts[i], ( fPts[i + 1] + fPts[i] ) * 0.5f );
            }
            path->quadTo( fPts[N - 2], fPts[N - 1] );
        }
        else
        {
            for ( int i = 1; i < N; ++i )
            {
                path->lineTo( fPts[i] );
            }
        }
        if ( fClosed )
        {
            path->close( );
        }
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        canvas->drawColor( 0xFFEEEEEE );

        SkPath path;
        this->makePath( &path );

        fStrokePaint.setStrokeWidth( fWidth );
        fStrokePaint.setStrokeJoin( (SkPaint::Join)fJoinType );
        fStrokePaint.setStrokeCap( (SkPaint::Cap)fCapType );

        if ( fShowStroke )
        {
            canvas->drawPath( path, fStrokePaint );
        }
        if ( fShowHidden )
        {
            SkPath hidden;
            fStrokePaint.getFillPath( path, &hidden );
            canvas->drawPath( hidden, fHiddenPaint );
        }
        if ( fShowSkeleton )
        {
            canvas->drawPath( path, fSkeletonPaint );
        }
        canvas->drawPoints( SkCanvas::kPoints_PointMode, N, fPts, fPtsPaint );
    }

    Sample::Click* onFindClickHandler( SkScalar x, SkScalar y, skui::ModifierKey modi ) override
    {
        const SkScalar tol = 4;
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
        return nullptr;
    }

private:
    using INHERITED = Sample;
};

int main()
{
    int result = SampleApplication<FatStroke>::Run( );
    return result;
}


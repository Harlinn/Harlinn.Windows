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
#include "skia/effects/SkCornerPathEffect.h"
#include "skia/utils/SkRandom.h"

using namespace Harlinn::Windows::Skia;


class ArcToView : public Sample
{
    bool fDoFrame, fDoCorner, fDoConic;
    SkPaint fPtsPaint, fSkeletonPaint, fCornerPaint;
public:
    enum
    {
        N = 4
    };
    SkPoint fPts[N];

    ArcToView( )
        : fDoFrame( false ), fDoCorner( false ), fDoConic( false )
    {
        SkRandom rand;
        for ( int i = 0; i < N; ++i )
        {
            fPts[i].fX = 20 + rand.nextUScalar1( ) * 640;
            fPts[i].fY = 20 + rand.nextUScalar1( ) * 480;
        }

        const SkScalar rad = 50;

        fPtsPaint.setAntiAlias( true );
        fPtsPaint.setStrokeWidth( 15 );
        fPtsPaint.setStrokeCap( SkPaint::kRound_Cap );

        fCornerPaint.setAntiAlias( true );
        fCornerPaint.setStyle( SkPaint::kStroke_Style );
        fCornerPaint.setStrokeWidth( 13 );
        fCornerPaint.setColor( SK_ColorGREEN );
        fCornerPaint.setPathEffect( SkCornerPathEffect::Make( rad * 2 ) );

        fSkeletonPaint.setAntiAlias( true );
        fSkeletonPaint.setStyle( SkPaint::kStroke_Style );
        fSkeletonPaint.setColor( SK_ColorRED );
    }

    void toggle( bool& value )
    {
        value = !value;
    }

protected:
    SkString name( ) override { return SkString( "ArcTo" ); }

    bool onChar( SkUnichar uni ) override
    {
        switch ( uni )
        {
            case '1': this->toggle( fDoFrame ); return true;
            case '2': this->toggle( fDoCorner ); return true;
            case '3': this->toggle( fDoConic ); return true;
            default: break;
        }
        return false;
    }

    void makePath( SkPath* path )
    {
        path->moveTo( fPts[0] );
        for ( int i = 1; i < N; ++i )
        {
            path->lineTo( fPts[i] );
        }
        if ( !fDoFrame )
        {
            path->close( );
        }
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        canvas->drawPoints( SkCanvas::kPoints_PointMode, N, fPts, fPtsPaint );

        SkPath path;
        this->makePath( &path );

        if ( fDoCorner )
        {
            canvas->drawPath( path, fCornerPaint );
        }

        canvas->drawPath( path, fSkeletonPaint );
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
    int result = SampleApplication<ArcToView>::Run( );
    return result;
}


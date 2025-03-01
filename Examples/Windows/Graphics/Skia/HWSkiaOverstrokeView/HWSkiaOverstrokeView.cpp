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
#include "skia/core/SkCanvas.h"
#include "skia/core/SkPath.h"

#include <cmath>

using namespace Harlinn::Windows::Skia;


#define PI SK_ScalarPI

#define LIN_SEGMENTS 10

class OverstrokeView : public Sample
{
public:
    SkScalar fStroke;
    int fPathType;  // super lazy enum
    bool fClosePath;
    bool fDrawFillPath;
    bool fDumpHex;
    OverstrokeView( )
    {
        fStroke = 5;
        fPathType = 0;
        fClosePath = false;
        fDrawFillPath = false;
        fDumpHex = false;
        this->setBGColor( 0xFFFFFFFF );
    }

protected:
    SkString name( ) override { return SkString( "PathOverstroke" ); }

    bool onChar( SkUnichar uni ) override
    {
        switch ( uni )
        {
            case ',':
                fStroke += 1.0;
                return true;
            case '.':
                fStroke -= 1.0;
                return true;
            case 'x':
                fPathType = ( fPathType + 1 ) % 4;
                return true;
            case 'c':
                fClosePath = !fClosePath;
                return true;
            case 'f':
                fDrawFillPath = !fDrawFillPath;
                return true;
            case 'D':
                fDumpHex = !fDumpHex;
                return true;
            default:
                break;
        }
        return false;
    }

    SkPath quadPath( SkPoint p1, SkPoint p2 )
    {
        SkASSERT( p1.y( ) == p2.y( ) );

        SkPath path;
        path.moveTo( p1 );
        path.lineTo( p2 );

        SkPoint p3 = SkPoint::Make( ( p1.x( ) + p2.x( ) ) / 2.0f, p1.y( ) * 0.7f );

        path.quadTo( p3, p1 );

        return path;
    }

    SkPath cubicPath( SkPoint p1, SkPoint p2 )
    {
        SkASSERT( p1.y( ) == p2.y( ) );

        SkPath path;
        path.moveTo( p1 );

        SkPoint p3 = SkPoint::Make( ( p1.x( ) + p2.x( ) ) / 3.0f, p1.y( ) * 0.7f );
        SkPoint p4 = SkPoint::Make( 2.0f * ( p1.x( ) + p2.x( ) ) / 3.0f, p1.y( ) * 1.5f );

        path.cubicTo( p3, p4, p2 );

        return path;
    }

    SkPath linSemicirclePath( SkPoint p1, SkPoint p2 )
    {
        SkASSERT( p1.y( ) == p2.y( ) );

        SkPath path;
        path.moveTo( p1 );
        path.lineTo( p2 );

        SkPoint pt;

        for ( int i = 0; i < LIN_SEGMENTS; i++ )
        {
            float theta = i * PI / ( LIN_SEGMENTS );
            SkScalar x = 65 + 15 * cos( theta );
            SkScalar y = 50 - 15 * sin( theta );
            pt = SkPoint::Make( x, y );
            path.lineTo( pt );
        }
        path.lineTo( p1 );

        return path;
    }

    SkPath rectPath( SkPoint p1 )
    {
        SkRect r = SkRect::MakeXYWH( p1.fX, p1.fY, 20, 20 );
        SkPath path;
        path.addRect( r );

        return path;
    }

    void onDrawContent( SkCanvas* canvas ) override
    {
        const float SCALE = 5;

        canvas->translate( 30, 40 );
        canvas->scale( SCALE, SCALE );

        SkPoint p1 = SkPoint::Make( 50, 50 );
        SkPoint p2 = SkPoint::Make( 80, 50 );

        SkPath path;
        switch ( fPathType )
        {
            case 0:
                path = quadPath( p1, p2 );
                break;
            case 1:
                path = cubicPath( p1, p2 );
                break;
            case 2:
                path = rectPath( p1 );
                break;
            case 3:
                path = linSemicirclePath( p1, p2 );
                break;
            default:
                path = quadPath( p1, p2 );
                break;
        }

        if ( fClosePath )
        {
            path.close( );
        }

        SkPaint p;
        p.setColor( SK_ColorRED );
        p.setAntiAlias( true );
        p.setStyle( SkPaint::kStroke_Style );
        p.setStrokeWidth( fStroke );

        canvas->drawPath( path, p );

        if ( fDumpHex )
        {
            std::cerr << "path dumpHex" << std::endl;
            path.dumpHex( );
        }

        SkPaint hairp;
        hairp.setColor( SK_ColorBLACK );
        hairp.setAntiAlias( true );
        hairp.setStyle( SkPaint::kStroke_Style );

        if ( fDrawFillPath )
        {
            SkPath fillpath;
            p.getFillPath( path, &fillpath );

            canvas->drawPath( fillpath, hairp );

            if ( fDumpHex )
            {
                std::cerr << "fillpath dumpHex" << std::endl;
                fillpath.dumpHex( );
            }
        }

        if ( fDumpHex )
        {
            std::cerr << std::endl;

            fDumpHex = false;
        }

        // draw original path with green hairline
        hairp.setColor( SK_ColorGREEN );
        canvas->drawPath( path, hairp );
    }

private:
    using INHERITED = Sample;
};




int main()
{
    int result = SampleApplication<OverstrokeView>::Run( );
    return result;
}


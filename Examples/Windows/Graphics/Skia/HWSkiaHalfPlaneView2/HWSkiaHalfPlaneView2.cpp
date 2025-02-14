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

#include <HWSkia.h>
#include <HWForm.h>
#include "skia/core/SkCanvas.h"
#include "skia/core/SkColorPriv.h"
#include "skia/core/SkFont.h"
#include "skia/core/SkPaint.h"
#include "skia/core/SkPathBuilder.h"
#include "skia/utils/SkRandom.h"
#include "src/core/SkPathPriv.h"
#include "skia/tools/Resources.h"
#include "src/core/SkEdgeClipper.h"

using namespace Harlinn::Windows;

struct SkHalfPlane
{
    SkScalar fA, fB, fC;

    SkScalar eval( SkScalar x, SkScalar y ) const
    {
        return fA * x + fB * y + fC;
    }
    SkScalar operator()( SkScalar x, SkScalar y ) const { return this->eval( x, y ); }

    bool twoPts( SkPoint pts[2] ) const
    {
        // normalize plane to help with the perpendicular step, below
        SkScalar len = SkScalarSqrt( fA * fA + fB * fB );
        if ( !len )
        {
            return false;
        }
        SkScalar denom = SkScalarInvert( len );
        SkScalar a = fA * denom;
        SkScalar b = fB * denom;
        SkScalar c = fC * denom;

        // We compute p0 on the half-plane by setting one of the components to 0
        // We compute p1 by stepping from p0 along a perpendicular to the normal
        if ( b )
        {
            pts[0] = { 0, -c / b };
            pts[1] = { b, pts[0].fY - a };
        }
        else if ( a )
        {
            pts[0] = { -c / a,        0 };
            pts[1] = { pts[0].fX + b, -a };
        }
        else
        {
            return false;
        }

        SkASSERT( SkScalarNearlyZero( this->operator()( pts[0].fX, pts[0].fY ) ) );
        SkASSERT( SkScalarNearlyZero( this->operator()( pts[1].fX, pts[1].fY ) ) );
        return true;
    }

    enum Result
    {
        kAllNegative,
        kAllPositive,
        kMixed
    };
    Result test( const SkRect& bounds ) const
    {
        SkPoint diagMin, diagMax;
        if ( fA >= 0 )
        {
            diagMin.fX = bounds.fLeft;
            diagMax.fX = bounds.fRight;
        }
        else
        {
            diagMin.fX = bounds.fRight;
            diagMax.fX = bounds.fLeft;
        }
        if ( fB >= 0 )
        {
            diagMin.fY = bounds.fTop;
            diagMax.fY = bounds.fBottom;
        }
        else
        {
            diagMin.fY = bounds.fBottom;
            diagMax.fY = bounds.fTop;
        }
        SkScalar test = this->eval( diagMin.fX, diagMin.fY );
        SkScalar sign = test * this->eval( diagMax.fX, diagMin.fY );
        if ( sign > 0 )
        {
            // the path is either all on one side of the half-plane or the other
            if ( test < 0 )
            {
                return kAllNegative;
            }
            else
            {
                return kAllPositive;
            }
        }
        return kMixed;
    }
};


static void draw_halfplane( SkCanvas* canvas, SkPoint p0, SkPoint p1, SkColor c )
{
    SkVector v = p1 - p0;
    p0 = p0 - v * 1000;
    p1 = p1 + v * 1000;

    SkPaint paint;
    paint.setColor( c );
    canvas->drawLine( p0, p1, paint );
}


static void draw_halfplane( SkCanvas* canvas, const SkHalfPlane& p, SkColor c )
{
    SkPoint pts[2];
    p.twoPts( pts );
    draw_halfplane( canvas, pts[0], pts[1], c );
}

static void compute_half_planes( const SkMatrix& mx, SkScalar width, SkScalar height,
    SkHalfPlane planes[4] )
{
    SkScalar a = mx[0], b = mx[1], c = mx[2],
        d = mx[3], e = mx[4], f = mx[5],
        g = mx[6], h = mx[7], i = mx[8];

    planes[0] = { 2 * g - 2 * a / width,  2 * h - 2 * b / width,  2 * i - 2 * c / width };
    planes[1] = { 2 * a / width,        2 * b / width,        2 * c / width };
    planes[2] = { 2 * g - 2 * d / height, 2 * h - 2 * e / height, 2 * i - 2 * f / height };
    planes[3] = { 2 * d / height,       2 * e / height,       2 * f / height };
}

static SkPath make_path( )
{
    SkRandom rand;
    auto rand_pt = [&rand]( ) {
        auto x = rand.nextF( );
        auto y = rand.nextF( );
        return SkPoint{ x * 400, y * 400 };
    };

    SkPathBuilder path;
    for ( int i = 0; i < 4; ++i )
    {
        SkPoint pts[6];
        for ( auto& p : pts )
        {
            p = rand_pt( );
        }
        path.moveTo( pts[0] ).quadTo( pts[1], pts[2] ).quadTo( pts[3], pts[4] ).lineTo( pts[5] );
    }
    return path.detach( );
}


class SkiaHalfPlaneView2Form : public Form
{
public:
    using Base = Form;
private:
    std::unique_ptr<SkiaControl> control_;
    SkPoint fPts[4];
    SkPath fPath;
    size_t index_ = 0;
public:
    SkiaHalfPlaneView2Form( )
        : Base( )
    {
        SetText( L"Half Plane View 2" );

        control_ = make_control<SkiaControl>( this );
        control_->OnBeforeFirstRender.connect( [this]( Control* control, SkCanvas* canvas )
        {
            BeforeDraw( );
        } );

        control_->OnRender.connect( [this]( Control* control, SkCanvas* canvas )
        {
            DrawContent( canvas );
        } );
        control_->OnMouseLeftButtonDown.connect( [this]( Control* control, Message& message )
        {
            OnMouseClick( control, message );
        } );
    }

    void BeforeDraw( )
    {
        fPath = make_path( );
        SkRect r = fPath.getBounds( );
        r.toQuad( fPts );
    }

    void DrawContent( SkCanvas* canvas )
    {
        canvas->clear( SK_ColorWHITE );
        SkMatrix mx;
        {
            SkRect r = fPath.getBounds( );
            SkPoint src[4];
            r.toQuad( src );
            mx.setPolyToPoly( src, fPts, 4 );
        }

        SkPaint paint;
        canvas->drawPath( fPath, paint );

        canvas->save( );
        canvas->concat( mx );
        paint.setColor( 0x40FF0000 );
        canvas->drawPath( fPath, paint );
        canvas->restore( );

        // draw the frame
        paint.setStrokeWidth( 10 );
        paint.setColor( SK_ColorGREEN );
        canvas->drawPoints( SkCanvas::kPoints_PointMode, 4, fPts, paint );

        // draw the half-planes
        SkHalfPlane planes[4];
        compute_half_planes( mx, 400, 400, planes );
        for ( auto& p : planes )
        {
            draw_halfplane( canvas, p, SK_ColorRED );
        }
    }

    bool OnMouseClick( Control* control, Message& message )
    {
        auto mousePosition = message.pt;
        control->ScreenToClient( mousePosition );

        fPts[index_].fX = mousePosition.x;
        fPts[index_].fY = mousePosition.y;
        index_ = index_ == 4 ? 0 : index_ + 1;

        control->InvalidateRect( );
        return true;
    }

protected:
    void DoOnSize( Message& message ) override
    {
        if ( control_ )
        {
            Harlinn::Windows::Rectangle clientRect = GetClientRect( );
            control_->MoveWindow( 0, 0, clientRect.Width( ), clientRect.Height( ) );
        }
    }
};




int main( )
{
    try
    {
        SetThreadDpiAwarenessContext( DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 );

        auto application = std::make_shared<Harlinn::Windows::Application>( );
        application->Start( );

        SkGraphics::Init( );

        SkiaHalfPlaneView2Form form;
        form.Initialize( );

        auto result = application->Run( form );

        application->Stop( );

        return result;

    }
    catch ( std::exception& exc )
    {
        std::cout << exc.what( ) << std::endl;
    }
    catch ( ... )
    {

    }
    return 0;
}

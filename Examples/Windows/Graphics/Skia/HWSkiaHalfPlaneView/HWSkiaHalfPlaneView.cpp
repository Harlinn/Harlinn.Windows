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



static SkPath clip( const SkPath& path, SkPoint p0, SkPoint p1 )
{
    SkMatrix mx, inv;
    SkVector v = p1 - p0;
    mx.setAll( v.fX, -v.fY, p0.fX,
        v.fY, v.fX, p0.fY,
        0, 0, 1 );
    SkAssertResult( mx.invert( &inv ) );

    SkPath rotated;
    path.transform( inv, &rotated );

    SkScalar big = 1e28f;
    SkRect clip = { -big, 0, big, big };

    struct Rec
    {
        SkPathBuilder   fResult;
        SkPoint         fPrev = { 0, 0 };
    } rec;

    SkEdgeClipper::ClipPath( rotated, clip, false,
        []( SkEdgeClipper* clipper, bool newCtr, void* ctx ) {
        Rec* rec = (Rec*)ctx;

        bool addLineTo = false;
        SkPoint      pts[4];
        SkPath::Verb verb;
        while ( ( verb = clipper->next( pts ) ) != SkPath::kDone_Verb )
        {
            if ( newCtr )
            {
                rec->fResult.moveTo( pts[0] );
                rec->fPrev = pts[0];
                newCtr = false;
            }

            if ( addLineTo || pts[0] != rec->fPrev )
            {
                rec->fResult.lineTo( pts[0] );
            }

            switch ( verb )
            {
                case SkPath::kLine_Verb:
                    rec->fResult.lineTo( pts[1] );
                    rec->fPrev = pts[1];
                    break;
                case SkPath::kQuad_Verb:
                    rec->fResult.quadTo( pts[1], pts[2] );
                    rec->fPrev = pts[2];
                    break;
                case SkPath::kCubic_Verb:
                    rec->fResult.cubicTo( pts[1], pts[2], pts[3] );
                    rec->fPrev = pts[3];
                    break;
                default: break;
            }
            addLineTo = true;
        }
    }, &rec );

    return rec.fResult.detach( ).makeTransform( mx );
}

static void draw_halfplane( SkCanvas* canvas, SkPoint p0, SkPoint p1, SkColor c )
{
    SkVector v = p1 - p0;
    p0 = p0 - v * 1000;
    p1 = p1 + v * 1000;

    SkPaint paint;
    paint.setAntiAlias( true );
    paint.setColor( c );
    canvas->drawLine( p0, p1, paint );
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

class SkiaHalfPlaneViewForm : public Form
{
public:
    using Base = Form;
private:
    std::unique_ptr<SkiaControl> control_;
    SkPoint fPts[2];
    SkPath fPath;
public:
    SkiaHalfPlaneViewForm( )
        : Base( )
    {
        SetText( L"Half Plane View" );

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
        fPts[0] = { 0, 0 };
        fPts[1] = { 3, 2 };
        fPath = make_path( );
    }

    void DrawContent( SkCanvas* canvas )
    {
        canvas->clear( SK_ColorWHITE );
        SkPaint paint;

        paint.setAntiAlias( true );
        paint.setColor( { 0.5f, 0.5f, 0.5f, 1.0f }, nullptr );
        canvas->drawPath( fPath, paint );

        paint.setColor( { 0, 0, 0, 1 }, nullptr );

        canvas->drawPath( clip( fPath, fPts[0], fPts[1] ), paint );

        draw_halfplane( canvas, fPts[0], fPts[1], SK_ColorRED );
    }

    bool OnMouseClick( Control* control, Message& message )
    {
        auto mousePosition = message.pt;
        control->ScreenToClient( mousePosition );

        fPts[0].fX = mousePosition.x;
        fPts[0].fY = mousePosition.y;

        fPts[1] = fPts[0] + SkPoint{ 3, 2 };
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

        SkiaHalfPlaneViewForm form;
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

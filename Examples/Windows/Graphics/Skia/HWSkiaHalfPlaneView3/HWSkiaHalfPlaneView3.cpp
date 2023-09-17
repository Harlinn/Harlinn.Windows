#include <HWSkia.h>
#include <HWForm.h>
#include <HCCEnvironment.h>
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
using namespace Harlinn::Common::Core;

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


static SkM44 inv( const SkM44& m )
{
    SkM44 inverse;
    SkAssertResult( m.invert( &inverse ) );
    return inverse;
}

static SkHalfPlane half_plane_w0( const SkMatrix& m )
{
    return { m[SkMatrix::kMPersp0], m[SkMatrix::kMPersp1], m[SkMatrix::kMPersp2] - 0.05f };
}


class SkiaCameraControlBase : public SkiaControl
{
public:
    using Base = SkiaControl;
private:
    float   fNear = 0.05f;
    float   fFar = 4;
    float   fAngle = SK_ScalarPI / 4;

    SkV3    fEye{ 0, 0, 1.0f / tan( fAngle / 2 ) - 1 };
    SkV3    fCOA{ 0, 0, 0 };
    SkV3    fUp{ 0, 1, 0 };

    SkM44  fRot;
    SkV3   fTrans;

    SkPath fPath;
    sk_sp<SkShader> fShader;
    bool fShowUnclipped = false;

public:
    SkiaCameraControlBase()
        : Base()
    { }

    void rotate( float x, float y, float z )
    {
        SkM44 r;
        if ( x )
        {
            r.setRotateUnit( { 1, 0, 0 }, x );
        }
        else if ( y )
        {
            r.setRotateUnit( { 0, 1, 0 }, y );
        }
        else
        {
            r.setRotateUnit( { 0, 0, 1 }, z );
        }
        fRot = r * fRot;
    }

    SkM44 get44( const SkRect& r )
    {
        SkScalar w = r.width( );
        SkScalar h = r.height( );

        SkM44 camera = SkM44::LookAt( fEye, fCOA, fUp ),
            perspective = SkM44::Perspective( fNear, fFar, fAngle ),
            translate = SkM44::Translate( fTrans.x, fTrans.y, fTrans.z ),
            viewport = SkM44::Translate( r.centerX( ), r.centerY( ), 0 ) *
            SkM44::Scale( w * 0.5f, h * 0.5f, 1 );

        return viewport * perspective * camera * translate * fRot * inv( viewport );
    }

    void FinalizeOnChar( Message& message )
    {
        InvalidateRect( );
        message.handled = true;
        message.result = 0;
    }

    void DoOnChar( Message& message ) override
    {
        wchar_t characterCode = message.wParam;
        float delta = SK_ScalarPI / 30;
        switch ( characterCode )
        {
            case '8': 
                this->rotate( delta, 0, 0 );
                FinalizeOnChar( message );
                break;
            case '2': 
                this->rotate( -delta, 0, 0 ); 
                FinalizeOnChar( message );
                break;
            case '4': 
                this->rotate( 0, delta, 0 ); 
                FinalizeOnChar( message );
                break;
            case '6': 
                this->rotate( 0, -delta, 0 ); 
                FinalizeOnChar( message );
                break;
            case '-': 
                this->rotate( 0, 0, delta ); 
                FinalizeOnChar( message );
                break;
            case '+': 
                this->rotate( 0, 0, -delta ); 
                FinalizeOnChar( message );
                break;
            case 'i': 
                fTrans.z += 0.1f; SkDebugf( "z %g\n", fTrans.z ); 
                FinalizeOnChar( message );
                break;
            case 'k': 
                fTrans.z -= 0.1f; SkDebugf( "z %g\n", fTrans.z ); 
                FinalizeOnChar( message );
                break;
            case 'n': 
                fNear += 0.1f; SkDebugf( "near %g\n", fNear ); 
                FinalizeOnChar( message );
                break;
            case 'N': 
                fNear -= 0.1f; SkDebugf( "near %g\n", fNear ); 
                FinalizeOnChar( message );
                break;
            case 'f': 
                fFar += 0.1f; SkDebugf( "far  %g\n", fFar ); 
                FinalizeOnChar( message );
                break;
            case 'F': 
                fFar -= 0.1f; SkDebugf( "far  %g\n", fFar ); 
                FinalizeOnChar( message );
                break;
            default: 
                
                break;
        }
    }


    void DoOnBeforeFirstRender( SkCanvas* canvas ) override
    {
        Base::DoOnBeforeFirstRender( canvas );
    }

    void DoOnRender( SkCanvas* canvas ) override
    {
        Base::DoOnRender( canvas );
    }
};


class SkiaCameraControl : public SkiaCameraControlBase
{
public:
    using Base = SkiaCameraControlBase;
private:
    SkPath fPath;
    sk_sp<SkShader> fShader;
    bool fShowUnclipped = false;
public:
    SkiaCameraControl()
        : Base()
    { }
protected:
    void DoOnChar( Message& message ) override
    {
        Base::DoOnChar( message );
        wchar_t characterCode = message.wParam;

        switch ( characterCode )
        {
            case 'u': 
                fShowUnclipped = !fShowUnclipped;
        }

    }
    void DoOnBeforeFirstRender( SkCanvas* canvas ) override
    {
        Base::DoOnBeforeFirstRender( canvas );
        fPath = make_path( );
        fShader = GetResourceAsImage( "images/mandrill_128.png" ) ->makeShader( SkSamplingOptions( ), SkMatrix::Scale( 3, 3 ) );

    }

    void DoOnRender( SkCanvas* canvas ) override
    {
        Base::DoOnRender( canvas );
        canvas->clear( SK_ColorWHITE );
        SkM44 mx = this->get44( { 0, 0, 400, 400 } );

        SkPaint paint;
        paint.setColor( { 0.75, 0.75, 0.75, 1 } );
        canvas->drawPath( fPath, paint );

        paint.setShader( fShader );

        if ( fShowUnclipped )
        {
            canvas->save( );
            canvas->concat( mx );
            paint.setAlphaf( 0.33f );
            canvas->drawPath( fPath, paint );
            paint.setAlphaf( 1.f );
            canvas->restore( );
        }


        SkColor planeColor = SK_ColorBLUE;
        SkPath clippedPath, * path = &fPath;
        if ( SkPathPriv::PerspectiveClip( fPath, mx.asM33( ), &clippedPath ) )
        {
            path = &clippedPath;
            planeColor = SK_ColorRED;
        }
        canvas->save( );
        canvas->concat( mx );
        canvas->drawPath( *path, paint );
        canvas->restore( );

        SkHalfPlane hpw = half_plane_w0( mx.asM33( ) );
        draw_halfplane( canvas, hpw, planeColor );
    }

};



class SkiaHalfPlaneView3Form : public Form
{
public:
    using Base = Form;
private:
    std::unique_ptr<SkiaCameraControl> control_;
    SkPoint fPts[4];
    SkPath fPath;
    size_t index_ = 0;
public:
    SkiaHalfPlaneView3Form( )
        : Base( )
    {
        SetText( L"Half Plane View 3" );
        control_ = make_control<SkiaCameraControl>( this );
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
    void DoOnSetFocus( Message& message ) override
    {
        Base::DoOnSetFocus( message );
        control_->SetFocus( );
    }

};




int main( )
{
    try
    {
        SetThreadDpiAwarenessContext( DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 );

        Harlinn::Windows::Application application;
        application.Start( );

        SkGraphics::Init( );

        auto hccHome = Environment::EnvironmentVariable( "HCC_HOME" );
        auto resourcesDirectory = hccHome + "\\resources";
        SetResourcePath( resourcesDirectory.c_str( ) );


        SkiaHalfPlaneView3Form form;
        form.Initialize( );

        auto result = application.Run( form );

        application.Stop( );

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

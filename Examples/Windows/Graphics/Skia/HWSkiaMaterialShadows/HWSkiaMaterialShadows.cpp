#include <HWSkia.h>
#include <HWForm.h>
#include "skia/core/SkColorFilter.h"
#include "skia/core/SkPath.h"
#include "skia/core/SkPoint3.h"
#include "skia/pathops/SkPathOps.h"
#include "skia/utils/SkCamera.h"
#include "skia/utils/SkShadowUtils.h"
#include "src/core/SkBlurMask.h"
#include "src/utils/SkUTF.h"
#include "skia/tools/ToolUtils.h"
#include "skia/tools/timer/TimeUtils.h"

using namespace Harlinn::Windows;

class SkiaMaterialShadowsForm : public Form
{
public:
    using Base = Form;
private:
    std::unique_ptr<SkiaControl> control_;
    SkPath    fCirclePath;
    SkPath    fCapsulePath;
    SkPath    fLargeRRPath;
    SkPath    fSmallRRPath;

    SkPoint3  fLightPos;
public:
    SkiaMaterialShadowsForm( )
        : Base( )
    {
        SetText( L"Material Shadows" );

        control_ = make_control<SkiaControl>( this );
        control_->OnBeforeFirstRender.connect( [this]( Control* control, SkCanvas* canvas )
        {
            BeforeDraw( );
        } );
        control_->OnRender.connect( [this]( Control* control, SkCanvas* canvas )
        {
            DrawContent( canvas );
        } );
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

    void BeforeDraw( )
    {
        fCirclePath.addCircle( 0, 0, 56 / 2 );
        fCapsulePath.addRRect( SkRRect::MakeRectXY( SkRect::MakeXYWH( -64, -24, 128, 48 ), 24, 24 ) );
        fLargeRRPath.addRRect( SkRRect::MakeRectXY( SkRect::MakeXYWH( -64, -64, 128, 128 ), 4, 4 ) );
        fSmallRRPath.addRRect( SkRRect::MakeRectXY( SkRect::MakeXYWH( -40, -40, 80, 80 ), 4, 4 ) );

        fLightPos = SkPoint3::Make( 0, -700, 700 );
    }

    void DrawShadowedPath( SkCanvas* canvas, const SkPath& path,
        const SkPoint3& zPlaneParams,
        const SkPaint& paint, SkScalar ambientAlpha,
        const SkPoint3& lightPos, SkScalar lightRadius, SkScalar spotAlpha )
    {
        uint32_t flags = 0;
        flags |= SkShadowFlags::kDirectionalLight_ShadowFlag;

        SkColor ambientColor = SkColorSetARGB( ambientAlpha * 255, 0, 0, 0 );
        SkColor spotColor = SkColorSetARGB( spotAlpha * 255, 0, 0, 0 );
        SkShadowUtils::DrawShadow( canvas, path, zPlaneParams, lightPos, lightRadius,
            ambientColor, spotColor, flags );

        canvas->drawPath( path, paint );
    }

    void DrawContent( SkCanvas* canvas )
    {
        canvas->drawColor( 0xFFFFFFFF );

        const SkScalar kLightRadius = 1.1f;
        const SkScalar kAmbientAlpha = 0.05f;
        const SkScalar kSpotAlpha = 0.35f;

        const std::array<SkScalar,6> elevations = { 1, 3, 6, 8, 12, 24 };

        SkPaint paint;
        paint.setAntiAlias( true );

        SkPoint3 lightPos = fLightPos;
        SkPoint3 zPlaneParams = SkPoint3::Make( 0, 0, 0 );

        paint.setColor( SK_ColorWHITE );
        canvas->save( );
        canvas->translate( 80, 80 );
        //for ( unsigned int i = 0; i < SK_ARRAY_COUNT( elevations ); ++i )
        for(auto elevation : elevations )
        {
            zPlaneParams.fZ = elevation;
            this->DrawShadowedPath( canvas, fCirclePath, zPlaneParams, paint, kAmbientAlpha, lightPos, kLightRadius, kSpotAlpha );
            canvas->translate( 80, 0 );
        }
        canvas->restore( );

        canvas->save( );
        canvas->translate( 120, 175 );
        for ( auto elevation : elevations )
        {
            zPlaneParams.fZ = elevation;
            this->DrawShadowedPath( canvas, fCapsulePath, zPlaneParams, paint, kAmbientAlpha, lightPos, kLightRadius, kSpotAlpha );
            canvas->translate( 160, 0 );
        }
        canvas->restore( );

        canvas->save( );
        canvas->translate( 120, 320 );
        for ( auto elevation : elevations )
        {
            zPlaneParams.fZ = elevation;
            this->DrawShadowedPath( canvas, fLargeRRPath, zPlaneParams, paint, kAmbientAlpha, lightPos, kLightRadius, kSpotAlpha );
            canvas->translate( 160, 0 );
        }
        canvas->restore( );

        canvas->save( );
        canvas->translate( 100, 475 );
        for ( auto elevation : elevations )
        {
            zPlaneParams.fZ = elevation;
            this->DrawShadowedPath( canvas, fSmallRRPath, zPlaneParams, paint, kAmbientAlpha, lightPos, kLightRadius, kSpotAlpha );
            canvas->translate( 160, 0 );
        }
        canvas->restore( );

        canvas->save( );
        canvas->translate( 100, 600 );
        for ( auto elevation : elevations )
        {
            canvas->save( );
            zPlaneParams.fZ = elevation;
            canvas->rotate( 10 );
            this->DrawShadowedPath( canvas, fSmallRRPath, zPlaneParams, paint, kAmbientAlpha, lightPos, kLightRadius, kSpotAlpha );
            canvas->restore( );
            canvas->translate( 160, 0 );
        }
        canvas->restore( );

        canvas->save( );
        canvas->translate( 100, 725 );
        for ( auto elevation : elevations )
        {
            canvas->save( );
            zPlaneParams.fZ = elevation;
            canvas->rotate( 45 );
            this->DrawShadowedPath( canvas, fSmallRRPath, zPlaneParams, paint, kAmbientAlpha, lightPos, kLightRadius, kSpotAlpha );
            canvas->restore( );
            canvas->translate( 160, 0 );
        }
        canvas->restore( );

    }

};




int main( )
{
    try
    {
        SetThreadDpiAwarenessContext( DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 );

        Harlinn::Windows::ApplicationOptions applicationOptions;
        applicationOptions.Load( );
        Harlinn::Windows::Application application( applicationOptions );
        application.Start( );

        SkGraphics::Init( );

        SkiaMaterialShadowsForm form;
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

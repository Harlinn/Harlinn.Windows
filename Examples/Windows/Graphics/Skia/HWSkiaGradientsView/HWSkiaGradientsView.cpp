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

#include "skia/effects/SkGradientShader.h"

using namespace Harlinn::Windows;

static sk_sp<SkShader> setgrad( const SkRect& r, SkColor c0, SkColor c1 )
{
    SkColor colors[] = { c0, c1 };
    SkPoint pts[] = { { r.fLeft, r.fTop }, { r.fRight, r.fTop } };
    return SkGradientShader::MakeLinear( pts, colors, nullptr, 2, SkTileMode::kClamp );
}

static void test_alphagradients( SkCanvas* canvas )
{
    SkRect r;
    r.setLTRB( 10, 10, 410, 30 );
    SkPaint p, p2;
    p2.setStyle( SkPaint::kStroke_Style );

    p.setShader( setgrad( r, 0xFF00FF00, 0x0000FF00 ) );
    canvas->drawRect( r, p );
    canvas->drawRect( r, p2 );

    r.offset( 0, r.height( ) + SkIntToScalar( 4 ) );
    p.setShader( setgrad( r, 0xFF00FF00, 0x00000000 ) );
    canvas->drawRect( r, p );
    canvas->drawRect( r, p2 );

    r.offset( 0, r.height( ) + SkIntToScalar( 4 ) );
    p.setShader( setgrad( r, 0xFF00FF00, 0x00FF0000 ) );
    canvas->drawRect( r, p );
    canvas->drawRect( r, p2 );
}

///////////////////////////////////////////////////////////////////////////////

struct GradData
{
    int             fCount;
    const SkColor* fColors;
    const SkScalar* fPos;
};

static const SkColor gColors[] = {
    SK_ColorRED, SK_ColorGREEN, SK_ColorBLUE, SK_ColorWHITE, SK_ColorBLACK
};
static const SkScalar gPos0[] = { 0, SK_Scalar1 };
static const SkScalar gPos1[] = { SK_Scalar1 / 4, SK_Scalar1 * 3 / 4 };
static const SkScalar gPos2[] = {
    0, SK_Scalar1 / 8, SK_Scalar1 / 2, SK_Scalar1 * 7 / 8, SK_Scalar1
};

static const GradData gGradData[] = {
    { 2, gColors, nullptr },
    { 2, gColors, gPos0 },
    { 2, gColors, gPos1 },
    { 5, gColors, nullptr },
    { 5, gColors, gPos2 }
};

static sk_sp<SkShader> MakeLinear( const SkPoint pts[2], const GradData& data, SkTileMode tm )
{
    return SkGradientShader::MakeLinear( pts, data.fColors, data.fPos, data.fCount, tm );
}

static sk_sp<SkShader> MakeRadial( const SkPoint pts[2], const GradData& data, SkTileMode tm )
{
    SkPoint center;
    center.set( SkScalarAve( pts[0].fX, pts[1].fX ),
        SkScalarAve( pts[0].fY, pts[1].fY ) );
    return SkGradientShader::MakeRadial( center, center.fX, data.fColors,
        data.fPos, data.fCount, tm );
}

static sk_sp<SkShader> MakeSweep( const SkPoint pts[2], const GradData& data, SkTileMode tm )
{
    SkPoint center;
    center.set( SkScalarAve( pts[0].fX, pts[1].fX ),
        SkScalarAve( pts[0].fY, pts[1].fY ) );
    return SkGradientShader::MakeSweep( center.fX, center.fY, data.fColors, data.fPos, data.fCount );
}

static sk_sp<SkShader> Make2Conical( const SkPoint pts[2], const GradData& data, SkTileMode tm )
{
    SkPoint center0, center1;
    center0.set( SkScalarAve( pts[0].fX, pts[1].fX ),
        SkScalarAve( pts[0].fY, pts[1].fY ) );
    center1.set( SkScalarInterp( pts[0].fX, pts[1].fX, SkIntToScalar( 3 ) / 5 ),
        SkScalarInterp( pts[0].fY, pts[1].fY, SkIntToScalar( 1 ) / 4 ) );
    return SkGradientShader::MakeTwoPointConical(
        center1, ( pts[1].fX - pts[0].fX ) / 7,
        center0, ( pts[1].fX - pts[0].fX ) / 2,
        data.fColors, data.fPos, data.fCount, tm );
}

static sk_sp<SkShader> Make2ConicalConcentric( const SkPoint pts[2], const GradData& data,
    SkTileMode tm )
{
    SkPoint center;
    center.set( SkScalarAve( pts[0].fX, pts[1].fX ),
        SkScalarAve( pts[0].fY, pts[1].fY ) );
    return SkGradientShader::MakeTwoPointConical(
        center, ( pts[1].fX - pts[0].fX ) / 7,
        center, ( pts[1].fX - pts[0].fX ) / 2,
        data.fColors, data.fPos, data.fCount, tm );
}

typedef sk_sp<SkShader>( *GradMaker )( const SkPoint pts[2], const GradData& data, SkTileMode tm );

static const GradMaker gGradMakers[] = {
    MakeLinear, MakeRadial, MakeSweep, Make2Conical, Make2ConicalConcentric
};


class SkiaGradientsViewForm : public Form
{
public:
    using Base = Form;
private:
    std::unique_ptr<SkiaControl> control_;
public:
    SkiaGradientsViewForm( )
        : Base( )
    {
        SetText( L"Gradients View" );

        control_ = make_control<SkiaControl>( this );
        control_->OnRender.connect( [this]( Control* control, SkCanvas* canvas )
        {
            canvas->clear( SK_ColorWHITE );
            SkPoint pts[2] = 
            {
                { 0, 0 },
                { SkIntToScalar( 100 ), SkIntToScalar( 100 ) }
            };
            SkRect r = { 0, 0, SkIntToScalar( 100 ), SkIntToScalar( 100 ) };
            SkPaint paint;
            paint.setDither( true );

            canvas->save( );
            canvas->translate( SkIntToScalar( 20 ), SkIntToScalar( 10 ) );

            for ( int tm = 0; tm < kSkTileModeCount; ++tm )
            {
                canvas->save( );
                for ( size_t i = 0; i < SK_ARRAY_COUNT( gGradData ); i++ )
                {
                    canvas->save( );
                    for ( size_t j = 0; j < SK_ARRAY_COUNT( gGradMakers ); j++ )
                    {
                        paint.setShader( gGradMakers[j]( pts, gGradData[i], (SkTileMode)tm ) );
                        canvas->drawRect( r, paint );
                        canvas->translate( 0, SkIntToScalar( 120 ) );
                    }
                    canvas->restore( );
                    canvas->translate( SkIntToScalar( 120 ), 0 );
                }
                canvas->restore( );
                canvas->translate( SK_ARRAY_COUNT( gGradData ) * SkIntToScalar( 120 ), 0 );
            }
            canvas->restore( );

            canvas->translate( 0, SkIntToScalar( 370 ) );
            test_alphagradients( canvas );
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
};




int main( )
{
    try
    {
        SetThreadDpiAwarenessContext( DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 );

        auto application = std::make_shared<Harlinn::Windows::Application>( );
        application->Start( );

        SkGraphics::Init( );

        SkiaGradientsViewForm form;
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

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


#include <HWSkia.h>
#include <HWForm.h>
#include <HWStdCtrls.h>
#include "skia/core/SkPath.h"
#include "skia/core/SkRRect.h"
#include "skia/core/SkTime.h"
#include "skia/utils/SkRandom.h"

using namespace Harlinn::Windows;
using namespace Harlinn::Common;

#define USE_PATH 1

class SkiaClockViewForm : public Form
{
public:
    using Base = Form;
private:
    std::unique_ptr<SkiaControl> control_;
    std::unique_ptr<Timer> timer_;
public:
    SkiaClockViewForm( )
        : Base( )
    {
        SetText( L"Clock" );

        timer_ = std::make_unique <Timer>( );
        timer_->OnTick.connect( [this]( Timer* sender ) 
        {
            control_->InvalidateRect( );
        } );

        control_ = make_control<SkiaControl>( this );
        control_->OnBeforeFirstRender.connect( [this]( Control* control, SkCanvas* canvas )
        {
            auto halfSecond = TimeSpan::FromSeconds( 0.5 );
            timer_->SetInterval( halfSecond );
            timer_->SetEnabled( );
        } );

        
        control_->OnRender.connect( [this]( Control* control, SkCanvas* canvas )
        {
            SkPaint paintFill;
            SkPaint paintStroke;
            SkPath  path;
            canvas->clear( SK_ColorWHITE );
            canvas->save( );
            canvas->translate( 150, 150 );
            canvas->scale( 0.4f, 0.4f );
            canvas->rotate( -180.f / 2.f );

            paintFill.setAntiAlias( true );
            paintFill.setColor( SK_ColorBLACK );
            paintStroke.setAntiAlias( true );
            paintStroke.setStyle( SkPaint::kStroke_Style );
            paintStroke.setColor( SK_ColorBLACK );
            paintStroke.setStrokeWidth( 8 );
            paintStroke.setStrokeCap( SkPaint::kRound_Cap );

            // Hour marks
            SkRect rect;
#ifndef USE_PATH
            rect = SkRect::MakeLTRB( 200 - 4, -4, 240 + 4, 4 );
            SkRRect rrect;
            SkVector radii[4] = { {4,4}, {4,4}, {4,4}, {4,4} };
            rrect.setRectRadii( rect, radii );
#endif
            canvas->save( );
            for ( int i = 0; i < 12; i++ )
            {
                canvas->rotate( 180.f / 6.f );
#ifdef USE_PATH
                path.reset( );
                path.moveTo( 200, 0 );
                path.lineTo( 240, 0 );
                canvas->drawPath( path, paintStroke );
#else
                canvas->drawRRect( rrect, paintFill );
#endif
            }
            canvas->restore( );

            // Minute marks
            canvas->save( );
#ifdef USE_PATH
            paintStroke.setStrokeWidth( 5 );
#else
            rect = SkRect::MakeLTRB( 231.5f, -2.5f, 242.5, 2.5f );
            radii[0] = SkPoint::Make( 2.5f, 2.5f );
            radii[1] = SkPoint::Make( 2.5f, 2.5f );
            radii[2] = SkPoint::Make( 2.5f, 2.5f );
            radii[3] = SkPoint::Make( 2.5f, 2.5f );
            rrect.setRectRadii( rect, radii );
#endif
            for ( int i = 0; i < 60; i++ )
            {
                if ( i % 5 == 0 )
                {
                    canvas->rotate( 180.f / 30.f );
                    continue;
                }
#ifdef USE_PATH
                path.reset( );
                path.moveTo( 234, 0 );
                path.lineTo( 240, 0 );
                canvas->drawPath( path, paintStroke );
#else
                canvas->drawRRect( rrect, paintFill );
#endif
                canvas->rotate( 180.f / 30.f );
            }
            canvas->restore( );

            auto now = Core::DateTime::Now( );
            SkTime::DateTime time{};
            time.fHour = now.Hour( );
            time.fMinute = now.Minute( );
            time.fSecond = now.Second( );


            time.fHour = time.fHour >= 12 ? time.fHour - 12 : time.fHour;
            paintFill.setColor( SK_ColorBLACK );

            // Write hours
            canvas->save( );
            canvas->rotate( time.fHour * ( 180.f / 6.f ) + time.fMinute * ( 180.f / 360.f )
                + time.fSecond * ( 180.f / 21600.f ) );
#ifdef USE_PATH
            paintStroke.setStrokeWidth( 14 );
            path.reset( );
            path.moveTo( -20, 0 );
            path.lineTo( 80, 0 );
            canvas->drawPath( path, paintStroke );
#else
            rect = SkRect::MakeLTRB( -20 - 7, -7, 80 + 7, 7 );
            radii[0] = SkPoint::Make( 7, 7 );
            radii[1] = SkPoint::Make( 7, 7 );
            radii[2] = SkPoint::Make( 7, 7 );
            radii[3] = SkPoint::Make( 7, 7 );
            rrect.setRectRadii( rect, radii );
            canvas->drawRRect( rrect, paintFill );
#endif
            canvas->restore( );

            // Write minutes
            canvas->save( );
            canvas->rotate( time.fMinute * ( 180.f / 30.f )
                + time.fSecond * ( 180.f / 1800.f ) );
#ifdef USE_PATH
            paintStroke.setStrokeWidth( 10 );
            path.reset( );
            path.moveTo( -56, 0 );
            path.lineTo( 224, 0 );
            canvas->drawPath( path, paintStroke );
#else
            rect = SkRect::MakeLTRB( -56 - 5, -5, 224 + 5, 5 );
            radii[0] = SkPoint::Make( 5, 5 );
            radii[1] = SkPoint::Make( 5, 5 );
            radii[2] = SkPoint::Make( 5, 5 );
            radii[3] = SkPoint::Make( 5, 5 );
            rrect.setRectRadii( rect, radii );
            canvas->drawRRect( rrect, paintFill );
#endif
            canvas->restore( );

            // Write seconds
            canvas->save( );
            canvas->rotate( time.fSecond * ( 180.f / 30.f ) );
            paintFill.setColor( 0xffd40000 );
            paintStroke.setColor( 0xffd40000 );
            paintStroke.setStrokeWidth( 6 );
#ifdef USE_PATH
            path.reset( );
            path.moveTo( -60, 0 );
            path.lineTo( 166, 0 );
            canvas->drawPath( path, paintStroke );
#else
            rect = SkRect::MakeLTRB( -60 - 3, -3, 166 + 3, 3 );
            radii[0] = SkPoint::Make( 3, 3 );
            radii[1] = SkPoint::Make( 3, 3 );
            radii[2] = SkPoint::Make( 3, 3 );
            radii[3] = SkPoint::Make( 3, 3 );
            rrect.setRectRadii( rect, radii );
            canvas->drawRRect( rrect, paintFill );
#endif
            rect = SkRect::MakeLTRB( -20, -20, 20, 20 );
#ifdef USE_PATH
            path.reset( );
            path.arcTo( rect, 0, 0, false );
            path.addOval( rect, SkPathDirection::kCCW );
            path.arcTo( rect, 360, 0, true );
            canvas->drawPath( path, paintFill );
#else
            canvas->drawOval( rect, paintFill );
#endif
            rect = SkRect::MakeLTRB( -20 + 190, -20, 20 + 190, 20 );
#ifdef USE_PATH
            path.reset( );
            path.arcTo( rect, 0, 0, false );
            path.addOval( rect, SkPathDirection::kCCW );
            path.arcTo( rect, 360, 0, true );
            canvas->drawPath( path, paintStroke );
#else
            canvas->drawOval( rect, paintStroke );
#endif
            paintFill.setColor( 0xff505050 );
#ifdef USE_PATH
            rect = SkRect::MakeLTRB( -6, -6, 6, 6 );
            path.arcTo( rect, 0, 0, false );
            path.addOval( rect, SkPathDirection::kCCW );
            path.arcTo( rect, 360, 0, true );
            canvas->drawPath( path, paintFill );
#else
            canvas->drawOval( rect, paintFill );
            rect = SkRect::MakeLTRB( -6, -6, 6, 6 );
            canvas->drawOval( rect, paintFill );
#endif
            canvas->restore( );

            paintStroke.setStrokeWidth( 18 );
            paintStroke.setColor( 0xff325FA2 );
            rect = SkRect::MakeLTRB( -284, -284, 284, 284 );
#ifdef USE_PATH
            path.reset( );
            path.arcTo( rect, 0, 0, false );
            path.addOval( rect, SkPathDirection::kCCW );
            path.arcTo( rect, 360, 0, true );
            canvas->drawPath( path, paintStroke );
#else
            canvas->drawOval( rect, paintStroke );
#endif

            canvas->restore( );
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

        SkiaClockViewForm form;
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

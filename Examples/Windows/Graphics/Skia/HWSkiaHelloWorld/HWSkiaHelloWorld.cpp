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

using namespace Harlinn::Windows;

class SkiaHelloWorldForm : public Form
{
public:
    using Base = Form;
private:
    std::unique_ptr<SkiaControl> control_;
    Harlinn::Windows::Point mousePosition_;
public:
    SkiaHelloWorldForm( )
        : Base( )
    {
        SetText( L"Skia Hello world" );

        control_ = make_control<SkiaControl>( this );
        control_->OnMouseMove.connect( [this]( Control* control, Message& message )
        {
            mousePosition_ = message.pt;
            control->ScreenToClient( mousePosition_ );
            InvalidateRect( );
        } );
        control_->OnRender.connect( [this]( Control* control, SkCanvas* canvas ) 
        {
            SkPaint paint;
            canvas->clear( SK_ColorWHITE );
            paint.setColor( SK_ColorRED );

            SkRect rect = SkRect::MakeXYWH( mousePosition_.X( ), mousePosition_.Y( ), 128, 128 );
            canvas->drawRect( rect, paint );
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




int main()
{
    try
    {
        SetThreadDpiAwarenessContext( DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 );

        auto application = std::make_shared<Harlinn::Windows::Application>( );
        application->Start( );

        SkGraphics::Init( );

        SkiaHelloWorldForm form;
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

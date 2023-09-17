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

        Harlinn::Windows::Application application;
        application.Start( );

        SkGraphics::Init( );

        SkiaHelloWorldForm form;
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

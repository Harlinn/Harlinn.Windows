#include <HWSkia.h>
#include <HWForm.h>
#include "skia/core/SkFont.h"
#include "skia/core/SkShader.h"

using namespace Harlinn::Windows;

class SkiaLCDTextForm : public Form
{
public:
    using Base = Form;
private:
    std::unique_ptr<SkiaControl> control_;
public:
    SkiaLCDTextForm( )
        : Base( )
    {
        SetText( L"LCD Text" );

        control_ = make_control<SkiaControl>( this );
        control_->OnRender.connect( [this]( Control* control, SkCanvas* canvas )
        {
            canvas->clear( SK_ColorWHITE );
            SkPaint paint;

            SkScalar textSize = SkIntToScalar( 6 );
            SkScalar delta = SK_Scalar1;
            const char* text = "HHHamburgefonts iii";
            size_t len = strlen( text );
            SkScalar x0 = SkIntToScalar( 10 );
            SkScalar x1 = SkIntToScalar( 310 );
            SkScalar y = SkIntToScalar( 20 );

            SkFont font;
            for ( int i = 0; i < 20; i++ )
            {
                font.setSize( textSize );
                textSize += delta;

                font.setEdging( SkFont::Edging::kAntiAlias );
                canvas->drawSimpleText( text, len, SkTextEncoding::kUTF8, x0, y, font, paint );
                font.setEdging( SkFont::Edging::kSubpixelAntiAlias );
                canvas->drawSimpleText( text, len, SkTextEncoding::kUTF8, x1, y, font, paint );

                y += font.getSpacing( );
            }
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

        Harlinn::Windows::ApplicationOptions applicationOptions;
        applicationOptions.Load( );
        Harlinn::Windows::Application application( applicationOptions );
        application.Start( );

        SkGraphics::Init( );

        SkiaLCDTextForm form;
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

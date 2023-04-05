// EWDX2D01Demo.cpp : Defines the entry point for the application.
//

#include "EWDX2D01Demo.h"

#include <HWApplication.h>
#include "HWForm.h"
#include "HWMenu.h"
#include "HCCDatetime.h"
#include "HWGraphics.h"
#include "HWDWrite.h"
#include "HWImaging.h"
#include "HWStdctrls.h"


using namespace Harlinn::Windows;

class MyForm : public Form
{
    Graphics::Factory7 factory_;
    DirectWrite::Factory writeFactory_;
    DirectWrite::TextFormat textFormat_;
    DirectWrite::TextLayout textLayout_;
    Graphics::ControlRenderTarget renderTarget_;
    Graphics::SolidColorBrush blackBrush_;
    DirectWrite::Typography typography_;
    Graphics::LinearGradientBrush backgroundBrush_;

    std::wstring text_;
    std::wstring titleText_;
    std::unique_ptr<Timer> timer_;
    bool showingTime_;
public:
    typedef Form Base;

    MyForm( );
protected:
    virtual void DoOnInitialize( );
    virtual void DoOnShown( );
    virtual void DoOnDestroy( Message& message );
    virtual void DoOnDisplayChange( Message& message );
    virtual void DoOnPaint( Message& message );
    virtual void DoOnSize( Message& message );
private:
    void InitializeMenuBar( );
};


MyForm::MyForm( )
    : Base( ),
      factory_( D2D1_FACTORY_TYPE_SINGLE_THREADED ),
      writeFactory_( DWRITE_FACTORY_TYPE_SHARED ),
      titleText_( L"Windows Development in C++ - working with menus" ),
      showingTime_( 0 )
{
    text_ = titleText_;
    timer_ = std::make_unique<Timer>( );

    timer_->OnTick.connect( [&]( Timer* sender )
    {
        if ( showingTime_ )
        {
            DateTime now = DateTime::Now( );
            if ( now.IsDaylightSavingTime( ) )
            {
                text_ = now.ToString( ) + L" Daylight saving time";
            }
            else
            {
                text_ = now.ToString( ) + L" Standard time";
            }
            InvalidateRect( );
        }
    } );

    auto interval = TimeSpan::FromMilliseconds( 500 );
    timer_->SetInterval( interval );
    timer_->SetEnabled( );

}

void MyForm::DoOnInitialize( )
{
    SetText( titleText_ ); // 
    textFormat_ = writeFactory_.CreateTextFormat( L"Gabriola", 72 );
    textFormat_.SetTextAlignment( DWRITE_TEXT_ALIGNMENT_CENTER );
    textFormat_.SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_CENTER );

    typography_ = writeFactory_.CreateTypography( );

    DWRITE_FONT_FEATURE fontFeature = { DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_7,1 };

    typography_.AddFontFeature( fontFeature );

    InitializeMenuBar( );
}


void MyForm::InitializeMenuBar( )
{
    auto menuBar = std::make_unique<MenuBar>( );

    auto fileSubMenu = menuBar->AddSubMenu( L"&File" );
    auto editSubMenu = menuBar->AddSubMenu( L"&Edit" );
    auto viewSubMenu = menuBar->AddSubMenu( L"&View" );

    fileSubMenu->AddMenuItem( L"&New", 
        [&]( MenuItem* ) 
    { 
        showingTime_ = false; 
        text_ = L"New selected"; 
        InvalidateRect( ); 
    } );

    fileSubMenu->AddMenuItem( L"&Open",
        [&]( MenuItem* ) 
    { 
        showingTime_ = false; 
        text_ = L"Open selected"; 
        InvalidateRect( ); 
    } );

    fileSubMenu->AddMenuItem( L"&Save", 
        [&]( MenuItem* ) 
    { 
        showingTime_ = false; 
        text_ = L"Save selected"; 
        InvalidateRect( ); 
    } );

    fileSubMenu->AddSeparator( );
    fileSubMenu->AddMenuItem( L"E&xit", 
        [&]( MenuItem* ) 
    { 
        Close( ); 
    } );

    editSubMenu->AddMenuItem( L"Cu&t", 
        [&]( MenuItem* ) 
    { 
        showingTime_ = false; 
        text_ = L"Cut selected"; 
        InvalidateRect( ); 
    } );
    editSubMenu->AddMenuItem( L"&Copy", 
        [&]( MenuItem* ) 
    { 
        showingTime_ = false; 
        text_ = L"Copy selected"; 
        InvalidateRect( ); 
    } );

    auto editPasteMenuItem = editSubMenu->AddMenuItem( L"&Paste",
        [&]( MenuItem* ) 
    { 
        showingTime_ = false; 
        text_ = L"Paste selected"; 
        InvalidateRect( ); 
    } );


    viewSubMenu->AddMenuItem( L"&Time", [&]( MenuItem* )
    {
        showingTime_ = true;
        DateTime now = DateTime::Now( );
        if ( now.IsDaylightSavingTime( ) )
        {
            text_ = now.ToString( ) + L" Daylight saving time";
        }
        else
        {
            text_ = now.ToString( ) + L" Standard time";
        }
        InvalidateRect( );
    } );

    SetMenu( std::move(menuBar) );
}



void MyForm::DoOnShown( )
{
    Base::DoOnShown( );

    renderTarget_ = factory_.CreateControlRenderTarget( *this );
    blackBrush_ = renderTarget_.CreateSolidColorBrush( D2D1::ColorF( D2D1::ColorF::Black ) );

    D2D1_GRADIENT_STOP gradientStops[2];
    gradientStops[0].color = D2D1::ColorF( D2D1::ColorF::White, 1 );
    gradientStops[0].position = 0.0f;
    gradientStops[1].color = D2D1::ColorF( D2D1::ColorF::DeepSkyBlue, 1 );
    gradientStops[1].position = 1.0f;


    Graphics::GradientStopCollection gradientStopCollection = renderTarget_.CreateGradientStopCollection( gradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_MIRROR );


    backgroundBrush_ = renderTarget_.CreateLinearGradientBrush( D2D1::LinearGradientBrushProperties( { .0f, .0f }, { 150.0f, 150.0f } ), gradientStopCollection );


}
void MyForm::DoOnDestroy( Message& message )
{
    Base::DoOnDestroy( message );
    blackBrush_.ResetPtr( );
    renderTarget_.ResetPtr( );
}

void MyForm::DoOnDisplayChange( Message& message )
{
    InvalidateRect( );
}

void MyForm::DoOnPaint( Message& message )
{
    Base::DoOnPaint( message );
    ValidateRect( );
    

    renderTarget_.BeginDraw( );

    RECT clientRectangle = GetClientRect( );
    auto dpiScale = static_cast<float>( GetDotsPerInch( ) )/96.0f;
    Graphics::RectangleF layoutRect( clientRectangle );
    layoutRect /= dpiScale;

    renderTarget_.SetTransform( D2D1::IdentityMatrix( ) );
    renderTarget_.Clear( D2D1::ColorF( D2D1::ColorF::White ) );

    renderTarget_.FillRectangle( layoutRect, backgroundBrush_ );

    Graphics::PointF  origin = layoutRect.LeftTop( );


    textLayout_ = writeFactory_.CreateTextLayout( text_.c_str( ), UINT( text_.length( ) ), textFormat_, 
        layoutRect.Right() - layoutRect.Left(), layoutRect.Bottom() - layoutRect.Top() );

    DWRITE_TEXT_RANGE textRange = { 0, UINT( text_.length( ) ) };

    textLayout_.SetTypography( typography_, textRange );

    auto found = text_.find( L"C++" );

    if ( found != std::wstring::npos )
    {
        textRange.startPosition = UINT( found );
        textRange.length = 3;
        textLayout_.SetFontSize( 144.0, textRange );
    }


    renderTarget_.DrawTextLayout( origin, textLayout_, blackBrush_ );

    renderTarget_.EndDraw( );
}

void MyForm::DoOnSize( Message& message )
{
    Base::DoOnSize( message );
    if ( renderTarget_ )
    {
        D2D1_SIZE_U size;
        size.width = LOWORD( message.lParam );
        size.height = HIWORD( message.lParam );
        renderTarget_.Resize( size );
    }
}





int APIENTRY wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{

    try
    {
        Harlinn::Windows::ApplicationOptions applicationOptions;
        applicationOptions.Load( );
        Harlinn::Windows::Application application( applicationOptions );
        application.Start( );

        UNREFERENCED_PARAMETER( hPrevInstance );
        UNREFERENCED_PARAMETER( lpCmdLine );
        SetThreadDpiAwarenessContext( DPI_AWARENESS_CONTEXT_SYSTEM_AWARE );
        
        MyForm form;
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



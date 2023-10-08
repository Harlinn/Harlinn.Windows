// HWSkiaSVGView.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "HWSkiaSVGView.h"

#include <HWFileDialog.h>


class SkiaSVGViewForm : public Harlinn::Windows::Form
{
public:
    using Base = Harlinn::Windows::Form;
private:
    std::unique_ptr<SkiaSVGView> control_;

public:
    SkiaSVGViewForm( )
        : Base( )
    {
        SetText( L"SVG View" );
        control_ = Harlinn::Windows::make_control<SkiaSVGView>( this );
    }

protected:

    void DoOnSize( Harlinn::Windows::Message& message )
    {
        if ( control_ )
        {
            Harlinn::Windows::Rectangle clientRect = GetClientRect( );
            control_->MoveWindow( 0, 0, clientRect.Width( ), clientRect.Height( ) );
        }
    }

    void OpenFile( )
    {
        auto fileOpenDialog = Harlinn::Windows::FileOpenDialog::Create( );
        HWND windowHandle = GetHandle( );
        if ( fileOpenDialog->Show( ) )
        {
            auto item = fileOpenDialog->GetResult( );
            auto fileName = item.GetDisplayName( SIGDN_FILESYSPATH );
            control_->LoadFromFile( fileName );
        }
        
    }

    void DoOnInitialize( )
    {
        auto menuBar = std::make_unique<MenuBar>( );

        auto fileSubMenu = menuBar->AddSubMenu( L"&File" );

        fileSubMenu->AddMenuItem( L"&Open",
            [&]( MenuItem* )
        {
            OpenFile( );
            InvalidateRect( );
        } );

        SetMenu( std::move( menuBar ) );
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

        SkiaSVGViewForm form;
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

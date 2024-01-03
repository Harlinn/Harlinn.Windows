/*
   Copyright 2024 Espen Harlinn

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

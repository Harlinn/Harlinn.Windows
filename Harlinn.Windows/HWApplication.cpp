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

#include "pch.h"
#include <HWApplication.h>

#pragma comment(lib,"Comctl32.lib")


namespace Harlinn::Windows
{
    // ------------------------------------------------------------------------
    // MessageLoop
    // ------------------------------------------------------------------------
    MessageLoop::MessageLoop( ) = default;

    MessageLoop::~MessageLoop( ) = default;

    int MessageLoop::Run( )
    {
        Message message;
        while ( this->GetMessage( message ) )
        {
            this->TranslateMessage( message );
            this->DispatchMessage( message );
        }
        return (int)message.wParam;
    }

    int MessageLoop::GetMessage( Message& message )
    {
        int result = ::GetMessage( &message, 0, 0, 0 );
        return result;
    }
    int MessageLoop::TranslateMessage( Message& message )
    {
        int result = ::TranslateMessage( &message );
        return result;
    }
    Message::Result MessageLoop::DispatchMessage( const Message& message )
    {
        Message::Result result = static_cast<Message::Result>( ::DispatchMessage( &message ) );
        return result;
    }


    // ------------------------------------------------------------------------
    // Application
    // ------------------------------------------------------------------------


    Application::Application( const std::shared_ptr<Windows::ApplicationOptions>& options, COINIT comInitalizationFlags )
        : Base( options )
    {
        HRESULT hr = CoInitializeEx(0, comInitalizationFlags );
        CheckHRESULT( hr );

        INITCOMMONCONTROLSEX icex = { 0, };
        icex.dwSize = sizeof( INITCOMMONCONTROLSEX );
        icex.dwICC = 0x0000FFFF;

        InitCommonControlsEx( &icex );

    }

    Application::Application( )
        : Application( Windows::ApplicationOptions::LoadFromFile<Windows::ApplicationOptions>( ) )
    {
    }

    Application::~Application( )
    {
        CoUninitialize( );
    }

    void Application::AddControl( HWND hWnd, Control* control )
    {
        auto it = controls_.find( hWnd );
        if ( it == controls_.end( ) )
        {
            controls_.emplace( hWnd, control );
        }
    }

    void Application::RemoveControl( HWND hWnd )
    {
        controls_.erase( hWnd );
    }

    Control* Application::GetControl( HWND hWnd )
    {
        auto it = controls_.find( hWnd );
        if ( it == controls_.end( ) )
        {
            auto result = ( *it ).second;
            return result;
        }
        return nullptr;
    }



    int Application::Run( Form& mainform )
    {

        MessageLoop messageLoop;
        int result = this->Run( mainform, messageLoop );
        return result;
    }

    int Application::Run( const std::unique_ptr<Form>& mainform )
    {
        return this->Run( *mainform );
    }


    int Application::Run( Form& mainform, MessageLoop& messageLoop )
    {
        mainform.OnDestroy.connect( []( Control* sender, Windows::Message& message )
        {
            ::PostQuitMessage( -1 );
        } );


        mainform.Show( );

        int result = messageLoop.Run( );
        return result;
    }


    const WindowClasses& Application::GetWindowClasses( ) const
    {
        return windowClasses_;
    }

    WindowClasses& Application::GetWindowClasses( )
    {
        return windowClasses_;
    }

    WindowClass* Application::GetWindowClass( const WideString& className )
    {
        auto& application = Application::Instance( );
        auto& windowClasses = application.GetWindowClasses( );
        auto result = windowClasses.GetWindowClass( className );
        return result;
    }
    WindowClass* Application::GetWindowClass( const wchar_t* className )
    {
        if ( className && className[0] )
        {
            WideString clsName( className );
            return GetWindowClass( clsName );
        }
        return nullptr;
    }

}
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
    Application* Application::currentApplication_ = nullptr;


    Application::Application( const Windows::ApplicationOptions& options )
        : Base( options )
    {
        HRESULT hr = CoInitializeEx( 0, COINIT_MULTITHREADED);
        //HRESULT hr = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
        CheckHRESULT( hr );

        currentApplication_ = this;
        INITCOMMONCONTROLSEX icex = { 0, };
        icex.dwSize = sizeof( INITCOMMONCONTROLSEX );
        icex.dwICC = 0x0000FFFF;

        InitCommonControlsEx( &icex );

    }

    Application::~Application( )
    {
        currentApplication_ = nullptr;
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


    Application* Application::Current( )
    {
        return currentApplication_;
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
        auto application = Application::Current( );
        if ( application )
        {
            auto& windowClasses = application->GetWindowClasses( );
            auto result = windowClasses.GetWindowClass( className );
            return result;
        }
        return nullptr;
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
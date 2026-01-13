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

#include "pch.h"
#include <HWForm.h>
#include <HWApplication.h>

namespace Harlinn::Windows
{
    // --------------------------------------------------------------------
    // FormWindowClass
    // --------------------------------------------------------------------
    class FormWindowClass : public WindowClass
    {
    public:
        static WideString ClassName;

        FormWindowClass( );
    };

    WideString FormWindowClass::ClassName = WideString( L"HarlinnWindowsFormWindowClassName" );

    typedef ControlMessageDispatcher<Form> FormMessageDispatcher;

    FormWindowClass::FormWindowClass( )
    {
        SetName( ClassName );
        WNDPROC procedure = FormMessageDispatcher::WndProc;
        SetProcedure( procedure );
        SetStyle( CS_HREDRAW | CS_VREDRAW );
        SetCursor( LoadCursor( nullptr, IDI_APPLICATION ) );

    }


    // --------------------------------------------------------------------
    // Form
    // --------------------------------------------------------------------

    Form& Form::Close( )
    {
        SendMessage( WM_CLOSE );
        return *this;
    }

    WindowClass* Form::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( FormWindowClass::ClassName );
        if ( !windowClass )
        {
            auto newWindowClass = std::make_unique<FormWindowClass>( );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }

    DWORD Form::GetStyle( ) const
    {
        auto result = Base::GetStyle( );
        result &= ~( WS_CHILD | WS_TABSTOP | WS_VISIBLE );
        result |= WS_OVERLAPPEDWINDOW;
        return result;
    }

    Form& Form::DrawMenuBar( )
    {
        if ( ::DrawMenuBar( GetHandle( ) ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return *this;
    }

    Form& Form::SetMenu( std::unique_ptr<MenuBar>&& menuBar )
    {

        menuBar_ = std::move( menuBar );
        if ( IsValid( ) )
        {
            HMENU hMenu = menuBar_->Handle();
            if ( ::SetMenu( GetHandle( ), hMenu ) == FALSE )
            {
                ThrowLastOSError( );
            }

            DrawMenuBar( );
        }
        return *this;
    }


    void Form::HandleMessage( Message& message )
    {
        switch ( message.message )
        {
            case WM_ACTIVATE:
                this->DoOnActivate( message );
                break;
            case WM_ACTIVATEAPP:
                this->DoOnActivateApp( message );
                break;
            case WM_DEVMODECHANGE:
                this->DoOnDevModeChange( message );
                break;
            case WM_ENDSESSION:
                this->DoOnEndSession( message );
                break;
            case WM_FONTCHANGE:
                this->DoOnFontChange( message );
                break;
            case WM_GETMINMAXINFO:
                this->DoOnGetMinMaxInfo( message );
                break;
            case WM_ICONERASEBKGND:
                this->DoOnIconEraseBackground( message );
                break;
            case WM_MOUSEACTIVATE:
                this->DoOnMouseActivate( message );
                break;
            case WM_PAINTICON:
                this->DoOnPaintIcon( message );
                break;
            case WM_POWERBROADCAST:
                this->DoOnPowerBroadcast( message );
                break;
            case WM_QUERYDRAGICON:
                this->DoOnQueryDragIcon( message );
                break;
            case WM_QUERYENDSESSION:
                this->DoOnQueryEndSession( message );
                break;
            case WM_QUERYOPEN:
                this->DoOnQueryOpen( message );
                break;
            case WM_SETTINGCHANGE:
                this->DoOnSettingChange( message );
                break;
            case WM_TIMECHANGE:
                this->DoOnTimeChange( message );
                break;
            default:
                Base::HandleMessage( message );
                break;
        }
    }

    void Form::DoOnHandleCreated( )
    {
        Base::DoOnHandleCreated( );
        if ( menuBar_ )
        {
            HMENU hMenu = menuBar_->Handle( );
            if ( ::SetMenu( GetHandle( ), hMenu ) == FALSE )
            {
                ThrowLastOSError( );
            }
            DrawMenuBar( );
        }

    }


    void Form::DoOnActivate( Message& message )
    {
        OnActivate( this, message );
    }

    void Form::DoOnActivateApp( Message& message )
    {
        OnActivateApp( this, message );
    }

    void Form::DoOnDevModeChange( Message& message )
    {
        OnDevModeChange( this, message );
    }

    void Form::DoOnEndSession( Message& message )
    {
        OnEndSession( this, message );
    }

    void Form::DoOnFontChange( Message& message )
    {
        OnFontChange( this, message );
    }

    void Form::DoOnGetMinMaxInfo( Message& message )
    {
        OnGetMinMaxInfo( this, message );
    }

    void Form::DoOnIconEraseBackground( Message& message )
    {
        OnIconEraseBackground( this, message );
    }

    void Form::DoOnMouseActivate( Message& message )
    {
        OnMouseActivate( this, message );
    }

    void Form::DoOnPaintIcon( Message& message )
    {
        OnPaintIcon( this, message );
    }

    void Form::DoOnPowerBroadcast( Message& message )
    {
        OnPowerBroadcast( this, message );
    }

    void Form::DoOnQueryDragIcon( Message& message )
    {
        OnQueryDragIcon( this, message );
    }

    void Form::DoOnQueryEndSession( Message& message )
    {
        OnQueryEndSession( this, message );
    }

    void Form::DoOnQueryOpen( Message& message )
    {
        OnQueryOpen( this, message );
    }

    void Form::DoOnSettingChange( Message& message )
    {
        OnSettingChange( this, message );
    }

    void Form::DoOnShowWindow( Message& message )
    {
        if ( !shown_ )
        {
            Rectangle rect = this->GetClientRect( );

            Message wmSize = message;
            wmSize.message = WM_SIZE;
            wmSize.wParam = 0;
            wmSize.lParam = ( rect.Height( ) << 16 ) | rect.Width( );
            this->HandleMessage( wmSize );
            shown_ = true;
            this->DoOnShown( );
        }
        Base::DoOnShowWindow( message );
    }

    void Form::DoOnShown( )
    {
        OnShown( this );
    }

    void Form::DoOnTimeChange( Message& message )
    {
        OnTimeChange( this, message );
    }
}
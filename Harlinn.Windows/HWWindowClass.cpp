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
#include <HWWindowClass.h>
#include <HCCException.h>
#include <HWHandles.h>

namespace Harlinn::Windows
{
    WideString WindowClass::animate_class_name = WideString( ANIMATE_CLASSW );
    WideString WindowClass::datetimepick_class_name = WideString( DATETIMEPICK_CLASSW );
    WideString WindowClass::hotkey_class_name = WideString( HOTKEY_CLASSW );
    WideString WindowClass::link_class_name = WideString( WC_LINK );
    WideString WindowClass::monthcal_class_name = WideString( MONTHCAL_CLASSW );
    WideString WindowClass::nativefontctl_class_name = WideString( WC_NATIVEFONTCTLW );
    WideString WindowClass::progress_class_name = WideString( PROGRESS_CLASSW );
    WideString WindowClass::rebar_class_name = WideString( REBARCLASSNAMEW );
    WideString WindowClass::status_class_name = WideString( STATUSCLASSNAMEW );
    WideString WindowClass::toolbar_class_name = WideString( TOOLBARCLASSNAMEW );
    WideString WindowClass::tooltips_class_name = WideString( TOOLTIPS_CLASSW );
    WideString WindowClass::trackbar_class_name = WideString( TRACKBAR_CLASSW );
    WideString WindowClass::updown_class_name = WideString( UPDOWN_CLASSW );
    WideString WindowClass::button_class_name = WideString( WC_BUTTONW );
    WideString WindowClass::combobox_class_name = WideString( WC_COMBOBOXEXW );
    WideString WindowClass::edit_class_name = WideString( WC_EDITW );
    WideString WindowClass::header_class_name = WideString( WC_HEADERW );
    WideString WindowClass::listbox_class_name = WideString( WC_LISTBOXW );
    WideString WindowClass::ipaddress_class_name = WideString( WC_IPADDRESSW );
    WideString WindowClass::listview_class_name = WideString( WC_LISTVIEWW );
    WideString WindowClass::pagescroller_class_name = WideString( WC_PAGESCROLLERW );
    WideString WindowClass::scrollbar_class_name = WideString( WC_SCROLLBARW );
    WideString WindowClass::static_class_name = WideString( WC_STATICW );
    WideString WindowClass::tabcontrol_class_name = WideString( WC_TABCONTROLW );
    WideString WindowClass::treeview_class_name = WideString( WC_TREEVIEWW );



    WindowClass::WindowClass( )
        : style_( 0 ), procedure_( 0 ), classExtraBytes_( 0 ), windowExtraBytes_( 0 ), moduleHandle_( 0 ),
        icon_( 0 ), cursor_( (HCURSOR)CursorHandle::Normal.Value()), backgroundBrush_( 0 ), smallIcon_( 0 )
    {
    }

    WindowClass::WindowClass( const WNDCLASSEXW& wndClass )
        : style_( wndClass.style ), procedure_( wndClass.lpfnWndProc ), classExtraBytes_( wndClass.cbClsExtra ),
        windowExtraBytes_( wndClass.cbWndExtra ), moduleHandle_( wndClass.hInstance ),
        icon_( wndClass.hIcon ), cursor_( wndClass.hCursor ), backgroundBrush_( wndClass.hbrBackground ), smallIcon_( wndClass.hIconSm )
    {
        if ( wndClass.lpszClassName )
        {
            name_ = WideString( wndClass.lpszClassName );
        }
        if ( wndClass.lpszMenuName )
        {
            menuName_ = WideString( wndClass.lpszMenuName );
        }
    }

    WindowClass::WindowClass( const WindowClass& wndClass ) = default;


    WindowClass::~WindowClass( )
    {

    }


    WNDCLASSEXW WindowClass::AsWNDCLASSEX( ) const
    {
        WNDCLASSEXW result = { 0, };

        result.cbSize = sizeof( WNDCLASSEXW );
        result.style = this->Style( );
        result.lpfnWndProc = this->Procedure( );
        result.cbClsExtra = this->ClassExtraBytes( );
        result.cbWndExtra = this->WindowExtraBytes( );
        result.hInstance = this->ModuleHandle( );
        result.hIcon = this->Icon( );
        result.hCursor = this->Cursor( );
        result.hbrBackground = this->BackgroundBrush( );
        if ( menuName_.length( ) )
        {
            result.lpszMenuName = menuName_.c_str( );
        }
        else
        {
            result.lpszMenuName = nullptr;
        }
        if ( name_.length( ) )
        {
            result.lpszClassName = name_.c_str( );
        }
        else
        {
            result.lpszClassName = nullptr;
        }
        result.hIconSm = this->SmallIcon( );

        return result;
    }


    const WideString& WindowClass::Name( ) const
    {
        return name_;
    }

    WindowClass& WindowClass::SetName( const WideString& name )
    {
        name_ = name;
        return *this;
    }


    const WideString& WindowClass::MenuName( ) const
    {
        return menuName_;
    }

    WindowClass& WindowClass::SetMenuName( const WideString& menuName )
    {
        menuName_ = menuName;
        return *this;
    }


    UINT WindowClass::Style( ) const
    {
        return style_;
    }

    WindowClass& WindowClass::SetStyle( UINT style )
    {
        style_ = style;
        return *this;
    }


    WNDPROC WindowClass::Procedure( ) const
    {
        return procedure_;
    }

    WindowClass& WindowClass::SetProcedure( WNDPROC procedure )
    {
        procedure_ = procedure;
        return *this;
    }


    int WindowClass::ClassExtraBytes( ) const
    {
        return classExtraBytes_;
    }

    WindowClass& WindowClass::SetClassExtraBytes( int classExtraBytes )
    {
        classExtraBytes_ = classExtraBytes;
        return *this;
    }


    int WindowClass::WindowExtraBytes( ) const
    {
        return windowExtraBytes_;
    }

    WindowClass& WindowClass::SetWindowExtraBytes( int windowExtraBytes )
    {
        windowExtraBytes_ = windowExtraBytes;
        return *this;
    }


    HINSTANCE WindowClass::ModuleHandle( ) const
    {
        return moduleHandle_;
    }

    WindowClass& WindowClass::SetModuleHandle( HINSTANCE moduleHandle )
    {
        moduleHandle_ = moduleHandle;
        return *this;
    }


    HICON WindowClass::Icon( ) const
    {
        return icon_;
    }

    WindowClass& WindowClass::SetIcon( HICON icon )
    {
        icon_ = icon;
        return *this;
    }


    HCURSOR WindowClass::Cursor( ) const
    {
        return cursor_;
    }

    WindowClass& WindowClass::SetCursor( HCURSOR cursor )
    {
        cursor_ = cursor;
        return *this;
    }


    HBRUSH WindowClass::BackgroundBrush( ) const
    {
        return backgroundBrush_;
    }

    WindowClass& WindowClass::SetBackgroundBrush( HBRUSH backgroundBrush )
    {
        backgroundBrush_ = backgroundBrush;
        return *this;
    }


    HICON WindowClass::SmallIcon( ) const
    {
        return smallIcon_;
    }

    WindowClass& WindowClass::SetSmallIcon( HICON smallIcon )
    {
        smallIcon_ = smallIcon;
        return *this;
    }




    WindowClasses::WindowClasses( )
    {
        LoadStandardClasses( );
    }

    WindowClasses::~WindowClasses( )
    {

    }



    void WindowClasses::LoadStandardClasses( )
    {
        LoadStandardClass( WindowClass::animate_class_name );
        LoadStandardClass( WindowClass::datetimepick_class_name );
        LoadStandardClass( WindowClass::hotkey_class_name );
        LoadStandardClass( WindowClass::link_class_name );
        LoadStandardClass( WindowClass::monthcal_class_name );
        LoadStandardClass( WindowClass::nativefontctl_class_name );
        LoadStandardClass( WindowClass::progress_class_name );
        LoadStandardClass( WindowClass::rebar_class_name );
        LoadStandardClass( WindowClass::status_class_name );
        LoadStandardClass( WindowClass::toolbar_class_name );
        LoadStandardClass( WindowClass::tooltips_class_name );
        LoadStandardClass( WindowClass::trackbar_class_name );
        LoadStandardClass( WindowClass::updown_class_name );
        LoadStandardClass( WindowClass::button_class_name );
        LoadStandardClass( WindowClass::combobox_class_name );
        LoadStandardClass( WindowClass::edit_class_name );
        LoadStandardClass( WindowClass::header_class_name );
        LoadStandardClass( WindowClass::listbox_class_name );
        LoadStandardClass( WindowClass::ipaddress_class_name );
        LoadStandardClass( WindowClass::listview_class_name );
        LoadStandardClass( WindowClass::pagescroller_class_name );
        LoadStandardClass( WindowClass::scrollbar_class_name );
        LoadStandardClass( WindowClass::static_class_name );
        LoadStandardClass( WindowClass::tabcontrol_class_name );
        LoadStandardClass( WindowClass::treeview_class_name );

    }


    void WindowClasses::LoadStandardClass( const WideString& className )
    {
        auto cit = map_.find( className );
        if ( cit == map_.end( ) )
        {
            auto windowClass = GetClassInfo( className );
            map_.insert( map_t::value_type( className, std::move( windowClass ) ) );
        }
    }


    std::unique_ptr<WindowClass> WindowClasses::GetClassInfo( const WideString& className )
    {
        auto result = GetClassInfo( (HINSTANCE)0, className );
        return result;
    }

    std::unique_ptr<WindowClass> WindowClasses::GetClassInfo( HINSTANCE hInstance, const WideString& className )
    {
        WNDCLASSEXW wndCls = { 0, };
        GetClassInfoExW( hInstance, className.c_str( ), &wndCls );
        auto result = std::make_unique<WindowClass>( wndCls );
        return result;
    }

    WindowClass* WindowClasses::GetWindowClass( const WideString& className ) const
    {
        auto it = map_.find( className );
        if ( it != map_.end( ) )
        {
            auto result = it->second.get();
            return result;
        }
        return nullptr;
    }

    bool WindowClasses::Register( std::unique_ptr<WindowClass>&& windowClass )
    {
        if ( !windowClass )
        {
            Common::Core::ThrowPointerIsNULL( );
        }

        auto name = windowClass->Name( );
        if ( name.length( ) )
        {
            auto existingWindowClass = GetWindowClass( name );
            if ( !existingWindowClass )
            {
                WNDCLASSEXW wndCls = windowClass->AsWNDCLASSEX( );
                ATOM atom = ::RegisterClassExW( &wndCls );
                if ( !atom )
                {
                    Common::Core::ThrowLastOSError( );
                }
                map_.emplace( name, std::move( windowClass ) );
                return true;
            }
        }
        return false;
    }


}


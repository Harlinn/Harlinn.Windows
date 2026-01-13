#pragma once
#ifndef __HWWINDOWCLASS_H__
#define __HWWINDOWCLASS_H__

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


#include <HWDef.h>

namespace Harlinn::Windows
{

    class WindowClass
    {
        WideString name_;
        WideString menuName_;

        UINT style_;
        WNDPROC procedure_;
        int classExtraBytes_;
        int windowExtraBytes_;
        HINSTANCE moduleHandle_;
        HICON icon_;
        HCURSOR cursor_;
        HBRUSH backgroundBrush_;
        HICON smallIcon_;
    public:
        static WideString HW_EXPORT animate_class_name;
        static WideString HW_EXPORT datetimepick_class_name;
        static WideString HW_EXPORT hotkey_class_name;
        static WideString HW_EXPORT link_class_name;
        static WideString HW_EXPORT monthcal_class_name;
        static WideString HW_EXPORT nativefontctl_class_name;
        static WideString HW_EXPORT progress_class_name;
        static WideString HW_EXPORT rebar_class_name;
        static WideString HW_EXPORT status_class_name;
        static WideString HW_EXPORT toolbar_class_name;
        static WideString HW_EXPORT tooltips_class_name;
        static WideString HW_EXPORT trackbar_class_name;
        static WideString HW_EXPORT updown_class_name;
        static WideString HW_EXPORT button_class_name;
        static WideString HW_EXPORT combobox_class_name;
        static WideString HW_EXPORT edit_class_name;
        static WideString HW_EXPORT header_class_name;
        static WideString HW_EXPORT listbox_class_name;
        static WideString HW_EXPORT ipaddress_class_name;
        static WideString HW_EXPORT listview_class_name;
        static WideString HW_EXPORT pagescroller_class_name;
        static WideString HW_EXPORT scrollbar_class_name;
        static WideString HW_EXPORT static_class_name;
        static WideString HW_EXPORT tabcontrol_class_name;
        static WideString HW_EXPORT treeview_class_name;


        HW_EXPORT WindowClass( );
        HW_EXPORT WindowClass( const WNDCLASSEXW& wndClass );
        HW_EXPORT WindowClass( const WindowClass& wndClass );
        HW_EXPORT ~WindowClass( );

        HW_EXPORT WNDCLASSEXW AsWNDCLASSEX( ) const;

        HW_EXPORT const WideString& Name( ) const;
        HW_EXPORT WindowClass& SetName( const WideString& name );

        HW_EXPORT const WideString& MenuName( ) const;
        HW_EXPORT WindowClass& SetMenuName( const WideString& menuName );

        HW_EXPORT UINT Style( ) const;
        HW_EXPORT WindowClass& SetStyle( UINT style );

        HW_EXPORT WNDPROC Procedure( ) const;
        HW_EXPORT WindowClass& SetProcedure( WNDPROC procedure );

        HW_EXPORT int ClassExtraBytes( ) const;
        HW_EXPORT WindowClass& SetClassExtraBytes( int classExtraBytes );

        HW_EXPORT int WindowExtraBytes( ) const;
        HW_EXPORT WindowClass& SetWindowExtraBytes( int windowExtraBytes );

        HW_EXPORT HINSTANCE ModuleHandle( ) const;
        HW_EXPORT WindowClass& SetModuleHandle( HINSTANCE moduleHandle );

        HW_EXPORT HICON Icon( ) const;
        HW_EXPORT WindowClass& SetIcon( HICON icon );

        HW_EXPORT HCURSOR Cursor( ) const;
        HW_EXPORT WindowClass& SetCursor( HCURSOR cursor );

        HW_EXPORT HBRUSH BackgroundBrush( ) const;
        HW_EXPORT WindowClass& SetBackgroundBrush( HBRUSH backgroundBrush );

        HW_EXPORT HICON SmallIcon( ) const;
        HW_EXPORT WindowClass& SetSmallIcon( HICON smallIcon );

    };

    class WindowClasses
    {
    public:

        typedef std::unordered_map<WideString, std::unique_ptr<WindowClass> > map_t;
    private:
        map_t map_;

        void LoadStandardClasses( );
        void LoadStandardClass( const WideString& className );
    public:
        HW_EXPORT WindowClasses( );
        HW_EXPORT ~WindowClasses( );

        static HW_EXPORT std::unique_ptr<WindowClass> GetClassInfo( const WideString& className );
        static HW_EXPORT std::unique_ptr<WindowClass> GetClassInfo( HINSTANCE hInstance, const WideString& className );


        HW_EXPORT WindowClass* GetWindowClass( const WideString& className ) const;
        HW_EXPORT bool Register( std::unique_ptr<WindowClass>&& windowClass );
    };


}


#endif

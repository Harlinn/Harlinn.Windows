#pragma once
#ifndef __HWWINDOWCLASS_H__
#define __HWWINDOWCLASS_H__

#include <HWDef.h>

namespace Harlinn::Windows
{

    class WindowClass
    {
        std::wstring name_;
        std::wstring menuName_;

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
        static std::wstring HW_EXPORT animate_class_name;
        static std::wstring HW_EXPORT datetimepick_class_name;
        static std::wstring HW_EXPORT hotkey_class_name;
        static std::wstring HW_EXPORT link_class_name;
        static std::wstring HW_EXPORT monthcal_class_name;
        static std::wstring HW_EXPORT nativefontctl_class_name;
        static std::wstring HW_EXPORT progress_class_name;
        static std::wstring HW_EXPORT rebar_class_name;
        static std::wstring HW_EXPORT status_class_name;
        static std::wstring HW_EXPORT toolbar_class_name;
        static std::wstring HW_EXPORT tooltips_class_name;
        static std::wstring HW_EXPORT trackbar_class_name;
        static std::wstring HW_EXPORT updown_class_name;
        static std::wstring HW_EXPORT button_class_name;
        static std::wstring HW_EXPORT combobox_class_name;
        static std::wstring HW_EXPORT edit_class_name;
        static std::wstring HW_EXPORT header_class_name;
        static std::wstring HW_EXPORT listbox_class_name;
        static std::wstring HW_EXPORT ipaddress_class_name;
        static std::wstring HW_EXPORT listview_class_name;
        static std::wstring HW_EXPORT pagescroller_class_name;
        static std::wstring HW_EXPORT scrollbar_class_name;
        static std::wstring HW_EXPORT static_class_name;
        static std::wstring HW_EXPORT tabcontrol_class_name;
        static std::wstring HW_EXPORT treeview_class_name;


        HW_EXPORT WindowClass( );
        HW_EXPORT WindowClass( const WNDCLASSEXW& wndClass );
        HW_EXPORT WindowClass( const WindowClass& wndClass );
        HW_EXPORT ~WindowClass( );

        HW_EXPORT WNDCLASSEXW AsWNDCLASSEX( ) const;

        HW_EXPORT const std::wstring& Name( ) const;
        HW_EXPORT WindowClass& SetName( const std::wstring& name );

        HW_EXPORT const std::wstring& MenuName( ) const;
        HW_EXPORT WindowClass& SetMenuName( const std::wstring& menuName );

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

        typedef std::unordered_map<std::wstring, std::unique_ptr<WindowClass> > map_t;
    private:
        map_t map_;

        void LoadStandardClasses( );
        void LoadStandardClass( const std::wstring& className );
    public:
        HW_EXPORT WindowClasses( );
        HW_EXPORT ~WindowClasses( );

        static HW_EXPORT std::unique_ptr<WindowClass> GetClassInfo( const std::wstring& className );
        static HW_EXPORT std::unique_ptr<WindowClass> GetClassInfo( HINSTANCE hInstance, const std::wstring& className );


        HW_EXPORT WindowClass* GetWindowClass( const std::wstring& className ) const;
        HW_EXPORT bool Register( std::unique_ptr<WindowClass>&& windowClass );
    };


}


#endif

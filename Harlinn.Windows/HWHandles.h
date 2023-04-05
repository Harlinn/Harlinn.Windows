#pragma once
#ifndef __HWHANDLES_H__
#define __HWHANDLES_H__

#include <HWDef.h>
#include <HCCException.h>
#include <HCCString.h>
#include <HCCHandle.h>
#include <HWCommon.h>


namespace Harlinn::Windows
{
    class Control;

    class ModuleHandle final : public Handle<ModuleHandle,HMODULE>
    {
    public:
        using Base = Handle<ModuleHandle, HMODULE>;

        constexpr ModuleHandle( ) noexcept
            : Base()
        {
        }

        explicit ModuleHandle( HMODULE hModule, bool closeHandle = true )
            : Base( hModule, closeHandle )
        {
        }

        ModuleHandle( const wchar_t* moduleName, DWORD flags = 0 )
        {
            CheckPointerNotNull( moduleName );
            HMODULE hModule = LoadLibraryExW( moduleName, nullptr, flags );
            if ( !hModule )
            {
                ThrowLastOSError( );
            }
            SetValue( hModule );
        }
        ModuleHandle( const std::wstring& moduleName, DWORD flags = 0 )
            : ModuleHandle( moduleName.c_str( ), flags )
        {
        }
        ModuleHandle( const char* moduleName, DWORD flags = 0 )
        {
            CheckPointerNotNull( moduleName );
            HMODULE hModule = LoadLibraryExA( moduleName, nullptr, flags );
            if ( !hModule )
            {
                ThrowLastOSError( );
            }
            SetValue( hModule );
        }
        ModuleHandle( const std::string& moduleName, DWORD flags = 0 )
            : ModuleHandle( moduleName.c_str( ), flags )
        {
        }

        void Close( ) noexcept
        {
            auto* derived = static_cast<DerivedType*>( this );
            if ( OwnsHandle( ) && derived->IsValid( ) )
            {
                FreeLibrary( value_ );
            }
        }


        std::wstring ModuleFileName( ) const
        {
            if ( IsValid() )
            {
                wchar_t buffer[512];
                std::wstring::size_type length = ::GetModuleFileNameW( Value( ), buffer, 512 );
                if ( length == 0 )
                {
                    ThrowLastOSError( );
                }
                std::wstring result( buffer, length );
                return result;
            }
            return std::wstring( );
        }


        static ModuleHandle Current( )
        {
            HMODULE hModule = GetModuleHandleW( nullptr );
            if ( !hModule )
            {
                ThrowLastOSError( );
            }
            ModuleHandle result( hModule, false );
            return result;
        }
    };

    class BitmapHandle final : public Handle<BitmapHandle, HBITMAP>
    {
        friend class DeviceContextHandle;
    public:
        

        using Base = Handle<BitmapHandle, HBITMAP>;
        constexpr BitmapHandle( ) noexcept
            : Base()
        {
        }

        constexpr explicit BitmapHandle( HBITMAP handle, bool ownsHandle = true ) noexcept
            : Base( handle, ownsHandle )
        {
        }

        BitmapHandle( int resourceId, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            HBITMAP hBitmap = static_cast<HBITMAP>( LoadImageW( 0, MAKEINTRESOURCE( resourceId ), IMAGE_BITMAP, width, height, flags ) );
            if ( !hBitmap )
            {
                ThrowLastOSError( );
            }
            SetValue( hBitmap, flags & LR_SHARED ? false : true );
        }

        BitmapHandle( const wchar_t* bitmapName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            CheckPointerNotNull( bitmapName );
            HBITMAP hBitmap = static_cast<HBITMAP>( LoadImageW( 0, bitmapName, IMAGE_BITMAP, width, height, flags ) );
            if ( !hBitmap )
            {
                ThrowLastOSError( );
            }
            SetValue( hBitmap, flags & LR_SHARED ? false : true );
        }
        BitmapHandle( const std::wstring& bitmapName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
            : BitmapHandle( bitmapName.c_str(), width, height, flags )
        {
        }
        BitmapHandle( const char* bitmapName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            CheckPointerNotNull( bitmapName );
            HBITMAP hBitmap = static_cast<HBITMAP>( LoadImageA( 0, bitmapName, IMAGE_BITMAP, width, height, flags ) );
            if ( !hBitmap )
            {
                ThrowLastOSError( );
            }
            SetValue( hBitmap, flags & LR_SHARED ? false : true );
        }
        BitmapHandle( const std::string& bitmapName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
            : BitmapHandle( bitmapName.c_str( ), width, height, flags )
        {
        }


        BitmapHandle( const ModuleHandle& module, int resourceId, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            auto hInstance = static_cast<HINSTANCE>( module.Value( ) );
            auto hBitmap = static_cast<HBITMAP>( LoadImageW( hInstance, MAKEINTRESOURCE( resourceId ), IMAGE_BITMAP, width, height, flags ) );
            if ( !hBitmap )
            {
                ThrowLastOSError( );
            }
            SetValue( hBitmap, flags & LR_SHARED ? false : true );
        }
        BitmapHandle( const ModuleHandle& module, const wchar_t* bitmapName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            auto hInstance = static_cast<HINSTANCE>( module.Value( ) );
            CheckPointerNotNull( bitmapName );
            auto hBitmap = static_cast<HBITMAP>( LoadImageW( hInstance, bitmapName, IMAGE_BITMAP, width, height, flags ) );
            if ( !hBitmap )
            {
                ThrowLastOSError( );
            }
            SetValue( hBitmap, flags & LR_SHARED ? false : true );
        }
        BitmapHandle( const ModuleHandle& module, const std::wstring& bitmapName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
            : BitmapHandle( module, bitmapName.c_str(), width, height, flags )
        {
        }

        void Close( ) noexcept
        {
            auto* derived = static_cast<DerivedType*>( this );
            if ( OwnsHandle( ) && derived->IsValid( ) )
            {
                DeleteObject( value_ );
            }
        }

        SIZE Size( ) const
        {
            SIZE result = { 0, };
            auto hBitmap = Value( );
            if ( hBitmap )
            {
                if ( GetBitmapDimensionEx( hBitmap, &result ) == FALSE )
                {
                    ThrowLastOSError( );
                }
            }
            return result;
        }


        HW_EXPORT static BitmapHandle LoadFromFile( const std::wstring& fileMame );
    };

    class ImageListHandle;
    class IconHandle : public Handle<IconHandle, HICON>
    {
    public:
        using Base = Handle<IconHandle, HICON>;

        HW_EXPORT static const IconHandle Question;
        HW_EXPORT static const IconHandle WinLogo;
        HW_EXPORT static const IconHandle Warning;
        HW_EXPORT static const IconHandle Error;
        HW_EXPORT static const IconHandle Information;
        HW_EXPORT static const IconHandle Shield;

        HW_EXPORT static const IconHandle Question16x16;
        HW_EXPORT static const IconHandle WinLogo16x16;
        HW_EXPORT static const IconHandle Warning16x16;
        HW_EXPORT static const IconHandle Error16x16;
        HW_EXPORT static const IconHandle Information16x16;
        HW_EXPORT static const IconHandle Shield16x16;

        HW_EXPORT static const IconHandle Question24x24;
        HW_EXPORT static const IconHandle WinLogo24x24;
        HW_EXPORT static const IconHandle Warning24x24;
        HW_EXPORT static const IconHandle Error24x24;
        HW_EXPORT static const IconHandle Information24x24;
        HW_EXPORT static const IconHandle Shield24x24;

        HW_EXPORT static const IconHandle Question32x32;
        HW_EXPORT static const IconHandle WinLogo32x32;
        HW_EXPORT static const IconHandle Warning32x32;
        HW_EXPORT static const IconHandle Error32x32;
        HW_EXPORT static const IconHandle Information32x32;
        HW_EXPORT static const IconHandle Shield32x32;

        constexpr IconHandle( ) noexcept
            : Base()
        {
        }


        constexpr explicit IconHandle( HICON hIcon, bool closeHandle = true )
            : Base( hIcon, closeHandle )
        {
        }

        IconHandle( int resourceId, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            auto hIcon = static_cast<HICON>(LoadImageW( 0, MAKEINTRESOURCE( resourceId ), IMAGE_ICON, width, height, flags ));
            if ( !hIcon )
            {
                ThrowLastOSError( );
            }
            SetValue( hIcon, flags & LR_SHARED ? false : true );
        }

        IconHandle( const wchar_t* iconName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            CheckPointerNotNull( iconName );
            auto hIcon = static_cast<HICON>( LoadImageW( 0, iconName, IMAGE_ICON, width, height, flags ) );
            if ( !hIcon )
            {
                ThrowLastOSError( );
            }
            SetValue( hIcon, flags & LR_SHARED ? false : true );
        }
        IconHandle( const std::wstring& iconName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
            : IconHandle( iconName.c_str( ), width, height, flags )
        {
        }

        IconHandle( const ModuleHandle& module, int resourceId, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            auto hInstance = static_cast<HINSTANCE>( module.Value( ) );
            auto hIcon = static_cast<HICON>( LoadImageW( hInstance, MAKEINTRESOURCE( resourceId ), IMAGE_ICON, width, height, flags ) );
            if ( !hIcon )
            {
                ThrowLastOSError( );
            }
            SetValue( hIcon, flags & LR_SHARED ? false : true );
        }
        IconHandle( const ModuleHandle& module, const wchar_t* iconName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            auto hInstance = static_cast<HINSTANCE>( module.Value( ) );
            CheckPointerNotNull( iconName );
            auto hIcon = static_cast<HICON>( LoadImageW( hInstance, iconName, IMAGE_ICON, width, height, flags ) );
            if ( !hIcon )
            {
                ThrowLastOSError( );
            }
            SetValue( hIcon, flags & LR_SHARED ? false : true );
        }
        IconHandle( const ModuleHandle& module, const std::wstring& iconName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
            : IconHandle( module, iconName.c_str(), width, height, flags )
        {
        }

        IconHandle( const ModuleHandle& module, const char* iconName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            auto hInstance = static_cast<HINSTANCE>( module.Value( ) );
            CheckPointerNotNull( iconName );
            auto hIcon = static_cast<HICON>( LoadImageA( hInstance, iconName, IMAGE_ICON, width, height, flags ) );
            if ( !hIcon )
            {
                ThrowLastOSError( );
            }
            SetValue( hIcon, flags & LR_SHARED ? false : true );
        }
        IconHandle( const ModuleHandle& module, const std::string& iconName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
            : IconHandle( module, iconName.c_str( ), width, height, flags )
        {
        }

        void Close( ) noexcept
        {
            auto* derived = static_cast<DerivedType*>( this );
            if ( OwnsHandle( ) && derived->IsValid( ) )
            {
                DeleteObject( value_ );
            }
        }

    };


    class CursorHandle : public Handle<CursorHandle,HCURSOR>
    {
    public:
        using Base = Handle<CursorHandle, HCURSOR>;

        HW_EXPORT static const CursorHandle Normal;
        HW_EXPORT static const CursorHandle IBeam;
        HW_EXPORT static const CursorHandle Wait;
        HW_EXPORT static const CursorHandle Cross;
        HW_EXPORT static const CursorHandle Up;
        HW_EXPORT static const CursorHandle Size;
        HW_EXPORT static const CursorHandle SizeNWSE;
        HW_EXPORT static const CursorHandle SizeNESW;
        HW_EXPORT static const CursorHandle SizeWE;
        HW_EXPORT static const CursorHandle SizeNS;
        HW_EXPORT static const CursorHandle No;
        HW_EXPORT static const CursorHandle Hand;
        HW_EXPORT static const CursorHandle AppStarting;

        constexpr CursorHandle( ) noexcept
            : Base( )
        {
        }

        constexpr explicit CursorHandle( HCURSOR hCursor, bool closeHandle = true )
            : Base( hCursor, closeHandle )
        {
        }


        CursorHandle( int resourceId, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            auto hCursor = static_cast<HCURSOR>(LoadImageW( 0, MAKEINTRESOURCE( resourceId ), IMAGE_CURSOR, width, height, flags ));
            if ( !hCursor )
            {
                ThrowLastOSError( );
            }
            SetValue( hCursor, flags & LR_SHARED ? false : true );
        }

        CursorHandle( const wchar_t* cursorName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            CheckPointerNotNull( cursorName );
            auto hCursor = static_cast<HCURSOR>( LoadImageW( 0, cursorName, IMAGE_CURSOR, width, height, flags ) );
            if ( !hCursor )
            {
                ThrowLastOSError( );
            }
            SetValue( hCursor, flags & LR_SHARED ? false : true );
        }
        CursorHandle( const std::wstring& cursorName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
            : CursorHandle( cursorName.c_str(), width , height, flags )
        {
        }

        CursorHandle( const ModuleHandle& module, int resourceId, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            auto hInstance = static_cast<HINSTANCE>( module.Value( ) );
            auto hCursor = static_cast<HCURSOR>( LoadImageW( hInstance, MAKEINTRESOURCE( resourceId ), IMAGE_CURSOR, width, height, flags ) );
            if ( !hCursor )
            {
                ThrowLastOSError( );
            }
            SetValue( hCursor, flags & LR_SHARED ? false : true );
        }
        CursorHandle( const ModuleHandle& module, const wchar_t* cursorName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            auto hInstance = static_cast<HINSTANCE>( module.Value( ) );
            CheckPointerNotNull( cursorName );
            auto hCursor = static_cast<HCURSOR>( LoadImageW( hInstance, cursorName, IMAGE_CURSOR, width, height, flags ) );
            if ( !hCursor )
            {
                ThrowLastOSError( );
            }
            SetValue( hCursor, flags & LR_SHARED ? false : true );
        }
        CursorHandle( const ModuleHandle& module, const std::wstring& cursorName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
            : CursorHandle( module, cursorName.c_str(), width, height, flags )
        {
        }

        CursorHandle( const ModuleHandle& module, const char* cursorName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
        {
            auto hInstance = static_cast<HINSTANCE>( module.Value( ) );
            CheckPointerNotNull( cursorName );
            auto hCursor = static_cast<HCURSOR>( LoadImageA( hInstance, cursorName, IMAGE_CURSOR, width, height, flags ) );
            if ( !hCursor )
            {
                ThrowLastOSError( );
            }
            SetValue( hCursor, flags & LR_SHARED ? false : true );
        }
        CursorHandle( const ModuleHandle& module, const std::string& cursorName, int width = 0, int height = 0, DWORD flags = LR_SHARED | LR_DEFAULTSIZE )
            : CursorHandle( module, cursorName.c_str( ), width, height, flags )
        {
        }

        void Close( ) noexcept
        {
            auto* derived = static_cast<DerivedType*>( this );
            if ( OwnsHandle( ) && derived->IsValid( ) )
            {
                DeleteObject( value_ );
            }
        }
    };


    class MenuHandle : public Handle<MenuHandle, HMENU>
    {
    public:
        using Base = Handle<MenuHandle, HMENU>;

        

        constexpr MenuHandle( ) noexcept
        {
        }

        constexpr explicit MenuHandle( HMENU hMenu, bool ownsHandle = true ) noexcept
            : Base( hMenu, ownsHandle )
        {
        }

        void Close( ) noexcept
        {
            auto* derived = static_cast<DerivedType*>( this );
            if ( OwnsHandle( ) && derived->IsValid( ) )
            {
                DestroyMenu( value_ );
            }
        }

        void AddStyle( DWORD style ) const
        {
            MENUINFO menuinfo = { sizeof( menuinfo ), 0 };
            menuinfo.fMask = MIM_STYLE;
            GetInfo( menuinfo );
            menuinfo.dwStyle |= style;
            SetInfo( menuinfo );
        }

        void Append( UINT uFlags, UINT_PTR uIDNewItem = 0, const wchar_t* newItem = nullptr ) const
        {
            if ( ::AppendMenuW( Value( ), uFlags, uIDNewItem, newItem ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void Append( UINT uFlags, UINT_PTR uIDNewItem, const char* newItem ) const
        {
            if ( ::AppendMenuA( Value( ), uFlags, uIDNewItem, newItem ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void CheckRadioItem( UINT idFirst, UINT idLast, UINT idCheck, UINT uFlags ) const
        {
            if ( ::CheckMenuRadioItem( Value( ), idFirst, idLast, idCheck, uFlags ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DeleteItem( UINT position, UINT uFlags ) const
        {
            if ( ::DeleteMenu( Value( ), position, uFlags ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void EnableItem( UINT idOfItem, UINT enableFlags ) const
        {
            if ( ::EnableMenuItem( Value( ), idOfItem, enableFlags ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        static void End( )
        {
            if ( ::EndMenu( ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        static long GetCheckMarkDimensions( )
        {
            return ::GetMenuCheckMarkDimensions( );
        }

        UINT GetDefaultItem( bool byPosition, UINT flags ) const
        {
            UINT result = ::GetMenuDefaultItem( Value( ), byPosition, flags );
            if ( result == -1 )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        void GetInfo( LPMENUINFO lpcmi ) const
        {
            if ( ::GetMenuInfo( Value( ), lpcmi ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void GetInfo( MENUINFO& lpcmi ) const
        {
            if ( ::GetMenuInfo( Value( ), &lpcmi ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        std::unique_ptr<MENUINFO> GetInfo( ) const
        {
            MENUINFO menuinfo = { sizeof( MENUINFO ), 0, };
            if ( ::GetMenuInfo( Value( ), &menuinfo ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return std::make_unique<MENUINFO>( menuinfo );
        }

        int GetItemCount( ) const
        {
            int result = ::GetMenuItemCount( Value( ) );
            if ( result == -1 )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        UINT GetItemID( int menuItemPosition ) const
        {
            UINT result = ::GetMenuItemID( Value( ), menuItemPosition );
            if ( result == -1 )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        void GetItemInfo( UINT itemIdOrPosition, bool byPosition, LPMENUITEMINFOW lpmii ) const
        {
            if ( ::GetMenuItemInfoW( Value( ), itemIdOrPosition, byPosition, lpmii ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void GetItemInfo( UINT itemIdOrPosition, bool byPosition, MENUITEMINFOW& lpmii ) const
        {
            if ( ::GetMenuItemInfoW( Value( ), itemIdOrPosition, byPosition, &lpmii ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        std::unique_ptr<MENUITEMINFOW> GetItemInfo( UINT itemIdOrPosition, bool byPosition ) const
        {
            MENUITEMINFOW menuiteminfo = { sizeof( MENUITEMINFOW ), 0 };
            if ( ::GetMenuItemInfoW( Value( ), itemIdOrPosition, byPosition, &menuiteminfo ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return std::make_unique<MENUITEMINFOW>( menuiteminfo );
        }

        UINT GetState( UINT itemIdOrPosition, bool byPosition ) const
        {
            UINT result = ::GetMenuState( Value( ), itemIdOrPosition, byPosition ? MF_BYPOSITION : MF_BYCOMMAND );
            if ( result == -1 )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        int GetTextLength( UINT itemIdOrPosition, bool byPosition ) const
        {
            int result = ::GetMenuStringW( Value( ), itemIdOrPosition, nullptr, 0, byPosition ? MF_BYPOSITION : MF_BYCOMMAND );
            return result;
        }
        int GetText( UINT itemIdOrPosition, LPTSTR lpString, int nMaxCount, bool byPosition ) const
        {
            int result = ::GetMenuStringW( Value( ), itemIdOrPosition, lpString, nMaxCount, byPosition ? MF_BYPOSITION : MF_BYCOMMAND );
            return result;
        }
        std::wstring GetText( UINT itemIdOrPosition, bool byPosition ) const
        {
            int length = GetTextLength( itemIdOrPosition, byPosition );
            if ( length )
            {
                std::wstring result( size_t( length ), '\x0' );
                ::GetMenuStringW( Value( ), itemIdOrPosition, const_cast<wchar_t*>( result.c_str( ) ), length, byPosition ? MF_BYPOSITION : MF_BYCOMMAND );
                return result;
            }
            return std::wstring( );
        }

        MenuHandle GetSubMenu( int position ) const
        {
            HMENU result = ::GetSubMenu( Value( ), position );
            return MenuHandle(result,false);
        }

        void Insert( UINT uPosition, UINT uFlags, UINT_PTR itemIdOrPosition, LPCWSTR newItemText ) const
        {
            if ( ::InsertMenuW( Value( ), uPosition, uFlags, itemIdOrPosition, newItemText ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void Insert( UINT uPosition, UINT uFlags, UINT_PTR itemIdOrPosition, const std::wstring& newItemText ) const
        {
            Insert( uPosition, uFlags, itemIdOrPosition, newItemText.c_str( ) );
        }
        void Insert( UINT uPosition, UINT uFlags, UINT_PTR itemIdOrPosition, LPCSTR newItemText ) const
        {
            if ( ::InsertMenuA( Value( ), uPosition, uFlags, itemIdOrPosition, newItemText ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void Insert( UINT uPosition, UINT uFlags, UINT_PTR itemIdOrPosition, const std::string& newItemText ) const
        {
            Insert( uPosition, uFlags, itemIdOrPosition, newItemText.c_str( ) );
        }

        void InsertItem( UINT itemIdOrPosition, bool byPosition, LPCMENUITEMINFOW menuItemInfo ) const
        {
            if ( ::InsertMenuItemW( Value( ), itemIdOrPosition, byPosition, menuItemInfo ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void InsertItem( UINT itemIdOrPosition, bool byPosition, LPCMENUITEMINFOA menuItemInfo ) const
        {
            if ( ::InsertMenuItemA( Value( ), itemIdOrPosition, byPosition, menuItemInfo ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void InsertItem( UINT itemIdOrPosition, bool byPosition, const MENUITEMINFOW& menuItemInfo ) const
        {
            if ( ::InsertMenuItemW( Value( ), itemIdOrPosition, byPosition, &menuItemInfo ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void InsertItem( UINT itemIdOrPosition, bool byPosition, const MENUITEMINFOA& menuItemInfo ) const
        {
            if ( ::InsertMenuItemA( Value( ), itemIdOrPosition, byPosition, &menuItemInfo ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        bool IsMenu( ) const
        {
            return ::IsMenu( Value( ) ) != FALSE;
        }


        static MenuHandle Load( LPCWSTR menuName )
        {
            return Load( ModuleHandle::Current( ), menuName );
        }
        static MenuHandle Load( const ModuleHandle& module, LPCWSTR menuName )
        {
            HINSTANCE hInstance = module.Value( );
            return Load( hInstance, menuName );
        }
        static MenuHandle Load( HINSTANCE module, LPCWSTR menuName )
        {
            HMENU hMenu = ::LoadMenuW( module, menuName );
            if ( !hMenu )
            {
                ThrowLastOSError( );
            }
            return MenuHandle( hMenu, true );
        }

        void Modify( UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR menuName ) const
        {
            if ( ::ModifyMenuW( Value( ), uPosition, uFlags, uIDNewItem, menuName ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void Remove( UINT uPosition, UINT uFlags ) const
        {
            if ( ::RemoveMenu( Value( ), uPosition, uFlags ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void SetDefaultItem( UINT itemIdOrPosition, bool byPosition ) const
        {
            if ( ::SetMenuDefaultItem( Value( ), itemIdOrPosition, byPosition ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void SetItemBitmaps( UINT itemIdOrPosition, bool byPosition, HBITMAP hBitmapUnchecked, HBITMAP hBitmapChecked ) const
        {
            if ( ::SetMenuItemBitmaps( Value( ), itemIdOrPosition, byPosition, hBitmapUnchecked, hBitmapChecked ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void SetItemInfo( UINT uItem, BOOL fByPosition, const LPMENUITEMINFOW menuItemInfo ) const
        {
            if ( ::SetMenuItemInfoW( Value( ), uItem, fByPosition, menuItemInfo ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void SetItemInfo( UINT uItem, BOOL fByPosition, const MENUITEMINFOW& menuItemInfo ) const
        {
            if ( ::SetMenuItemInfoW( Value( ), uItem, fByPosition, &menuItemInfo ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void SetInfo( LPCMENUINFO menuInfo ) const
        {
            if ( ::SetMenuInfo( Value( ), menuInfo ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void SetInfo( const MENUINFO& menuInfo ) const
        {
            SetInfo( &menuInfo );
        }
    };


    enum class SysColor : int
    {
        ScrollBar = 0,
        Desktop = 1,
        ActiveCaption = 2,
        InactiveCaption = 3,
        Menu = 4,
        Window = 5,
        WindowFrame = 6,
        MenuText = 7,
        WindowText = 8,
        ActiveCaptionText = 9,
        ActiveBorder = 10,
        InactiveBorder = 11,
        AppWorkspace = 12,
        Highlight = 13,
        HighlightText = 14,
        ButtonFace = 15,
        Control = 15,
        ButtonShadow = 16,
        ControlDark = 16,
        GrayText = 17,
        ControlText = 18,
        InactiveCaptionText = 19,
        ControlLight = 20,
        ButtonHighlight = 20,
        ControlDarkDark = 21,
        ControlLightLight = 22,
        InfoText = 23,
        Info = 24,
        HotTrack = 26,
        GradientActiveCaption = 27,
        GradientInactiveCaption = 28,
        MenuHighlight = 29,
        MenuBar = 30
    };


    class ColorRef
    {
        COLORREF color_;
    public:
        constexpr ColorRef( ) noexcept
            : color_( 0 )
        {
        }
        constexpr ColorRef( BYTE r, BYTE g, BYTE b ) noexcept
            : color_( RGB( r, g, b ) )
        {
        }
        ColorRef( SysColor sysColor ) noexcept
            : color_( GetSysColor( int( sysColor ) ) )
        {
        }

        constexpr ColorRef( COLORREF colorref ) noexcept
            : color_( colorref )
        {
        }
        constexpr ColorRef( const ColorRef& colorref ) noexcept
            : color_( colorref )
        {
        }

        constexpr ColorRef& operator = ( COLORREF colorref ) noexcept
        {
            color_ = colorref;
            return *this;
        }

        static constexpr ColorRef None( )
        {
            return ColorRef( CLR_NONE );
        }

        constexpr auto operator<=>( const ColorRef& ) const noexcept = default;
        constexpr bool operator==( const ColorRef& ) const noexcept = default;

        constexpr auto operator<=>( COLORREF colorref ) const noexcept
        {
            return color_ <=> colorref;
        }
        constexpr bool operator==( COLORREF colorref ) const noexcept
        {
            return color_ == colorref;
        }

        constexpr BYTE Red( ) const noexcept
        {
            return GetRValue( color_ );
        }
        constexpr BYTE Green( ) const noexcept
        {
            return GetGValue( color_ );
        }
        constexpr BYTE Blue( ) const noexcept
        {
            return GetBValue( color_ );
        }

        constexpr operator COLORREF( ) const noexcept
        {
            return color_;
        }


        constexpr COLORREF Value( ) const noexcept
        {
            return color_;
        }

        constexpr bool Invalid( ) const noexcept
        {
            return color_ == CLR_INVALID;
        }
    };


    enum class BrushStyle : UINT
    {
        Solid = 0,
        Null = 1,
        Hollow = Null,
        Hatched = 2,
        Pattern = 3,
        Indexed = 4,
        DibPattern = 5,
        DibPatternPT = 6,
        Pattern8X8 = 7,
        DibPattern8X8 = 8,
        MonoPattern = 9
    };

    enum class HatchStyle : UINT
    {
        Horizontal = 0,       /* ----- */
        Vertical = 1,       /* ||||| */
        ForwardDiagonal = 2,       /* \\\\\ */
        BackwardDiagonal = 3,       /* ///// */
        Cross = 4,       /* +++++ */
        DiagonalCross = 5        /* xxxxx */
    };

    enum class PenStyle : UINT
    {
        Solid = 0,
        Dash = 1,       /* -------  */
        Dot = 2,       /* .......  */
        DashDot = 3,       /* _._._._  */
        DashDotDot = 4,       /* _.._.._  */
        Null = 5,
        InsideFrame = 6,
        UserStyle = 7,
        Alternate = 8
    };

    enum class PenEndCaps : UINT
    {
        Round = 0x00000000,
        Square = 0x00000100,
        Flat = 0x00000200
    };

    enum class PenJoin : UINT
    {
        Round = 0x00000000,
        Bevel = 0x00001000,
        Miter = 0x00002000
    };

    enum class PenType : UINT
    {
        Cosmetic = 0x00000000,
        Geometric = 0x00010000
    };



    class BrushHandle : public Handle<BrushHandle, HBRUSH>
    {
        friend class DeviceContextHandle;
    public:
        typedef Handle<BrushHandle, HBRUSH> Base;

        constexpr BrushHandle( ) noexcept
        {
        }

        constexpr explicit BrushHandle( HBRUSH handle, bool ownsHandle = true ) noexcept
            : Base( handle, ownsHandle )
        {
        }

        explicit BrushHandle( const LOGBRUSH& logBrush )
            : Base( CreateBrushIndirect( &logBrush ), true )
        {
            if ( !Value( ) )
            {
                ThrowLastOSError( );
            }
        }
        explicit BrushHandle( COLORREF color )
            : Base( CreateSolidBrush( color ), true )
        {
            if ( !Value( ) )
            {
                ThrowLastOSError( );
            }
        }
        explicit BrushHandle( SysColor sysColor )
            : Base( GetSysColorBrush( int( sysColor ) ), false )
        {
            if ( !Value( ) )
            {
                ThrowLastOSError( );
            }
        }

        void Close( ) noexcept
        {
            auto* derived = static_cast<DerivedType*>( this );
            if ( OwnsHandle( ) && derived->IsValid( ) )
            {
                DeleteObject( value_ );
            }
        }
    };


    class PenHandle : public Handle<PenHandle, HPEN>
    {
        friend class DeviceContextHandle;
    public:
        using Base = Handle<PenHandle, HPEN>;
        constexpr PenHandle( ) noexcept
        {
        }


        constexpr explicit PenHandle( HPEN handle, bool ownsHandle = true ) noexcept
            : Base( handle, ownsHandle )
        {
        }

        void Close( ) noexcept
        {
            auto* derived = static_cast<DerivedType*>( this );
            if ( OwnsHandle( ) && derived->IsValid( ) )
            {
                DeleteObject( value_ );
            }
        }
    };

    class FontHandle : public Handle<FontHandle, HFONT>
    {
        friend class DeviceContextHandle;
    public:
        using Base = Handle<FontHandle, HFONT>;
        constexpr FontHandle( ) noexcept
        {
        }

        constexpr explicit FontHandle( HFONT handle, bool ownsHandle = true ) noexcept
            : Base( handle, ownsHandle )
        {
        }

        void Close( ) noexcept
        {
            auto* derived = static_cast<DerivedType*>( this );
            if ( OwnsHandle( ) && derived->IsValid( ) )
            {
                DeleteObject( value_ );
            }
        }
    };

    enum class RegionType : int
    {
        Error = 0,
        Null = 1,
        Simple = 2,
        Complex = 3
    };


    class RegionHandle : public Handle<RegionHandle, HRGN>
    {
        friend class DeviceContextHandle;
    public:
        using Base = Handle<RegionHandle, HRGN>;

        constexpr RegionHandle( ) noexcept
        {
        }

        constexpr explicit RegionHandle( HRGN handle, bool ownsHandle = true ) noexcept
            : Base( handle, ownsHandle )
        {
        }

        void Close( ) noexcept
        {
            auto* derived = static_cast<DerivedType*>( this );
            if ( OwnsHandle( ) && derived->IsValid( ) )
            {
                DeleteObject( value_ );
            }
        }
    };

    class PaletteHandle : public Handle<PaletteHandle, HPALETTE>
    {
        friend class DeviceContextHandle;
    public:
        using Base = Handle<PaletteHandle, HPALETTE>;

        constexpr PaletteHandle( ) noexcept
        {
        }

        constexpr explicit PaletteHandle( HPALETTE handle, bool ownsHandle = true ) noexcept
            : Base( handle, ownsHandle )
        {
        }

        void Close( ) noexcept
        {
            auto* derived = static_cast<DerivedType*>( this );
            if ( OwnsHandle( ) && derived->IsValid( ) )
            {
                DeleteObject( value_ );
            }
        }
    };


#pragma pack(push,8)
#pragma pack(pop)


    enum class DrawCaptionOptions : int
    {
        Active = 0x0001,
        SmallCaption = 0x0002,
        Icon = 0x0004,
        Text = 0x0008,
        InButton = 0x0010,
        Gradient = 0x0020,
        Buttons = 0x1000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( DrawCaptionOptions, int );

    enum class ForegroundMixMode : int
    {
        Black = 1,   /*  0       */
        NotMergePen = 2,   /* DPon     */
        MaskNotPen = 3,   /* DPna     */
        NotCopyPen = 4,   /* PN       */
        MaskPenNot = 5,   /* PDna     */
        Not = 6,   /* Dn       */
        XorPen = 7,   /* DPx      */
        NotMaskPen = 8,   /* DPan     */
        MaskPen = 9,   /* DPa      */
        NotXorPen = 10,  /* DPxn     */
        Nop = 11,  /* D        */
        MergeNotPen = 12,  /* DPno     */
        CopyPen = 13,  /* P        */
        MergePenNot = 14,  /* PDno     */
        MergePen = 15,  /* DPo      */
        White = 16  /*  1       */
    };


    enum class BackgroundMixMode : int
    {
        Transparent = 1,
        Opaque = 2
    };

    enum class BorderStyle : UINT
    {
        RaisedOuter = 0x0001,
        SunkenOuter = 0x0002,
        RaisedInner = 0x0004,
        SunkenInner = 0x0008,
        Raised = ( BDR_RAISEDOUTER | BDR_RAISEDINNER ),
        Sunken = ( BDR_SUNKENOUTER | BDR_SUNKENINNER ),
        Etched = ( BDR_SUNKENOUTER | BDR_RAISEDINNER ),
        Bump = ( BDR_RAISEDOUTER | BDR_SUNKENINNER )
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( BorderStyle, UINT );

    enum class BorderFlags : UINT
    {
        Left = 0x0001,
        Top = 0x0002,
        Right = 0x0004,
        Bottom = 0x0008,

        TopLeft = ( BF_TOP | BF_LEFT ),
        TopRight = ( BF_TOP | BF_RIGHT ),
        BottomLeft = ( BF_BOTTOM | BF_LEFT ),
        BottomRight = ( BF_BOTTOM | BF_RIGHT ),
        Rectangle = ( BF_LEFT | BF_TOP | BF_RIGHT | BF_BOTTOM ),

        Diagonal = 0x0010,

        // For diagonal lines, the BF_RECT flags specify the end point of the
        // vector bounded by the rectangle parameter.
        DiagonalEndTopRight = ( BF_DIAGONAL | BF_TOP | BF_RIGHT ),
        DiagonalEndTopLeft = ( BF_DIAGONAL | BF_TOP | BF_LEFT ),
        DiagonalEndBottomLeft = ( BF_DIAGONAL | BF_BOTTOM | BF_LEFT ),
        DiagonalEndBottomRight = ( BF_DIAGONAL | BF_BOTTOM | BF_RIGHT ),


        Middle = 0x0800,  /* Fill in the middle */
        Soft = 0x1000,  /* For softer buttons */
        Adjust = 0x2000,  /* Calculate the space left over */
        Flat = 0x4000,  /* For flat rather than 3D borders */
        Mono = 0x8000  /* For monochrome borders */
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( BorderFlags, UINT );


        enum class DrawFrameControlType : UINT
    {
        Caption = 1,
        MenuBar = 2,
        ScrollBar = 3,
        Button = 4,
        PopupMenu = 5
    };

    enum class DrawFrameControlCaptionPart
    {
        CloseButton = 0x0000,
        MinimizeButton = 0x0001,
        MaximizeButton = 0x0002,
        RestoreButton = 0x0003,
        HelpButton = 0x0004
    };

    enum class DrawFrameControlMenuBarPart
    {
        Arrow = 0x0000,
        Check = 0x0001,
        Bullet = 0x0002,
        ArrowRight = 0x0004
    };


    enum class DrawFrameControlScrollBarPart
    {
        Up = 0x0000,
        Down = 0x0001,
        Left = 0x0002,
        Right = 0x0003,
        ComboBox = 0x0005,
        SizeGrip = 0x0008,
        SizeGripRight = 0x0010
    };

    enum class DrawFrameControlButtonOptions : Int32
    {
        CheckBox = 0x0000,
        RadioImage = 0x0001,
        RadioMask = 0x0002,
        RadioButton = 0x0004,
        ThreeState = 0x0008,
        PushButton = 0x0010
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( DrawFrameControlButtonOptions, Int32 );

    enum class DrawFrameControlPopupMenuPart
    {
        Arrow = 0x0000,
        Check = 0x0001,
        Bullet = 0x0002,
        ArrowRight = 0x0004
    };

    enum class DrawFrameControlOptions : UINT
    {
        None = 0x0000,
        Inactive = 0x0100,
        Pushed = 0x0200,
        Checked = 0x0400,
        Transparent = 0x0800,
        HotTracked = 0x1000,
        AdjustRectangle = 0x2000,
        Flat = 0x4000,
        Mono = 0x8000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( DrawFrameControlOptions, UINT );

    enum class DrawStateFlags : Int32
    {
        Normal = 0x0000,
        Prefix = 0x0002,
        Dithered = 0x0010,  /* Gray string appearance */
        Disabled = 0x0020,
        Mono = 0x0080,
        HidePrefix = 0x0200,
        PrefixOnly = 0x0400,
        Right = 0x8000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( DrawStateFlags, Int32 );


    enum class BoundsAccumulationFlags : Int32
    {
        Reset = 0x0001,
        Accumulate = 0x0002,
        Dirty = DCB_ACCUMULATE,
        Set = ( DCB_RESET | DCB_ACCUMULATE ),
        Enable = 0x0004,
        Disable = 0x0008
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( BoundsAccumulationFlags, Int32 );

    enum class ArcDirection
    {
        CounterClockwise = AD_COUNTERCLOCKWISE,
        Clockwise = AD_CLOCKWISE
    };

    enum class PolyDrawCommand : BYTE
    {
        CloseFigure = PT_CLOSEFIGURE,
        LineTo = PT_LINETO,
        LineToAndClose = PT_LINETO | PT_CLOSEFIGURE,
        BezierTo = PT_BEZIERTO,
        BezierToAndClose = PT_BEZIERTO | PT_CLOSEFIGURE,
        MoveTo = PT_MOVETO
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( PolyDrawCommand, BYTE );


    enum class DrawTextFlags : UINT
    {
        Top = 0x00000000,
        Left = 0x00000000,
        Center = 0x00000001,
        Right = 0x00000002,
        VCenter = 0x00000004,
        Bottom = 0x00000008,
        WordBreak = 0x00000010,
        SingleLine = 0x00000020,
        ExpandTabs = 0x00000040,
        TabStop = 0x00000080,
        NoClip = 0x00000100,
        ExternalLeading = 0x00000200,
        CalcRect = 0x00000400,
        NoPrefix = 0x00000800,
        Internal = 0x00001000,
        EditControl = 0x00002000,
        PathEllipsis = 0x00004000,
        EndEllipsis = 0x00008000,
        ModifyString = 0x00010000,
        RtlReading = 0x00020000,
        WordEllipsis = 0x00040000,
        NoFullWidthCharBreak = 0x00080000,
        HidePrefix = 0x00100000,
        PrefixOnly = 0x00200000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( DrawTextFlags, UINT );

    enum class TextAlignment : UINT
    {
        NoUpdateCP = 0,
        Left = 0,
        Top = 0,
        UpdateCP = 1,
        Right = 2,
        Center = 6,
        Bottom = 8,
        Baseline = 24,
        RtlReading = 256
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TextAlignment, UINT );

    enum class GraphicsMode
    {
        Compatible = GM_COMPATIBLE,
        Advanced = GM_ADVANCED
    };


    enum class MapMode
    {
        Text = 1,
        LoMetric = 2,
        HiMetric = 3,
        LoEnglish = 4,
        HiEnglish = 5,
        Twips = 6,
        Isotropic = 7,
        Anisotropic = 8
    };


    enum class RasterOperation : DWORD
    {
        SourceCopy = 0x00CC0020, /* dest = source                   */
        SourcePaint = 0x00EE0086, /* dest = source OR dest           */
        SourceOrDestination = 0x00EE0086, /* dest = source OR dest           */
        SourceAndDestination = 0x008800C6, /* dest = source AND dest          */
        SourceInvert = 0x00660046, /* dest = source XOR dest          */
        SourceXorDestination = 0x00660046, /* dest = source XOR dest          */
        SourceErase = 0x00440328, /* dest = source AND (NOT dest )   */
        SourceAndNotDestination = 0x00440328, /* dest = source AND (NOT dest )   */
        NotSourceCopy = 0x00330008, /* dest = (NOT source)             */
        NotSourceErase = 0x001100A6, /* dest = (NOT src) AND (NOT dest) */
        NotSourceAndNotDestination = 0x001100A6, /* dest = (NOT src) AND (NOT dest) */
        MergeCopy = 0x00C000CA, /* dest = (source AND pattern)     */
        MergePaint = 0x00BB0226, /* dest = (NOT source) OR dest     */
        PatternCopy = 0x00F00021, /* dest = pattern                  */
        PatternPaint = 0x00FB0A09, /* dest = DPSnoo                   */
        PatternInvert = 0x005A0049, /* dest = pattern XOR dest         */
        DestinationInvert = 0x00550009, /* dest = (NOT dest)               */
        Blackness = 0x00000042, /* dest = BLACK                    */
        Whiteness = 0x00FF0062, /* dest = WHITE                    */
        NoMirrorBitmap = 0x80000000, /* Do not Mirror the bitmap in this call */
        CaptureBlt = 0x40000000 /* Include layered windows */
    };


    class DeviceContextHandle : public Handle<DeviceContextHandle,HDC>
    {
        HPEN originalPen_;
        HBRUSH originalBrush_;
        HBITMAP originalBitmap_;
        HFONT originalFont_;
    protected:
        void SaveDefaultObjects( ) noexcept
        {
            HDC hDC = Value( );
            if ( hDC )
            {
                originalPen_ = (HPEN)GetCurrentObject( hDC, OBJ_PEN );
                originalBrush_ = (HBRUSH)GetCurrentObject( hDC, OBJ_BRUSH );
                originalBitmap_ = (HBITMAP)GetCurrentObject( hDC, OBJ_BITMAP );
                originalFont_ = (HFONT)GetCurrentObject( hDC, OBJ_FONT );
            }
        }
        void RestoreDefaultObjects( ) noexcept
        {
            HDC hDC = Value( );
            if ( hDC )
            {
                SelectObject( hDC, originalPen_ );
                SelectObject( hDC, originalBrush_ );
                SelectObject( hDC, originalBitmap_ );
                SelectObject( hDC, originalFont_ );
            }
        }

    public:
        using Base = Handle<DeviceContextHandle, HDC>;
    protected:
        constexpr DeviceContextHandle( ) noexcept
            : originalPen_( nullptr ), originalBrush_(nullptr), originalBitmap_(nullptr), originalFont_(nullptr)
        {
        }

        constexpr DeviceContextHandle( HDC handle, bool ownsHandle = true ) noexcept
            : Base( handle, ownsHandle ), originalPen_( nullptr ), originalBrush_( nullptr ), originalBitmap_( nullptr ), originalFont_( nullptr )
        {
        }
        
    public:
        // TODO: Fixme for derived classes
        void Close( ) noexcept
        {

        }

        PenHandle Pen( ) const
        {
            auto hObject = static_cast<HPEN>(GetCurrentObject( Value( ), OBJ_PEN ));
            if ( !hObject )
            {
                ThrowLastOSError( );
            }
            return PenHandle( hObject, false );
        }
        PenHandle SetPen( const PenHandle& newPen ) const
        {
            auto hObject = static_cast<HPEN>( SelectObject( Value( ), newPen.Value( ) ) );
            if ( !hObject )
            {
                ThrowLastOSError( );
            }
            return PenHandle( hObject, false );
        }

        BrushHandle Brush( ) const
        {
            auto hObject = static_cast<HBRUSH>( GetCurrentObject( Value( ), OBJ_BRUSH ) );
            if ( !hObject )
            {
                ThrowLastOSError( );
            }
            return BrushHandle( hObject, false );
        }
        BrushHandle SetBrush( const BrushHandle& newBrush ) const
        {
            auto hObject = static_cast<HBRUSH>( SelectObject( Value( ), newBrush.Value( ) ) );
            if ( !hObject )
            {
                ThrowLastOSError( );
            }
            return BrushHandle( hObject, false );
        }

        BitmapHandle Bitmap( ) const
        {
            auto hObject = static_cast<HBITMAP>( GetCurrentObject( Value( ), OBJ_BRUSH ) );
            if ( !hObject )
            {
                ThrowLastOSError( );
            }
            return BitmapHandle( hObject, false );
        }
        BitmapHandle SetBitmap( const BitmapHandle& newBitmap ) const
        {
            auto hObject = static_cast<HBITMAP>( SelectObject( Value( ), newBitmap.Value( ) ) );
            if ( !hObject )
            {
                ThrowLastOSError( );
            }
            return BitmapHandle( hObject, false );
        }

        FontHandle Font( ) const
        {
            auto hObject = static_cast<HFONT>( GetCurrentObject( Value( ), OBJ_BRUSH ) );
            if ( !hObject )
            {
                ThrowLastOSError( );
            }
            return FontHandle( hObject, false );
        }
        FontHandle SetFont( const FontHandle& newFont ) const
        {
            auto hObject = static_cast<HFONT>( SelectObject( Value( ), newFont.Value( ) ) );
            if ( !hObject )
            {
                ThrowLastOSError( );
            }
            return FontHandle( hObject, false );
        }


        HW_EXPORT void DrawCaption( const Control& control, const RECT& boundingRectangle, DrawCaptionOptions options ) const;

        void DrawEdge( RECT& boundingRectangle, BorderStyle borderStyle, BorderFlags borderFlags ) const
        {
            if ( ::DrawEdge( Value( ), &boundingRectangle, UINT( borderStyle ), UINT( borderFlags ) ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawFocusRect( RECT& boundingRectangle ) const
        {
            if ( ::DrawFocusRect( Value( ), &boundingRectangle ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawFrameControl( DrawFrameControlType frameControlType, RECT& boundingRectangle, UINT state ) const
        {
            if ( ::DrawFrameControl( Value( ), &boundingRectangle, static_cast<UINT>( frameControlType ), state ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawCaptionFrameControl( DrawFrameControlCaptionPart part, RECT& boundingRectangle, DrawFrameControlOptions options ) const
        {
            UINT state = static_cast<UINT>( part ) | static_cast<UINT>( options );
            DrawFrameControl( DrawFrameControlType::Caption, boundingRectangle, state );
        }
        void DrawMenuBarFrameControl( DrawFrameControlMenuBarPart part, RECT& boundingRectangle, DrawFrameControlOptions options ) const
        {
            UINT state = static_cast<UINT>( part ) | static_cast<UINT>( options );
            DrawFrameControl( DrawFrameControlType::MenuBar, boundingRectangle, state );
        }
        void DrawScrollBarFrameControl( DrawFrameControlScrollBarPart part, RECT& boundingRectangle, DrawFrameControlOptions options ) const
        {
            UINT state = static_cast<UINT>( part ) | static_cast<UINT>( options );
            DrawFrameControl( DrawFrameControlType::ScrollBar, boundingRectangle, state );
        }
        void DrawButtonFrameControl( DrawFrameControlButtonOptions buttonOptions, RECT& boundingRectangle, DrawFrameControlOptions options ) const
        {
            UINT state = static_cast<UINT>( buttonOptions ) | static_cast<UINT>( options );
            DrawFrameControl( DrawFrameControlType::Button, boundingRectangle, state );
        }
        void DrawPopupMenuFrameControl( DrawFrameControlPopupMenuPart part, RECT& boundingRectangle, DrawFrameControlOptions options ) const
        {
            UINT state = static_cast<UINT>( part ) | static_cast<UINT>( options );
            DrawFrameControl( DrawFrameControlType::PopupMenu, boundingRectangle, state );
        }

        void DrawState( HBRUSH hbrFore, DRAWSTATEPROC qfnCallBack, LPARAM lData, WPARAM wData, int x, int y, int cx, int cy, UINT uFlags ) const
        {
            auto rc = ::DrawState( Value( ), hbrFore, qfnCallBack, lData, wData, x, y, cx, cy, uFlags );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

    private:
        static constexpr UINT ConvertDrawStateFlagsForText( DrawStateFlags drawStateFlags ) noexcept
        {
            UINT flags = static_cast<UINT>( drawStateFlags );

            if ( ( flags & DSS_PREFIXONLY ) != 0 )
            {
                flags &= ~DSS_HIDEPREFIX;
            }
            if ( ( flags & ( DSS_HIDEPREFIX | DSS_PREFIXONLY ) ) != 0 )
            {
                flags |= DST_PREFIXTEXT;
            }
            if ( ( flags & DST_PREFIXTEXT ) == 0 )
            {
                flags |= DST_TEXT;
            }
            return flags;
        }
    public:


        void DrawState( const wchar_t* text, int x, int y, int cx, int cy, DrawStateFlags drawStateFlags ) const
        {
            auto flags = ConvertDrawStateFlagsForText( drawStateFlags );
            DrawState( nullptr, nullptr, LPARAM( text ), 0, x, y, cx, cy, flags );
        }
        void DrawState( const wchar_t* text, int x, int y, DrawStateFlags drawStateFlags ) const
        {
            DrawState( text, x, y, 0, 0, drawStateFlags );
        }

        void DrawState( const std::wstring& text, int x, int y, int cx, int cy, DrawStateFlags drawStateFlags ) const
        {
            auto flags = ConvertDrawStateFlagsForText( drawStateFlags );
            DrawState( nullptr, nullptr, reinterpret_cast<LPARAM>( text.c_str() ), static_cast<WPARAM>( text.length( ) ), x, y, cx, cy, flags );
        }
        void DrawState( const std::wstring& text, int x, int y, DrawStateFlags drawStateFlags ) const
        {
            DrawState( text, x, y, 0, 0, drawStateFlags );
        }

        void DrawState( const BrushHandle& brush, const wchar_t* text, int x, int y, int cx, int cy, DrawStateFlags drawStateFlags ) const
        {
            auto flags = ConvertDrawStateFlagsForText( drawStateFlags );
            DrawState( brush.Value(), nullptr, reinterpret_cast<LPARAM>( text ), 0, x, y, cx, cy, flags );
        }
        void DrawState( const BrushHandle& brush, const std::wstring& text, int x, int y, int cx, int cy, DrawStateFlags drawStateFlags ) const
        {
            auto flags = ConvertDrawStateFlagsForText( drawStateFlags );
            DrawState( brush.Value( ), nullptr, reinterpret_cast<LPARAM>( text.c_str() ), static_cast<WPARAM>( text.length( ) ), x, y, cx, cy, flags );
        }

        void DrawState( const BrushHandle& brush, const wchar_t* text, int x, int y, DrawStateFlags flags ) const
        {
            DrawState( brush, text, x, y, 0, 0, flags );
        }
        void DrawState( const BrushHandle& brush, const std::wstring& text, int x, int y, DrawStateFlags flags ) const
        {
            DrawState( brush, text, x, y, 0, 0, flags );
        }

        void DrawState( const BitmapHandle& bitmap, int x, int y, int cx, int cy, DrawStateFlags drawStateFlags ) const
        {
            UINT flags = static_cast<UINT>( drawStateFlags ) | DST_BITMAP;
            DrawState( nullptr, nullptr, reinterpret_cast<LPARAM>( bitmap.Value( ) ), 0, x, y, cx, cy, flags );
        }
        void DrawState( const BitmapHandle& bitmap, int x, int y, DrawStateFlags flags ) const
        {
            DrawState( bitmap, x, y, 0, 0, flags );
        }
        void DrawState( const IconHandle& icon, int x, int y, int cx, int cy, DrawStateFlags drawStateFlags ) const
        {
            UINT flags = static_cast<UINT>( drawStateFlags ) | DST_ICON;
            DrawState( nullptr, nullptr, reinterpret_cast<LPARAM>( icon.Value( ) ), 0, x, y, cx, cy, flags );
        }
        void DrawState( const IconHandle& icon, int x, int y, DrawStateFlags flags ) const
        {
            DrawState( icon, x, y, 0, 0, flags );
        }


        HW_EXPORT RegionType ExcludeUpdateRgn( const Control& control ) const;
        static void Flush( )
        {
            if ( GdiFlush( ) == FALSE && GetLastError( ) )
            {
                ThrowLastOSError( );
            }
        }
        static DWORD BatchLimit( )
        {
            auto rc = GdiGetBatchLimit( );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return rc;
        }
        static DWORD SetBatchLimit( DWORD newBatchLimit )
        {
            auto rc = GdiSetBatchLimit( newBatchLimit );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return rc;
        }

        ColorRef BackgroundColor( ) const
        {
            return GetBkColor( Value( ) );
        }

        ColorRef SetBackgroundColor( COLORREF color ) const
        {
            ColorRef result = SetBkColor( Value( ), color );
            if ( result.Invalid( ) )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        Windows::BackgroundMixMode BackgroundMixMode( ) const
        {
            int result = GetBkMode( Value( ) );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return static_cast<Windows::BackgroundMixMode>( result );
        }
        Windows::BackgroundMixMode SetBackgroundMixMode( Windows::BackgroundMixMode mixMode ) const
        {
            auto mode = static_cast<int>( mixMode );
            auto rc = SetBkMode( Value( ), mode );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return Windows::BackgroundMixMode( rc );
        }

        BoundsAccumulationFlags BoundsRect( RECT& boundingRectangle ) const
        {
            auto rc = GetBoundsRect( Value( ), &boundingRectangle, 0 );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return static_cast<BoundsAccumulationFlags>( rc );
        }
        BoundsAccumulationFlags BoundsRect( RECT& boundingRectangle, bool clear ) const
        {
            auto rc = GetBoundsRect( Value( ), &boundingRectangle, clear ? DCB_RESET : 0 );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return static_cast<BoundsAccumulationFlags>( rc );
        }
        BoundsAccumulationFlags SetBoundsRect( const RECT& boundingRectangle, BoundsAccumulationFlags boundsAccumulationFlags ) const
        {
            int flags = static_cast<int>( boundsAccumulationFlags );
            auto rc = ::SetBoundsRect( Value( ), &boundingRectangle, flags );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return static_cast<BoundsAccumulationFlags>( rc );
        }

        Windows::ForegroundMixMode ForegroundMixMode( ) const
        {
            auto rc = GetROP2( Value( ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return static_cast<Windows::ForegroundMixMode>( rc );
        }
        Windows::ForegroundMixMode SetForegroundMixMode( Windows::ForegroundMixMode mixMode ) const
        {
            auto mode = static_cast<int>( mixMode );
            auto rc = SetROP2( Value( ), mode );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return static_cast<Windows::ForegroundMixMode>( rc );
        }

        void DrawGrayString( const std::wstring& text, int X, int Y, int nWidth = 0, int nHeight = 0 ) const
        {
            if ( text.length( ) )
            {
                if ( ::GrayStringW( Value( ), nullptr, nullptr, LPARAM( text.c_str( ) ), int( text.length( ) ), X, Y, nWidth, nHeight ) == 0 )
                {
                    ThrowLastOSError( );
                }
            }
        }
        void DrawGrayString( const BrushHandle& brush, const std::wstring& text, int X, int Y, int nWidth = 0, int nHeight = 0 ) const
        {
            if ( text.length( ) )
            {
                if ( ::GrayString( Value( ), brush.Value(), nullptr, LPARAM( text.c_str( ) ), int( text.length( ) ), X, Y, nWidth, nHeight ) == 0 )
                {
                    ThrowLastOSError( );
                }
            }
        }

        void DrawDesktopWallPaper( ) const
        {
            if ( PaintDesktop( Value( ) ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawChord( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2 ) const
        {
            if ( ::Chord( Value( ), nLeftRect, nTopRect, nRightRect, nBottomRect, nXRadial1, nYRadial1, nXRadial2, nYRadial2 ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawChord( const RECT& rectangle, const POINT& start, const POINT& end ) const
        {
            if ( ::Chord( Value( ), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, start.x, start.y, end.x, end.y ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawEllipse( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect ) const
        {
            if ( ::Ellipse( Value( ), nLeftRect, nTopRect, nRightRect, nBottomRect ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawEllipse( const RECT& rectangle ) const
        {
            if ( ::Ellipse( Value( ), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawFilledRectangle( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, const BrushHandle& brush ) const
        {
            RECT rect = { nLeftRect, nTopRect, nRightRect, nBottomRect };
            if ( ::FillRect( Value( ), &rect, brush ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawFilledRectangle( const RECT& rectangle, const BrushHandle& brush ) const
        {
            if ( ::FillRect( Value( ), &rectangle, brush ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawFrameRectangle( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, const BrushHandle& brush ) const
        {
            RECT rect = { nLeftRect, nTopRect, nRightRect, nBottomRect };
            if ( ::FrameRect( Value( ), &rect, brush ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawFrameRectangle( const RECT& rectangle, const BrushHandle& brush ) const
        {
            if ( ::FrameRect( Value( ), &rectangle, brush ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawInvertedRectangle( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect ) const
        {
            RECT rect = { nLeftRect, nTopRect, nRightRect, nBottomRect };
            if ( ::InvertRect( Value( ), &rect ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawInvertedRectangle( const RECT& rectangle ) const
        { 
            if ( ::InvertRect( Value( ), &rectangle ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawPie( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2 ) const
        {
            if ( ::Pie( Value( ), nLeftRect, nTopRect, nRightRect, nBottomRect, nXRadial1, nYRadial1, nXRadial2, nYRadial2 ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawPie( const RECT& rectangle, const POINT& start, const POINT& end ) const
        {
            if ( ::Pie( Value( ), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, start.x, start.y, end.x, end.y ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawPolygon( const POINT* lpPoints, int nCount ) const
        {
            if ( ::Polygon( Value( ), lpPoints, nCount ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawPolygon( const std::vector<POINT>& points ) const
        {
            DrawPolygon( points.data( ), static_cast<int>( points.size() ) );
        }

        void DrawPolyPolygons( const std::vector< std::vector<POINT> >& polyPolygons ) const
        {
            std::vector<INT> polyCounts;
            polyCounts.reserve( polyPolygons.size( ) );
            size_t totalNumberOfPoints = 0;
            for ( auto polygon : polyPolygons )
            {
                if ( polygon.size( ) < 2 )
                {
                    throw ArgumentException( L"Not enough points in the polygon" );
                }
                int numberOfPoints = INT( polygon.size( ) );
                polyCounts.push_back( numberOfPoints );
                totalNumberOfPoints += numberOfPoints;
            }
            std::vector<POINT> points;
            points.reserve( totalNumberOfPoints );
            for ( auto polygon : polyPolygons )
            {
                for ( auto point : polygon )
                {
                    points.push_back( point );
                }
            }
            if ( ::PolyPolygon( Value( ), points.data( ), polyCounts.data( ), int( polyCounts.size( ) ) ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawPolyPolygon( const POINT* lpPoints, const INT* lpPolyCounts, int nCount ) const
        {
            if ( ::PolyPolygon( Value( ), lpPoints, lpPolyCounts, nCount ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawRectangle( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect ) const
        {
            if ( ::Rectangle( Value( ), nLeftRect, nTopRect, nRightRect, nBottomRect ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawRectangle( const RECT& rectangle ) const
        {
            if ( ::Rectangle( Value( ), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawRoundedRectangle( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidth, int nHeight ) const
        {
            if ( ::RoundRect( Value( ), nLeftRect, nTopRect, nRightRect, nBottomRect, nWidth, nHeight ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawRoundedRectangle( const RECT& rectangle, int nWidth, int nHeight ) const
        {
            if ( ::RoundRect( Value( ), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, nWidth, nHeight ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawRoundedRectangle( const RECT& rectangle, const SIZE& ellipseSize ) const
        {
            if ( ::RoundRect( Value( ), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, ellipseSize.cx, ellipseSize.cy ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawAngleArc( int X, int Y, DWORD dwRadius, FLOAT eStartAngle, FLOAT eSweepAngle ) const
        {
            if ( ::AngleArc( Value( ), X, Y, dwRadius, eStartAngle, eSweepAngle ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawAngleArc( const POINT& center, DWORD dwRadius, FLOAT eStartAngle, FLOAT eSweepAngle ) const
        {
            if ( ::AngleArc( Value( ), center.x, center.y, dwRadius, eStartAngle, eSweepAngle ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawArc( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nXStartArc, int nYStartArc, int nXEndArc, int nYEndArc ) const
        {
            if ( ::Arc( Value( ), nLeftRect, nTopRect, nRightRect, nBottomRect, nXStartArc, nYStartArc, nXEndArc, nYEndArc ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawArc( const RECT& rectangle, const POINT& start, const POINT& end ) const
        {
            if ( ::Arc( Value( ), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom, start.x, start.y, end.x, end.y ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        Windows::ArcDirection ArcDirection( ) const
        {
            auto rc = GetArcDirection( Value( ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return static_cast<Windows::ArcDirection>( rc );
        }
        Windows::ArcDirection SetArcDirection( Windows::ArcDirection newArcDirection ) const
        {
            int nad = int( newArcDirection );
            auto rc = ::SetArcDirection( Value( ), nad );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return static_cast<Windows::ArcDirection>( rc );
        }

        void DrawLineTo( int nXEnd, int nYEnd ) const
        {
            if ( ::LineTo( Value( ), nXEnd, nYEnd ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawLineTo( const POINT& endPoint ) const
        {
            if ( ::LineTo( Value( ), endPoint.x, endPoint.y ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void MoveTo( int newX, int newY ) const
        {
            if ( ::MoveToEx( Value( ), newX, newY, nullptr ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void MoveTo( int newX, int newY, int& previousX, int& previousY ) const
        {
            POINT p = { 0, };
            if ( ::MoveToEx( Value( ), newX, newY, &p ) == FALSE )
            {
                ThrowLastOSError( );
            }
            previousX = p.x;
            previousY = p.y;
        }
        void MoveTo( const POINT& newPosition ) const
        {
            if ( ::MoveToEx( Value( ), newPosition.x, newPosition.y, nullptr ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void MoveTo( const POINT& newPosition, POINT& previousPosition ) const
        {
            if ( ::MoveToEx( Value( ), newPosition.x, newPosition.y, &previousPosition ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawPolyBezier( const POINT* lppt, DWORD cPoints ) const
        {
            if ( ::PolyBezier( Value( ), lppt, cPoints ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawPolyBezier( const std::vector<POINT>& points ) const
        {
            DrawPolyBezier( points.data( ), static_cast<DWORD>( points.size( ) ) );
        }

        void DrawPolyBezierTo( const POINT* lppt, DWORD cPoints ) const
        {
            if ( ::PolyBezierTo( Value( ), lppt, cPoints ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawPolyBezierTo( const std::vector<POINT>& points ) const
        {
            DrawPolyBezierTo( points.data( ), static_cast<int>( points.size() ) );
        }

        void Draw( const POINT* lppt, const PolyDrawCommand* lpbTypes, int cCount ) const
        {
            if ( ::PolyDraw( Value( ), lppt, (BYTE*)lpbTypes, cCount ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawPolyLine( const POINT* lppt, DWORD cPoints ) const
        {
            if ( ::Polyline( Value( ), lppt, cPoints ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawPolyLine( const std::vector<POINT>& points ) const
        {
            DrawPolyLine( points.data( ), static_cast<int>( points.size( ) ) );
        }

        void DrawPolyLineTo( const POINT* lppt, DWORD cPoints ) const
        {
            if ( ::PolylineTo( Value( ), lppt, cPoints ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawPolyLineTo( const std::vector<POINT>& points ) const
        {
            DrawPolyLineTo( points.data( ), static_cast<int>( points.size( ) ) );
        }

        ColorRef TextColor( ) const
        {
            COLORREF resultClr = GetTextColor( Value( ) );
            if ( resultClr == CLR_INVALID )
            {
                ThrowLastOSError( );
            }
        }
        ColorRef SetTextColor( COLORREF colorRef ) const
        {
            COLORREF resultClr = ::SetTextColor( Value( ), colorRef );
            if ( resultClr == CLR_INVALID )
            {
                ThrowLastOSError( );
            }
            return ColorRef( resultClr );
        }


        Windows::TextAlignment TextAlignment( ) const
        {
            auto result = GetTextAlign( Value( ) );
            if ( result == GDI_ERROR )
            {
                ThrowLastOSError( );
            }
            return static_cast<Windows::TextAlignment>( result );
        }
        Windows::TextAlignment SetTextAlignment( Windows::TextAlignment textAlignment ) const
        {
            UINT ta = static_cast<UINT>( textAlignment );
            auto result = SetTextAlign( Value( ), ta );
            if ( result == GDI_ERROR )
            {
                ThrowLastOSError( );
            }
            return static_cast<Windows::TextAlignment>( result );
        }


        int DrawText( LPCWSTR text, int textLength, RECT& rect, DrawTextFlags drawTextFlags ) const
        {
            int result = ::DrawTextW( Value( ), text, textLength, &rect, static_cast<UINT>( drawTextFlags ) );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        int DrawText( LPCSTR text, int textLength, RECT& rect, DrawTextFlags drawTextFlags ) const
        {
            int result = ::DrawTextA( Value( ), text, textLength, &rect, static_cast<UINT>( drawTextFlags ) );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        int DrawText( const std::wstring& text, RECT& rect, DrawTextFlags drawTextFlags ) const
        {
            return DrawText( text.c_str( ), static_cast<int>( text.length( ) ), rect, drawTextFlags );
        }
        int DrawText( const std::string& text, RECT& rect, DrawTextFlags drawTextFlags ) const
        {
            return DrawText( text.c_str( ), static_cast<int>( text.length( ) ), rect, drawTextFlags );
        }


        int DrawText( const wchar_t* text, int textLength, RECT& rect, DrawTextFlags uFormat, DRAWTEXTPARAMS& drawTextParams ) const
        {
            int result = ::DrawTextExW( Value( ), const_cast<wchar_t*>(text), textLength, &rect, UINT( uFormat ), &drawTextParams );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        int DrawText( const char* text, int textLength, RECT& rect, DrawTextFlags uFormat, DRAWTEXTPARAMS& drawTextParams ) const
        {
            int result = ::DrawTextExA( Value( ), const_cast<char*>(text), textLength, &rect, UINT( uFormat ), &drawTextParams );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        void DrawText( int nXStart, int nYStart, LPCWSTR text, int textLength ) const
        {
            if ( ::TextOutW( Value( ), nXStart, nYStart, text, textLength ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void DrawText( int nXStart, int nYStart, LPCSTR text, int textLength ) const
        {
            if ( ::TextOutA( Value( ), nXStart, nYStart, text, textLength ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void DrawText( int nXStart, int nYStart, const std::wstring& text ) const
        {
            DrawText( nXStart, nYStart, text.c_str( ), static_cast<int>( text.length( ) ) );
        }
        void DrawText( int nXStart, int nYStart, const std::string& text ) const
        {
            DrawText( nXStart, nYStart, text.c_str( ), static_cast<int>( text.length( ) ) );
        }
        void DrawText( const POINT& startPosition, const std::wstring& text ) const
        {
            DrawText( startPosition.x, startPosition.y, text.c_str( ), static_cast<int>( text.length( ) ) );
        }
        void DrawText( const POINT& startPosition, const std::string& text ) const
        {
            DrawText( startPosition.x, startPosition.y, text.c_str( ), static_cast<int>( text.length( ) ) );
        }

        SIZE DrawText( int X, int Y, LPCWSTR text, int textLength, int nTabPositions, const LPINT lpnTabStopPositions, int nTabOrigin ) const
        {
            LONG res = ::TabbedTextOutW( Value( ), X, Y, text, textLength, nTabPositions, lpnTabStopPositions, nTabOrigin );
            if ( !res )
            {
                ThrowLastOSError( );
            }
            SIZE result = { LOWORD( res ), HIWORD( res ) };
            return result;
        }
        void DrawText( int X, int Y, UINT fuOptions, const RECT* lprc, LPCWSTR lpString, UINT cbCount, const INT* lpDx ) const
        {
            if ( ::ExtTextOutW( Value( ), X, Y, fuOptions, lprc, lpString, cbCount, lpDx ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        POINT CurrentPosition( ) const
        {
            POINT result = { 0, };
            if ( GetCurrentPositionEx( Value( ), &result ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        void CurrentPosition( POINT& currentPosition ) const
        {
            if ( GetCurrentPositionEx( Value( ), &currentPosition ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        Windows::GraphicsMode GraphicsMode( ) const
        {
            auto gm = GetGraphicsMode( Value( ) );
            if ( !gm )
            {
                ThrowLastOSError( );
            }
            return static_cast<Windows::GraphicsMode>( gm );
        }
        Windows::GraphicsMode SetGraphicsMode( Windows::GraphicsMode newGraphicsMode ) const
        {
            auto gm = ::SetGraphicsMode( Value( ), static_cast<int>( newGraphicsMode ) );
            if ( !gm )
            {
                ThrowLastOSError( );
            }
            return static_cast<Windows::GraphicsMode>( gm );
        }

        Windows::MapMode MapMode( ) const
        {
            auto mm = GetMapMode( Value( ) );
            if ( !mm )
            {
                ThrowLastOSError( );
            }
            return static_cast<Windows::MapMode>( mm );
        }
        Windows::MapMode SetMapMode( Windows::MapMode newMapMode ) const
        {
            auto mm = ::SetMapMode( Value( ), static_cast<int>( newMapMode ) );
            if ( !mm )
            {
                ThrowLastOSError( );
            }
            return static_cast<Windows::MapMode>( mm );
        }

        SIZE ViewportExtent( ) const
        {
            SIZE result = { 0, };
            if ( GetViewportExtEx( Value( ), &result ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        SIZE SetViewportExtent( const SIZE& newViewportExtent ) const
        {
            SIZE result = { 0, };
            if ( SetViewportExtEx( Value( ), newViewportExtent.cx, newViewportExtent.cy, &result ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        SIZE ScaleViewportExtent( int Xnum, int Xdenom, int Ynum, int Ydenom ) const
        {
            SIZE result = { 0, };
            if ( ScaleViewportExtEx( Value( ), Xnum, Xdenom, Ynum, Ydenom, &result ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        POINT ViewportOrigin( ) const
        {
            POINT result = { 0, };
            if ( GetViewportOrgEx( Value( ), &result ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        POINT SetViewportOrigin( const POINT& newViewportOrigin ) const
        {
            POINT result = { 0, };
            if ( SetViewportOrgEx( Value( ), newViewportOrigin.x, newViewportOrigin.y, &result ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        POINT OffsetViewportOrigin( int xOffset, int yOffset ) const
        {
            POINT result = { 0, };
            if ( OffsetViewportOrgEx( Value( ), xOffset, yOffset, &result ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        SIZE WindowExtent( ) const
        {
            SIZE result = { 0, };
            if ( GetWindowExtEx( Value( ), &result ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        SIZE SetWindowExtent( const SIZE& newWindowExtent ) const
        {
            SIZE result = { 0, };
            if ( SetWindowExtEx( Value( ), newWindowExtent.cx, newWindowExtent.cy, &result ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        SIZE ScaleWindowExtent( int Xnum, int Xdenom, int Ynum, int Ydenom ) const
        {
            SIZE result = { 0, };
            if ( ScaleWindowExtEx( Value( ), Xnum, Xdenom, Ynum, Ydenom, &result ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        POINT WindowOrigin( ) const
        {
            POINT result = { 0, };
            if ( GetWindowOrgEx( Value( ), &result ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        POINT SetWindowOrigin( const POINT& newWindowOrigin ) const
        {
            POINT result = { 0, };
            if ( SetWindowOrgEx( Value( ), newWindowOrigin.x, newWindowOrigin.y, &result ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        POINT OffsetWindowOrigin( int xOffset, int yOffset ) const
        {
            POINT result = { 0, };
            if ( OffsetWindowOrgEx( Value( ), xOffset, yOffset, &result ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        void WorldTransform( XFORM& xform ) const
        {
            if ( GetWorldTransform( Value( ), &xform ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        XFORM WorldTransform( ) const
        {
            XFORM xform;
            if ( GetWorldTransform( Value( ), &xform ) == FALSE )
            {
                ThrowLastOSError( );
            }
            return xform;
        }

        void SetWorldTransform( XFORM& xform ) const
        {
            if ( ::SetWorldTransform( Value( ), &xform ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        void ModifyWorldTransform( const XFORM& xform, bool rightMultiply = false ) const
        {
            if ( ::ModifyWorldTransform( Value( ), &xform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        void ResetWorldTransform( ) const
        {
            if ( ::ModifyWorldTransform( Value( ), nullptr, MWT_IDENTITY ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }


        void DrawBitmap( const BitmapHandle& bitmap ) const;
        void DrawBitmap( const BitmapHandle& bitmap, const POINT& position ) const;
        void DrawBitmap( const BitmapHandle& bitmap, const POINT& position, const SIZE size ) const;

        void DrawBitmap( const DeviceContextHandle& source ) const
        {
            auto size = source.ViewportExtent( );
            POINT position = { 0, };
            return DrawBitmap( source, position, size );
        }
        void DrawBitmap( const DeviceContextHandle& source, const POINT& position ) const
        {
            auto size = source.ViewportExtent( );
            return DrawBitmap( source, position, size );
        }
        void DrawBitmap( const DeviceContextHandle& source, const POINT& position, const SIZE size ) const
        {
            if ( ::BitBlt( Value( ), position.x, position.y, size.cx, size.cy, source.Value( ), 0, 0, SRCCOPY ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }



    };

    
    enum class WindowDeviceContextFlags : int
    {
        // Returns a DeviceContext that corresponds to the window 
        // rectangle rather than the client rectangle.
        Window = 0x00000001L,
        // Returns a DeviceContext  from the cache, rather than the OWNDC or 
        // CLASSDC window. Essentially overrides CS_OWNDC and CS_CLASSDC
        Cache = 0x00000002L,
        // Does not reset the attributes of this DeviceContext  to the 
        // default attributes when this DC is released.
        NoResetAttributes = 0x00000004L,
        // Excludes the visible regions of all child windows 
        // below the window identified by hWnd.
        ClipChildren = 0x00000008L,
        // Excludes the visible regions of all sibling windows above 
        // the window identified by hWnd
        ClipSiblings = 0x00000010L,
        // Uses the visible region of the parent window. The parent's 
        // WS_CLIPCHILDREN and CS_PARENTDC style bits are ignored. The origin is 
        // set to the upper-left corner of the window identified by hWnd.
        ParentClip = 0x00000020L,
        // The clipping region identified by hrgnClip is excluded from 
        // the visible region of the returned DeviceContext.
        ExcludeRegion = 0x00000040L,
        // The clipping region identified by hrgnClip is intersected with the 
        // visible region of the returned DeviceContext
        IntersectRegion = 0x00000080L,

        ExcludeUpdate = 0x00000100L,
        //IntersectUpdate  = 0x00000200L,

        // Allows drawing even if there is a LockWindowUpdate call in effect that would 
        // otherwise exclude this window. Used for drawing during tracking.
        LockWindowUpdate = 0x00000400L,
        //Validate         = 0x00200000L
    };
    

    class WindowDeviceContextHandle : public DeviceContextHandle
    {

    public:
        static void CloseHandle( HRGN handle ) noexcept
        {
            DeleteObject( handle );
        }

        typedef DeviceContextHandle Base;
    };


    class PaintDeviceContextHandle : public DeviceContextHandle
    {
        PAINTSTRUCT paintStruct_;
        HWND windowHandle_;
    public:
        typedef DeviceContextHandle Base;

        HW_EXPORT PaintDeviceContextHandle( const Control& control );
        PaintDeviceContextHandle( HWND hWnd )
        {
            windowHandle_ = hWnd;
            auto theHandle = BeginPaint( windowHandle_, &paintStruct_ );
            if ( !theHandle )
            {
                ThrowLastOSError( );
            }
            SetValue( theHandle, true );
            SaveDefaultObjects( );
        }

        ~PaintDeviceContextHandle( )
        {
            HDC hDC = Value( );
            if ( hDC )
            {
                RestoreDefaultObjects( );
            }
            if ( OwnsHandle( ) && hDC )
            {
                EndPaint( windowHandle_, &paintStruct_ );
            }
        }

        

    };


    class MemoryDeviceContextHandle : public DeviceContextHandle
    {
    public:
        typedef DeviceContextHandle Base;
        constexpr MemoryDeviceContextHandle( ) noexcept
        {
        }
        constexpr MemoryDeviceContextHandle(HDC handle, bool ownshandle ) noexcept
            : Base( handle, ownshandle )
        {
        }

        MemoryDeviceContextHandle( const DeviceContextHandle& deviceContext )
        {
            HDC handle = CreateCompatibleDC( deviceContext.Value( ) );
            if ( !handle )
            {
                ThrowLastOSError( );
            }
            SetValue( handle, true );
            SaveDefaultObjects( );
        }
        MemoryDeviceContextHandle( const DeviceContextHandle& deviceContext, const BitmapHandle& bitmap )
            : MemoryDeviceContextHandle( deviceContext )
        {
            SetBitmap( bitmap );
        }
        ~MemoryDeviceContextHandle( ) noexcept
        {
            HDC hDC = Value( );
            if ( hDC )
            {
                RestoreDefaultObjects( );
            }
            if ( OwnsHandle( ) && hDC )
            {
                DeleteDC( hDC );
            }
        }
    };

    inline void DeviceContextHandle::DrawBitmap( const BitmapHandle& bitmap ) const
    {
        POINT position = { 0, };
        SIZE size = bitmap.Size( );
        MemoryDeviceContextHandle mdc( *this, bitmap );
        DrawBitmap( mdc, position, size );
    }
    inline void DeviceContextHandle::DrawBitmap( const BitmapHandle& bitmap, const POINT& position ) const
    {
        MemoryDeviceContextHandle mdc( *this, bitmap );
        SIZE size = bitmap.Size( );
        return DrawBitmap( mdc, position, size );
    }
    inline void DeviceContextHandle::DrawBitmap( const BitmapHandle& bitmap, const POINT& position, const SIZE size ) const
    {
        MemoryDeviceContextHandle mdc( *this, bitmap );
        DrawBitmap( mdc, position, size );
    }




    /*
    class Accelerator : public Handle
    {
    public:
    typedef Handle Base;

    };*/


    class BitmapSelection
    {
        const DeviceContextHandle& deviceContext;
        BitmapHandle previouslySelectedBitmap;
    public:
        BitmapSelection( const DeviceContextHandle& deviceContext, const BitmapHandle& bitmap )
            : deviceContext( deviceContext )
        {
            previouslySelectedBitmap = deviceContext.SetBitmap( bitmap );
        }
        ~BitmapSelection( )
        {
            deviceContext.SetBitmap( previouslySelectedBitmap );
        }
    };


    class BrushSelection
    {
        const DeviceContextHandle& deviceContext_;
        BrushHandle previouslySelectedBrush_;
    public:
        BrushSelection( const DeviceContextHandle& deviceContext, const BrushHandle& brush )
            : deviceContext_( deviceContext )
        {
            previouslySelectedBrush_ = deviceContext_.SetBrush( brush );
        }
        ~BrushSelection( )
        {
            deviceContext_.SetBrush( previouslySelectedBrush_ );
        }
    };


    class PenSelection
    {
        const DeviceContextHandle& deviceContext_;
        PenHandle previouslySelectedPen_;
    public:
        PenSelection( const DeviceContextHandle& deviceContext, const PenHandle& pen )
            : deviceContext_( deviceContext )
        {
            previouslySelectedPen_ = deviceContext.SetPen( pen );
        }
        ~PenSelection( )
        {
            deviceContext_.SetPen( previouslySelectedPen_ );
        }
    };

    class FontSelection
    {
        const DeviceContextHandle& deviceContext_;
        FontHandle previouslySelectedFont_;
    public:
        FontSelection( const DeviceContextHandle& deviceContext, const FontHandle& font )
            : deviceContext_( deviceContext )
        {
            previouslySelectedFont_ = deviceContext.SetFont( font );
        }
        ~FontSelection( )
        {
            deviceContext_.SetFont( previouslySelectedFont_ );
        }
    };



    class RegistryHandle : public Handle<RegistryHandle, HKEY>
    {
    public:
        using Base = Handle<RegistryHandle, HKEY>;
    protected:
        
    public:
        RegistryHandle( )
            : Base( )
        {
        }

        RegistryHandle( void* initialHandleValue, bool ownsValue = true )
            : Base( static_cast<HKEY>(initialHandleValue), ownsValue )
        {
            
        }


        static constexpr HKEY InvalidHandleValue( ) noexcept
        {
            return static_cast<HKEY>(INVALID_HANDLE_VALUE);
        }

        constexpr bool IsValid( ) const noexcept
        {
            return value_ != static_cast<HandleType>( 0 ) && 
                value_ != static_cast<HandleType>( INVALID_HANDLE_VALUE );
        }


        void Close( ) noexcept
        {
            if ( IsValid( ) )
            {
                auto handleValue = value_;
                value_ = this->InvalidHandleValue( );
                if ( OwnsHandle( ) )
                {
                    RegCloseKey( (HKEY)handleValue );
                }
            }
        }


        static RegistryHandle ClassesRoot( )
        {
            RegistryHandle result( (void*)HKEY_CLASSES_ROOT, false );
            return result;
        }

        static RegistryHandle CurrentUser( )
        {
            RegistryHandle result( (void*)HKEY_CURRENT_USER, false );
            return result;
        }

        static RegistryHandle LocalMachine( )
        {
            RegistryHandle result( (void*)HKEY_LOCAL_MACHINE, false );
            return result;
        }

        static RegistryHandle Users( )
        {
            RegistryHandle result( (void*)HKEY_USERS, false );
            return result;
        }

        static RegistryHandle PerformanceData( )
        {
            RegistryHandle result( (void*)HKEY_PERFORMANCE_DATA, false );
            return result;
        }

        static RegistryHandle PerformanceText( )
        {
            RegistryHandle result( (void*)HKEY_PERFORMANCE_TEXT, false );
            return result;
        }

        static RegistryHandle PerformanceNlsText( )
        {
            RegistryHandle result( (void*)HKEY_PERFORMANCE_NLSTEXT, false );
            return result;
        }

        static RegistryHandle CurrentConfig( )
        {
            RegistryHandle result( (void*)HKEY_CURRENT_CONFIG, false );
            return result;
        }

        static RegistryHandle DynamicData( )
        {
            RegistryHandle result( (void*)HKEY_DYN_DATA, false );
            return result;
        }

        static RegistryHandle CurrentUserLocalSettings( )
        {
            RegistryHandle result( (void*)HKEY_CURRENT_USER_LOCAL_SETTINGS, false );
            return result;
        }


        void OverridePredefinedKey( const RegistryHandle& theNewHandle )
        {
            auto self = (HKEY)Value( );
            if ( theNewHandle )
            {
                auto newHandle = (HKEY)theNewHandle.Value( );
                auto result = RegOverridePredefKey( self, newHandle );
                if ( result != ERROR_SUCCESS )
                {
                    ThrowOSError( result );
                }
            }
            else
            {
                auto result = RegOverridePredefKey( self, 0 );
                if ( result != ERROR_SUCCESS )
                {
                    ThrowOSError( result );
                }
            }
        }

        void ResetPredefinedKey( )
        {
            auto self = (HKEY)Value( );
            auto result = RegOverridePredefKey( self, 0 );
            if ( result != ERROR_SUCCESS )
            {
                ThrowOSError( result );
            }
        }

        static RegistryHandle OpenUserClassesRoot( HANDLE hToken, REGSAM desiredAccess )
        {
            HKEY hKey = 0;
            auto rc = RegOpenUserClassesRoot( hToken, 0, desiredAccess, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle OpenCurrentUser( REGSAM desiredAccess )
        {
            HKEY hKey = 0;
            auto rc = RegOpenCurrentUser( desiredAccess, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static void DisablePredefinedCache( )
        {
            auto rc = RegDisablePredefinedCache( );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        static void DisablePredefinedCacheEx( )
        {
            auto rc = RegDisablePredefinedCacheEx( );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
        }

        static RegistryHandle ConnectRegistry( const RegistryHandle& thePredefinedHandle )
        {
            HKEY hKey = 0;
            auto predefinedHandle = (HKEY)thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryW( nullptr, predefinedHandle, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const std::string& theMachineName, const RegistryHandle& thePredefinedHandle )
        {
            HKEY hKey = 0;
            auto predefinedHandle = (HKEY)thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryA( theMachineName.data( ), predefinedHandle, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const std::wstring& theMachineName, const RegistryHandle& thePredefinedHandle )
        {
            HKEY hKey = 0;
            auto predefinedHandle = (HKEY)thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryW( theMachineName.data( ), predefinedHandle, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const char* theMachineName, const RegistryHandle& thePredefinedHandle )
        {
            HKEY hKey = 0;
            auto predefinedHandle = (HKEY)thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryA( theMachineName, predefinedHandle, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const wchar_t* theMachineName, const RegistryHandle& thePredefinedHandle )
        {
            HKEY hKey = 0;
            auto predefinedHandle = (HKEY)thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryW( theMachineName, predefinedHandle, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }


        static RegistryHandle ConnectRegistry( const RegistryHandle& thePredefinedHandle, ULONG theFlags )
        {
            HKEY hKey = 0;
            auto predefinedHandle = (HKEY)thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryExW( nullptr, predefinedHandle, theFlags, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const std::string& theMachineName, const RegistryHandle& thePredefinedHandle, ULONG theFlags )
        {
            HKEY hKey = 0;
            auto predefinedHandle = (HKEY)thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryExA( theMachineName.data( ), predefinedHandle, theFlags, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const std::wstring& theMachineName, const RegistryHandle& thePredefinedHandle, ULONG theFlags )
        {
            HKEY hKey = 0;
            auto predefinedHandle = (HKEY)thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryExW( theMachineName.data( ), predefinedHandle, theFlags, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const char* theMachineName, const RegistryHandle& thePredefinedHandle, ULONG theFlags )
        {
            HKEY hKey = 0;
            auto predefinedHandle = (HKEY)thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryExA( theMachineName, predefinedHandle, theFlags, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle ConnectRegistry( const wchar_t* theMachineName, const RegistryHandle& thePredefinedHandle, ULONG theFlags )
        {
            HKEY hKey = 0;
            auto predefinedHandle = (HKEY)thePredefinedHandle.Value( );
            auto rc = RegConnectRegistryExW( theMachineName, predefinedHandle, theFlags, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const char* theSubKey )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            auto rc = RegCreateKeyA( self, theSubKey, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const wchar_t* theSubKey )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            auto rc = RegCreateKeyW( self, theSubKey, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const std::string& theSubKey )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            auto rc = RegCreateKeyA( self, theSubKey.data( ), &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const std::wstring& theSubKey )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            auto rc = RegCreateKeyW( self, theSubKey.data( ), &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const std::string& theSubKey, const std::string& theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyExA( self, theSubKey.data( ), 0, const_cast<char*>( theClass.data( ) ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const char* theSubKey, const char* theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyExA( self, theSubKey, 0, const_cast<char*>( theClass ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }


        RegistryHandle CreateKey( const std::wstring& theSubKey, const std::wstring& theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyExW( self, theSubKey.data( ), 0, const_cast<wchar_t*>( theClass.data( ) ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const wchar_t* theSubKey, const wchar_t* theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyExW( self, theSubKey, 0, const_cast<wchar_t*>( theClass ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const std::string& theSubKey, const std::string& theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated, HANDLE hTransaction )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyTransactedA( self, theSubKey.data( ), 0, const_cast<char*>( theClass.data( ) ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const char* theSubKey, const char* theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated, HANDLE hTransaction )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyTransactedA( self, theSubKey, 0, const_cast<char*>( theClass ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }


        RegistryHandle CreateKey( const std::wstring& theSubKey, const std::wstring& theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated, HANDLE hTransaction )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyTransactedW( self, theSubKey.data( ), 0, const_cast<wchar_t*>( theClass.data( ) ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle CreateKey( const wchar_t* theSubKey, const wchar_t* theClass, DWORD theOptions, REGSAM desiredAccess, LPSECURITY_ATTRIBUTES theSecurityAttributes, bool& keyWasCreated, HANDLE hTransaction )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            DWORD disposition = 0;
            auto rc = RegCreateKeyTransactedW( self, theSubKey, 0, const_cast<wchar_t*>( theClass ), theOptions, desiredAccess, theSecurityAttributes, &hKey, &disposition, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            keyWasCreated = disposition == REG_CREATED_NEW_KEY;
            RegistryHandle result( hKey, true );
            return result;
        }


        RegistryHandle& DeleteKey( const std::string& theSubKey )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyA( self, theSubKey.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKey( const char* theSubKey )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyA( self, theSubKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }


        RegistryHandle& DeleteKey( const std::wstring& theSubKey )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            auto rc = RegDeleteKeyW( self, theSubKey.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKey( const wchar_t* theSubKey )
        {
            auto self = (HKEY)Value( );
            HKEY hKey = 0;
            auto rc = RegDeleteKeyW( self, theSubKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKey( const std::string& theSubKey, REGSAM desiredRegistryView )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyExA( self, theSubKey.data( ), desiredRegistryView, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKey( const char* theSubKey, REGSAM desiredRegistryView )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyExA( self, theSubKey, desiredRegistryView, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKey( const std::wstring& theSubKey, REGSAM desiredRegistryView )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyExW( self, theSubKey.data( ), desiredRegistryView, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKey( const wchar_t* theSubKey, REGSAM desiredRegistryView )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyExW( self, theSubKey, desiredRegistryView, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKey( const std::string& theSubKey, REGSAM desiredRegistryView, HANDLE hTransaction )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyTransactedA( self, theSubKey.data( ), desiredRegistryView, 0, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKey( const char* theSubKey, REGSAM desiredRegistryView, HANDLE hTransaction )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyTransactedA( self, theSubKey, desiredRegistryView, 0, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKey( const std::wstring& theSubKey, REGSAM desiredRegistryView, HANDLE hTransaction )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyTransactedW( self, theSubKey.data( ), desiredRegistryView, 0, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKey( const wchar_t* theSubKey, REGSAM desiredRegistryView, HANDLE hTransaction )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyTransactedW( self, theSubKey, desiredRegistryView, 0, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKeyValue( )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyValueW( self, nullptr, nullptr );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKeyValue( const std::string& theValueName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyValueA( self, nullptr, theValueName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKeyValue( const char* theValueName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyValueA( self, nullptr, theValueName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKeyValue( const std::string& theSubKey, const std::string& theValueName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyValueA( self, theSubKey.data( ), theValueName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKeyValue( const char* theSubKey, const char* theValueName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyValueA( self, theSubKey, theValueName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKeyValue( const std::wstring& theValueName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyValueW( self, nullptr, theValueName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKeyValue( const wchar_t* theValueName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyValueW( self, nullptr, theValueName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKeyValue( const std::wstring& theSubKey, const std::wstring& theValueName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyValueW( self, theSubKey.data( ), theValueName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteKeyValue( const wchar_t* theSubKey, const wchar_t* theValueName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteKeyValueW( self, theSubKey, theValueName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DisableReflectionKey( )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDisableReflectionKey( self );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& EnableReflectionKey( )
        {
            auto self = (HKEY)Value( );
            auto rc = RegEnableReflectionKey( self );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        bool QueryReflectionKey( ) const
        {
            auto self = (HKEY)Value( );
            BOOL isReflectionDisabled = FALSE;
            auto rc = RegQueryReflectionKey( self, &isReflectionDisabled );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return isReflectionDisabled != FALSE;
        }

        bool IsReflectionDisabled( ) const
        {
            return QueryReflectionKey( );
        }

        bool IsReflectionEnabled( ) const
        {
            return QueryReflectionKey( ) == false;
        }

        RegistryHandle& DeleteValue( )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteValueW( self, nullptr );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteValue( const std::string& theValueName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteValueA( self, theValueName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteValue( const char* theValueName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteValueA( self, theValueName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }


        RegistryHandle& DeleteValue( const std::wstring& theValueName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteValueW( self, theValueName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& DeleteValue( const wchar_t* theValueName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegDeleteValueW( self, theValueName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }


        long EnumKey( DWORD theIndex, char* theNameBuffer, DWORD& theSizeOfTheNameBuffer, char* theClassNameBuffer, DWORD& theSizeOfTheClassNameBuffer, FILETIME& theLastWriteTime ) const
        {
            auto self = (HKEY)Value( );
            auto rc = RegEnumKeyExA( self, theIndex, theNameBuffer, &theSizeOfTheNameBuffer, nullptr, theClassNameBuffer, &theSizeOfTheClassNameBuffer, &theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long EnumKey( DWORD theIndex, char* theNameBuffer, DWORD& theSizeOfTheNameBuffer, FILETIME& theLastWriteTime ) const
        {
            auto self = (HKEY)Value( );
            auto rc = RegEnumKeyExA( self, theIndex, theNameBuffer, &theSizeOfTheNameBuffer, nullptr, nullptr, 0, &theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
            {
                ThrowOSError( rc );
            }
            return rc;
        }


        long EnumKey( DWORD theIndex, wchar_t* theNameBuffer, DWORD& theSizeOfTheNameBuffer, wchar_t* theClassNameBuffer, DWORD& theSizeOfTheClassNameBuffer, FILETIME& theLastWriteTime ) const
        {
            auto self = (HKEY)Value( );
            auto rc = RegEnumKeyExW( self, theIndex, theNameBuffer, &theSizeOfTheNameBuffer, nullptr, theClassNameBuffer, &theSizeOfTheClassNameBuffer, &theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long EnumKey( DWORD theIndex, wchar_t* theNameBuffer, DWORD& theSizeOfTheNameBuffer, FILETIME& theLastWriteTime ) const
        {
            auto self = (HKEY)Value( );
            auto rc = RegEnumKeyExW( self, theIndex, theNameBuffer, &theSizeOfTheNameBuffer, nullptr, nullptr, 0, &theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
            {
                ThrowOSError( rc );
            }
            return rc;
        }


        long EnumKeyNames( std::vector<std::wstring>& result )
        {
            long rc = ERROR_SUCCESS;
            DWORD index = 0;
            wchar_t nameBuffer[256] = { 0, };
            result.clear( );
            auto self = (HKEY)Value( );
            do
            {
                DWORD sizeOfTheNameBuffer = 256;
                rc = RegEnumKeyExW( self, index, nameBuffer, &sizeOfTheNameBuffer, nullptr, nullptr, 0, nullptr );
                if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
                {
                    ThrowOSError( rc );
                }
                else if ( rc == ERROR_SUCCESS )
                {
                    std::wstring name( nameBuffer, static_cast<size_t>( sizeOfTheNameBuffer ) );
                    result.push_back( name );
                }
                index++;
            } while ( rc == ERROR_SUCCESS );
            return rc;
        }


        long EnumKeyNames( std::vector<std::string>& result )
        {
            long rc = ERROR_SUCCESS;
            DWORD index = 0;
            char nameBuffer[256] = { 0, };
            result.clear( );
            auto self = (HKEY)Value( );
            do
            {
                DWORD sizeOfTheNameBuffer = 256;
                rc = RegEnumKeyExA( self, index, nameBuffer, &sizeOfTheNameBuffer, nullptr, nullptr, 0, nullptr );
                if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
                {
                    ThrowOSError( rc );
                }
                else if ( rc == ERROR_SUCCESS )
                {
                    std::string name( nameBuffer, static_cast<size_t>( sizeOfTheNameBuffer ) );
                    result.push_back( name );
                }
                index++;
            } while ( rc == ERROR_SUCCESS );
            return rc;
        }


        long EnumValue( DWORD theIndex, char* theNameBuffer, DWORD& theSizeOfTheNameBuffer, DWORD& theType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = (HKEY)Value( );
            auto rc = RegEnumValueA( self, theIndex, theNameBuffer, &theSizeOfTheNameBuffer, nullptr, &theType, (LPBYTE)theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long EnumValue( DWORD theIndex, wchar_t* theNameBuffer, DWORD& theSizeOfTheNameBuffer, DWORD& theType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = (HKEY)Value( );
            auto rc = RegEnumValueW( self, theIndex, theNameBuffer, &theSizeOfTheNameBuffer, nullptr, &theType, (LPBYTE)theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_NO_MORE_ITEMS )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        RegistryHandle& FlushKey( )
        {
            auto self = (HKEY)Value( );
            auto rc = RegFlushKey( self );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        long GetKeySecurity( SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR theSecurityDescriptor, DWORD& theSizeOfTheSecurityDescriptor )
        {
            auto self = (HKEY)Value( );
            auto rc = RegGetKeySecurity( self, SecurityInformation, theSecurityDescriptor, &theSizeOfTheSecurityDescriptor );
            if ( rc != ERROR_SUCCESS && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        RegistryHandle& LoadKey( const std::string& theSubKey, const std::string& theFilename )
        {
            auto self = (HKEY)Value( );
            auto rc = RegLoadKeyA( self, theSubKey.data( ), theFilename.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& LoadKey( const char* theSubKey, const char* theFilename )
        {
            auto self = (HKEY)Value( );
            auto rc = RegLoadKeyA( self, theSubKey, theFilename );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& LoadKey( const std::string& theFilename )
        {
            auto self = (HKEY)Value( );
            auto rc = RegLoadKeyA( self, nullptr, theFilename.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& LoadKey( const char* theFilename )
        {
            auto self = (HKEY)Value( );
            auto rc = RegLoadKeyA( self, nullptr, theFilename );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& LoadKey( const std::wstring& theSubKey, const std::wstring& theFilename )
        {
            auto self = (HKEY)Value( );
            auto rc = RegLoadKeyW( self, theSubKey.data( ), theFilename.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& LoadKey( const wchar_t* theSubKey, const wchar_t* theFilename )
        {
            auto self = (HKEY)Value( );
            auto rc = RegLoadKeyW( self, theSubKey, theFilename );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& LoadKey( const std::wstring& theFilename )
        {
            auto self = (HKEY)Value( );
            auto rc = RegLoadKeyW( self, nullptr, theFilename.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& LoadKey( const wchar_t* theFilename )
        {
            auto self = (HKEY)Value( );
            auto rc = RegLoadKeyW( self, nullptr, theFilename );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        static RegistryHandle LoadAppKey( const std::string& theFilename, REGSAM desiredAccess, DWORD theOptions )
        {
            HKEY hKey = 0;
            auto rc = RegLoadAppKeyA( theFilename.data( ), &hKey, desiredAccess, theOptions, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle LoadAppKey( const char* theFilename, REGSAM desiredAccess, DWORD theOptions )
        {
            HKEY hKey = 0;
            auto rc = RegLoadAppKeyA( theFilename, &hKey, desiredAccess, theOptions, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle LoadAppKey( const std::wstring& theFilename, REGSAM desiredAccess, DWORD theOptions )
        {
            HKEY hKey = 0;
            auto rc = RegLoadAppKeyW( theFilename.data( ), &hKey, desiredAccess, theOptions, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        static RegistryHandle LoadAppKey( const wchar_t* theFilename, REGSAM desiredAccess, DWORD theOptions )
        {
            HKEY hKey = 0;
            auto rc = RegLoadAppKeyW( theFilename, &hKey, desiredAccess, theOptions, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle& NotifyChangeKeyValue( bool watchSubtree, DWORD dwNotifyFilter, HANDLE hEvent, bool asynchronous )
        {
            auto self = (HKEY)Value( );
            auto rc = RegNotifyChangeKeyValue( self, watchSubtree ? TRUE : FALSE, dwNotifyFilter, hEvent, asynchronous ? TRUE : FALSE );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        bool KeyExists( const std::string& theSubKey ) const
        {
            if ( theSubKey.length( ) )
            {
                HKEY hKey = 0;
                auto self = (HKEY)Value( );
                auto rc = RegOpenKeyExA( self, theSubKey.data( ), 0, KEY_READ, &hKey );
                if ( rc == ERROR_SUCCESS )
                {
                    RegCloseKey( hKey );
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                throw ArgumentException( L"Invalid key name", L"theSubKey" );
            }
        }

        bool KeyExists( const std::wstring& theSubKey ) const
        {
            if ( theSubKey.length( ) )
            {
                HKEY hKey = 0;
                auto self = (HKEY)Value( );
                auto rc = RegOpenKeyExW( self, theSubKey.data( ), 0, KEY_READ, &hKey );
                if ( rc == ERROR_SUCCESS )
                {
                    RegCloseKey( hKey );
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                throw ArgumentException( L"Invalid key name", L"theSubKey" );
            }
        }


        RegistryHandle OpenKey( const std::string& theSubKey, REGSAM desiredAccess ) const
        {
            HKEY hKey = 0;
            auto self = Value( );
            if ( self == HKEY_CLASSES_ROOT && theSubKey.data( ) == nullptr )
            {
                return RegistryHandle( HKEY_CLASSES_ROOT, false );
            }
            auto rc = RegOpenKeyExA( self, theSubKey.data( ), 0, desiredAccess, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle OpenKey( const char* theSubKey, REGSAM desiredAccess ) const
        {
            HKEY hKey = 0;
            auto self = (HKEY)Value( );
            if ( self == HKEY_CLASSES_ROOT && theSubKey == nullptr )
            {
                return RegistryHandle( HKEY_CLASSES_ROOT, false );
            }
            auto rc = RegOpenKeyExA( self, theSubKey, 0, desiredAccess, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }


        RegistryHandle OpenKey( const std::wstring& theSubKey, REGSAM desiredAccess ) const
        {
            HKEY hKey = 0;
            auto self = (HKEY)Value( );
            if ( self == HKEY_CLASSES_ROOT && theSubKey.data( ) == nullptr )
            {
                return RegistryHandle( HKEY_CLASSES_ROOT, false );
            }
            auto rc = RegOpenKeyExW( self, theSubKey.data( ), 0, desiredAccess, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle OpenKey( const wchar_t* theSubKey, REGSAM desiredAccess ) const
        {
            HKEY hKey = 0;
            auto self = (HKEY)Value( );
            if ( self == HKEY_CLASSES_ROOT && theSubKey == nullptr )
            {
                return RegistryHandle( HKEY_CLASSES_ROOT, false );
            }
            auto rc = RegOpenKeyExW( self, theSubKey, 0, desiredAccess, &hKey );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle OpenKey( const std::string& theSubKey, REGSAM desiredAccess, HANDLE hTransaction ) const
        {
            HKEY hKey = 0;
            auto self = (HKEY)Value( );
            auto rc = RegOpenKeyTransactedA( self, theSubKey.data( ), 0, desiredAccess, &hKey, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle OpenKey( const char* theSubKey, REGSAM desiredAccess, HANDLE hTransaction ) const
        {
            HKEY hKey = 0;
            auto self = (HKEY)Value( );
            auto rc = RegOpenKeyTransactedA( self, theSubKey, 0, desiredAccess, &hKey, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }


        RegistryHandle OpenKey( const std::wstring& theSubKey, REGSAM desiredAccess, HANDLE hTransaction )
        {
            HKEY hKey = 0;
            auto self = (HKEY)Value( );
            auto rc = RegOpenKeyTransactedW( self, theSubKey.data( ), 0, desiredAccess, &hKey, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        RegistryHandle OpenKey( const wchar_t* theSubKey, REGSAM desiredAccess, HANDLE hTransaction )
        {
            HKEY hKey = 0;
            auto self = (HKEY)Value( );
            auto rc = RegOpenKeyTransactedW( self, theSubKey, 0, desiredAccess, &hKey, hTransaction, 0 );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            RegistryHandle result( hKey, true );
            return result;
        }

        long QueryInfoKey( char* theClassNameBuffer, DWORD& theSizeOfTheClassNameBuffer,
            DWORD& theNumberOfSubKeys, DWORD& theMaxSubKeyLen, DWORD& theMaxClassLen, DWORD& theNumberOfValues,
            DWORD& theMaxValueNameLen, DWORD& theMaxValueLen, DWORD& theSecurityDescriptorSize, FILETIME& theLastWriteTime )
        {
            auto self = (HKEY)Value( );
            auto rc = RegQueryInfoKeyA( self, theClassNameBuffer, &theSizeOfTheClassNameBuffer, nullptr,
                &theNumberOfSubKeys, &theMaxSubKeyLen, &theMaxClassLen, &theNumberOfValues,
                &theMaxValueNameLen, &theMaxValueLen, &theSecurityDescriptorSize, &theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryInfoKey( char* theClassNameBuffer, DWORD* theSizeOfTheClassNameBuffer,
            DWORD* theNumberOfSubKeys, DWORD* theMaxSubKeyLen, DWORD* theMaxClassLen, DWORD* theNumberOfValues,
            DWORD* theMaxValueNameLen, DWORD* theMaxValueLen, DWORD* theSecurityDescriptorSize, FILETIME* theLastWriteTime )
        {
            auto self = (HKEY)Value( );
            auto rc = RegQueryInfoKeyA( self, theClassNameBuffer, theSizeOfTheClassNameBuffer, nullptr,
                theNumberOfSubKeys, theMaxSubKeyLen, theMaxClassLen, theNumberOfValues,
                theMaxValueNameLen, theMaxValueLen, theSecurityDescriptorSize, theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA )
            {
                ThrowOSError( rc );
            }
            return rc;
        }



        long QueryInfoKey( wchar_t* theClassNameBuffer, DWORD& theSizeOfTheClassNameBuffer,
            DWORD& theNumberOfSubKeys, DWORD& theMaxSubKeyLen, DWORD& theMaxClassLen, DWORD& theNumberOfValues,
            DWORD& theMaxValueNameLen, DWORD& theMaxValueLen, DWORD& theSecurityDescriptorSize, FILETIME& theLastWriteTime )
        {
            auto self = (HKEY)Value( );
            auto rc = RegQueryInfoKeyW( self, theClassNameBuffer, &theSizeOfTheClassNameBuffer, nullptr,
                &theNumberOfSubKeys, &theMaxSubKeyLen, &theMaxClassLen, &theNumberOfValues,
                &theMaxValueNameLen, &theMaxValueLen, &theSecurityDescriptorSize, &theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryInfoKey( wchar_t* theClassNameBuffer, DWORD* theSizeOfTheClassNameBuffer,
            DWORD* theNumberOfSubKeys, DWORD* theMaxSubKeyLen, DWORD* theMaxClassLen, DWORD* theNumberOfValues,
            DWORD* theMaxValueNameLen, DWORD* theMaxValueLen, DWORD* theSecurityDescriptorSize, FILETIME* theLastWriteTime )
        {
            auto self = (HKEY)Value( );
            auto rc = RegQueryInfoKeyW( self, theClassNameBuffer, theSizeOfTheClassNameBuffer, nullptr,
                theNumberOfSubKeys, theMaxSubKeyLen, theMaxClassLen, theNumberOfValues,
                theMaxValueNameLen, theMaxValueLen, theSecurityDescriptorSize, theLastWriteTime );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryMultipleValues( PVALENTA theValueList, DWORD theNumberOfEntriesInTheValueList, char* theBuffer, DWORD& theBufferSize )
        {
            auto self = (HKEY)Value( );
            auto rc = RegQueryMultipleValuesA( self, theValueList, theNumberOfEntriesInTheValueList, theBuffer, &theBufferSize );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryMultipleValues( PVALENTW theValueList, DWORD theNumberOfEntriesInTheValueList, wchar_t* theBuffer, DWORD& theBufferSize )
        {
            auto self = (HKEY)Value( );
            auto rc = RegQueryMultipleValuesW( self, theValueList, theNumberOfEntriesInTheValueList, theBuffer, &theBufferSize );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryValue( const std::string& theValueName, DWORD& theValueType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = (HKEY)Value( );
            auto rc = RegQueryValueExA( self, theValueName.data( ), nullptr, &theValueType, (LPBYTE)theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryValue( const char* theValueName, DWORD& theValueType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = (HKEY)Value( );
            auto rc = RegQueryValueExA( self, theValueName, nullptr, &theValueType, (LPBYTE)theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryValue( const std::wstring& theValueName, DWORD& theValueType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = (HKEY)Value( );
            auto rc = RegQueryValueExW( self, theValueName.data( ), nullptr, &theValueType, (LPBYTE)theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryValue( const wchar_t* theValueName, DWORD& theValueType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = (HKEY)Value( );
            auto rc = RegQueryValueExW( self, theValueName, nullptr, &theValueType, (LPBYTE)theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }

        long QueryValue( DWORD& theValueType, void* theDataBuffer, DWORD& theSizeOfTheDataBuffer ) const
        {
            auto self = (HKEY)Value( );
            auto rc = RegQueryValueExW( self, nullptr, nullptr, &theValueType, (LPBYTE)theDataBuffer, &theSizeOfTheDataBuffer );
            if ( rc != ERROR_SUCCESS && rc != ERROR_MORE_DATA && rc != ERROR_INSUFFICIENT_BUFFER )
            {
                ThrowOSError( rc );
            }
            return rc;
        }


    private:
        std::wstring ToString( const std::vector<char>& theData )
        {
            std::wstring result;
            size_t length = theData.size( ) / 2;
            if ( length )
            {
                auto data = (const wchar_t*)theData.data( );
                while ( ( length ) && ( data[length - 1] == 0 ) )
                {
                    length--;
                }
                if ( length )
                {
                    result = std::wstring( data, length );
                }
            }
            return result;
        }


        bool ToBoolean( DWORD theValueType, const std::vector<char>& theData )
        {
            bool result = false;
            switch ( theValueType )
            {
                case REG_DWORD:
                case REG_QWORD:
                case REG_BINARY:
                {
                    switch ( theData.size( ) )
                    {
                        case 1:
                        {
                            auto data = (const char*)theData.data( );
                            result = *data ? true : false;
                        }
                        break;
                        case 2:
                        {
                            auto data = (const short*)theData.data( );
                            result = *data ? true : false;
                        }
                        break;
                        case 4:
                        {
                            auto data = (const int*)theData.data( );
                            result = *data ? true : false;
                        }
                        break;
                        case 8:
                        {
                            auto data = (const long long*)theData.data( );
                            result = *data ? true : false;
                        }
                        break;
                    }
                }
                break;
                case REG_EXPAND_SZ:
                case REG_MULTI_SZ:
                case REG_SZ:
                {
                    auto s = ToString( theData );
                    result = Common::Core::ToBoolean( s );
                }
                break;
            }
            return result;
        }

        int ToInt32( DWORD theValueType, const std::vector<char>& theData )
        {
            int result = 0;
            switch ( theValueType )
            {
                case REG_DWORD:
                case REG_QWORD:
                case REG_BINARY:
                {
                    switch ( theData.size( ) )
                    {
                        case 1:
                        {
                            auto data = (const char*)theData.data( );
                            result = static_cast<int>( *data );
                        }
                        break;
                        case 2:
                        {
                            auto data = (const short*)theData.data( );
                            result = static_cast<int>( *data );
                        }
                        break;
                        case 4:
                        {
                            auto data = (const int*)theData.data( );
                            result = static_cast<int>( *data );
                        }
                        break;
                        case 8:
                        {
                            auto data = (const long long*)theData.data( );
                            result = static_cast<int>( *data );
                        }
                        break;
                    }
                }
                break;
                case REG_EXPAND_SZ:
                case REG_MULTI_SZ:
                case REG_SZ:
                {
                    auto s = ToString( theData );
                    result = Common::Core::ToInt32( s );
                }
                break;
            }
            return result;
        }

        unsigned int ToUInt32( DWORD theValueType, const std::vector<char>& theData )
        {
            unsigned int result = 0;
            switch ( theValueType )
            {
                case REG_DWORD:
                case REG_QWORD:
                case REG_BINARY:
                {
                    switch ( theData.size( ) )
                    {
                        case 1:
                        {
                            auto data = (const unsigned char*)theData.data( );
                            result = static_cast<unsigned int>( *data );
                        }
                        break;
                        case 2:
                        {
                            auto data = (const unsigned short*)theData.data( );
                            result = static_cast<unsigned int>( *data );
                        }
                        break;
                        case 4:
                        {
                            auto data = (const unsigned int*)theData.data( );
                            result = static_cast<unsigned int>( *data );
                        }
                        break;
                        case 8:
                        {
                            auto data = ( const unsigned long long* )theData.data( );
                            result = static_cast<unsigned int>( *data );
                        }
                        break;
                    }
                }
                break;
                case REG_EXPAND_SZ:
                case REG_MULTI_SZ:
                case REG_SZ:
                {
                    auto s = ToString( theData );
                    result = Common::Core::ToUInt32( s );
                }
                break;
            }
            return result;
        }

        long long ToInt64( DWORD theValueType, const std::vector<char>& theData )
        {
            long long result = 0;
            switch ( theValueType )
            {
                case REG_DWORD:
                case REG_QWORD:
                case REG_BINARY:
                {
                    switch ( theData.size( ) )
                    {
                        case 1:
                        {
                            auto data = (const char*)theData.data( );
                            result = static_cast<long long>( *data );
                        }
                        break;
                        case 2:
                        {
                            auto data = (const short*)theData.data( );
                            result = static_cast<long long>( *data );
                        }
                        break;
                        case 4:
                        {
                            auto data = (const int*)theData.data( );
                            result = static_cast<long long>( *data );
                        }
                        break;
                        case 8:
                        {
                            auto data = (const long long*)theData.data( );
                            result = static_cast<long long>( *data );
                        }
                        break;
                    }
                }
                break;
                case REG_EXPAND_SZ:
                case REG_MULTI_SZ:
                case REG_SZ:
                {
                    auto s = ToString( theData );
                    result = Common::Core::ToInt64( s );
                }
                break;
            }
            return result;
        }

        unsigned long long ToUInt64( DWORD theValueType, const std::vector<char>& theData )
        {
            unsigned long long result = 0;
            switch ( theValueType )
            {
                case REG_DWORD:
                case REG_QWORD:
                case REG_BINARY:
                {
                    switch ( theData.size( ) )
                    {
                        case 1:
                        {
                            auto data = (const unsigned char*)theData.data( );
                            result = static_cast<unsigned long long>( *data );
                        }
                        break;
                        case 2:
                        {
                            auto data = (const unsigned short*)theData.data( );
                            result = static_cast<unsigned long long>( *data );
                        }
                        break;
                        case 4:
                        {
                            auto data = (const unsigned int*)theData.data( );
                            result = static_cast<unsigned long long>( *data );
                        }
                        break;
                        case 8:
                        {
                            auto data = ( const unsigned long long* )theData.data( );
                            result = static_cast<unsigned long long>( *data );
                        }
                        break;
                    }
                }
                break;
                case REG_EXPAND_SZ:
                case REG_MULTI_SZ:
                case REG_SZ:
                {
                    auto s = ToString( theData );
                    result = Common::Core::ToUInt64( s );
                }
                break;
            }
            return result;
        }

        char ToSByte( DWORD theValueType, const std::vector<char>& theData )
        {
            return static_cast<char>( ToInt32( theValueType, theData ) );
        }

        unsigned char ToByte( DWORD theValueType, const std::vector<char>& theData )
        {
            return static_cast<unsigned char>( ToUInt32( theValueType, theData ) );
        }

        short ToInt16( DWORD theValueType, const std::vector<char>& theData )
        {
            return static_cast<char>( ToInt32( theValueType, theData ) );
        }

        unsigned short ToUInt16( DWORD theValueType, const std::vector<char>& theData )
        {
            return static_cast<unsigned char>( ToUInt32( theValueType, theData ) );
        }

        double ToDouble( DWORD theValueType, const std::vector<char>& theData )
        {
            auto v = ToUInt64( theValueType, theData );
            double result = *(double*)&v;
            return result;
        }

        float ToSingle( DWORD theValueType, const std::vector<char>& theData )
        {
            auto v = ToUInt32( theValueType, theData );
            float result = *(float*)&v;
            return result;
        }

        std::wstring ToString( DWORD theValueType, const std::vector<char>& theData )
        {
            std::wstring result;
            switch ( theValueType )
            {
                case REG_EXPAND_SZ:
                case REG_MULTI_SZ:
                case REG_SZ:
                case REG_BINARY:
                {
                    size_t length = theData.size( ) / 2;
                    if ( length )
                    {
                        auto data = (const wchar_t*)theData.data( );
                        while ( ( length ) && ( data[length - 1] == 0 ) )
                        {
                            length--;
                        }
                        if ( length )
                        {
                            result = std::wstring( data, length );
                        }
                    }
                }
                break;
                case REG_DWORD:
                {
                    size_t length = theData.size( );
                    if ( length == sizeof( int ) )
                    {
                        auto data = (const int*)theData.data( );
                        result = std::to_wstring( *data );
                    }
                }

                break;
                case REG_QWORD:
                {
                    size_t length = theData.size( );
                    if ( length == sizeof( long long ) )
                    {
                        auto data = (const long long*)theData.data( );
                        result = std::to_wstring( *data );
                    }
                }
                break;

            }
            return result;
        }

    public:
        bool ReadValue( const wchar_t* theValueName, DWORD& theValueType, std::vector<char>& theData )
        {
            DWORD sizeOfTheDataBuffer = 128 * sizeof( WCHAR );
            theData.clear( );
            theData.resize( sizeOfTheDataBuffer );
            auto self = (HKEY)Value( );
            auto rc = RegQueryValueExW( self, theValueName, nullptr, &theValueType, (LPBYTE)theData.data( ), &sizeOfTheDataBuffer );
            if ( rc == ERROR_SUCCESS )
            {
                theData.resize( sizeOfTheDataBuffer );
            }
            else if ( rc == ERROR_FILE_NOT_FOUND )
            {
                return false;
            }
            else
            {
                if ( rc == ERROR_MORE_DATA )
                {
                    theData.resize( sizeOfTheDataBuffer );
                    rc = RegQueryValueExW( self, nullptr, nullptr, &theValueType, (LPBYTE)theData.data( ), &sizeOfTheDataBuffer );
                    if ( rc != ERROR_SUCCESS )
                    {
                        ThrowOSError( rc );
                    }
                }

                else
                {
                    ThrowOSError( rc );
                }
            }
            return true;
        }


        bool ReadBoolean( const wchar_t* theValueName, bool& theResult )
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToBoolean( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadSByte( const wchar_t* theValueName, char& theResult )
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToSByte( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadByte( const wchar_t* theValueName, unsigned char& theResult )
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToByte( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadInt16( const wchar_t* theValueName, short& theResult )
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToInt16( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadUInt16( const wchar_t* theValueName, unsigned short& theResult )
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToUInt16( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }


        bool ReadInt32( const wchar_t* theValueName, int& theResult )
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToInt32( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadUInt32( const wchar_t* theValueName, unsigned int& theResult )
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToUInt32( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadInt64( const wchar_t* theValueName, long long& theResult )
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToInt64( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadUInt64( const wchar_t* theValueName, unsigned long long& theResult )
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToUInt64( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadSingle( const wchar_t* theValueName, float& theResult )
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToSingle( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }

        bool ReadDouble( const wchar_t* theValueName, double& theResult )
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToDouble( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }



        bool ReadString( const wchar_t* theValueName, std::wstring& theResult )
        {
            DWORD valueType;
            std::vector<char> data;
            if ( ReadValue( theValueName, valueType, data ) )
            {
                theResult = ToString( valueType, data );
                return true;
            }
            else
            {
                return false;
            }
        }



        RegistryHandle& ReplaceKey( const std::string& theSubKey, const std::string& newFile, const std::string& oldFile )
        {
            auto self = (HKEY)Value( );
            auto rc = RegReplaceKeyA( self, theSubKey.data( ), newFile.data( ), oldFile.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& ReplaceKey( const char* theSubKey, const char* newFile, const char* oldFile )
        {
            auto self = (HKEY)Value( );
            auto rc = RegReplaceKeyA( self, theSubKey, newFile, oldFile );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& ReplaceKey( const std::string& newFile, const std::string& oldFile )
        {
            auto self = (HKEY)Value( );
            auto rc = RegReplaceKeyA( self, nullptr, newFile.data( ), oldFile.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& ReplaceKey( const char* newFile, const char* oldFile )
        {
            auto self = (HKEY)Value( );
            auto rc = RegReplaceKeyA( self, nullptr, newFile, oldFile );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }


        RegistryHandle& ReplaceKey( const std::wstring& theSubKey, const std::wstring& newFile, const std::wstring& oldFile )
        {
            auto self = (HKEY)Value( );
            auto rc = RegReplaceKeyW( self, theSubKey.data( ), newFile.data( ), oldFile.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& ReplaceKey( const wchar_t* theSubKey, const wchar_t* newFile, const wchar_t* oldFile )
        {
            auto self = (HKEY)Value( );
            auto rc = RegReplaceKeyW( self, theSubKey, newFile, oldFile );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& ReplaceKey( const std::wstring& newFile, const std::wstring& oldFile )
        {
            auto self = (HKEY)Value( );
            auto rc = RegReplaceKeyW( self, nullptr, newFile.data( ), oldFile.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& ReplaceKey( const wchar_t* newFile, const wchar_t* oldFile )
        {
            auto self = (HKEY)Value( );
            auto rc = RegReplaceKeyW( self, nullptr, newFile, oldFile );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& RestoreKey( const std::string& oldFile, DWORD theFlags )
        {
            auto self = (HKEY)Value( );
            auto rc = RegRestoreKeyA( self, oldFile.data( ), theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }


        RegistryHandle& RestoreKey( const char* oldFile, DWORD theFlags )
        {
            auto self = (HKEY)Value( );
            auto rc = RegRestoreKeyA( self, oldFile, theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& RestoreKey( const std::wstring& oldFile, DWORD theFlags )
        {
            auto self = (HKEY)Value( );
            auto rc = RegRestoreKeyW( self, oldFile.data( ), theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& RestoreKey( const wchar_t* oldFile, DWORD theFlags )
        {
            auto self = (HKEY)Value( );
            auto rc = RegRestoreKeyW( self, oldFile, theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& RenameKey( const std::wstring& oldSubKeyName, const std::wstring& newSubKeyName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegRenameKey( self, oldSubKeyName.data( ), newSubKeyName.data( ) );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& RenameKey( const std::string& oldSubKeyName, const std::string& newSubKeyName )
        {
            auto on = ToWideString( oldSubKeyName );
            auto nn = ToWideString( newSubKeyName );
            RenameKey( on, nn );
            return *this;
        }


        RegistryHandle& RenameKey( const wchar_t* oldSubKeyName, const wchar_t* newSubKeyName )
        {
            auto self = (HKEY)Value( );
            auto rc = RegRenameKey( self, oldSubKeyName, newSubKeyName );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& SaveKey( const std::string& theFilename, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr )
        {
            auto self = (HKEY)Value( );
            auto rc = RegSaveKeyA( self, theFilename.data( ), theSecurityAttributes );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& SaveKey( const char* theFilename, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr )
        {
            auto self = (HKEY)Value( );
            auto rc = RegSaveKeyA( self, theFilename, theSecurityAttributes );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& SaveKey( const std::wstring& theFilename, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr )
        {
            auto self = (HKEY)Value( );
            auto rc = RegSaveKeyW( self, theFilename.data( ), theSecurityAttributes );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& SaveKey( const wchar_t* theFilename, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr )
        {
            auto self = (HKEY)Value( );
            auto rc = RegSaveKeyW( self, theFilename, theSecurityAttributes );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& SaveKey( const std::string& theFilename, DWORD theFlags, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr )
        {
            auto self = (HKEY)Value( );
            auto rc = RegSaveKeyExA( self, theFilename.data( ), theSecurityAttributes, theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& SaveKey( const char* theFilename, DWORD theFlags, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr )
        {
            auto self = (HKEY)Value( );
            auto rc = RegSaveKeyExA( self, theFilename, theSecurityAttributes, theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }


        RegistryHandle& SaveKey( const std::wstring& theFilename, DWORD theFlags, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr )
        {
            auto self = (HKEY)Value( );
            auto rc = RegSaveKeyExW( self, theFilename.data( ), theSecurityAttributes, theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& SaveKey( const wchar_t* theFilename, DWORD theFlags, LPSECURITY_ATTRIBUTES theSecurityAttributes = nullptr )
        {
            auto self = (HKEY)Value( );
            auto rc = RegSaveKeyExW( self, theFilename, theSecurityAttributes, theFlags );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& SetKeySecurity( SECURITY_INFORMATION SecurityInformation, PSECURITY_DESCRIPTOR pSecurityDescriptor )
        {
            auto self = (HKEY)Value( );
            auto rc = RegSetKeySecurity( self, SecurityInformation, pSecurityDescriptor );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& SetValue( const std::string& theValueName, DWORD theType, const void* theData, DWORD theSizeOfTheData )
        {
            auto self = (HKEY)Value( );
            auto rc = RegSetValueExA( self, theValueName.data( ), 0, theType, (const BYTE*)theData, theSizeOfTheData );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& SetValue( const char* theValueName, DWORD theType, const void* theData, DWORD theSizeOfTheData )
        {
            auto self = (HKEY)Value( );
            auto rc = RegSetValueExA( self, theValueName, 0, theType, (const BYTE*)theData, theSizeOfTheData );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }


        RegistryHandle& SetValue( const std::wstring& theValueName, DWORD theType, const void* theData, DWORD theSizeOfTheData )
        {
            auto self = (HKEY)Value( );
            auto rc = RegSetValueExW( self, theValueName.data( ), 0, theType, (const BYTE*)theData, theSizeOfTheData );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }

        RegistryHandle& SetValue( const wchar_t* theValueName, DWORD theType, const void* theData, DWORD theSizeOfTheData )
        {
            auto self = (HKEY)Value( );
            auto rc = RegSetValueExW( self, theValueName, 0, theType, (const BYTE*)theData, theSizeOfTheData );
            if ( rc != ERROR_SUCCESS )
            {
                ThrowOSError( rc );
            }
            return *this;
        }
    };

}


#endif
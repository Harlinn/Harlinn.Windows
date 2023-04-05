#include "pch.h"
#include <HWEnvironment.h>

#include <HCCException.h>

#include <Knownfolders.h>
#include <Shlobj.h>
#include <stdarg.h>

#pragma comment(lib,"Secur32")


namespace Harlinn::Windows
{
    Environment::Environment( )
    {

    }




    std::wstring Environment::GetResourceString( const wchar_t* key, ... )
    {
        va_list args;
        va_start( args, key );

        wchar_t buffer[1024];

        std::string::size_type length = _vsnwprintf_s( buffer, 1023, key, args );
        buffer[1023] = '\x0';
        std::wstring result( buffer, length );
        va_end( args );
        return result;
    }

    std::string Environment::GetResourceString( const char* key, ... )
    {
        va_list args;
        va_start( args, key );

        char buffer[1024];

        std::string::size_type length = vsnprintf_s( buffer, 1023, key, args );
        buffer[1023] = '\x0';
        std::string result( buffer, length );
        va_end( args );
        return result;
    }
    /*
    std::wstring Environment::GetResourceString(const std::wstring& key, ...)
    {
        va_list args;
        va_start(args, key);

        wchar_t buffer[1024];

        std::string::size_type length = _vsnwprintf_s (buffer,1023, key.c_str(), args );
        buffer[1023] = '\x0';
        std::wstring result(buffer, length);
        va_end(args);
        return result;
    }
    */

    std::wstring Environment::NewLine( )
    {
        return std::wstring( L"\r\n", 2 );
    }

    std::wstring Environment::Expand( const std::wstring& s )
    {
        if ( s.length( ) )
        {
            auto length = ExpandEnvironmentStringsW( s.c_str( ), nullptr, 0 );
            if ( !length )
            {
                ThrowLastOSError( );
            }
            std::wstring result;
            result.resize( length - 1 );
            ExpandEnvironmentStringsW( s.c_str( ), LPWSTR( result.c_str( ) ), DWORD( length ) );
            return result;
        }
        return s;
    }

    std::wstring Environment::Read( const std::wstring& s )
    {
        wchar_t buffer[512];
        size_t length = GetEnvironmentVariableW( s.c_str( ), buffer, 512 );
        if ( length >= 512 )
        {
            std::wstring result;
            result.resize( length );
            GetEnvironmentVariableW( s.c_str( ), result.data( ), static_cast<DWORD>( length + 1 ) );
            return result;
        }
        else
        {
            std::wstring result( buffer, length );
            return result;
        }
    }


    // ---------------------------------------------------------------------
    // Environment::SystemParameters
    // ---------------------------------------------------------------------

    bool Environment::SystemParameters::ClearType( )
    {
        BOOL result;
        if ( SystemParametersInfoW( SPI_GETCLEARTYPE, 0, &result, 0 ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return result ? true : false;
    }
    void Environment::SystemParameters::SetClearType( bool theValue, bool sendChange, bool updateProfile )
    {
        UINT flags = 0;
        if ( sendChange )
        {
            flags |= SPIF_SENDCHANGE;
        }
        if ( updateProfile )
        {
            flags |= SPIF_UPDATEINIFILE;
        }

        if ( SystemParametersInfoW( SPI_SETCLEARTYPE, 0, PVOID( theValue ), flags ) == FALSE )
        {
            ThrowLastOSError( );
        }
    }

    std::wstring Environment::SystemParameters::DesktopWallpaper( )
    {
        wchar_t buffer[MAX_PATH + 1];
        if ( SystemParametersInfoW( SPI_GETDESKWALLPAPER, MAX_PATH, buffer, 0 ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return std::wstring( buffer );
    }
    void Environment::SystemParameters::SetDesktopWallpaper( const std::wstring& theValue, bool sendChange, bool updateProfile )
    {
        UINT flags = 0;
        if ( sendChange )
        {
            flags |= SPIF_SENDCHANGE;
        }
        if ( updateProfile )
        {
            flags |= SPIF_UPDATEINIFILE;
        }

        if ( SystemParametersInfoW( SPI_SETDESKWALLPAPER, UINT( theValue.length( ) ), PVOID( theValue.c_str( ) ), flags ) == FALSE )
        {
            ThrowLastOSError( );
        }
    }


    bool Environment::SystemParameters::DropShadow( )
    {
        BOOL result;
        if ( SystemParametersInfoW( SPI_GETDROPSHADOW, 0, &result, 0 ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return result ? true : false;
    }
    void Environment::SystemParameters::SetDropShadow( bool theValue, bool sendChange, bool updateProfile )
    {
        UINT flags = 0;
        if ( sendChange )
        {
            flags |= SPIF_SENDCHANGE;
        }
        if ( updateProfile )
        {
            flags |= SPIF_UPDATEINIFILE;
        }

        if ( SystemParametersInfoW( SPI_SETDROPSHADOW, 0, PVOID( theValue ), flags ) == FALSE )
        {
            ThrowLastOSError( );
        }
    }


    bool Environment::SystemParameters::FlatMenu( )
    {
        BOOL result;
        if ( SystemParametersInfoW( SPI_GETFLATMENU, 0, &result, 0 ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return result ? true : false;
    }
    void Environment::SystemParameters::SetFlatMenu( bool theValue, bool sendChange, bool updateProfile )
    {
        UINT flags = 0;
        if ( sendChange )
        {
            flags |= SPIF_SENDCHANGE;
        }
        if ( updateProfile )
        {
            flags |= SPIF_UPDATEINIFILE;
        }

        if ( SystemParametersInfoW( SPI_SETFLATMENU, 0, PVOID( theValue ), flags ) == FALSE )
        {
            ThrowLastOSError( );
        }
    }

    bool Environment::SystemParameters::FontSmoothing( )
    {
        BOOL result;
        if ( SystemParametersInfoW( SPI_GETFONTSMOOTHING, 0, &result, 0 ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return result ? true : false;
    }
    void Environment::SystemParameters::SetFontSmoothing( bool theValue, bool sendChange, bool updateProfile )
    {
        UINT flags = 0;
        if ( sendChange )
        {
            flags |= SPIF_SENDCHANGE;
        }
        if ( updateProfile )
        {
            flags |= SPIF_UPDATEINIFILE;
        }

        if ( SystemParametersInfoW( SPI_SETFONTSMOOTHING, 0, PVOID( theValue ), flags ) == FALSE )
        {
            ThrowLastOSError( );
        }
    }

    UINT Environment::SystemParameters::FontSmoothingContrast( )
    {
        UINT result;
        if ( SystemParametersInfoW( SPI_GETFONTSMOOTHINGCONTRAST, 0, &result, 0 ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return result;
    }
    void Environment::SystemParameters::SetFontSmoothingContrast( UINT value, bool sendChange, bool updateProfile )
    {
        UINT flags = 0;
        if ( sendChange )
        {
            flags |= SPIF_SENDCHANGE;
        }
        if ( updateProfile )
        {
            flags |= SPIF_UPDATEINIFILE;
        }

        PVOID v = (PVOID)static_cast<size_t>(value);
        if ( SystemParametersInfoW( SPI_SETFONTSMOOTHINGCONTRAST, 0, v, flags ) == FALSE )
        {
            ThrowLastOSError( );
        }
    }


    Windows::FontSmoothingOrientation Environment::SystemParameters::FontSmoothingOrientation( )
    {
        UINT result;
        if ( SystemParametersInfoW( SPI_GETFONTSMOOTHINGORIENTATION, 0, &result, 0 ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return Windows::FontSmoothingOrientation( result );
    }
    void Environment::SystemParameters::SetFontSmoothingOrientation( Windows::FontSmoothingOrientation theValue, bool sendChange, bool updateProfile )
    {
        UINT flags = 0;
        if ( sendChange )
        {
            flags |= SPIF_SENDCHANGE;
        }
        if ( updateProfile )
        {
            flags |= SPIF_UPDATEINIFILE;
        }

        if ( SystemParametersInfoW( SPI_SETFONTSMOOTHINGCONTRAST, 0, PVOID( theValue ), flags ) == FALSE )
        {
            ThrowLastOSError( );
        }
    }

    Windows::NonClientMetrics Environment::SystemParameters::NonClientMetrics( )
    {
        Windows::NonClientMetrics result;

        if ( SystemParametersInfoW( SPI_GETNONCLIENTMETRICS, sizeof( NONCLIENTMETRICS ), &result, 0 ) == FALSE )
        {
            ThrowLastOSError( );
        }

        return result;
    }





    // ---------------------------------------------------------------------
    // Environment::SystemMetrics
    // ---------------------------------------------------------------------
    int Environment::SystemMetrics::ScreenWidth( ) { return GetSystemMetrics( SM_CXSCREEN ); }
    int Environment::SystemMetrics::ScreenHeight( ) { return GetSystemMetrics( SM_CYSCREEN ); }
    SIZE Environment::SystemMetrics::ScreenSize( )
    {
        SIZE result;
        result.cx = ScreenWidth( );
        result.cy = ScreenHeight( );
        return result;
    }
    int Environment::SystemMetrics::VerticalScrollBarWidth( ) { return GetSystemMetrics( SM_CXVSCROLL ); }
    int Environment::SystemMetrics::HorizontalScrollBarHeight( ) { return GetSystemMetrics( SM_CYHSCROLL ); }
    int Environment::SystemMetrics::CaptionHeight( ) { return GetSystemMetrics( SM_CYCAPTION ); }
    int Environment::SystemMetrics::BorderWidth( ) { return GetSystemMetrics( SM_CXBORDER ); }
    int Environment::SystemMetrics::BorderHeight( ) { return GetSystemMetrics( SM_CYBORDER ); }
    int Environment::SystemMetrics::VerticalScrollBarThumbHeight( ) { return GetSystemMetrics( SM_CYVTHUMB ); }
    int Environment::SystemMetrics::HorizontalScrollBarThumbWidth( ) { return GetSystemMetrics( SM_CXHTHUMB ); }
    int Environment::SystemMetrics::IconWidth( ) { return GetSystemMetrics( SM_CXICON ); }
    int Environment::SystemMetrics::IconHeight( ) { return GetSystemMetrics( SM_CYICON ); }
    SIZE Environment::SystemMetrics::IconSize( )
    {
        SIZE result;
        result.cx = IconWidth( );
        result.cy = IconHeight( );
        return result;
    }
    int Environment::SystemMetrics::CursorWidth( ) { return GetSystemMetrics( SM_CXCURSOR ); }
    int Environment::SystemMetrics::CursorHeight( ) { return GetSystemMetrics( SM_CYCURSOR ); }
    SIZE Environment::SystemMetrics::CursorSize( )
    {
        SIZE result;
        result.cx = CursorWidth( );
        result.cy = CursorHeight( );
        return result;
    }
    int Environment::SystemMetrics::MenuBarHeight( ) { return GetSystemMetrics( SM_CYMENU ); }
    int Environment::SystemMetrics::PrimaryDisplayWidth( ) { return GetSystemMetrics( SM_CXFULLSCREEN ); }
    int Environment::SystemMetrics::PrimaryDisplayHeight( ) { return GetSystemMetrics( SM_CYFULLSCREEN ); }
    SIZE Environment::SystemMetrics::PrimaryDisplaySize( )
    {
        SIZE result;
        result.cx = PrimaryDisplayWidth( );
        result.cy = PrimaryDisplayHeight( );
        return result;
    }
    int Environment::SystemMetrics::KanjiWindowHeight( ) { return GetSystemMetrics( SM_CYKANJIWINDOW ); }
    int Environment::SystemMetrics::MousePresent( ) { return GetSystemMetrics( SM_MOUSEPRESENT ); }
    int Environment::SystemMetrics::VerticalScrollBarArrowHeight( ) { return GetSystemMetrics( SM_CYVSCROLL ); }
    int Environment::SystemMetrics::HorizontalScrollBarArrowWidth( ) { return GetSystemMetrics( SM_CXHSCROLL ); }
    int Environment::SystemMetrics::IsDebugVersion( ) { return GetSystemMetrics( SM_DEBUG ); }
    int Environment::SystemMetrics::AreMouseButtonsSwapped( ) { return GetSystemMetrics( SM_SWAPBUTTON ); }
    int Environment::SystemMetrics::MinimumWindowWidth( ) { return GetSystemMetrics( SM_CXMIN ); }
    int Environment::SystemMetrics::MinimumWindowHeight( ) { return GetSystemMetrics( SM_CYMIN ); }
    SIZE Environment::SystemMetrics::MinimumWindowSize( )
    {
        SIZE result;
        result.cx = MinimumWindowWidth( );
        result.cy = MinimumWindowHeight( );
        return result;
    }
    int Environment::SystemMetrics::CaptionButtonWidth( ) { return GetSystemMetrics( SM_CXSIZE ); }
    int Environment::SystemMetrics::CaptionButtonHeight( ) { return GetSystemMetrics( SM_CYSIZE ); }
    SIZE Environment::SystemMetrics::CaptionButtonSize( )
    {
        SIZE result;
        result.cx = CaptionButtonWidth( );
        result.cy = CaptionButtonHeight( );
        return result;
    }
    int Environment::SystemMetrics::SizeableBorderWidth( ) { return GetSystemMetrics( SM_CXFRAME ); }
    int Environment::SystemMetrics::SizeableBorderHeight( ) { return GetSystemMetrics( SM_CYFRAME ); }
    int Environment::SystemMetrics::MinimumWindowResizableWidth( ) { return GetSystemMetrics( SM_CXMINTRACK ); }
    int Environment::SystemMetrics::MinimumWindowResizableHeight( ) { return GetSystemMetrics( SM_CYMINTRACK ); }
    int Environment::SystemMetrics::DoubleClickAreaWidth( ) { return GetSystemMetrics( SM_CXDOUBLECLK ); }
    int Environment::SystemMetrics::DoubleClickAreaHeight( ) { return GetSystemMetrics( SM_CYDOUBLECLK ); }
    SIZE Environment::SystemMetrics::DoubleClickAreaSize( )
    {
        SIZE result;
        result.cx = DoubleClickAreaWidth( );
        result.cy = DoubleClickAreaHeight( );
        return result;
    }
    int Environment::SystemMetrics::IconViewCellWidth( ) { return GetSystemMetrics( SM_CXICONSPACING ); }
    int Environment::SystemMetrics::IconViewCellHeight( ) { return GetSystemMetrics( SM_CYICONSPACING ); }
    SIZE Environment::SystemMetrics::IconViewCellSize( )
    {
        SIZE result;
        result.cx = IconViewCellWidth( );
        result.cy = IconViewCellHeight( );
        return result;
    }
    int Environment::SystemMetrics::DropDownMenusAreRightAligned( ) { return GetSystemMetrics( SM_MENUDROPALIGNMENT ); }
    int Environment::SystemMetrics::IsWindowsPenEnabled( ) { return GetSystemMetrics( SM_PENWINDOWS ); }
    int Environment::SystemMetrics::DBCSEnabled( ) { return GetSystemMetrics( SM_DBCSENABLED ); }
    int Environment::SystemMetrics::NumberOfMouseButtons( ) { return GetSystemMetrics( SM_CMOUSEBUTTONS ); }
    int Environment::SystemMetrics::FixedBorderWidth( ) { return GetSystemMetrics( SM_CXFIXEDFRAME ); }
    int Environment::SystemMetrics::FixedBorderHeight( ) { return GetSystemMetrics( SM_CYFIXEDFRAME ); }

    int Environment::SystemMetrics::EdgeBorderWidth( ) { return GetSystemMetrics( SM_CXEDGE ); }
    int Environment::SystemMetrics::EdgeBorderHeight( ) { return GetSystemMetrics( SM_CYEDGE ); }
    int Environment::SystemMetrics::MinimizedWindowCellWidth( ) { return GetSystemMetrics( SM_CXMINSPACING ); }
    int Environment::SystemMetrics::MinimizedWindowCellHeight( ) { return GetSystemMetrics( SM_CYMINSPACING ); }
    int Environment::SystemMetrics::SmallIconWidth( ) { return GetSystemMetrics( SM_CXSMICON ); }
    int Environment::SystemMetrics::SmallIconHeight( ) { return GetSystemMetrics( SM_CYSMICON ); }
    SIZE Environment::SystemMetrics::SmallIconSize( )
    {
        SIZE result;
        result.cx = SmallIconWidth( );
        result.cy = SmallIconHeight( );
        return result;
    }
    int Environment::SystemMetrics::SmallCaptionHeight( ) { return GetSystemMetrics( SM_CYSMCAPTION ); }
    int Environment::SystemMetrics::SmallCaptionButtonWidth( ) { return GetSystemMetrics( SM_CXSMSIZE ); }
    int Environment::SystemMetrics::SmallCaptionButtonHeight( ) { return GetSystemMetrics( SM_CYSMSIZE ); }
    SIZE Environment::SystemMetrics::SmallCaptionButtonSize( )
    {
        SIZE result;
        result.cx = SmallCaptionButtonWidth( );
        result.cy = SmallCaptionButtonHeight( );
        return result;
    }
    int Environment::SystemMetrics::MenuBarButtonWidth( ) { return GetSystemMetrics( SM_CXMENUSIZE ); }
    int Environment::SystemMetrics::MenuBarButtonHeight( ) { return GetSystemMetrics( SM_CYMENUSIZE ); }
    SIZE Environment::SystemMetrics::MenuBarButtonSize( )
    {
        SIZE result;
        result.cx = MenuBarButtonWidth( );
        result.cy = MenuBarButtonHeight( );
        return result;
    }
    int Environment::SystemMetrics::MinimizedWindowsArragement( ) { return GetSystemMetrics( SM_ARRANGE ); }
    int Environment::SystemMetrics::MinimizedWindowWidth( ) { return GetSystemMetrics( SM_CXMINIMIZED ); }
    int Environment::SystemMetrics::MinimizedWindowHeight( ) { return GetSystemMetrics( SM_CYMINIMIZED ); }
    int Environment::SystemMetrics::MaximumWindowResizableWidth( ) { return GetSystemMetrics( SM_CXMAXTRACK ); }
    int Environment::SystemMetrics::MaximumWindowResizableHeight( ) { return GetSystemMetrics( SM_CYMAXTRACK ); }
    int Environment::SystemMetrics::PrimaryDisplayMaximumWindowWidth( ) { return GetSystemMetrics( SM_CXMAXIMIZED ); }
    int Environment::SystemMetrics::PrimaryDisplayMaximumWindowHeight( ) { return GetSystemMetrics( SM_CYMAXIMIZED ); }
    int Environment::SystemMetrics::NetworkIsPresent( ) { return GetSystemMetrics( SM_NETWORK ); }
    int Environment::SystemMetrics::CleanBoot( ) { return GetSystemMetrics( SM_CLEANBOOT ); }
    int Environment::SystemMetrics::MinimumNoDragHorizontalMouseMovement( ) { return GetSystemMetrics( SM_CXDRAG ); }
    int Environment::SystemMetrics::MinimumNoDragVerticalMouseMovement( ) { return GetSystemMetrics( SM_CYDRAG ); }
    int Environment::SystemMetrics::ShowSounds( ) { return GetSystemMetrics( SM_SHOWSOUNDS ); }
    int Environment::SystemMetrics::MenuCheckMarkWidth( ) { return GetSystemMetrics( SM_CXMENUCHECK ); }
    int Environment::SystemMetrics::MenuCheckMarkHeight( ) { return GetSystemMetrics( SM_CYMENUCHECK ); }
    SIZE Environment::SystemMetrics::MenuCheckMarkSize( )
    {
        SIZE result;
        result.cx = MenuCheckMarkWidth( );
        result.cy = MenuCheckMarkHeight( );
        return result;
    }
    int Environment::SystemMetrics::SlowMachine( ) { return GetSystemMetrics( SM_SLOWMACHINE ); }
    int Environment::SystemMetrics::MiddleEastEnabled( ) { return GetSystemMetrics( SM_MIDEASTENABLED ); }
    int Environment::SystemMetrics::MouseWheelPresent( ) { return GetSystemMetrics( SM_MOUSEWHEELPRESENT ); }
    int Environment::SystemMetrics::VirtualScreenXPosition( ) { return GetSystemMetrics( SM_XVIRTUALSCREEN ); }
    int Environment::SystemMetrics::VirtualScreenYPosition( ) { return GetSystemMetrics( SM_YVIRTUALSCREEN ); }
    POINT Environment::SystemMetrics::VirtualScreenPosition( )
    {
        POINT result;
        result.x = VirtualScreenXPosition( );
        result.y = VirtualScreenYPosition( );
        return result;
    }
    int Environment::SystemMetrics::VirtualScreenWidth( ) { return GetSystemMetrics( SM_CXVIRTUALSCREEN ); }
    int Environment::SystemMetrics::VirtualScreenHeight( ) { return GetSystemMetrics( SM_CYVIRTUALSCREEN ); }
    SIZE Environment::SystemMetrics::VirtualScreenSize( )
    {
        SIZE result;
        result.cx = VirtualScreenWidth( );
        result.cy = VirtualScreenHeight( );
        return result;
    }

    int Environment::SystemMetrics::NumberOfMonitors( ) { return GetSystemMetrics( SM_CMONITORS ); }
    int Environment::SystemMetrics::MonitorsHasSameDisplayFormat( ) { return GetSystemMetrics( SM_SAMEDISPLAYFORMAT ); }
    int Environment::SystemMetrics::InputMethodManagerEnabled( ) { return GetSystemMetrics( SM_IMMENABLED ); }
    int Environment::SystemMetrics::FocusedBorderWidth( ) { return GetSystemMetrics( SM_CXFOCUSBORDER ); }
    int Environment::SystemMetrics::FocusedBorderHeight( ) { return GetSystemMetrics( SM_CYFOCUSBORDER ); }
    int Environment::SystemMetrics::TabletPC( ) { return GetSystemMetrics( SM_TABLETPC ); }
    int Environment::SystemMetrics::MediaCenterPC( ) { return GetSystemMetrics( SM_MEDIACENTER ); }
    int Environment::SystemMetrics::StarterEdition( ) { return GetSystemMetrics( SM_STARTER ); }
    int Environment::SystemMetrics::WindowsServer2003R2BuildNumber( ) { return GetSystemMetrics( SM_SERVERR2 ); }
    int Environment::SystemMetrics::MouseHorizontalWheelPresent( ) { return GetSystemMetrics( SM_MOUSEHORIZONTALWHEELPRESENT ); }
    int Environment::SystemMetrics::CaptionedWindowBorderPadding( ) { return GetSystemMetrics( SM_CXPADDEDBORDER ); }
    int Environment::SystemMetrics::TabletPCInputTypeFlags( ) { return GetSystemMetrics( SM_DIGITIZER ); }
    int Environment::SystemMetrics::MaximumTouches( ) { return GetSystemMetrics( SM_MAXIMUMTOUCHES ); }
    int Environment::SystemMetrics::InTerminalServicesClientSession( ) { return GetSystemMetrics( SM_REMOTESESSION ); }
    int Environment::SystemMetrics::ShuttingDown( ) { return GetSystemMetrics( SM_SHUTTINGDOWN ); }
    int Environment::SystemMetrics::IsTerminalServerSessionRemoteControlled( ) { return GetSystemMetrics( SM_REMOTECONTROL ); }
    int Environment::SystemMetrics::IsCaretBlinkingEnabled( ) { return GetSystemMetrics( SM_CARETBLINKINGENABLED ); }
    int Environment::SystemMetrics::ConvertibleSlateMode( ) { return GetSystemMetrics( SM_CONVERTIBLESLATEMODE ); }
    int Environment::SystemMetrics::IsSystemDocked( ) { return GetSystemMetrics( SM_SYSTEMDOCKED ); }



    // ---------------------------------------------------------------------
    // Environment::ComputerName
    // ---------------------------------------------------------------------

    std::wstring Environment::ComputerName::QueryComputerName( COMPUTER_NAME_FORMAT format )
    {
        wchar_t buffer[512];
        DWORD bufferLength = sizeof( buffer ) / sizeof( wchar_t );
        int length = GetComputerNameExW( format, buffer, &bufferLength );
        if ( !length )
        {
            auto lastError = GetLastError( );
            if ( lastError == ERROR_MORE_DATA )
            {
                std::wstring result( size_t( bufferLength ), L'\x00' );
                length = GetComputerNameExW( format, const_cast<LPWSTR>( result.c_str( ) ), &bufferLength );
                if ( !length )
                {
                    ThrowLastOSError( );
                }
                return result;
            }
            else
            {
                ThrowOSError( lastError );
            }
        }
        std::wstring s( buffer, size_t( bufferLength ) );
        return s;
    }

    std::wstring Environment::ComputerName::DnsDomain( )
    {
        return QueryComputerName( ComputerNameDnsDomain );
    }
    std::wstring Environment::ComputerName::DnsFullyQualified( )
    {
        return QueryComputerName( ComputerNameDnsFullyQualified );
    }
    std::wstring Environment::ComputerName::DnsHostname( )
    {
        return QueryComputerName( ComputerNameDnsHostname );
    }
    std::wstring Environment::ComputerName::NetBIOS( )
    {
        return QueryComputerName( ComputerNameNetBIOS );
    }
    std::wstring Environment::ComputerName::PhysicalDnsDomain( )
    {
        return QueryComputerName( ComputerNamePhysicalDnsDomain );
    }
    std::wstring Environment::ComputerName::PhysicalDnsFullyQualified( )
    {
        return QueryComputerName( ComputerNamePhysicalDnsFullyQualified );
    }
    std::wstring Environment::ComputerName::PhysicalDnsHostname( )
    {
        return QueryComputerName( ComputerNamePhysicalDnsHostname );
    }
    std::wstring Environment::ComputerName::PhysicalNetBIOS( )
    {
        return QueryComputerName( ComputerNamePhysicalNetBIOS );
    }

    // ---------------------------------------------------------------------
    // Environment::ComputerName
    // ---------------------------------------------------------------------
    std::wstring Environment::UserName::QueryUserName( EXTENDED_NAME_FORMAT format )
    {
        wchar_t buffer[512];
        DWORD bufferLength = sizeof( buffer ) / sizeof( wchar_t );
        int length = GetUserNameExW( format, buffer, &bufferLength );
        if ( !length )
        {
            auto lastError = GetLastError( );
            if ( lastError == ERROR_MORE_DATA )
            {
                std::wstring result( size_t( bufferLength ), L'\x00' );
                length = GetUserNameExW( format, const_cast<LPWSTR>( result.c_str( ) ), &bufferLength );
                if ( !length )
                {
                    ThrowLastOSError( );
                }
                return result;
            }
            else
            {
                if ( lastError != ERROR_NONE_MAPPED )
                {
                    ThrowOSError( lastError );
                }
                else
                {
                    return std::wstring( );
                }
            }
        }
        std::wstring s( buffer, size_t( bufferLength ) );
        return s;
    }

    std::wstring Environment::UserName::FullyQualifiedDN( )
    {
        return QueryUserName( NameFullyQualifiedDN );
    }
    std::wstring Environment::UserName::SamCompatible( )
    {
        return QueryUserName( NameSamCompatible );
    }
    std::wstring Environment::UserName::Display( )
    {
        return QueryUserName( NameDisplay );
    }
    std::wstring Environment::UserName::UniqueId( )
    {
        return QueryUserName( NameUniqueId );
    }
    std::wstring Environment::UserName::Canonical( )
    {
        return QueryUserName( NameCanonical );
    }
    std::wstring Environment::UserName::UserPrincipal( )
    {
        return QueryUserName( NameUserPrincipal );
    }
    std::wstring Environment::UserName::CanonicalEx( )
    {
        return QueryUserName( NameCanonicalEx );
    }
    std::wstring Environment::UserName::ServicePrincipal( )
    {
        return QueryUserName( NameServicePrincipal );
    }
    std::wstring Environment::UserName::DnsDomain( )
    {
        return QueryUserName( NameDnsDomain );
    }
    std::wstring Environment::UserName::GivenName( )
    {
        return QueryUserName( NameGivenName );
    }
    std::wstring Environment::UserName::Surname( )
    {
        return QueryUserName( NameSurname );
    }

    // ---------------------------------------------------------------------
    // Environment::KnownFolder
    // ---------------------------------------------------------------------
    std::wstring Environment::KnownFolder::QueryKnownFolder( const GUID& folderId, KnownFolderFlags flags, HANDLE userToken )
    {
        wchar_t* buffer;
        DWORD theFlags = DWORD( flags );
        HRESULT hr = SHGetKnownFolderPath( folderId, static_cast<DWORD>( flags ), userToken, &buffer );
        CheckHRESULT( hr );
        std::wstring result( buffer );
        CoTaskMemFree( buffer );
        return result;
    }

    std::wstring Environment::KnownFolder::NetworkFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_NetworkFolder, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ComputerFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ComputerFolder, flags, userToken );
    }
    std::wstring Environment::KnownFolder::InternetFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_InternetFolder, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ControlPanelFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ControlPanelFolder, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PrintersFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PrintersFolder, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SyncManagerFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SyncManagerFolder, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SyncSetupFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SyncSetupFolder, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ConflictFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ConflictFolder, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SyncResultsFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SyncResultsFolder, flags, userToken );
    }
    std::wstring Environment::KnownFolder::RecycleBinFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_RecycleBinFolder, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ConnectionsFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ConnectionsFolder, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Fonts( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Fonts, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Desktop( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Desktop, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Startup( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Startup, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Programs( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Programs, flags, userToken );
    }
    std::wstring Environment::KnownFolder::StartMenu( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_StartMenu, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Recent( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Recent, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SendTo( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SendTo, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Documents( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Documents, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Favorites( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Favorites, flags, userToken );
    }
    std::wstring Environment::KnownFolder::NetHood( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_NetHood, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PrintHood( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PrintHood, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Templates( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Templates, flags, userToken );
    }
    std::wstring Environment::KnownFolder::CommonStartup( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CommonStartup, flags, userToken );
    }
    std::wstring Environment::KnownFolder::CommonPrograms( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CommonPrograms, flags, userToken );
    }
    std::wstring Environment::KnownFolder::CommonStartMenu( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CommonStartMenu, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PublicDesktop( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicDesktop, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ProgramData( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramData, flags, userToken );
    }
    std::wstring Environment::KnownFolder::CommonTemplates( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CommonTemplates, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PublicDocuments( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicDocuments, flags, userToken );
    }
    std::wstring Environment::KnownFolder::RoamingAppData( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_RoamingAppData, flags, userToken );
    }
    std::wstring Environment::KnownFolder::LocalAppData( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_LocalAppData, flags, userToken );
    }
    std::wstring Environment::KnownFolder::LocalAppDataLow( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_LocalAppDataLow, flags, userToken );
    }
    std::wstring Environment::KnownFolder::InternetCache( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_InternetCache, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Cookies( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Cookies, flags, userToken );
    }
    std::wstring Environment::KnownFolder::History( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_History, flags, userToken );
    }
    std::wstring Environment::KnownFolder::System( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_System, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SystemX86( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SystemX86, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Windows( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Windows, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Profile( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Profile, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Pictures( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Pictures, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ProgramFilesX86( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramFilesX86, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ProgramFilesCommonX86( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramFilesCommonX86, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ProgramFilesX64( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramFilesX64, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ProgramFilesCommonX64( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramFilesCommonX64, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ProgramFiles( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramFiles, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ProgramFilesCommon( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramFilesCommon, flags, userToken );
    }
    std::wstring Environment::KnownFolder::UserProgramFiles( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_UserProgramFiles, flags, userToken );
    }
    std::wstring Environment::KnownFolder::UserProgramFilesCommon( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_UserProgramFilesCommon, flags, userToken );
    }
    std::wstring Environment::KnownFolder::AdminTools( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_AdminTools, flags, userToken );
    }
    std::wstring Environment::KnownFolder::CommonAdminTools( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CommonAdminTools, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Music( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Music, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Videos( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Videos, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Ringtones( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Ringtones, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PublicPictures( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicPictures, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PublicMusic( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicMusic, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PublicVideos( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicVideos, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PublicRingtones( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicRingtones, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ResourceDir( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ResourceDir, flags, userToken );
    }
    std::wstring Environment::KnownFolder::LocalizedResourcesDir( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_LocalizedResourcesDir, flags, userToken );
    }
    std::wstring Environment::KnownFolder::CommonOEMLinks( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CommonOEMLinks, flags, userToken );
    }
    std::wstring Environment::KnownFolder::CDBurning( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CDBurning, flags, userToken );
    }
    std::wstring Environment::KnownFolder::UserProfiles( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_UserProfiles, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Playlists( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Playlists, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SamplePlaylists( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SamplePlaylists, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SampleMusic( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SampleMusic, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SamplePictures( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SamplePictures, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SampleVideos( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SampleVideos, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PhotoAlbums( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PhotoAlbums, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Public( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Public, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ChangeRemovePrograms( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ChangeRemovePrograms, flags, userToken );
    }
    std::wstring Environment::KnownFolder::AppUpdates( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_AppUpdates, flags, userToken );
    }
    std::wstring Environment::KnownFolder::AddNewPrograms( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_AddNewPrograms, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Downloads( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Downloads, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PublicDownloads( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicDownloads, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SavedSearches( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SavedSearches, flags, userToken );
    }
    std::wstring Environment::KnownFolder::QuickLaunch( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_QuickLaunch, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Contacts( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Contacts, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SidebarParts( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SidebarParts, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SidebarDefaultParts( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SidebarDefaultParts, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PublicGameTasks( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicGameTasks, flags, userToken );
    }
    std::wstring Environment::KnownFolder::GameTasks( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_GameTasks, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SavedGames( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SavedGames, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Games( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Games, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SEARCH_MAPI( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SEARCH_MAPI, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SEARCH_CSC( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SEARCH_CSC, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Links( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Links, flags, userToken );
    }
    std::wstring Environment::KnownFolder::UsersFiles( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_UsersFiles, flags, userToken );
    }
    std::wstring Environment::KnownFolder::UsersLibraries( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_UsersLibraries, flags, userToken );
    }
    std::wstring Environment::KnownFolder::SearchHome( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SearchHome, flags, userToken );
    }
    std::wstring Environment::KnownFolder::OriginalImages( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_OriginalImages, flags, userToken );
    }
    std::wstring Environment::KnownFolder::DocumentsLibrary( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_DocumentsLibrary, flags, userToken );
    }
    std::wstring Environment::KnownFolder::MusicLibrary( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_MusicLibrary, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PicturesLibrary( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PicturesLibrary, flags, userToken );
    }
    std::wstring Environment::KnownFolder::VideosLibrary( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_VideosLibrary, flags, userToken );
    }
    std::wstring Environment::KnownFolder::RecordedTVLibrary( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_RecordedTVLibrary, flags, userToken );
    }
    std::wstring Environment::KnownFolder::HomeGroup( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_HomeGroup, flags, userToken );
    }
    std::wstring Environment::KnownFolder::HomeGroupCurrentUser( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_HomeGroupCurrentUser, flags, userToken );
    }
    std::wstring Environment::KnownFolder::DeviceMetadataStore( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_DeviceMetadataStore, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Libraries( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Libraries, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PublicLibraries( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicLibraries, flags, userToken );
    }
    std::wstring Environment::KnownFolder::UserPinned( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_UserPinned, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ImplicitAppShortcuts( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ImplicitAppShortcuts, flags, userToken );
    }
    std::wstring Environment::KnownFolder::AccountPictures( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_AccountPictures, flags, userToken );
    }
    std::wstring Environment::KnownFolder::PublicUserTiles( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicUserTiles, flags, userToken );
    }
    std::wstring Environment::KnownFolder::AppsFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_AppsFolder, flags, userToken );
    }
    std::wstring Environment::KnownFolder::ApplicationShortcuts( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ApplicationShortcuts, flags, userToken );
    }
    std::wstring Environment::KnownFolder::RoamingTiles( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_RoamingTiles, flags, userToken );
    }
    std::wstring Environment::KnownFolder::RoamedTileImages( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_RoamedTileImages, flags, userToken );
    }
    std::wstring Environment::KnownFolder::Screenshots( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Screenshots, flags, userToken );
    }
}


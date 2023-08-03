#include "pch.h"
#include <HWEnvironment.h>

#include <HCCException.h>

#include <Knownfolders.h>
#include <Shlobj.h>
#include <stdarg.h>

#pragma comment(lib,"Secur32")


namespace Harlinn::Windows
{

    WideString Environment::GetResourceString( const wchar_t* key, ... )
    {
        va_list args;
        va_start( args, key );

        wchar_t buffer[1024];

        WideString::size_type length = _vsnwprintf_s( buffer, 1023, key, args );
        buffer[1023] = '\x0';
        WideString result( buffer, length );
        va_end( args );
        return result;
    }

    AnsiString Environment::GetResourceString( const char* key, ... )
    {
        va_list args;
        va_start( args, key );

        char buffer[1024];

        AnsiString::size_type length = vsnprintf_s( buffer, 1023, key, args );
        buffer[1023] = '\x0';
        AnsiString result( buffer, length );
        va_end( args );
        return result;
    }

    WideString Environment::NewLine( )
    {
        return WideString( L"\r\n", 2 );
    }

    WideString Environment::Expand( const WideString& s )
    {
        if ( s.length( ) )
        {
            auto length = ExpandEnvironmentStringsW( s.c_str( ), nullptr, 0 );
            if ( !length )
            {
                ThrowLastOSError( );
            }
            WideString result;
            result.resize( length - 1 );
            ExpandEnvironmentStringsW( s.c_str( ), LPWSTR( result.c_str( ) ), DWORD( length ) );
            return result;
        }
        return s;
    }

    WideString Environment::Read( const WideString& s )
    {
        wchar_t buffer[512];
        size_t length = GetEnvironmentVariableW( s.c_str( ), buffer, 512 );
        if ( length >= 512 )
        {
            WideString result;
            result.resize( length );
            GetEnvironmentVariableW( s.c_str( ), result.data( ), static_cast<DWORD>( length + 1 ) );
            return result;
        }
        else
        {
            WideString result( buffer, length );
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

    WideString Environment::SystemParameters::DesktopWallpaper( )
    {
        wchar_t buffer[MAX_PATH + 1];
        if ( SystemParametersInfoW( SPI_GETDESKWALLPAPER, MAX_PATH, buffer, 0 ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return WideString( buffer );
    }
    void Environment::SystemParameters::SetDesktopWallpaper( const WideString& theValue, bool sendChange, bool updateProfile )
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

        if ( SystemParametersInfoW( SPI_GETFONTSMOOTHINGORIENTATION, 0, PVOID( theValue ), flags ) == FALSE )
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

    WideString Environment::ComputerName::QueryComputerName( COMPUTER_NAME_FORMAT format )
    {
        wchar_t buffer[512];
        DWORD bufferLength = sizeof( buffer ) / sizeof( wchar_t );
        int length = GetComputerNameExW( format, buffer, &bufferLength );
        if ( !length )
        {
            auto lastError = GetLastError( );
            if ( lastError == ERROR_MORE_DATA )
            {
                WideString result( size_t( bufferLength ), L'\x00' );
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
        WideString s( buffer, size_t( bufferLength ) );
        return s;
    }

    WideString Environment::ComputerName::DnsDomain( )
    {
        return QueryComputerName( ComputerNameDnsDomain );
    }
    WideString Environment::ComputerName::DnsFullyQualified( )
    {
        return QueryComputerName( ComputerNameDnsFullyQualified );
    }
    WideString Environment::ComputerName::DnsHostname( )
    {
        return QueryComputerName( ComputerNameDnsHostname );
    }
    WideString Environment::ComputerName::NetBIOS( )
    {
        return QueryComputerName( ComputerNameNetBIOS );
    }
    WideString Environment::ComputerName::PhysicalDnsDomain( )
    {
        return QueryComputerName( ComputerNamePhysicalDnsDomain );
    }
    WideString Environment::ComputerName::PhysicalDnsFullyQualified( )
    {
        return QueryComputerName( ComputerNamePhysicalDnsFullyQualified );
    }
    WideString Environment::ComputerName::PhysicalDnsHostname( )
    {
        return QueryComputerName( ComputerNamePhysicalDnsHostname );
    }
    WideString Environment::ComputerName::PhysicalNetBIOS( )
    {
        return QueryComputerName( ComputerNamePhysicalNetBIOS );
    }

    // ---------------------------------------------------------------------
    // Environment::ComputerName
    // ---------------------------------------------------------------------
    WideString Environment::UserName::QueryUserName( EXTENDED_NAME_FORMAT format )
    {
        wchar_t buffer[512];
        DWORD bufferLength = sizeof( buffer ) / sizeof( wchar_t );
        int length = GetUserNameExW( format, buffer, &bufferLength );
        if ( !length )
        {
            auto lastError = GetLastError( );
            if ( lastError == ERROR_MORE_DATA )
            {
                WideString result( size_t( bufferLength ), L'\x00' );
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
                    return WideString( );
                }
            }
        }
        WideString s( buffer, size_t( bufferLength ) );
        return s;
    }

    WideString Environment::UserName::FullyQualifiedDN( )
    {
        return QueryUserName( NameFullyQualifiedDN );
    }
    WideString Environment::UserName::SamCompatible( )
    {
        return QueryUserName( NameSamCompatible );
    }
    WideString Environment::UserName::Display( )
    {
        return QueryUserName( NameDisplay );
    }
    WideString Environment::UserName::UniqueId( )
    {
        return QueryUserName( NameUniqueId );
    }
    WideString Environment::UserName::Canonical( )
    {
        return QueryUserName( NameCanonical );
    }
    WideString Environment::UserName::UserPrincipal( )
    {
        return QueryUserName( NameUserPrincipal );
    }
    WideString Environment::UserName::CanonicalEx( )
    {
        return QueryUserName( NameCanonicalEx );
    }
    WideString Environment::UserName::ServicePrincipal( )
    {
        return QueryUserName( NameServicePrincipal );
    }
    WideString Environment::UserName::DnsDomain( )
    {
        return QueryUserName( NameDnsDomain );
    }
    WideString Environment::UserName::GivenName( )
    {
        return QueryUserName( NameGivenName );
    }
    WideString Environment::UserName::Surname( )
    {
        return QueryUserName( NameSurname );
    }

    // ---------------------------------------------------------------------
    // Environment::KnownFolder
    // ---------------------------------------------------------------------
    WideString Environment::KnownFolder::QueryKnownFolder( const GUID& folderId, KnownFolderFlags flags, HANDLE userToken )
    {
        wchar_t* buffer;
        DWORD theFlags = DWORD( flags );
        HRESULT hr = SHGetKnownFolderPath( folderId, static_cast<DWORD>( flags ), userToken, &buffer );
        CheckHRESULT( hr );
        WideString result( buffer );
        CoTaskMemFree( buffer );
        return result;
    }

    WideString Environment::KnownFolder::NetworkFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_NetworkFolder, flags, userToken );
    }
    WideString Environment::KnownFolder::ComputerFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ComputerFolder, flags, userToken );
    }
    WideString Environment::KnownFolder::InternetFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_InternetFolder, flags, userToken );
    }
    WideString Environment::KnownFolder::ControlPanelFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ControlPanelFolder, flags, userToken );
    }
    WideString Environment::KnownFolder::PrintersFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PrintersFolder, flags, userToken );
    }
    WideString Environment::KnownFolder::SyncManagerFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SyncManagerFolder, flags, userToken );
    }
    WideString Environment::KnownFolder::SyncSetupFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SyncSetupFolder, flags, userToken );
    }
    WideString Environment::KnownFolder::ConflictFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ConflictFolder, flags, userToken );
    }
    WideString Environment::KnownFolder::SyncResultsFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SyncResultsFolder, flags, userToken );
    }
    WideString Environment::KnownFolder::RecycleBinFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_RecycleBinFolder, flags, userToken );
    }
    WideString Environment::KnownFolder::ConnectionsFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ConnectionsFolder, flags, userToken );
    }
    WideString Environment::KnownFolder::Fonts( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Fonts, flags, userToken );
    }
    WideString Environment::KnownFolder::Desktop( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Desktop, flags, userToken );
    }
    WideString Environment::KnownFolder::Startup( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Startup, flags, userToken );
    }
    WideString Environment::KnownFolder::Programs( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Programs, flags, userToken );
    }
    WideString Environment::KnownFolder::StartMenu( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_StartMenu, flags, userToken );
    }
    WideString Environment::KnownFolder::Recent( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Recent, flags, userToken );
    }
    WideString Environment::KnownFolder::SendTo( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SendTo, flags, userToken );
    }
    WideString Environment::KnownFolder::Documents( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Documents, flags, userToken );
    }
    WideString Environment::KnownFolder::Favorites( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Favorites, flags, userToken );
    }
    WideString Environment::KnownFolder::NetHood( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_NetHood, flags, userToken );
    }
    WideString Environment::KnownFolder::PrintHood( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PrintHood, flags, userToken );
    }
    WideString Environment::KnownFolder::Templates( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Templates, flags, userToken );
    }
    WideString Environment::KnownFolder::CommonStartup( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CommonStartup, flags, userToken );
    }
    WideString Environment::KnownFolder::CommonPrograms( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CommonPrograms, flags, userToken );
    }
    WideString Environment::KnownFolder::CommonStartMenu( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CommonStartMenu, flags, userToken );
    }
    WideString Environment::KnownFolder::PublicDesktop( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicDesktop, flags, userToken );
    }
    WideString Environment::KnownFolder::ProgramData( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramData, flags, userToken );
    }
    WideString Environment::KnownFolder::CommonTemplates( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CommonTemplates, flags, userToken );
    }
    WideString Environment::KnownFolder::PublicDocuments( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicDocuments, flags, userToken );
    }
    WideString Environment::KnownFolder::RoamingAppData( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_RoamingAppData, flags, userToken );
    }
    WideString Environment::KnownFolder::LocalAppData( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_LocalAppData, flags, userToken );
    }
    WideString Environment::KnownFolder::LocalAppDataLow( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_LocalAppDataLow, flags, userToken );
    }
    WideString Environment::KnownFolder::InternetCache( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_InternetCache, flags, userToken );
    }
    WideString Environment::KnownFolder::Cookies( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Cookies, flags, userToken );
    }
    WideString Environment::KnownFolder::History( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_History, flags, userToken );
    }
    WideString Environment::KnownFolder::System( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_System, flags, userToken );
    }
    WideString Environment::KnownFolder::SystemX86( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SystemX86, flags, userToken );
    }
    WideString Environment::KnownFolder::Windows( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Windows, flags, userToken );
    }
    WideString Environment::KnownFolder::Profile( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Profile, flags, userToken );
    }
    WideString Environment::KnownFolder::Pictures( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Pictures, flags, userToken );
    }
    WideString Environment::KnownFolder::ProgramFilesX86( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramFilesX86, flags, userToken );
    }
    WideString Environment::KnownFolder::ProgramFilesCommonX86( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramFilesCommonX86, flags, userToken );
    }
    WideString Environment::KnownFolder::ProgramFilesX64( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramFilesX64, flags, userToken );
    }
    WideString Environment::KnownFolder::ProgramFilesCommonX64( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramFilesCommonX64, flags, userToken );
    }
    WideString Environment::KnownFolder::ProgramFiles( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramFiles, flags, userToken );
    }
    WideString Environment::KnownFolder::ProgramFilesCommon( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ProgramFilesCommon, flags, userToken );
    }
    WideString Environment::KnownFolder::UserProgramFiles( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_UserProgramFiles, flags, userToken );
    }
    WideString Environment::KnownFolder::UserProgramFilesCommon( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_UserProgramFilesCommon, flags, userToken );
    }
    WideString Environment::KnownFolder::AdminTools( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_AdminTools, flags, userToken );
    }
    WideString Environment::KnownFolder::CommonAdminTools( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CommonAdminTools, flags, userToken );
    }
    WideString Environment::KnownFolder::Music( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Music, flags, userToken );
    }
    WideString Environment::KnownFolder::Videos( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Videos, flags, userToken );
    }
    WideString Environment::KnownFolder::Ringtones( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Ringtones, flags, userToken );
    }
    WideString Environment::KnownFolder::PublicPictures( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicPictures, flags, userToken );
    }
    WideString Environment::KnownFolder::PublicMusic( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicMusic, flags, userToken );
    }
    WideString Environment::KnownFolder::PublicVideos( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicVideos, flags, userToken );
    }
    WideString Environment::KnownFolder::PublicRingtones( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicRingtones, flags, userToken );
    }
    WideString Environment::KnownFolder::ResourceDir( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ResourceDir, flags, userToken );
    }
    WideString Environment::KnownFolder::LocalizedResourcesDir( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_LocalizedResourcesDir, flags, userToken );
    }
    WideString Environment::KnownFolder::CommonOEMLinks( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CommonOEMLinks, flags, userToken );
    }
    WideString Environment::KnownFolder::CDBurning( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_CDBurning, flags, userToken );
    }
    WideString Environment::KnownFolder::UserProfiles( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_UserProfiles, flags, userToken );
    }
    WideString Environment::KnownFolder::Playlists( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Playlists, flags, userToken );
    }
    WideString Environment::KnownFolder::SamplePlaylists( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SamplePlaylists, flags, userToken );
    }
    WideString Environment::KnownFolder::SampleMusic( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SampleMusic, flags, userToken );
    }
    WideString Environment::KnownFolder::SamplePictures( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SamplePictures, flags, userToken );
    }
    WideString Environment::KnownFolder::SampleVideos( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SampleVideos, flags, userToken );
    }
    WideString Environment::KnownFolder::PhotoAlbums( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PhotoAlbums, flags, userToken );
    }
    WideString Environment::KnownFolder::Public( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Public, flags, userToken );
    }
    WideString Environment::KnownFolder::ChangeRemovePrograms( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ChangeRemovePrograms, flags, userToken );
    }
    WideString Environment::KnownFolder::AppUpdates( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_AppUpdates, flags, userToken );
    }
    WideString Environment::KnownFolder::AddNewPrograms( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_AddNewPrograms, flags, userToken );
    }
    WideString Environment::KnownFolder::Downloads( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Downloads, flags, userToken );
    }
    WideString Environment::KnownFolder::PublicDownloads( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicDownloads, flags, userToken );
    }
    WideString Environment::KnownFolder::SavedSearches( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SavedSearches, flags, userToken );
    }
    WideString Environment::KnownFolder::QuickLaunch( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_QuickLaunch, flags, userToken );
    }
    WideString Environment::KnownFolder::Contacts( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Contacts, flags, userToken );
    }
    WideString Environment::KnownFolder::SidebarParts( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SidebarParts, flags, userToken );
    }
    WideString Environment::KnownFolder::SidebarDefaultParts( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SidebarDefaultParts, flags, userToken );
    }
    WideString Environment::KnownFolder::PublicGameTasks( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicGameTasks, flags, userToken );
    }
    WideString Environment::KnownFolder::GameTasks( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_GameTasks, flags, userToken );
    }
    WideString Environment::KnownFolder::SavedGames( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SavedGames, flags, userToken );
    }
    WideString Environment::KnownFolder::Games( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Games, flags, userToken );
    }
    WideString Environment::KnownFolder::SEARCH_MAPI( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SEARCH_MAPI, flags, userToken );
    }
    WideString Environment::KnownFolder::SEARCH_CSC( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SEARCH_CSC, flags, userToken );
    }
    WideString Environment::KnownFolder::Links( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Links, flags, userToken );
    }
    WideString Environment::KnownFolder::UsersFiles( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_UsersFiles, flags, userToken );
    }
    WideString Environment::KnownFolder::UsersLibraries( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_UsersLibraries, flags, userToken );
    }
    WideString Environment::KnownFolder::SearchHome( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_SearchHome, flags, userToken );
    }
    WideString Environment::KnownFolder::OriginalImages( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_OriginalImages, flags, userToken );
    }
    WideString Environment::KnownFolder::DocumentsLibrary( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_DocumentsLibrary, flags, userToken );
    }
    WideString Environment::KnownFolder::MusicLibrary( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_MusicLibrary, flags, userToken );
    }
    WideString Environment::KnownFolder::PicturesLibrary( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PicturesLibrary, flags, userToken );
    }
    WideString Environment::KnownFolder::VideosLibrary( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_VideosLibrary, flags, userToken );
    }
    WideString Environment::KnownFolder::RecordedTVLibrary( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_RecordedTVLibrary, flags, userToken );
    }
    WideString Environment::KnownFolder::HomeGroup( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_HomeGroup, flags, userToken );
    }
    WideString Environment::KnownFolder::HomeGroupCurrentUser( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_HomeGroupCurrentUser, flags, userToken );
    }
    WideString Environment::KnownFolder::DeviceMetadataStore( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_DeviceMetadataStore, flags, userToken );
    }
    WideString Environment::KnownFolder::Libraries( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Libraries, flags, userToken );
    }
    WideString Environment::KnownFolder::PublicLibraries( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicLibraries, flags, userToken );
    }
    WideString Environment::KnownFolder::UserPinned( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_UserPinned, flags, userToken );
    }
    WideString Environment::KnownFolder::ImplicitAppShortcuts( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ImplicitAppShortcuts, flags, userToken );
    }
    WideString Environment::KnownFolder::AccountPictures( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_AccountPictures, flags, userToken );
    }
    WideString Environment::KnownFolder::PublicUserTiles( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_PublicUserTiles, flags, userToken );
    }
    WideString Environment::KnownFolder::AppsFolder( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_AppsFolder, flags, userToken );
    }
    WideString Environment::KnownFolder::ApplicationShortcuts( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_ApplicationShortcuts, flags, userToken );
    }
    WideString Environment::KnownFolder::RoamingTiles( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_RoamingTiles, flags, userToken );
    }
    WideString Environment::KnownFolder::RoamedTileImages( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_RoamedTileImages, flags, userToken );
    }
    WideString Environment::KnownFolder::Screenshots( KnownFolderFlags flags, HANDLE userToken )
    {
        return QueryKnownFolder( FOLDERID_Screenshots, flags, userToken );
    }
}


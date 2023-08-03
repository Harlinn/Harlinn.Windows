#pragma once
#ifndef __HWENVIRONMENT_H__
#define __HWENVIRONMENT_H__

#include <HWDef.h>
#include <HCCDateTime.h>


namespace Harlinn::Windows
{
    enum class KnownFolderFlags : uint
    {
        Default = 0x00000000,
        NoAppContainerRedirection = 0x00010000,
        Create = 0x00008000,
        DontVerify = 0x00004000,
        DontUnexpand = 0x00002000,
        NoAlias = 0x00001000,
        Init = 0x00000800,
        DefaultPath = 0x00000400,
        NotParentRelative = 0x00000200,
        SimpleIDList = 0x00000100,
        AliasOnly = 0x80000000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( KnownFolderFlags, uint );

    enum class AccessTimeoutFlags : DWord
    {
        None = 0x0000,
        TimeOutOn = 0x0001,
        FeedbackOn = 0x0002
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( AccessTimeoutFlags, DWord );

    struct AccessTimeOut
    {
        AccessTimeoutFlags Flags;
        TimeSpan TimeOut;
    };


    enum class FilterKeysFlags : DWord
    {
        FilterKeysOn = 0x00000001,
        Available = 0x00000002,
        HotKeyActive = 0x00000004,
        ConfirmHotKey = 0x00000008,
        HotKeySound = 0x00000010,
        Indicator = 0x00000020,
        ClickOn = 0x00000040
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( FilterKeysFlags, DWord );

    struct FilterKeys
    {
        FilterKeysFlags Flags;
        TimeSpan Wait;
        TimeSpan Delay;
        TimeSpan Repeat;
        TimeSpan Bounce;
    };


    enum class HighContrastFlags : DWord
    {
        HighContrastOn = 0x00000001,
        Available = 0x00000002,
        HotKeyActive = 0x00000004,
        ConfirmHotKey = 0x00000008,
        HotKeySound = 0x00000010,
        Indicator = 0x00000020,
        HotKeyAvailable = 0x00000040,
        LogonDesktop = 0x00000100,
        DefaultDesktop = 0x00000200
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( HighContrastFlags, DWord );

    struct HighContrast
    {
        HighContrastFlags Flags;
        WideString DefaultScheme;
    };

    enum class MouseKeysFlags : DWord
    {
        MouseKeysOn = 0x00000001,
        Available = 0x00000002,
        HotKeyActive = 0x00000004,
        ConfirmHotKey = 0x00000008,
        HotKeySound = 0x00000010,
        Indicator = 0x00000020,
        Modifiers = 0x00000040,
        ReplaceNumbers = 0x00000080,
        LeftButtonSel = 0x10000000,
        RightButtonSel = 0x20000000,
        LeftButtonDown = 0x01000000,
        RightButtonDown = 0x02000000,
        MOUSEMODE = 0x80000000
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( MouseKeysFlags, DWord );


    struct MouseKeys
    {
        MouseKeysFlags Flags;
        DWORD MaxSpeed;
        TimeSpan TimeToMaxSpeed;
        DWORD CtrlSpeed;
    };


    enum class FontSmoothingOrientation : UInt
    {
        BGR = 0x0000,
        RGB = 0x0001
    };

    class NonClientMetrics : public NONCLIENTMETRICS
    {
    public:
    };

    namespace Environment
    {
        HW_EXPORT WideString GetResourceString( const wchar_t* key, ... );
        HW_EXPORT AnsiString GetResourceString( const char* key, ... );
        

        HW_EXPORT WideString NewLine( );
        HW_EXPORT WideString Expand( const WideString& s );
        HW_EXPORT WideString Read( const WideString& s );

        namespace SystemParameters
        {
            // Desktop
            HW_EXPORT bool ClearType( );
            HW_EXPORT void SetClearType( bool theValue, bool sendChange = true, bool updateProfile = true );

            HW_EXPORT WideString DesktopWallpaper( );
            HW_EXPORT void SetDesktopWallpaper( const WideString& theValue, bool sendChange = true, bool updateProfile = true );

            HW_EXPORT bool DropShadow( );
            HW_EXPORT void SetDropShadow( bool theValue, bool sendChange = true, bool updateProfile = true );

            HW_EXPORT bool FlatMenu( );
            HW_EXPORT void SetFlatMenu( bool theValue, bool sendChange = true, bool updateProfile = true );

            HW_EXPORT bool FontSmoothing( );
            HW_EXPORT void SetFontSmoothing( bool theValue, bool sendChange = true, bool updateProfile = true );

            HW_EXPORT UINT FontSmoothingContrast( );
            HW_EXPORT void SetFontSmoothingContrast( UINT theValue, bool sendChange = true, bool updateProfile = true );

            HW_EXPORT Windows::FontSmoothingOrientation FontSmoothingOrientation( );
            HW_EXPORT void SetFontSmoothingOrientation( Windows::FontSmoothingOrientation theValue, bool sendChange = true, bool updateProfile = true );


            HW_EXPORT Windows::NonClientMetrics NonClientMetrics( );



        };

        namespace SystemMetrics
        {
            HW_EXPORT int ScreenWidth( );
            HW_EXPORT int ScreenHeight( );
            HW_EXPORT SIZE ScreenSize( );
            HW_EXPORT int VerticalScrollBarWidth( );
            HW_EXPORT int HorizontalScrollBarHeight( );
            HW_EXPORT int CaptionHeight( );
            HW_EXPORT int BorderWidth( );
            HW_EXPORT int BorderHeight( );
            HW_EXPORT int VerticalScrollBarThumbHeight( );
            HW_EXPORT int HorizontalScrollBarThumbWidth( );
            HW_EXPORT int IconWidth( );
            HW_EXPORT int IconHeight( );
            HW_EXPORT SIZE IconSize( );
            HW_EXPORT int CursorWidth( );
            HW_EXPORT int CursorHeight( );
            HW_EXPORT SIZE CursorSize( );
            HW_EXPORT int MenuBarHeight( );
            HW_EXPORT int PrimaryDisplayWidth( );
            HW_EXPORT int PrimaryDisplayHeight( );
            HW_EXPORT SIZE PrimaryDisplaySize( );
            HW_EXPORT int KanjiWindowHeight( );
            HW_EXPORT int MousePresent( );
            HW_EXPORT int VerticalScrollBarArrowHeight( );
            HW_EXPORT int HorizontalScrollBarArrowWidth( );
            HW_EXPORT int IsDebugVersion( );
            HW_EXPORT int AreMouseButtonsSwapped( );
            HW_EXPORT int MinimumWindowWidth( );
            HW_EXPORT int MinimumWindowHeight( );
            HW_EXPORT SIZE MinimumWindowSize( );
            HW_EXPORT int CaptionButtonWidth( );
            HW_EXPORT int CaptionButtonHeight( );
            HW_EXPORT SIZE CaptionButtonSize( );
            HW_EXPORT int SizeableBorderWidth( );
            HW_EXPORT int SizeableBorderHeight( );
            HW_EXPORT int MinimumWindowResizableWidth( );
            HW_EXPORT int MinimumWindowResizableHeight( );
            HW_EXPORT int DoubleClickAreaWidth( );
            HW_EXPORT int DoubleClickAreaHeight( );
            HW_EXPORT SIZE DoubleClickAreaSize( );
            HW_EXPORT int IconViewCellWidth( );
            HW_EXPORT int IconViewCellHeight( );
            HW_EXPORT SIZE IconViewCellSize( );
            HW_EXPORT int DropDownMenusAreRightAligned( );
            HW_EXPORT int IsWindowsPenEnabled( );
            HW_EXPORT int DBCSEnabled( );
            HW_EXPORT int NumberOfMouseButtons( );
            HW_EXPORT int FixedBorderWidth( );
            HW_EXPORT int FixedBorderHeight( );

            HW_EXPORT int EdgeBorderWidth( );
            HW_EXPORT int EdgeBorderHeight( );
            HW_EXPORT int MinimizedWindowCellWidth( );
            HW_EXPORT int MinimizedWindowCellHeight( );
            HW_EXPORT int SmallIconWidth( );
            HW_EXPORT int SmallIconHeight( );
            HW_EXPORT SIZE SmallIconSize( );
            HW_EXPORT int SmallCaptionHeight( );
            HW_EXPORT int SmallCaptionButtonWidth( );
            HW_EXPORT int SmallCaptionButtonHeight( );
            HW_EXPORT SIZE SmallCaptionButtonSize( );
            HW_EXPORT int MenuBarButtonWidth( );
            HW_EXPORT int MenuBarButtonHeight( );
            HW_EXPORT SIZE MenuBarButtonSize( );
            HW_EXPORT int MinimizedWindowsArragement( );
            HW_EXPORT int MinimizedWindowWidth( );
            HW_EXPORT int MinimizedWindowHeight( );
            HW_EXPORT int MaximumWindowResizableWidth( );
            HW_EXPORT int MaximumWindowResizableHeight( );
            HW_EXPORT int PrimaryDisplayMaximumWindowWidth( );
            HW_EXPORT int PrimaryDisplayMaximumWindowHeight( );
            HW_EXPORT int NetworkIsPresent( );
            HW_EXPORT int CleanBoot( );
            HW_EXPORT int MinimumNoDragHorizontalMouseMovement( );
            HW_EXPORT int MinimumNoDragVerticalMouseMovement( );
            HW_EXPORT int ShowSounds( );
            HW_EXPORT int MenuCheckMarkWidth( );
            HW_EXPORT int MenuCheckMarkHeight( );
            HW_EXPORT SIZE MenuCheckMarkSize( );
            HW_EXPORT int SlowMachine( );
            HW_EXPORT int MiddleEastEnabled( );
            HW_EXPORT int MouseWheelPresent( );
            HW_EXPORT int VirtualScreenXPosition( );
            HW_EXPORT int VirtualScreenYPosition( );
            HW_EXPORT POINT VirtualScreenPosition( );
            HW_EXPORT int VirtualScreenWidth( );
            HW_EXPORT int VirtualScreenHeight( );
            HW_EXPORT SIZE VirtualScreenSize( );
            HW_EXPORT int NumberOfMonitors( );
            HW_EXPORT int MonitorsHasSameDisplayFormat( );
            HW_EXPORT int InputMethodManagerEnabled( );
            HW_EXPORT int FocusedBorderWidth( );
            HW_EXPORT int FocusedBorderHeight( );
            HW_EXPORT int TabletPC( );
            HW_EXPORT int MediaCenterPC( );
            HW_EXPORT int StarterEdition( );
            HW_EXPORT int WindowsServer2003R2BuildNumber( );
            HW_EXPORT int MouseHorizontalWheelPresent( );
            HW_EXPORT int CaptionedWindowBorderPadding( );
            HW_EXPORT int TabletPCInputTypeFlags( );
            HW_EXPORT int MaximumTouches( );
            HW_EXPORT int InTerminalServicesClientSession( );
            HW_EXPORT int ShuttingDown( );
            HW_EXPORT int IsTerminalServerSessionRemoteControlled( );
            HW_EXPORT int IsCaretBlinkingEnabled( );
            HW_EXPORT int ConvertibleSlateMode( );
            HW_EXPORT int IsSystemDocked( );

        }



        namespace ComputerName
        {
            HW_EXPORT WideString QueryComputerName( COMPUTER_NAME_FORMAT format );

            HW_EXPORT WideString DnsDomain( );
            HW_EXPORT WideString DnsFullyQualified( );
            HW_EXPORT WideString DnsHostname( );
            HW_EXPORT WideString NetBIOS( );
            HW_EXPORT WideString PhysicalDnsDomain( );
            HW_EXPORT WideString PhysicalDnsFullyQualified( );
            HW_EXPORT WideString PhysicalDnsHostname( );
            HW_EXPORT WideString PhysicalNetBIOS( );
        }


        namespace UserName
        {
            
            HW_EXPORT WideString QueryUserName( EXTENDED_NAME_FORMAT format );
        
            HW_EXPORT WideString FullyQualifiedDN( );
            HW_EXPORT WideString SamCompatible( );
            HW_EXPORT WideString Display( );
            HW_EXPORT WideString UniqueId( );
            HW_EXPORT WideString Canonical( );
            HW_EXPORT WideString UserPrincipal( );
            HW_EXPORT WideString CanonicalEx( );
            HW_EXPORT WideString ServicePrincipal( );
            HW_EXPORT WideString DnsDomain( );
            HW_EXPORT WideString GivenName( );
            HW_EXPORT WideString Surname( );

        }


        namespace KnownFolder
        {
            HW_EXPORT WideString QueryKnownFolder( const GUID& folderId, KnownFolderFlags flags, HANDLE userToken );

            HW_EXPORT WideString NetworkFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ComputerFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString InternetFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ControlPanelFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PrintersFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SyncManagerFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SyncSetupFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ConflictFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SyncResultsFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString RecycleBinFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ConnectionsFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Fonts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Desktop( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Startup( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Programs( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString StartMenu( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Recent( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SendTo( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Documents( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Favorites( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString NetHood( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PrintHood( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Templates( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString CommonStartup( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString CommonPrograms( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString CommonStartMenu( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PublicDesktop( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ProgramData( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString CommonTemplates( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PublicDocuments( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString RoamingAppData( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString LocalAppData( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString LocalAppDataLow( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString InternetCache( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Cookies( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString History( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString System( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SystemX86( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Windows( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Profile( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Pictures( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ProgramFilesX86( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ProgramFilesCommonX86( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ProgramFilesX64( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ProgramFilesCommonX64( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ProgramFiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ProgramFilesCommon( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString UserProgramFiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString UserProgramFilesCommon( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString AdminTools( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString CommonAdminTools( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Music( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Videos( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Ringtones( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PublicPictures( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PublicMusic( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PublicVideos( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PublicRingtones( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ResourceDir( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString LocalizedResourcesDir( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString CommonOEMLinks( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString CDBurning( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString UserProfiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Playlists( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SamplePlaylists( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SampleMusic( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SamplePictures( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SampleVideos( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PhotoAlbums( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Public( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ChangeRemovePrograms( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString AppUpdates( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString AddNewPrograms( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Downloads( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PublicDownloads( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SavedSearches( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString QuickLaunch( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Contacts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SidebarParts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SidebarDefaultParts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PublicGameTasks( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString GameTasks( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SavedGames( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Games( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SEARCH_MAPI( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SEARCH_CSC( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Links( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString UsersFiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString UsersLibraries( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString SearchHome( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString OriginalImages( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString DocumentsLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString MusicLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PicturesLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString VideosLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString RecordedTVLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString HomeGroup( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString HomeGroupCurrentUser( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString DeviceMetadataStore( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Libraries( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PublicLibraries( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString UserPinned( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ImplicitAppShortcuts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString AccountPictures( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString PublicUserTiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString AppsFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString ApplicationShortcuts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString RoamingTiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString RoamedTileImages( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT WideString Screenshots( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
        };
    };
}

#endif

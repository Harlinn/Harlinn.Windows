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

    class Environment
    {
        HW_EXPORT Environment( );
    public:
        HW_EXPORT static WideString GetResourceString( const wchar_t* key, ... );
        HW_EXPORT static std::string GetResourceString( const char* key, ... );
        //HW_EXPORT static WideString GetResourceString(const WideString& key, ...);

        HW_EXPORT static WideString NewLine( );
        HW_EXPORT static WideString Expand( const WideString& s );
        HW_EXPORT static WideString Read( const WideString& s );



        class SystemParameters
        {
            HW_EXPORT SystemParameters( );
        public:
            // Desktop
            HW_EXPORT static bool ClearType( );
            HW_EXPORT static void SetClearType( bool theValue, bool sendChange = true, bool updateProfile = true );

            HW_EXPORT static WideString DesktopWallpaper( );
            HW_EXPORT static void SetDesktopWallpaper( const WideString& theValue, bool sendChange = true, bool updateProfile = true );

            HW_EXPORT static bool DropShadow( );
            HW_EXPORT static void SetDropShadow( bool theValue, bool sendChange = true, bool updateProfile = true );

            HW_EXPORT static bool FlatMenu( );
            HW_EXPORT static void SetFlatMenu( bool theValue, bool sendChange = true, bool updateProfile = true );

            HW_EXPORT static bool FontSmoothing( );
            HW_EXPORT static void SetFontSmoothing( bool theValue, bool sendChange = true, bool updateProfile = true );

            HW_EXPORT static UINT FontSmoothingContrast( );
            HW_EXPORT static void SetFontSmoothingContrast( UINT theValue, bool sendChange = true, bool updateProfile = true );

            HW_EXPORT static Windows::FontSmoothingOrientation FontSmoothingOrientation( );
            HW_EXPORT static void SetFontSmoothingOrientation( Windows::FontSmoothingOrientation theValue, bool sendChange = true, bool updateProfile = true );


            HW_EXPORT static Windows::NonClientMetrics NonClientMetrics( );



        };

        class SystemMetrics
        {
            HW_EXPORT SystemMetrics( );
        public:
            HW_EXPORT static int ScreenWidth( );
            HW_EXPORT static int ScreenHeight( );
            HW_EXPORT static SIZE ScreenSize( );
            HW_EXPORT static int VerticalScrollBarWidth( );
            HW_EXPORT static int HorizontalScrollBarHeight( );
            HW_EXPORT static int CaptionHeight( );
            HW_EXPORT static int BorderWidth( );
            HW_EXPORT static int BorderHeight( );
            HW_EXPORT static int VerticalScrollBarThumbHeight( );
            HW_EXPORT static int HorizontalScrollBarThumbWidth( );
            HW_EXPORT static int IconWidth( );
            HW_EXPORT static int IconHeight( );
            HW_EXPORT static SIZE IconSize( );
            HW_EXPORT static int CursorWidth( );
            HW_EXPORT static int CursorHeight( );
            HW_EXPORT static SIZE CursorSize( );
            HW_EXPORT static int MenuBarHeight( );
            HW_EXPORT static int PrimaryDisplayWidth( );
            HW_EXPORT static int PrimaryDisplayHeight( );
            HW_EXPORT static SIZE PrimaryDisplaySize( );
            HW_EXPORT static int KanjiWindowHeight( );
            HW_EXPORT static int MousePresent( );
            HW_EXPORT static int VerticalScrollBarArrowHeight( );
            HW_EXPORT static int HorizontalScrollBarArrowWidth( );
            HW_EXPORT static int IsDebugVersion( );
            HW_EXPORT static int AreMouseButtonsSwapped( );
            HW_EXPORT static int MinimumWindowWidth( );
            HW_EXPORT static int MinimumWindowHeight( );
            HW_EXPORT static SIZE MinimumWindowSize( );
            HW_EXPORT static int CaptionButtonWidth( );
            HW_EXPORT static int CaptionButtonHeight( );
            HW_EXPORT static SIZE CaptionButtonSize( );
            HW_EXPORT static int SizeableBorderWidth( );
            HW_EXPORT static int SizeableBorderHeight( );
            HW_EXPORT static int MinimumWindowResizableWidth( );
            HW_EXPORT static int MinimumWindowResizableHeight( );
            HW_EXPORT static int DoubleClickAreaWidth( );
            HW_EXPORT static int DoubleClickAreaHeight( );
            HW_EXPORT static SIZE DoubleClickAreaSize( );
            HW_EXPORT static int IconViewCellWidth( );
            HW_EXPORT static int IconViewCellHeight( );
            HW_EXPORT static SIZE IconViewCellSize( );
            HW_EXPORT static int DropDownMenusAreRightAligned( );
            HW_EXPORT static int IsWindowsPenEnabled( );
            HW_EXPORT static int DBCSEnabled( );
            HW_EXPORT static int NumberOfMouseButtons( );
            HW_EXPORT static int FixedBorderWidth( );
            HW_EXPORT static int FixedBorderHeight( );

            HW_EXPORT static int EdgeBorderWidth( );
            HW_EXPORT static int EdgeBorderHeight( );
            HW_EXPORT static int MinimizedWindowCellWidth( );
            HW_EXPORT static int MinimizedWindowCellHeight( );
            HW_EXPORT static int SmallIconWidth( );
            HW_EXPORT static int SmallIconHeight( );
            HW_EXPORT static SIZE SmallIconSize( );
            HW_EXPORT static int SmallCaptionHeight( );
            HW_EXPORT static int SmallCaptionButtonWidth( );
            HW_EXPORT static int SmallCaptionButtonHeight( );
            HW_EXPORT static SIZE SmallCaptionButtonSize( );
            HW_EXPORT static int MenuBarButtonWidth( );
            HW_EXPORT static int MenuBarButtonHeight( );
            HW_EXPORT static SIZE MenuBarButtonSize( );
            HW_EXPORT static int MinimizedWindowsArragement( );
            HW_EXPORT static int MinimizedWindowWidth( );
            HW_EXPORT static int MinimizedWindowHeight( );
            HW_EXPORT static int MaximumWindowResizableWidth( );
            HW_EXPORT static int MaximumWindowResizableHeight( );
            HW_EXPORT static int PrimaryDisplayMaximumWindowWidth( );
            HW_EXPORT static int PrimaryDisplayMaximumWindowHeight( );
            HW_EXPORT static int NetworkIsPresent( );
            HW_EXPORT static int CleanBoot( );
            HW_EXPORT static int MinimumNoDragHorizontalMouseMovement( );
            HW_EXPORT static int MinimumNoDragVerticalMouseMovement( );
            HW_EXPORT static int ShowSounds( );
            HW_EXPORT static int MenuCheckMarkWidth( );
            HW_EXPORT static int MenuCheckMarkHeight( );
            HW_EXPORT static SIZE MenuCheckMarkSize( );
            HW_EXPORT static int SlowMachine( );
            HW_EXPORT static int MiddleEastEnabled( );
            HW_EXPORT static int MouseWheelPresent( );
            HW_EXPORT static int VirtualScreenXPosition( );
            HW_EXPORT static int VirtualScreenYPosition( );
            HW_EXPORT static POINT VirtualScreenPosition( );
            HW_EXPORT static int VirtualScreenWidth( );
            HW_EXPORT static int VirtualScreenHeight( );
            HW_EXPORT static SIZE VirtualScreenSize( );
            HW_EXPORT static int NumberOfMonitors( );
            HW_EXPORT static int MonitorsHasSameDisplayFormat( );
            HW_EXPORT static int InputMethodManagerEnabled( );
            HW_EXPORT static int FocusedBorderWidth( );
            HW_EXPORT static int FocusedBorderHeight( );
            HW_EXPORT static int TabletPC( );
            HW_EXPORT static int MediaCenterPC( );
            HW_EXPORT static int StarterEdition( );
            HW_EXPORT static int WindowsServer2003R2BuildNumber( );
            HW_EXPORT static int MouseHorizontalWheelPresent( );
            HW_EXPORT static int CaptionedWindowBorderPadding( );
            HW_EXPORT static int TabletPCInputTypeFlags( );
            HW_EXPORT static int MaximumTouches( );
            HW_EXPORT static int InTerminalServicesClientSession( );
            HW_EXPORT static int ShuttingDown( );
            HW_EXPORT static int IsTerminalServerSessionRemoteControlled( );
            HW_EXPORT static int IsCaretBlinkingEnabled( );
            HW_EXPORT static int ConvertibleSlateMode( );
            HW_EXPORT static int IsSystemDocked( );

        };



        class ComputerName
        {
            HW_EXPORT ComputerName( );
            HW_EXPORT static WideString QueryComputerName( COMPUTER_NAME_FORMAT format );
        public:

            HW_EXPORT static WideString DnsDomain( );
            HW_EXPORT static WideString DnsFullyQualified( );
            HW_EXPORT static WideString DnsHostname( );
            HW_EXPORT static WideString NetBIOS( );
            HW_EXPORT static WideString PhysicalDnsDomain( );
            HW_EXPORT static WideString PhysicalDnsFullyQualified( );
            HW_EXPORT static WideString PhysicalDnsHostname( );
            HW_EXPORT static WideString PhysicalNetBIOS( );
        };


        class UserName
        {
            HW_EXPORT UserName( );
            HW_EXPORT static WideString QueryUserName( EXTENDED_NAME_FORMAT format );
        public:
            HW_EXPORT static WideString FullyQualifiedDN( );
            HW_EXPORT static WideString SamCompatible( );
            HW_EXPORT static WideString Display( );
            HW_EXPORT static WideString UniqueId( );
            HW_EXPORT static WideString Canonical( );
            HW_EXPORT static WideString UserPrincipal( );
            HW_EXPORT static WideString CanonicalEx( );
            HW_EXPORT static WideString ServicePrincipal( );
            HW_EXPORT static WideString DnsDomain( );
            HW_EXPORT static WideString GivenName( );
            HW_EXPORT static WideString Surname( );

        };


        class KnownFolder
        {
            HW_EXPORT KnownFolder( );
            HW_EXPORT static WideString QueryKnownFolder( const GUID& folderId, KnownFolderFlags flags, HANDLE userToken );
        public:

            HW_EXPORT static WideString NetworkFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ComputerFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString InternetFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ControlPanelFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PrintersFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SyncManagerFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SyncSetupFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ConflictFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SyncResultsFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString RecycleBinFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ConnectionsFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Fonts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Desktop( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Startup( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Programs( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString StartMenu( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Recent( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SendTo( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Documents( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Favorites( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString NetHood( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PrintHood( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Templates( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString CommonStartup( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString CommonPrograms( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString CommonStartMenu( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PublicDesktop( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ProgramData( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString CommonTemplates( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PublicDocuments( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString RoamingAppData( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString LocalAppData( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString LocalAppDataLow( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString InternetCache( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Cookies( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString History( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString System( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SystemX86( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Windows( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Profile( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Pictures( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ProgramFilesX86( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ProgramFilesCommonX86( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ProgramFilesX64( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ProgramFilesCommonX64( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ProgramFiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ProgramFilesCommon( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString UserProgramFiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString UserProgramFilesCommon( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString AdminTools( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString CommonAdminTools( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Music( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Videos( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Ringtones( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PublicPictures( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PublicMusic( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PublicVideos( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PublicRingtones( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ResourceDir( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString LocalizedResourcesDir( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString CommonOEMLinks( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString CDBurning( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString UserProfiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Playlists( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SamplePlaylists( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SampleMusic( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SamplePictures( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SampleVideos( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PhotoAlbums( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Public( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ChangeRemovePrograms( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString AppUpdates( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString AddNewPrograms( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Downloads( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PublicDownloads( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SavedSearches( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString QuickLaunch( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Contacts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SidebarParts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SidebarDefaultParts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PublicGameTasks( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString GameTasks( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SavedGames( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Games( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SEARCH_MAPI( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SEARCH_CSC( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Links( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString UsersFiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString UsersLibraries( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString SearchHome( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString OriginalImages( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString DocumentsLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString MusicLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PicturesLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString VideosLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString RecordedTVLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString HomeGroup( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString HomeGroupCurrentUser( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString DeviceMetadataStore( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Libraries( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PublicLibraries( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString UserPinned( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ImplicitAppShortcuts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString AccountPictures( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString PublicUserTiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString AppsFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString ApplicationShortcuts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString RoamingTiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString RoamedTileImages( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static WideString Screenshots( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
        };
    };
}

#endif

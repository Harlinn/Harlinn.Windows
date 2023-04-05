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
        std::wstring DefaultScheme;
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
        HW_EXPORT static std::wstring GetResourceString( const wchar_t* key, ... );
        HW_EXPORT static std::string GetResourceString( const char* key, ... );
        //HW_EXPORT static std::wstring GetResourceString(const std::wstring& key, ...);

        HW_EXPORT static std::wstring NewLine( );
        HW_EXPORT static std::wstring Expand( const std::wstring& s );
        HW_EXPORT static std::wstring Read( const std::wstring& s );



        class SystemParameters
        {
            HW_EXPORT SystemParameters( );
        public:
            // Desktop
            HW_EXPORT static bool ClearType( );
            HW_EXPORT static void SetClearType( bool theValue, bool sendChange = true, bool updateProfile = true );

            HW_EXPORT static std::wstring DesktopWallpaper( );
            HW_EXPORT static void SetDesktopWallpaper( const std::wstring& theValue, bool sendChange = true, bool updateProfile = true );

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
            HW_EXPORT static std::wstring QueryComputerName( COMPUTER_NAME_FORMAT format );
        public:

            HW_EXPORT static std::wstring DnsDomain( );
            HW_EXPORT static std::wstring DnsFullyQualified( );
            HW_EXPORT static std::wstring DnsHostname( );
            HW_EXPORT static std::wstring NetBIOS( );
            HW_EXPORT static std::wstring PhysicalDnsDomain( );
            HW_EXPORT static std::wstring PhysicalDnsFullyQualified( );
            HW_EXPORT static std::wstring PhysicalDnsHostname( );
            HW_EXPORT static std::wstring PhysicalNetBIOS( );
        };


        class UserName
        {
            HW_EXPORT UserName( );
            HW_EXPORT static std::wstring QueryUserName( EXTENDED_NAME_FORMAT format );
        public:
            HW_EXPORT static std::wstring FullyQualifiedDN( );
            HW_EXPORT static std::wstring SamCompatible( );
            HW_EXPORT static std::wstring Display( );
            HW_EXPORT static std::wstring UniqueId( );
            HW_EXPORT static std::wstring Canonical( );
            HW_EXPORT static std::wstring UserPrincipal( );
            HW_EXPORT static std::wstring CanonicalEx( );
            HW_EXPORT static std::wstring ServicePrincipal( );
            HW_EXPORT static std::wstring DnsDomain( );
            HW_EXPORT static std::wstring GivenName( );
            HW_EXPORT static std::wstring Surname( );

        };


        class KnownFolder
        {
            HW_EXPORT KnownFolder( );
            HW_EXPORT static std::wstring QueryKnownFolder( const GUID& folderId, KnownFolderFlags flags, HANDLE userToken );
        public:

            HW_EXPORT static std::wstring NetworkFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ComputerFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring InternetFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ControlPanelFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PrintersFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SyncManagerFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SyncSetupFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ConflictFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SyncResultsFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring RecycleBinFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ConnectionsFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Fonts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Desktop( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Startup( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Programs( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring StartMenu( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Recent( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SendTo( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Documents( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Favorites( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring NetHood( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PrintHood( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Templates( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring CommonStartup( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring CommonPrograms( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring CommonStartMenu( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PublicDesktop( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ProgramData( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring CommonTemplates( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PublicDocuments( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring RoamingAppData( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring LocalAppData( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring LocalAppDataLow( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring InternetCache( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Cookies( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring History( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring System( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SystemX86( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Windows( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Profile( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Pictures( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ProgramFilesX86( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ProgramFilesCommonX86( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ProgramFilesX64( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ProgramFilesCommonX64( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ProgramFiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ProgramFilesCommon( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring UserProgramFiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring UserProgramFilesCommon( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring AdminTools( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring CommonAdminTools( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Music( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Videos( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Ringtones( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PublicPictures( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PublicMusic( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PublicVideos( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PublicRingtones( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ResourceDir( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring LocalizedResourcesDir( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring CommonOEMLinks( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring CDBurning( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring UserProfiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Playlists( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SamplePlaylists( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SampleMusic( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SamplePictures( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SampleVideos( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PhotoAlbums( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Public( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ChangeRemovePrograms( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring AppUpdates( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring AddNewPrograms( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Downloads( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PublicDownloads( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SavedSearches( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring QuickLaunch( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Contacts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SidebarParts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SidebarDefaultParts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PublicGameTasks( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring GameTasks( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SavedGames( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Games( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SEARCH_MAPI( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SEARCH_CSC( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Links( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring UsersFiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring UsersLibraries( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring SearchHome( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring OriginalImages( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring DocumentsLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring MusicLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PicturesLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring VideosLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring RecordedTVLibrary( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring HomeGroup( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring HomeGroupCurrentUser( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring DeviceMetadataStore( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Libraries( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PublicLibraries( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring UserPinned( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ImplicitAppShortcuts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring AccountPictures( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring PublicUserTiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring AppsFolder( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring ApplicationShortcuts( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring RoamingTiles( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring RoamedTileImages( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
            HW_EXPORT static std::wstring Screenshots( KnownFolderFlags flags = KnownFolderFlags::Default, HANDLE userToken = nullptr );
        };
    };
}

#endif

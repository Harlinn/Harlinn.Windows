#pragma once
#ifndef __HWCONTROL_H__
#define __HWCONTROL_H__
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
#include <HWMessage.h>
#include <HWKeys.h>
#include <HWMouseButton.h>
#include <HWWindowClass.h>
#include <HWHandles.h>

namespace Harlinn::Windows
{


    enum class AnchorStyles : int
    {
        None = 0,
        Top = 1,
        Bottom = 2,
        Left = 4,
        Right = 8
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( AnchorStyles, int );


    enum class HorizontalAlignment : int
    {
        Left = 0,
        Right = 1,
        Center = 2
    };


    enum class ContentAlignment
    {
        TopLeft = 1,
        TopCenter = 2,
        TopRight = 4,
        MiddleLeft = 16,
        MiddleCenter = 32,
        MiddleRight = 64,
        BottomLeft = 256,
        BottomCenter = 512,
        BottomRight = 1024
    };


    enum class DockStyle
    {
        // The control is not docked.
        None = 0,
        // The control's top edge is docked to the top of its containing control.
        Top = 1,
        // The control's bottom edge is docked to the bottom of its containing control.
        Bottom = 2,
        // The control's left edge is docked to the left edge of its containing control.
        Left = 3,
        // The control's right edge is docked to the right edge of its containing control.
        Right = 4,
        // All the control's edges are docked to the all edges of its containing control
        // and sized appropriately.
        Fill = 5,
    };



    enum class WindowStyle : DWORD
    {
        Overlapped = WS_OVERLAPPED,
        Popup = WS_POPUP,
        Child = WS_CHILD,
        Minimize = WS_MINIMIZE,
        Visible = WS_VISIBLE,
        Disabled = WS_DISABLED,
        ClipSiblings = WS_CLIPSIBLINGS,
        ClipChildren = WS_CLIPCHILDREN,
        Maximize = WS_MAXIMIZE,
        Caption = WS_CAPTION,
        Border = WS_BORDER,
        DialogFrame = WS_DLGFRAME,
        VerticalScrollbar = WS_VSCROLL,
        HorizontalScrollbar = WS_HSCROLL,
        SystemMenu = WS_SYSMENU,
        ThickFrame = WS_THICKFRAME,
        Group = WS_GROUP,
        TabStop = WS_TABSTOP,
        MinimizeButton = WS_MINIMIZEBOX,
        MaximizeButton = WS_MAXIMIZEBOX,
        Tiled = WS_TILED,
        Iconic = WS_ICONIC,
        SizeButton = WS_SIZEBOX,
        TiledWindow = WS_TILEDWINDOW,
        OverlappedWindow = WS_OVERLAPPEDWINDOW,
        PopupWindow = WS_POPUPWINDOW,
        ChildWindow = WS_CHILDWINDOW
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( WindowStyle, DWORD );

    enum class ExtendedWindowStyle : DWORD
    {
        DialogModalFrame = WS_EX_DLGMODALFRAME,
        NoParentNotify = WS_EX_NOPARENTNOTIFY,
        Topmost = WS_EX_TOPMOST,
        AcceptFiles = WS_EX_ACCEPTFILES,
        Transparent = WS_EX_TRANSPARENT,
        MdiChild = WS_EX_MDICHILD,
        ToolWindow = WS_EX_TOOLWINDOW,
        WindowEdge = WS_EX_WINDOWEDGE,
        ClientEdge = WS_EX_CLIENTEDGE,
        ContextHelp = WS_EX_CONTEXTHELP,
        Right = WS_EX_RIGHT,
        Left = WS_EX_LEFT,
        RightToLeftReading = WS_EX_RTLREADING,
        LeftToRightReading = WS_EX_LTRREADING,
        LeftScrollbar = WS_EX_LEFTSCROLLBAR,
        RightScrollbar = WS_EX_RIGHTSCROLLBAR,
        ControlParent = WS_EX_CONTROLPARENT,
        StaticEdge = WS_EX_STATICEDGE,
        AppWindow = WS_EX_APPWINDOW,
        OverlappedWindow = WS_EX_OVERLAPPEDWINDOW,
        PaletteWindow = WS_EX_PALETTEWINDOW,
        Layered = WS_EX_LAYERED,
        NoInheritLayout = WS_EX_NOINHERITLAYOUT,
        NoreDirectionBitmap = WS_EX_NOREDIRECTIONBITMAP,
        LayoutRightToLeft = WS_EX_LAYOUTRTL,
        composited = WS_EX_COMPOSITED,
        NoActivate = WS_EX_NOACTIVATE

    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ExtendedWindowStyle, DWORD );



    class Control;
    // --------------------------------------------------------------------
    // Controls
    // --------------------------------------------------------------------
    class Controls 
    {
        friend class Control;
    public:
        typedef std::vector< Control* > vector;

    private:
        vector items_;
        Control& control_;

        HW_EXPORT void DoOnHandleCreated( );
        HW_EXPORT void DoBeforeHandleDestroy( );
        HW_EXPORT void Remove( const Control* control );
        HW_EXPORT void Add( Control* control );
        HW_EXPORT void DisconnectParentControl( );

    public:
        HW_EXPORT Controls( Control& control );
        HW_EXPORT bool Contains( const Control* childControl ) const;

        Controls( const Controls& other ) = delete;
        Controls( Controls&& other ) = delete;
        Controls& operator = ( const Controls& other ) = delete;
        Controls& operator = ( Controls&& other ) = delete;

    };


    // --------------------------------------------------------------------
    // Control
    // --------------------------------------------------------------------
    class ComControl;
    class Control
    {
        friend class MessageDispatcherBase;
        friend class Controls;
        friend class ComControl;

        HWND handle_;
        Control* parentControl_;

        Point position_;

        Windows::Size size_;

        LONG id_;
        Windows::Controls controls_;
        WideString text_;
        bool automaticallyAddParentlessOwnedControls_;

        AnchorStyles anchorStyles_;
        bool enabled_ : 1;
        bool visible_ : 1;
        bool tabStop_ : 1;
        bool recreatingHandle_ : 1;

        DockStyle dock_;

        WNDPROC originalWindowsProcedure_;

    protected:
        HW_EXPORT static UINT REFLECTED_WM_COMMAND;
        HW_EXPORT static UINT REFLECTED_WM_NOTIFY;
        HW_EXPORT static UINT REFLECTED_WM_DRAWITEM;
        HW_EXPORT static UINT WM_GET_CONTROL;  
    public:

        HW_EXPORT Control( );
        HW_EXPORT virtual ~Control( );

    protected:
        HW_EXPORT virtual void DoOnInitialize( );

        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;

        HW_EXPORT virtual DWORD GetStyle( ) const;
        HW_EXPORT virtual DWORD GetStyleEx( ) const;

        HW_EXPORT Control& SetWindowStyle( DWORD theStyle );
        HW_EXPORT Control& SetWindowStyleEx( DWORD theExStyle );

        bool IsRecreatingHandle( ) const { return recreatingHandle_; };
        HW_EXPORT void RecreateHandle( );
        HW_EXPORT virtual void DoOnBeforeRecreatingHandle( );
        HW_EXPORT virtual void DoOnAfterRecreatingHandle( );
    public:
        HW_EXPORT bool IsChild( ) const;
        HW_EXPORT bool IsToplevel( ) const;
        HW_EXPORT bool IsPopup( ) const;

        HW_EXPORT bool Enabled( ) const;
        HW_EXPORT Control& SetEnabled( bool theValue );

        HW_EXPORT bool Visible( ) const;
        HW_EXPORT Control& SetVisible( bool theValue );

        HW_EXPORT bool TabStop( ) const;
        HW_EXPORT Control& SetTabStop( bool theValue );
    protected:
        HW_EXPORT virtual void DoOnSetEnabled( bool theValue );
    public:
        HW_EXPORT long Id( ) const;
        HW_EXPORT Control& SetId( long theValue );

    protected:
        HW_EXPORT virtual HWND CreateHandle( );
        HW_EXPORT virtual void DoOnHandleCreated( );

        HW_EXPORT virtual void DestroyHandle( );
        HW_EXPORT virtual void DoBeforeHandleDestroy( );
    private:
        HW_EXPORT void DisconnectParentControl( );

        HW_EXPORT Control& RestoreSubClassedWindowsProcedure( );
        static LRESULT CALLBACK SubClassWndProc( HWND hWnd, UINT messageId, WPARAM wParam, LPARAM lParam );
    public:
        HW_EXPORT Control& SubClass( HWND hWnd );
        HW_EXPORT bool IsSubClassed( ) const;
    protected:
        HW_EXPORT virtual void DoOnWindowSubClassed( );
    public:

        HW_EXPORT HWND GetHandle( ) const;
        bool IsHandleCreated( ) const
        {
            return handle_ != 0;
        }
    protected:
        HW_EXPORT virtual void HandleMessage( Message& message );

        HW_EXPORT static void RegisterControl( HWND hWnd, Control* constrol );
        HW_EXPORT static void UnregisterControl( HWND hWnd );
        HW_EXPORT static Control* GetControlFromHWND( HWND hWnd );
    public:
        HW_EXPORT const Control& GetClientRect( RECT* rectangle ) const;
        HW_EXPORT const Control& GetClientRect( RECT& rectangle ) const;
        HW_EXPORT RECT GetClientRect( ) const;
        HW_EXPORT D2D1_SIZE_F ClientSize( ) const;
        HW_EXPORT UInt32 GetDotsPerInch( ) const;

        void ScreenToClient( POINT& pt ) const
        {
            auto rc = ::ScreenToClient( GetHandle( ), &pt );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }
        void ClientToScreen( POINT& pt ) const
        {
            auto rc = ::ClientToScreen( GetHandle( ), &pt );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        HW_EXPORT Control& SetParent( Control* parentControl );
        const Windows::Controls& Controls( ) const
        {
            return controls_;
        }
        Windows::Controls& Controls( )
        {
            return controls_;
        }
        Control* Parent( ) const
        {
            return parentControl_;
        }
        bool HasParent( ) const
        {
            return parentControl_ != nullptr;
        }


        HDC BeginPaint( PAINTSTRUCT& paintStruct ) const
        {
            auto hdc = ::BeginPaint( GetHandle( ), &paintStruct );
            if ( !hdc )
            {
                ThrowLastOSError( );
            }
            return hdc;
        }
        void EndPaint( const PAINTSTRUCT& paintStruct ) const
        {
            auto rc = ::EndPaint( GetHandle( ), &paintStruct );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        HW_EXPORT const Control& UpdateRect( RECT& updateRectangle ) const;
        HW_EXPORT Control& UpdateRect( RECT& updateRectangle, bool erase );
        HW_EXPORT RECT UpdateRect( ) const;
        HW_EXPORT RECT UpdateRect( bool erase );


        //HW_EXPORT std::vector< Control* > GetChildren() const;


        HW_EXPORT bool IsChildOf( const Control& parentControl ) const;
        HW_EXPORT bool IsChildOf( HWND parentControl ) const;

        HW_EXPORT bool IsParentOf( const Control& childControl ) const;
        HW_EXPORT bool IsParentOf( HWND childControl ) const;

        HW_EXPORT bool IsValid( ) const;

        HW_EXPORT bool IsVisible( ) const;

        HW_EXPORT Control& InvalidateRect( bool erase = false );
        HW_EXPORT Control& InvalidateRect( const RECT& rectangle, bool erase = false );


        HW_EXPORT Control& MoveWindow( int x, int y, int width, int height, bool repaint = false );

        HW_EXPORT LONG SetWindowLong( int index, LONG newValue );
        HW_EXPORT LONG GetWindowLong( int index ) const;

        HW_EXPORT LRESULT SendMessage( UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0 ) const;
        HW_EXPORT const Control& PostMessage( UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0 ) const;


        HW_EXPORT int TextLength( ) const;
        HW_EXPORT WideString Text( ) const;
        HW_EXPORT bool SetText( const WideString& text );
        HW_EXPORT bool SetText( const wchar_t* text );

        HW_EXPORT bool Show( );
        HW_EXPORT bool ValidateRect( const RECT& rectangle );
        HW_EXPORT bool ValidateRect( );

        const Windows::Size& Size( ) const
        {
            return size_;
        }
        HW_EXPORT Control& SetSize( int width, int height );
        HW_EXPORT Control& SetSize( const Windows::Size& theSize );

        const Point& Position( ) const
        {
            return position_;
        }

        HW_EXPORT Control& SetPosition( int x, int y );
        HW_EXPORT Control& SetPosition( const Point& thePosition );

        HWND SetFocus( ) const
        {
            auto result = ::SetFocus( GetHandle() );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        HW_EXPORT Control& Initialize( );
        HW_EXPORT Control& Initialize( Control* owner );

        boost::signals2::signal<void( Control* sender )> OnHandleCreated;
        boost::signals2::signal<void( Control* sender )> OnBeforeHandleDestroy;


        boost::signals2::signal<void( Control* sender, Message& message )> OnCancelMode;
        boost::signals2::signal<void( Control* sender, Message& message )> OnChar;
        boost::signals2::signal<void( Control* sender, Message& message )> OnCharToItem;
        boost::signals2::signal<void( Control* sender, Message& message )> OnClose;
        boost::signals2::signal<void( Control* sender, Message& message )> OnCompareItem;
        boost::signals2::signal<void( Control* sender, Message& message )> OnCommand;
        boost::signals2::signal<void( Control* sender, Message& message )> OnCopyData;
        boost::signals2::signal<void( Control* sender, Message& message )> OnDeadChar;
        boost::signals2::signal<void( Control* sender, Message& message )> OnDeleteItem;
        boost::signals2::signal<void( Control* sender, Message& message )> OnDestroy;
        boost::signals2::signal<void( Control* sender, Message& message )> OnDisplayChange;
        boost::signals2::signal<void( Control* sender, Message& message )> OnDrawItem;
        boost::signals2::signal<void( Control* sender, Message& message )> OnEnable;
        boost::signals2::signal<void( Control* sender, Message& message )> OnEnterSizeMove;
        boost::signals2::signal<void( Control* sender, Message& message )> OnEraseBackground;
        boost::signals2::signal<void( Control* sender, Message& message )> OnExitSizeMove;
        boost::signals2::signal<void( Control* sender, Message& message )> OnGetHotKey;
        boost::signals2::signal<void( Control* sender, Message& message )> OnGetText;
        boost::signals2::signal<void( Control* sender, Message& message )> OnGetTextLength;
        boost::signals2::signal<void( Control* sender, Message& message )> OnInitMenu;
        boost::signals2::signal<void( Control* sender, Message& message )> OnInitMenuPopup;
        boost::signals2::signal<void( Control* sender, Message& message )> OnKeyDown;
        boost::signals2::signal<void( Control* sender, Message& message )> OnKeyUp;
        boost::signals2::signal<void( Control* sender, Message& message )> OnKillFocus;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMeasureItem;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMenuCommand;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseMove;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseLeftButtonDown;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseLeftButtonUp;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseLeftButtonDoubleClick;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseMiddleButtonDown;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseMiddleButtonUp;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseMiddleButtonDoubleClick;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseRightButtonDown;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseRightButtonUp;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseRightButtonDoubleClick;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseXButtonDown;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseXButtonUp;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseXButtonDoubleClick;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMouseWheel;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMove;
        boost::signals2::signal<void( Control* sender, Message& message )> OnMoving;
        boost::signals2::signal<void( Control* sender, Message& message )> OnNcActivate;
        boost::signals2::signal<void( Control* sender, Message& message )> OnNcCalcSize;
        boost::signals2::signal<void( Control* sender, Message& message )> OnNcDestroy;
        boost::signals2::signal<void( Control* sender, Message& message )> OnNotify;
        boost::signals2::signal<void( Control* sender, Message& message )> OnPaint;
        boost::signals2::signal<void( Control* sender, Message& message )> OnSetCursor;
        boost::signals2::signal<void( Control* sender, Message& message )> OnSetFocus;
        boost::signals2::signal<void( Control* sender, Message& message )> OnSetHotKey;
        boost::signals2::signal<void( Control* sender, Message& message )> OnSetRedraw;
        boost::signals2::signal<void( Control* sender, Message& message )> OnSetText;
        boost::signals2::signal<void( Control* sender, Message& message )> OnShowWindow;
        boost::signals2::signal<void( Control* sender, Message& message )> OnSize;
        boost::signals2::signal<void( Control* sender, Message& message )> OnSizing;
        boost::signals2::signal<void( Control* sender, Message& message )> OnSysChar;
        boost::signals2::signal<void( Control* sender, Message& message )> OnSysCommand;
        boost::signals2::signal<void( Control* sender, Message& message )> OnSysDeadChar;
        boost::signals2::signal<void( Control* sender, Message& message )> OnSysKeyDown;
        boost::signals2::signal<void( Control* sender, Message& message )> OnSysKeyUp;
        boost::signals2::signal<void( Control* sender, Message& message )> OnUniChar;
        boost::signals2::signal<void( Control* sender, Message& message )> OnVKeyToItem;
        boost::signals2::signal<void( Control* sender, Message& message )> OnWindowPosChanging;
        boost::signals2::signal<void( Control* sender, Message& message )> OnWindowPosChanged;

    protected:
        HW_EXPORT virtual bool IsInputChar( wchar_t charCode );
        HW_EXPORT virtual bool IsInputKey( Keys keyData );
        HW_EXPORT virtual bool ProcessMnemonic( wchar_t charCode );

        HW_EXPORT virtual void DoOnCancelMode( Message& message );
        HW_EXPORT virtual void DoOnChar( Message& message );
        HW_EXPORT virtual void DoOnCharToItem( Message& message );
        HW_EXPORT virtual void DoOnClose( Message& message );
        HW_EXPORT virtual void DoOnCompareItem( Message& message );
        HW_EXPORT virtual void DoOnCommand( Message& message );
        HW_EXPORT virtual void DoOnCopyData( Message& message );
        HW_EXPORT virtual void DoOnDeadChar( Message& message );
        HW_EXPORT virtual void DoOnDeleteItem( Message& message );
        HW_EXPORT virtual void DoOnDestroy( Message& message );
        HW_EXPORT virtual void DoOnDisplayChange( Message& message );
        HW_EXPORT virtual void DoOnDrawItem( Message& message );
        HW_EXPORT virtual void DoOnEnable( Message& message );
        HW_EXPORT virtual void DoOnEnterSizeMove( Message& message );
        HW_EXPORT virtual void DoOnEraseBackground( Message& message );
        HW_EXPORT virtual void DoOnExitSizeMove( Message& message );
        HW_EXPORT virtual void DoOnGetHotKey( Message& message );
        HW_EXPORT virtual void DoOnGetText( Message& message );
        HW_EXPORT virtual void DoOnGetTextLength( Message& message );
        HW_EXPORT virtual void DoOnInitMenu( Message& message );
        HW_EXPORT virtual void DoOnInitMenuPopup( Message& message );
        HW_EXPORT virtual void DoOnKeyDown( Message& message );
        HW_EXPORT virtual void DoOnKeyUp( Message& message );
        HW_EXPORT virtual void DoOnKillFocus( Message& message );
        HW_EXPORT virtual void DoOnMeasureItem( Message& message );
        HW_EXPORT virtual void DoOnMenuCommand( Message& message );
        HW_EXPORT virtual void DoOnMouseMove( Message& message );
        HW_EXPORT virtual void DoOnMouseLeftButtonDown( Message& message );
        HW_EXPORT virtual void DoOnMouseLeftButtonUp( Message& message );
        HW_EXPORT virtual void DoOnMouseLeftButtonDoubleClick( Message& message );
        HW_EXPORT virtual void DoOnMouseMiddleButtonDown( Message& message );
        HW_EXPORT virtual void DoOnMouseMiddleButtonUp( Message& message );
        HW_EXPORT virtual void DoOnMouseMiddleButtonDoubleClick( Message& message );
        HW_EXPORT virtual void DoOnMouseRightButtonDown( Message& message );
        HW_EXPORT virtual void DoOnMouseRightButtonUp( Message& message );
        HW_EXPORT virtual void DoOnMouseRightButtonDoubleClick( Message& message );
        HW_EXPORT virtual void DoOnMouseXButtonDown( Message& message );
        HW_EXPORT virtual void DoOnMouseXButtonUp( Message& message );
        HW_EXPORT virtual void DoOnMouseXButtonDoubleClick( Message& message );
        HW_EXPORT virtual void DoOnMouseWheel( Message& message );
        HW_EXPORT virtual void DoOnMove( Message& message );
        HW_EXPORT virtual void DoOnMoving( Message& message );
        HW_EXPORT virtual void DoOnNcActivate( Message& message );
        HW_EXPORT virtual void DoOnNcCalcSize( Message& message );
        HW_EXPORT virtual void DoOnNcDestroy( Message& message );
        HW_EXPORT virtual void DoOnNotify( Message& message );
        HW_EXPORT virtual void DoOnPaint( Message& message );
        HW_EXPORT virtual void DoOnSetCursor( Message& message );
        HW_EXPORT virtual void DoOnSetFocus( Message& message );
        HW_EXPORT virtual void DoOnSetHotKey( Message& message );
        HW_EXPORT virtual void DoOnSetRedraw( Message& message );
        HW_EXPORT virtual void DoOnSetText( Message& message );
        HW_EXPORT virtual void DoOnShowWindow( Message& message );
        HW_EXPORT virtual void DoOnSize( Message& message );
        HW_EXPORT virtual void DoOnSizing( Message& message );
        HW_EXPORT virtual void DoOnSysChar( Message& message );
        HW_EXPORT virtual void DoOnSysCommand( Message& message );
        HW_EXPORT virtual void DoOnSysDeadChar( Message& message );
        HW_EXPORT virtual void DoOnSysKeyDown( Message& message );
        HW_EXPORT virtual void DoOnSysKeyUp( Message& message );
        HW_EXPORT virtual void DoOnUniChar( Message& message );
        HW_EXPORT virtual void DoOnVKeyToItem( Message& message );
        HW_EXPORT virtual void DoOnWindowPosChanging( Message& message );
        HW_EXPORT virtual void DoOnWindowPosChanged( Message& message );

    };



    template< typename T >
    std::unique_ptr<T> make_control( )
    {
        auto result = std::make_unique<T>( );
        result->Initialize( );
        return result;
    }

    template< typename T >
    std::unique_ptr<T> make_control( Control* parentControl )
    {
        auto result = std::make_unique<T>( );
        result->SetParent( parentControl );
        result->Initialize( parentControl );
        return result;
    }

    template< typename T, typename A >
    std::unique_ptr<T> make_control( Control* parentControl, const A& argument )
    {
        auto result = std::make_unique<T>( argument );
        result->SetParent( parentControl );
        result->Initialize( parentControl );
        return result;
    }


    template< typename T, typename A1, typename A2 >
    std::unique_ptr<T> make_control( const Control* parentControl, const A1& argument1, const A2& argument2 )
    {
        auto result = std::make_unique<T>( argument1, argument2 );
        result->SetParent( parentControl );
        result->Initialize( parentControl );
        return result;
    }



    // --------------------------------------------------------------------
    // MessageDispatcherBase
    // --------------------------------------------------------------------
    class MessageDispatcherBase
    {
    protected:
        static void HandleMessage( Control* control, Message& message )
        {
            control->HandleMessage( message );
        }

        static void RegisterControl( HWND hWnd, Control* control )
        {
            Control::RegisterControl( hWnd, control );
        }

        static void UnregisterControl( HWND hWnd )
        {
            Control::UnregisterControl( hWnd );
        }

    };


    // --------------------------------------------------------------------
    // ControlMessageDispatcher
    // --------------------------------------------------------------------
    template< typename ControlClass_ >
    class ControlMessageDispatcher : public MessageDispatcherBase
    {
    public:
        static LRESULT CALLBACK WndProc( HWND hWnd, UINT messageId, WPARAM wParam, LPARAM lParam )
        {
            Message message;
            message.hwnd = hWnd;
            message.message = messageId;
            message.wParam = wParam;
            message.lParam = lParam;
            message.time = GetMessageTime( );
            DWORD pos = GetMessagePos( );

            message.pt.x = GET_X_LPARAM( pos );
            message.pt.y = GET_Y_LPARAM( pos );

            LONG_PTR userData = (LONG_PTR)0;

            if ( messageId == WM_NCCREATE )
            {
                CREATESTRUCT* createStruct = (CREATESTRUCT*)lParam;
                if ( createStruct != nullptr )
                {
                    userData = (LONG_PTR)createStruct->lpCreateParams;
                    if ( userData )
                    {
                        SetWindowLongPtr( hWnd, GWLP_USERDATA, userData );
                        Control* control = (Control*)userData;
                        RegisterControl( hWnd, control );
                    }
                }
            }
            else
            {
                userData = GetWindowLongPtr( hWnd, GWLP_USERDATA );

            }

            if ( userData )
            {
                Control* control = (Control*)userData;

                HandleMessage( control, message );
                if ( message.handled )
                {
                    return message.result;
                }
            }
            if ( !message.handled )
            {
                message.result = DefWindowProc( hWnd, message.message, message.wParam, message.lParam );
            }

            if ( messageId == WM_NCDESTROY )
            {
                UnregisterControl( hWnd );
            }

            return message.result;
        }
    };


    template< typename ControlClass_ >
    class SuperClassMessageDispatcher : public MessageDispatcherBase
    {
    public:
        static WNDPROC ControlProcedure;
        static LRESULT CALLBACK WndProc( HWND hWnd, UINT messageId, WPARAM wParam, LPARAM lParam )
        {
            Message message;
            message.hwnd = hWnd;
            message.message = messageId;
            message.wParam = wParam;
            message.lParam = lParam;
            message.time = GetMessageTime( );
            DWORD pos = GetMessagePos( );

            message.pt.x = GET_X_LPARAM( pos );
            message.pt.y = GET_Y_LPARAM( pos );

            LONG_PTR userData = (LONG_PTR)0;

            if ( messageId == WM_NCCREATE )
            {
                CREATESTRUCT* createStruct = (CREATESTRUCT*)lParam;
                if ( createStruct != nullptr )
                {
                    userData = (LONG_PTR)createStruct->lpCreateParams;
                    if ( userData )
                    {
                        SetWindowLongPtr( hWnd, GWLP_USERDATA, userData );
                        Control* control = (Control*)userData;
                        RegisterControl( hWnd, control );
                    }
                }
            }
            else
            {
                userData = GetWindowLongPtr( hWnd, GWLP_USERDATA );
            }

            if ( userData )
            {
                Control* control = (Control*)userData;

                HandleMessage( control, message );
                if ( message.handled )
                {
                    return message.result;
                }
            }
            if ( !message.handled )
            {
                message.result = ControlProcedure( hWnd, message.message, message.wParam, message.lParam );
            }

            if ( messageId == WM_NCDESTROY )
            {
                UnregisterControl( hWnd );
            }

            return message.result;
        }
    };


}

#endif

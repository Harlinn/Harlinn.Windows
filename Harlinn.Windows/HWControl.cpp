#include "pch.h"
#include <HWControl.h>
#include <HWApplication.h>
#include <HWKeys.h>

namespace Harlinn::Windows
{

    // --------------------------------------------------------------------
    // Controls
    // --------------------------------------------------------------------
    Controls::Controls( Control& control )
        : control_( control )
    {

    }



    void Controls::DoOnHandleCreated( )
    {
        for ( auto item : items_ )
        {
            item->GetHandle( );
        }
    }

    void Controls::DoBeforeHandleDestroy( )
    {
    }

    void Controls::Remove( const Control* control )
    {
        if ( control )
        {
            auto it = std::find( items_.begin( ), items_.end( ), control );
            if ( it != items_.end( ) )
            {
                items_.erase( it );
            }
        }
    }
    void Controls::Add( Control* control )
    {
        if ( control )
        {
            if ( Contains( control ) == false )
            {
                items_.push_back( control );
            }
        }
    }


    void Controls::DisconnectParentControl( )
    {
        for ( auto item : items_ )
        {
            item->DisconnectParentControl( );
        }
    }



    bool Controls::Contains( const Control* childControl ) const
    {
        bool result = false;
        if ( childControl )
        {
            auto it = std::find( items_.begin( ), items_.end( ), childControl );
            if ( it != items_.end( ) )
            {
                result = true;
            }
        }
        return result;
    }

    // --------------------------------------------------------------------
    // ControlWindowClass
    // --------------------------------------------------------------------
    class ControlWindowClass : public WindowClass
    {
    public:
        static std::wstring ClassName;

        ControlWindowClass( );
    };

    std::wstring ControlWindowClass::ClassName = std::wstring( L"HarlinnWindowsControlWindowClassName" );

    typedef ControlMessageDispatcher<Control> DefaultControlMessageDispatcher;

    ControlWindowClass::ControlWindowClass( )
    {
        SetName( ClassName );
        WNDPROC procedure = DefaultControlMessageDispatcher::WndProc;
        SetProcedure( procedure );

    }


    // --------------------------------------------------------------------
    // Control
    // --------------------------------------------------------------------
    UINT Control::REFLECTED_WM_COMMAND = RegisterWindowMessageW( L"Control::REFLECTED_WM_COMMAND" );
    UINT Control::REFLECTED_WM_NOTIFY = RegisterWindowMessageW( L"Control::REFLECTED_WM_NOTIFY" );
    UINT Control::REFLECTED_WM_DRAWITEM = RegisterWindowMessageW( L"Control::REFLECTED_WM_DRAWITEM" );
    UINT Control::WM_GET_CONTROL = RegisterWindowMessageW( L"Control::WM_GET_CONTROL" );


    Control::Control( )
        : handle_( 0 ),
          parentControl_(nullptr),
          id_( 0 ),
          controls_(*this),
          dock_( DockStyle::None ),
          enabled_( true ),
          visible_( true ),
          tabStop_( true ),
          recreatingHandle_( false ),
          anchorStyles_( AnchorStyles::Left | AnchorStyles::Top ),
          automaticallyAddParentlessOwnedControls_( true ),
          originalWindowsProcedure_( nullptr ),
          position_( CW_USEDEFAULT, CW_USEDEFAULT ),
          size_( CW_USEDEFAULT, CW_USEDEFAULT )
    {

    }


    Control::~Control( )
    {
        SetParent( nullptr );
        DisconnectParentControl( );
        if ( handle_ )
        {
            DestroyHandle( );
        }

    }

    Control& Control::Initialize( )
    {
        this->DoOnInitialize( );
        return *this;
    }
    Control& Control::Initialize( Control* owner )
    {
        Initialize( );
        return *this;
    }

    void Control::DoOnInitialize( )
    {
        
    }


    WindowClass* Control::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( ControlWindowClass::ClassName );
        if ( !windowClass )
        {
            auto newWindowClass = std::make_unique<ControlWindowClass>( );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }

    DWORD Control::GetStyle( ) const
    {
        DWORD result = WS_CHILD;
        if ( visible_ )
        {
            result |= WS_VISIBLE;
        }
        if ( tabStop_ )
        {
            result |= WS_TABSTOP;
        }
        if ( !enabled_ )
        {
            result |= WS_DISABLED;
        }
        return result;
    }


    DWORD Control::GetStyleEx( ) const
    {
        return 0;
    }

    Control& Control::SetWindowStyle( DWORD style )
    {
        SetWindowLong( GWL_STYLE, style );
        return *this;
    }
    Control& Control::SetWindowStyleEx( DWORD extendedStyle )
    {
        SetWindowLong( GWL_EXSTYLE, extendedStyle );
        return *this;
    }

    void Control::RecreateHandle( )
    {
        if ( controls_.items_.size( ) )
        {
            throw InvalidOperationException( L"RecreateHandle called for a control with children" );
        }
        if ( ( IsSubClassed( ) == false ) && ( IsValid( ) ) )
        {
            try
            {
                recreatingHandle_ = true;
                this->DoOnBeforeRecreatingHandle( );
                ::DestroyWindow( handle_ );
                handle_ = this->CreateHandle( );
                this->DoOnAfterRecreatingHandle( );
            }
            catch ( ... )
            {
                recreatingHandle_ = false;
                throw;
            }
            recreatingHandle_ = false;
        }
    }
    void Control::DoOnBeforeRecreatingHandle( )
    {
    }
    void Control::DoOnAfterRecreatingHandle( )
    {
    }



    bool Control::IsChild( ) const
    {
        bool result = ( GetStyle( ) & WS_CHILD ) != 0;
        return result;
    }
    bool Control::IsToplevel( ) const
    {
        bool result = ( GetStyle( ) & WS_CHILD ) == 0;
        return result;
    }
    bool Control::IsPopup( ) const
    {
        bool result = ( GetStyle( ) & WS_POPUP ) != 0;
        return result;
    }


    bool Control::Enabled( ) const
    {
        return enabled_;
    }
    Control& Control::SetEnabled( bool value )
    {
        if ( value != enabled_ )
        {
            this->DoOnSetEnabled( value );
            enabled_ = value;
        }
        return *this;
    }

    bool Control::Visible( ) const
    {
        return visible_;
    }
    Control& Control::SetVisible( bool value )
    {
        if ( visible_ != value )
        {
            visible_ = value;
            if ( IsHandleCreated( ) )
            {
                if ( SetWindowPos( handle_,
                    nullptr,
                    0, 0, 0, 0,
                    SWP_NOSIZE
                    | SWP_NOMOVE
                    | SWP_NOZORDER
                    | SWP_NOACTIVATE
                    | ( value ? SWP_SHOWWINDOW : SWP_HIDEWINDOW ) ) == 0 )
                {
                    ThrowLastOSError( );
                }
            }
        }
        return *this;
    }

    bool Control::TabStop( ) const
    {
        return tabStop_;
    }
    Control& Control::SetTabStop( bool value )
    {
        if ( tabStop_ != value )
        {
            tabStop_ = value;
            if ( IsHandleCreated( ) )
            {
                DWORD style = this->GetStyle( );
                SetWindowStyle( style );
            }
        }
        return *this;
    }


    void Control::DoOnSetEnabled( bool theValue )
    {
    }

    long Control::Id( ) const
    {
        return id_;
    }
    Control& Control::SetId( long value )
    {
        if ( id_ != value )
        {
            id_ = value;
            if ( IsValid( ) )
            {
                SetWindowLong( GWL_ID, value );
            }
        }
        return *this;
    }


    HWND Control::CreateHandle( )
    {
        auto windowClass = this->GetWindowClass( );
        HWND result = nullptr;
        if ( windowClass )
        {
            auto& className = windowClass->Name( );
            if ( className.length( ) )
            {
                HWND hWndParent = 0;
                if ( parentControl_ )
                {
                    hWndParent = parentControl_->GetHandle( );
                }
                result = ::CreateWindowExW( this->GetStyleEx( ),
                    className.c_str( ),
                    nullptr, this->GetStyle( ),
                    position_.X( ), position_.Y( ), size_.Width( ), size_.Height( ),
                    hWndParent, 0, 0, (LPVOID)this );
                if ( !result )
                {
                    ThrowLastOSError( );
                }
                RECT rect = { 0, };
                GetWindowRect( result, &rect );
                size_.Assign( rect.right - rect.left, rect.bottom - rect.top );
                position_.Assign( rect.left, rect.top );
            }
        }
        return result;
    }

    void Control::DoOnHandleCreated( )
    {
        if ( text_.length( ) )
        {
            ::SetWindowTextW( handle_, text_.c_str( ) );
        }
        if ( id_ )
        {
            SetWindowLong( GWLP_ID, id_ );
        }
        this->DoOnSetEnabled( Enabled( ) );
        controls_.DoOnHandleCreated( );
        OnHandleCreated( this );
    }


    void Control::DestroyHandle( )
    {
        if ( IsValid( ) )
        {
            this->DoBeforeHandleDestroy( );
            bool succeeded = ::DestroyWindow( handle_ ) != FALSE;
            handle_ = nullptr;
            if ( !succeeded )
            {
                ThrowLastOSError( );
            }
        }
        handle_ = nullptr;
    }

    void Control::DoBeforeHandleDestroy( )
    {
        OnBeforeHandleDestroy( this );
    }

    void Control::DisconnectParentControl( )
    {
        controls_.DisconnectParentControl( );
        parentControl_ = nullptr;
    }


    Control& Control::RestoreSubClassedWindowsProcedure( )
    {
        if ( IsSubClassed( ) && handle_ )
        {
            ::SetWindowLongPtrW( handle_, GWLP_WNDPROC, LONG_PTR( originalWindowsProcedure_ ) );
        }
        return *this;
    }

    LRESULT CALLBACK Control::SubClassWndProc( HWND hWnd, UINT messageId, WPARAM wParam, LPARAM lParam )
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

        userData = ::GetWindowLongPtr( hWnd, GWLP_USERDATA );

        if ( userData )
        {
            Control* control = (Control*)userData;

            control->HandleMessage( message );
            if ( !message.handled )
            {
                message.result = control->originalWindowsProcedure_( hWnd, message.message, message.wParam, message.lParam );
            }
            if ( messageId == WM_NCDESTROY )
            {
                control->RestoreSubClassedWindowsProcedure( );
            }
        }


        if ( messageId == WM_NCDESTROY )
        {
            Control::UnregisterControl( hWnd );
        }
        return message.result;
    }

    Control& Control::SubClass( HWND hWnd )
    {

        if ( IsSubClassed( ) )
        {
            throw InvalidOperationException( L"Window is already subclassed" );
        }
        Message::Result res = ::SendMessageW( hWnd, WM_GET_CONTROL, 0, 0 );
        if ( res )
        {
            throw InvalidOperationException( L"Window should not be subclassed, it's already a Control" );
        }

        originalWindowsProcedure_ = ( WNDPROC ) ::GetWindowLongPtrW( handle_, GWLP_WNDPROC );
        ::SetWindowLongPtrW( handle_, GWLP_WNDPROC, LONG_PTR( SubClassWndProc ) );
        ::SetWindowLongPtrW( hWnd, GWLP_USERDATA, LONG_PTR( this ) );
        Control::RegisterControl( hWnd, this );

        return *this;
    }
    bool Control::IsSubClassed( ) const
    {
        return originalWindowsProcedure_ != nullptr;
    }

    void Control::DoOnWindowSubClassed( )
    {

    }


    HWND Control::GetHandle( ) const
    {
        if ( !handle_ )
        {
            Control* self = const_cast<Control*>( this );
            self->handle_ = self->CreateHandle( );
            self->DoOnHandleCreated( );
        }
        return handle_;
    }



    const Control& Control::GetClientRect( RECT* rectangle ) const
    {
        CheckPointerNotNull( rectangle );
        if ( ::GetClientRect( GetHandle( ), rectangle ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return *this;
    }
    const Control& Control::GetClientRect( RECT& rectangle ) const
    {
        if ( ::GetClientRect( GetHandle( ), &rectangle ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return *this;
    }
    RECT Control::GetClientRect( ) const
    {
        RECT result;
        if ( ::GetClientRect( GetHandle( ), &result ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return result;
    }


    D2D1_SIZE_F Control::ClientSize( ) const
    {
        RECT rect;
        if ( ::GetClientRect( GetHandle( ), &rect ) == FALSE )
        {
            ThrowLastOSError( );
        }
        D2D1_SIZE_F result;
        result.width = float( rect.right - rect.left );
        result.height = float( rect.bottom - rect.top );
        return result;
    }

    UInt32 Control::GetDotsPerInch( ) const
    {
        auto result = GetDpiForWindow( GetHandle( ) );
        return result;
    }





    void Control::RegisterControl( HWND hWnd, Control* constrol )
    {
        auto application = Application::Current( );
        if ( application )
        {
            application->AddControl( hWnd, constrol );
        }

    }

    void Control::UnregisterControl( HWND hWnd )
    {
        auto application = Application::Current( );
        if ( application )
        {
            application->RemoveControl( hWnd );
        }
    }

    Control* Control::GetControlFromHWND( HWND hWnd )
    {
        auto application = Application::Current( );
        if ( application )
        {
            Control* result = application->GetControl( hWnd );
            return result;
        }
        return nullptr;
    }


    Control& Control::SetParent( Control* parentControl )
    {
        auto currentParent = Parent( );
        if ( parentControl != currentParent )
        {
            if ( parentControl )
            {
                if ( parentControl->IsChildOf( *this ) )
                {
                    throw InvalidOperationException( L"Attempted to create a cyclic parent/child control relationship." );
                }
                if ( currentParent )
                {
                    currentParent->Controls( ).Remove( this );
                }
                parentControl->Controls( ).Add( this );
                parentControl_ = parentControl;
                if ( parentControl->IsValid( ) )
                {
                    if ( IsValid( ) == false )
                    {
                        GetHandle( );
                    }
                    else
                    {
                        if ( ::SetParent( handle_, parentControl->handle_ ) == FALSE )
                        {
                            ThrowLastOSError( );
                        }
                    }
                }
                else
                {
                    this->DestroyHandle( );
                }

            }
            else if ( currentParent )
            {
                currentParent->Controls( ).Remove( this );
                if ( handle_ )
                {
                    if ( ( this->GetStyle( ) & WS_CHILD ) == 0 )
                    {
                        if ( ::SetParent( handle_, nullptr ) == FALSE )
                        {
                            ThrowLastOSError( );
                        }
                    }
                    else
                    {
                        this->DestroyHandle( );
                    }
                }

            }
        }
        return *this;
    }



    const Control& Control::UpdateRect( RECT& updateRectangle ) const
    {
        if ( GetUpdateRect( GetHandle( ), &updateRectangle, false ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return *this;
    }
    Control& Control::UpdateRect( RECT& updateRectangle, bool erase )
    {
        if ( GetUpdateRect( GetHandle( ), &updateRectangle, erase ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return *this;
    }
    RECT Control::UpdateRect( ) const
    {
        RECT result = { 0, };
        if ( GetUpdateRect( GetHandle( ), &result, false ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return result;
    }
    RECT Control::UpdateRect( bool erase )
    {
        RECT result = { 0, };
        if ( GetUpdateRect( GetHandle( ), &result, erase ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return result;
    }


    /*
    BOOL CALLBACK EnumChildWindowsProcedure(HWND hWnd, LPARAM lParam)
    {
    std::vector< Control* >* vector = (std::vector< Control* >*)lParam;

    Control* control = Control::GetControlFromHWND(hWnd);
    if(control)
    {
    vector->push_back(control);
    }
    return TRUE;
    }

    std::vector< Control* > Control::GetChildren() const
    {
    std::vector< Control* > result;
    LPARAM lParam = (LPARAM)&result;

    // Even if EnumChildWindows has a return type of BOOL the return value is not used
    ::EnumChildWindows(GetHandle(),EnumChildWindowsProcedure,lParam);

    return result;
    }
    */

    bool Control::IsChildOf( const Control& parentControl ) const
    {
        bool result = false;
        auto pControl = Parent( );
        while ( pControl )
        {
            if ( pControl == &parentControl )
            {
                result = true;
                break;
            }
            pControl = pControl->Parent( );
        }
        return result;
    }

    bool Control::IsChildOf( HWND parentControl ) const
    {
        bool result = ::IsChild( parentControl, GetHandle( ) ) != FALSE;
        return result;
    }

    bool Control::IsParentOf( const Control& childControl ) const
    {
        bool result = false;
        result = childControl.IsChildOf( *this );
        return result;
    }

    bool Control::IsParentOf( HWND childControl ) const
    {
        bool result = ::IsChild( GetHandle( ), childControl ) != FALSE;
        return result;
    }

    bool Control::IsValid( ) const
    {
        bool result = false;
        if ( handle_ )
        {
            result = ::IsWindow( handle_ ) != FALSE;
        }
        return result;
    }

    bool Control::IsVisible( ) const
    {
        bool result = false;
        if ( handle_ )
        {
            result = ::IsWindowVisible( handle_ ) != FALSE;
        }
        return result;
    }

    Control& Control::InvalidateRect( bool erase )
    {
        if ( handle_ )
        {
            if ( ::InvalidateRect( handle_, nullptr, erase ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        return *this;
    }
    Control& Control::InvalidateRect( const RECT& rectangle, bool erase )
    {
        if ( handle_ )
        {
            if ( ::InvalidateRect( handle_, &rectangle, erase ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        return *this;
    }

    Control& Control::MoveWindow( int x, int y, int width, int height, bool repaint )
    {
        if ( handle_ )
        {
            if ( ::MoveWindow( handle_, x, y, width, height, repaint ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        position_.Assign( x, y );
        size_.Assign( width, height );

        return *this;
    }

    LONG Control::SetWindowLong( int index, LONG newValue )
    {
        if ( IsValid( ) == false )
        {
            throw InvalidOperationException( L"Valid window handle required" );
        }
        SetLastError( 0 );

        LONG result = ::SetWindowLong( handle_, index, newValue );

        if ( GetLastError( ) != 0 )
        {
            ThrowLastOSError( );
        }
        return result;
    }
    LONG Control::GetWindowLong( int index ) const
    {
        if ( IsValid( ) == false )
        {
            throw InvalidOperationException( L"Valid window handle required" );
        }
        SetLastError( 0 );

        LONG result = ::GetWindowLong( handle_, index );

        if ( GetLastError( ) != 0 )
        {
            ThrowLastOSError( );
        }
        return result;
    }


    LRESULT Control::SendMessage( UINT Msg, WPARAM wParam, LPARAM lParam ) const
    {
        return ::SendMessage( GetHandle( ), Msg, wParam, lParam );
    }

    const Control& Control::PostMessage( UINT Msg, WPARAM wParam, LPARAM lParam ) const
    {
        if ( ::PostMessage( GetHandle( ), Msg, wParam, lParam ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return *this;
    }

    int Control::TextLength( ) const
    {
        int size = ::GetWindowTextLengthW( GetHandle( ) );
        return size;
    }

    std::wstring Control::Text( ) const
    {
        int size = ::GetWindowTextLengthW( GetHandle( ) );
        if ( size > 0 )
        {
            wchar_t* buffer = (wchar_t*)alloca( ( size + 1 ) * sizeof( wchar_t ) );

            ::GetWindowTextW( handle_, buffer, size + 1 );

            std::wstring result = std::wstring( buffer );
            return result;
        }
        else
        {
            return std::wstring( );
        }
    }


    bool Control::SetText( const std::wstring& text )
    {
        bool result = true;
        if ( handle_ )
        {
            result = ::SetWindowTextW( GetHandle( ), text.empty() == false ? text.c_str( ) : L"" ) != FALSE;
        }
        text_ = text;
        return result;
    }
    bool Control::SetText( const wchar_t* text )
    {
        bool result = true;
        if ( handle_ )
        {
            if ( ( text ) && ( text[0] ) )
            {
                result = ::SetWindowTextW( GetHandle( ), text ) != FALSE;
            }
            else
            {
                result = ::SetWindowTextW( GetHandle( ), L"" ) != FALSE;
            }
        }
        if ( ( text ) && ( text[0] ) )
        {
            text_ = text;
        }
        else
        {
            text_ = std::wstring( );
        }
        return result;
    }


    bool Control::Show( )
    {
        bool result = ::ShowWindow( GetHandle( ), SW_SHOW ) != FALSE;
        return result;
    }

    bool Control::ValidateRect( const RECT& rectangle )
    {
        bool result = ::ValidateRect( GetHandle( ), &rectangle ) != FALSE;
        return result;
    }

    bool Control::ValidateRect( )
    {
        bool result = ::ValidateRect( GetHandle( ), nullptr ) != FALSE;
        return result;
    }

    Control& Control::SetSize( int width, int height )
    {
        if ( IsHandleCreated( ) )
        {
            MoveWindow( position_.X( ), position_.Y( ), width, height );
        }
        else
        {
            size_ = Windows::Size( width, height );
        }
        return *this;
    }

    Control& Control::SetSize( const Windows::Size& size )
    {
        if ( IsHandleCreated( ) )
        {
            MoveWindow( position_.X( ), position_.Y( ), size.Width( ), size.Height( ) );
        }
        else
        {
            size_ = size;
        }
        return *this;
    }


    Control& Control::SetPosition( int x, int y )
    {
        if ( IsHandleCreated( ) )
        {
            MoveWindow( x, y, size_.Width( ), size_.Height( ) );
        }
        else
        {
            position_.Assign( x, y );
        }
        return *this;
    }
    Control& Control::SetPosition( const Point& position )
    {
        if ( IsHandleCreated( ) )
        {
            MoveWindow( position.X( ), position.Y( ), size_.Width( ), size_.Height( ) );
        }
        else
        {
            position_ = position;
        }
        return *this;
    }



    bool Control::IsInputChar( wchar_t charCode )
    {
        int mask = DLGC_WANTCHARS | DLGC_WANTALLKEYS;
        if ( charCode == (wchar_t)Keys::Tab )
        {
            mask |= DLGC_WANTTAB;
        }
        if ( IsHandleCreated( ) )
        {
            return ( SendMessage( WM_GETDLGCODE ) & mask ) != 0;
        }
        return false;
    }

    bool Control::IsInputKey( Keys keyData )
    {
        if ( ( keyData & Keys::Alt ) == Keys::Alt )
        {
            return false;
        }
        int mask = DLGC_WANTALLKEYS;
        auto keyCode = keyData & Keys::KeyCode;
        switch ( keyCode )
        {
            case Keys::Tab:
                mask |= DLGC_WANTTAB;
                break;
            case Keys::Left:
            case Keys::Right:
            case Keys::Up:
            case Keys::Down:
                mask |= DLGC_WANTARROWS;
                break;
        }

        if ( IsHandleCreated( ) )
        {
            return ( SendMessage( WM_GETDLGCODE ) & mask ) != 0;
        }
        return false;
    }

    bool Control::ProcessMnemonic( wchar_t charCode )
    {
        return false;
    }



    void Control::HandleMessage( Message& message )
    {
        if ( message.message == REFLECTED_WM_COMMAND )
        {
            this->DoOnCommand( message );
            message.result = 1;
        }
        else if ( message.message == REFLECTED_WM_NOTIFY )
        {
            this->DoOnNotify( message );
        }
        else if ( message.message == REFLECTED_WM_DRAWITEM )
        {
            this->DoOnDrawItem( message );
        }
        else if ( message.message == WM_GET_CONTROL )
        {
            message.handled = true;
            message.result = ( Message::Result )this;
        }
        else
        {
            switch ( message.message )
            {
                case WM_CANCELMODE:
                    this->DoOnCancelMode( message );
                    break;
                case WM_CHAR:
                    this->DoOnChar( message );
                    break;
                case WM_CHARTOITEM:
                    this->DoOnCharToItem( message );
                    break;
                case WM_CLOSE:
                    this->DoOnClose( message );
                    break;
                case WM_COMPAREITEM:
                    this->DoOnCompareItem( message );
                    break;
                case WM_COMMAND:
                    if ( message.lParam != 0 )
                    {
                        HWND hWnd = (HWND)message.lParam;
                        LRESULT result = ::SendMessageW( hWnd, REFLECTED_WM_COMMAND, message.wParam, message.lParam );
                        if ( result )
                        {
                            message.result = 0;
                            return;
                        }
                    }
                    this->DoOnCommand( message );
                    break;
                case WM_COPYDATA:
                    this->DoOnCopyData( message );
                    break;
                case WM_DEADCHAR:
                    this->DoOnDeadChar( message );
                    break;
                case WM_DELETEITEM:
                    this->DoOnDeleteItem( message );
                    break;
                case WM_DESTROY:
                    this->DoOnDestroy( message );
                    break;
                case WM_DISPLAYCHANGE:
                    this->DoOnDisplayChange( message );
                    break;
                case WM_DRAWITEM:
                    this->DoOnDrawItem( message );
                    break;
                case WM_ENABLE:
                    this->DoOnEnable( message );
                    break;
                case WM_ENTERSIZEMOVE:
                    this->DoOnEnterSizeMove( message );
                    break;
                case WM_ERASEBKGND:
                    this->DoOnEraseBackground( message );
                    break;
                case WM_EXITSIZEMOVE:
                    this->DoOnExitSizeMove( message );
                    break;
                case WM_GETHOTKEY:
                    this->DoOnGetHotKey( message );
                    break;
                case WM_GETTEXT:
                    this->DoOnGetText( message );
                    break;
                case WM_GETTEXTLENGTH:
                    this->DoOnGetTextLength( message );
                    break;
                case WM_INITMENU:
                    this->DoOnInitMenu( message );
                    break;
                case WM_KEYDOWN:
                    this->DoOnKeyDown( message );
                    break;
                case WM_KEYUP:
                    this->DoOnKeyUp( message );
                    break;
                case WM_KILLFOCUS:
                    this->DoOnKillFocus( message );
                    break;
                case WM_MEASUREITEM:
                    this->DoOnMeasureItem( message );
                    break;
                case WM_MENUCOMMAND:
                    this->DoOnMenuCommand( message );
                    break;
                case WM_MOUSEMOVE:
                    this->DoOnMouseMove( message );
                    break;
                case WM_LBUTTONDOWN:
                    this->DoOnMouseLeftButtonDown( message );
                    break;
                case WM_LBUTTONUP:
                    this->DoOnMouseLeftButtonUp( message );
                    break;
                case WM_LBUTTONDBLCLK:
                    this->DoOnMouseLeftButtonDoubleClick( message );
                    break;
                case WM_RBUTTONDOWN:
                    this->DoOnMouseRightButtonDown( message );
                    break;
                case WM_RBUTTONUP:
                    this->DoOnMouseRightButtonUp( message );
                    break;
                case WM_RBUTTONDBLCLK:
                    this->DoOnMouseRightButtonDoubleClick( message );
                    break;
                case WM_MBUTTONDOWN:
                    this->DoOnMouseMiddleButtonDown( message );
                    break;
                case WM_MBUTTONUP:
                    this->DoOnMouseMiddleButtonUp( message );
                    break;
                case WM_MBUTTONDBLCLK:
                    this->DoOnMouseMiddleButtonDoubleClick( message );
                    break;
                case WM_XBUTTONDOWN:
                    this->DoOnMouseXButtonDown( message );
                    break;
                case WM_XBUTTONUP:
                    this->DoOnMouseXButtonUp( message );
                    break;
                case WM_XBUTTONDBLCLK:
                    this->DoOnMouseXButtonDoubleClick( message );
                    break;
                case WM_MOUSEHWHEEL:
                    this->DoOnMouseWheel( message );
                    break;
                case WM_MOVE:
                    position_.Assign( (int)(short)LOWORD( message.lParam ), (int)(short)HIWORD( message.lParam ) );
                    this->DoOnMove( message );
                    break;
                case WM_MOVING:
                    this->DoOnMoving( message );
                    break;
                case WM_NCACTIVATE:
                    this->DoOnNcActivate( message );
                    break;
                case WM_NCCALCSIZE:
                    this->DoOnNcCalcSize( message );
                    break;
                case WM_NCDESTROY:
                    this->DoOnNcDestroy( message );
                    break;
                case WM_NOTIFY:
                {
                    NMHDR* nmhdr = (NMHDR*)message.lParam;
                    if ( nmhdr )
                    {
                        HWND hWnd = nmhdr->hwndFrom;
                        message.result = ::SendMessageW( hWnd, REFLECTED_WM_NOTIFY, message.wParam, message.lParam );
                    }
                }
                break;
                case WM_PAINT:
                    this->DoOnPaint( message );
                    break;
                case WM_SETCURSOR:
                    this->DoOnSetCursor( message );
                    break;
                case WM_SETFOCUS:
                    this->DoOnSetFocus( message );
                    break;
                case WM_SETHOTKEY:
                    this->DoOnSetHotKey( message );
                    break;
                case WM_SETREDRAW:
                    this->DoOnSetRedraw( message );
                    break;
                case WM_SETTEXT:
                    this->DoOnSetText( message );
                    break;
                case WM_SHOWWINDOW:
                    this->DoOnShowWindow( message );
                    break;
                case WM_SIZE:
                {
                    RECT rect = { 0, };
                    GetWindowRect( message.hwnd, &rect );
                    size_.Assign( rect.right - rect.left, rect.bottom - rect.top );
                    this->DoOnSize( message );
                }
                break;
                case WM_SIZING:
                    this->DoOnSizing( message );
                    break;
                case WM_SYSCHAR:
                    this->DoOnSysChar( message );
                    break;
                case WM_SYSCOMMAND:
                    this->DoOnSysCommand( message );
                    break;
                case WM_SYSDEADCHAR:
                    this->DoOnSysDeadChar( message );
                    break;
                case WM_SYSKEYDOWN:
                    this->DoOnSysKeyDown( message );
                    break;
                case WM_SYSKEYUP:
                    this->DoOnSysKeyUp( message );
                    break;
                case WM_UNICHAR:
                    this->DoOnUniChar( message );
                    break;
                case WM_VKEYTOITEM:
                    this->DoOnVKeyToItem( message );
                    break;
                case WM_WINDOWPOSCHANGING:
                    this->DoOnWindowPosChanging( message );
                    break;
                case WM_WINDOWPOSCHANGED:
                    this->DoOnWindowPosChanged( message );
                    break;
            }
        }
    }

    void Control::DoOnCancelMode( Message& message )
    {
        OnCancelMode( this, message );
    }

    void Control::DoOnChar( Message& message )
    {
        OnChar( this, message );
    }

    void Control::DoOnCharToItem( Message& message )
    {
        OnCharToItem( this, message );
    }

    void Control::DoOnClose( Message& message )
    {
        OnClose( this, message );
    }

    void Control::DoOnCompareItem( Message& message )
    {
        OnCompareItem( this, message );
    }

    void Control::DoOnCommand( Message& message )
    {
        OnCommand( this, message );
    }

    void Control::DoOnCopyData( Message& message )
    {
        OnCopyData( this, message );
    }

    void Control::DoOnDeadChar( Message& message )
    {
        OnDeadChar( this, message );
    }

    void Control::DoOnDeleteItem( Message& message )
    {
        OnDeleteItem( this, message );
    }

    void Control::DoOnDestroy( Message& message )
    {
        OnDestroy( this, message );
    }

    void Control::DoOnDisplayChange( Message& message )
    {
        OnDisplayChange( this, message );
    }

    void Control::DoOnDrawItem( Message& message )
    {
        OnDrawItem( this, message );
        if ( !message.handled )
        {
            DRAWITEMSTRUCT* drawItemStruct = (DRAWITEMSTRUCT*)message.lParam;
            if ( drawItemStruct && drawItemStruct->CtlType == ODT_MENU )
            {
                MenuItem* menuItem = (MenuItem*)drawItemStruct->itemData;
                if ( menuItem )
                {
                    menuItem->DoOnDrawItem( *drawItemStruct );
                    message.handled = true;
                    message.result = true;
                }
            }
        }
    }

    void Control::DoOnEnable( Message& message )
    {
        OnEnable( this, message );
    }

    void Control::DoOnEnterSizeMove( Message& message )
    {
        OnEnterSizeMove( this, message );
    }

    void Control::DoOnEraseBackground( Message& message )
    {
        OnEraseBackground( this, message );
    }

    void Control::DoOnExitSizeMove( Message& message )
    {
        OnExitSizeMove( this, message );
    }

    void Control::DoOnGetHotKey( Message& message )
    {
        OnGetHotKey( this, message );
    }

    void Control::DoOnGetText( Message& message )
    {
        OnGetText( this, message );
    }

    void Control::DoOnGetTextLength( Message& message )
    {
        OnGetTextLength( this, message );
    }

    void Control::DoOnInitMenu( Message& message )
    {
        OnInitMenu( this, message );
        if ( !message.handled )
        {
            HMENU hMenu = (HMENU)message.lParam;
            if ( hMenu )
            {
                auto menu = Menu::GetFromMenuMap( hMenu );
                if ( menu )
                {
                    menu->DoOnInitMenu( message );
                }
            }
        }
    }

    void Control::DoOnInitMenuPopup( Message& message )
    {
        OnInitMenuPopup( this, message );
        if ( !message.handled )
        {
            HMENU hMenu = (HMENU)message.wParam;
            if ( hMenu )
            {
                auto menu = Menu::GetFromMenuMap( hMenu );
                if ( menu )
                {
                    menu->DoOnInitMenuPopup( message );
                }
            }
        }
    }


    void Control::DoOnKeyDown( Message& message )
    {
        OnKeyDown( this, message );
    }

    void Control::DoOnKeyUp( Message& message )
    {
        OnKeyUp( this, message );
    }

    void Control::DoOnKillFocus( Message& message )
    {
        OnKillFocus( this, message );
    }

    void Control::DoOnMeasureItem( Message& message )
    {
        OnMeasureItem( this, message );
        if ( !message.handled )
        {
            MEASUREITEMSTRUCT* measureItemStruct = (MEASUREITEMSTRUCT*)message.lParam;
            if ( measureItemStruct && measureItemStruct->CtlType == ODT_MENU )
            {
                MenuItem* menuItem = (MenuItem*)measureItemStruct->itemData;
                if ( menuItem )
                {
                    menuItem->DoOnMeasureItem( *measureItemStruct );
                    message.handled = true;
                    message.result = true;
                }
            }
        }
    }

    void Control::DoOnMenuCommand( Message& message )
    {
        OnMenuCommand( this, message );
        if ( !message.handled )
        {
            HMENU hMenu = (HMENU)message.lParam;
            if ( hMenu )
            {
                auto menu = Menu::GetFromMenuMap( hMenu );
                if ( menu )
                {
                    menu->DoOnMenuCommand( message );
                }
            }
        }
    }

    void Control::DoOnMouseMove( Message& message )
    {
        OnMouseMove( this, message );
    }

    void Control::DoOnMouseLeftButtonDown( Message& message )
    {
        OnMouseLeftButtonDown( this, message );
    }

    void Control::DoOnMouseLeftButtonUp( Message& message )
    {
        OnMouseLeftButtonUp( this, message );
    }

    void Control::DoOnMouseLeftButtonDoubleClick( Message& message )
    {
        OnMouseLeftButtonDoubleClick( this, message );
    }

    void Control::DoOnMouseMiddleButtonDown( Message& message )
    {
        OnMouseMiddleButtonDown( this, message );
    }

    void Control::DoOnMouseMiddleButtonUp( Message& message )
    {
        OnMouseMiddleButtonUp( this, message );
    }

    void Control::DoOnMouseMiddleButtonDoubleClick( Message& message )
    {
        OnMouseMiddleButtonDoubleClick( this, message );
    }

    void Control::DoOnMouseRightButtonDown( Message& message )
    {
        OnMouseRightButtonDown( this, message );
    }

    void Control::DoOnMouseRightButtonUp( Message& message )
    {
        OnMouseRightButtonUp( this, message );
    }

    void Control::DoOnMouseRightButtonDoubleClick( Message& message )
    {
        OnMouseRightButtonDoubleClick( this, message );
    }

    void Control::DoOnMouseXButtonDown( Message& message )
    {
        OnMouseXButtonDown( this, message );
    }

    void Control::DoOnMouseXButtonUp( Message& message )
    {
        OnMouseXButtonUp( this, message );
    }

    void Control::DoOnMouseXButtonDoubleClick( Message& message )
    {
        OnMouseXButtonDoubleClick( this, message );
    }

    void Control::DoOnMouseWheel( Message& message )
    {
        OnMouseWheel( this, message );
    }



    void Control::DoOnMove( Message& message )
    {
        OnMove( this, message );
    }

    void Control::DoOnMoving( Message& message )
    {
        OnMoving( this, message );
    }

    void Control::DoOnNcActivate( Message& message )
    {
        OnNcActivate( this, message );
    }

    void Control::DoOnNcCalcSize( Message& message )
    {
        OnNcCalcSize( this, message );
    }

    void Control::DoOnNcDestroy( Message& message )
    {
        OnNcDestroy( this, message );
    }

    void Control::DoOnNotify( Message& message )
    {
        OnNotify( this, message );
    }

    void Control::DoOnPaint( Message& message )
    {
        OnPaint( this, message );
    }

    void Control::DoOnSetCursor( Message& message )
    {
        OnSetCursor( this, message );
    }

    void Control::DoOnSetFocus( Message& message )
    {
        OnSetFocus( this, message );
    }

    void Control::DoOnSetHotKey( Message& message )
    {
        OnSetHotKey( this, message );
    }

    void Control::DoOnSetRedraw( Message& message )
    {
        OnSetRedraw( this, message );
    }

    void Control::DoOnSetText( Message& message )
    {
        OnSetText( this, message );
    }
    void Control::DoOnShowWindow( Message& message )
    {
        OnShowWindow( this, message );
    }

    void Control::DoOnSize( Message& message )
    {
        OnSize( this, message );
    }

    void Control::DoOnSizing( Message& message )
    {
        OnSizing( this, message );
    }

    void Control::DoOnSysChar( Message& message )
    {
        OnSysChar( this, message );
    }

    void Control::DoOnSysCommand( Message& message )
    {
        OnSysCommand( this, message );
    }

    void Control::DoOnSysDeadChar( Message& message )
    {
        OnSysDeadChar( this, message );
    }

    void Control::DoOnSysKeyDown( Message& message )
    {
        OnSysKeyDown( this, message );
    }

    void Control::DoOnSysKeyUp( Message& message )
    {
        OnSysKeyUp( this, message );
    }


    void Control::DoOnUniChar( Message& message )
    {
        OnUniChar( this, message );
    }

    void Control::DoOnVKeyToItem( Message& message )
    {
        OnVKeyToItem( this, message );
    }

    void Control::DoOnWindowPosChanging( Message& message )
    {
        OnWindowPosChanging( this, message );
    }

    void Control::DoOnWindowPosChanged( Message& message )
    {
        OnWindowPosChanged( this, message );
    }

}
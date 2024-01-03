/*
   Copyright 2024 Espen Harlinn

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

#include "pch.h"
#include <HWStdCtrls.h>
#include <HWApplication.h>
#include <HWEnvironment.h>

namespace Harlinn::Windows
{
    // --------------------------------------------------------------------
    // ButtonBase
    // --------------------------------------------------------------------
    class ButtonWindowClass : public Windows::WindowClass
    {
    public:
        typedef Windows::WindowClass Base;
        static WideString windowClassName;
        ButtonWindowClass( const Windows::WindowClass& existingClass );
    };

    WideString ButtonWindowClass::windowClassName = WideString( L"CommonButtonWindowClassName" );

    typedef SuperClassMessageDispatcher<Button> ButtonMessageDispatcher;
    WNDPROC ButtonMessageDispatcher::ControlProcedure;

    ButtonWindowClass::ButtonWindowClass( const Windows::WindowClass& existingClass )
        : Base( existingClass )
    {
        ButtonMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = ButtonMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }

    ButtonBase::ButtonBase( )
        : Base( ),
          autoEllipsis_( false )

    {
    }

    WindowClass* ButtonBase::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( ButtonWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::button_class_name );
            auto newWindowClass = std::make_unique<ButtonWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }

    DWORD ButtonBase::GetStyle( ) const
    {
        auto result = Base::GetStyle( );
        result |= WS_TABSTOP | WS_CHILD | WS_VISIBLE;
        return result;
    }

    bool ButtonBase::AutoEllipsis( ) const
    {
        return autoEllipsis_;
    }
    ButtonBase& ButtonBase::SetAutoEllipsis( bool value )
    {
        autoEllipsis_ = value;
        return *this;
    }



    void ButtonBase::DoOnSetEnabled( bool theValue )
    {
        Button_Enable( this->GetHandle( ), theValue );
    }

    ButtonBase& ButtonBase::Click( )
    {
        if ( IsValid( ) )
        {
            SendMessage( BM_CLICK );
        }
        else
        {
            this->DoOnClick( );
        }
        return *this;
    }

    const ButtonBase& ButtonBase::GetTextMargin( RECT& margin ) const
    {
        Button_GetTextMargin( GetHandle( ), &margin );
        return *this;
    }

    RECT ButtonBase::GetTextMargin( ) const
    {
        RECT margin = { 0, };
        Button_GetTextMargin( GetHandle( ), &margin );
        return margin;
    }


    ButtonBase& ButtonBase::SetTextMargin( const RECT& margin )
    {
        Button_SetTextMargin( GetHandle( ), &margin );
        return *this;
    }

    const ButtonBase& ButtonBase::GetIdealSize( SIZE& preferredSize ) const
    {
        Button_GetIdealSize( GetHandle( ), &preferredSize );
        return *this;
    }

    SIZE ButtonBase::GetIdealSize( ) const
    {
        SIZE result = { 0, };
        Button_GetIdealSize( GetHandle( ), &result );
        return result;
    }


    void ButtonBase::DoOnClick( )
    {
        OnClick( this );
    }

    void ButtonBase::DoOnCommand( Message& message )
    {
        WORD notificationCode = HIWORD( message.wParam );
        if ( ( notificationCode == BN_CLICKED ) && ( message.message == REFLECTED_WM_COMMAND ) )
        {
            this->DoOnClick( );
        }
        Base::DoOnCommand( message );
    }

    // --------------------------------------------------------------------
    // PushButtonBase
    // --------------------------------------------------------------------
    PushButtonBase::PushButtonBase( )
        : isDefault_( false )
    {
    }

    bool PushButtonBase::IsDefault( ) const
    {
        return isDefault_;
    }
    PushButtonBase& PushButtonBase::SetDefault( bool value )
    {
        if ( isDefault_ != value )
        {
            isDefault_ = value;
            if ( IsValid( ) )
            {
                this->DoOnSetDefault( value );
            }
            this->DoOnDefaultChanged( value );
        }
        return *this;
    }

    void PushButtonBase::DoOnSetDefault( bool theValue )
    {
    }
    void PushButtonBase::DoOnDefaultChanged( bool theValue )
    {
        OnDefaultChanged( this, theValue );
    }



    // --------------------------------------------------------------------
    // Button
    // --------------------------------------------------------------------
    Button::Button( )
        : Base( )
    {

    }

    DWORD Button::GetStyle( ) const
    {
        DWORD result = Base::GetStyle( );
        result |= BS_PUSHBUTTON | WS_TABSTOP;
        if ( IsDefault( ) )
        {
            result |= BS_DEFPUSHBUTTON;
        }
        else
        {
            result &= ~BS_DEFPUSHBUTTON;
        }

        return result;
    }

    void Button::DoOnSetDefault( bool theValue )
    {
        Base::DoOnSetDefault( theValue );
        if ( IsValid( ) )
        {
            DWORD style = Base::GetStyle( );
            if ( IsDefault( ) )
            {
                style |= BS_DEFPUSHBUTTON;
            }
            else
            {
                style &= ~BS_DEFPUSHBUTTON;
            }
            Base::SetWindowStyle( style );
        }

    }


    // --------------------------------------------------------------------
    // DropDownButton
    // --------------------------------------------------------------------
    DropDownButton::DropDownButton( )
        : Base( )
    {
    }

    void DropDownButton::DoOnInitialize( )
    {
        popupMenu_ = std::make_unique<PopupMenu>( );
    }


    DWORD DropDownButton::GetStyle( ) const
    {
        DWORD result = Base::GetStyle( );

        if ( IsDefault( ) )
        {
            result |= BS_DEFSPLITBUTTON;
            result &= ~BS_SPLITBUTTON;
        }
        else
        {
            result &= ~BS_DEFSPLITBUTTON;
            result |= BS_SPLITBUTTON;
        }

        return result;
    }

    PopupMenu* DropDownButton::Menu( ) const
    {
        return popupMenu_.get();
    }

    void DropDownButton::DoOnSetDefault( bool theValue )
    {
        Base::DoOnSetDefault( theValue );
        if ( IsValid( ) )
        {
            DWORD style = Base::GetStyle( );
            if ( IsDefault( ) )
            {
                style |= BS_DEFPUSHBUTTON;
                style &= ~BS_SPLITBUTTON;
            }
            else
            {
                style &= ~BS_DEFPUSHBUTTON;
                style |= BS_SPLITBUTTON;
            }
            Base::SetWindowStyle( style );
        }
    }

    void DropDownButton::DoOnNotify( Message& message )
    {
        Base::DoOnNotify( message );
        if ( !message.handled )
        {
            if ( message.message == REFLECTED_WM_NOTIFY )
            {
                NMHDR* nmhdr = (NMHDR*)message.lParam;
                if ( nmhdr->code == BCN_DROPDOWN )
                {
                    NMBCDROPDOWN* nmbcdropdown = (NMBCDROPDOWN*)message.lParam;
                    POINT pt;
                    pt.x = nmbcdropdown->rcButton.left;
                    pt.y = nmbcdropdown->rcButton.bottom;
                    ::ClientToScreen( nmbcdropdown->hdr.hwndFrom, &pt );

                    popupMenu_->Show( *this, pt, nmbcdropdown->rcButton );
                    message.handled = true;
                    message.result = true;
                }
            }
        }
    }


    // --------------------------------------------------------------------
    // CommandButton
    // --------------------------------------------------------------------
    CommandButton::CommandButton( )
        : Base( )
    {

    }

    DWORD CommandButton::GetStyle( ) const
    {
        DWORD result = Base::GetStyle( );

        if ( IsDefault( ) )
        {
            result |= BS_DEFCOMMANDLINK;
            result &= ~BS_COMMANDLINK;
        }
        else
        {
            result &= ~BS_DEFCOMMANDLINK;
            result |= BS_COMMANDLINK;
        }

        return result;
    }

    void CommandButton::DoOnSetDefault( bool theValue )
    {
        Base::DoOnSetDefault( theValue );
        if ( IsValid( ) )
        {
            DWORD style = Base::GetStyle( );
            if ( IsDefault( ) )
            {
                style |= BS_DEFCOMMANDLINK;
                style &= ~BS_COMMANDLINK;
            }
            else
            {
                style &= ~BS_DEFCOMMANDLINK;
                style |= BS_COMMANDLINK;
            }
            Base::SetWindowStyle( style );
        }
    }



    // --------------------------------------------------------------------
    // StateButton
    // --------------------------------------------------------------------
    StateButton::StateButton( )
        : Base( ),
          checkState_( CheckState::Unchecked ),
          allowGrayed_( false )
    {

    }

    void StateButton::DoOnHandleCreated( )
    {
        Base::DoOnHandleCreated( );
        int check = int( checkState_ );
        Button_SetCheck( GetHandle( ), check );
    }

    void StateButton::HandleMessage( Message& message )
    {
        Base::HandleMessage( message );
        if ( !message.handled )
        {
            switch ( message.message )
            {
                case BM_SETCHECK:
                {
                    auto theCheckState = Windows::CheckState( message.wParam );
                    if ( checkState_ != theCheckState )
                    {
                        checkState_ = theCheckState;
                        this->DoOnCheckStateChanged( checkState_ );
                    }
                }
                break;
            }
        }
    }


    StateButton& StateButton::SetCheckState( Windows::CheckState theCheckState )
    {
        if ( IsValid( ) )
        {
            int check = int( theCheckState );
            Button_SetCheck( GetHandle( ), check );
        }
        else
        {
            if ( checkState_ != theCheckState )
            {
                checkState_ = theCheckState;
                this->DoOnCheckStateChanged( checkState_ );
            }
        }
        return *this;
    }
    Windows::CheckState StateButton::CheckState( ) const
    {
        return checkState_;
    }

    bool StateButton::AllowGrayed( ) const
    {
        return allowGrayed_;
    }
    StateButton& StateButton::SetAllowGrayed( bool theValue )
    {
        if ( allowGrayed_ != theValue )
        {
            allowGrayed_ = theValue;
        }
        return *this;
    }

    bool StateButton::Checked( ) const
    {
        return checkState_ == Windows::CheckState::Checked;
    }
    StateButton& StateButton::SetChecked( bool theValue )
    {
        SetCheckState( theValue ? Windows::CheckState::Checked : Windows::CheckState::Unchecked );
        return *this;
    }

    StateButton& StateButton::Toggle( )
    {
        if ( checkState_ == CheckState::Unchecked )
        {
            SetCheckState( CheckState::Checked );
        }
        else if ( checkState_ == CheckState::Checked )
        {
            if ( allowGrayed_ )
            {
                SetCheckState( CheckState::Indeterminate );
            }
            else
            {
                SetCheckState( CheckState::Unchecked );
            }
        }
        else
        {
            SetCheckState( CheckState::Unchecked );
        }
        return *this;
    }


    void StateButton::DoOnCheckStateChanged( Windows::CheckState theCheckState )
    {
        OnCheckStateChanged( this, theCheckState );
    }

    void StateButton::DoOnClick( )
    {
        Toggle( );
        Base::DoOnClick( );
    }



    // --------------------------------------------------------------------
    // CheckBox
    // --------------------------------------------------------------------
    CheckBox::CheckBox( )
        : Base( )
    {
    }

    DWORD CheckBox::GetStyle( ) const
    {
        DWORD result = Base::GetStyle( ) | BS_CHECKBOX;
        return result;
    }

    // --------------------------------------------------------------------
    // RadioButton
    // --------------------------------------------------------------------
    RadioButton::RadioButton( )
        : Base( )
    {

    }


    DWORD RadioButton::GetStyle( ) const
    {
        DWORD result = Base::GetStyle( ) | BS_RADIOBUTTON;
        return result;
    }

    // --------------------------------------------------------------------
    // DateTimePicker
    // --------------------------------------------------------------------
    class DateTimePickerWindowClass : public WindowClass
    {
    public:
        typedef WindowClass Base;
        static WideString windowClassName;
        DateTimePickerWindowClass( const WindowClass& existingClass );
    };

    WideString DateTimePickerWindowClass::windowClassName = WideString( L"CommonDateTimePickerWindowClassName" );

    typedef SuperClassMessageDispatcher<DateTimePicker> DateTimePickerMessageDispatcher;
    WNDPROC DateTimePickerMessageDispatcher::ControlProcedure;

    DateTimePickerWindowClass::DateTimePickerWindowClass( const WindowClass& existingClass )
        : Base( existingClass )
    {
        DateTimePickerMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = DateTimePickerMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }

    DateTimePicker::DateTimePicker( )
        : Base( )
    {

    }

    WindowClass* DateTimePicker::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( DateTimePickerWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::datetimepick_class_name );
            auto newWindowClass = std::make_unique<DateTimePickerWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }


    DWORD DateTimePicker::GetStyle( ) const
    {
        return Base::GetStyle( );
    }


    // --------------------------------------------------------------------
    // GroupBox
    // --------------------------------------------------------------------
    class GroupBoxWindowClass : public WindowClass
    {
    public:
        typedef WindowClass Base;
        static WideString windowClassName;
        GroupBoxWindowClass( const WindowClass& existingClass );
    };

    WideString GroupBoxWindowClass::windowClassName = WideString( L"CommonGroupBoxWindowClassName" );

    typedef SuperClassMessageDispatcher<GroupBox> GroupBoxMessageDispatcher;
    WNDPROC GroupBoxMessageDispatcher::ControlProcedure;

    GroupBoxWindowClass::GroupBoxWindowClass( const WindowClass& existingClass )
        : Base( existingClass )
    {
        GroupBoxMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = GroupBoxMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }

    GroupBox::GroupBox( )
        : Base( )
    {


    }

    WindowClass* GroupBox::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( GroupBoxWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::button_class_name );
            auto newWindowClass = std::make_unique<GroupBoxWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }


    DWORD GroupBox::GetStyle( ) const
    {
        return Base::GetStyle( ) | BS_GROUPBOX;
    }


    // --------------------------------------------------------------------
    // Label
    // --------------------------------------------------------------------
    class LabelWindowClass : public WindowClass
    {
    public:
        typedef WindowClass Base;
        static WideString windowClassName;
        LabelWindowClass( const WindowClass& existingClass );
    };

    WideString LabelWindowClass::windowClassName = WideString( L"CommonLabelWindowClassName" );

    typedef SuperClassMessageDispatcher<Label> LabelMessageDispatcher;
    WNDPROC LabelMessageDispatcher::ControlProcedure;

    LabelWindowClass::LabelWindowClass( const WindowClass& existingClass )
        : Base( existingClass )
    {
        LabelMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = LabelMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }

    Label::Label( )
        : Base( )
    {

    }

    WindowClass* Label::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( LabelWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::static_class_name );
            auto newWindowClass = std::make_unique<LabelWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }

    DWORD Label::GetStyle( ) const
    {
        return Base::GetStyle( );
    }


    // --------------------------------------------------------------------
    // LinkLabel
    // --------------------------------------------------------------------
    class LinkLabelWindowClass : public WindowClass
    {
    public:
        typedef WindowClass Base;
        static WideString windowClassName;
        LinkLabelWindowClass( const WindowClass& existingClass );
    };

    WideString LinkLabelWindowClass::windowClassName = WideString( L"CommonLinkLabelWindowClassName" );

    typedef SuperClassMessageDispatcher<LinkLabel> LinkLabelMessageDispatcher;
    WNDPROC LinkLabelMessageDispatcher::ControlProcedure;

    LinkLabelWindowClass::LinkLabelWindowClass( const WindowClass& existingClass )
        : Base( existingClass )
    {
        LinkLabelMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = LinkLabelMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }

    LinkLabel::LinkLabel( )
        : Base( )
    {

    }

    WindowClass* LinkLabel::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( LinkLabelWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::link_class_name );
            auto newWindowClass = std::make_unique<LinkLabelWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }

    DWORD LinkLabel::GetStyle( ) const
    {
        return Base::GetStyle( );
    }


    void LinkLabel::DoOnClick( NMLINK* pNMLINK )
    {
        OnClick( this, pNMLINK );
    }

    void LinkLabel::DoOnNotify( Message& message )
    {
        Base::DoOnNotify( message );
        if ( message.handled == false )
        {
            if ( ( ( (LPNMHDR)message.lParam )->code == NM_CLICK ) || ( ( (LPNMHDR)message.lParam )->code == NM_RETURN ) )
            {
                PNMLINK pNMLink = (PNMLINK)message.lParam;
                this->DoOnClick( pNMLink );
            }
        }
    }



    // --------------------------------------------------------------------
    // ListControl
    // --------------------------------------------------------------------
    ListControl::ListControl( )
        : Base( )
    {

    }




    // --------------------------------------------------------------------
    // ComboBox
    // --------------------------------------------------------------------
    class ComboBoxWindowClass : public WindowClass
    {
    public:
        typedef WindowClass Base;
        static WideString windowClassName;
        ComboBoxWindowClass( const WindowClass& existingClass );
    };

    WideString ComboBoxWindowClass::windowClassName = WideString( L"CommonComboBoxWindowClassName" );

    typedef SuperClassMessageDispatcher<ComboBox> ComboBoxMessageDispatcher;
    WNDPROC ComboBoxMessageDispatcher::ControlProcedure;

    ComboBoxWindowClass::ComboBoxWindowClass( const WindowClass& existingClass )
        : Base( existingClass )
    {
        ComboBoxMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = ComboBoxMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }

    ComboBox::ComboBox( )
        : Base( )
    {

    }

    WindowClass* ComboBox::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( ComboBoxWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::combobox_class_name );
            auto newWindowClass = std::make_unique<ComboBoxWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }

    DWORD ComboBox::GetStyle( ) const
    {
        return Base::GetStyle( );
    }


    // --------------------------------------------------------------------
    // ListBox
    // --------------------------------------------------------------------
    class ListBoxWindowClass : public WindowClass
    {
    public:
        typedef WindowClass Base;
        static WideString windowClassName;
        ListBoxWindowClass( const WindowClass& existingClass );
    };

    WideString ListBoxWindowClass::windowClassName = WideString( L"CommonListBoxWindowClassName" );

    typedef SuperClassMessageDispatcher<ListBox> ListBoxMessageDispatcher;
    WNDPROC ListBoxMessageDispatcher::ControlProcedure;

    ListBoxWindowClass::ListBoxWindowClass( const WindowClass& existingClass )
        : Base( existingClass )
    {
        ListBoxMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = ListBoxMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }

    ListBox::ListBox( )
        : Base( )
    {

    }

    WindowClass* ListBox::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( ListBoxWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::listbox_class_name );
            auto newWindowClass = std::make_unique<ListBoxWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }

    DWORD ListBox::GetStyle( ) const
    {
        return Base::GetStyle( );
    }

    // --------------------------------------------------------------------
    // CheckedListBox
    // --------------------------------------------------------------------
    CheckedListBox::CheckedListBox( )
        : Base( )
    {
    }


    DWORD CheckedListBox::GetStyle( ) const
    {
        return Base::GetStyle( );
    }

    // --------------------------------------------------------------------
    // HeaderControlItem
    // --------------------------------------------------------------------
    HeaderControlItem::HeaderControlItem( HeaderControlItems* theHeaderControlItems )
        : items_( theHeaderControlItems ),
          mask_( HeaderControlItemMask::None ),
          dimension_( 0 ),
          format_( HeaderControlItemFormat::Default ),
          imageIndex_( I_IMAGENONE ),
          order_( -1 ),
          filterType_( HeaderControlItemFilterType::None )
    {
    }


    HeaderControlItem::HeaderControlItem( HeaderControlItems* theHeaderControlItems, const WideString& theText )
        : items_( theHeaderControlItems ),
          mask_( HeaderControlItemMask::None ),
          dimension_( 50 ),
          format_( HeaderControlItemFormat::Default ),
          imageIndex_( I_IMAGENONE ),
          order_( -1 ),
          filterType_( HeaderControlItemFilterType::None ),
          text_( theText )
    {
    }

    bool HeaderControlItem::IsHandleCreated( ) const
    {
        return items_->headerControl_->IsHandleCreated( );
    }

    HWND HeaderControlItem::GetControlHandle( ) const
    {
        return items_->headerControl_->GetHandle( );
    }

    HeaderControl* HeaderControlItem::GetControl( ) const
    {
        return items_->headerControl_;
    }





    WideString HeaderControlItem::Text( ) const
    {
        return text_;
    }
    HeaderControlItem& HeaderControlItem::SetText( const WideString& theText )
    {
        if ( text_ != theText )
        {
            text_ = theText;
        }
        return *this;
    }



    HeaderControlItem& HeaderControlItem::Assign( const HDITEMW& item )
    {
        if ( item.mask & HDI_BITMAP )
        {
            if ( item.hbm )
            {
                bitmap_ = BitmapHandle( item.hbm, false );
            }
            else
            {
                bitmap_.Close();
            }
        }
        if ( item.mask & HDI_FORMAT )
        {
            format_ = HeaderControlItemFormat( item.fmt );
        }
        if ( item.mask & HDI_FILTER )
        {

        }
        if ( item.mask & HDI_HEIGHT )
        {
            dimension_ = item.cxy;
        }
        if ( item.mask & HDI_IMAGE )
        {
            imageIndex_ = item.iImage;
        }
        if ( item.mask & HDI_LPARAM )
        {

        }
        if ( item.mask & HDI_ORDER )
        {
            order_ = item.iOrder;
        }

        if ( item.mask & HDI_STATE )
        {
            if ( item.state & HDIS_FOCUSED )
            {
                auto index = IndexOf( );
                items_->focusedIndex_ = index;
            }
        }
        if ( item.mask & HDI_TEXT )
        {
            WideString s( item.pszText, item.cchTextMax );
            if ( text_ != s )
            {
                text_ = s;
            }
        }


        return *this;
    }


    const HeaderControlItem& HeaderControlItem::AssignTo( HDITEMW& item ) const
    {
        if ( bitmap_ )
        {
            item.hbm = bitmap_;
            item.mask |= HDI_BITMAP;
        }
        else
        {
            item.mask &= ~HDI_BITMAP;
        }
        item.mask |= HDI_FORMAT;
        item.fmt = int( format_ );
        if ( items_->headerControl_->imageList_ )
        {
            item.iImage = imageIndex_;
            item.mask |= HDI_IMAGE;
        }
        else
        {
            item.mask &= ~HDI_IMAGE;
        }
        if ( dimension_ > 0 )
        {
            item.mask |= HDI_HEIGHT;
            item.cxy = dimension_;
        }
        else
        {
            item.mask &= ~HDI_HEIGHT;
        }
        if ( order_ >= 0 )
        {
            item.mask |= HDI_ORDER;
            item.iOrder = order_;
        }
        else
        {
            item.mask &= ~HDI_ORDER;
        }
        if ( text_.empty( ) == false )
        {
            item.mask |= HDI_TEXT;
            item.pszText = (LPWSTR)text_.c_str( );
            item.cchTextMax = int( text_.length( ) );
        }
        else
        {
            item.mask &= ~HDI_TEXT;
        }
        return *this;
    }

    size_t HeaderControlItem::IndexOf( ) const
    {
        return items_->IndexOf( this );
    }

    void HeaderControlItem::DoOnBeginDrag( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnBeginFilterEdit( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnBeginTrack( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnDividerDoubleClick( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnDropDown( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnEndDrag( NMHEADER* pNMHEADER )
    {
    }

    void HeaderControlItem::DoOnEndFilterEdit( NMHEADER* pNMHEADER )
    {
    }

    void HeaderControlItem::DoOnEndTrack( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnFilterButtonClicked( NMHDFILTERBTNCLICK* pNMHDFILTERBTNCLICK )
    {
    }
    void HeaderControlItem::DoOnFilterChange( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnGetDispInfo( NMHDDISPINFO* pNMHDDISPINFO )
    {
    }
    void HeaderControlItem::DoOnItemChanged( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnItemChanging( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnItemClicked( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnItemDoubleClicked( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnItemKeyDown( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnItemStateIconClicked( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnItemOverflowButtonClicked( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnTrack( NMHEADER* pNMHEADER )
    {
    }
    void HeaderControlItem::DoOnCustomDraw( NMCUSTOMDRAW* pNMCUSTOMDRAW )
    {
    }
    void HeaderControlItem::DoOnRightClicked( const Point& mousePosition )
    {
    }


    void HeaderControlItem::InsertHDITEM( )
    {
        if ( IsHandleCreated( ) )
        {
            HWND hWnd = GetControlHandle( );
            int index = int( IndexOf( ) );
            HDITEMW hditem = { 0, };
            this->AssignTo( hditem );
            if ( Header_InsertItem( hWnd, index, &hditem ) == -1 )
            {
                ThrowLastOSError( );
            }
        }
    }
    void HeaderControlItem::UpdateHDITEM( )
    {
        if ( IsHandleCreated( ) )
        {
            HWND hWnd = GetControlHandle( );
            int index = int( IndexOf( ) );
            HDITEMW hditem = { 0, };
            this->AssignTo( hditem );
            if ( Header_SetItem( hWnd, index, &hditem ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
    }
    void HeaderControlItem::DeleteHDITEM( )
    {
        auto index = IndexOf( );
        items_->RemoveAt( index );
    }

    // --------------------------------------------------------------------
    // HeaderControlItems
    // --------------------------------------------------------------------
    HeaderControlItems::HeaderControlItems( HeaderControl* theHeaderControl )
        : headerControl_( theHeaderControl ), focusedIndex_( npos )
    {

    }

    void HeaderControlItems::DoOnHandleCreated( )
    {
        for ( size_type i = 0; i < items_.size( ); i++ )
        {
            auto& item = items_.at( i );
            item->InsertHDITEM( );
        }
    }


    HeaderControlItems::size_type HeaderControlItems::Count( ) const
    {
        return items_.size( );
    }

    HeaderControlItems::size_type HeaderControlItems::IndexOf( const HeaderControlItem* theItem ) const
    {
        if ( theItem )
        {
            for ( size_type i = 0; i < items_.size( ); i++ )
            {
                auto item = items_.at( i ).get();
                if ( item )
                {
                    if ( item == theItem )
                    {
                        return i;
                    }
                }
            }
        }
        return npos;
    }

    HeaderControlItems::size_type HeaderControlItems::IndexOf( const HeaderControlItem& theItem ) const
    {
        return IndexOf( &theItem );
    }

    const HeaderControlItem* HeaderControlItems::FocusedItem( ) const
    {
        if ( focusedIndex_ < items_.size( ) )
        {
            return items_.at( focusedIndex_ ).get();
        }
        return nullptr;
    }

    HeaderControlItem* HeaderControlItems::FocusedItem( )
    {
        if ( focusedIndex_ < items_.size( ) )
        {
            return items_.at( focusedIndex_ ).get();
        }
        return nullptr;
    }

    HeaderControlItems::size_type HeaderControlItems::FocusedIndex( ) const
    {
        return focusedIndex_;
    }


    const HeaderControlItem* HeaderControlItems::Add( const WideString& headerText )
    {
        auto newItem = std::make_unique<HeaderControlItem>( this, headerText );
        auto result = newItem.get( );
        items_.push_back( std::move( newItem ) );
        result->InsertHDITEM( );
        return result;
    }
    const HeaderControlItem* HeaderControlItems::Add( const WideString& headerText, HorizontalAlignment alignment )
    {
        auto newItem = std::make_unique<HeaderControlItem>( this, headerText );
        auto result = newItem.get( );
        result->format_ |= HeaderControlItemFormat( int( alignment ) );
        items_.push_back( std::move( newItem ) );
        result->InsertHDITEM( );
        return result;
    }

    HeaderControlItems& HeaderControlItems::RemoveAt( size_type index )
    {
        if ( index < items_.size( ) )
        {
            items_.erase( items_.begin( ) + index );
            if ( headerControl_->IsHandleCreated( ) )
            {
                HWND hWnd = headerControl_->GetHandle( );
                if ( Header_DeleteItem( hWnd, int( index ) ) == FALSE )
                {
                    ThrowLastOSError( );
                }
            }
        }
        return *this;
    }



    // --------------------------------------------------------------------
    // HeaderControl
    // --------------------------------------------------------------------
    class HeaderControlWindowClass : public WindowClass
    {
    public:
        typedef WindowClass Base;
        static WideString windowClassName;
        HeaderControlWindowClass( const WindowClass& existingClass );
    };

    WideString HeaderControlWindowClass::windowClassName = WideString( L"CommonHeaderControlWindowClassName" );

    typedef SuperClassMessageDispatcher<HeaderControl> HeaderControlMessageDispatcher;
    WNDPROC HeaderControlMessageDispatcher::ControlProcedure;

    HeaderControlWindowClass::HeaderControlWindowClass( const WindowClass& existingClass )
        : Base( existingClass )
    {
        HeaderControlMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = HeaderControlMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }


    HeaderControl::HeaderControl( )
        : Base( ),
          items_( new HeaderControlItems( this ) ),
          bitmapMargin_( DefaultBitmapMargin( ) )
    {

    }

    HeaderControl::~HeaderControl( )
    {
        delete items_;
    }

    WindowClass* HeaderControl::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( HeaderControlWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::header_class_name );
            auto newWindowClass = std::make_unique<HeaderControlWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }

    DWORD HeaderControl::GetStyle( ) const
    {
        return Base::GetStyle( );
    }


    const Windows::ImageList& HeaderControl::ImageList( ) const
    {
        return imageList_;
    }

    HeaderControl& HeaderControl::SetImageList( const Windows::ImageList& theImageList )
    {
        imageList_ = Windows::ImageList(theImageList.Value(),false);
        if ( IsHandleCreated( ) )
        {
            if ( imageList_ )
            {
                Header_SetImageList( GetHandle( ), imageList_.Value( ) );
            }
            else
            {
                Header_SetImageList( GetHandle( ), nullptr );
            }
        }
        return *this;
    }

    const Windows::ImageList& HeaderControl::StateImageList( ) const
    {
        return stateImageList_;
    }
    HeaderControl& HeaderControl::SetStateImageList( const Windows::ImageList& theImageList )
    {
        stateImageList_ = Windows::ImageList(theImageList.Value(), false);
        if ( IsHandleCreated( ) )
        {
            if ( stateImageList_ )
            {
                Header_SetStateImageList( GetHandle( ), stateImageList_.Value( ) );
            }
            else
            {
                Header_SetStateImageList( GetHandle( ), nullptr );
            }
        }
        return *this;
    }




    Rectangle HeaderControl::GetItemRectangle( size_t theIndex ) const
    {
        Rectangle result;
        if ( SendMessage( HDM_GETITEMRECT, WPARAM( theIndex ), LPARAM( &result ) ) == 0 )
        {
            ThrowLastOSError( );
        }
        return result;
    }
    Rectangle HeaderControl::GetItemRectangle( const HeaderControlItem* theItem ) const
    {
        if ( theItem == nullptr )
        {
            throw ArgumentNullException( L"theItem" );
        }
        auto index = items_->IndexOf( theItem );
        if ( index == HeaderControlItems::npos )
        {
            throw ArgumentNullException( L"theItem is not an HeaderControlItem belonging to this HeaderControl" );
        }
        return GetItemRectangle( index );
    }
    Rectangle HeaderControl::GetItemRectangle( const HeaderControlItem& theItem ) const
    {
        auto index = items_->IndexOf( theItem );
        if ( index == HeaderControlItems::npos )
        {
            throw ArgumentNullException( L"theItem is not an HeaderControlItem belonging to this HeaderControl" );
        }
        return GetItemRectangle( index );
    }

    int HeaderControl::DefaultBitmapMargin( )
    {
        return Environment::SystemMetrics::EdgeBorderWidth( ) * 3;
    }


    HeaderControl& HeaderControl::SetBitmapMargin( int theMargin )
    {
        bitmapMargin_ = theMargin;
        if ( IsHandleCreated( ) )
        {
            SendMessage( HDM_SETBITMAPMARGIN, theMargin );
        }
        return *this;
    }


    void HeaderControl::DoOnHandleCreated( )
    {
        items_->DoOnHandleCreated( );
    }
    void HeaderControl::DoOnWindowSubClassed( )
    {
    }

    void HeaderControl::DoOnBeginDrag( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnBeginDrag( pNMHEADER );
        OnBeginDrag( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnBeginFilterEdit( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnBeginFilterEdit( pNMHEADER );
        OnBeginFilterEdit( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnBeginTrack( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnBeginTrack( pNMHEADER );
        OnBeginTrack( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnDividerDoubleClick( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnDividerDoubleClick( pNMHEADER );
        OnDividerDoubleClick( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnDropDown( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnDropDown( pNMHEADER );
        OnDropDown( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnEndDrag( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnEndDrag( pNMHEADER );
        OnEndDrag( this, pNMHEADER, item );
    }

    void HeaderControl::DoOnEndFilterEdit( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnEndFilterEdit( pNMHEADER );
        OnEndFilterEdit( this, pNMHEADER, item );
    }

    void HeaderControl::DoOnEndTrack( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnEndTrack( pNMHEADER );
        OnEndTrack( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnFilterButtonClicked( NMHDFILTERBTNCLICK* pNMHDFILTERBTNCLICK, HeaderControlItem& item )
    {
        item.DoOnFilterButtonClicked( pNMHDFILTERBTNCLICK );
        OnFilterButtonClicked( this, pNMHDFILTERBTNCLICK, item );
    }
    void HeaderControl::DoOnFilterChange( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnFilterChange( pNMHEADER );
        OnFilterChange( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnGetDispInfo( NMHDDISPINFO* pNMHDDISPINFO, HeaderControlItem& item )
    {
        item.DoOnGetDispInfo( pNMHDDISPINFO );
        OnGetDispInfo( this, pNMHDDISPINFO, item );
    }
    void HeaderControl::DoOnItemChanged( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnItemChanged( pNMHEADER );
        OnItemChanged( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnItemChanging( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnItemChanging( pNMHEADER );
        OnItemChanging( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnItemClicked( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnItemClicked( pNMHEADER );
        OnItemClicked( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnItemDoubleClicked( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnItemDoubleClicked( pNMHEADER );
        OnItemDoubleClicked( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnItemKeyDown( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnItemKeyDown( pNMHEADER );
        OnItemKeyDown( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnItemStateIconClicked( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnItemStateIconClicked( pNMHEADER );
        OnItemStateIconClicked( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnItemOverflowButtonClicked( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnItemOverflowButtonClicked( pNMHEADER );
        OnItemOverflowButtonClicked( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnTrack( NMHEADER* pNMHEADER, HeaderControlItem& item )
    {
        item.DoOnTrack( pNMHEADER );
        OnTrack( this, pNMHEADER, item );
    }
    void HeaderControl::DoOnCustomDraw( NMCUSTOMDRAW* pNMCUSTOMDRAW )
    {
        OnCustomDraw( this, pNMCUSTOMDRAW );
    }
    void HeaderControl::DoOnRightClicked( const Point& mousePosition )
    {
        OnRightClicked( this, mousePosition );
    }
    void HeaderControl::DoOnCaptureReleased( const Point& mousePosition )
    {
        OnCaptureReleased( this, mousePosition );
    }


    void HeaderControl::DoOnNotify( Message& message )
    {
        Base::DoOnNotify( message );
        if ( message.handled == false )
        {
            NMHDR* pNMHDR = (NMHDR*)message.lParam;
            if ( pNMHDR )
            {
                switch ( pNMHDR->code )
                {
                    case HDN_BEGINDRAG:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get();
                        this->DoOnBeginDrag( pNMHEADER, *item );
                    }
                    break;
                    case HDN_BEGINFILTEREDIT:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnBeginFilterEdit( pNMHEADER, *item );
                    }
                    break;
                    case HDN_BEGINTRACK:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnBeginTrack( pNMHEADER, *item );
                    }
                    break;
                    case HDN_DIVIDERDBLCLICK:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnDividerDoubleClick( pNMHEADER, *item );
                    }
                    break;
                    case HDN_DROPDOWN:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnDropDown( pNMHEADER, *item );
                    }
                    break;
                    case HDN_ENDDRAG:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnEndDrag( pNMHEADER, *item );
                    }
                    break;
                    case HDN_ENDFILTEREDIT:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnEndFilterEdit( pNMHEADER, *item );
                    }
                    break;
                    case HDN_ENDTRACK:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnEndTrack( pNMHEADER, *item );
                    }
                    break;
                    case HDN_FILTERBTNCLICK:
                    {
                        NMHDFILTERBTNCLICK* pNMHDFILTERBTNCLICK = (NMHDFILTERBTNCLICK*)pNMHDR;
                        auto item = items_->items_.at( pNMHDFILTERBTNCLICK->iItem ).get( );
                        this->DoOnFilterButtonClicked( pNMHDFILTERBTNCLICK, *item );
                    }
                    break;
                    case HDN_FILTERCHANGE:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnFilterChange( pNMHEADER, *item );
                    }
                    break;
                    case HDN_GETDISPINFO:
                    {
                        NMHDDISPINFO* pNMHDDISPINFO = (NMHDDISPINFO*)pNMHDR;
                        auto item = items_->items_.at( pNMHDDISPINFO->iItem ).get( );
                        this->DoOnGetDispInfo( pNMHDDISPINFO, *item );
                    }
                    break;
                    case HDN_ITEMCHANGED:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnItemChanged( pNMHEADER, *item );
                    }
                    break;
                    case HDN_ITEMCHANGING:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnItemChanging( pNMHEADER, *item );
                    }
                    break;
                    case HDN_ITEMCLICK:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnItemClicked( pNMHEADER, *item );
                    }
                    break;
                    case HDN_ITEMDBLCLICK:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnItemDoubleClicked( pNMHEADER, *item );
                    }
                    break;
                    case HDN_ITEMKEYDOWN:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnItemKeyDown( pNMHEADER, *item );
                    }
                    break;
                    case HDN_ITEMSTATEICONCLICK:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnItemStateIconClicked( pNMHEADER, *item );
                    }
                    break;
                    case HDN_OVERFLOWCLICK:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnItemOverflowButtonClicked( pNMHEADER, *item );
                    }
                    break;
                    case HDN_TRACK:
                    {
                        NMHEADER* pNMHEADER = (NMHEADER*)pNMHDR;
                        auto item = items_->items_.at( pNMHEADER->iItem ).get( );
                        this->DoOnTrack( pNMHEADER, *item );
                    }
                    break;
                    case NM_CUSTOMDRAW:
                    {
                        NMCUSTOMDRAW* pNMCUSTOMDRAW = (NMCUSTOMDRAW*)pNMHDR;
                        this->DoOnCustomDraw( pNMCUSTOMDRAW );
                    }
                    break;
                    case NM_RCLICK:
                    {
                        Point pt( message.pt );
                        this->DoOnRightClicked( pt );
                    }
                    break;
                    case NM_RELEASEDCAPTURE:
                    {
                        Point pt( message.pt );
                        this->DoOnCaptureReleased( pt );
                    }
                    break;
                };
            }
        }
    }



    // --------------------------------------------------------------------
    // ListView
    // --------------------------------------------------------------------
    class ListViewWindowClass : public WindowClass
    {
    public:
        typedef WindowClass Base;
        static WideString windowClassName;
        ListViewWindowClass( const WindowClass& existingClass );
    };

    WideString ListViewWindowClass::windowClassName = WideString( L"CommonListViewWindowClassName" );

    typedef SuperClassMessageDispatcher<ListView> ListViewMessageDispatcher;
    WNDPROC ListViewMessageDispatcher::ControlProcedure;

    ListViewWindowClass::ListViewWindowClass( const WindowClass& existingClass )
        : Base( existingClass )
    {
        ListViewMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = ListViewMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }

    ListView::ListView( )
        : Base( )
    {

    }

    WindowClass* ListView::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( ListViewWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::listview_class_name );
            auto newWindowClass = std::make_unique<ListViewWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }

    DWORD ListView::GetStyle( ) const
    {
        return Base::GetStyle( );
    }


    // --------------------------------------------------------------------
    // MonthCalendar
    // --------------------------------------------------------------------
    class MonthCalendarWindowClass : public WindowClass
    {
    public:
        typedef WindowClass Base;
        static WideString windowClassName;
        MonthCalendarWindowClass( const WindowClass& existingClass );
    };

    WideString MonthCalendarWindowClass::windowClassName = WideString( L"CommonMonthCalendarWindowClassName" );

    typedef SuperClassMessageDispatcher<MonthCalendar> MonthCalendarMessageDispatcher;
    WNDPROC MonthCalendarMessageDispatcher::ControlProcedure;

    MonthCalendarWindowClass::MonthCalendarWindowClass( const WindowClass& existingClass )
        : Base( existingClass )
    {
        MonthCalendarMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = MonthCalendarMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }

    MonthCalendar::MonthCalendar( )
        : Base( )
    {

    }

    WindowClass* MonthCalendar::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( MonthCalendarWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::monthcal_class_name );
            auto newWindowClass = std::make_unique<MonthCalendarWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }

    DWORD MonthCalendar::GetStyle( ) const
    {
        return Base::GetStyle( );
    }



    // --------------------------------------------------------------------
    // TreeEditBase
    // --------------------------------------------------------------------
    TreeEditBase::TreeEditBase( )
        : Base( )
    {

    }


    // --------------------------------------------------------------------
    // EditBase
    // --------------------------------------------------------------------
    EditBase::EditBase( )
        : Base( )
    {

    }



    // --------------------------------------------------------------------
    // TextEditBase
    // --------------------------------------------------------------------
    TextEditBase::TextEditBase( )
        : Base( )
    {
    }

    // --------------------------------------------------------------------
    // TextEdit
    // --------------------------------------------------------------------
    class TextEditWindowClass : public WindowClass
    {
    public:
        typedef WindowClass Base;
        static WideString windowClassName;
        TextEditWindowClass( const WindowClass& existingClass );
    };

    WideString TextEditWindowClass::windowClassName = WideString( L"CommonTextEditWindowClassName" );

    typedef SuperClassMessageDispatcher<TextEdit> TextEditMessageDispatcher;
    WNDPROC TextEditMessageDispatcher::ControlProcedure;

    TextEditWindowClass::TextEditWindowClass( const WindowClass& existingClass )
        : Base( existingClass )
    {
        TextEditMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = TextEditMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }

    TextEdit::TextEdit( TextEditStyles editStyle )
        : Base( ), editStyle_( editStyle )
    {

    }

    WindowClass* TextEdit::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( TextEditWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::edit_class_name );
            auto newWindowClass = std::make_unique<TextEditWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move(newWindowClass) );
        }
        return windowClass;
    }

    DWORD TextEdit::GetStyle( ) const
    {
        return Base::GetStyle( ) + static_cast<UInt32>( editStyle_ );
    }


    bool TextEdit::CanUndo( ) const
    {
        LRESULT messageResult = SendMessage( UINT( EM_CANUNDO ) );
        return messageResult != 0;

    }

    TextEdit& TextEdit::Undo( )
    {
        SendMessage( EM_UNDO );
        return *this;
    }

    TextEdit& TextEdit::EmptyUndoBuffer( )
    {
        SendMessage( EM_EMPTYUNDOBUFFER );
        return *this;
    }
    TextEdit& TextEdit::FmtLines( bool addSoftLinebreaks )
    {
        SendMessage( EM_FMTLINES, addSoftLinebreaks ? TRUE : FALSE );
        return *this;
    }
    WideString TextEdit::CueBannerText( ) const
    {
        wchar_t buffer[1024] = { 0, };
        if ( SendMessage( EM_GETCUEBANNER, WPARAM( buffer ), 1024 ) != FALSE )
        {
            return WideString( buffer );
        }
        return WideString( );
    }

    TextEdit& TextEdit::SetCueBannerText( const WideString& theText, bool displayWhileFocused )
    {
        SetCueBannerText( theText.c_str( ), displayWhileFocused );
        return *this;
    }
    TextEdit& TextEdit::SetCueBannerText( const wchar_t* theText, bool displayWhileFocused )
    {
        if ( theText && theText[0] )
        {
            SendMessage( EM_SETCUEBANNER, WPARAM( displayWhileFocused ? TRUE : FALSE ), LPARAM( theText ) );
        }
        else
        {
            SendMessage( EM_SETCUEBANNER, WPARAM( displayWhileFocused ? TRUE : FALSE ), LPARAM( L"" ) );
        }
        return *this;
    }

    int TextEdit::GetFirstVisibleLine( ) const
    {
        LRESULT messageResult = SendMessage( UINT( EM_GETFIRSTVISIBLELINE ) );
        return int( messageResult );
    }
    UINT TextEdit::TextLimit( ) const
    {
        LRESULT messageResult = SendMessage( UINT( EM_GETLIMITTEXT ) );
        return UINT( messageResult );
    }
    TextEdit& TextEdit::SetTextLimit( UINT theValue )
    {
        SendMessage( UINT( EM_SETLIMITTEXT ), theValue );
        return *this;
    }


    int TextEdit::LineIndex( int theIndex ) const
    {
        LRESULT messageResult = SendMessage( UINT( EM_LINEINDEX ), WPARAM( theIndex ) );
        return int( messageResult );
    }

    int TextEdit::LineLength( int theIndex ) const
    {
        int lineIndex = LineIndex( theIndex );
        if ( lineIndex >= 0 )
        {
            LRESULT messageResult = SendMessage( UINT( EM_LINELENGTH ), WPARAM( lineIndex ) );
            return int( messageResult );
        }
        return -1;
    }
    WideString TextEdit::Line( int theIndex ) const
    {
        int lineLength = LineLength( theIndex );
        if ( lineLength > 0 )
        {
            WideString result( nullptr, WideString::size_type( lineLength ) );
            *(WORD*)result.c_str( ) = WORD( lineLength );
            LRESULT messageResult = SendMessage( UINT( EM_GETLINE ), WPARAM( theIndex ), LPARAM( result.c_str( ) ) );
            result.resize( messageResult );
            return result;
        }
        return WideString( );
    }
    int TextEdit::LineCount( ) const
    {
        LRESULT messageResult = SendMessage( UINT( EM_GETLINECOUNT ) );
        return int( messageResult );
    }
    bool TextEdit::IsModified( ) const
    {
        LRESULT messageResult = SendMessage( UINT( EM_GETMODIFY ) );
        return messageResult != 0;
    }

    wchar_t TextEdit::PasswordChar( ) const
    {
        LRESULT messageResult = SendMessage( UINT( EM_GETPASSWORDCHAR ) );
        return wchar_t( messageResult );
    }
    TextEdit& TextEdit::SetPasswordChar( wchar_t theValue )
    {
        SendMessage( UINT( EM_SETPASSWORDCHAR ), theValue );
        return *this;
    }

    Range TextEdit::Selection( ) const
    {
        DWORD start;
        DWORD end;
        SendMessage( UINT( EM_GETSEL ), WPARAM( &start ), LPARAM( &end ) );
        return Range( start, end );
    }
    TextEdit& TextEdit::SetSelection( const Range& selectionRange )
    {
        SendMessage( UINT( EM_SETSEL ), WPARAM( selectionRange.Start( ) ), LPARAM( selectionRange.End( ) ) );
        return *this;
    }

    void TextEdit::DoOnSetEnabled( bool theValue )
    {
        Edit_Enable( this->GetHandle( ), theValue );
    }

    TextEdit& TextEdit::ReplaceSelection( const WideString& theText )
    {
        ReplaceSelection( theText.c_str( ) );
        return *this;
    }
    TextEdit& TextEdit::ReplaceSelection( const wchar_t* theText )
    {
        if ( theText && theText[0] )
        {
            SendMessage( UINT( EM_REPLACESEL ), FALSE, LPARAM( theText ) );
        }
        else
        {
            SendMessage( UINT( EM_REPLACESEL ), FALSE, LPARAM( L"" ) );
        }
        return *this;
    }
    TextEdit& TextEdit::Append( const WideString& theText )
    {
        Range currentSelection = Selection( );
        int endOfText = TextLength( );
        Range endSelection( endOfText, endOfText );
        SetSelection( endSelection );
        ReplaceSelection( theText );
        SetSelection( currentSelection );
        return *this;
    }


    TextEdit& TextEdit::Append( const wchar_t* theText )
    {
        if ( theText && theText[0] )
        {
            WideString s( theText );
            Append( s );
        }
        return *this;
    }



    // --------------------------------------------------------------------
    // MemoEdit
    // --------------------------------------------------------------------
    MemoEdit::MemoEdit( )
        : Base( )
    {

    }


    DWORD MemoEdit::GetStyle( ) const
    {
        return Base::GetStyle( ) | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL;
    }

    int MemoEdit::FirstVisibleLine( ) const
    {
        LRESULT messageResult = SendMessage( EM_GETFIRSTVISIBLELINE );
        return int( messageResult );
    }

    MemoEdit& MemoEdit::AppendLine( const WideString& theText )
    {
        auto length = theText.length( );
        if ( length )
        {
            WideString text( L"\r\n", 2 );
            text.append( theText.c_str( ), length );
            Append( text );
        }
        return *this;
    }

    MemoEdit& MemoEdit::AppendLine( const wchar_t* theText )
    {
        if ( theText && theText[0] )
        {
            auto len = wcslen( theText );
            WideString s( L"\r\n", 2 );
            s.append( theText, len );
            Append( s );
        }
        return *this;
    }


    // --------------------------------------------------------------------
    // HotKey
    // --------------------------------------------------------------------
    class HotKeyWindowClass : public WindowClass
    {
    public:
        typedef WindowClass Base;
        static WideString windowClassName;
        HotKeyWindowClass( const WindowClass& existingClass );
    };

    WideString HotKeyWindowClass::windowClassName = WideString( L"CommonHotKeyWindowClassName" );

    typedef SuperClassMessageDispatcher<HotKey> HotKeyMessageDispatcher;
    WNDPROC HotKeyMessageDispatcher::ControlProcedure;

    HotKeyWindowClass::HotKeyWindowClass( const WindowClass& existingClass )
        : Base( existingClass )
    {
        HotKeyMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = HotKeyMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }


    HotKey::HotKey( )
        : Base( )
    {
    }
    WindowClass* HotKey::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( HotKeyWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::hotkey_class_name );
            auto newWindowClass = std::make_unique<HotKeyWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }
    DWORD HotKey::GetStyle( ) const
    {
        DWORD result = Base::GetStyle( );
        return result;
    }



    // --------------------------------------------------------------------
    // ScrollBar
    // --------------------------------------------------------------------
    class ScrollBarWindowClass : public WindowClass
    {
    public:
        typedef WindowClass Base;
        static WideString windowClassName;
        ScrollBarWindowClass( const WindowClass& existingClass );
    };

    WideString ScrollBarWindowClass::windowClassName = WideString( L"CommonScrollBarWindowClassName" );

    typedef SuperClassMessageDispatcher<ScrollBar> ScrollBarMessageDispatcher;
    WNDPROC ScrollBarMessageDispatcher::ControlProcedure;

    ScrollBarWindowClass::ScrollBarWindowClass( const WindowClass& existingClass )
        : Base( existingClass )
    {
        ScrollBarMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = ScrollBarMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }

    ScrollBar::ScrollBar( )
        : Base( )
    {

    }

    WindowClass* ScrollBar::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( ScrollBarWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::scrollbar_class_name );
            auto newWindowClass = std::make_unique<ScrollBarWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }

    DWORD ScrollBar::GetStyle( ) const
    {
        return Base::GetStyle( );
    }


    // --------------------------------------------------------------------
    // HScrollBar
    // --------------------------------------------------------------------
    HScrollBar::HScrollBar( )
        : Base( )
    {

    }

    DWORD HScrollBar::GetStyle( ) const
    {
        return Base::GetStyle( );
    }

    // --------------------------------------------------------------------
    // VScrollBar
    // --------------------------------------------------------------------
    VScrollBar::VScrollBar( )
        : Base( )
    {

    }

    DWORD VScrollBar::GetStyle( ) const
    {
        return Base::GetStyle( );
    }

    // --------------------------------------------------------------------
    // Timer::TimerControl
    // --------------------------------------------------------------------
    UINT_PTR Timer::TimerControl::TimerID_ = 1;
    Timer::TimerControl::TimerControl( Timer& theTimer )
        : Base( ), timer_( theTimer ), timerId_( 0 )
    {
        SetVisible( false );
        SetEnabled( false );
        SetTabStop( false );
    }


    void Timer::TimerControl::HandleMessage( Message& message )
    {
        Base::HandleMessage( message );
        if ( message.handled == false )
        {
            if ( ( message.message == WM_TIMER ) && ( message.wParam == timerId_ ) )
            {
                timer_.DoOnTick( );
            }
            else if ( message.message == WM_CLOSE )
            {
                StopTimer( );
            }
        }
    }

    HWND Timer::TimerControl::CreateHandle( )
    {
        auto windowClass = this->GetWindowClass( );
        HWND result = nullptr;
        if ( windowClass )
        {
            const WideString& className = windowClass->Name( );
            if ( className.length( ) )
            {
                HWND hWndParent = HWND_MESSAGE;
                result = ::CreateWindowExW( this->GetStyleEx( ),
                    className.c_str( ),
                    nullptr, this->GetStyle( ),
                    0, 0, 0, 0,
                    hWndParent, 0, 0, (LPVOID)this );
                if ( !result )
                {
                    ThrowLastOSError( );
                }
            }
        }
        return result;
    }

    DWORD Timer::TimerControl::GetStyle( ) const
    {
        return Base::GetStyle( );
    }

    void Timer::TimerControl::StopTimer( )
    {
        if ( IsHandleCreated( ) )
        {
            if ( KillTimer( GetHandle( ), timerId_ ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
    }

    void Timer::TimerControl::StartTimer( )
    {
        UINT period = UINT( timer_.interval_.TotalMilliseconds( ) );
        timerId_ = SetTimer( GetHandle( ), TimerID_++, period, nullptr );
    }



    void Timer::TimerControl::DoBeforeHandleDestroy( )
    {
        StopTimer( );
        Base::DoBeforeHandleDestroy( );

    }


    // --------------------------------------------------------------------
    // Timer
    // --------------------------------------------------------------------
    Timer::Timer( )
        : interval_( TimeSpan::FromMilliseconds( 100 ) ),
          enabled_( false )
    {
    }


    TimeSpan Timer::Interval( ) const
    {
        return interval_;
    }
    Timer& Timer::SetInterval( const TimeSpan& interval )
    {
        if ( interval_ != interval )
        {
            interval_ = interval;
            if ( timerControl_ )
            {
                timerControl_->StopTimer( );
                timerControl_->StartTimer( );
            }
        }
        return *this;
    }


    bool Timer::Enabled( ) const
    {
        return enabled_;
    }
    Timer& Timer::SetEnabled( bool theValue )
    {
        if ( enabled_ != theValue )
        {
            enabled_ = theValue;
            if ( enabled_ )
            {
                timerControl_ = std::make_unique<TimerControl>( *this );
                timerControl_->StartTimer( );
            }
            else if ( timerControl_ )
            {
                timerControl_ = nullptr;
            }
        }
        return *this;
    }


    void Timer::DoOnTick( )
    {
        OnTick( this );
    }


    // --------------------------------------------------------------------
    // TreeView
    // --------------------------------------------------------------------
    class TreeViewWindowClass : public WindowClass
    {
    public:
        typedef WindowClass Base;
        static WideString windowClassName;
        TreeViewWindowClass( const WindowClass& existingClass );
    };

    WideString TreeViewWindowClass::windowClassName = WideString( L"CommonTreeViewWindowClassName" );

    typedef SuperClassMessageDispatcher<TreeView> TreeViewMessageDispatcher;
    WNDPROC TreeViewMessageDispatcher::ControlProcedure;

    TreeViewWindowClass::TreeViewWindowClass( const WindowClass& existingClass )
        : Base( existingClass )
    {
        TreeViewMessageDispatcher::ControlProcedure = existingClass.Procedure( );
        SetName( windowClassName );
        WNDPROC procedure = TreeViewMessageDispatcher::WndProc;
        SetProcedure( procedure );
    }


    TreeView::TreeView( ) = default;
    TreeView::~TreeView( ) = default;

    WindowClass* TreeView::GetWindowClass( ) const
    {
        auto windowClass = Application::GetWindowClass( TreeViewWindowClass::windowClassName );
        if ( !windowClass )
        {
            auto windowsWindowClass = Application::GetWindowClass( WindowClass::treeview_class_name );
            auto newWindowClass = std::make_unique<TreeViewWindowClass>( *windowsWindowClass );
            windowClass = newWindowClass.get( );
            Application::RegisterWindowClass( std::move( newWindowClass ) );
        }
        return windowClass;
    }


    DWORD TreeView::GetStyle( ) const
    {
        return Base::GetStyle( ) | TVS_DISABLEDRAGDROP | TVS_HASBUTTONS | TVS_HASLINES;
    }

    TreeViewItem TreeView::AddItem( const WideString& theText )
    {
        TreeViewItem item( *this, theText );
        TVINSERTSTRUCTW tvis = { 0, };
        tvis.itemex.pszText = (LPWSTR)theText.c_str( );

        auto newHandle = TreeView_InsertItem( this->GetHandle( ), &tvis );

        item.handle_ = newHandle;
        return item;
    }


    // --------------------------------------------------------------------
    // TreeViewItem
    // --------------------------------------------------------------------
    TreeViewItem::TreeViewItem( Windows::TreeView& treeView, const WideString& theText )
        : treeView_( treeView ), handle_( 0 ), text_( theText )
    {
    }

}

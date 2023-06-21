#pragma once
#ifndef __HWMENU_H__
#define __HWMENU_H__

#include <HWHandles.h>
#include <HWmessage.h>

namespace Harlinn::Windows
{
    class Control;
    class Menu;
    class MenuItems;
    class MenuItem
    {
        friend class Control;
        friend class Menu;
        friend class MenuItems;

        Menu* parentMenu_ = nullptr;
        HBITMAP bitmap_ = 0;
        HBITMAP checkedBitmap_ = 0;
        HBITMAP uncheckedBitmap_ = 0;

        bool checked_ : 1 = false;
        bool isDefault_ : 1 = false;
        bool disabled_ : 1 = false;
        bool grayed_ : 1 = false;
        bool highlighted_ : 1 = false;


        bool menuBarBreak_ : 1 = false;
        bool menuBreak_ : 1 = false;
        bool ownerDraw_ : 1 = false;

        
    public:
        MenuItem( Menu* parentMenu )
            : parentMenu_( parentMenu )
        {

        }

        MenuItem( const MenuItem& other ) = delete;
        MenuItem( MenuItem&& other ) = delete;
        MenuItem& operator = ( const MenuItem& other ) = delete;
        MenuItem& operator = ( MenuItem&& other ) = delete;


        MenuItems& ParentMenuItems( ) const;
        Menu* ParentMenu( ) const
        {
            return parentMenu_;
        }
        int IndexOf( ) const;

        BitmapHandle Bitmap( ) const noexcept
        {
            return BitmapHandle(bitmap_,false);
        }
        MenuItem& SetBitmap( const BitmapHandle& bitmap )
        {
            if ( bitmap_ != bitmap )
            {
                bitmap_ = bitmap;
                this->UpdateMenuItem( );
            }
            return *this;
        }

        BitmapHandle CheckedBitmap( ) const noexcept
        {
            return BitmapHandle( checkedBitmap_, false );
        }
        MenuItem& SetCheckedBitmap( const BitmapHandle& checkedBitmap )
        {
            if ( checkedBitmap_ != checkedBitmap )
            {
                checkedBitmap_ = checkedBitmap;
                this->UpdateMenuItem( );
            }
            return *this;
        }

        BitmapHandle UncheckedBitmap( ) const noexcept
        {
            return BitmapHandle( uncheckedBitmap_, false );
        }
        MenuItem& SetUncheckedBitmap( const BitmapHandle& uncheckedBitmap )
        {
            if ( uncheckedBitmap_ != uncheckedBitmap )
            {
                uncheckedBitmap_ = uncheckedBitmap;
                this->UpdateMenuItem( );
            }
            return *this;
        }

        constexpr bool IsChecked( ) const noexcept
        {
            return checked_;
        }

        MenuItem& SetChecked( bool value = true )
        {
            if ( checked_ != value )
            {
                checked_ = value;
                this->UpdateMenuItem( );
            }
            return *this;
        }

        constexpr bool IsDefault( ) const noexcept
        {
            return isDefault_;
        }
        MenuItem& SetDefault( bool value = true )
        {
            if ( isDefault_ != value )
            {
                isDefault_ = value;
                this->UpdateMenuItem( );
            }
            return *this;
        }

        constexpr bool IsDisabled( ) const noexcept
        {
            return disabled_;
        }
        MenuItem& SetDisabled( bool value = true )
        {
            if ( disabled_ != value )
            {
                disabled_ = value;
                this->UpdateMenuItem( );
            }
            return *this;
        }

        constexpr bool IsEnabled( ) const noexcept
        {
            return ( disabled_ || grayed_ ) == false;
        }
        MenuItem& SetEnabled( bool value = true )
        {
            return SetDisabled( value ? false : true );;
        }

        constexpr bool IsGrayed( ) const noexcept
        {
            return grayed_;
        }

        MenuItem& SetGrayed( bool value = true )
        {
            if ( grayed_ != value )
            {
                grayed_ = value;
                this->UpdateMenuItem( );
            }
            return *this;
        }

        constexpr bool IsHighlighted( ) const noexcept
        {
            return highlighted_;
        }
        MenuItem& SetHighlighted( bool value = true )
        {
            if ( highlighted_ != value )
            {
                highlighted_ = value;
                this->UpdateMenuItem( );
            }
            return *this;
        }

        boost::signals2::signal<void( MenuItem* sender )> OnClick;
        boost::signals2::signal<void( MenuItem* sender, MEASUREITEMSTRUCT& measureItemStruct )> OnMeasureItem;
        boost::signals2::signal<void( MenuItem* sender, DRAWITEMSTRUCT& drawItemStruct )> OnDrawItem;
    protected:
        HW_EXPORT virtual void DoOnAdd( ) const;
        HW_EXPORT virtual void DoOnRemove( ) const;
        HW_EXPORT virtual void UpdateMenuItem( ) const;
        HW_EXPORT virtual void InitializeMenuItemInfo( MENUITEMINFOW& info ) const;
        HW_EXPORT virtual void DoOnMenuCommand( Message& message );
        HW_EXPORT virtual void DoOnMeasureItem( MEASUREITEMSTRUCT& measureItemStruct );
        HW_EXPORT virtual void DoOnDrawItem( DRAWITEMSTRUCT& drawItemStruct );

    };


    class TextMenuItem : public MenuItem
    {
        WideString text_;
    public:
        using Base = MenuItem ;

        TextMenuItem( Menu* parentMenu, const wchar_t* text )
            : Base( parentMenu ), text_( text )
        {
        }
        TextMenuItem( Menu* parentMenu, const WideString& text )
            : Base( parentMenu ), text_( text )
        {
        }

        TextMenuItem& SetText( const wchar_t* text )
        {
            if ( text_ != text )
            {
                text_ = text;
                this->UpdateMenuItem( );
            }
            return *this;
        }
        TextMenuItem& SetText( const WideString& text )
        {
            if ( text_ != text )
            {
                text_ = text;
                this->UpdateMenuItem( );
            }
            return *this;
        }

        const WideString& Text( ) const
        {
            return text_;
        }

    protected:
        virtual void InitializeMenuItemInfo( MENUITEMINFOW& info ) const override
        {
            Base::InitializeMenuItemInfo( info );
            info.fMask |= MIIM_STRING;
            info.cch = static_cast<UINT>(text_.length( ));
            info.dwTypeData = const_cast<LPWSTR>(text_.c_str( ));
        }
    };

    class SeparatorMenuItem : public MenuItem
    {
    public:
        typedef MenuItem Base;

        SeparatorMenuItem( Menu* parentMenu )
            : Base( parentMenu )
        { }
    protected:
        virtual void DoOnAdd( ) const override;
    };


    class SubMenuItem : public MenuItem
    {
        WideString text_;
        mutable std::unique_ptr<Menu> menu_;
    public:
        typedef MenuItem Base;

        explicit SubMenuItem( Menu* parentMenu, const wchar_t* text )
            : Base( parentMenu ),
              text_( text )
        {
        }
        explicit SubMenuItem( Menu* parentMenu, const WideString& text )
            : Base( parentMenu ),
              text_( text )
        {
        }

        Menu& Menu( ) const;

        const MenuItems& Items( ) const;
        MenuItems& Items( );

        void Add( std::unique_ptr<MenuItem>&& menuItem );
        void Remove( const MenuItem* menuItem );

        TextMenuItem* AddMenuItem( const wchar_t* text );
        template<typename Func>
            requires std::is_invocable_v<Func, MenuItem*>
        TextMenuItem* AddMenuItem( const wchar_t* text, Func&& func );

        TextMenuItem* AddMenuItem( const WideString& text );

        SeparatorMenuItem* AddSeparator( );

        SubMenuItem* AddSubMenu( const wchar_t* text );
        SubMenuItem* AddSubMenu( const WideString& text );

    protected:
        virtual void InitializeMenuItemInfo( MENUITEMINFOW& info ) const;
    };




    class MenuItems 
    {
    public:
        typedef std::vector< std::unique_ptr<MenuItem> > vector;
    private:
        friend class Menu;
        Menu* owner_;
        vector items_;
    public:
        MenuItems( Menu* owner )
            : owner_( owner )
        {
        }
        ~MenuItems( )
        {
            std::for_each( items_.begin( ), items_.end( ), []( std::unique_ptr<MenuItem>& item ) { item->parentMenu_ = nullptr; } );
        }

        MenuItems( const MenuItems& other ) = delete;
        MenuItems( MenuItems&& other ) = delete;
        MenuItems& operator = ( const MenuItems& other ) = delete;
        MenuItems& operator = ( MenuItems&& other ) = delete;


        constexpr Menu* Menu( ) const noexcept
        {
            return owner_;
        }
        void Add( std::unique_ptr< MenuItem >&& menuItem )
        {
            if ( menuItem )
            {
                auto thisMenu = Menu( );
                menuItem->parentMenu_ = thisMenu;
                auto* rawPtr = menuItem.get( );
                items_.emplace_back( std::move( menuItem ) );
                rawPtr->DoOnAdd( );
            }
        }
        void Remove( const MenuItem* menuItem )
        {
            if ( menuItem )
            {
                int index = IndexOf( menuItem );
                menuItem->DoOnRemove( );
                items_.erase( items_.begin( ) + index );
            }
        }

        TextMenuItem* AddMenuItem( const wchar_t* text )
        {
            auto menu = Menu( );
            auto menuItem = std::make_unique<TextMenuItem>( menu, text );
            auto result = menuItem.get( );
            Add( std::move( menuItem ) );
            return result;
        }
        template<typename Func>
        requires std::is_invocable_v<Func, MenuItem*>
        TextMenuItem* AddMenuItem( const wchar_t* text, Func&& func )
        {
            auto result = AddMenuItem( text );
            result->OnClick.connect( std::forward<Func>( func ) );
            return result;
        }


        TextMenuItem* AddMenuItem( const WideString& text )
        {
            return AddMenuItem( text.c_str() );
        }

        SeparatorMenuItem* AddSeparator( )
        {
            auto menu = Menu( );
            auto menuItem = std::make_unique<SeparatorMenuItem>( menu );
            auto result = menuItem.get( );
            Add( std::move( menuItem ) );
            return result;
        }

        SubMenuItem* AddSubMenu( const wchar_t* text )
        {
            auto menu = Menu( );
            auto menuItem = std::make_unique<SubMenuItem>( menu, text );
            auto result = menuItem.get( );
            Add( std::move( menuItem ) );
            return result;
        }
        SubMenuItem* AddSubMenu( const WideString& text )
        {
            auto menu = Menu( );
            auto menuItem = std::make_unique<SubMenuItem>( menu, text );
            auto result = menuItem.get( );
            Add( std::move( menuItem ) );
            return result;
        }

        int IndexOf( const MenuItem* menuItem ) const
        {
            auto it = std::find_if( items_.begin( ), items_.end( ), [menuItem]( auto& ptr ) { return ptr.get( ) == menuItem;  } );
            if ( it != items_.end( ) )
            {
                auto offset = std::distance( items_.begin( ), it );
                return static_cast<int>( offset );
            }
            return -1;
        }
        const MenuItem* Item( int position ) const
        {
            if ( position >= 0 && static_cast<size_t>( position ) < items_.size( ) )
            {
                return items_[static_cast<size_t>( position )].get( );
            }
            return nullptr;
        }
        MenuItem* Item( int position )
        {
            if ( position >= 0 && static_cast<size_t>( position ) < items_.size( ) )
            {
                return items_[static_cast<size_t>( position )].get( );
            }
            return nullptr;
        }
    };


    class Menu
    {
        friend class MenuItems;
        friend class Control;

        static std::unordered_map<HMENU, Menu*> menuMap_;

        HW_EXPORT static void AddToMenuMap( HMENU hMenu, Menu* menu );
        HW_EXPORT static void RemoveFromMenuMap( HMENU hMenu );
        HW_EXPORT static Menu* GetFromMenuMap( HMENU hMenu );

        MenuHandle handle_;
        MenuItems items_;

    protected:
        HW_EXPORT virtual void DoOnInitMenu( Message& message );
        HW_EXPORT virtual void DoOnInitMenuPopup( Message& message );
        HW_EXPORT virtual void DoOnMenuCommand( Message& message );

    public:
        Menu( MenuHandle menuHandle )
            : handle_( std::move(menuHandle) ), 
              items_(this)
        {
            if ( handle_ )
            {
                HMENU hMenu = handle_;
                if ( hMenu )
                {
                    AddToMenuMap( hMenu, this );
                }
            }
        }
    
        ~Menu( )
        {
            if ( handle_ )
            {
                HMENU hMenu = handle_;
                if ( hMenu )
                {
                    RemoveFromMenuMap( hMenu );
                }
            }
        }

        Menu( const Menu& other ) = delete;
        Menu( Menu&& other ) = delete;
        Menu& operator = ( const Menu& other ) = delete;
        Menu& operator = ( Menu&& other ) = delete;


        constexpr const MenuHandle& Handle( ) const noexcept
        {
            return handle_;
        }

        constexpr const MenuItems& Items( ) const noexcept
        {
            return items_;
        }
        constexpr MenuItems& Items( ) noexcept
        {
            return items_;
        }

        const MenuItem* Item( int position ) const noexcept
        {
            return items_.Item( position );
        }
        MenuItem* Item( int position ) noexcept
        {
            return items_.Item( position );
        }

        Menu& AddStyle( DWORD style )
        {
            handle_.AddStyle( style );
            return *this;
        }

        void Add( std::unique_ptr<MenuItem>&& menuItem )
        {
            items_.Add( std::move(menuItem) );
        }
        void Remove( const MenuItem* menuItem )
        {
            items_.Remove( menuItem );
        }

        TextMenuItem* AddMenuItem( const wchar_t* text )
        {
            return items_.AddMenuItem( text );
        }

        template<typename Func>
            requires std::is_invocable_v<Func, MenuItem*>
        TextMenuItem* AddMenuItem( const wchar_t* text, Func&& func )
        {
            return items_.AddMenuItem( text, std::forward<Func>( func ) );
        }

        TextMenuItem* AddMenuItem( const WideString& text )
        {
            return items_.AddMenuItem( text );
        }

        SeparatorMenuItem* AddSeparator( )
        {
            return items_.AddSeparator( );
        }

        SubMenuItem* AddSubMenu( const wchar_t* text )
        {
            return items_.AddSubMenu( text );
        }
        SubMenuItem* AddSubMenu( const WideString& text )
        {
            return items_.AddSubMenu( text );
        }

        boost::signals2::signal<void( Message& message )> OnMenuCommand;
        boost::signals2::signal<void( Message& message )> OnInitMenu;
        boost::signals2::signal<void( Message& message )> OnInitMenuPopup;
    };

    inline MenuItems& MenuItem::ParentMenuItems( ) const
    {
        assert( parentMenu_ );
        return parentMenu_->Items( );
    }
    inline int MenuItem::IndexOf( ) const
    {
        auto& parentMenuItems = ParentMenuItems( );
        return parentMenuItems.IndexOf( this );
    }

    inline void SeparatorMenuItem::DoOnAdd( ) const
    {
        auto menu = ParentMenu( );
        if ( menu )
        {
            menu->Handle( ).Append( MF_SEPARATOR );
        }
    }

    inline Menu& SubMenuItem::Menu( ) const
    {
        if ( !menu_ )
        {
            auto hMenu = ::CreatePopupMenu( );
            if ( !hMenu )
            {
                ThrowLastOSError( );
            }
            MenuHandle menuHandle( hMenu, true );

            menu_ = std::make_unique<Windows::Menu>( std::move( menuHandle ) );
            menu_->AddStyle( MNS_NOTIFYBYPOS );
        }
        return *menu_;
    }

    inline const MenuItems& SubMenuItem::Items( ) const
    {
        auto& menu = Menu( );
        return menu.Items( );
    }
    inline MenuItems& SubMenuItem::Items( )
    {
        auto& menu = Menu( );
        return menu.Items( );
    }

    inline void SubMenuItem::Add( std::unique_ptr<MenuItem>&& menuItem )
    {
        auto& menu = Menu( );
        menu.Add( std::move( menuItem ) );
    }
    inline void SubMenuItem::Remove( const MenuItem* menuItem )
    {
        auto& menu = Menu( );
        menu.Remove( menuItem  );
    }

    inline TextMenuItem* SubMenuItem::AddMenuItem( const wchar_t* text )
    {
        auto& menu = Menu( );
        return menu.AddMenuItem( text );
    }
    template<typename Func>
        requires std::is_invocable_v<Func, MenuItem*>
    inline TextMenuItem* SubMenuItem::AddMenuItem( const wchar_t* text, Func&& func )
    {
        auto& menu = Menu( );
        return menu.AddMenuItem( text, std::forward<Func>(func));
    }

    inline TextMenuItem* SubMenuItem::AddMenuItem( const WideString& text )
    {
        auto& menu = Menu( );
        return menu.AddMenuItem( text );
    }

    inline SeparatorMenuItem* SubMenuItem::AddSeparator( )
    {
        auto& menu = Menu( );
        return menu.AddSeparator( );
    }

    inline SubMenuItem* SubMenuItem::AddSubMenu( const wchar_t* text )
    {
        auto& menu = Menu( );
        return menu.AddSubMenu( text );
    }
    inline SubMenuItem* SubMenuItem::AddSubMenu( const WideString& text )
    {
        auto& menu = Menu( );
        return menu.AddSubMenu( text );
    }

    inline void SubMenuItem::InitializeMenuItemInfo( MENUITEMINFOW& info ) const
    {
        Base::InitializeMenuItemInfo( info );

        info.fMask |= MIIM_STRING;
        info.cch = static_cast<UINT>(text_.length( ));
        info.dwTypeData = const_cast<LPWSTR>(text_.c_str( ));

        auto& menu = Menu( );
        info.fMask |= MIIM_SUBMENU;
        info.hSubMenu = menu.Handle( );
    }



    class MenuBar : public Menu
    {
        static MenuHandle CreateHandle( )
        {
            HMENU hMenu = ::CreateMenu( );
            if ( !hMenu )
            {
                ThrowLastOSError( );
            }
            MenuHandle result( hMenu, true );
            return result;
        }
    public:
        using Base = Menu;

        MenuBar( )
            : Base( CreateHandle( ) )
        {
            AddStyle( MNS_NOTIFYBYPOS );
        }
    };

    enum class PopupMenuAlignment : int
    {
        Left = 0x0000,
        Center = 0x0004,
        Right = 0x0008,
        Top = 0x0000,
        VerticalCenter = 0x0010,
        Bottom = 0x0020
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( PopupMenuAlignment, int );


    class PopupMenu : public Menu
    {
        static MenuHandle CreateHandle( )
        {
            HMENU hMenu = ::CreatePopupMenu( );
            if ( !hMenu )
            {
                ThrowLastOSError( );
            }
            MenuHandle result( hMenu, true );
            return result;
        }
        PopupMenuAlignment alignment_;
        static PopupMenuAlignment GetDefaultAlignment( )
        {
            if ( ::GetSystemMetrics( SM_MENUDROPALIGNMENT ) )
            {
                return PopupMenuAlignment::Right | PopupMenuAlignment::Top;
            }
            else
            {
                return PopupMenuAlignment::Left | PopupMenuAlignment::Top;
            }
        }
    public:
        typedef Menu Base;

        PopupMenu( )
            : Base( CreateHandle( ) ),
              alignment_( GetDefaultAlignment( ) )
        {
            AddStyle( MNS_NOTIFYBYPOS );
        }


        constexpr PopupMenuAlignment Alignment( ) const noexcept
        {
            return alignment_;
        }
        PopupMenu& SetAlignment( PopupMenuAlignment alignment )
        {
            if ( alignment_ != alignment )
            {
                alignment_ = alignment;
            }
            return *this;
        }

        PopupMenu& Show( const Control& control, const POINT& screenPosition );
        PopupMenu& Show( const Control& control, const POINT& screenPosition, const RECT& excludeArea );


    };


}

#endif

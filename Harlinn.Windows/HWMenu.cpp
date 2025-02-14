/*
   Copyright 2024-2025 Espen Harlinn

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
#include <HWMenu.h>
#include "HWControl.h"

// ----------------------------------------------------------------------
// MenuItem
// ----------------------------------------------------------------------
namespace Harlinn::Windows
{
    void MenuItem::DoOnAdd( ) const
    {
        auto menu = ParentMenu( );
        if ( menu )
        {
            MENUITEMINFOW info;
            this->InitializeMenuItemInfo( info );

            auto index = IndexOf( );

            menu->Handle( ).InsertItem( static_cast<UINT>(index), true, info );
        }
    }

    void MenuItem::DoOnRemove( ) const
    {
        auto menu = ParentMenu( );
        if ( menu )
        {
            auto index = IndexOf( );
            if ( index >= 0 )
            {
                auto& handle = menu->Handle( );
                if ( handle.IsMenu( ) )
                {
                    handle.Remove( index, MF_BYPOSITION );
                }
            }
        }
    }


    void MenuItem::InitializeMenuItemInfo( MENUITEMINFOW& info ) const
    {
        memset( &info, 0, sizeof( MENUITEMINFOW ) );
        info.cbSize = sizeof( MENUITEMINFOW );
        info.fMask |= MIIM_DATA | MIIM_STATE | MIIM_FTYPE;
        info.dwItemData = (ULONG_PTR)this;

        if ( bitmap_ )
        {
            info.fMask |= MIIM_BITMAP;
            info.hbmpItem = bitmap_;
        }
        if ( checkedBitmap_ )
        {
            info.fMask |= MIIM_CHECKMARKS;
            info.hbmpChecked = checkedBitmap_;
        }
        if ( uncheckedBitmap_ )
        {
            info.fMask |= MIIM_CHECKMARKS;
            info.hbmpUnchecked = uncheckedBitmap_;
        }
        if ( checked_ )
        {
            info.fState |= MFS_CHECKED;
        }
        if ( isDefault_ )
        {
            info.fState |= MFS_DEFAULT;
        }
        if ( disabled_ )
        {
            info.fState |= MFS_DISABLED;
        }
        if ( grayed_ )
        {
            info.fState |= MFS_GRAYED;
        }
        if ( highlighted_ )
        {
            info.fState |= MFS_HILITE;
        }
        if ( menuBarBreak_ )
        {
            info.fType |= MFT_MENUBARBREAK;
        }
        if ( menuBreak_ )
        {
            info.fType |= MFT_MENUBREAK;
        }
        if ( ownerDraw_ )
        {
            info.fType |= MFT_OWNERDRAW;
        }
    }

    void MenuItem::UpdateMenuItem( ) const
    {
        if ( parentMenu_ )
        {
            MENUITEMINFOW info;
            this->InitializeMenuItemInfo( info );
            int index = IndexOf( );
            parentMenu_->Handle( ).SetItemInfo( index, true, &info );
        }
    }

    void MenuItem::DoOnMenuCommand( Message& message )
    {
        OnClick( this );
    }

    void MenuItem::DoOnMeasureItem( MEASUREITEMSTRUCT& measureItemStruct )
    {
        OnMeasureItem( this, measureItemStruct );
    }
    void MenuItem::DoOnDrawItem( DRAWITEMSTRUCT& drawItemStruct )
    {
        OnDrawItem( this, drawItemStruct );
    }

    // ----------------------------------------------------------------------
    // Menu
    // ----------------------------------------------------------------------
    std::unordered_map<HMENU, Menu*> Menu::menuMap_;

    void Menu::AddToMenuMap( HMENU hMenu, Menu* menu )
    {
        CheckPointerNotNull( menu );
        CheckPointerNotNull( hMenu );

        auto it = menuMap_.find( hMenu );
        if ( it == menuMap_.end( ) )
        {
            menuMap_.insert( std::map<HMENU, Menu*>::value_type( hMenu, menu ) );
        }
    }
    void Menu::RemoveFromMenuMap( HMENU hMenu )
    {
        CheckPointerNotNull( hMenu );
        auto it = menuMap_.find( hMenu );

        if ( it != menuMap_.end( ) )
        {
            menuMap_.erase( it );
        }

    }
    Menu* Menu::GetFromMenuMap( HMENU hMenu )
    {
        if ( hMenu )
        {
            auto it = menuMap_.find( hMenu );

            if ( it != menuMap_.end( ) )
            {
                auto result = ( *it ).second;
                return result;
            }
        }
        return nullptr;
    }

    void Menu::DoOnInitMenu( Message& message )
    {
        OnInitMenu( message );
    }
    void Menu::DoOnInitMenuPopup( Message& message )
    {
        OnInitMenuPopup( message );
    }
    void Menu::DoOnMenuCommand( Message& message )
    {
        OnMenuCommand( message );
        if ( !message.handled )
        {
            int position = (int)message.wParam;
            auto item = Item( position );
            if ( item )
            {
                item->DoOnMenuCommand( message );
            }
        }
    }

    // ----------------------------------------------------------------------
    // PopupMenu
    // ----------------------------------------------------------------------
    PopupMenu& PopupMenu::Show( const Control& control, const POINT& screenPosition )
    {
        HMENU hMenu = this->Handle( );
        int flags = int( alignment_ );
        if ( TrackPopupMenuEx( hMenu, flags, screenPosition.x, screenPosition.y, control.GetHandle( ), nullptr ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return *this;
    }

    PopupMenu& PopupMenu::Show( const Control& control, const POINT& screenPosition, const RECT& excludeArea )
    {
        HMENU hMenu = this->Handle( );
        int flags = int( alignment_ );
        TPMPARAMS tpmparams = { 0, };
        tpmparams.cbSize = sizeof( TPMPARAMS );
        tpmparams.rcExclude = excludeArea;
        if ( TrackPopupMenuEx( hMenu, flags, screenPosition.x, screenPosition.y, control.GetHandle( ), &tpmparams ) == FALSE )
        {
            ThrowLastOSError( );
        }
        return *this;
    }



}
#pragma once
#ifndef __HWFORM_H__
#define __HWFORM_H__

#include <HWContainerControl.h>
#include <HWMenu.h>

namespace Harlinn::Windows
{
    // --------------------------------------------------------------------
    // Form
    // --------------------------------------------------------------------
    class MenuBar;
    class Form : public ContainerControl
    {
        bool shown_;
        std::unique_ptr<MenuBar> menuBar_;
    private:

    public:
        typedef ContainerControl Base;

        Form( )
            : Base( ),
              shown_( false )
        {
        }

    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;
    public:
        HW_EXPORT virtual DWORD GetStyle( ) const;

        HW_EXPORT virtual void HandleMessage( Message& message );

        HW_EXPORT Form& Close( );

        HW_EXPORT Form& DrawMenuBar( );

        MenuBar* Menu( ) const
        {
            return menuBar_.get( );
        }
        HW_EXPORT Form& SetMenu( std::unique_ptr<MenuBar>&& menuBar );

        HW_EXPORT Form& GetMenuBarInfo( LONG idObject, LONG idItem, PMENUBARINFO pmbi );
        HW_EXPORT Form& GetMenuBarInfo( LONG idObject, LONG idItem, MENUBARINFO& pmbi );
        HW_EXPORT MENUBARINFO GetMenuBarInfo( LONG idObject, LONG idItem );

        boost::signals2::signal<void( Form* form, Message& message )> OnActivate;
        boost::signals2::signal<void( Form* form, Message& message )> OnActivateApp;
        boost::signals2::signal<void( Form* form, Message& message )> OnDevModeChange;
        boost::signals2::signal<void( Form* form, Message& message )> OnEndSession;
        boost::signals2::signal<void( Form* form, Message& message )> OnFontChange;
        boost::signals2::signal<void( Form* form, Message& message )> OnGetMinMaxInfo;
        boost::signals2::signal<void( Form* form, Message& message )> OnIconEraseBackground;
        boost::signals2::signal<void( Form* form, Message& message )> OnMouseActivate;
        boost::signals2::signal<void( Form* form, Message& message )> OnPaintIcon;
        boost::signals2::signal<void( Form* form, Message& message )> OnPowerBroadcast;
        boost::signals2::signal<void( Form* form, Message& message )> OnQueryDragIcon;
        boost::signals2::signal<void( Form* form, Message& message )> OnQueryEndSession;
        boost::signals2::signal<void( Form* form, Message& message )> OnQueryOpen;
        boost::signals2::signal<void( Form* form, Message& message )> OnSettingChange;
        boost::signals2::signal<void( Form* form )> OnShown;
        boost::signals2::signal<void( Form* form, Message& message )> OnTimeChange;
    protected:
        HW_EXPORT virtual void DoOnHandleCreated( );


        HW_EXPORT virtual void DoOnActivate( Message& message );
        HW_EXPORT virtual void DoOnActivateApp( Message& message );
        HW_EXPORT virtual void DoOnDevModeChange( Message& message );
        HW_EXPORT virtual void DoOnEndSession( Message& message );
        HW_EXPORT virtual void DoOnFontChange( Message& message );
        HW_EXPORT virtual void DoOnGetMinMaxInfo( Message& message );
        HW_EXPORT virtual void DoOnIconEraseBackground( Message& message );
        HW_EXPORT virtual void DoOnMouseActivate( Message& message );
        HW_EXPORT virtual void DoOnPaintIcon( Message& message );
        HW_EXPORT virtual void DoOnPowerBroadcast( Message& message );
        HW_EXPORT virtual void DoOnQueryDragIcon( Message& message );
        HW_EXPORT virtual void DoOnQueryEndSession( Message& message );
        HW_EXPORT virtual void DoOnQueryOpen( Message& message );
        HW_EXPORT virtual void DoOnSettingChange( Message& message );
        HW_EXPORT virtual void DoOnShown( );
        HW_EXPORT virtual void DoOnShowWindow( Message& message );
        HW_EXPORT virtual void DoOnTimeChange( Message& message );


    };

}

#endif

#pragma once
#ifndef __HWAPPLICATION_H__
#define __HWAPPLICATION_H__

#include <HWMessage.h>
#include <HWForm.h>
#include <HWWindowClass.h>
#include <HWApplicationOptions.h>
#include <HCCApplication.h>

namespace Harlinn::Windows
{
    class MessageLoop
    {
    public:
        HW_EXPORT MessageLoop( );
        HW_EXPORT virtual ~MessageLoop( );

        HW_EXPORT virtual int Run( );
    protected:
        HW_EXPORT virtual int GetMessage( Message& message );
        HW_EXPORT virtual int TranslateMessage( Message& message );
        HW_EXPORT virtual Message::Result DispatchMessage( const Message& message );
    };

    class Application : public Common::Core::Application
    {
        friend class Control;

        static Application* currentApplication_;

        WindowClasses windowClasses_;

        std::unordered_map<HWND, Control*> controls_;

        HW_EXPORT void AddControl( HWND hWnd, Control* control );
        HW_EXPORT void RemoveControl( HWND hWnd );
        HW_EXPORT Control* GetControl( HWND hWnd );

    public:
        using Base = Common::Core::Application;
        HW_EXPORT Application( const std::shared_ptr<Windows::ApplicationOptions>& options, COINIT comInitalizationFlags = COINIT::COINIT_APARTMENTTHREADED );
        HW_EXPORT Application( );
        HW_EXPORT virtual ~Application( );

        HW_EXPORT static Application* Current( );

        HW_EXPORT virtual int Run( Form& mainform );
        HW_EXPORT int Run( const std::unique_ptr<Form>& mainform );

        HW_EXPORT virtual int Run( Form& mainform, MessageLoop& messageLoop );

        template<typename FormT>
            requires std::is_base_of_v<Form, FormT>
        int Run( )
        {
            auto form = make_control<FormT>( );
            auto result = this->Run( *form );
            return result;
        }


        HW_EXPORT const WindowClasses& GetWindowClasses( ) const;
        HW_EXPORT WindowClasses& GetWindowClasses( );
        HW_EXPORT static WindowClass* GetWindowClass( const WideString& className );
        HW_EXPORT static WindowClass* GetWindowClass( const wchar_t* className );

        static void RegisterWindowClass( std::unique_ptr<WindowClass>&& windowClass )
        {
            auto currentApplication = Current( );
            if ( currentApplication )
            {
                auto& windowClasses = currentApplication->GetWindowClasses( );
                windowClasses.Register( std::move( windowClass ) );
            }
        }

    };

}

#endif

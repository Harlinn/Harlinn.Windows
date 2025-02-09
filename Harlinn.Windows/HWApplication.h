#pragma once
#ifndef __HWAPPLICATION_H__
#define __HWAPPLICATION_H__
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

#include <HWMessage.h>
#include <HWForm.h>
#include <HWWindowClass.h>
#include <HWApplicationOptions.h>
#include <HCCApplication.h>

namespace Harlinn::Windows
{
    /// <summary>
    /// The standard message loop
    /// </summary>
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

    /// <summary>
    /// <para>
    /// A message loop based on PeekMessage
    /// that fires the OnIdle event when there
    /// are no messages in the message queue.
    /// </para>
    /// <para>
    /// This message loop is suitable for implementing
    /// a render loop in a 3D application.
    /// </para>
    /// </summary>
    class PeekMessageLoop : public MessageLoop
    {
    public:
        boost::signals2::signal<void( PeekMessageLoop* sender )> OnIdle;

        HW_EXPORT PeekMessageLoop( );
        HW_EXPORT virtual ~PeekMessageLoop( );
        HW_EXPORT virtual int Run( );
    protected:
        HW_EXPORT virtual int GetMessage( Message& message );
        HW_EXPORT virtual void DoOnIdle( );
    };


    class Application : public Common::Core::Application
    {
        friend class Control;

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

        static Application& Instance( )
        {
            return static_cast< Application& >( Base::Instance( ) );
        }

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
            auto& currentApplication = Instance( );
            auto& windowClasses = currentApplication.GetWindowClasses( );
            windowClasses.Register( std::move( windowClass ) );
        }

    };

}

#endif

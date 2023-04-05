#pragma once
#ifndef HARLINN_WINDOWS_HWIMGUI_H_
#define HARLINN_WINDOWS_HWIMGUI_H_

#include "HWForm.h"
#include "HWDXApplication.h"

#include "imgui.h"
#include "implot.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx12.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

namespace Harlinn::Windows::ImGui
{
    class Form;
    class Application : public DXApplication
    {
        friend class Form;
        ImGuiIO& io_;
    private:
        static ImGuiIO& GetImGuiIO( )
        {
            ::ImGui::CreateContext( );
            ::ImPlot::CreateContext( );
            return ::ImGui::GetIO( );
        }
    public:
        using Base = DXApplication;
        Application( const Windows::ApplicationOptions& options, std::unique_ptr<DXContext> dxContext = std::make_unique<DXContext>( ) )
            : Base( options, std::move( dxContext ) ), io_( GetImGuiIO( ) )
        {
            io_.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io_.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io_.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
            //::ImGui::StyleColorsDark( );
            //::ImGui::StyleColorsLight( );
            ::ImGui::StyleColorsClassic( );
        }
        virtual ~Application( )
        {
            ImGui_ImplDX12_Shutdown( );
            ImGui_ImplWin32_Shutdown( );
            ::ImPlot::DestroyContext( );
            ::ImGui::DestroyContext( );
        }

        using Base::Run;
        virtual int Run( Windows::Form& mainform, DXMessageLoop& messageLoop ) override
        {
            auto context = Context( );

            context->CreateDeviceD3D( mainform.GetHandle( ) );

            ImGuiStyle& style = ::ImGui::GetStyle( );
            if ( io_.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
            {
                style.WindowRounding = 0.0f;
                style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            }
            style.AntiAliasedFill = true;
            style.AntiAliasedLines = true;

            auto& srvDescHeap = context->SrvDescHeap( );
            ImGui_ImplWin32_Init( mainform.GetHandle( ) );
            ImGui_ImplDX12_Init( static_cast<ID3D12Device*>(context->Device().GetInterfacePointer()), 
                            DXContext::FRAMES_IN_FLIGHT_COUNT, 
                            DXGI_FORMAT_R8G8B8A8_UNORM, 
                            static_cast<ID3D12DescriptorHeap*>(srvDescHeap.GetInterfacePointer()), 
                            srvDescHeap.GetCPUDescriptorHandleForHeapStart( ), 
                            srvDescHeap.GetGPUDescriptorHandleForHeapStart( ) );

            auto result = Base::Run( mainform, messageLoop );
            return result;
        }
    };


    class Form : public Windows::Form
    {
    public:
        using Base = Windows::Form;
        boost::signals2::signal<void( Form* sender )> OnRender;
    private:
        bool attached_ = false;
        boost::signals2::connection onRenderConnection_;

    protected:
        virtual void HandleMessage( Message& message ) override
        {
            if ( !attached_ )
            {
                auto messageLoop = DXMessageLoop::Instance( );
                if ( messageLoop )
                {
                    messageLoop->OnRender.connect( [this]( DXMessageLoop* sender ) 
                    {
                        this->DoOnRenderFrame( );
                    } );
                    attached_ = true;
                }
            }
            if ( ImGui_ImplWin32_WndProcHandler( message.hwnd, message.message, message.wParam, message.lParam ) )
            {
                message.handled = true;
            }
            else
            {
                if ( message.message == WM_SIZE )
                {
                    auto& application = DXApplication::Instance( );
                    auto context = application.Context( );
                    context->WaitForLastSubmittedFrame( );
                    ImGui_ImplDX12_InvalidateDeviceObjects( );
                    context->CleanupRenderTarget( );
                    context->ResizeSwapChain( message.hwnd, (UINT)LOWORD( message.lParam ), (UINT)HIWORD( message.lParam ) );
                    context->CreateRenderTarget( );
                    ImGui_ImplDX12_CreateDeviceObjects( );
                }
                Base::HandleMessage( message );
            }
        }

        virtual void DoOnNewFrame( )
        {
            ImGui_ImplDX12_NewFrame( );
            ImGui_ImplWin32_NewFrame( );
            ::ImGui::NewFrame( );
        }

        virtual void DoOnFrameDone( )
        {
            auto& application = static_cast<Application&>(DXApplication::Instance( ));
            auto context = application.Context( );
            if ( context )
            {
                ::ImGui::Render( );

                context->PrepareFrame( );
                context->PrepareCommandList( );

                ID3D12GraphicsCommandList* commandList = static_cast<ID3D12GraphicsCommandList*>( context->CommandList( ).GetInterfacePointer( ) );

                ImGui_ImplDX12_RenderDrawData( ::ImGui::GetDrawData( ), commandList );

                context->CloseCommandList( );

                context->ExecuteCommandList( );

                // Update and Render additional Platform Windows
                if ( application.io_.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
                {
                    ::ImGui::UpdatePlatformWindows( );
                    ::ImGui::RenderPlatformWindowsDefault( NULL, (void*)commandList );
                }

                context->Present( );
                context->FrameCompleted( );
            }
        }



    public:
        virtual void DoOnRenderFrame( )
        {
            this->DoOnNewFrame( );
            this->DoOnRender( );
            this->DoOnFrameDone( );
        }
        virtual void DoOnRender( )
        {
            OnRender( this );
        }


    };
}

#endif

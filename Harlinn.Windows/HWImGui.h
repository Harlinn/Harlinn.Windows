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
        Application( const std::shared_ptr<Windows::ApplicationOptions>& options, std::unique_ptr<DXContext> dxContext = std::make_unique<DXContext>( ) )
            : Base( options, std::move( dxContext ) ), io_( GetImGuiIO( ) )
        {
            io_.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            ::ImGui::StyleColorsClassic( );
        }

        Application( std::unique_ptr<DXContext> dxContext = std::make_unique<DXContext>( ) )
            : Application( Windows::ApplicationOptions::LoadFromFile<Windows::ApplicationOptions>(), std::move( dxContext ) )
        { }

        virtual ~Application( )
        {
            ImGui_ImplDX12_Shutdown( );
            ImGui_ImplWin32_Shutdown( );
            ::ImPlot::DestroyContext( );
            ::ImGui::DestroyContext( );
        }

        using Base::Run;
        virtual int Run( Windows::Form& mainForm, DXMessageLoop& messageLoop ) override
        {
            auto context = Context( );

            ImGuiStyle& style = ::ImGui::GetStyle( );
            style.AntiAliasedFill = true;
            style.AntiAliasedLines = true;

            auto& shaderResourceViewDescHeap = context->ShaderResourceViewDescHeap( );
            ImGui_ImplWin32_Init( mainForm.GetHandle( ) );
            ImGui_ImplDX12_Init( static_cast<ID3D12Device*>(context->Device().GetInterfacePointer()), 
                            DXContext::FRAMES_IN_FLIGHT_COUNT, 
                            DXGI_FORMAT_R8G8B8A8_UNORM, 
                            static_cast<ID3D12DescriptorHeap*>( shaderResourceViewDescHeap.GetInterfacePointer()),
                            shaderResourceViewDescHeap.GetCPUDescriptorHandleForHeapStart( ),
                            shaderResourceViewDescHeap.GetGPUDescriptorHandleForHeapStart( ) );

            auto result = Base::Run( mainForm, messageLoop );
            return result;
        }
    };


    class Form : public Windows::DXForm
    {
    public:
        using Base = Windows::DXForm;
    private:
    protected:
        virtual void HandleMessage( Message& message ) override
        {
            if ( ImGui_ImplWin32_WndProcHandler( message.hwnd, message.message, message.wParam, message.lParam ) )
            {
                message.handled = true;
            }
            else
            {
                Base::HandleMessage( message );
            }
        }

        virtual void DoOnNewFrame( ) override
        {
            ImGui_ImplDX12_NewFrame( );
            ImGui_ImplWin32_NewFrame( );
            ::ImGui::NewFrame( );
            Base::DoOnNewFrame( );
        }

        virtual void DoOnFrameDone( ) override
        {
            auto& application = static_cast<Application&>(DXApplication::Instance( ));
            auto context = application.Context( );
            if ( context )
            {
                ::ImGui::Render( );
                ID3D12GraphicsCommandList* commandList = static_cast<ID3D12GraphicsCommandList*>( context->CommandList( ).GetInterfacePointer( ) );
                ImGui_ImplDX12_RenderDrawData( ::ImGui::GetDrawData( ), commandList );
            }
            Base::DoOnFrameDone( );
        }

        virtual void DoOnInvalidateDeviceObjects( DXContext* context ) override
        {
            ImGui_ImplDX12_InvalidateDeviceObjects( );
        }

        virtual void DoOnCreateDeviceObjects( DXContext* context ) override
        {
            ImGui_ImplDX12_CreateDeviceObjects( );
        }
    };
}

#endif

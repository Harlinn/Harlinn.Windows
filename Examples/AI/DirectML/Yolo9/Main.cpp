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

//--------------------------------------------------------------------------------------
// Main.cpp
//
// Entry point for Windows desktop application.
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------

#include "pch.h"

#include "yolo9.h"

#include "FileDialog.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );


class MyForm : public Harlinn::Windows::Form
{
    std::unique_ptr<Sample> sample_;

    bool in_sizemove_ = false;
    bool in_suspend_ = false;
    bool minimized_ = false;
    bool fullscreen_ = false;
public:
    using Base = Harlinn::Windows::Form;

    MyForm( )
        : Base( )
    {
        sample_ = std::make_unique<Sample>( );
    }

    void OnIdle( )
    {
        sample_->Tick( );
    }

    virtual void DoOnHandleCreated() override
    {
        Base::DoOnHandleCreated( );
        
        auto run_on_gpu = false;

        auto rect = GetClientRect( );

        sample_->Initialize( GetHandle( ), rect.right - rect.left, rect.bottom - rect.top, run_on_gpu );
            
    }

    virtual void HandleMessage( Message& message ) override
    {
        
        
        if ( ImGui_ImplWin32_WndProcHandler( message.hwnd, message.message, message.wParam, message.lParam ) )
        {
            message.handled = true;
        }

        switch ( message.message )
        {
            case WM_PAINT:
                if ( in_sizemove_ && sample_ )
                {
                    sample_->Tick( );
                }
                else
                {
                    PAINTSTRUCT ps;
                    HDC hdc;
                    hdc = BeginPaint( ps );
                    EndPaint( ps );
                }
                break;

            case WM_MOVE:
                if ( sample_ )
                {
                    sample_->OnWindowMoved( );
                }
                break;

            case WM_SIZE:
                if ( message.wParam == SIZE_MINIMIZED )
                {
                    if ( !minimized_ )
                    {
                        minimized_ = true;
                        if ( !in_suspend_ && sample_ )
                        {
                            sample_->OnSuspending( );
                        }
                        in_suspend_ = true;
                    }
                }
                else if ( minimized_ )
                {
                    minimized_ = false;
                    if ( in_suspend_ && sample_ )
                    {
                        sample_->OnResuming( );
                    }
                    in_suspend_ = false;
                }
                else if ( !in_sizemove_ && sample_ )
                {
                    sample_->OnWindowSizeChanged( LOWORD( message.lParam ), HIWORD( message.lParam ) );
                }
                break;

            case WM_ENTERSIZEMOVE:
                in_sizemove_ = true;
                break;

            case WM_EXITSIZEMOVE:
                in_sizemove_ = false;
                if ( sample_ )
                {
                    RECT rc;
                    GetClientRect( &rc );

                    sample_->OnWindowSizeChanged( rc.right - rc.left, rc.bottom - rc.top );
                }
                break;

            case WM_GETMINMAXINFO:
            {
                auto info = reinterpret_cast< MINMAXINFO* >( message.lParam );
                info->ptMinTrackSize.x = 320;
                info->ptMinTrackSize.y = 200;
            }
            break;

            case WM_ACTIVATEAPP:
                if ( sample_ )
                {
                    DirectX::Keyboard::ProcessMessage( message.message, message.wParam, message.lParam );
                    DirectX::Mouse::ProcessMessage( message.message, message.wParam, message.lParam );

                    if ( message.wParam )
                    {
                        sample_->OnActivated( );
                    }
                    else
                    {
                        sample_->OnDeactivated( );
                    }
                }
                break;

            case WM_POWERBROADCAST:
                switch ( message.wParam )
                {
                    case PBT_APMQUERYSUSPEND:
                        if ( !in_suspend_ && sample_ )
                        {
                            sample_->OnSuspending( );
                        }
                        in_suspend_ = true;
                        message.result = TRUE;
                        message.handled = true;

                    case PBT_APMRESUMESUSPEND:
                        if ( !minimized_ )
                        {
                            if ( in_suspend_ && sample_ )
                            {
                                sample_->OnResuming( );
                            }
                            in_suspend_ = false;
                        }
                        message.result = TRUE;
                        message.handled = true;
                }
                break;

            case WM_DESTROY:
                PostQuitMessage( 0 );
                break;

            case WM_LBUTTONDBLCLK:
            {
                volatile int a = 0;
                break;
            }
            case WM_INPUT:
            case WM_MOUSEMOVE:
            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_RBUTTONDOWN:
                DirectX::Mouse::ProcessMessage( message.message, message.wParam, message.lParam );
                break;
            case WM_RBUTTONUP:
            case WM_CONTEXTMENU:
            {
                RECT rect;
                POINT p = { GET_X_LPARAM( message.lParam ) , GET_Y_LPARAM( message.lParam ) };
                //ScreenToClient(hWnd, &p);
                GetClientRect( &rect );

                std::wstring title = L"Open Video file";
                std::wstring filename;
                bool bVideo = true;

                // where did I click?
                bool bAddModel = false;
                if ( p.y > rect.top + ( ( rect.bottom - rect.top ) * 9 / 10 ) )
                {
                    bVideo = false;
                    if ( ( GetAsyncKeyState( VK_CONTROL ) & 0x8000 ) != 0 )
                    {
                        title = L"Add ONNX model";
                        bAddModel = true;
                    }
                    else
                        title = L"Open ONNX model";
                }

                auto hr = FileOpen( title, filename, bVideo, bAddModel );
                if ( hr == S_OK )

                    //if (GetOpenFileName(&ofn) == TRUE)
                {
                    //
                    // use ofn.lpstrFile

                    if ( !bVideo )
                    {
                        sample_->OnNewModel( filename.c_str( ), bAddModel );
                    }
                    else
                    {
                        sample_->OnNewFile( filename.c_str( ) );
                    }
                }
                else
                {
                    sample_->m_player->Skip( -5 );

                }
                message.result = 1;
                message.handled = true;
                break;
            }
            case WM_MBUTTONDOWN:
            case WM_MBUTTONUP:
            case WM_MOUSEWHEEL:
            case WM_XBUTTONDOWN:
            case WM_XBUTTONUP:
            case WM_MOUSEHOVER:
                DirectX::Mouse::ProcessMessage( message.message, message.wParam, message.lParam );
                break;

            case WM_KEYDOWN:
            case WM_KEYUP:
            case WM_SYSKEYUP:
                DirectX::Keyboard::ProcessMessage( message.message, message.wParam, message.lParam );
                break;

            case WM_SYSKEYDOWN:
                if ( message.wParam == VK_RETURN && ( message.lParam & 0x60000000 ) == 0x20000000 )
                {
                    // Implements the classic ALT+ENTER fullscreen toggle
                    if ( fullscreen_ )
                    {
                        SetWindowLongPtr( GetHandle(), GWL_STYLE, WS_OVERLAPPEDWINDOW );
                        SetWindowLongPtr( GetHandle( ), GWL_EXSTYLE, 0 );

                        int width = 800;
                        int height = 600;
                        if ( sample_ )
                            sample_->GetDefaultSize( width, height );

                        ShowWindow( GetHandle( ), SW_SHOWNORMAL );

                        SetWindowPos( GetHandle( ), HWND_TOP, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED );
                    }
                    else
                    {
                        SetWindowLongPtr( GetHandle( ), GWL_STYLE, 0 );
                        SetWindowLongPtr( GetHandle( ), GWL_EXSTYLE, WS_EX_TOPMOST );

                        SetWindowPos( GetHandle( ), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );

                        ShowWindow( GetHandle( ), SW_SHOWMAXIMIZED );
                    }

                    fullscreen_ = !fullscreen_;
                }
                DirectX::Keyboard::ProcessMessage( message.message, message.wParam, message.lParam );
                break;

            case WM_MENUCHAR:
                // A menu is active and the user presses a key that does not correspond
                // to any mnemonic or accelerator key. Ignore so we don't produce an error beep.
                message.result = MAKELRESULT( 0, MNC_CLOSE );
                message.handled = true;
        }
        if ( !message.handled )
        {
            Base::HandleMessage( message );
        }
    }
};


// Indicates to hybrid graphics systems to prefer the discrete part by default
extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}



int main( int argc, char* argv [] )
{
    try
    {
        auto application = std::make_shared<Harlinn::Windows::Application>( );
        application->Start( );

        Media::MediaFoundation mediaFoundation;

        MyForm form;
        form.SetText( L"Yolo v9 Object Detection" );

        PeekMessageLoop messageLoop;

        messageLoop.OnIdle.connect( [ &form ]( auto* sender )
            {
                form.OnIdle( );
            } );

        auto result = application->Run( form, messageLoop );

        application->Stop( );

        return result;
    }
    catch ( std::exception& exc )
    {
        std::cout << exc.what( ) << std::endl;
    }
    catch ( ... )
    {
        std::cout << "Unknown exception" << std::endl;
    }
    return 0;
}



// Exit helper
void ExitSample()
{
    PostQuitMessage(0);
}

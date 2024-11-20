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


// EWMFCameraViewer1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Viewer.h"

#include <HWApplication.h>
#include "HWForm.h"
#include "HWMenu.h"

#include <iostream>

class MyForm : public Form
{
    Com::HeapObject<Viewer>* player_ = nullptr;
public:
    using Base = Form;
    MyForm()
    {
    }
protected:
    virtual void DoOnInitialize();
    virtual void DoOnHandleCreated();
    virtual void DoBeforeHandleDestroy();
    virtual void DoOnSize(Message& message) override;

    virtual void DoOnPaint(Message& message);
private:
    void InitializeMenuBar();
    void OnOpenFile();
    void OnRTSP( );
    void OnCamera( );
};

void MyForm::DoOnInitialize()
{
    InitializeMenuBar();
}

void MyForm::InitializeMenuBar()
{
    auto menuBar = std::make_unique<MenuBar>();

    auto fileSubMenu = menuBar->AddSubMenu(L"&File");

    fileSubMenu->AddMenuItem(L"Open", [&](MenuItem* sender)
        {
            OnOpenFile();
        });
    fileSubMenu->AddMenuItem( L"RTSP", [ & ]( MenuItem* sender )
        {
            OnRTSP( );
        } );
    fileSubMenu->AddMenuItem( L"Camera", [ & ]( MenuItem* sender )
        {
            OnCamera( );
        } );

    SetMenu(std::move(menuBar));
}

void MyForm::DoOnHandleCreated()
{
    Base::DoOnHandleCreated();
    auto windowHandle = GetHandle();
    player_ = new Com::HeapObject<Viewer>(windowHandle);
}
void MyForm::DoBeforeHandleDestroy()
{
    if (player_)
    {
        player_->Close();
        player_->Release();
        player_ = nullptr;
    }
    Base::DoBeforeHandleDestroy();
}


void MyForm::DoOnSize(Message& message)
{
    Base::DoOnSize(message);
    auto size = Size();

    if (player_)
    {
        player_->Resize(size);
    }

}


void MyForm::DoOnPaint(Message& message)
{
    Base::DoOnPaint(message);
    PaintDeviceContextHandle dc(*this);

    if (player_ && player_->HasVideo())
    {
        // We have a player with an active topology and a video renderer that can paint the
        // window surface - ask the videor renderer (through the player) to redraw the surface.
        player_->Repaint();
    }
    else
    {
        // The player topology hasn't been activated, which means there is no video renderer that 
        // repaint the surface.  This means we must do it ourselves.
        RECT rect = this->GetClientRect();
        BrushHandle controlBrush(SysColor::Control);
        dc.DrawFilledRectangle(rect, controlBrush);

    }
}

void MyForm::OnOpenFile()
{
    // common dialog box structure
    static OPENFILENAMEW ofn{};
    // buffer for file name
    static WCHAR  szFile[260];

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = GetHandle();
    ofn.lpstrFile = szFile;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = '\0\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"WMV\0*.wmv\0ASF\0*.asf\0AVI\0*.avi\0All\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    //ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box. 

    if (GetOpenFileNameW(&ofn) == TRUE)
    {
        if (player_ != nullptr)
        {
            player_->OpenURL(ofn.lpstrFile);
        }
    }
}


void MyForm::OnRTSP( )
{
    if ( player_ != nullptr )
    {
        player_->OpenURL( L"rtsp://127.0.0.1:39000/Camera" );
    }
}

void MyForm::OnCamera( )
{
    if ( player_ != nullptr )
    {
        player_->OpenURL( L"" );
    }
}


int main()
{
    try
    {
        auto application = std::make_shared<Harlinn::Windows::Application>();
        application->Start();

        SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
        // Initialization/Shutdown of the Media Foundation platform
        MediaFoundation mediaFoundation;

        auto result = application->Run<MyForm>();
        application->Stop();
        return result;
    }
    catch (std::exception& exc)
    {
        std::cout << exc.what() << std::endl;
    }
    catch (...)
    {

    }
    return 0;
}

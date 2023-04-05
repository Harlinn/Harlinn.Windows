// EWMFPlayer1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Player.h"

#include <HWApplication.h>
#include "HWForm.h"
#include "HWMenu.h"

#include <iostream>

class MyForm : public Form
{
    Player* player_ = nullptr;
public:
    using Base = Form;
    MyForm()
    { }
protected:
    virtual void DoOnInitialize();
    virtual void DoOnHandleCreated();
    virtual void DoBeforeHandleDestroy();
    virtual void DoOnSize(Message& message) override;
    
    virtual void DoOnPaint(Message& message);
private:
    void InitializeMenuBar();
    void OnOpenFile();
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

    SetMenu(std::move(menuBar));
}

void MyForm::DoOnHandleCreated()
{
    Base::DoOnHandleCreated();
    auto windowHandle = GetHandle();
    player_ = new Player(windowHandle);
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

    if (player_ )
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
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box. 

    if (GetOpenFileNameW(&ofn) == TRUE)
    {
        if (player_ != nullptr)
        {
            player_->OpenURL(ofn.lpstrFile);
        }
    }
}


int main()
{
    try
    {
        Harlinn::Windows::ApplicationOptions applicationOptions;
        applicationOptions.Load();
        Harlinn::Windows::Application application(applicationOptions);
        application.Start();

        SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
        // Initializatio/Shutdown of the Media Foundation platform
        MF::MediaFoundation mediaFoundation;


        MyForm form;
        form.Initialize();

        auto result = application.Run(form);
        application.Stop();
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

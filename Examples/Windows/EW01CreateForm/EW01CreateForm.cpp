/*
    Copyright 2024-2026 Espen Harlinn
 
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
// EW01CreateForm.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "EW01CreateForm.h"

#include "HWApplication.h"
#include "HWform.h"
#include "HWmenu.h"
#include "HWstdctrls.h"
#include <iostream>

using namespace Harlinn::Windows;

class TextEditForm : public Form
{
    std::unique_ptr<MemoEdit> edit_;
public:
    typedef Form Base;
    TextEditForm( );
protected:
    virtual void DoOnInitialize( );
    virtual void DoOnSize( Message& message );
    virtual void DoOnShown( );
};


TextEditForm::TextEditForm( )
    : Base( )
{
    SetText( L"Text Edit example" );
    SetSize( 300, 300 );
}

void TextEditForm::DoOnInitialize( )
{
    Base::DoOnInitialize( );
    edit_ = make_control<MemoEdit>( this );
}


void TextEditForm::DoOnSize( Message& message )
{
    Harlinn::Windows::Rectangle clientRect = GetClientRect( );
    edit_->MoveWindow( 0, 0, clientRect.Width( ), clientRect.Height( ) );
}


void TextEditForm::DoOnShown( )
{
    Base::DoOnShown( );
    
    edit_->Append( L"Append" );
    edit_->AppendLine( L"AppendLine" );
    edit_->Append( L"Append" );
    edit_->AppendLine( L"AppendLine" );
    
}




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    try
    {
        auto application = std::make_shared<Harlinn::Windows::Application>();
        application->Start( );
        auto result = application->Run<TextEditForm>();
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




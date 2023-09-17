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
        Harlinn::Windows::Application application;
        application.Start( );
        auto result = application.Run<TextEditForm>();
        application.Stop( );

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




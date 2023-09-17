#include "HWDXApplication.h"
#include "CIMTool.h"
#include "HWmenu.h"
#include "HWstdctrls.h"
#include <iostream>

using namespace Harlinn;
namespace hcc = Harlinn::Common::Core;


hcc::UInt64 Harlinn::CIMTool::TreeNode::nextId_ = 0;

int main( )
{
    int result = 1;

    hcc::Com::Initialize( );
    hcc::Com::InitializeClientSecurity( );


    Windows::ImGui::Application application;
    application.Start( );

    try
    {
        Windows::ImGui::Form form;
        form.SetText( L"Harlinn CIM Tool" );

        Harlinn::CIMTool::Main mainUI;

        form.OnRender.connect( [&mainUI]( auto* sender )
        {
            mainUI.Render( );
        } );

        result = application.Run( form );
        application.Stop( );
        result = 0;
    }
    catch ( std::exception& exc )
    {
        std::cout << exc.what( ) << std::endl;
    }
    catch ( ... )
    {
        std::cout << "Unknown exception" << std::endl;
    }
    hcc::Com::Uninitialize( );
    return result;

}


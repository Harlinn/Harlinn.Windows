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


    auto application = std::make_shared<Windows::ImGui::Application>();
    application->Start( );

    try
    {
        Windows::ImGui::Form form;
        form.SetText( L"Harlinn CIM Tool" );

        Harlinn::CIMTool::Main mainUI;

        form.OnRender.connect( [&mainUI]( auto* sender )
        {
            mainUI.Render( );
        } );

        result = application->Run( form );
        application->Stop( );
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


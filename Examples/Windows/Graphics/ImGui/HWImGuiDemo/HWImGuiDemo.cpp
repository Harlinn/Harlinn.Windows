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


#include "HWDXApplication.h"
#include "HWImGui.h"
#include "HWmenu.h"
#include "HWstdctrls.h"
#include <iostream>

using namespace Harlinn;

int main()
{
    try
    {
        auto application = std::make_shared<Windows::ImGui::Application>();
        application->Start( );

        Windows::ImGui::Form form;
        form.SetText( L"ImGui & ImPlot Demo" );

        bool showImGuiDemoWindow = true;
        bool showImPlotDemoWindow = true;
        bool showAnotherWindow = false;

        form.OnRender.connect( [&showImGuiDemoWindow,&showImPlotDemoWindow, &showAnotherWindow]( Windows::DXForm* sender )
        {
            if ( showImGuiDemoWindow )
            {
                ImGui::ShowDemoWindow( &showImGuiDemoWindow );
            }
            if ( showImPlotDemoWindow )
            {
                ImPlot::ShowDemoWindow( &showImPlotDemoWindow );
            }

        } );

        auto result = application->Run( form );

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


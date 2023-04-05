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
        Windows::ApplicationOptions applicationOptions;
        applicationOptions.Load( );
        Windows::ImGui::Application application( applicationOptions );
        application.Start( );

        Windows::ImGui::Form form;
        form.SetText( L"ImGui & ImPlot Demo" );

        bool showImGuiDemoWindow = true;
        bool showImPlotDemoWindow = true;
        bool showAnotherWindow = false;

        form.OnRender.connect( [&showImGuiDemoWindow,&showImPlotDemoWindow, &showAnotherWindow]( Windows::ImGui::Form* sender )
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

        auto result = application.Run( form );

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


// EWD312HelloTriangle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <HWDXApplication.h>

using namespace Harlinn;



int main()
{
    try
    {
        Windows::DXApplication application;
        application.Start( );

        Windows::DXForm form;
        form.SetText( L"Hello Triangle Demo" );

        form.OnRender.connect( [ ]( Windows::DXForm* sender )
        {
            
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


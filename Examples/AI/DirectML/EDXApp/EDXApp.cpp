// EDXApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <HWMediaFoundation.h>

using namespace Harlinn::Windows;

int main()
{
    try
    {
        Media::Init init;

    }
    catch ( std::exception& exc )
    {
        auto message = exc.what( );
        PrintLn( "Exception caught in main: {}", message );
    }
}


#pragma once
#ifndef __JULIATESTFIXTURE_H__
#define __JULIATESTFIXTURE_H__

#include <HJulia.h>

class LocalFixture
{
public:
    LocalFixture( )
    {
        using namespace Harlinn::Common::Core;
        CoInitializeEx( nullptr, COINIT_MULTITHREADED );

    }
    ~LocalFixture( )
    {
        CoUninitialize( );
    }
};


#endif

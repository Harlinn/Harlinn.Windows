#include "pch.h"
#include "HCCVariant.h"

namespace Harlinn::Common::Core
{
    void foo1( )
    {
        Variant variant( true );
        auto value = variant.As<bool>( );
    }

    void foo2( )
    {
        PropertyVariant variant( true );
        auto boolValue = variant.As<bool>( );
        auto doubleValue = variant.As<double>( );
    }
}
#include "pch.h"
#include <HJulia.h>

namespace Harlinn::Julia
{
    void Init( )
    {
        jl_init( );
    }

    void Finalize( int status )
    {
        jl_atexit_hook( status );
    }
}
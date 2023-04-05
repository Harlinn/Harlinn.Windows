#include "pch.h"
#include <HOCIInternal.h>

namespace Harlinn::OCI
{
    void CStringBind::Reserve( size_t maxColumnSize )
    {
        auto byteCount = BytesRequired( maxColumnSize );
        if ( string_ && allocated_ != byteCount )
        {
            auto ptr = (wchar_t*)realloc( string_, byteCount );
            if ( ptr )
            {
                string_ = ptr;
            }
            else
            {
                HCC_THROW( OutOfMemoryException, L"Cannot reserve the requested amount of memory" );
            }
            allocated_ = byteCount;
        }
        else
        {
            string_ = (wchar_t*)malloc( byteCount );
            if ( !string_ )
            {
                HCC_THROW( OutOfMemoryException, L"Cannot reserve the requested amount of memory" );
            }
            allocated_ = byteCount;
        }
        memset( string_, 0, byteCount );
    }

    void CStringBind::Require( size_t maxColumnSize )
    {
        auto byteCount = BytesRequired( maxColumnSize );
        if ( allocated_ < byteCount )
        {
            Reserve( maxColumnSize );
        }
    }
}
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
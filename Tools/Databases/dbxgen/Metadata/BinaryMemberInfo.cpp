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
#include "ModelInfo.h"

namespace Harlinn::ODBC::Tool
{
    void BinaryMemberInfo::Load( const XmlElement& memberElement )
    {
        Base::Load( memberElement );
        if ( memberElement.HasAttribute( L"size" ) )
        {
            auto size = memberElement.Read<WideString>( L"size" );
            if ( size == L"unlimited" )
            {
                size_ = 0;
            }
            else if ( size.StartsWith( L"0x" ) )
            {
                size_ = Parse<UInt64>( size.data( ) + 2, 16 );
            }
            else if ( size.Length( ) > 0 )
            {
                size_ = Parse<UInt64>( size );
            }
            else
            {
                size_ = 0;
            }
            if ( size_ >= 8000 )
            {
                size_ = 0;
            }
        }
    }
}
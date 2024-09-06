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
#include "ModelInfo.h"

namespace Harlinn::ODBC::Tool
{
    void ReferenceMemberInfo::Load( const XmlElement& memberElement )
    {
        Base::Load( memberElement );
        if ( memberElement.HasAttribute( L"type" ) )
        {
            auto typeName = memberElement.Read<WideString>( L"type" );
            auto model = Model( );
            auto type = model->FindClass( typeName );
            type_ = type;
        }
    }

    void ReferenceMemberInfo::Validate( ) const
    {
        auto referencedType = ReferencedType( );
        if ( referencedType == nullptr )
        {
            auto ownerName = Owner( )->Name( );
            auto name = Name( );
            auto message = Format( L"Unknown referenced type for {}.{}.", ownerName, name );
            throw Exception( message );
        }
    }
}
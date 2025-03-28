/*
Copyright 2024-2025 Espen Harlinn

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
#include "Metadata/ModelInfo.h"

namespace Harlinn::Tools::DbXGen::Metadata
{
    void EnumMemberInfo::Load( const XmlElement& memberElement )
    {
        Base::Load( memberElement );
        if ( memberElement.HasAttribute( L"type" ) )
        {
            auto typeName = memberElement.Read<WideString>( L"type" );
            auto model = Model( );
            auto enumType = model->FindEnum( typeName );
            type_ = enumType;
        }
    }

    void EnumMemberInfo::Validate( ) const
    {
        auto enumType = EnumType( );
        if ( enumType == nullptr )
        {
            auto ownerName = Owner( )->Name( );
            auto name = Name( );
            auto message = Format( L"Unknown enum for {}.{}.", ownerName, name );
            throw Exception( message );
        }

    }
}
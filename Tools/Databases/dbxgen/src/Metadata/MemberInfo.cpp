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
    std::shared_ptr<Metadata::ModelInfo> MemberInfo::Model( ) const
    {
        auto owner = Owner( );
        if ( owner )
        {
            return owner->Owner( );
        }
        return {};
    }

    void MemberInfo::Load( const XmlElement& memberElement )
    {
        if ( memberElement.HasAttribute( L"nullable" ) )
        {
            nullable_ = memberElement.Read<bool>( L"nullable" );
        }
        if ( memberElement.HasAttribute( L"primarykey" ) )
        {
            primaryKey_ = memberElement.Read<bool>( L"primarykey" );
        }
        if ( memberElement.HasAttribute( L"displayname" ) )
        {
            displayName_ = memberElement.Read<WideString>( L"displayname" );
        }
        if ( memberElement.HasAttribute( L"description" ) )
        {
            description_ = memberElement.Read<WideString>( L"description" );
        }
    }


    void MemberInfo::Validate( ) const
    {

    }

}
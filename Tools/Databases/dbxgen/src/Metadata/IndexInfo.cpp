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

#include "Metadata/ClassInfo.h"

namespace Harlinn::Tools::DbXGen::Metadata
{
    void IndexInfo::Load( const XmlElement& indexElement )
    {
        if ( indexElement.HasAttribute( L"unique" ) )
        {
            unique_ = indexElement.Read<bool>( L"unique" );
        }
        if ( indexElement.HasAttribute( L"range" ) )
        {
            range_ = indexElement.Read<bool>( L"range" );
        }
        if ( indexElement.HasAttribute( L"fields" ) )
        {
            fieldNames_ = indexElement.Read<WideString>( L"fields" );
        }
    }

    void IndexInfo::Validate( ) const
    {
        size_t nullableFieldCount = 0;
        for ( const auto& field : fields_ )
        {
            if ( field->Nullable( ) )
            {
                nullableFieldCount++;
            }
        }
        if ( nullableFieldCount > 1 )
        {
            auto ownerName = Owner( )->Name( );
            auto name = Name( );
            auto message = Format( L"Too many nullable fields in index {}.{}.", ownerName, name );
            throw Exception( message );
        }
    }

    void IndexInfo::AfterLoad( )
    {
        std::vector<WideString> fieldNames;
        fieldNames_.Split( L';', fieldNames );
        auto classInfo = Owner( );
        for ( auto& fieldName : fieldNames )
        {
            auto memberInfo = classInfo->FindOwnPersistentMember( fieldName );
            fields_.emplace_back( memberInfo );
        }
    }
}
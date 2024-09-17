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
    std::shared_ptr<ReferenceMemberInfo> CollectionMemberInfo::ReferencingMember( ) const
    {
        auto referencingMember = referencingMember_.lock( );
        if ( referencingMember == nullptr )
        {
            auto referencingType = type_.lock( );
            if ( referencingType )
            {
                if ( referenceName_.Length( ) )
                {
                    referencingMember = std::dynamic_pointer_cast< ReferenceMemberInfo >( referencingType->FindOwnPersistentMember( referenceName_ ) );
                }
                else
                {
                    const auto& referencingTypeMembers = referencingType->OwnPersistentMembers( );
                    const auto count = referencingTypeMembers.size( );
                    for ( size_t i = 0; i < count; i++ )
                    {
                        const auto& referencingTypeMember = referencingTypeMembers[ i ];
                        auto referencingTypeMemberType = referencingTypeMember->Type( );
                        if ( referencingTypeMemberType == MemberInfoType::Reference || referencingTypeMemberType == MemberInfoType::TimeSeries )
                        {
                            auto referenceMemberInfo = std::dynamic_pointer_cast< ReferenceMemberInfo >( referencingTypeMember );
                            auto referencedType = referenceMemberInfo->ReferencedType( );
                            if ( referencedType )
                            {
                                if ( Owner( )->Id( ) == referencedType->Id( ) )
                                {
                                    referencingMember = referenceMemberInfo;
                                }
                            }
                        }
                    }
                }
                if ( referencingMember )
                {
                    referencingMember_ = referencingMember;
                }
            }
        }
        return referencingMember;
    }

    void CollectionMemberInfo::Load( const XmlElement& memberElement )
    {
        Base::Load( memberElement );
        if ( memberElement.HasAttribute( L"type" ) )
        {
            auto typeName = memberElement.Read<WideString>( L"type" );
            auto model = Model( );
            auto type = model->FindClass( typeName );
            type_ = type;
        }

        if ( memberElement.HasAttribute( L"reference" ) )
        {
            referenceName_ = memberElement.Read<WideString>( L"reference" );
        }
        if ( memberElement.HasAttribute( L"aggregated" ) )
        {
            aggregated_ = memberElement.Read<bool>( L"aggregated" );
        }
    }

    void CollectionMemberInfo::Validate( ) const
    {
        auto referencingMember = ReferencingMember( );
        if ( referencingMember == nullptr )
        {
            auto ownerName = Owner( )->Name( );
            auto name = Name( );
            auto message = Format( L"Unknown referencing member for {}.{}.", ownerName, name );
            throw Exception( message );
        }
    }

}
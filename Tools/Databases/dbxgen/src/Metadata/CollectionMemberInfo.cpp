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
    std::shared_ptr<ReferenceMemberInfo> CollectionMemberInfo::ReferencingReferenceMember( ) const
    {
        auto referencingReferenceMember = referencingReferenceMember_.lock( );
        if ( referencingReferenceMember == nullptr )
        {
            auto referencingType = type_.lock( );
            if ( referencingType )
            {
                if ( member_.Length( ) )
                {
                    referencingReferenceMember = std::dynamic_pointer_cast< ReferenceMemberInfo >( referencingType->FindOwnPersistentMember( member_ ) );
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
                                    referencingReferenceMember = referenceMemberInfo;
                                }
                            }
                        }
                    }
                }
                if ( referencingReferenceMember )
                {
                    referencingReferenceMember_ = referencingReferenceMember;
                }
            }
        }
        return referencingReferenceMember;
    }

    std::shared_ptr<CollectionMemberInfo> CollectionMemberInfo::ReferencingCollectionMember( ) const
    {
        auto referencingCollectionMember = referencingCollectionMember_.lock( );
        if ( referencingCollectionMember == nullptr )
        {
            auto referencingType = type_.lock( );
            if ( referencingType )
            {
                if ( member_.Length( ) )
                {
                    referencingCollectionMember = std::dynamic_pointer_cast< CollectionMemberInfo >( referencingType->FindOwnPersistentMember( member_ ) );
                }
                else
                {
                    const auto& referencingTypeMembers = referencingType->OwnPersistentMembers( );
                    const auto count = referencingTypeMembers.size( );
                    for ( size_t i = 0; i < count; i++ )
                    {
                        const auto& referencingTypeMember = referencingTypeMembers[ i ];
                        auto referencingTypeMemberType = referencingTypeMember->Type( );
                        if ( referencingTypeMemberType == MemberInfoType::Collection )
                        {
                            auto collectionMemberInfo = std::dynamic_pointer_cast< CollectionMemberInfo >( referencingTypeMember );
                            auto referencedType = collectionMemberInfo->ReferencedType( );
                            if ( referencedType )
                            {
                                if ( Owner( )->Id( ) == referencedType->Id( ) )
                                {
                                    referencingCollectionMember = collectionMemberInfo;
                                }
                            }
                        }
                    }
                }
                if ( referencingCollectionMember )
                {
                    referencingCollectionMember_ = referencingCollectionMember;
                }
            }
        }
        return referencingCollectionMember;
    }

    bool CollectionMemberInfo::IsManyToMany( ) const
    {
        if ( isManyToMany_.has_value( ) )
        {
            return isManyToMany_.value( );
        }
        auto result = ReferencingCollectionMember( ) != nullptr;
        isManyToMany_ = result;
        return result;
    }
    bool CollectionMemberInfo::IsOneToMany( ) const
    {
        if ( isOneToMany_.has_value( ) )
        {
            return isOneToMany_.value( );
        }
        auto result = ReferencingReferenceMember( ) != nullptr;
        isOneToMany_ = result;
        return result;
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

        if ( memberElement.HasAttribute( L"member" ) )
        {
            member_ = memberElement.Read<WideString>( L"member" );
        }
        if ( memberElement.HasAttribute( L"aggregated" ) )
        {
            aggregated_ = memberElement.Read<bool>( L"aggregated" );
        }
    }

    void CollectionMemberInfo::Validate( ) const
    {
        auto referencingReferenceMember = ReferencingReferenceMember( );
        if ( referencingReferenceMember == nullptr )
        {
            auto referencingCollectionMember = ReferencingCollectionMember( );
            if ( referencingCollectionMember == nullptr )
            {
                auto ownerName = Owner( )->Name( );
                auto name = Name( );
                auto message = Format( L"Unknown referencing member for {}.{}.", ownerName, name );
                throw Exception( message );
            }
        }
    }

}
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
        if ( memberElement.HasAttribute( L"member" ) )
        {
            member_ = memberElement.Read<WideString>( L"member" );
        }
    }

    void ReferenceMemberInfo::Validate( ) const
    {
        Base::Validate( );
        auto referencingReferenceMember = ReferencingReferenceMember( );
        if ( referencingReferenceMember == nullptr )
        {
            auto referencingCollectionMember = ReferencingCollectionMember( );
            if ( referencingCollectionMember == nullptr )
            {
                auto ownerName = Owner( )->Name( );
                auto name = Name( );
                auto message = Format( L"Unknown referenced type for {}.{}.", ownerName, name );
                throw Exception( message );
            }
            else
            {
                if ( Nullable( ) == false )
                {
                    if ( referencingCollectionMember->Aggregated( ) == false )
                    {
                        auto ownerName = Owner( )->Name( );
                        auto name = Name( );
                        auto message = Format( L"{}.{} must be nullable.", ownerName, name );
                        throw Exception( message );
                    }
                }
            }
        }
        else
        {
            if ( Nullable( ) == false )
            {
                auto ownerName = Owner( )->Name( );
                auto name = Name( );
                auto message = Format( L"{}.{} must be nullable.", ownerName, name );
                throw Exception( message );
            }
        }
    }

    std::shared_ptr<CollectionMemberInfo> ReferenceMemberInfo::ReferencingCollectionMember( ) const
    {
        auto result = collectionMember_.lock( );
        if ( result )
        {
            return result;
        }
        auto referencedType = ReferencedType( );
        if ( member_.Length( ) )
        {
            result = std::dynamic_pointer_cast< CollectionMemberInfo >( referencedType->FindOwnPersistentMember( member_ ) );
            return result;
        }
        else
        {
            const auto& referencedTypeMembers = referencedType->OwnMembers( );
            for ( const auto& referencedTypeMember : referencedTypeMembers )
            {
                if ( referencedTypeMember->Type( ) == MemberInfoType::Collection )
                {
                    auto collectionMember = std::static_pointer_cast< const CollectionMemberInfo >( referencedTypeMember );
                    const auto referencingMember = collectionMember->ReferencingReferenceMember( );
                    if ( referencingMember.get( ) == this )
                    {
                        result = std::const_pointer_cast< CollectionMemberInfo >( collectionMember );
                        collectionMember_ = result;
                        return result;
                    }
                }
            }
        }
        return {};
    }
    std::shared_ptr<ReferenceMemberInfo> ReferenceMemberInfo::ReferencingReferenceMember( ) const
    {
        if ( member_ )
        {
            auto result = referencingMember_.lock( );
            if ( result )
            {
                return result;
            }
            auto referencedType = ReferencedType( );
            if ( member_.Length( ) )
            {
                result = std::dynamic_pointer_cast< ReferenceMemberInfo >( referencedType->FindOwnPersistentMember( member_ ) );
                return result;
            }
            else
            {
                const auto& referencedTypeMembers = referencedType->OwnMembers( );
                for ( const auto& referencedTypeMember : referencedTypeMembers )
                {
                    auto referencedTypeMemberType = referencedTypeMember->Type( );
                    if ( referencedTypeMemberType == MemberInfoType::Reference || referencedTypeMemberType == MemberInfoType::TimeSeries )
                    {
                        auto referenceMember = std::static_pointer_cast< const ReferenceMemberInfo >( referencedTypeMember );

                        if ( referenceMember->Name( ) == member_ )
                        {
                            result = std::const_pointer_cast< ReferenceMemberInfo >( referenceMember );
                            referencingMember_ = result;
                            return result;
                        }
                    }
                }
            }
        }
        return {};
    }

    bool ReferenceMemberInfo::IsOneToMany( ) const
    {
        if ( isOneToMany_.has_value( ) )
        {
            return isOneToMany_.value( );
        }
        auto result = ReferencingCollectionMember( ) != nullptr;
        isOneToMany_ = result;
        return result;
    }
    bool ReferenceMemberInfo::IsOneToOne( ) const
    {
        if ( isOneToOne_.has_value( ) )
        {
            return isOneToOne_.value( );
        }
        auto result = ReferencingReferenceMember( ) != nullptr;
        isOneToOne_ = result;
        return result;
    }

}
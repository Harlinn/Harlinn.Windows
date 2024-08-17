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
    std::vector<std::shared_ptr<ClassInfo>> ClassInfo::BaseClasses( ) const
    {
        std::vector<std::shared_ptr<ClassInfo>> result;
        auto baseClass = BaseClass( );
        while ( baseClass )
        {
            result.emplace_back( baseClass );
            baseClass = baseClass->BaseClass( );
        }
        std::reverse( result.begin( ), result.end( ) );
        return result;
    }
    std::vector<std::shared_ptr<ClassInfo>> ClassInfo::BaseClassesAndSelf( ) const
    {
        std::vector<std::shared_ptr<ClassInfo>> result = BaseClasses( );

        auto self = std::const_pointer_cast< ClassInfo >( shared_from_this( ) );

        result.emplace_back( self );
        return result;
    }

    void ClassInfo::Load( const XmlElement& classElement )
    {
        
        if ( classElement.HasAttribute( L"abstract" ) )
        {
            abstract_ = classElement.Read<bool>( L"abstract" );
        }

        if ( classElement.HasAttribute( L"guid" ) )
        {
            guid_ = Guid::Parse( classElement.Read<WideString>( L"guid" ) );
        }

        if ( classElement.HasAttribute( L"displayname" ) )
        {
            displayName_ = classElement.Read<WideString>( L"displayname" );
        }
        if ( classElement.HasAttribute( L"description" ) )
        {
            description_ = classElement.Read<WideString>( L"description" );
        }


        auto membersElement = classElement.Read<XmlElement>( L"members" );
        if ( membersElement )
        {
            LoadMembers( membersElement );
        }
        if ( classElement.HasAttribute( L"base" ) )
        {
            auto baseTypeName = classElement.Read<WideString>( L"base" );
            auto model = Owner( );
            auto baseType = model->FindClass( baseTypeName );
            if ( baseType )
            {
                baseClass_ = baseType;
                auto self = shared_from_this( );
                baseType->AddDerivedClass( self );
            }
        }

        auto self = shared_from_this( );
        auto indexElementList = classElement.ElementsByTagName( L"index" );
        for ( auto indexElement : indexElementList )
        {
            auto indexName = indexElement.Read<WideString>( L"name" );
            auto indexInfo = std::make_shared<IndexInfo>( self, indexName );
            indexInfo->Load( indexElement );
            indexes_.emplace_back( indexInfo );
        }

    }

    void ClassInfo::LoadMembers( const XmlElement& membersElement )
    {
        auto self = shared_from_this( );
        auto childNodes = membersElement.ChildNodes( );
        for ( auto childNode : childNodes )
        {
            if ( childNode.NodeType( ) == Xml::Dom::NodeType::Element )
            {
                auto childElement = childNode.As<XmlElement>( );
                auto typeName = childElement.BaseName( );
                auto name = childElement.Read<WideString>( L"name" );
                if ( typeName == L"boolean" )
                {
                    auto member = std::make_shared<BooleanMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"sbyte" )
                {
                    auto member = std::make_shared<SByteMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"byte" )
                {
                    auto member = std::make_shared<ByteMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"int16" )
                {
                    auto member = std::make_shared<Int16MemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"uint16" )
                {
                    auto member = std::make_shared<UInt16MemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"int32" )
                {
                    auto member = std::make_shared<Int32MemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"uint32" )
                {
                    auto member = std::make_shared<UInt32MemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"int64" )
                {
                    auto member = std::make_shared<Int64MemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"uint64" )
                {
                    auto member = std::make_shared<Int64MemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"enum" )
                {
                    auto member = std::make_shared<EnumMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"single" )
                {
                    auto member = std::make_shared<SingleMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"double" )
                {
                    auto member = std::make_shared<DoubleMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"currency" )
                {
                    auto member = std::make_shared<CurrencyMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"datetime" )
                {
                    auto member = std::make_shared<DateTimeMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"timespan" )
                {
                    auto member = std::make_shared<TimeSpanMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"guid" )
                {
                    auto member = std::make_shared<GuidMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"string" )
                {
                    auto member = std::make_shared<StringMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"binary" )
                {
                    auto member = std::make_shared<BinaryMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"rowversion" )
                {
                    auto member = std::make_shared<RowVersionMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    rowVersion_ = member;
                    member->Load( childElement );
                }
                else if ( typeName == L"reference" )
                {
                    auto member = std::make_shared<ReferenceMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"timeseries" )
                {
                    auto member = std::make_shared<TimeSeriesMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
                else if ( typeName == L"collection" )
                {
                    auto member = std::make_shared<CollectionMemberInfo>( self, name );
                    ownMembers_.emplace_back( member );
                    member->Load( childElement );
                }
            }
        }

        for ( auto member : ownMembers_ )
        {
            ownMembersByName_.emplace( member->Name( ), member );
            if ( member->Persistent( ) )
            {
                ownPersistentMembers_.emplace_back( member );
                ownPersistentMembersByName_.emplace( member->Name( ), member );
                if ( member->PrimaryKey( ) )
                {
                    primaryKey_ = member;
                }
                if ( member->Type( ) == MemberInfoType::RowVersion )
                {
                    rowVersion_ = std::static_pointer_cast< RowVersionMemberInfo >( member );
                }
            }
        }
    }

    void ClassInfo::AfterLoad( )
    {
        std::sort( derivedClasses_.begin( ), derivedClasses_.end( ), []( const auto& first, const auto& second ) { return first->Name( ) < second->Name( ); } );
        for ( auto& index : indexes_ )
        {
            index->AfterLoad( );
        }

        if ( IsTopLevel( ) == false )
        {
            auto baseClass = BaseClass( );
            members_ = baseClass->Members();
            membersByName_ = baseClass->MembersByName( );
            persistentMembers_ = baseClass->PersistentMembers( );
            persistentMembersByName_ = baseClass->PersistentMembersByName( );
        }
        for ( auto member : ownMembers_ )
        {
            members_.emplace_back( member );
            membersByName_.emplace( member->Name( ), member );
            if ( member->Persistent( ) )
            {
                persistentMembers_.emplace_back( member );
                persistentMembersByName_.emplace( member->Name( ), member );
            }
        }



    }

    void ClassInfo::AddDerivedClassesToClassList( std::vector<std::shared_ptr<ClassInfo>>& classList ) const
    {
        for ( auto& derivedClass : derivedClasses_ )
        {
            classList.emplace_back( derivedClass );
            derivedClass->AddDerivedClassesToClassList( classList );
        }
    }



    void ClassInfo::AddDerivedClass( const std::shared_ptr<ClassInfo>& derivedClass )
    {
        derivedClasses_.emplace_back( derivedClass );
    }
}
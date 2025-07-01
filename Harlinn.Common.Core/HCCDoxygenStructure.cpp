#include "pch.h"
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

#include "HCCDoxygen.h"

namespace Harlinn::Common::Core::Doxygen::Structure
{
    namespace
    {
        size_t IndexOfUnqualifiedName( const std::string& qualifiedName )
        {
            const auto* qualifiedNamePtr = qualifiedName.c_str( );
            const auto* ptr = qualifiedNamePtr;
            auto qualifiedNameLength = qualifiedName.length( );
            const auto* qualifiedNameEndPtr = qualifiedNamePtr + qualifiedNameLength;
            const auto* nameStartPtr = qualifiedNamePtr;
            while ( ptr < qualifiedNameEndPtr )
            {
                auto c1 = *ptr;
                if( IsAlnum(c1) || c1 == L'_' )
                { 
                }
                else if ( c1 == L':' )
                {
                    ptr++;
                    auto c2 = *ptr;
                    if ( c2 == L':' )
                    {
                        nameStartPtr = ptr + 1;
                    }
                }
                else
                {
                    break;
                }
                ptr++;
            }
            return nameStartPtr - qualifiedNamePtr;
        }

        std::string GetNameOf( const std::string& compoundName, DoxLanguage language )
        {
            auto index = IndexOfUnqualifiedName( compoundName );
            if ( index )
            {
                return compoundName.substr( index );
            }
            return compoundName;
        }

        std::string GetQualifiedNameOfOwner( const std::string& compoundName, DoxLanguage language )
        {
            auto index = IndexOfUnqualifiedName( compoundName );
            if ( index )
            {
                assert( index >= 2 );
                return compoundName.substr( 0, index - 2 );
            }
            return {};
        }


        std::string GetNameOf( const CompoundDefTypePtr& compoundDef )
        {
            auto compoundName = compoundDef->CompoundName( );
            auto language = compoundDef->Language( );
            return GetNameOf( compoundName, language );
        }

        std::string GetQualifiedNameOfOwner( const CompoundDefTypePtr& compoundDef )
        {
            auto compoundName = compoundDef->CompoundName( );
            auto language = compoundDef->Language( );
            return GetQualifiedNameOfOwner( compoundName, language );
        }

        std::string GetQualifiedNameOfOwner( const CompoundDefTypePtr& compoundDef, const MemberDefTypePtr& memberDef )
        {
            auto qualifiedName = memberDef->QualifiedName( );
            auto language = compoundDef->Language( );
            return GetQualifiedNameOfOwner( qualifiedName, language );
        }


    }

    TypeSystem::TypeSystem( )
    {
        
    }
    TypeSystem::~TypeSystem( ) = default;

    void TypeSystem::Process( const DocumentCollection& documentCollection )
    {

        for ( const auto& documentEntry : documentCollection )
        {
            const auto& document = *documentEntry.second;
            for ( const auto& compoundDefPtr : document )
            {
                auto originalMemberDefCount = allMemberDefs_.size( );
                auto compoundDef = AddCompoundDef( compoundDefPtr );
                if ( compoundDef )
                {
                    ScanSections( compoundDefPtr );
                }
                auto newMemberDefCount = allMemberDefs_.size( );
                if ( compoundDef->Kind( ) == DoxCompoundKind::Namespace && originalMemberDefCount == newMemberDefCount )
                {
                    allCompoundDefs_.erase( compoundDef->Id( ) );
                }
            }
        }

        for ( const auto& entry : allCompoundDefs_ )
        {
            auto* compoundDef = entry.second;
            compoundDef->Process( );
        }

        for ( const auto& entry : allCompoundDefs_ )
        {
            auto* compoundDef = entry.second;
            auto kind = compoundDef->Kind( );
            if ( kind == DoxCompoundKind::Namespace )
            {
                namespaceMap_.emplace( compoundDef->CompoundName(), static_cast< NamespaceCompoundDef* >( compoundDef ) );
                namespaces_.emplace_back( static_cast< NamespaceCompoundDef* >( compoundDef ) );
            }
        }

        for ( const auto& entry : allCompoundDefs_ )
        {
            auto* compoundDef = entry.second;
            if ( compoundDef->Owner( ) == nullptr )
            {
                auto kind = compoundDef->Kind( );
                if ( kind != DoxCompoundKind::File && kind != DoxCompoundKind::Dir )
                {
                    rootCompoundDefs_.emplace( compoundDef->Id( ), compoundDef );
                }
            }
        }



    }

    void TypeSystem::ScanSections( const CompoundDefTypePtr& compoundDefTypePtr )
    {
        const auto& sections = compoundDefTypePtr->SectionDef( );
        for ( const auto& section : sections )
        {
            const auto& memberDefs = section->MemberDef( );
            for ( const auto& memberDef : memberDefs )
            {
                AddMemberDef( memberDef );
            }
        }
    }

    bool TypeSystem::ParentNamespaceName( std::string_view compoundName, std::string& parentCompoundName )
    {
        auto offset = compoundName.rfind( "::" );
        if ( offset != std::string_view::npos )
        {
            parentCompoundName.assign( compoundName.data( ), offset );
            return true;
        }
        return false;
    }

    CompoundDef* TypeSystem::FindCompoundDefByName( const std::string& compoundName )
    {
        for ( auto entry : allCompoundDefs_ )
        {
            auto compoundDef = entry.second;
            if ( compoundDef->CompoundName( ) == compoundName )
            {
                return compoundDef;
            }
        }
        return nullptr;
    }

    NamespaceCompoundDef* TypeSystem::FindNamespace( const std::string& compoundName )
    {
        auto compoundDef = FindCompoundDefByName( compoundName );
        if ( compoundDef && compoundDef->Kind( ) == DoxCompoundKind::Namespace )
        {
            return static_cast<NamespaceCompoundDef*>( compoundDef );
        }
        return nullptr;
    }

    NamespaceCompoundDef* TypeSystem::CreateNamespace( const std::string& compoundName )
    {
        return nullptr;
    }


    void CompoundDef::Process( )
    {
        auto typeSystem = Types( );
        const auto& def = Def( );
        const auto& baseCompoundRefs = def->BaseCompoundRef( );
        for ( auto& ptr : baseCompoundRefs )
        {
            const auto& refId = ptr->RefId( );
            auto baseCompoundDef = typeSystem->FindCompoundDef( refId );
            if ( baseCompoundDef )
            {
                DoxProtectionKind protection = ptr->Prot( );
                DoxVirtualKind virtualKind = ptr->Virt( );
                const auto& content = ptr->Content( );
                Inherit inherit( baseCompoundDef, protection, virtualKind, content );
                inherits_.emplace_back( inherit );
            }
        }




        const std::vector<RefTypePtr>& innerModules = def->InnerModule( );
        ProcessChildren( innerModules );
        const std::vector<RefTypePtr>& innerDirs = def->InnerDir( );
        ProcessChildren( innerDirs );
        const std::vector<RefTypePtr>& innerFiles = def->InnerFile( );
        ProcessChildren( innerFiles );
        const std::vector<RefTypePtr>& innerClasses = def->InnerClass( );
        ProcessChildren( innerClasses );
        const std::vector<RefTypePtr>& innerConcepts = def->InnerConcept( );
        ProcessChildren( innerConcepts );
        const std::vector<RefTypePtr>& innerNamespaces = def->InnerNamespace( );
        ProcessChildren( innerNamespaces );
        const std::vector<RefTypePtr>& innerPages = def->InnerPage( );
        ProcessChildren( innerPages );
        const std::vector<RefTypePtr>& innerGroups = def->InnerGroup( );
        ProcessChildren( innerGroups );

        const auto& listOfallMembersPtr = def->ListOfallMembers( );
        if ( listOfallMembersPtr )
        {
            const auto& listOfallMembers = *listOfallMembersPtr;
            for ( auto& ptr : listOfallMembers )
            {
                const auto& refId = ptr->RefId( );
                if ( membersMap_.contains( refId ) == false )
                {
                    auto memberDef = typeSystem->FindMemberDef( refId );
                    if ( memberDef )
                    {
                        const auto& name = ptr->Name( );
                        const auto& scope = ptr->Scope( );
                        const auto prot = ptr->Prot( );
                        const auto virt = ptr->Virt( );
                        const auto& ambiguityScope = ptr->AmbiguityScope( );

                        MemberEntry memberEntry( memberDef, name, scope, prot, virt, ambiguityScope );
                        members_.emplace_back( memberEntry );
                        membersMap_.emplace( refId, memberEntry );
                        memberDef->SetOwner( this );
                    }
                }
            }
        }


    }

    void CompoundDef::ProcessChildren( const std::vector<RefTypePtr>& children )
    {
        auto typeSystem = Types( );
        for ( auto& ptr : children )
        {
            const auto& refId = ptr->RefId( );
            auto otherCompoundRef = typeSystem->FindCompoundDef( refId );
            if ( otherCompoundRef )
            {
                DoxProtectionKind prot = ptr->Prot( );
                bool isInline = ptr->Inline( );
                std::string_view content = ptr->Content( );
                ChildEntry childEntry( otherCompoundRef, prot, isInline, content );

                auto compoundName = CompoundName( );
                auto otherCompoundName = otherCompoundRef->CompoundName( );
                if ( otherCompoundName.starts_with( compoundName ) )
                {
                    if ( childrenMap_.contains( refId ) == false )
                    {
                        children_.emplace_back( childEntry );
                        childrenMap_.emplace( refId, childEntry );
                        otherCompoundRef->SetOwner( this );
                    }
                }
                else if ( referenceMap_.contains( refId ) == false )
                {
                    references_.emplace_back( childEntry );
                    referenceMap_.emplace( refId, childEntry );
                }
            }
        }
    }
    
 

}
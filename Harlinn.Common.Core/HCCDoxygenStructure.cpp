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


        std::string GetNameOf( const Doxygen::CompoundDefTypePtr& compoundDef )
        {
            auto compoundName = compoundDef->CompoundName( );
            auto language = compoundDef->Language( );
            return GetNameOf( compoundName, language );
        }

        std::string GetQualifiedNameOfOwner( const Doxygen::CompoundDefTypePtr& compoundDef )
        {
            auto compoundName = compoundDef->CompoundName( );
            auto language = compoundDef->Language( );
            return GetQualifiedNameOfOwner( compoundName, language );
        }

        std::string GetQualifiedNameOfOwner( const Doxygen::CompoundDefTypePtr& compoundDef, const Doxygen::MemberDefTypePtr& memberDef )
        {
            auto qualifiedName = memberDef->QualifiedName( );
            auto language = compoundDef->Language( );
            return GetQualifiedNameOfOwner( qualifiedName, language );
        }


    }

    TypeSystem::TypeSystem( )
    {
        auto global = std::make_unique<Namespace>( this );
        global_ = global.get( );
        all_.emplace_back( std::move( global ) );
    }
    TypeSystem::~TypeSystem( ) = default;

    void TypeSystem::Process( const DocumentCollection& documentCollection )
    {
        for ( const auto& documentEntry : documentCollection )
        {
            const auto& document = *documentEntry.second;
            for ( const auto& compoundDef : document )
            {
                auto member = AddCompoundDef( compoundDef );
                if ( member )
                {
                    ScanSections( compoundDef, static_cast< Container* >( member ) );
                }
            }
        }

        for ( const auto& entry : allNamespaces_ )
        {
            auto nspace = entry.second;
            auto nspaceQualifiedName = nspace->QualifiedName( );
            const auto& compoundDef = nspace->CompoundDef( );
            auto ownerQualifiedName = GetQualifiedNameOfOwner( compoundDef );
            if ( ownerQualifiedName.length() )
            {
                auto ownerNamespace = FindNamespaceByQualifiedName( ownerQualifiedName );
                if ( ownerNamespace != nullptr )
                {
                    ownerNamespace->Add( nspace );
                    nspace->SetOwner( ownerNamespace );
                }
            }
            else
            {
                global_->Add( nspace );
                nspace->SetOwner( global_ );
            }
        }

        for ( const auto& entry : allTypes_ )
        {
            auto type = entry.second;
            auto memberType = type->MemberType( );
            if ( memberType <= MemberType::Concept )
            {
                auto typeQualifiedName = type->QualifiedName( );
                CompoundDefTypePtr compoundDef;
                if ( memberType <= MemberType::Module )
                {
                    compoundDef = static_cast< TypeContainer* >( type )->CompoundDef( );
                }
                else
                {
                    compoundDef = static_cast< Concept* >( type )->CompoundDef( );
                }
                
                auto ownerQualifiedName = GetQualifiedNameOfOwner( compoundDef );
                if ( ownerQualifiedName.length( ) )
                {
                    auto ownerNamespace = FindNamespaceByQualifiedName( ownerQualifiedName );
                    if ( ownerNamespace != nullptr )
                    {
                        ownerNamespace->Add( type );
                        type->SetOwner( ownerNamespace );
                    }
                    else
                    {
                        auto ownerType = static_cast<Container*>(FindTypeByQualifiedName( ownerQualifiedName ));
                        if ( ownerType != nullptr )
                        {
                            ownerType->Add( type );
                            type->SetOwner( ownerType );
                        }
                    }
                }
                else
                {
                    global_->Add( type );
                    type->SetOwner( global_ );
                }
            }

            switch ( memberType )
            {
                case MemberType::Struct:
                {
                    auto strct = static_cast< Struct* >( type );
                    strct->Process( this, strct );
                }
                break;
                case MemberType::Class:
                {
                    auto clss = static_cast< Class* >( type );
                    clss->Process( this, clss );
                }
                break;
            }
        }

        for ( const auto& entry : allFunctionsByQualifiedName_ )
        {
            Function* function = entry.second;
            auto owner = function->Owner( );
            if ( owner == nullptr )
            {
                global_->Add( function );
                function->SetOwner( global_ );
            }
        }


        for ( const auto& entry : allNamespaces_ )
        {
            entry.second->Process( );
        }


    }

    void TypeSystem::ScanSections( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container )
    {
        const auto& sections = compoundDef->SectionDef( );
        for ( const auto& section : sections )
        {
            const auto& memberDefs = section->MemberDef( );
            for ( const auto& memberDef : memberDefs )
            {
                AddMemberDef( compoundDef, container, section, memberDef );
            }
        }
    }

    Namespace* TypeSystem::AddNamespace( const Doxygen::CompoundDefTypePtr& compoundDef )
    {
        auto id = compoundDef->Id( );
        
        auto it = allNamespaces_.find( id );
        if ( it != allNamespaces_.end( ) )
        {
            return it->second;
        }
        else
        {
            auto name = GetNameOf( compoundDef );
            std::unique_ptr<Namespace> nspace( new Namespace( this ) );
            auto* result = nspace.get( );
            all_.emplace_back( std::move( nspace ) );
            allNamespaces_.emplace( id, result );
            auto qualifiedName = compoundDef->CompoundName( );
            allNamespacesByQualifiedName_.emplace( qualifiedName, result );
            result->Assign( compoundDef );
            return result;
        }
    }
    Struct* TypeSystem::AddStruct( const Doxygen::CompoundDefTypePtr& compoundDef )
    {
        auto id = compoundDef->Id( );
        auto it = allTypes_.find( id );
        if ( it != allTypes_.end( ) )
        {
            return static_cast< Struct* >( it->second );
        }
        else
        {
            auto qualifiedName = compoundDef->CompoundName( );
            auto name = GetNameOf( compoundDef );
            std::unique_ptr<Struct> type( new Struct( this ) );
            auto* result = type.get( );
            all_.emplace_back( std::move( type ) );
            allTypes_.emplace( id, result );
            allTypesByQualifiedName_.emplace( qualifiedName, result );
            result->Assign( compoundDef );
            return result;
        }
    }
    Class* TypeSystem::AddClass( const Doxygen::CompoundDefTypePtr& compoundDef )
    {
        auto id = compoundDef->Id( );
        auto it = allTypes_.find( id );
        if ( it != allTypes_.end( ) )
        {
            return static_cast< Class* >( it->second );
        }
        else
        {
            auto qualifiedName = compoundDef->CompoundName( );
            auto name = GetNameOf( compoundDef );
            std::unique_ptr<Class> type( new Class( this ) );
            auto* result = type.get( );
            all_.emplace_back( std::move( type ) );
            allTypes_.emplace( id, result );
            allTypesByQualifiedName_.emplace( qualifiedName, result );
            result->Assign( compoundDef );
            return result;
        }
    }
    Union* TypeSystem::AddUnion( const Doxygen::CompoundDefTypePtr& compoundDef )
    {
        auto id = compoundDef->Id( );
        auto it = allTypes_.find( id );
        if ( it != allTypes_.end( ) )
        {
            return static_cast< Union* >( it->second );
        }
        else
        {
            auto qualifiedName = compoundDef->CompoundName( );
            auto name = GetNameOf( compoundDef );
            std::unique_ptr<Union> type( new Union( this ) );
            auto* result = type.get( );
            all_.emplace_back( std::move( type ) );
            allTypes_.emplace( id, result );
            allTypesByQualifiedName_.emplace( qualifiedName, result );
            result->Assign( compoundDef );
            return result;
        }
    }
    Interface* TypeSystem::AddInterface( const Doxygen::CompoundDefTypePtr& compoundDef )
    {
        auto id = compoundDef->Id( );
        auto it = allTypes_.find( id );
        if ( it != allTypes_.end( ) )
        {
            return static_cast< Interface* >( it->second );
        }
        else
        {
            auto qualifiedName = compoundDef->CompoundName( );
            auto name = GetNameOf( compoundDef );
            std::unique_ptr<Interface> type( new Interface( this ) );
            auto* result = type.get( );
            all_.emplace_back( std::move( type ) );
            allTypes_.emplace( id, result );
            allTypesByQualifiedName_.emplace( qualifiedName, result );
            result->Assign( compoundDef );
            return result;
        }
    }
    Concept* TypeSystem::AddConcept( const Doxygen::CompoundDefTypePtr& compoundDef )
    {
        auto id = compoundDef->Id( );
        auto it = allTypes_.find( id );
        if ( it != allTypes_.end( ) )
        {
            return static_cast< Concept* >( it->second );
        }
        else
        {
            auto qualifiedName = compoundDef->CompoundName( );
            auto name = GetNameOf( compoundDef );
            std::unique_ptr<Concept> type( new Concept( this ) );
            auto* result = type.get( );
            all_.emplace_back( std::move( type ) );
            allTypes_.emplace( id, result );
            allTypesByQualifiedName_.emplace( qualifiedName, result );
            result->Assign( compoundDef );
            return result;
        }
    }
    Module* TypeSystem::AddModule( const Doxygen::CompoundDefTypePtr& compoundDef )
    {
        auto id = compoundDef->Id( );
        auto it = allTypes_.find( id );
        if ( it != allTypes_.end( ) )
        {
            return static_cast< Module* >( it->second );
        }
        else
        {
            auto qualifiedName = compoundDef->CompoundName( );
            auto name = GetNameOf( compoundDef );
            std::unique_ptr<Module> type( new Module( this ) );
            auto* result = type.get( );
            all_.emplace_back( std::move( type ) );
            allTypes_.emplace( id, result );
            allTypesByQualifiedName_.emplace( qualifiedName, result );
            result->Assign( compoundDef );
            return result;
        }
    }

    Member* TypeSystem::AddCompoundDef( const Doxygen::CompoundDefTypePtr& compoundDef )
    {
        Member* result = nullptr;
        auto kind = compoundDef->Kind( );
        switch ( kind )
        {
            case DoxCompoundKind::Namespace:
            {
                result = AddNamespace( compoundDef );
            }
            break;
            case DoxCompoundKind::Struct:
            {
                result = AddStruct( compoundDef );
            }
            break;
            case DoxCompoundKind::Class:
            {
                result = AddClass( compoundDef );
            }
            break;
            case DoxCompoundKind::Union:
            {
                result = AddUnion( compoundDef );
            }
            break;
            case DoxCompoundKind::Interface:
            {
                result = AddInterface( compoundDef );
            }
            break;
            case DoxCompoundKind::Concept:
            {
                result = AddConcept( compoundDef );
            }
            break;
            case DoxCompoundKind::Module:
            {
                result = AddModule( compoundDef );
            }
            break;
            case DoxCompoundKind::File:
            {
                //result = AddModule( compoundDef );
            }
            break;
            case DoxCompoundKind::Dir:
            {
                //result = AddModule( compoundDef );
            }
            break;
            case DoxCompoundKind::Group:
            {
                //result = AddModule( compoundDef );
            }
            break;
            case DoxCompoundKind::Page:
            {
                //result = AddModule( compoundDef );
            }
            break;
            default:
            {
                DebugBreak( );
            }
            break;
        }
        return result;
    }

    Function* TypeSystem::AddFunction( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto id = memberDef->Id( );
        auto it = allFunctionOverloadsById_.find( id );
        if ( it != allFunctionOverloadsById_.end( ) )
        {
            return static_cast< Function* >( it->second->Owner( ) );
        }
        else
        {
            auto qualifiedName = memberDef->QualifiedName( );
            auto name = memberDef->Name( );

            auto* funtion = FindFunctionByQualifiedName( qualifiedName );
            if ( !funtion )
            {
                auto f = std::make_unique<Function>( this );
                funtion = f.get( );
                all_.emplace_back( std::move( f ) );
                funtion->SetQualifiedName( qualifiedName );
                funtion->SetName( name );
                funtion->SetOwner( container );
                container->Add( funtion );
                allFunctionsByQualifiedName_.emplace( qualifiedName, funtion );
            }
            auto& argsString = memberDef->ArgsString( );
            auto* fo = static_cast< FunctionOverload* >( funtion->FindMemberByName( argsString ) );
            if ( fo == nullptr )
            {
                auto functionOverload = std::make_unique<FunctionOverload>( this );
                functionOverload->Assign( compoundDef, sectionDef, memberDef );
                fo = functionOverload.get( );
                fo->SetQualifiedName( qualifiedName );
                fo->SetName( name );
                fo->SetId( id );
                all_.emplace_back( std::move( functionOverload ) );
                funtion->Add( fo, argsString );
                allFunctionOverloadsById_.emplace( id, fo );
            }
            return funtion;
        }
    }

    Enum* TypeSystem::AddEnum( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto qualifiedName = memberDef->QualifiedName( );
        auto name = memberDef->Name( );
        auto result = AddMemberDef<Enum>( qualifiedName, name, compoundDef, container, sectionDef, memberDef );
        auto id = memberDef->Id( );
        allTypes_.emplace( id, result );
        allTypesByQualifiedName_.emplace( qualifiedName, result );
        return result;
    }

    Define* TypeSystem::AddDefine( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto qualifiedName = memberDef->QualifiedName( );
        auto name = memberDef->Name( );
        auto result = AddMemberDef<Define>( qualifiedName, name, compoundDef, container, sectionDef, memberDef );
        return result;
    }

    Property* TypeSystem::AddProperty( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto qualifiedName = memberDef->QualifiedName( );
        auto name = memberDef->Name( );
        auto result = AddMemberDef<Property>( qualifiedName, name, compoundDef, container, sectionDef, memberDef );
        return result;
    }

    Event* TypeSystem::AddEvent( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto qualifiedName = memberDef->QualifiedName( );
        auto name = memberDef->Name( );
        auto result = AddMemberDef<Event>( qualifiedName, name, compoundDef, container, sectionDef, memberDef );
        return result;
    }

    Variable* TypeSystem::AddVariable( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto qualifiedName = memberDef->QualifiedName( );
        auto name = memberDef->Name( );
        auto result = AddMemberDef<Variable>( qualifiedName, name, compoundDef, container, sectionDef, memberDef );
        return result;
    }

    Typedef* TypeSystem::AddTypedef( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto qualifiedName = memberDef->QualifiedName( );
        auto name = memberDef->Name( );
        auto result = AddMemberDef<Typedef>( qualifiedName, name, compoundDef, container, sectionDef, memberDef );
        auto id = memberDef->Id( );
        allTypes_.emplace( id, result );
        allTypesByQualifiedName_.emplace( qualifiedName, result );
        return result;
    }

    Signal* TypeSystem::AddSignal( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto qualifiedName = memberDef->QualifiedName( );
        auto name = memberDef->Name( );
        auto result = AddMemberDef<Signal>( qualifiedName, name, compoundDef, container, sectionDef, memberDef );
        return result;
    }

    Prototype* TypeSystem::AddPrototype( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto qualifiedName = memberDef->QualifiedName( );
        auto name = memberDef->Name( );
        auto result = AddMemberDef<Prototype>( qualifiedName, name, compoundDef, container, sectionDef, memberDef );
        return result;
    }

    Friend* TypeSystem::AddFriend( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto qualifiedName = memberDef->QualifiedName( );
        auto name = memberDef->Name( );
        auto result = AddMemberDef<Friend>( qualifiedName, name, compoundDef, container, sectionDef, memberDef );
        return result;
    }

    DCop* TypeSystem::AddDCop( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto qualifiedName = memberDef->QualifiedName( );
        auto name = memberDef->Name( );
        auto result = AddMemberDef<DCop>( qualifiedName, name, compoundDef, container, sectionDef, memberDef );
        return result;
    }

    Slot* TypeSystem::AddSlot( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto qualifiedName = memberDef->QualifiedName( );
        auto name = memberDef->Name( );
        auto result = AddMemberDef<Slot>( qualifiedName, name, compoundDef, container, sectionDef, memberDef );
        return result;
    }

    InterfaceReference* TypeSystem::AddInterfaceReference( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto qualifiedName = memberDef->QualifiedName( );
        auto name = memberDef->Name( );
        auto result = AddMemberDef<InterfaceReference>( qualifiedName, name, compoundDef, container, sectionDef, memberDef );
        return result;
    }

    Service* TypeSystem::AddService( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        auto qualifiedName = memberDef->QualifiedName( );
        auto name = memberDef->Name( );
        auto result = AddMemberDef<Service>( qualifiedName, name, compoundDef, container, sectionDef, memberDef );
        return result;
    }


    Member* TypeSystem::AddMemberDef( const Doxygen::CompoundDefTypePtr& compoundDef, Container* container, const Doxygen::SectionDefTypePtr& sectionDef, const Doxygen::MemberDefTypePtr& memberDef )
    {
        Member* result = nullptr;
        auto kind = memberDef->Kind( );
        switch ( kind )
        {
            case DoxMemberKind::Define:
            {
                result = AddDefine( compoundDef, container, sectionDef, memberDef );
            }
            break;
            case DoxMemberKind::Property:
            {
                result = AddProperty( compoundDef, container, sectionDef, memberDef );
            }
            break;
            case DoxMemberKind::Event:
            {
                result = AddEvent( compoundDef, container, sectionDef, memberDef );
            }
            break;
            case DoxMemberKind::Variable:
            {
                result = AddVariable( compoundDef, container, sectionDef, memberDef );
            }
            break;
            case DoxMemberKind::Typedef:
            {
                result = AddTypedef( compoundDef, container, sectionDef, memberDef );
            }
            break;
            case DoxMemberKind::Enum:
            {
                result = AddEnum( compoundDef, container, sectionDef, memberDef );
            }
            break;
            case DoxMemberKind::Function:
            {
                result = AddFunction( compoundDef, container, sectionDef, memberDef );
            }
            break;
            case DoxMemberKind::Signal:
            {
                result = AddSignal( compoundDef, container, sectionDef, memberDef );
            }
            break;
            case DoxMemberKind::Prototype:
            {
                result = AddPrototype( compoundDef, container, sectionDef, memberDef );
            }
            break;
            case DoxMemberKind::Friend:
            {
                result = AddFriend( compoundDef, container, sectionDef, memberDef );
            }
            break;
            case DoxMemberKind::DCop:
            {
                result = AddDCop( compoundDef, container, sectionDef, memberDef );
            }
            break;
            case DoxMemberKind::Slot:
            {
                result = AddSlot( compoundDef, container, sectionDef, memberDef );
            }
            break;
            case DoxMemberKind::Interface:
            {
                result = AddInterfaceReference( compoundDef, container, sectionDef, memberDef );
            }
            break;
            case DoxMemberKind::Service:
            {
                result = AddService( compoundDef, container, sectionDef, memberDef );
            }
            break;
        }
        return result;
    }

    std::string Member::NameOf( const Doxygen::CompoundDefTypePtr& compoundDef )
    {
        return GetNameOf( compoundDef );
    }


    void Namespace::Process( )
    {
        const auto& members = Members( );
        for ( auto member : members )
        {
            auto memberType = member->MemberType( );
            switch ( memberType )
            {
                case MemberType::Struct:
                {
                    auto strct = static_cast< Structure::Struct* >( member );
                    types_.push_back( strct );
                }
                break;
                case MemberType::Class:
                {
                    auto clss = static_cast< Structure::Class* >( member );
                    types_.push_back( clss );
                }
                break;
                case MemberType::Typedef:
                {
                    auto typeDef = static_cast< Structure::Typedef* >( member );
                    types_.push_back( typeDef );
                }
                break;
                case MemberType::Union:
                {
                    auto u = static_cast< Structure::Union* >( member );
                    types_.push_back( u );
                }
                break;
                case MemberType::Interface:
                {
                    auto i = static_cast< Structure::Interface* >( member );
                    types_.push_back( i );
                }
                break;
                case MemberType::Enum:
                {
                    auto e = static_cast< Structure::Enum* >( member );
                    types_.push_back( e );
                }
                break;
                case MemberType::Function:
                {
                    auto f = static_cast< Structure::Function* >( member );
                    functions_.push_back( f );
                    const auto& overloads = f->Members( );
                    for ( auto o : overloads )
                    {
                        auto overload = static_cast< Structure::FunctionOverload* >( o );
                        functionOverloads_.push_back( overload );
                    }
                }
                break;
                case MemberType::Variable:
                {
                    auto v = static_cast< Structure::Variable* >( member );
                    variables_.push_back( v );
                }
                break;
            }
        }
    }

    void ClassInfo::Process( Structure::TypeSystem* typeSystem, Structure::TypeContainer* type )
    {
        const auto& compoundDef = type->CompoundDef( );
        const auto& baseCompoundRefs = compoundDef->BaseCompoundRef( );
        for ( auto& baseCompoundRef : baseCompoundRefs )
        {
            auto baseType = static_cast< Structure::TypeContainer* >( typeSystem->FindTypeById( baseCompoundRef->RefId( ) ) );
            if ( baseType )
            {
                Structure::InheritanceInfo inheritanceInfo( baseType, baseCompoundRef->Prot( ), baseCompoundRef->Virt( ) == DoxVirtualKind::Virtual );
                inheritance_.push_back( inheritanceInfo );
            }
        }

        const auto& members = type->Members( );
        for ( auto member : members )
        {
            auto memberType = member->MemberType( );
            switch ( memberType )
            {
                case MemberType::Struct:
                {
                    auto strct = static_cast< Structure::Struct* >( member );
                    nestedTypes_.push_back( strct );
                }
                break;
                case MemberType::Class:
                {
                    auto clss = static_cast< Structure::Class* >( member );
                    nestedTypes_.push_back( clss );
                }
                break;
                case MemberType::Typedef:
                {
                    auto typeDef = static_cast< Structure::Typedef* >( member );
                    nestedTypes_.push_back( typeDef );
                }
                break;
                case MemberType::Union:
                {
                    auto u = static_cast< Structure::Union* >( member );
                    nestedTypes_.push_back( u );
                }
                break;
                case MemberType::Interface:
                {
                    auto i = static_cast< Structure::Interface* >( member );
                    nestedTypes_.push_back( i );
                }
                break;
                case MemberType::Enum:
                {
                    auto e = static_cast< Structure::Enum* >( member );
                    nestedTypes_.push_back( e );
                }
                break;
                case MemberType::Function:
                {
                    auto f = static_cast< Structure::Function* >( member );
                    functions_.push_back( f );
                    const auto& overloads = f->Members( );
                    for ( auto o : overloads )
                    {
                        auto overload = static_cast< Structure::FunctionOverload* >( o );
                        if ( overload->Static( ) )
                        {
                            staticFunctionOverloads_.push_back( overload );
                        }
                        else
                        {
                            functionOverloads_.push_back( overload );
                        }
                    }
                }
                break;
                case MemberType::Variable:
                {
                    auto v = static_cast< Structure::Variable* >( member );
                    if ( v->Static( ) )
                    {
                        staticVariables_.push_back( v );
                    }
                    else
                    {
                        variables_.push_back( v );
                    }
                }
                break;
            }
        }

    }
 

}
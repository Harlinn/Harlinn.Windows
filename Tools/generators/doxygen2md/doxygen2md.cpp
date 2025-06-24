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

#include <HCCDoxygen.h>
#include <HCCStringBuilder.h>

#include "doxygen2mdOptions.h"


using namespace Harlinn::Common::Core;
using namespace Doxygen2Md;

class DocMember
{
public:
    
private:
    Doxygen::Structure::Member* member_;
public:
    DocMember( Doxygen::Structure::Member* member )
        : member_( member )
    { }

    Doxygen::Structure::Member* Member( ) const
    {
        return member_;
    }

};


class DocContainer : public DocMember
{
public:
    using Base = DocMember;

    DocContainer( Doxygen::Structure::Container* container )
        : Base( container )
    { }

};

class DocTypeContainer : public DocContainer
{
public:
    using Base = DocContainer;

    DocTypeContainer( Doxygen::Structure::TypeContainer* typeContainer )
        : Base( typeContainer )
    { }

};


class DocNamespace : public DocTypeContainer
{
public:
    using Base = DocTypeContainer;

    DocNamespace( Doxygen::Structure::Namespace* nspace )
        : Base( nspace )
    { }
};

class DocStructOrClass : public DocTypeContainer
{
public:
    using Base = DocTypeContainer;

    DocStructOrClass( Doxygen::Structure::TypeContainer* typeContainer )
        : Base( typeContainer )
    { }
};

class DocStruct : public DocStructOrClass
{
public:
    using Base = DocStructOrClass;

    DocStruct( Doxygen::Structure::Struct* type )
        : Base( type )
    { }
};

class DocClass : public DocStructOrClass
{
public:
    using Base = DocStructOrClass;

    DocClass( Doxygen::Structure::Class* type )
        : Base( type )
    { }
};

class DocUnion : public DocTypeContainer
{
public:
    using Base = DocTypeContainer;

    DocUnion( Doxygen::Structure::Union* type )
        : Base( type )
    { }
};




class DocContext
{

};

void ProcessMembers( DocContext& context, Doxygen::Structure::Member* owner, const std::vector<Doxygen::Structure::Member*>& members, size_t level );


void ProcessNamespace( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Namespace* nspace, size_t level )
{
    PrintLn( L"Namespace: {} -> {}", nspace->Name( ), nspace->QualifiedName( ) );
    

    const auto& members = nspace->Members( );
    ProcessMembers( context, nspace, members, level + 1 );
}

void ProcessStruct( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Struct* type, size_t level )
{
    PrintLn( L"Struct: {} -> {}", type->Name( ), type->QualifiedName( ) );
    const auto& members = type->Members( );
    ProcessMembers( context, type, members, level + 1 );
}

void ProcessClass( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Class* type, size_t level )
{
    PrintLn( L"Class: {} -> {}", type->Name( ), type->QualifiedName( ) );
    const auto& members = type->Members( );
    ProcessMembers( context, type, members, level + 1 );
}

void ProcessUnion( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Union* type, size_t level )
{
    PrintLn( L"Union: {} -> {}", type->Name( ), type->QualifiedName( ) );
    const auto& members = type->Members( );
    ProcessMembers( context, type, members, level + 1 );
}

void ProcessInterface( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Interface* type, size_t level )
{
    PrintLn( L"Interface: {} -> {}", type->Name( ), type->QualifiedName( ) );
    const auto& members = type->Members( );
    ProcessMembers( context, type, members, level + 1 );
}

void ProcessModule( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Module* mod, size_t level )
{
    PrintLn( L"Module: {} -> {}", mod->Name( ), mod->QualifiedName( ) );
    const auto& members = mod->Members( );
    ProcessMembers( context, mod, members, level + 1 );
}

void ProcessConcept( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Concept* cpt, size_t level )
{
    PrintLn( L"Concept: {} -> {}", cpt->Name( ), cpt->QualifiedName( ) );
    const auto& members = cpt->Members( );
    ProcessMembers( context, cpt, members, level + 1 );
}

void ProcessFunction( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Function* func, size_t level )
{
    PrintLn( L"Function: {} -> {}", func->Name( ), func->QualifiedName( ) );
}

void ProcessEnum( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Enum* type, size_t level )
{
    PrintLn( L"Enum: {} -> {}", type->Name( ), type->QualifiedName( ) );
    const auto& members = type->Members( );
    ProcessMembers( context, type, members, level + 1 );
}

void ProcessDefine( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Define* def, size_t level )
{
    PrintLn( L"Define: {} -> {}", def->Name( ), def->QualifiedName( ) );
}

void ProcessProperty( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Property* prop, size_t level )
{
    PrintLn( L"Property: {} -> {}", prop->Name( ), prop->QualifiedName( ) );
}

void ProcessEvent( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Event* evt, size_t level )
{
    PrintLn( L"Event: {} -> {}", evt->Name( ), evt->QualifiedName( ) );
}

void ProcessVariable( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Variable* var, size_t level )
{
    PrintLn( L"Variable: {} -> {}", var->Name( ), var->QualifiedName( ) );
}

void ProcessTypedef( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Typedef* type, size_t level )
{
    PrintLn( L"Typedef: {} -> {}", type->Name( ), type->QualifiedName( ) );
}

void ProcessSignal( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Signal* s, size_t level )
{
    PrintLn( L"Signal: {} -> {}", s->Name( ), s->QualifiedName( ) );
}

void ProcessPrototype( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Prototype* p, size_t level )
{
    PrintLn( L"Prototype: {} -> {}", p->Name( ), p->QualifiedName( ) );
}

void ProcessFriend( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Friend* frnd, size_t level )
{
    PrintLn( L"Friend: {} -> {}", frnd->Name( ), frnd->QualifiedName( ) );
}

void ProcessDCop( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::DCop* dcop, size_t level )
{
    PrintLn( L"DCop: {} -> {}", dcop->Name( ), dcop->QualifiedName( ) );
}

void ProcessSlot( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Slot* slot, size_t level )
{
    PrintLn( L"Slot: {} -> {}", slot->Name( ), slot->QualifiedName( ) );
}

void ProcessInterfaceReference( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::InterfaceReference* ir, size_t level )
{
    PrintLn( L"InterfaceReference: {} -> {}", ir->Name( ), ir->QualifiedName( ) );
}

void ProcessService( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Service* service, size_t level )
{
    PrintLn( L"Service: {} -> {}", service->Name( ), service->QualifiedName( ) );
}


void ProcessMember( DocContext& context, Doxygen::Structure::Member* owner, Doxygen::Structure::Member* member, size_t level )
{
    auto memberType = member->MemberType( );

    
    

    switch ( memberType )
    {
        case Doxygen::Structure::MemberType::Namespace:
            ProcessNamespace( context, owner, static_cast< Doxygen::Structure::Namespace* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Struct:
            ProcessStruct( context, owner, static_cast< Doxygen::Structure::Struct* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Class:
            ProcessClass( context, owner, static_cast< Doxygen::Structure::Class* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Union:
            ProcessUnion( context, owner, static_cast< Doxygen::Structure::Union* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Interface:
            ProcessInterface( context, owner, static_cast< Doxygen::Structure::Interface* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Module:
            ProcessModule( context, owner, static_cast< Doxygen::Structure::Module* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Concept:
            ProcessConcept( context, owner, static_cast< Doxygen::Structure::Concept* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Function:
            ProcessFunction( context, owner, static_cast< Doxygen::Structure::Function* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Enum:
            ProcessEnum( context, owner, static_cast< Doxygen::Structure::Enum* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Define:
            ProcessDefine( context, owner, static_cast< Doxygen::Structure::Define* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Property:
            ProcessProperty( context, owner, static_cast< Doxygen::Structure::Property* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Event:
            ProcessEvent( context, owner, static_cast< Doxygen::Structure::Event* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Variable:
            ProcessVariable( context, owner, static_cast< Doxygen::Structure::Variable* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Typedef:
            ProcessTypedef( context, owner, static_cast< Doxygen::Structure::Typedef* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Signal:
            ProcessSignal( context, owner, static_cast< Doxygen::Structure::Signal* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Prototype:
            ProcessPrototype( context, owner, static_cast< Doxygen::Structure::Prototype* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Friend:
            ProcessFriend( context, owner, static_cast< Doxygen::Structure::Friend* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::DCop:
            ProcessDCop( context, owner, static_cast< Doxygen::Structure::DCop* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Slot:
            ProcessSlot( context, owner, static_cast< Doxygen::Structure::Slot* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::InterfaceReference:
            ProcessInterfaceReference( context, owner, static_cast< Doxygen::Structure::InterfaceReference* >( member ), level );
            break;
        case Doxygen::Structure::MemberType::Service:
            ProcessService( context, owner, static_cast< Doxygen::Structure::Service* >( member ), level );
            break;
    }
}


void ProcessMembers( DocContext& context, Doxygen::Structure::Member* owner, const std::vector<Doxygen::Structure::Member*>& members, size_t level )
{
    for ( auto member : members )
    {
        ProcessMember( context, owner, member, level );
    }
}


int main(int argc, char* argv[] )
{
    using namespace Harlinn::Common::Core;
    using namespace Doxygen2Md;

    Doxygen2MdOptions options;
    

    if ( options.Parse( argc, argv ) )
    {
        Doxygen::DocumentCollection documentCollection;
        auto directory = options.InputDirectory();
        documentCollection.AddDirectory( directory );
        auto typeSystem = documentCollection.TypeSystem( );
        const auto& allTypes = typeSystem->AllTypes( );
        auto allTypesSize = allTypes.size( );

        auto globalNamespace = typeSystem->GlobalNamespace( );

        const auto& globalNamespaceMembers = globalNamespace->Members( );

        DocContext context;
        ProcessMembers( context, globalNamespace, globalNamespaceMembers, 0 );

        auto documentCount = documentCollection.size( );
    }


}

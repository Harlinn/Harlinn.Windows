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

#include "D2MStructure.h"

using namespace Doxygen2Md;



void ProcessMembers( DocContext& context, DocContainer* owner, const std::vector<Doxygen::Structure::Member*>& members );


void ProcessNamespace( DocContext& context, DocContainer* owner, Doxygen::Structure::Namespace* nspace )
{
    auto* newNamespace = context.AddNamespace( owner, nspace );
    const auto& members = nspace->Members( );
    ProcessMembers( context, newNamespace, members );
}

void ProcessStruct( DocContext& context, DocContainer* owner, Doxygen::Structure::Struct* type )
{
    auto* newStruct = context.AddStruct( owner, type );
    const auto& members = type->Members( );
    ProcessMembers( context, newStruct, members );
}

void ProcessClass( DocContext& context, DocContainer* owner, Doxygen::Structure::Class* type )
{
    auto* newClass = context.AddClass( owner, type );
    
    const auto& members = type->Members( );
    ProcessMembers( context, newClass, members );
}

void ProcessUnion( DocContext& context, DocContainer* owner, Doxygen::Structure::Union* type )
{
    auto* newUnion = context.AddUnion( owner, type );
    const auto& members = type->Members( );
    ProcessMembers( context, newUnion, members );
}

void ProcessInterface( DocContext& context, DocContainer* owner, Doxygen::Structure::Interface* type )
{
    auto* newInterface = context.AddInterface( owner, type );
    const auto& members = type->Members( );
    ProcessMembers( context, newInterface, members );
}

void ProcessModule( DocContext& context, DocContainer* owner, Doxygen::Structure::Module* mod )
{
    auto* newModule = context.AddModule( owner, mod );
    const auto& members = mod->Members( );
    ProcessMembers( context, newModule, members );
}

void ProcessConcept( DocContext& context, DocContainer* owner, Doxygen::Structure::Concept* cpt )
{
    auto* newConcept = context.AddConcept( owner, cpt );
    const auto& members = cpt->Members( );
    ProcessMembers( context, newConcept, members );
}

void ProcessFunction( DocContext& context, DocContainer* owner, Doxygen::Structure::Function* func )
{
    auto* newFunction = context.AddFunction( owner, func );
    const auto& members = func->Members( );
    ProcessMembers( context, newFunction, members );
}

void ProcessFunctionOverload( DocContext& context, DocContainer* owner, Doxygen::Structure::FunctionOverload* functionOverload )
{
    auto* newFunctionOverload = context.AddFunctionOverload( owner, functionOverload );
    
}

void ProcessEnum( DocContext& context, DocContainer* owner, Doxygen::Structure::Enum* type )
{
    auto* newEnum = context.AddEnum( owner, type );
    const auto& members = type->Members( );
    ProcessMembers( context, newEnum, members );
}

void ProcessDefine( DocContext& context, DocContainer* owner, Doxygen::Structure::Define* def )
{
    PrintLn( "Define: {} -> {}", def->Name( ), def->QualifiedName( ) );
}

void ProcessProperty( DocContext& context, DocContainer* owner, Doxygen::Structure::Property* prop )
{
    PrintLn( "Property: {} -> {}", prop->Name( ), prop->QualifiedName( ) );
}

void ProcessEvent( DocContext& context, DocContainer* owner, Doxygen::Structure::Event* evt )
{
    PrintLn( "Event: {} -> {}", evt->Name( ), evt->QualifiedName( ) );
}

void ProcessVariable( DocContext& context, DocContainer* owner, Doxygen::Structure::Variable* var )
{
    context.AddVariable( owner, var );
    //const auto& members = var->Members( );
    //ProcessMembers( context, newVariable, members );
}

void ProcessTypedef( DocContext& context, DocContainer* owner, Doxygen::Structure::Typedef* type )
{
    context.AddTypedef( owner, type );
}

void ProcessSignal( DocContext& context, DocContainer* owner, Doxygen::Structure::Signal* s )
{
    PrintLn( "Signal: {} -> {}", s->Name( ), s->QualifiedName( ) );
}

void ProcessPrototype( DocContext& context, DocContainer* owner, Doxygen::Structure::Prototype* p )
{
    PrintLn( "Prototype: {} -> {}", p->Name( ), p->QualifiedName( ) );
}

void ProcessFriend( DocContext& context, DocContainer* owner, Doxygen::Structure::Friend* frnd )
{
    PrintLn( "Friend: {} -> {}", frnd->Name( ), frnd->QualifiedName( ) );
}

void ProcessDCop( DocContext& context, DocContainer* owner, Doxygen::Structure::DCop* dcop )
{
    PrintLn( "DCop: {} -> {}", dcop->Name( ), dcop->QualifiedName( ) );
}

void ProcessSlot( DocContext& context, DocContainer* owner, Doxygen::Structure::Slot* slot )
{
    PrintLn( "Slot: {} -> {}", slot->Name( ), slot->QualifiedName( ) );
}

void ProcessInterfaceReference( DocContext& context, DocContainer* owner, Doxygen::Structure::InterfaceReference* ir )
{
    PrintLn( "InterfaceReference: {} -> {}", ir->Name( ), ir->QualifiedName( ) );
}

void ProcessService( DocContext& context, DocContainer* owner, Doxygen::Structure::Service* service )
{
    PrintLn( "Service: {} -> {}", service->Name( ), service->QualifiedName( ) );
}


void ProcessMember( DocContext& context, DocContainer* owner, Doxygen::Structure::Member* member )
{
    using MemberType = Doxygen::Structure::MemberType;
    auto memberType = member->MemberType( );

    switch ( memberType )
    {
        case MemberType::Namespace:
            ProcessNamespace( context, owner, static_cast< Doxygen::Structure::Namespace* >( member ) );
            break;
        case MemberType::Struct:
            ProcessStruct( context, owner, static_cast< Doxygen::Structure::Struct* >( member ) );
            break;
        case MemberType::Class:
            ProcessClass( context, owner, static_cast< Doxygen::Structure::Class* >( member ) );
            break;
        case MemberType::Union:
            ProcessUnion( context, owner, static_cast< Doxygen::Structure::Union* >( member ) );
            break;
        case MemberType::Interface:
            ProcessInterface( context, owner, static_cast< Doxygen::Structure::Interface* >( member ) );
            break;
        case MemberType::Module:
            ProcessModule( context, owner, static_cast< Doxygen::Structure::Module* >( member ) );
            break;
        case MemberType::Concept:
            ProcessConcept( context, owner, static_cast< Doxygen::Structure::Concept* >( member ) );
            break;
        case MemberType::Function:
            ProcessFunction( context, owner, static_cast< Doxygen::Structure::Function* >( member ) );
            break;
        case MemberType::FunctionOverload:
            ProcessFunctionOverload( context, owner, static_cast< Doxygen::Structure::FunctionOverload* >( member ) );
            break;
        case MemberType::Enum:
            ProcessEnum( context, owner, static_cast< Doxygen::Structure::Enum* >( member ) );
            break;
        case MemberType::Define:
            ProcessDefine( context, owner, static_cast< Doxygen::Structure::Define* >( member ) );
            break;
        case MemberType::Property:
            ProcessProperty( context, owner, static_cast< Doxygen::Structure::Property* >( member ) );
            break;
        case MemberType::Event:
            ProcessEvent( context, owner, static_cast< Doxygen::Structure::Event* >( member ) );
            break;
        case MemberType::Variable:
            ProcessVariable( context, owner, static_cast< Doxygen::Structure::Variable* >( member ) );
            break;
        case MemberType::Typedef:
            ProcessTypedef( context, owner, static_cast< Doxygen::Structure::Typedef* >( member ) );
            break;
        case MemberType::Signal:
            ProcessSignal( context, owner, static_cast< Doxygen::Structure::Signal* >( member ) );
            break;
        case MemberType::Prototype:
            ProcessPrototype( context, owner, static_cast< Doxygen::Structure::Prototype* >( member ) );
            break;
        case MemberType::Friend:
            ProcessFriend( context, owner, static_cast< Doxygen::Structure::Friend* >( member ) );
            break;
        case MemberType::DCop:
            ProcessDCop( context, owner, static_cast< Doxygen::Structure::DCop* >( member ) );
            break;
        case MemberType::Slot:
            ProcessSlot( context, owner, static_cast< Doxygen::Structure::Slot* >( member ) );
            break;
        case MemberType::InterfaceReference:
            ProcessInterfaceReference( context, owner, static_cast< Doxygen::Structure::InterfaceReference* >( member ) );
            break;
        case MemberType::Service:
            ProcessService( context, owner, static_cast< Doxygen::Structure::Service* >( member ) );
            break;
    }
}


void ProcessMembers( DocContext& context, DocContainer* owner, const std::vector<Doxygen::Structure::Member*>& members )
{
    for ( auto member : members )
    {
        ProcessMember( context, owner, member );
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

        DocContext context( options );

        auto globalNamespace = typeSystem->GlobalNamespace( );
        auto globalDocNamespace = context.AddNamespace(nullptr, globalNamespace );

        const auto& globalNamespaceMembers = globalNamespace->Members( );

        
        ProcessMembers( context, globalDocNamespace, globalNamespaceMembers );

        auto& allNamespacesByQualifiedName = typeSystem->AllNamespacesByQualifiedName( );
        auto& allContextNamespaces = context.AllNamespacesByQualifiedName( );

        PrintLn( "Namespaces:{}", allNamespacesByQualifiedName.size( ) );
        PrintLn( "Namespaces:{}", allContextNamespaces.size( ) );

        for ( const auto& entry : allNamespacesByQualifiedName )
        {
            auto member = entry.second;
            const auto& memberQualifiedName = member->QualifiedName( );

            auto it = allContextNamespaces.find( memberQualifiedName );
            if ( it == allContextNamespaces.end( ) )
            {
                auto root = member->Root( );
                const auto& rootId = root->Id( );
                auto path = member->Path( );
                auto owner = member->Owner( );
                auto memberMemberType = to_string( member->MemberType( ) );
                auto ownerMemberType = owner ? to_string( owner->MemberType( ) ) : std::string("<no owner>");
                auto rootIsGlobalNamespace = globalNamespace == root;
                PrintLn( "Missing {}, Path {} {} {} {} {}", memberQualifiedName, path, memberMemberType, ownerMemberType, rootId, rootIsGlobalNamespace );
                //PrintLn( "Missing {}, {}", memberQualifiedName, rootIsGlobalNamespace );

            }
        }


        
        auto& allFunctionsByQualifiedName = typeSystem->AllFunctionsByQualifiedName( );
        auto& allContextFunctionsByQualifiedName = context.AllFunctionsByQualifiedName( );

        PrintLn( "Function names:{}", allFunctionsByQualifiedName.size( ) );
        PrintLn( "Function names:{}", allContextFunctionsByQualifiedName.size( ) );
        /*
        for ( const auto& entry : allFunctions )
        {
            auto function = entry.second;
            const auto& functionQualifiedName = function->QualifiedName( );
            
            auto it = allContextFunctions.find( functionQualifiedName );
            if ( it == allContextFunctions.end( ) )
            {
                auto root = function->Root( );
                const auto& rootId = root->Id( );
                auto path = function->Path( );
                auto owner = function->Owner( );
                auto functionMemberType = to_string( function->MemberType( ) );
                auto ownerMemberType = to_string( owner->MemberType( ) );
                auto rootIsGlobalNamespace = globalNamespace == root;
                //PrintLn( "Missing {}, Path {} {} {} {} {}", functionQualifiedName, path, functionMemberType, ownerMemberType, rootId, rootIsGlobalNamespace );
                PrintLn( "Missing {}, {}", functionQualifiedName, rootIsGlobalNamespace );
                
            }
        }
        */

        size_t functionImplementations = 0;
        for ( const auto& entry : allFunctionsByQualifiedName )
        {
            auto* funtion = entry.second;
            const auto& overloads = funtion->Members( );
            functionImplementations += overloads.size( );
        }   
        PrintLn( "Functions implemented:{}", functionImplementations );
        PrintLn( "Functions implemented:{}", context.AllFunctionOverloadsById( ).size( ) );
        

        auto documentCount = documentCollection.size( );



    }


}

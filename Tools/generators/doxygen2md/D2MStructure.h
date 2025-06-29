#pragma once
#ifndef D2MSTRUCTURE_H_
#define D2MSTRUCTURE_H_

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
#include <HCCString.h>
#include "doxygen2mdOptions.h"

namespace Doxygen2Md
{
    
    using namespace Harlinn::Common;
    using namespace Harlinn::Common::Core;

    class DocMember;
    class DocContainer;
    class DocTypeContainer;
    class DocNamespace;
    template<typename DerivedT>
    class DocStructOrClass;
    class DocStruct;
    class DocClass;
    class DocUnion;
    class DocInterface;
    class DocEnum;
    class DocConcept;
    class DocModule;
    class DocFunction;
    class DocFunctionOverload;
    class DocDefine;
    class DocProperty;
    class DocEvent;
    class DocVariable;
    class DocTypedef;
    class DocSignal;
    class DocPrototype;
    class DocFriend;


    class DocContext
    {
        Doxygen2MdOptions& options_;
        std::vector<std::unique_ptr<DocMember>> all_;
        std::unordered_map<std::string, DocNamespace*> allNamespacesById_;
        std::unordered_map<std::string, DocNamespace*> allNamespacesByQualifiedName_;
        std::unordered_map<std::string, DocMember*> allTypesById_;
        std::unordered_map<std::string, DocMember*> allTypesByQualifiedName_;
        std::unordered_map<std::string, DocFunction*> allFunctionsByQualifiedName_;
        std::unordered_map<std::string, DocFunctionOverload*> allFunctionOverloadsById_;
        std::unordered_map<std::string, DocFunctionOverload*> allFunctionOverloadsByQualifiedNameAndArgsString_;
    public:
        DocContext( Doxygen2MdOptions& options )
            : options_( options )
        {
        }

        Doxygen2MdOptions& Options( ) const
        {
            return options_;
        }

        template<typename D, typename T>
        inline D* Add( DocContainer* owner, T* member );

        template<typename D, typename T>
        D* AddType( DocContainer* owner, T* member )
        {
            auto* result = Add<D>( owner, member );
            const auto& qualifiedName = result->QualifiedName( );
            allTypesByQualifiedName_.emplace( qualifiedName, result );
            allTypesById_.emplace( member->Id( ), result );
            return result;
        }

        const std::unordered_map<std::string, DocNamespace*>& AllNamespacesById( ) const { return allNamespacesById_; }
        const std::unordered_map<std::string, DocNamespace*>& AllNamespacesByQualifiedName( ) const { return allNamespacesByQualifiedName_; }
        const std::unordered_map<std::string, DocMember*>& AllTypesById( ) const { return allTypesById_; }
        const std::unordered_map<std::string, DocMember*>& AllTypesByQualifiedName( ) const { return allTypesByQualifiedName_; }
        const std::unordered_map<std::string, DocFunction*>& AllFunctionsByQualifiedName( ) const { return allFunctionsByQualifiedName_; }
        const std::unordered_map<std::string, DocFunctionOverload*>& AllFunctionOverloadsById( ) const { return allFunctionOverloadsById_; }
        const std::unordered_map<std::string, DocFunctionOverload*>& AllFunctionOverloadsByQualifiedNameAndArgsString( ) const { return allFunctionOverloadsByQualifiedNameAndArgsString_; }

    private:
        template<typename T>
        static T* Find( const std::unordered_map<std::string, T*>& map, const std::string& key )
        {
            auto it = map.find( key );
            if ( it != map.end( ) )
            {
                return it->second;
            }
            return nullptr;
        }
    public:
        DocNamespace* FindNamespaceById( const std::string& id ) const
        {
            return Find( allNamespacesById_, id );
        }
        DocNamespace* FindNamespaceByQualifiedName( const std::string& qualifiedName ) const
        {
            return Find( allNamespacesByQualifiedName_, qualifiedName );
        }

        DocMember* FindTypeById( const std::string& id ) const
        {
            return Find( allTypesById_, id );
        }
        DocMember* FindTypeByQualifiedName( const std::string& qualifiedName ) const
        {
            return Find( allTypesByQualifiedName_, qualifiedName );
        }
        DocFunction* FindFunctionByQualifiedName( const std::string& qualifiedName ) const
        {
            return Find( allFunctionsByQualifiedName_, qualifiedName );
        }
        DocFunctionOverload* FindFunctionOverloadById( const std::string& id ) const
        {
            return Find( allFunctionOverloadsById_, id );
        }
        DocFunctionOverload* FindFunctionOverloadByQualifiedNameAndArgsString( const std::string& qualifiedNameAndArgsString ) const
        {
            return Find( allFunctionOverloadsByQualifiedNameAndArgsString_, qualifiedNameAndArgsString );
        }


        inline DocNamespace* AddNamespace( DocContainer* owner, Doxygen::Structure::Namespace* nspace );
        inline DocStruct* AddStruct( DocContainer* owner, Doxygen::Structure::Struct* type );
        inline DocClass* AddClass( DocContainer* owner, Doxygen::Structure::Class* type );
        inline DocUnion* AddUnion( DocContainer* owner, Doxygen::Structure::Union* type );
        inline DocInterface* AddInterface( DocContainer* owner, Doxygen::Structure::Interface* type );
        inline DocEnum* AddEnum( DocContainer* owner, Doxygen::Structure::Enum* type );
        inline DocConcept* AddConcept( DocContainer* owner, Doxygen::Structure::Concept* cpt );
        inline DocModule* AddModule( DocContainer* owner, Doxygen::Structure::Module* module );
        inline DocFunction* AddFunction( DocContainer* owner, Doxygen::Structure::Function* function );
        inline DocFunctionOverload* AddFunctionOverload( DocContainer* owner, Doxygen::Structure::FunctionOverload* functionOverload );
        inline DocDefine* AddDefine( DocContainer* owner, Doxygen::Structure::Define* define );
        inline DocProperty* AddProperty( DocContainer* owner, Doxygen::Structure::Property* property );
        inline DocEvent* AddEvent( DocContainer* owner, Doxygen::Structure::Event* property );
        inline DocVariable* AddVariable( DocContainer* owner, Doxygen::Structure::Variable* variable );
        inline DocTypedef* AddTypedef( DocContainer* owner, Doxygen::Structure::Typedef* typeDef );
        inline DocSignal* AddSignal( DocContainer* owner, Doxygen::Structure::Signal* signal );
        inline DocPrototype* AddPrototype( DocContainer* owner, Doxygen::Structure::Prototype* prototype );
        inline DocFriend* AddFriend( DocContainer* owner, Doxygen::Structure::Friend* frnd );



    };

    class DocContainer;

    class DocMember
    {
    public:

    private:
        DocContext& context_;
        DocContainer* owner_;
        Doxygen::Structure::Member* member_;
    public:
        DocMember( DocContext& context, DocContainer* owner, Doxygen::Structure::Member* member )
            : context_( context ), owner_( owner ), member_( member )
        {
        }

        virtual ~DocMember( ) = default;

        Doxygen::Structure::Member* Member( ) const
        {
            return member_;
        }

        Doxygen::Structure::MemberType MemberType( ) const
        {
            return member_->MemberType( );
        }

        DocContainer* Owner( ) const
        {
            return owner_;
        }

        const std::string& Name( ) const
        {
            return member_->Name( );
        }
        const std::string& QualifiedName( ) const
        {
            return member_->QualifiedName( );
        }
        const std::string& Id( ) const
        {
            return member_->Id( );
        }

    };


    class DocContainer : public DocMember
    {
        std::vector<DocMember*> members_;
        std::unordered_map<std::string, DocMember*> membersByName_;
    public:
        using Base = DocMember;

        DocContainer( DocContext& context, DocContainer* owner, Doxygen::Structure::Container* container )
            : Base( context, owner, container )
        {
        }


        Doxygen::Structure::Container* Container( ) const
        {
            return static_cast< Doxygen::Structure::Container* >( Base::Member( ) );
        }

        const std::vector<DocMember*>& Members( ) const { return members_; }
        const std::unordered_map<std::string, DocMember*>& MembersByName( ) const { return membersByName_; }

        virtual void Add( DocMember* member, const std::string& name )
        {
            assert( member != nullptr );
            if ( !membersByName_.contains( name ) )
            {
                membersByName_.emplace( name, member );
                members_.emplace_back( member );
            }
        }

        virtual void Add( DocMember* member )
        {
            assert( member != nullptr );
            Add( member, member->Name( ) );
        }




    };

    class DocTypeContainer : public DocContainer
    {
    public:
        using Base = DocContainer;

        DocTypeContainer( DocContext& context, DocContainer* owner, Doxygen::Structure::TypeContainer* typeContainer )
            : Base( context, owner, typeContainer )
        {
        }

        Doxygen::Structure::TypeContainer* TypeContainer( ) const
        {
            return static_cast< Doxygen::Structure::TypeContainer* >( Base::Member( ) );
        }

    };


    class DocNamespace : public DocTypeContainer
    {
    public:
        using Base = DocTypeContainer;

        DocNamespace( DocContext& context, DocContainer* owner, Doxygen::Structure::Namespace* nspace )
            : Base( context, owner, nspace )
        {
        }

        Doxygen::Structure::Namespace* Namespace( ) const
        {
            return static_cast< Doxygen::Structure::Namespace* >( Base::Member( ) );
        }

    };

    template<typename DerivedT>
    class DocStructOrClass : public DocTypeContainer
    {
    public:
        using Base = DocTypeContainer;
        using DerivedType = DerivedT;

        DocStructOrClass( DocContext& context, DocContainer* owner, Doxygen::Structure::TypeContainer* typeContainer )
            : Base( context, owner, typeContainer )
        {
        }
    };

    class DocStruct : public DocStructOrClass<DocStruct>
    {
    public:
        using Base = DocStructOrClass<DocStruct>;

        DocStruct( DocContext& context, DocContainer* owner, Doxygen::Structure::Struct* type )
            : Base( context, owner, type )
        {
        }

        Doxygen::Structure::Struct* Struct( ) const
        {
            return static_cast< Doxygen::Structure::Struct* >( Base::Member( ) );
        }
    };

    class DocClass : public DocStructOrClass<DocClass>
    {
    public:
        using Base = DocStructOrClass<DocClass>;

        DocClass( DocContext& context, DocContainer* owner, Doxygen::Structure::Class* type )
            : Base( context, owner, type )
        {
        }

        Doxygen::Structure::Class* Class( ) const
        {
            return static_cast< Doxygen::Structure::Class* >( Base::Member( ) );
        }

    };

    class DocUnion : public DocTypeContainer
    {
    public:
        using Base = DocTypeContainer;

        DocUnion( DocContext& context, DocContainer* owner, Doxygen::Structure::Union* type )
            : Base( context, owner, type )
        {
        }

        Doxygen::Structure::Union* Union( ) const
        {
            return static_cast< Doxygen::Structure::Union* >( Base::Member( ) );
        }
    };

    class DocInterface : public DocTypeContainer
    {
    public:
        using Base = DocTypeContainer;

        DocInterface( DocContext& context, DocContainer* owner, Doxygen::Structure::Interface* type )
            : Base( context, owner, type )
        {
        }

        Doxygen::Structure::Interface* Interface( ) const
        {
            return static_cast< Doxygen::Structure::Interface* >( Base::Member( ) );
        }
    };

    class DocEnum : public DocContainer
    {
    public:
        using Base = DocContainer;

        DocEnum( DocContext& context, DocContainer* owner, Doxygen::Structure::Enum* type )
            : Base( context, owner, type )
        {
        }

        Doxygen::Structure::Enum* Enum( ) const
        {
            return static_cast< Doxygen::Structure::Enum* >( Base::Member( ) );
        }
    };

    class DocConcept : public DocTypeContainer
    {
    public:
        using Base = DocTypeContainer;

        DocConcept( DocContext& context, DocContainer* owner, Doxygen::Structure::Concept* cpt )
            : Base( context, owner, cpt )
        {
        }

        Doxygen::Structure::Concept* Concept( ) const
        {
            return static_cast< Doxygen::Structure::Concept* >( Base::Member( ) );
        }
    };

    class DocModule : public DocTypeContainer
    {
    public:
        using Base = DocTypeContainer;

        DocModule( DocContext& context, DocContainer* owner, Doxygen::Structure::Module* module )
            : Base( context, owner, module )
        {
        }

        Doxygen::Structure::Module* Module( ) const
        {
            return static_cast< Doxygen::Structure::Module* >( Base::Member( ) );
        }
    };

    class DocFunction : public DocContainer
    {
    public:
        using Base = DocContainer;

        DocFunction( DocContext& context, DocContainer* owner, Doxygen::Structure::Function* function )
            : Base( context, owner, function )
        {
        }

        Doxygen::Structure::Function* Function( ) const
        {
            return static_cast< Doxygen::Structure::Function* >( Base::Member( ) );
        }
    };


    class DocFunctionOverload : public DocMember
    {
    public:
        using Base = DocMember;

        DocFunctionOverload( DocContext& context, DocContainer* owner, Doxygen::Structure::FunctionOverload* functionOverload )
            : Base( context, owner, functionOverload )
        {
        }

        Doxygen::Structure::FunctionOverload* FunctionOverload( ) const
        {
            return static_cast< Doxygen::Structure::FunctionOverload* >( Base::Member( ) );
        }
    };

    class DocDefine : public DocMember
    {
    public:
        using Base = DocMember;

        DocDefine( DocContext& context, DocContainer* owner, Doxygen::Structure::Define* define )
            : Base( context, owner, define )
        {
        }

        Doxygen::Structure::Define* Define( ) const
        {
            return static_cast< Doxygen::Structure::Define* >( Base::Member( ) );
        }
    };

    class DocProperty : public DocMember
    {
    public:
        using Base = DocMember;

        DocProperty( DocContext& context, DocContainer* owner, Doxygen::Structure::Property* property )
            : Base( context, owner, property )
        {
        }

        Doxygen::Structure::Property* Property( ) const
        {
            return static_cast< Doxygen::Structure::Property* >( Base::Member( ) );
        }
    };

    class DocEvent : public DocMember
    {
    public:
        using Base = DocMember;

        DocEvent( DocContext& context, DocContainer* owner, Doxygen::Structure::Event* property )
            : Base( context, owner, property )
        {
        }

        Doxygen::Structure::Event* Event( ) const
        {
            return static_cast< Doxygen::Structure::Event* >( Base::Member( ) );
        }
    };

    class DocVariable : public DocMember
    {
    public:
        using Base = DocMember;

        DocVariable( DocContext& context, DocContainer* owner, Doxygen::Structure::Variable* variable )
            : Base( context, owner, variable )
        {
        }

        Doxygen::Structure::Variable* Variable( ) const
        {
            return static_cast< Doxygen::Structure::Variable* >( Base::Member( ) );
        }

    };

    class DocTypedef : public DocMember
    {
    public:
        using Base = DocMember;

        DocTypedef( DocContext& context, DocContainer* owner, Doxygen::Structure::Typedef* typeDef )
            : Base( context, owner, typeDef )
        {
        }

        Doxygen::Structure::Typedef* Typedef( ) const
        {
            return static_cast< Doxygen::Structure::Typedef* >( Base::Member( ) );
        }

    };

    class DocSignal : public DocMember
    {
    public:
        using Base = DocMember;

        DocSignal( DocContext& context, DocContainer* owner, Doxygen::Structure::Signal* signal )
            : Base( context, owner, signal )
        {
        }

        Doxygen::Structure::Signal* Signal( ) const
        {
            return static_cast< Doxygen::Structure::Signal* >( Base::Member( ) );
        }

    };

    class DocPrototype : public DocMember
    {
    public:
        using Base = DocMember;

        DocPrototype( DocContext& context, DocContainer* owner, Doxygen::Structure::Prototype* prototype )
            : Base( context, owner, prototype )
        {
        }

        Doxygen::Structure::Prototype* Prototype( ) const
        {
            return static_cast< Doxygen::Structure::Prototype* >( Base::Member( ) );
        }

    };

    class DocFriend : public DocMember
    {
    public:
        using Base = DocMember;

        DocFriend( DocContext& context, DocContainer* owner, Doxygen::Structure::Friend* frnd )
            : Base( context, owner, frnd )
        {
        }

        Doxygen::Structure::Friend* Friend( ) const
        {
            return static_cast< Doxygen::Structure::Friend* >( Base::Member( ) );
        }
    };

    template<typename D, typename T>
    inline D* DocContext::Add( DocContainer* owner, T* member )
    {
        auto ptr = std::make_unique<D>( *this, owner, member );
        auto* result = ptr.get( );
        all_.emplace_back( std::move( ptr ) );
        if ( owner )
        {
            owner->Add( result );
        }
        return result;
    }


    inline DocNamespace* DocContext::AddNamespace( DocContainer* owner, Doxygen::Structure::Namespace* nspace )
    {
        auto* result = Add<DocNamespace, Doxygen::Structure::Namespace>( owner, nspace );
        const auto qualifiedName = result->QualifiedName( );
        const auto id = nspace->Id( );
        allNamespacesByQualifiedName_.emplace( qualifiedName, result );
        allNamespacesById_.emplace( id, result );
        return result;
    }
    inline DocStruct* DocContext::AddStruct( DocContainer* owner, Doxygen::Structure::Struct* type )
    {
        return AddType<DocStruct, Doxygen::Structure::Struct>( owner, type );
    }
    inline DocClass* DocContext::AddClass( DocContainer* owner, Doxygen::Structure::Class* type )
    {
        return AddType<DocClass, Doxygen::Structure::Class>( owner, type );
    }
    inline DocUnion* DocContext::AddUnion( DocContainer* owner, Doxygen::Structure::Union* type )
    {
        return AddType<DocUnion, Doxygen::Structure::Union>( owner, type );
    }
    inline DocInterface* DocContext::AddInterface( DocContainer* owner, Doxygen::Structure::Interface* type )
    {
        return AddType<DocInterface, Doxygen::Structure::Interface>( owner, type );
    }
    inline DocEnum* DocContext::AddEnum( DocContainer* owner, Doxygen::Structure::Enum* type )
    {
        return AddType<DocEnum, Doxygen::Structure::Enum>( owner, type );
    }
    inline DocConcept* DocContext::AddConcept( DocContainer* owner, Doxygen::Structure::Concept* cpt )
    {
        return Add<DocConcept, Doxygen::Structure::Concept>( owner, cpt );
    }
    inline DocModule* DocContext::AddModule( DocContainer* owner, Doxygen::Structure::Module* module )
    {
        return Add<DocModule, Doxygen::Structure::Module>( owner, module );
    }
    inline DocFunction* DocContext::AddFunction( DocContainer* owner, Doxygen::Structure::Function* function )
    {
        auto* result = Add<DocFunction, Doxygen::Structure::Function>( owner, function );
        const auto& qualifiedName = result->QualifiedName( );
        allFunctionsByQualifiedName_.emplace( qualifiedName, result );
        return result;
    }

    inline DocFunctionOverload* DocContext::AddFunctionOverload( DocContainer* owner, Doxygen::Structure::FunctionOverload* functionOverload )
    {
        auto ptr = std::make_unique<DocFunctionOverload>( *this, owner, functionOverload );
        auto* result = ptr.get( );
        all_.emplace_back( std::move( ptr ) );
        if ( owner )
        {
            owner->Add( result, functionOverload->ArgsString( ) );
        }
        const auto& qualifiedName = functionOverload->QualifiedName( );
        const auto& argsString = functionOverload->ArgsString( );
        std::string qualifiedNameAndArgsString = qualifiedName + argsString;
        allFunctionOverloadsByQualifiedNameAndArgsString_.emplace( qualifiedNameAndArgsString, result );
        allFunctionOverloadsById_.emplace( functionOverload->Id( ), result );
        return result;
    }

    inline DocDefine* DocContext::AddDefine( DocContainer* owner, Doxygen::Structure::Define* define )
    {
        return Add<DocDefine, Doxygen::Structure::Define>( owner, define );
    }
    inline DocProperty* DocContext::AddProperty( DocContainer* owner, Doxygen::Structure::Property* property )
    {
        return Add<DocProperty, Doxygen::Structure::Property>( owner, property );
    }
    inline DocEvent* DocContext::AddEvent( DocContainer* owner, Doxygen::Structure::Event* event )
    {
        return Add<DocEvent, Doxygen::Structure::Event>( owner, event );
    }
    inline DocVariable* DocContext::AddVariable( DocContainer* owner, Doxygen::Structure::Variable* variable )
    {
        return Add<DocVariable>( owner, variable );
    }
    inline DocTypedef* DocContext::AddTypedef( DocContainer* owner, Doxygen::Structure::Typedef* typeDef )
    {
        return AddType<DocTypedef>( owner, typeDef );
    }
    inline DocSignal* DocContext::AddSignal( DocContainer* owner, Doxygen::Structure::Signal* signal )
    {
        return Add<DocSignal>( owner, signal );
    }
    inline DocPrototype* DocContext::AddPrototype( DocContainer* owner, Doxygen::Structure::Prototype* prototype )
    {
        return Add<DocPrototype>( owner, prototype );
    }
    inline DocFriend* DocContext::AddFriend( DocContainer* owner, Doxygen::Structure::Friend* frnd )
    {
        return Add<DocFriend>( owner, frnd );
    }


}


#endif

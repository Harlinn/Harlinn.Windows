#pragma once
#ifndef HARLINN_CIMTOOLTYPES_H_
#define HARLINN_CIMTOOLTYPES_H_

/*
   Copyright 2024-2026 Espen Harlinn

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


#include "HWImGui.h"
#include "HCCwbem.h"
#include "HCCEnvironment.h"
#include "HCCString.h"

namespace hcc
{
    using namespace Harlinn::Common;
    using namespace Harlinn::Common::Core;
}
namespace hw = Harlinn::Windows;

namespace Harlinn::CIMTool
{
    using Guid = hcc::Guid;
    using TimeSpan = hcc::TimeSpan;
    using DateTime = hcc::DateTime;
    using Int16 = hcc::Int16;
    using Int32 = hcc::Int32;
    using Int64 = hcc::Int64;
    using UInt16 = hcc::UInt16;
    using UInt32 = hcc::UInt32;
    using UInt64 = hcc::UInt64;
    using Single = hcc::Single;
    using Double = hcc::Double;

    class Command;
    class Renderable
    {
        Renderable* owner_;
    public:
        explicit Renderable( Renderable* owner )
            : owner_( owner )
        { }

        virtual ~Renderable( )
        { }

        Renderable* Owner( ) const
        {
            return owner_;
        }

        virtual void Render( ) = 0;
        virtual Command* GetCommand( const Guid& commandId ) const
        {
            if ( owner_ )
            {
                return owner_->GetCommand( commandId );
            }
            else
            {
                return nullptr;
            }
        }
    };


    enum class ThreeState : Int32
    {
        Unknown = -1,
        False = 0,
        True = 1
    };
    class TreeNode : public Renderable
    {
    public:
        using Base = Renderable;
    private:
        ThreeState HasChildren = ThreeState::Unknown;
        static UInt64 nextId_;
        UInt64 id_;
        hcc::AnsiString caption_;
    public:
        TreeNode( Renderable* owner, UInt64 id, const hcc::AnsiString& caption )
            : Base( owner ), id_(id), caption_(hcc::Format("{}##%ull", caption, id ) )
        { }

        static UInt64 NextId( )
        {
            nextId_++;
            return nextId_;
        }

        virtual void Render( ) override
        {
            if ( ImGui::TreeNode( caption_.c_str() ) )
            {
                this->RenderChildNodes( );
                ImGui::TreePop( );
            }
        }
    protected:
        virtual void RenderChildNodes( )
        {

        }

    };
    


    class Command
    {
        Guid id_;
        hcc::AnsiString caption_;
        hcc::AnsiString shortcut_;
        hcc::AnsiString tooltip_;
        mutable bool selected_ = false;
        bool enabled_ = true;
    public:
        Command( const Guid& id, hcc::AnsiString& caption, const hcc::AnsiString& shortcut = hcc::AnsiString( ), const hcc::AnsiString& tooltip = hcc::AnsiString( ), bool selected = false, bool enabled = true )
            : id_( id ), caption_( caption ), shortcut_( shortcut ), tooltip_( tooltip ), selected_( selected ), enabled_( enabled )
        { }

        const Guid& Id( ) const
        {
            return id_;
        }
        const char* Caption( ) const
        {
            return caption_.c_str( );
        }
        const char* Shortcut( ) const
        {
            return shortcut_.empty( ) == false ? shortcut_.c_str( ) : nullptr;
        }
        const char* Tooltip( )
        {
            return tooltip_.empty( ) == false ? tooltip_.c_str( ) : nullptr;
        }
        bool Selected( ) const
        {
            return *this->GetSelectedPtr( );
        }
        bool Enabled( ) const
        {
            return enabled_;
        }

    protected:
        virtual bool* GetSelectedPtr( ) const
        {
            return &selected_;
        }
        
        


    };


    class CommandManager
    {
    public:
        using Container = std::unordered_map<Guid, std::unique_ptr<Command>>;
    private:
        Renderable* owner_;
        Container items_;
    public:
        explicit CommandManager( Renderable* owner )
            : owner_( owner )
        { }

        template<typename T = Command>
        requires std::is_base_of_v<Command,T>
        T* AddCommand( const Guid& id, hcc::AnsiString& caption, const hcc::AnsiString& shortcut = hcc::AnsiString( ), const hcc::AnsiString& tooltip = hcc::AnsiString( ), bool selected = false, bool enabled = true )
        {
            auto command = std::make_unique<T>( id, caption, shortcut, tooltip, selected, enabled );
            T* result = command.get( );
            items_.emplace( id, std::move( command ) );
            return result;
        }

        Command* GetCommand( const Guid& commandId ) const
        {
            auto it = items_.find( commandId );
            if ( it != items_.end( ) )
            {
                return it->second.get( );
            }
            else
            {
                return nullptr;
            }
        }

    };




    class Window : public Renderable
    {
    public:
        using Base = Renderable;
    private:
        bool visible_ = true;
        hcc::AnsiString caption_;
        hw::Size initialSize_;
        ImGuiWindowFlags windowFlags_;
        CommandManager commandManager_;
    public:
        Window( Renderable* owner, const hcc::AnsiString& caption, const hw::Size& initialSize, ImGuiWindowFlags windowFlags )
            : Base( owner ), caption_( caption ), initialSize_( initialSize ), windowFlags_( windowFlags ), commandManager_( this )
        { }
        virtual void Render( ) override
        {
            ImGui::SetNextWindowSize( ImVec2( initialSize_.Width(), initialSize_.Height() ), ImGuiCond_FirstUseEver );
            if ( ImGui::Begin( caption_.c_str(), &visible_, windowFlags_ ) )
            {
                this->RenderContents( );
            }
            ImGui::End( );
        }

        virtual Command* GetCommand( const Guid& commandId ) const override
        {
            auto found = commandManager_.GetCommand( commandId );
            if ( !found )
            {
                return Base::GetCommand( commandId );
            }
            return found;
        }
    protected:
        virtual void RenderContents( )
        {

        }


    };


    class MenuItem : public Renderable
    {
    public:
        using Base = Renderable;
    private:
    public:
        explicit MenuItem( Renderable* owner )
            : Base( owner )
        { }
        virtual void Render( ) override
        {
        }
    };





    class SubMenuItem : public MenuItem
    {
    public:
        using Base = MenuItem;
        using ContainerType = boost::container::small_vector<std::unique_ptr<MenuItem>, 10>;
    private:
        hcc::AnsiString caption_;
        ContainerType items_;
    public:
        explicit SubMenuItem( Renderable* owner, const hcc::AnsiString& caption )
            : Base( owner ), caption_( caption )
        {

        }

        virtual void Render( ) override
        {
            Base::Render( );
            if ( ImGui::BeginMenu( caption_.c_str( ) ) )
            {
                RenderItems( );
                ImGui::EndMenu( );
            }
        }
    protected:
        void RenderItems( )
        {
            for ( auto& item : items_ )
            {
                item->Render( );
            }
        }

    };



    class Menu : public Renderable
    {
    public:
        using Base = Renderable;
        using ContainerType = boost::container::small_vector<std::unique_ptr<MenuItem>, 10>;
    private:
        hcc::AnsiString caption_;
        ContainerType items_;
    public:
        Menu( Renderable* owner, const hcc::AnsiString& caption )
            : Base( owner ), caption_( caption )
        { }

        virtual void Render( ) override
        {
            if ( ImGui::BeginMenu( caption_.c_str() ) )
            {
                RenderItems( );
                ImGui::EndMenu( );
            }
        }


        SubMenuItem* AddSubMenuItem( const hcc::AnsiString& caption )
        {
            auto subMenuItem = std::make_unique<SubMenuItem>(this, caption );
            SubMenuItem* result = subMenuItem.get( );
            items_.emplace_back( std::move( subMenuItem ) );
            return result;
        }

    protected:
        void RenderItems( )
        {
            for ( auto& item : items_ )
            {
                item->Render( );
            }
        }
    };

    class PropertiesNode;
    class PropertyNode : public TreeNode
    {
    public:
        using Base = TreeNode;
        hcc::Variant value_;
    private:

    public:
        
    protected:
        virtual void RenderChildNodes( ) override
        {

        }


    };

    class ClassObjectNode;
    class PropertiesNode : public TreeNode
    {
    public:
        using Base = TreeNode;
    private:

    public:
        inline PropertiesNode( ClassObjectNode* owner );
    protected:
        virtual void RenderChildNodes( ) override
        {

        }
    };



    class NamespaceNode;
    class ClassObjectNode : public TreeNode
    {
    public:
        using Base = TreeNode;
        
    private:
        hcc::WbemClassObject object_;
    public:
        inline ClassObjectNode( NamespaceNode* owner, const hcc::AnsiString& name, hcc::WbemClassObject&& object );

        virtual NamespaceNode* Namespace( ) const;

    protected:
        inline ClassObjectNode( Renderable* owner, const hcc::AnsiString& name );
    protected:
        virtual void RenderChildNodes( ) override
        {

        }
    };

    inline PropertiesNode::PropertiesNode( ClassObjectNode* owner )
        : Base( owner, NextId( ), hcc::AnsiString("Properties") )
    {
    }

    class NamespaceNode : public ClassObjectNode
    {
    public:
        using Base = ClassObjectNode;
        using NamespaceContainer = std::map<hcc::AnsiString, std::unique_ptr< NamespaceNode >>;
        using ClassObjectContainer = std::map<hcc::AnsiString, std::unique_ptr< ClassObjectNode >>;
    private:
        hcc::WbemServices services_;
        bool retrievedItems_ = false;
        NamespaceContainer namespaces_;
        ClassObjectContainer items_;
    public:
        NamespaceNode( Renderable* owner, const hcc::AnsiString& serverName, hcc::WbemServices&& services )
            : Base( owner, serverName ) , services_(std::move( services ))
        {
        }
    
        NamespaceNode( NamespaceNode* owner, const hcc::AnsiString& serverName, hcc::WbemClassObject&& object, hcc::WbemServices&& services )
            : Base( owner, serverName, std::move( object ) ), services_( std::move( services ) )
        {
        }
    protected:
        void RetrieveNamespaces( )
        {
            if ( services_ )
            {
                const wchar_t* query = L"SELECT * FROM __NAMESPACE";
                auto namespaceEnum = services_.ExecQuery( query );
                while ( auto object = namespaceEnum.Next( ) )
                {
                    auto namespaceName = object.Get( L"Name" );
                    auto namespaceNameWStr = namespaceName.AsWideString( );
                    auto namespaceNameStr = hcc::ToAnsiString( namespaceNameWStr );

                    hcc::WbemServices services;
                    try
                    {
                        services = services_.OpenNamespace( namespaceNameWStr );
                    }
                    catch ( hcc::SystemException& exc )
                    {

                    }

                    auto node = std::make_unique<NamespaceNode>( this, namespaceNameStr, std::move( object ), std::move( services ) );
                    namespaces_.emplace( namespaceNameStr, std::move( node ) );
                }
            }
        }
        void RetrieveClasses( )
        {
            if ( services_ )
            {
                auto classEnum = services_.CreateClassEnum( );
                while ( auto object = classEnum.Next( ) )
                {
                    auto className = object.Get( L"__CLASS" );
                    auto classNameStr = className.AsAnsiString( );
                    auto node = std::make_unique<ClassObjectNode>( this, classNameStr, std::move( object ) );
                    items_.emplace( classNameStr, std::move( node ) );
                }
            }
        }


        void RetrieveChildren( )
        {
            if ( !retrievedItems_ )
            {
                RetrieveNamespaces( );
                RetrieveClasses( );
                retrievedItems_ = true;
            }
        }
        virtual void RenderChildNodes( ) override
        {
            Base::RenderChildNodes( );
            RetrieveChildren( );
            for ( auto& entry : namespaces_ )
            {
                entry.second->Render( );
            }
            for ( auto& entry : items_ )
            {
                entry.second->Render( );
            }
        }
    };

    inline NamespaceNode* ClassObjectNode::Namespace( ) const
    {
        return static_cast<NamespaceNode*>( Owner( ) );
    }



    class Connection : public NamespaceNode
    {
    public:
        using Base = NamespaceNode;
        using Container = std::map<hcc::AnsiString, std::unique_ptr< ClassObjectNode >>;
    private:
        
    public:

        Connection( Renderable* owner, const hcc::AnsiString& serverName, hcc::WbemServices&& root )
            : Base( owner, serverName, std::move( root ) )
        {
        }

        virtual NamespaceNode* Namespace( ) const override
        {
            return nullptr;
        }

    protected:
        

    };

    inline ClassObjectNode::ClassObjectNode( NamespaceNode* owner, const hcc::AnsiString& name, hcc::WbemClassObject&& object )
        : Base( owner, NextId( ), name ), object_( std::move( object ) )
    {
    }

    inline ClassObjectNode::ClassObjectNode( Renderable* owner, const hcc::AnsiString& name )
        : Base( owner, NextId( ), name )
    {

    }




    class ConnectionManager : public Renderable
    {
    public:
        using Base = Renderable;
        using Container = std::map<hcc::AnsiString, std::unique_ptr<Connection>>;
    private:
        hcc::WbemLocator locator_;
        Container items_;
    public:
        ConnectionManager( Renderable* owner )
            : Base( owner )
        {
            locator_ = hcc::WbemLocator::Create( );
            AddLocalConnection( );
        }
    private:
        void AddLocalConnection( )
        {
            auto computerName = hcc::ToAnsiString( hcc::Environment::ComputerName( hcc::Environment::ComputerNameFormat::NetBIOS ) );
            auto root = locator_.ConnectServer( L"ROOT" );
            hcc::Com::SetClientProxyBlanket( root );
            auto connection = std::make_unique<Connection>( this, computerName, std::move( root ) );
            items_.emplace( computerName, std::move( connection ) );
        }
    public:

        virtual void Render( ) override
        {
            for ( auto& entry : items_ )
            {
                entry.second->Render( );
            }
        }


    };


    class ExplorerWindow : public Window
    {
    public:
        using Base = Window;
    private:
        ConnectionManager connectionManager_;
    public:
        ExplorerWindow( Renderable* owner, const hw::Size& initialSize )
            : Base( owner, hcc::AnsiString("Explorer"), initialSize, ImGuiWindowFlags_None ), connectionManager_(this)
        {
        }
    protected:
        virtual void RenderContents( )
        {
            Base::RenderContents( );
            connectionManager_.Render( );
        }

    };

    class PropertiesWindow : public Window
    {
    public:
        using Base = Window;
    private:
    public:
        PropertiesWindow( Renderable* owner, const hw::Size& initialSize )
            : Base( owner, hcc::AnsiString( "Properties"), initialSize, ImGuiWindowFlags_None )
        {
        }
    protected:
        virtual void RenderContents( )
        {
            Base::RenderContents( );
        }
    };



    class FileMenu : public Menu
    {
    public:
        using Base = Menu;
    private:
    public:
        FileMenu( Renderable* owner )
            : Base( owner, hcc::AnsiString( "File") )
        {

        }
    };

    class EditMenu : public Menu
    {
    public:
        using Base = Menu;
    private:
    public:
        EditMenu( Renderable* owner )
            : Base( owner, hcc::AnsiString( "Edit" ))
        {

        }
    };

    class ViewMenu : public Menu
    {
    public:
        using Base = Menu;
    private:
    public:
        ViewMenu( Renderable* owner )
            : Base( owner, hcc::AnsiString( "View" ) )
        {

        }
    };



    class MainMenuBar : public Renderable
    {
    public:
        using Base = Renderable;
    private:
        bool visible_ = true;
        FileMenu fileMenu_;
        EditMenu editMenu_;
        ViewMenu viewMenu_;
    public:
        MainMenuBar( Renderable* owner )
            : Base( owner ),
            fileMenu_( this ),
            editMenu_( this ),
            viewMenu_( this )
        {
        }

        virtual void Render( ) override
        {
            if ( visible_ )
            {
                if ( ImGui::BeginMainMenuBar( ) )
                {
                    RenderItems( );
                    ImGui::EndMainMenuBar( );
                }
            }
        }
    protected:
        void RenderItems( )
        {
            fileMenu_.Render( );
            editMenu_.Render( );
            viewMenu_.Render( );
        }

    };


    



    class Main : public Renderable
    {
    public:
        using Base = Renderable;
    private:
        CommandManager commandManager_;
        ExplorerWindow explorerWindow_;
        PropertiesWindow propertiesWindow_;
        MainMenuBar mainMenuBar_;
    public:
        Main()
            : Base(nullptr),
              commandManager_( this ),
              explorerWindow_( this, {500,300} ),
              propertiesWindow_( this, { 500,300 } ),
              mainMenuBar_( this )
        { }

        virtual void Render( ) override
        {
            mainMenuBar_.Render( );
            explorerWindow_.Render( );
            propertiesWindow_.Render( );
        }

        virtual Command* GetCommand( const Guid& commandId ) const override
        {
            auto found = commandManager_.GetCommand( commandId );
            return found;
        }

    };



}



#endif

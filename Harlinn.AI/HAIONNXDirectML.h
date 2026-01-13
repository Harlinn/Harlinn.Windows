#pragma once
#ifndef HARLINN_AI_HAIONNXDIRECTML_H_
#define HARLINN_AI_HAIONNXDIRECTML_H_

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

#include "HAIONNX.h"
#include "HAIDirectML.h"

#include <dml_provider_factory.h>

namespace Harlinn::AI::ONNX::DirectML
{
    using namespace Harlinn::Windows::Graphics;

    enum class ComputeNodeState
    {
        Unknown,
        Uninitialized,
        Initialized
    };


    enum class ComputeNodeMessageType
    {
        Unknown,
        Stop,
        Load,
        Execute,
        Compute
    };

    /// <summary>
    /// Base message type for the ComputeNodeMessageType enumeration
    /// </summary>
    using ComputeNodeMessage = Concurrency::Messages::Message<ComputeNodeMessageType>;

    /// <summary>
    /// SimpleMessage specialized for the ComputeNodeMessageType enumeration
    /// </summary>
    template<ComputeNodeMessageType messageId>
    using SimpleComputeNodeMessage = Concurrency::Messages::SimpleMessage<ComputeNodeMessageType, messageId>;

    /// <summary>
    /// SimpleRequestMessage specialized for the ComputeNodeMessageType enumeration
    /// </summary>
    template<typename ReplyT, ComputeNodeMessageType messageId>
    using SimpleComputeNodeRequestMessage = Concurrency::Messages::SimpleRequestMessage<ReplyT, ComputeNodeMessageType, messageId>;

    /// <summary>
    /// SimpleValueMessage specialized for the ComputeNodeMessageType enumeration
    /// </summary>
    template<typename ValueT, ComputeNodeMessageType messageId>
    using ComputeNodeValueMessage = Concurrency::Messages::SimpleValueMessage<ValueT, ComputeNodeMessageType, messageId>;

    /// <summary>
    /// SimpleValueRequestMessage specialized for the ComputeNodeMessageType enumeration
    /// </summary>
    template<typename ValueT, typename ReplyT, ComputeNodeMessageType messageId>
    using SimpleComputeNodeValueRequestMessage = Concurrency::Messages::SimpleValueRequestMessage<ValueT, ReplyT, ComputeNodeMessageType, messageId>;



    using ComputeNodeStopMessage = SimpleComputeNodeMessage<ComputeNodeMessageType::Stop>;


    class Model;
    using ComputeNodeLoadMessage = SimpleComputeNodeValueRequestMessage<WideString, std::shared_ptr<Model>, ComputeNodeMessageType::Load>;

    struct ComputeMessageParams
    {
        const Binary buffer; 
        Math::Vector2f viewportSize;
    };

    using ComputeNodeComputeMessage = ComputeNodeValueMessage<ComputeMessageParams, ComputeNodeMessageType::Compute>;

    class ComputeNode;
    namespace Internal
    {
        class ComputeNodeExecuteMessageBase : public SimpleComputeNodeMessage<ComputeNodeMessageType::Execute>
        {
            ONNX::DirectML::ComputeNode* computeNode_;
        public:
            using Base = SimpleComputeNodeMessage<ComputeNodeMessageType::Execute>;
            ComputeNodeExecuteMessageBase( ONNX::DirectML::ComputeNode* computeNode )
                : computeNode_( computeNode )
            { }
            virtual void Execute( ) = 0;
        protected:
            ONNX::DirectML::ComputeNode* ComputeNode( )
            {
                return computeNode_;
            }

        };

        template<typename FunctionT>
        class ComputeNodeExecuteMessage : public ComputeNodeExecuteMessageBase
        {
            FunctionT function_;
        public:
            using Base = ComputeNodeExecuteMessageBase;
            ComputeNodeExecuteMessage( ONNX::DirectML::ComputeNode* computeNode, FunctionT&& function )
                : Base( computeNode ), function_( std::forward<FunctionT>( function ) )
            { }

            virtual void Execute( ) override
            {
                auto computeNode = ComputeNode( );
                function_( computeNode );
            }
        };
    }

    class ComputeNode;
    class Model : public ONNX::Model
    {
        std::weak_ptr<ComputeNode> computeNode_;
    public:
        using Base = ONNX::Model;
        HAI_EXPORT Model( const std::shared_ptr<ComputeNode>& computeNode, const std::shared_ptr<ONNX::Session>& session );
        HAI_EXPORT virtual void Compute( const Binary& inputTensorData, const Math::Vector2f& viewportSize ) override;
    };

    class ComputeEngine;
    class ComputeNode : public Concurrency::ActiveObject< std::shared_ptr<ComputeNodeMessage>>
    {
        friend class ComputeEngine;
    public:
        using Base = Concurrency::ActiveObject< std::shared_ptr<ComputeNodeMessage>>;
    private:
        WideString computeNodeName_;
        WideString deviceName_;
        std::weak_ptr<ComputeEngine> engine_;
        ComputeNodeState state_ = ComputeNodeState::Unknown;
        DXCore::Adapter1 adapter_;
        D3D_FEATURE_LEVEL featureLevel_ = D3D_FEATURE_LEVEL_12_1;
        D3D12::Device1 d3dDevice_;
        D3D12::CommandQueue d3dCommandQueue_;
        D3D12::CommandAllocator d3dCommandAllocator_;
        D3D12::GraphicsCommandList d3dCommandList_;
        DML::Device dmlDevice_;

        std::shared_ptr<ONNX::SessionOptions> sessionOptions_;
        std::shared_ptr<ONNX::Session> session_;
        const OrtDmlApi* ortDmlApi_ = nullptr;
        std::shared_ptr<Model> model_;
    public:
        boost::signals2::signal<void( ComputeNode* sender, Model* model )> OnComputeDone;

        HAI_EXPORT ComputeNode( const std::shared_ptr<ComputeEngine>& engine, const WideString& computeNodeName, const DXCore::Adapter1& adapter, const std::shared_ptr<ONNX::SessionOptions>& sessionOptions, D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_1 );

        void DoOnComputeDone( Model* model )
        {
            OnComputeDone( this, model );
        }

        
        const WideString& ComputeNodeName( ) const
        {
            return computeNodeName_;
        }
        const WideString& DeviceName( ) const
        {
            return deviceName_;
        }

        ComputeNodeState State( ) const
        {
            return state_;
        }
        const DXCore::Adapter1& Adapter( ) const
        {
            return adapter_;
        }
        D3D_FEATURE_LEVEL FeatureLevel( ) const
        {
            return featureLevel_;
        }
        const D3D12::Device1& Device( ) const
        {
            return d3dDevice_;
        }
        const D3D12::CommandQueue& CommandQueue( ) const
        {
            return d3dCommandQueue_;
        }
        const D3D12::CommandAllocator& CommandAllocator( ) const
        {
            return d3dCommandAllocator_;
        }
        const D3D12::GraphicsCommandList& CommandList( ) const
        {
            return d3dCommandList_;
        }
        const DML::Device& DirectMLDevice( ) const
        {
            return dmlDevice_;
        }

        const std::shared_ptr<ONNX::SessionOptions>& SessionOptions( ) const
        {
            return sessionOptions_;
        }
        std::shared_ptr<ONNX::Session> Session( ) const
        {
            return session_;
        }


        std::shared_ptr<ComputeEngine> Engine( ) const
        {
            return engine_.lock();
        }

        HAI_EXPORT std::future<std::shared_ptr<Model>> Load( const WideString& modelPath );
    protected:
        HAI_EXPORT virtual void OnLoad( const WideString& modelPath );
    public:
        template<typename T>
            requires std::is_invocable_v<T, ONNX::DirectML::ComputeNode*>
        void Run( T&& invocable )
        {
            auto message = std::make_shared< Internal::ComputeNodeExecuteMessage<T> >(this, std::forward<T>( invocable ) );
            PostMessage( message );
        }

        HAI_EXPORT void Compute( const Binary& tensorData, const Math::Vector2f& viewportSize );
    protected:
        HAI_EXPORT virtual void OnCompute( const Binary& tensorData, const Math::Vector2f& viewportSize );
    
    protected:
    
        HAI_EXPORT virtual void ProcessMessage( const MessageType& message ) override;
    

        virtual bool IsStopMessage( const MessageType& message ) const noexcept override
        {
            return message->MessageType( ) == ComputeNodeMessageType::Stop;
        }
        virtual void PostStopMessage( ) override
        {
            auto message = std::make_shared< ComputeNodeStopMessage >( );
            PostMessage( message );
        }

        

    private:
        HAI_EXPORT void Initialize( );
        
    };

    class ComputeEngine : public std::enable_shared_from_this<ComputeEngine>
    {
        std::shared_ptr<ONNX::Environment> environment_;
        std::shared_ptr<SessionOptions> defaultSessionOptions_;
        std::unordered_map<WideString, std::shared_ptr<ComputeNode>> computeNodes_;
    public:

        HAI_EXPORT ComputeEngine( const std::shared_ptr<SessionOptions>& defaultSessionOptions = std::make_shared<SessionOptions>( ), const Ort::ThreadingOptions& threadingOptions = {} );
        HAI_EXPORT virtual ~ComputeEngine( );

        HAI_EXPORT std::shared_ptr<ComputeNode> AddComputeNode( const WideString& computeNodeName );
        HAI_EXPORT std::shared_ptr<ComputeNode> AddComputeNode( const WideString& computeNodeName, const DXCore::Adapter1& adapter, D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_1 );
        HAI_EXPORT std::shared_ptr<ComputeNode> AddComputeNode( const WideString& computeNodeName, const DXCore::Adapter1& adapter, const std::shared_ptr<SessionOptions>& sessionOptions, D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_1 );

        const std::shared_ptr<ONNX::Environment>& Environment( ) const
        {
            return environment_;
        }

        HAI_EXPORT static DXCore::Adapter1 FindAdapter( );

    };

}

#endif

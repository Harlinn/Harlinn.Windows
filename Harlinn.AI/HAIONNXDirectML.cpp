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

#include "pch.h"
#include "HAIONNXDirectML.h"


namespace Harlinn::AI::ONNX::DirectML
{
    HAI_EXPORT ComputeNode::ComputeNode( const std::shared_ptr<ComputeEngine>& engine, const WideString& computeNodeName, const DXCore::Adapter1& adapter, const std::shared_ptr<ONNX::SessionOptions>& sessionOptions, D3D_FEATURE_LEVEL featureLevel )
        : Base( computeNodeName ), computeNodeName_( computeNodeName ), engine_( engine ), state_( ComputeNodeState::Uninitialized ), adapter_( adapter ), deviceName_( adapter.DriverDescription( ) ), sessionOptions_( sessionOptions ), featureLevel_( featureLevel )
    { }

    HAI_EXPORT void ComputeNode::ProcessMessage( const MessageType& message )
    {
        Base::ProcessMessage( message );
        auto messageType = message->MessageType( );
        switch ( messageType )
        {
            case ComputeNodeMesasgeType::Load:
            {
                auto loadMessage = static_cast< ComputeNodeLoadMessage* >( message.get( ) );
                auto fileName = loadMessage->Value( );
            }
            break;
            case ComputeNodeMesasgeType::Execute:
            {
                auto executeMessage = static_cast<Internal::ComputeNodeExecuteMessageBase*>(message.get( ));
                executeMessage->Execute( );
            }
            break;
        }
    }

    HAI_EXPORT void ComputeNode::Load( const WideString& modelPath )
    {
        if ( IO::File::Exist( modelPath ) )
        {
            auto message = std::make_shared< ComputeNodeLoadMessage >( modelPath );
            PostMessage( message );
        }
        else
        {
            HCC_THROW( ArgumentException, Format( L"The file `{}` does not exist.", modelPath ), L"modelPath" );
        }
    }
    HAI_EXPORT void ComputeNode::OnLoad( const WideString& modelPath )
    {
        auto engine = Engine( );
        auto environment = engine->Environment( );
#ifdef _DEBUG
        auto stopwatch = Stopwatch::StartNew( );
#endif
        session_ = std::make_shared<ONNX::Session>( environment, modelPath.c_str( ), *sessionOptions_.get() );
#ifdef _DEBUG
        stopwatch.Stop( );
        auto duration = stopwatch.TotalSeconds( );
        PrintLn( L"Loaded {} in {} seconds.", modelPath, duration );
#endif
    }



    HAI_EXPORT void ComputeNode::Initialize( )
    {
        if ( state_ != ComputeNodeState::Initialized )
        {
            auto d3dDevice = D3D12::CreateDevice<D3D12::Device14>( adapter_, featureLevel_ );

            // Create the DML Device and D3D12 Command Queue

            D3D12::CommandQueueDesc queueDesc = {};
            queueDesc.Type = D3D12::CommandListType::Compute;
            auto commandQueue = d3dDevice.CreateCommandQueue( queueDesc );

            auto commandAllocator = d3dDevice.CreateCommandAllocator( D3D12_COMMAND_LIST_TYPE_COMPUTE );
            auto commandList = d3dDevice.CreateCommandList( 0, D3D12_COMMAND_LIST_TYPE_COMPUTE, commandAllocator );

            auto dmlDevice = DML::CreateDevice1( d3dDevice, DML::FeatureLevel::_6_0 );

            d3dDevice_ = std::move( d3dDevice );
            d3dCommandQueue_ = std::move( commandQueue );
            d3dCommandAllocator_ = std::move( commandAllocator );
            d3dCommandList_ = std::move( commandList );
            dmlDevice_ = std::move( dmlDevice );

            const OrtApi& ortApi = Ort::GetApi( );
            ortDmlApi_ = nullptr;
            Ort::ThrowOnError( ortApi.GetExecutionProviderApi( "DML", ORT_API_VERSION, reinterpret_cast< const void** >( &ortDmlApi_ ) ) );
            Ort::ThrowOnError( ortDmlApi_->SessionOptionsAppendExecutionProvider_DML1( sessionOptions_->Impl( ), dmlDevice_.GetInterfacePointer<IDMLDevice>( ), d3dCommandQueue_.GetInterfacePointer<ID3D12CommandQueue>( ) ) );


            state_ = ComputeNodeState::Initialized;
        }


    }


    HAI_EXPORT ComputeEngine::ComputeEngine( const std::shared_ptr<SessionOptions>& defaultSessionOptions, const Ort::ThreadingOptions& threadingOptions )
        : environment_( std::make_shared<ONNX::Environment>( threadingOptions ) ), defaultSessionOptions_( defaultSessionOptions )
    { }

    HAI_EXPORT ComputeEngine::~ComputeEngine( )
    {
        std::vector<std::shared_ptr<ComputeNode>> nodes_;
        for ( auto& entry : computeNodes_ )
        {
            nodes_.emplace_back( entry.second );
        }
        for ( auto& node : nodes_ )
        {
            node->Stop( );
        }
    }

    HAI_EXPORT std::shared_ptr<ComputeNode> ComputeEngine::AddComputeNode( const WideString& computeNodeName, const DXCore::Adapter1& adapter, D3D_FEATURE_LEVEL featureLevel )
    {
        return AddComputeNode( computeNodeName, adapter, defaultSessionOptions_, featureLevel );
    }

    HAI_EXPORT std::shared_ptr<ComputeNode> ComputeEngine::AddComputeNode( const WideString& computeNodeName, const DXCore::Adapter1& adapter, const std::shared_ptr<SessionOptions>& sessionOptions, D3D_FEATURE_LEVEL featureLevel )
    {
        if ( computeNodes_.contains( computeNodeName ) )
        {
            HCC_THROW( ArgumentException, Format( L"The node `{}` already exist.", computeNodeName ), L"computeNodeName" );
        }
        auto newNode = std::make_shared<ComputeNode>( shared_from_this(), computeNodeName, adapter, sessionOptions, featureLevel );
        newNode->Initialize( );
        newNode->Start( );
        computeNodes_.emplace( computeNodeName, newNode );
        return newNode;
    }

}
#pragma once
#ifndef HWDMLMODEL_H_
#define HWDMLMODEL_H_

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

   This file contains a rewrite of DirectMLX.h from
   https://github.com/microsoft/DirectML/blob/master/Libraries/DirectMLX.h

   It uses the DirectML classes implemented in 
   HAIDirectML.h, making it easier to create 
   the operator implementations.


*/

//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************


#include "HAIDirectML.h"

namespace Harlinn::AI::DML::X
{
    template <typename T, size_t N>
    using SmallVector = boost::container::small_vector<T, N>;

    class Expression;
    class Graph;

    using TensorDimensions = SmallVector<UInt32, 4>;
    using TensorStrides = SmallVector<UInt32, 4>;

    struct TensorProperties
    {
        std::optional<TensorStrides> strides = std::nullopt;
        UInt64 totalTensorSizeInBytes = 0;
        UInt32 guaranteedBaseOffsetAlignment = 0;
    };

    namespace Internal
    {
        inline TensorProperties ComputeDefault( TensorDataType dataType, TensorFlags /*flags*/, std::span<const UInt32> sizes )
        {
            UInt32 dimensionCount = static_cast< UInt32 >( sizes.size( ) );
            TensorProperties props;
            props.totalTensorSizeInBytes = CalcBufferTensorSize( dataType, dimensionCount, sizes.data( ), nullptr );
            return props;
        }

        inline TensorProperties ComputeInterleavedChannel( TensorDataType dataType, TensorFlags flags /*flags*/, std::span<const UInt32> sizes )
        {
            UInt32 dimensionCount = static_cast< UInt32 >( sizes.size( ) );
            TensorStrides strides( dimensionCount );

            enum Axes { N, C, /* spatial dimensions ... */ };

            // N dimension strides
            if ( dimensionCount >= 1 )
            {
                strides[ N ] = 1;
                for ( UInt32 i = 1; i < dimensionCount; ++i )
                {
                    strides[ N ] *= sizes[ i ];
                }
            }

            // C dimension strides
            if ( dimensionCount >= 2 )
            {
                strides[ C ] = 1;
            }

            // Spatial dimension strides
            if ( dimensionCount >= 3 )
            {
                UInt32 stride = sizes[ C ];
                for ( UInt32 i = dimensionCount - 1; i >= 2; --i )
                {
                    strides[ i ] = stride;
                    stride *= sizes[ i ];
                }
            }

            TensorProperties props;
            props.strides = std::move( strides );
            props.totalTensorSizeInBytes = CalcBufferTensorSize( dataType, dimensionCount, sizes.data( ), props.strides->data( ) );
            props.guaranteedBaseOffsetAlignment = 0;
            return props;
        }
    }


    class TensorPolicy
    {
    public:
        // A function type that returns a TensorProperties object given a tensor data type, flags, and sizes.
        using Func = std::function< TensorProperties( TensorDataType dataType, TensorFlags flags, std::span<const UInt32> sizes ) >;
    private:
        Func impl_;
    public:
        TensorPolicy( ) = default;
        TensorPolicy( Func impl )
            : impl_( impl )
        {
        }

        TensorProperties Get( TensorDataType dataType, TensorFlags flags, std::span<const UInt32> sizes ) const
        {
            // Empty/uninitialized policy falls back to default.
            if ( !impl_ )
            {
                return Internal::ComputeDefault( dataType, flags, sizes );
            }
            return impl_( dataType, flags, sizes );
        }

        // Returns the default tensor policy, which doesn't produce any changes to tensor layout, has no guaranteed
        // alignment, and which uses DMLCalcBufferTensorSize to compute the total tensor size.
        static TensorPolicy Default( )
        {
            return TensorPolicy( );
        }

        // A tensor policy that returns strides which produce tensors with a layout transposed to dimension order
        // (0, 2, ..., n, 1). This is often referred to as "NHWC" or "interleaved channel" layout. This is useful,
        // for example, when applied to 2D Convolution to produce outputs in an NHWC layout (as opposed to NCHW, which
        // is the DirectML default for 2D Convolution).
        // 
        // Examples of the transposes produced by this policy:
        //   NCW -> NWC
        //   NCHW -> NHWC
        //   NCDHW -> NDHWC
        static TensorPolicy InterleavedChannel( )
        {
            return TensorPolicy( &Internal::ComputeInterleavedChannel );
        }
    };

    struct TensorDesc
    {
        mutable BufferTensorDesc bufferDesc_;
        mutable DML::TensorDesc tensorDesc_;
    public:
        TensorDataType DataType = TensorDataType::Unknown;
        TensorFlags Flags = TensorFlags::None;
        TensorDimensions Sizes;
        std::optional<TensorStrides> Strides;
        UInt64 TotalTensorSizeInBytes = 0;
        UInt32 GuaranteedBaseOffsetAlignment = 0;

        TensorDesc( ) = default;

        TensorDesc( TensorDataType dataType, const TensorDimensions& sizes, const TensorPolicy& policy = {} )
            : TensorDesc( dataType, TensorFlags::None, sizes, policy )
        {
        }

        TensorDesc( TensorDataType dataType, TensorFlags flags, const TensorDimensions& sizes, const TensorPolicy& policy = {} )
        {
            TensorProperties props = policy.Get( dataType, flags, sizes );
            Initialize(
                dataType,
                flags,
                sizes,
                props.strides,
                props.totalTensorSizeInBytes,
                props.guaranteedBaseOffsetAlignment );
        }

        TensorDesc( TensorDataType dataType, TensorFlags flags, const TensorDimensions& sizes, const std::optional<TensorDimensions>& strides, UInt64 totalTensorSizeInBytes, UInt32 guaranteedBaseOffsetAlignment )
        {
            Initialize( dataType, flags, sizes, strides, totalTensorSizeInBytes, guaranteedBaseOffsetAlignment );
        }

        TensorDesc( const DML::TensorDesc& desc )
            : TensorDesc( *static_cast< const BufferTensorDesc* >( desc.Desc ) )
        {
            assert( desc.Type == TensorType::Buffer );
            assert( desc.Desc != nullptr );
        }

        TensorDesc( const BufferTensorDesc& desc )
        {
            DataType = desc.DataType;
            Flags = desc.Flags;
            Sizes.assign( desc.Sizes, desc.Sizes + desc.DimensionCount );
            if ( desc.Strides )
            {
                Strides.emplace( );
                Strides->assign( desc.Strides, desc.Strides + desc.DimensionCount );
            }
            this->TotalTensorSizeInBytes = desc.TotalTensorSizeInBytes;
            this->GuaranteedBaseOffsetAlignment = desc.GuaranteedBaseOffsetAlignment;
        }

        template <typename T>
        const T* As( ) const
        {
            // "sizeof(T) == -1" is always false; this is just to make the static_assert dependent on the template
            // parameter and therefore not evaluated until template instantiation
            static_assert( sizeof( T ) == -1, "Invalid type" );
        }

        template <>
        const DML::BufferTensorDesc* As<DML::BufferTensorDesc>( ) const
        {
            assert( !Strides || Sizes.size( ) == Strides->size( ) );

            bufferDesc_.DataType = DataType;
            bufferDesc_.Flags = Flags;
            bufferDesc_.DimensionCount = static_cast< UInt32 >( Sizes.size( ) );
            bufferDesc_.Sizes = Sizes.data( );
            bufferDesc_.Strides = Strides ? Strides->data( ) : nullptr;
            bufferDesc_.TotalTensorSizeInBytes = TotalTensorSizeInBytes;
            bufferDesc_.GuaranteedBaseOffsetAlignment = GuaranteedBaseOffsetAlignment;
            return &bufferDesc_;
        }

        template <>
        const DML::TensorDesc* As<DML::TensorDesc>( ) const
        {
            tensorDesc_ = DML::TensorDesc{ TensorType::Buffer, As<DML::BufferTensorDesc>( ) };
            return &tensorDesc_;
        }

    private:
        void Initialize( TensorDataType tensorDataType, TensorFlags tensorFlags, const TensorDimensions& tensorSizes, const std::optional<TensorStrides>& tensorStrides, UInt64 totalTensorSizeInBytesVal, UInt32 guaranteedBaseOffsetAlignmentVal )
        {
            assert( !tensorStrides || tensorStrides->size( ) == static_cast< UInt32 >( tensorSizes.size( ) ) );

            DataType = tensorDataType;
            Flags = tensorFlags;
            Sizes = tensorSizes;
            Strides = tensorStrides;
            TotalTensorSizeInBytes = totalTensorSizeInBytesVal;
            GuaranteedBaseOffsetAlignment = guaranteedBaseOffsetAlignmentVal;
        }
    };

    namespace Internal
    {
        class GraphBuilder;
        class NodeOutput;

        // A node in the graph which represents a graph input.
        struct InputNode
        {
            UInt32 inputIndex = 0;
        };

        // A node in the graph which represents a DML operator.
        struct OperatorNode
        {
            DML::Operator op;

            // The inputs to this node
            std::vector<NodeOutput*> inputs;

            std::string name;
        };

        // Used for representing reshapes and type punning
        struct ReinterpretNode
        {
            NodeOutput* input = nullptr;
        };

        // A node in the graph that represents data available during graph compilation.
        struct ConstantNode
        {
            // This node does not own the memory to avoid copying large amounts of data.
            std::span<const Byte> data;

            std::string name;
        };

        enum class NodeType
        {
            Invalid,
            Input,
            Operator,
            Reinterpret,
            Constant,
        };

        // Identifies a node in the graph.
        struct NodeID
        {
            NodeType type = NodeType::Invalid;
            // The index of this node in the GraphBuilder
            UInt32 index = 0;
        };

        // Represents one of the outputs of a node.
        class NodeOutput
        {
            GraphBuilder* owner_ = nullptr;
            NodeID node_;

            // An operator can have multiple outputs; this index identifies which one of the operator's  outputs this
            // NodeOutput represents.
            UInt32 outputIndex_ = 0;

            TensorDesc tensorDesc_;
        public:
            NodeOutput( GraphBuilder* owner, NodeID node, UInt32 outputIndex, TensorDesc tensorDesc )
                : owner_( owner ) , node_( node ) , outputIndex_( outputIndex ) , tensorDesc_( std::move( tensorDesc ) )
            {
            }

            // Retrieves the GraphBuilder that owns this object.
            GraphBuilder* GetGraphBuilder( ) const 
            { 
                return owner_; 
            }

            NodeID GetNode( ) const 
            { 
                return node_; 
            }
            UInt32 GetOutputIndex( ) const 
            { 
                return outputIndex_; 
            }
            const TensorDesc& GetOutputDesc( ) const 
            { 
                return tensorDesc_; 
            }

        private:
            
        };

        struct GraphDesc
        {
            UInt32 inputCount = 0;
            UInt32 outputCount = 0;
            
            std::vector<DML::OperatorGraphNodeDesc> operatorNodes;
#if DML_TARGET_VERSION >= 0x6200
            std::vector<DML::ConstantDataGraphNodeDesc> constantNodes;
#endif // DML_TARGET_VERSION >= 0x6200
            std::vector<DML::InputGraphEdgeDesc> inputEdges;
            std::vector<DML::OutputGraphEdgeDesc> outputEdges;
            std::vector<DML::IntermediateGraphEdgeDesc> intermediateEdges;

            // Offset of the first operator node in the merged node list.
            constexpr UInt32 BaseOperatorNodeIndexInMergedNodes( ) const
            {
                return 0;
            }

            // Offset of the first constant node in the merged node list.
            UInt32 BaseConstantNodeIndexInMergedNodes( ) const
            {
                return static_cast< UInt32 >( operatorNodes.size( ) );
            }

            // Merges the operator and constant nodes into a single list of graph nodes, with all operator nodes
            // inserted before the constant nodes. The returned array is only valid so long as this instance of
            // GraphDesc is alive and not copied.
            
            std::vector<DML::GraphNodeDesc> Nodes( ) const
            {
                const size_t operatorNodeCount = operatorNodes.size( );
#if DML_TARGET_VERSION >= 0x6200
                const size_t constantNodeCount = constantNodes.size( );
#else
                const UInt32 constantNodeCount = 0;
#endif // DML_TARGET_VERSION >= 0x6200

                std::vector<DML::GraphNodeDesc> nodes( operatorNodeCount + constantNodeCount );

                auto nodesOperatorNodeSpan = std::span<DML::GraphNodeDesc>( nodes.data( ) + BaseOperatorNodeIndexInMergedNodes( ), operatorNodeCount );
                for ( size_t i = 0; i < nodesOperatorNodeSpan.size( ); ++i )
                {
                    nodesOperatorNodeSpan[ i ] = { GraphNodeType::Operator, &operatorNodes[ i ] };
                }

#if DML_TARGET_VERSION >= 0x6200
                auto nodesConstantNodeSpan = std::span<DML::GraphNodeDesc>( nodes.data( ) + BaseConstantNodeIndexInMergedNodes( ), constantNodeCount );
                for ( size_t i = 0; i < nodesConstantNodeSpan.size( ); ++i )
                {
                    
                    nodesConstantNodeSpan[ i ] = { GraphNodeType::Constant, &constantNodes[ i ] };
                }
#endif // DML_TARGET_VERSION >= 0x6200

                return nodes;
            }

            
            template <typename T>
            std::vector<DML::GraphEdgeDesc> Edges( DML::GraphEdgeType type, std::span<const T> edgesImpl ) const
            {
                std::vector<DML::GraphEdgeDesc> edges( edgesImpl.size( ) );
                for ( size_t i = 0; i < edges.size( ); ++i )
                {
                    edges[ i ] = { type, &edgesImpl[ i ] };
                }

                return edges;
            }

            std::vector<DML::GraphEdgeDesc> InputEdges( ) const
            {
                
                return Edges( DML::GraphEdgeType::Input, std::span<const DML::InputGraphEdgeDesc>( inputEdges ) );
            }

            std::vector<DML::GraphEdgeDesc> OutputEdges( ) const
            {
                return Edges( DML::GraphEdgeType::Output, std::span<const DML::OutputGraphEdgeDesc>( outputEdges ) );
            }

            std::vector<DML::GraphEdgeDesc> IntermediateEdges( ) const
            {
                return Edges( DML::GraphEdgeType::Intermediate, std::span<const DML::IntermediateGraphEdgeDesc>( intermediateEdges ) );
            }
        };

        class GraphBuilder
        {
            DML::Device1 m_device;
            TensorPolicy m_tensorPolicy;
            std::vector<InputNode> m_inputNodes;
            std::vector<OperatorNode> m_operatorNodes;
            std::vector<ReinterpretNode> m_reinterpretNodes;
            std::vector<ConstantNode> m_constantNodes;
            std::deque<NodeOutput> m_nodeOutputs; // deque doesn't invalidate references to elements when it resizes

            std::string m_name;
            std::stack<size_t> m_nameSubLengths;
        public:
            GraphBuilder( const DML::Device1& device, TensorPolicy tensorPolicy = {} )
                : m_device( device )
                , m_tensorPolicy( tensorPolicy )
            {
            }

            const DML::Device1& GetDevice( ) const
            {
                return m_device;
            }

            void PushName( std::string_view name )
            {
                m_nameSubLengths.push( m_name.size( ) );
                if ( !m_name.empty( ) )
                {
                    m_name += "_";
                }
                m_name += name;
            }

            void PopName( )
            {
                if ( !m_nameSubLengths.empty( ) )
                {
                    m_name.resize( m_nameSubLengths.top( ) );
                    m_nameSubLengths.pop( );
                }
            }

            void SetTensorPolicy( const TensorPolicy& policy ) 
            { 
                m_tensorPolicy = policy; 
            }
            const TensorPolicy& GetTensorPolicy( ) const 
            { 
                return m_tensorPolicy; 
            }
            TensorPolicy& GetTensorPolicy( ) 
            { 
                return m_tensorPolicy; 
            }

            // Creates a DML operator node owned by this graph builder and returns a NodeInfo identifier. The
            // inputs to this node must be supplied in the correct order matching the DML operator.
            
            template<typename T>
            NodeID CreateOperatorNode( const T& desc, std::span<NodeOutput* const> inputs );
            NodeID CreateInputNode( UInt32 inputIndex );
            NodeID CreateReinterpretNode( NodeOutput* input );
#if DML_TARGET_VERSION >= 0x6200
            NodeID CreateConstantNode( std::span<const Byte> data );
#endif // DML_TARGET_VERSION >= 0x6200
            NodeOutput* CreateNodeOutput( NodeID node, UInt32 outputIndex, const TensorDesc& tensorDesc );
            GraphDesc GetGraphDesc( std::span<const Expression> outputs ) const;
        };

    } // namespace Internal

    class Expression
    {
        // Owned by GraphBuilder
        Internal::NodeOutput* nodeOutput_;
    public:
        Expression( Internal::NodeOutput* nodeOutput = nullptr )
            : nodeOutput_( nodeOutput )
        {
        }

        // Returns a struct containing the required properties of the tensor to hold the output of this expression,
        // once evaluated.
        const TensorDesc& GetOutputDesc( ) const 
        { 
            return Impl( )->GetOutputDesc( ); 
        }

        // For internal use only
        Internal::NodeOutput* Impl( ) const 
        { 
            return nodeOutput_; 
        }

        explicit operator bool( ) const
        {
            return nodeOutput_ != nullptr;
        }
    };

    class NameScope
    {
        Internal::GraphBuilder* builder_ = nullptr;
    public:
        

        NameScope( Internal::GraphBuilder* builder, std::string_view name ) 
            : builder_( builder )
        {
            if ( builder_ )
            {
                builder_->PushName( name );
            }
        }

        ~NameScope( )
        {
            if ( builder_ )
            {
                builder_->PopName( );
            }
        }
    };

    class Graph
    {
        std::unique_ptr<Internal::GraphBuilder> graphBuilder_;
    public:
        explicit Graph( const DML::Device1& device, TensorPolicy tensorPolicy = {} )
            : graphBuilder_( std::make_unique<Internal::GraphBuilder>( device, tensorPolicy ) )
        {
        }

        // For internal use only
        Internal::GraphBuilder* Impl( ) 
        { 
            return graphBuilder_.get( );
        }

        // Sets/gets the tensor policy. If not set, defaults to TensorPolicy::Default(). Tensor policies can be used
        // to control properties (such as strides) on output tensors produced by this Graph.
        void SetTensorPolicy( TensorPolicy policy ) 
        { 
            graphBuilder_->SetTensorPolicy( std::move( policy ) );
        }
        const TensorPolicy& GetTensorPolicy( ) const 
        { 
            return graphBuilder_->GetTensorPolicy( );
        }
        TensorPolicy& GetTensorPolicy( ) 
        { 
            return graphBuilder_->GetTensorPolicy( );
        }

        NameScope CreateNameScope( std::string_view name ) 
        { 
            return NameScope( graphBuilder_.get( ), name );
        }

        void PushName( std::string_view name ) 
        { 
            graphBuilder_->PushName( name );
        }
        void PopName( ) 
        { 
            graphBuilder_->PopName( );
        }

        DML::CompiledOperator Compile( DML::ExecutionFlags flags, std::span<const Expression> outputs, UInt32 inputCount = 0 ) const
        {
            Internal::GraphDesc graph = graphBuilder_->GetGraphDesc( outputs );

            // If supplied, the requested number of inputs to the compiled operator can be larger than the actual
            // number of input nodes on the graph (e.g. in the case of unused empty inputs), but never smaller.
            assert( inputCount == 0 || inputCount >= graph.inputCount );

            std::vector<DML::GraphNodeDesc> graphNodes = graph.Nodes( );
            std::vector<DML::GraphEdgeDesc> inputEdges = graph.InputEdges( );
            std::vector<DML::GraphEdgeDesc> outputEdges = graph.OutputEdges( );
            std::vector<DML::GraphEdgeDesc> intermediateEdges = graph.IntermediateEdges( );
            
            DML::GraphDesc graphDesc = {};
            graphDesc.InputCount = inputCount ? inputCount : graph.inputCount;
            graphDesc.OutputCount = graph.outputCount;
            graphDesc.NodeCount = static_cast< UINT >( graphNodes.size( ) );
            graphDesc.Nodes = graphNodes.data( );
            graphDesc.InputEdgeCount = static_cast< UINT >( inputEdges.size( ) );
            graphDesc.InputEdges = inputEdges.data( );
            graphDesc.OutputEdgeCount = static_cast< UINT >( outputEdges.size( ) );
            graphDesc.OutputEdges = outputEdges.data( );
            graphDesc.IntermediateEdgeCount = static_cast< UINT >( intermediateEdges.size( ) );
            graphDesc.IntermediateEdges = intermediateEdges.data( );

            auto device = graphBuilder_->GetDevice( );
            auto compiledGraph = device.CompileGraph( graphDesc, flags );
            return compiledGraph;
        }

    private:
        
    };

    // Represents an activation to be fused with an existing operator. The meaning of param1 and param2 depend on the
    // activation to be fused.
    // 
    // For HARD_SIGMOID, LINEAR, PARAMETRIC_SOFTPLUS, and SCALED_TANH: param1 = Alpha and param2 = Beta
    // For ELU, LEAKY_RELU, THRESHOLDED_RELU, and CELU: param1 = Alpha. param2 is unused.
    // For SCALED_ELU, param1 = Alpha and param2 = Gamma.
    // For SHRINK, param1 = Bias and param2 = Threshold
    // For SOFTPLUS, param1 = Steepness.
    // For all other activations, both param1 and param2 are unused.
    struct FusedActivation
    {
        DML::OperatorType activation = DML::OperatorType::Invalid;
        float param1 = 0.0f;
        float param2 = 0.0f;

        FusedActivation( ) = default;

        explicit FusedActivation( DML::OperatorType activation, float param1 = 0.0f, float param2 = 0.0f )
            : activation( activation ), param1( param1 ), param2( param2 )
        {
        }

        static FusedActivation None( )
        {
            return FusedActivation( );
        }

        static FusedActivation ELU( float alpha = 1.0f )
        {
            return FusedActivation( DML::OperatorType::ActivationELU, alpha );
        }

        static FusedActivation HardSigmoid( float alpha = 0.2f, float beta = 0.5f )
        {
            return FusedActivation( DML::OperatorType::ActivationHardSigmoid, alpha, beta );
        }

        static FusedActivation Identity( )
        {
            return FusedActivation( DML::OperatorType::ActivationIdentity );
        }

        static FusedActivation LeakyReLU( float alpha = 0.01f )
        {
            return FusedActivation( DML::OperatorType::ActivationLeakyReLU, alpha );
        }

        static FusedActivation Linear( float alpha, float beta )
        {
            return FusedActivation( DML::OperatorType::ActivationLinear, alpha, beta );
        }

        static FusedActivation ParametricSoftPlus( float alpha, float beta )
        {
            return FusedActivation( DML::OperatorType::ActivationParametricSoftPlus, alpha, beta );
        }

        static FusedActivation ReLU( )
        {
            return FusedActivation( DML::OperatorType::ActivationReLU );
        }

        static FusedActivation ScaledELU( float alpha = 1.67326319217681884765625f, float gamma = 1.05070102214813232421875f )
        {
            return FusedActivation( DML::OperatorType::ActivationScaledELU, alpha, gamma );
        }

        static FusedActivation ScaledTanH( float alpha = 1.0f, float beta = 0.5f )
        {
            return FusedActivation( DML::OperatorType::ActivationScaledTanH, alpha, beta );
        }

        static FusedActivation Sigmoid( )
        {
            return FusedActivation( DML::OperatorType::ActivationSigmoid );
        }

        static FusedActivation SoftPlus( float steepness = 1.0f )
        {
            return FusedActivation( DML::OperatorType::ActivationSoftPlus, steepness );
        }

        static FusedActivation SoftSign( )
        {
            return FusedActivation( DML::OperatorType::ActivationSoftSign );
        }

        static FusedActivation TanH( )
        {
            return FusedActivation( DML::OperatorType::ActivationTanH );
        }

        static FusedActivation ThresholdedReLU( float alpha = 1.0f )
        {
            return FusedActivation( DML::OperatorType::ActivationThresholdedReLU, alpha );
        }

        static FusedActivation Shrink( float bias = 0.0f, float threshold = 0.5f )
        {
            return FusedActivation( DML::OperatorType::ActivationShrink, bias, threshold );
        }

        static FusedActivation CeLU( float alpha = 1.0f )
        {
            return FusedActivation( DML::OperatorType::ActivationCeLU, alpha );
        }

#if DML_TARGET_VERSION >= 0x5100
        static FusedActivation GeLU( )
        {
            return FusedActivation( DML::OperatorType::ActivationGeLU );
        }
#endif // DML_TARGET_VERSION >= 0x5100
    };

    // Implementation Internal helper for determining if a list of expressions share the same GraphBuilder.
    namespace Internal
    {
        inline bool HasSameOwner( std::span<const Expression> exprs )
        {
            if ( exprs.size( ) == 0 )
            {
                return true;
            }

            auto* owner = exprs.begin( )->Impl( )->GetGraphBuilder( );
            for ( Expression expr : exprs )
            {
                if ( expr.Impl( )->GetGraphBuilder( ) != owner )
                {
                    return false;
                }
            }

            return true;
        }
        
        inline bool HasSameOwner( std::initializer_list<Expression> exprs )
        {
            std::span<const Expression> span( exprs.begin( ), exprs.size( ) );
            return HasSameOwner( span );
        }
        

        inline bool HasSameDataType( std::span<const Expression> exprs )
        {
            if ( exprs.size( ) == 0 )
            {
                return true;
            }

            DML::TensorDataType dataType = exprs.begin( )->Impl( )->GetOutputDesc( ).DataType;
            for ( Expression expr : exprs )
            {
                if ( expr.Impl( )->GetOutputDesc( ).DataType != dataType )
                {
                    return false;
                }
            }

            return true;
        }
        
        inline bool HasSameDataType( std::initializer_list<Expression> exprs )
        {
            std::span<const Expression> span( exprs.begin( ), exprs.size( ) );
            return HasSameDataType( span );
        }
        
    } // namespace Internal

    // Expression implementation helpers
    namespace Internal
    {
        // Used to reserve some space on the stack for setting up fused activation operator descs.
        struct FusedActivationStorage
        {
            DML::OperatorDesc opDesc;

            // All fuseable activation descs have a common layout: two tensor desc pointers and up to 2 optional
            // float parameters, so just use LINEAR as an archetype
            DML::ActivationLinearOperatorDesc activationDesc;
        };

        // Returns the correct value for filling out fused activation fields in the DML API, e.g.
        // DML_CONVOLUTION_OPERATOR_DESC::FusedActivation. The descs themselves are stored in the `storage` outptr.
        inline const DML::OperatorDesc* GetFusedActivationPtr( FusedActivation fusedActivation, _Out_ FusedActivationStorage* storage )
        {
            if ( fusedActivation.activation == DML::OperatorType::Invalid )
            {
                // No fused activation
                return nullptr;
            }

            storage->activationDesc.InputTensor = nullptr;
            storage->activationDesc.OutputTensor = nullptr;
            storage->activationDesc.Alpha = fusedActivation.param1;
            storage->activationDesc.Beta = fusedActivation.param2;

            storage->opDesc.Type = fusedActivation.activation;
            storage->opDesc.Desc = &storage->activationDesc;

            return &storage->opDesc;
        }

        template <typename TDesc, typename ...Args>
        Expression UnaryImpl( const std::optional<DML::ScaleBias>& scaleBias, Expression input, Args&& ... args )
        {
            Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

            TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
            TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) ); // Same as input

            const DML::ScaleBias* sb = scaleBias.has_value( ) ? &scaleBias.value( ) : nullptr;

            TDesc desc( inputTensor.As<DML::TensorDesc>( ), outputTensor.As<DML::TensorDesc>( ), sb, std::forward<Args>( args )... );

            Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
            Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
            Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

            return output;
        }

        template <typename TDesc, typename ...Args>
        Expression UnaryImpl( DML::TensorDataType outputDataType, Expression input, Args&& ... args )
        {
            auto* builder = input.Impl( )->GetGraphBuilder( );

            const TensorDesc& inputTensor = input.Impl( )->GetOutputDesc( );

            if ( outputDataType == DML::TensorDataType::Unknown )
            {
                outputDataType = inputTensor.DataType;
            }
            TensorDesc outputTensor( outputDataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

            TDesc desc( inputTensor.As<DML::TensorDesc>( ), outputTensor.As<DML::TensorDesc>( ), std::forward<Args>( args )... );

            Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
            Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
            Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

            return output;
        }

        template <typename TDesc, typename ...Args>
        Expression UnaryImpl( Expression input, Args&& ... args )
        {
            auto* builder = input.Impl( )->GetGraphBuilder( );

            const TensorDesc& inputTensor = input.Impl( )->GetOutputDesc( );
            TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

            TDesc desc( inputTensor.As<DML::TensorDesc>( ), outputTensor.As<DML::TensorDesc>( ), std::forward<Args>( args )... );

            Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
            Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
            Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

            return output;
        }


        template <typename TDesc, typename ...Args>
        Expression BinaryImpl( Expression a, Expression b, Args&& ... args )
        {
            assert( Internal::HasSameOwner( { a, b } ) );
            Internal::GraphBuilder* builder = a.Impl( )->GetGraphBuilder( );

            TensorDesc aTensor = a.Impl( )->GetOutputDesc( );
            TensorDesc bTensor = b.Impl( )->GetOutputDesc( );
            TensorDesc outputTensor( aTensor.DataType, aTensor.Sizes, builder->GetTensorPolicy( ) ); // Same as input

            TDesc desc( aTensor.As<DML::TensorDesc>( ), bTensor.As<DML::TensorDesc>( ), outputTensor.As<DML::TensorDesc>( ), std::forward<Args>( args )... );

            Internal::NodeOutput* const inputs[ ] = { a.Impl( ), b.Impl( ) };
            Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
            Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

            return output;
        }

        template <typename TDesc, typename ...Args>
        Expression BinaryImpl( const std::optional<DML::ScaleBias>& scaleBias, Expression a, Expression b, Args&& ... args )
        {
            assert( Internal::HasSameOwner( { a, b } ) );
            Internal::GraphBuilder* builder = a.Impl( )->GetGraphBuilder( );

            TensorDesc aTensor = a.Impl( )->GetOutputDesc( );
            TensorDesc bTensor = b.Impl( )->GetOutputDesc( );
            TensorDesc outputTensor( aTensor.DataType, aTensor.Sizes, builder->GetTensorPolicy( ) ); // Same as input

            const DML::ScaleBias* sb = scaleBias.has_value( ) ? &scaleBias.value( ) : nullptr;

            TDesc desc( aTensor.As<DML::TensorDesc>( ), bTensor.As<DML::TensorDesc>( ), outputTensor.As<DML::TensorDesc>( ), sb, std::forward<Args>( args )... );

            Internal::NodeOutput* const inputs[ ] = { a.Impl( ), b.Impl( ) };
            Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
            Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

            return output;
        }

        template <typename TDesc, typename ...Args>
        Expression BinaryImpl( FusedActivation fusedActivation, Expression a, Expression b, Args&& ... args )
        {
            assert( Internal::HasSameOwner( { a, b } ) );
            Internal::GraphBuilder* builder = a.Impl( )->GetGraphBuilder( );

            TensorDesc aTensor = a.Impl( )->GetOutputDesc( );
            TensorDesc bTensor = b.Impl( )->GetOutputDesc( );
            TensorDesc outputTensor( aTensor.DataType, aTensor.Sizes, builder->GetTensorPolicy( ) ); // Same as input
            Internal::FusedActivationStorage storage;

            TDesc desc( aTensor.As<DML::TensorDesc>( ), bTensor.As<DML::TensorDesc>( ), outputTensor.As<DML::TensorDesc>( ), std::forward<Args>( args )... );

            desc.FusedActivation = Internal::GetFusedActivationPtr( fusedActivation, &storage );

            Internal::NodeOutput* const inputs[ ] = { a.Impl( ), b.Impl( ) };
            Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
            Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

            return output;
        }


        template <typename TDesc, typename ...Args>
        Expression CompareImpl( DML::TensorDataType outputDataType, Expression a, Expression b, Args&& ... args )
        {
            assert( Internal::HasSameOwner( { a, b } ) );
            Internal::GraphBuilder* builder = a.Impl( )->GetGraphBuilder( );

            TensorDesc aTensor = a.Impl( )->GetOutputDesc( );
            TensorDesc bTensor = b.Impl( )->GetOutputDesc( );
            TensorDesc outputTensor( outputDataType, aTensor.Sizes, builder->GetTensorPolicy( ) );

            TDesc desc( aTensor.As<DML::TensorDesc>( ), bTensor.As<DML::TensorDesc>( ), outputTensor.As<DML::TensorDesc>( ), std::forward<Args>( args )... );

            Internal::NodeOutput* const inputs[ ] = { a.Impl( ), b.Impl( ) };
            Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
            Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

            return output;
        }

        

        inline const DML::ScaleBias* ToScaleBias( const std::optional<DML::ScaleBias>& scaleBias )
        {
            return scaleBias.has_value( ) ? &scaleBias.value( ) : nullptr;
        }


    } // namespace Internal

    inline Expression InputTensor( Graph& graph, UInt32 inputIndex, TensorDesc desc )
    {
        Internal::GraphBuilder* builder = graph.Impl( );

        Internal::NodeID node = builder->CreateInputNode( inputIndex );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( desc ) );
        return output;
    }

#if DML_TARGET_VERSION >= 0x6200
    // Creates a constant node in the graph that directly consumes memory accessible to the CPU.
    // The graph node is a weak reference to the memory, so the backing memory must remain valid
    // until the DMLX graph is compiled.
    inline Expression ConstantData( Graph& graph, std::span<const Byte> data, TensorDesc desc )
    {
        Internal::GraphBuilder* builder = graph.Impl( );

        Internal::NodeID node = builder->CreateConstantNode( data );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, desc );
        return output;
    }
#endif

    inline Expression Identity( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseIdentityOperatorDesc>( scaleBias, input  );
    }

    inline Expression Abs( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseAbsOperatorDesc>( scaleBias, input );
    }

    inline Expression ACos( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseACosOperatorDesc>( scaleBias, input  );
    }

    inline Expression Add( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseAddOperatorDesc>( a, b );
    }

    inline Expression Add( Expression a, Expression b, FusedActivation fusedActivation )
    {
        return Internal::BinaryImpl<ElementWiseAdd1OperatorDesc>( fusedActivation, a, b );
    }

    inline Expression ASin( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseASinOperatorDesc>( scaleBias, input );
    }

    inline Expression ATan( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseATanOperatorDesc>( scaleBias, input );
    }

#if DML_TARGET_VERSION >= 0x3100

    inline Expression ATanYX( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseATanYXOperatorDesc>( a, b );
    }

#endif // DML_TARGET_VERSION >= 0x3100

    inline Expression Ceil( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseCeilOperatorDesc>( scaleBias, input );
    }

    inline Expression Clip( Expression input, float min, float max, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseClipOperatorDesc>( input, Internal::ToScaleBias( scaleBias ), min, max );

        /*
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) ); // Same as input

        ElementWiseClipOperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.ScaleBias = scaleBias ? &scaleBias.value( ) : nullptr;
        desc.Min = min;
        desc.Max = max;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
        */
    }

#if DML_TARGET_VERSION >= 0x3100

    inline Expression ClipGrad( Expression input, Expression inputGradient, float min, float max )
    {
        TensorDesc inputGradientTensor = inputGradient.Impl( )->GetOutputDesc( );
        return Internal::UnaryImpl<ElementWiseClipGradOperatorDesc>( input, inputGradientTensor.As<DML::TensorDesc>( ), min, max );

        /*
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc inputGradientTensor = inputGradient.Impl( )->GetOutputDesc( );
        TensorDesc outputGradientTensor( inputGradientTensor.DataType, inputGradientTensor.Sizes, builder->GetTensorPolicy( ) );

        ElementWiseClipGradOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.InputGradientTensor = inputGradientTensor.As<DML::TensorDesc>( );
        desc.OutputGradientTensor = outputGradientTensor.As<DML::TensorDesc>( );
        desc.Min = min;
        desc.Max = max;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputGradientTensor ) );

        return output;
        */
    }

#endif // DML_TARGET_VERSION >= 0x3100

    inline Expression Cos( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseCosOperatorDesc>( scaleBias, input );
    }

    inline Expression Divide( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseDivideOperatorDesc>( a, b );
    }

    inline Expression Exp( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseExpOperatorDesc>( scaleBias, input );
    }

    inline Expression Floor( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseFloorOperatorDesc>( scaleBias, input );
    }

    inline Expression Log( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseLogOperatorDesc>( scaleBias, input );
    }

    inline Expression LogicalAnd( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseLogicalAndOperatorDesc>( a, b );
    }

    inline Expression Equals( Expression a, Expression b, DML::TensorDataType outputDataType = DML::TensorDataType::UInt8 )
    {
        return Internal::CompareImpl<ElementWiseLogicalEqualsOperatorDesc>( outputDataType, a, b );
    }

    inline Expression GreaterThan( Expression a, Expression b, DML::TensorDataType outputDataType = DML::TensorDataType::UInt8 )
    {
        return Internal::CompareImpl<ElementWiseLogicalGreaterThanOperatorDesc>( outputDataType, a, b );
    }

    inline Expression GreaterThanOrEqual( Expression a, Expression b, DML::TensorDataType outputDataType = DML::TensorDataType::UInt8 )
    {
        return Internal::CompareImpl<ElementWiseLogicalGreaterThanOrEqualOperatorDesc>( outputDataType, a, b );
    }

    inline Expression LessThan( Expression a, Expression b, DML::TensorDataType outputDataType = DML::TensorDataType::UInt8 )
    {
        return Internal::CompareImpl<ElementWiseLogicalLessThanOperatorDesc>( outputDataType, a, b );
    }

    inline Expression LessThanOrEqual( Expression a, Expression b, DML::TensorDataType outputDataType = DML::TensorDataType::UInt8 )
    {
        return Internal::CompareImpl<ElementWiseLogicalLessThanOrEqualOperatorDesc>( outputDataType, a, b );
    }

    inline Expression LogicalNot( Expression input )
    {
        return Internal::UnaryImpl<ElementWiseLogicalNotOperatorDesc>( input );
        /*
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) ); // Same as input

        ElementWiseLogicalNotOperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
        */
    }

    inline Expression LogicalOr( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseLogicalOrOperatorDesc>( a, b );
    }

    inline Expression LogicalXor( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseLogicalXorOperatorDesc>( a, b );
    }

    inline Expression Max( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseMaxOperatorDesc>( a, b );
    }

    inline Expression Mean( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseMeanOperatorDesc>( a, b );
    }

    inline Expression Min( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseMinOperatorDesc>( a, b );
    }

    inline Expression Multiply( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseMultiplyOperatorDesc>( a, b );
    }

    inline Expression Pow( Expression input, Expression exponent, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::BinaryImpl<ElementWisePowOperatorDesc>( scaleBias, input, exponent );
        /*
        assert( Internal::HasSameOwner( { input, exponent } ) );
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc exponentTensor = exponent.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) ); // Same as input

        ElementWisePowOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.ExponentTensor = exponentTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.ScaleBias = scaleBias ? &scaleBias.value( ) : nullptr;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), exponent.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
        */
    }

    inline Expression Pow( Expression input, float exponent, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseConstantPowOperatorDesc>( scaleBias, input, exponent );
        /*
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) ); // Same as input

        ElementWiseConstantPowOperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.ScaleBias = scaleBias ? &scaleBias.value( ) : nullptr;
        desc.Exponent = exponent;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
        */
    }

    inline Expression Reciprocal( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseReciprocalOperatorDesc>( scaleBias, input );
    }

    inline Expression Sin( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseSinOperatorDesc>( scaleBias, input );
    }

    inline Expression Sqrt( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseSqrtOperatorDesc>( scaleBias, input );
    }

#if DML_TARGET_VERSION >= 0x3100

    inline Expression DifferenceSquare( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseDifferenceSquareOperatorDesc>( a, b );
    }

#endif // DML_TARGET_VERSION >= 0x3100

    inline Expression Subtract( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseSubtractOperatorDesc>( a, b );
    }

    inline Expression Tan( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseTanOperatorDesc>( scaleBias, input );
    }

    inline Expression Threshold( Expression input, float min, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseThresholdOperatorDesc>( scaleBias, input, min );
        /*
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) ); // Same as input

        ElementWiseThresholdOperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.ScaleBias = scaleBias ? &scaleBias.value( ) : nullptr;
        desc.Min = min;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
        */
    }

    inline Expression QuantizeLinear( Expression input, Expression scale, Expression zeroPoint, DML::TensorDataType outputDataType = DML::TensorDataType::UInt8 )
    {
        assert( Internal::HasSameOwner( { input, scale, zeroPoint } ) );

        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc scaleTensor = scale.Impl( )->GetOutputDesc( );
        TensorDesc zeroPointTensor = zeroPoint.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( outputDataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        ElementWiseQuantizeLinearOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.ScaleTensor = scaleTensor.As<DML::TensorDesc>( );
        desc.ZeroPointTensor = zeroPointTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), scale.Impl( ), zeroPoint.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression DequantizeLinear( Expression input, Expression scale, Expression zeroPoint )
    {
        assert( Internal::HasSameOwner( { input, scale, zeroPoint } ) );

        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc scaleTensor = scale.Impl( )->GetOutputDesc( );
        TensorDesc zeroPointTensor = zeroPoint.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( scaleTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        ElementWiseDequantizeLinearOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.ScaleTensor = scaleTensor.As<DML::TensorDesc>( );
        desc.ZeroPointTensor = zeroPointTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), scale.Impl( ), zeroPoint.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression Sign( Expression a )
    {
        return Internal::UnaryImpl<ElementWiseSignOperatorDesc>( a );
    }

    inline Expression IsNaN( Expression input, DML::TensorDataType outputDataType = DML::TensorDataType::UInt8 )
    {
        
        return Internal::UnaryImpl<ElementWiseIsNaNOperatorDesc>( outputDataType, input  );
    }

    inline Expression Erf( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseErfOperatorDesc>( scaleBias, input );
    }

    inline Expression Sinh( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseSinHOperatorDesc>( scaleBias, input );
    }

    inline Expression Cosh( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseCosHOperatorDesc>( scaleBias, input );
    }

    inline Expression Tanh( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseTanHOperatorDesc>( scaleBias, input );
    }

    inline Expression ASinh( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseASinHOperatorDesc>( scaleBias, input );
    }

    inline Expression ACosh( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseACosHOperatorDesc>( scaleBias, input );
    }

    inline Expression ATanh( Expression input, const std::optional<DML::ScaleBias>& scaleBias = std::nullopt )
    {
        return Internal::UnaryImpl<ElementWiseATanHOperatorDesc>( scaleBias, input );
    }

    inline Expression If( Expression condition, Expression a, Expression b )
    {
        assert( Internal::HasSameOwner( { condition, a, b } ) );
        assert( Internal::HasSameDataType( { a, b } ) );

        Internal::GraphBuilder* builder = condition.Impl( )->GetGraphBuilder( );

        TensorDesc conditionTensor = condition.Impl( )->GetOutputDesc( );
        
        assert( conditionTensor.DataType == DML::TensorDataType::UInt8 );

        TensorDesc aTensor = a.Impl( )->GetOutputDesc( );
        TensorDesc bTensor = b.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( aTensor.DataType, aTensor.Sizes, builder->GetTensorPolicy( ) );

        ElementWiseIfOperatorDesc desc = {};
        desc.ConditionTensor = conditionTensor.As<DML::TensorDesc>( );
        desc.ATensor = aTensor.As<DML::TensorDesc>( );
        desc.BTensor = bTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );

        Internal::NodeOutput* const inputs[ ] = { condition.Impl( ), a.Impl( ), b.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression BitShiftLeft( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseBitShiftLeftOperatorDesc>( a, b );
    }

    inline Expression BitShiftRight( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseBitShiftRightOperatorDesc>( a, b );
    }

    inline Expression BitAnd( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseBitAndOperatorDesc>( a, b );
    }

    inline Expression BitOr( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseBitOrOperatorDesc>( a, b );
    }

    inline Expression BitXor( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseBitXorOperatorDesc>( a, b );
    }

    inline Expression BitNot( Expression a )
    {
        return Internal::UnaryImpl<ElementWiseBitNotOperatorDesc>( a );
    }

    inline Expression BitCount( Expression a, DML::TensorDataType outputDataType = DML::TensorDataType::UInt8 )
    {
        return Internal::UnaryImpl<ElementWiseBitCountOperatorDesc>( outputDataType, a );
    }

    inline Expression Round( Expression input, DML::RoundingMode roundingMode = DML::RoundingMode::HalvesToNearestEven )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) ); // Same as input

        ElementWiseRoundOperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.RoundingMode = roundingMode;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression IsInfinity( Expression input, DML::IsInfinityMode infinityMode = DML::IsInfinityMode::Either, DML::TensorDataType outputDataType = DML::TensorDataType::UInt8 )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( outputDataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        ElementWiseIsInfinityOperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.InfinityMode = infinityMode;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression ModulusTruncate( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseModulusTruncateOperatorDesc>( a, b );
    }

    inline Expression ModulusFloor( Expression a, Expression b )
    {
        return Internal::BinaryImpl<ElementWiseModulusFloorOperatorDesc>( a, b );
    }


    namespace Internal
    {
        template<typename TDesc, typename ...Args>
        Expression ActivationImpl( const Expression& input, Args&& ... args )
        {
            Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( ); 
                
            const TensorDesc& inputTensor = input.Impl( )->GetOutputDesc( ); 
            TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) ); 
            
            TDesc desc( inputTensor.As<DML::TensorDesc>( ), outputTensor.As<DML::TensorDesc>( ), std::forward<Args>( args )... );
                
            Internal::NodeOutput* const inputs[ ] = { input.Impl( ) }; 
            Internal::NodeID node = builder->CreateOperatorNode( desc, inputs ); 
            Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) ); 

            return output; 
        }
    }


    inline Expression ActivationElu( Expression input, float alpha = 1.0f )
    {
        return Internal::ActivationImpl<ActivationELUOperatorDesc>( input, alpha );
    }

    inline Expression ActivationHardMax( Expression input )
    {
        return Internal::ActivationImpl<ActivationHardMaxOperatorDesc>( input );
    }

    inline Expression ActivationHardSigmoid( Expression input, float alpha = 0.2f, float beta = 0.5f )
    {
        return Internal::ActivationImpl<ActivationHardSigmoidOperatorDesc>( input, alpha, beta );
    }

    inline Expression ActivationIdentity( Expression input )
    {
        return Internal::ActivationImpl<ActivationIdentityOperatorDesc>( input );
    }

    inline Expression ActivationLeakyReLU( Expression input, float alpha = 0.01f )
    {
        return Internal::ActivationImpl<ActivationLeakyReLUOperatorDesc>( input, alpha );
    }

    inline Expression ActivationLinear( Expression input, float alpha, float beta )
    {
        return Internal::ActivationImpl<ActivationLinearOperatorDesc>( input, alpha, beta );
    }

    inline Expression ActivationLogSoftMax( Expression input )
    {
        return Internal::ActivationImpl<ActivationLogSoftMaxOperatorDesc>( input );
    }

    inline Expression ActivationParameterizedReLU( Expression input, Expression slope )
    {
        assert( Internal::HasSameOwner( { input, slope } ) );

        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc slopeTensor = slope.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        ActivationParameterizedReLUOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.SlopeTensor = slopeTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), slope.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression ActivationParametricSoftPlus( Expression input, float alpha, float beta )
    {
        return Internal::ActivationImpl<ActivationParametricSoftPlusOperatorDesc>( input, alpha, beta );
    }

    inline Expression ActivationReLU( Expression input )
    {
        return Internal::ActivationImpl<ActivationReLUOperatorDesc>( input );
    }

    inline Expression ActivationScaledELU( Expression input, float alpha = 1.67326319217681884765625f, float gamma = 1.05070102214813232421875f )
    {
        return Internal::ActivationImpl<ActivationScaledELUOperatorDesc>( input, alpha, gamma );
    }

    inline Expression ActivationScaledTanH( Expression input, float alpha = 1.0f, float beta = 0.5f )
    {
        return Internal::ActivationImpl<ActivationScaledTanHOperatorDesc>( input, alpha, beta );
    }

    inline Expression ActivationSigmoid( Expression input )
    {
        return Internal::ActivationImpl<ActivationSigmoidOperatorDesc>( input );
    }

    inline Expression ActivationSoftMax( Expression input )
    {
        return Internal::ActivationImpl<ActivationSoftMaxOperatorDesc>( input );
    }

#if DML_TARGET_VERSION >= 0x5100
    inline Expression ActivationSoftMax( Expression input, std::span<const UInt32> axes )
    {
        return Internal::ActivationImpl<ActivationSoftMax1OperatorDesc>( input, axes );
    }

    inline Expression ActivationGeLU( Expression input )
    {
        return Internal::ActivationImpl<ActivationGeLUOperatorDesc>( input );
    }
#endif

    inline Expression ActivationSoftPlus( Expression input, float steepness = 1.0f )
    {
        return Internal::ActivationImpl<ActivationSoftPlusOperatorDesc>( input, steepness );
    }

    inline Expression ActivationSoftSign( Expression input )
    {
        return Internal::ActivationImpl<ActivationSoftSignOperatorDesc>( input );
    }

    inline Expression ActivationTanH( Expression input )
    {
        return Internal::ActivationImpl<ActivationTanHOperatorDesc>( input );
    }

    inline Expression ActivationThresholdedReLU( Expression input, float alpha = 1.0f )
    {
        return Internal::ActivationImpl<ActivationThresholdedReLUOperatorDesc>( input, alpha );
    }

    inline Expression ActivationShrink( Expression input, float bias = 0.0f, float threshold = 0.5f )
    {
        return Internal::ActivationImpl<ActivationShrinkOperatorDesc>( input, bias, threshold );
    }

    inline Expression ActivationCelu( Expression input, float alpha = 1.0f )
    {
        return Internal::ActivationImpl<ActivationCeLUOperatorDesc>( input, alpha );
    }


    // ---------------------------------------------------------------------------------------------------------------

    // If not specified, parameters are defaulted to the following values:
    //   Mode = DML::ConvolutionMode::CrossCorrelation
    //   Direction = DML::ConvolutionDirection::Forward
    //   Strides = { 1, 1 } for 2D convolution, { 1, 1, 1 } for 3D convolution
    //   Dilations = { 1, 1 } for 2D convolution, { 1, 1, 1 } for 3D convolution
    //   StartPadding = { 0, 0 } for 2D convolution, { 0, 0, 0 } for 3D convolution
    //   EndPadding = { 0, 0 } for 2D convolution, { 0, 0, 0 } for 3D convolution
    //   OutputPadding = { 0, 0 } for 2D convolution, { 0, 0, 0 } for 3D convolution
    //   GroupCount = 1
    //   FusedActivation = nullptr
    //   OutputSizes = computed from other parameters
    inline Expression Convolution(
        Expression input,
        Expression filter,
        std::optional<Expression> bias = std::nullopt,
        DML::ConvolutionMode mode = DML::ConvolutionMode::CrossCorrelation,
        DML::ConvolutionDirection direction = DML::ConvolutionDirection::Forward,
        std::span<const UInt32> strides = {},
        std::span<const UInt32> dilations = {},
        std::span<const UInt32> startPadding = {},
        std::span<const UInt32> endPadding = {},
        std::span<const UInt32> outputPadding = {},
        UInt32 groupCount = 1,
        FusedActivation fusedActivation = FusedActivation::None( ),
        TensorDimensions outputSizes = {} )
    {
        assert( Internal::HasSameOwner( { input, filter } ) );
        assert( !bias || Internal::HasSameOwner( { input, *bias } ) );

        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc filterTensor = filter.Impl( )->GetOutputDesc( );
        TensorDesc biasTensor;
        if ( bias )
        {
            biasTensor = bias->Impl( )->GetOutputDesc( );
        }

        UInt32 dimensionCount = static_cast< UInt32 >( inputTensor.Sizes.size( ) );

        assert( dimensionCount == 4 || dimensionCount == 5 );
        UInt32 spatialDimensionCount = dimensionCount - 2;

        // If the spatial dimension count is 2, we'll just use the first two elements by setting
        // DimensionCount = 2 in the desc
        const UInt32 defaultStridesAndDilations[ 3 ] = { 1, 1, 1 };
        const UInt32 defaultPadding[ 3 ] = { 0, 0, 0 };

        assert( strides.empty( ) || strides.size( ) == spatialDimensionCount );
        assert( dilations.empty( ) || dilations.size( ) == spatialDimensionCount );
        assert( startPadding.empty( ) || startPadding.size( ) == spatialDimensionCount );
        assert( endPadding.empty( ) || endPadding.size( ) == spatialDimensionCount );
        assert( outputPadding.empty( ) || outputPadding.size( ) == spatialDimensionCount );
        assert( outputSizes.empty( ) || outputSizes.size( ) == inputTensor.Sizes.size( ) );

        strides = strides.empty( ) ? std::span<const UInt32>{ defaultStridesAndDilations } : strides;
        dilations = dilations.empty( ) ? std::span<const UInt32>{ defaultStridesAndDilations } : dilations;
        startPadding = startPadding.empty( ) ? std::span<const UInt32>{ defaultPadding } : startPadding;
        endPadding = endPadding.empty( ) ? std::span<const UInt32>{ defaultPadding } : endPadding;
        outputPadding = outputPadding.empty( ) ? std::span<const UInt32>{ defaultPadding } : outputPadding;

        // Compute the output shapes

        if ( outputSizes.empty( ) )
        {
            if ( direction == DML::ConvolutionDirection::Forward )
            {
                outputSizes.push_back( inputTensor.Sizes[ 0 ] ); // output[N] = input[N]
                outputSizes.push_back( filterTensor.Sizes[ 0 ] ); // output[C] = filter[N]

                for ( UInt32 dim = 0; dim < spatialDimensionCount; ++dim )
                {
                    UInt32 inputSize = inputTensor.Sizes[ dim + 2 ];
                    UInt32 paddedSize = inputSize + startPadding[ dim ] + endPadding[ dim ];

                    UInt32 windowSize = filterTensor.Sizes[ dim + 2 ];
                    UInt32 kernelSize = 1 + ( windowSize - 1 ) * dilations[ dim ];

                    assert( kernelSize <= paddedSize );
                    assert( strides[ dim ] != 0 );

                    outputSizes.push_back( 1 + ( paddedSize - kernelSize ) / strides[ dim ] );
                }
            }
            else if ( direction == DML::ConvolutionDirection::Backward )
            {
                // TODO: implement me
                assert( false );
            }
            else
            {
                assert( false );
                HCC_COM_CHECK_HRESULT( E_UNEXPECTED );
            }
        }

        TensorDesc outputTensor( inputTensor.DataType, outputSizes, builder->GetTensorPolicy( ) );
        Internal::FusedActivationStorage storage;

        ConvolutionOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.FilterTensor = filterTensor.As<DML::TensorDesc>( );
        desc.BiasTensor = bias ? biasTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.Mode = mode;
        desc.Direction = direction;
        desc.DimensionCount = spatialDimensionCount;
        desc.Strides = strides.data( );
        desc.Dilations = dilations.data( );
        desc.StartPadding = startPadding.data( );
        desc.EndPadding = endPadding.data( );
        desc.OutputPadding = outputPadding.data( );
        desc.GroupCount = groupCount;
        desc.FusedActivation = Internal::GetFusedActivationPtr( fusedActivation, &storage );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), filter.Impl( ), bias ? bias->Impl( ) : nullptr };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    // Helper for setting parameters for the Convolution operator. Sample usage:
    // 
    //   auto conv = dml::ConvolutionBuilder(...)
    //        .StartPadding(...)
    //        .EndPadding(...)
    //        .Strides(...)
    //        .Build();
    // 
    // Parameters left unspecified will be defaulted with the same values as dml::Convolution().
    class ConvolutionBuilder
    {
        Expression input_;
        Expression filter_;
        std::optional<Expression> bias_;
        DML::ConvolutionMode mode_ = DML::ConvolutionMode::CrossCorrelation;
        DML::ConvolutionDirection direction_ = DML::ConvolutionDirection::Forward;
        SmallVector<UInt32, 3> strides_ = {};
        SmallVector<UInt32, 3> dilations_ = {};
        SmallVector<UInt32, 3> startPadding_ = {};
        SmallVector<UInt32, 3> endPadding_ = {};
        SmallVector<UInt32, 3> outputPadding_ = {};
        UInt32 groupCount_ = 1;
        X::FusedActivation fusedActivation_;
        TensorDimensions outputSizes_ = {};
    public:
        ConvolutionBuilder( Expression input, Expression filter, std::optional<Expression> bias = std::nullopt )
            : input_( input ), filter_( filter ), bias_( bias )
        {
        }

        ConvolutionBuilder& Mode( DML::ConvolutionMode mode ) 
        { 
            mode_ = mode; 
            return *this; 
        }
        ConvolutionBuilder& Direction( DML::ConvolutionDirection direction ) 
        { 
            direction_ = direction; 
            return *this; 
        }
        ConvolutionBuilder& Strides( const std::span<const UInt32>& strides ) 
        { 
            strides_.assign( strides.begin( ), strides.end( ) ); 
            return *this; 
        }
        ConvolutionBuilder& Dilations( const std::span<const UInt32>& dilations )
        { 
            dilations_.assign( dilations.begin( ), dilations.end( ) ); 
            return *this; 
        }
        ConvolutionBuilder& StartPadding( const std::span<const UInt32>& startPadding )
        { 
            startPadding_.assign( startPadding.begin( ), startPadding.end( ) ); 
            return *this; 
        }
        ConvolutionBuilder& EndPadding( const std::span<const UInt32>& endPadding ) 
        { 
            endPadding_.assign( endPadding.begin( ), endPadding.end( ) ); 
            return *this; 
        }
        ConvolutionBuilder& OutputPadding( const std::span<const UInt32>& outputPadding )
        { 
            outputPadding_.assign( outputPadding.begin( ), outputPadding.end( ) ); 
            return *this; 
        }
        ConvolutionBuilder& GroupCount( UInt32 groupCount ) 
        { 
            groupCount_ = groupCount; 
            return *this; 
        }
        ConvolutionBuilder& FusedActivation( const FusedActivation& fusedActivation ) 
        { 
            fusedActivation_ = fusedActivation; 
            return *this; 
        }
        ConvolutionBuilder& OutputSizes( const TensorDimensions& outputSizes ) 
        { 
            outputSizes_ = outputSizes; 
            return *this; 
        }

        Expression Build( ) const
        {
            return Convolution(
                input_,
                filter_,
                bias_,
                mode_,
                direction_,
                strides_,
                dilations_,
                startPadding_,
                endPadding_,
                outputPadding_,
                groupCount_,
                fusedActivation_,
                outputSizes_);
        }

    private:
        
    };

    // ---------------------------------------------------------------------------------------------------------------

    inline Expression Gemm(
        Expression a,
        Expression b,
        std::optional<Expression> c = std::nullopt,
        DML::MatrixTransform transA = DML::MatrixTransform::None,
        DML::MatrixTransform transB = DML::MatrixTransform::None,
        float alpha = 1.0f,
        float beta = 1.0f,
        FusedActivation fusedActivation = FusedActivation::None( ) )
    {
        assert( Internal::HasSameOwner( { a, b } ) );
        assert( !c || Internal::HasSameOwner( { a, *c } ) );

        Internal::GraphBuilder* builder = a.Impl( )->GetGraphBuilder( );

        TensorDesc aTensor = a.Impl( )->GetOutputDesc( );
        TensorDesc bTensor = b.Impl( )->GetOutputDesc( );
        TensorDesc cTensor;
        if ( c )
        {
            cTensor = c->Impl( )->GetOutputDesc( );
        }

        TensorDimensions outputSizes;
        outputSizes.push_back( aTensor.Sizes[ 0 ] ); // output[N] = input[N]
        outputSizes.push_back( aTensor.Sizes[ 1 ] ); // output[C] = input[C]
        outputSizes.push_back( transA == DML::MatrixTransform::None ? aTensor.Sizes[ 2 ] : aTensor.Sizes[ 3 ] );
        outputSizes.push_back( transB == DML::MatrixTransform::None ? bTensor.Sizes[ 3 ] : bTensor.Sizes[ 2 ] );

        TensorDesc outputTensor( aTensor.DataType, outputSizes, builder->GetTensorPolicy( ) );
        Internal::FusedActivationStorage storage;

        GEMMOperatorDesc desc = {};
        desc.ATensor = aTensor.As<DML::TensorDesc>( );
        desc.BTensor = bTensor.As<DML::TensorDesc>( );
        desc.CTensor = c ? cTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.TransA = transA;
        desc.TransB = transB;
        desc.Alpha = alpha;
        desc.Beta = beta;
        desc.FusedActivation = Internal::GetFusedActivationPtr( fusedActivation, &storage );

        Internal::NodeOutput* const inputs[ ] = { a.Impl( ), b.Impl( ), c ? c->Impl( ) : nullptr };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    // Helper for setting parameters for the Gemm operator. Parameters left unspecified will be defaulted with the
    // same values as dml::Gemm().
    class GemmBuilder
    {
        Expression a_;
        Expression b_;
        std::optional<Expression> c_;
        DML::MatrixTransform transformA_ = DML::MatrixTransform::None;
        DML::MatrixTransform transformB_ = DML::MatrixTransform::None;
        float alpha_ = 1.0f;
        float beta_ = 1.0f;
        X::FusedActivation fusedActivation_;
    public:
        GemmBuilder( Expression a, Expression b, std::optional<Expression> c = std::nullopt )
            : a_( a ), b_( b ), c_( c )
        {
        }

        GemmBuilder& TransformA( DML::MatrixTransform matrixTransform )
        { 
            transformA_ = matrixTransform;
            return *this;
        }
        GemmBuilder& TransformB( DML::MatrixTransform matrixTransform )
        { 
            transformB_ = matrixTransform;
            return *this; 
        }
        GemmBuilder& Alpha( float alpha ) 
        { 
            alpha_ = alpha; 
            return *this; 
        }
        GemmBuilder& Beta( float beta ) 
        { 
            beta_ = beta; 
            return *this; 
        }
        GemmBuilder& FusedActivation( FusedActivation fusedActivation ) 
        { 
            fusedActivation_ = fusedActivation; 
        return *this; 
        }

        Expression Build( ) const
        {
            return Gemm( a_, b_, c_, transformA_, transformB_, alpha_, beta_, fusedActivation_ );
        }

    private:
        
    };

    // ---------------------------------------------------------------------------------------------------------------

    // If `axes` is not specified, by default this reduces the entire tensor to single element.
    inline Expression Reduce(
        Expression input,
        DML::ReduceFunction function,
        std::span<const UInt32> axes = {},
        DML::TensorDataType outputDataType = DML::TensorDataType::Unknown )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        UInt32 dimensionCount = static_cast< UInt32 >( inputTensor.Sizes.size( ) );

        SmallVector<UInt32, 4> defaultAxes;
        if ( axes.empty( ) )
        {
            for ( UInt32 i = 0; i < dimensionCount; ++i )
            {
                defaultAxes.push_back( i );
            }
            axes = defaultAxes;
        }

        // Compute the output tensor dimensions
        TensorDimensions outputSizes;
        for ( UInt32 i = 0; i < dimensionCount; ++i )
        {
            // If the dimension is to be reduced, this dimension in the output tensor has a size of 1, otherwise
            // it matches the input tensor.
            const bool dimensionIsReduced = std::find( axes.begin( ), axes.end( ), i ) != axes.end( );
            if ( dimensionIsReduced )
            {
                outputSizes.push_back( 1 );
            }
            else
            {
                outputSizes.push_back( inputTensor.Sizes[ i ] );
            }
        }

        // All reductions other than ARGMIN and ARGMAX produce an output with the same type
        // as the input.
        if ( outputDataType == DML::TensorDataType::Unknown )
        {
            if ( function == DML::ReduceFunction::ArgMin || function == DML::ReduceFunction::ArgMax )
            {
                // Default to UINT32 if the output type wasn't specified
                outputDataType = DML::TensorDataType::UInt32;
            }
            else
            {
                outputDataType = inputTensor.DataType;
            }
        }

        TensorDesc outputTensor( outputDataType, outputSizes, builder->GetTensorPolicy( ) );

        ReduceOperatorDesc desc = {};
        desc.Function = function;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.AxisCount = static_cast< UInt32 >( axes.size( ) );
        desc.Axes = axes.data( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, outputTensor );

        return output;
    }

    inline Expression AveragePooling(
        Expression input,
        std::span<const UInt32> strides,
        std::span<const UInt32> windowSizes,
        std::span<const UInt32> startPadding,
        std::span<const UInt32> endPadding,
#if DML_TARGET_VERSION >= 0x6200
        std::span<const UInt32> dilations,
#endif // DML_TARGET_VERSION >= 0x6200
        bool includePadding,
        TensorDimensions outputSizes = {} )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );

#if DML_TARGET_VERSION >= 0x6200
        const UInt32 defaultStridesAndDilations[ 3 ] = { 1, 1, 1 };

        AveragePooling1OperatorDesc averagePoolDesc;
        // dilations must be omitted or have the same rank as the spatial dimension count (inputTensor rank - 2)
        assert( dilations.empty( ) || dilations.size( ) == inputTensor.Sizes.size( ) - 2 );
        averagePoolDesc.Dilations = dilations.empty( ) ? defaultStridesAndDilations : dilations.data( );
#else
        AveragePoolingOperatorDesc averagePoolDesc = {};
#endif // DML_TARGET_VERSION >= 0x6200

        assert( strides.size( ) == windowSizes.size( ) );
        assert( strides.size( ) == startPadding.size( ) );
        assert( strides.size( ) == endPadding.size( ) );

        // Calculate output size, if not explicitly provided
        if ( outputSizes.empty( ) )
        {
            outputSizes.push_back( inputTensor.Sizes[ 0 ] ); // N
            outputSizes.push_back( inputTensor.Sizes[ 1 ] ); // C
            for ( size_t i = 0; i < windowSizes.size( ); ++i )
            {
                UInt32 paddedInputSize = inputTensor.Sizes[ 2 + i ] + startPadding[ i ] + endPadding[ i ];
                UInt32 outputSize = ( paddedInputSize - windowSizes[ i ] ) / strides[ i ] + 1;
                outputSizes.push_back( outputSize );
            }
        }

        TensorDesc outputTensor( inputTensor.DataType, outputSizes, builder->GetTensorPolicy( ) );

        averagePoolDesc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        averagePoolDesc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        averagePoolDesc.DimensionCount = static_cast< UInt32 >( windowSizes.size( ) );
        averagePoolDesc.Strides = strides.data( );
        averagePoolDesc.WindowSize = windowSizes.data( );
        averagePoolDesc.StartPadding = startPadding.data( );
        averagePoolDesc.EndPadding = endPadding.data( );
        averagePoolDesc.IncludePadding = includePadding;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
#if DML_TARGET_VERSION >= 0x6200
        Internal::NodeID node = builder->CreateOperatorNode( averagePoolDesc, inputs );
#else
        Internal::NodeID node = builder->CreateOperatorNode( averagePoolDesc, inputs );
#endif // DML_TARGET_VERSION >= 0x6200

        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    // 
    // TODO: LpPooling
    // 

    // ---------------------------------------------------------------------------------------------------------------

    struct MaxPoolingOutputs
    {
        Expression values;
        Expression indices; // Only valid if outputIndices = true is supplied to MaxPooling()
    };

    // If not specified, parameters are defaulted to the following values:
    //   Strides = 1 for each spatial dimension
    //   StartPadding = 0 for each spatial dimension
    //   EndPadding = 0 for each spatial dimension
    //   Dilations = 1 for each spatial dimension
    //   OutputIndices = false
    inline MaxPoolingOutputs MaxPooling(
        Expression input,
        std::span<const UInt32> windowSize,
        std::span<const UInt32> strides = {},
        std::span<const UInt32> startPadding = {},
        std::span<const UInt32> endPadding = {},
        std::span<const UInt32> dilations = {},
        bool outputIndices = false,
        TensorDimensions outputSizes = {} )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );

        // If the spatial dimension count is 2, we'll just use the first two elements by setting
        // DimensionCount = 2 in the desc
        const UInt32 defaultStridesAndDilations[ 3 ] = { 1, 1, 1 };
        const UInt32 defaultPadding[ 3 ] = { 0, 0, 0 };

        assert( windowSize.size( ) == 2 || windowSize.size( ) == 3 );
        assert( strides.empty( ) || strides.size( ) == windowSize.size( ) );
        assert( dilations.empty( ) || dilations.size( ) == windowSize.size( ) );
        assert( startPadding.empty( ) || startPadding.size( ) == windowSize.size( ) );
        assert( endPadding.empty( ) || endPadding.size( ) == windowSize.size( ) );

        strides = strides.empty( ) ? std::span<const UInt32>{ defaultStridesAndDilations } : strides;
        dilations = dilations.empty( ) ? std::span<const UInt32>{ defaultStridesAndDilations } : dilations;
        startPadding = startPadding.empty( ) ? std::span<const UInt32>{ defaultPadding } : startPadding;
        endPadding = endPadding.empty( ) ? std::span<const UInt32>{ defaultPadding } : endPadding;

        // Calculate output size, if not explicitly provided
        if ( outputSizes.empty( ) )
        {
            outputSizes.push_back( inputTensor.Sizes[ 0 ] ); // N
            outputSizes.push_back( inputTensor.Sizes[ 1 ] ); // C
            for ( size_t i = 0; i < windowSize.size( ); i++ )
            {
                UInt32 paddedInputSize = inputTensor.Sizes[ 2 + i ] + startPadding[ i ] + endPadding[ i ];
                UInt32 dilatedWindowSize = 1 + ( windowSize[ i ] - 1 ) * dilations[ i ];
                UInt32 outputSize = ( dilatedWindowSize >= paddedInputSize ) ? 1 : ( paddedInputSize - dilatedWindowSize ) / strides[ i ] + 1;
                outputSizes.push_back( outputSize );
            }
        }

        TensorDesc outputTensor( inputTensor.DataType, outputSizes, builder->GetTensorPolicy( ) );
        TensorDesc outputIndicesTensor( DML::TensorDataType::UInt32, outputSizes, builder->GetTensorPolicy( ) );

        MaxPooling2OperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.OutputIndicesTensor = outputIndices ? outputIndicesTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.DimensionCount = static_cast< UInt32 >( windowSize.size( ) );
        desc.Strides = strides.data( );
        desc.WindowSize = windowSize.data( );
        desc.StartPadding = startPadding.data( );
        desc.EndPadding = endPadding.data( );
        desc.Dilations = dilations.data( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );

        Internal::NodeOutput* outputExpr = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );
        if ( outputIndices )
        {
            Internal::NodeOutput* outputIndicesExpr = builder->CreateNodeOutput( node, 1, std::move( outputIndicesTensor ) );
            return { outputExpr, outputIndicesExpr };
        }
        return { outputExpr, Expression( ) };
    }

    // Helper for setting parameters for the MaxPooling operator. Sample usage:
    // 
    //   auto [out, outIndices] = dml::MaxPoolingBuilder(...)
    //        .StartPadding(...)
    //        .EndPadding(...)
    //        .OutputIndices(...)
    //        .Build();
    // 
    // Parameters left unspecified will be defaulted with the same values as dml::MaxPooling().
    class MaxPoolingBuilder
    {
        Expression input_;
        SmallVector<UInt32, 3> windowSize_;
        SmallVector<UInt32, 3> strides_ = {};
        SmallVector<UInt32, 3> startPadding_ = {};
        SmallVector<UInt32, 3> endPadding_ = {};
        SmallVector<UInt32, 3> dilations_ = {};
        bool outputIndices_ = false;
        TensorDimensions outputSizes_ = {};
    public:
        MaxPoolingBuilder( const Expression& input, const std::span<const UInt32>& windowSize )
            : input_( input ), windowSize_( windowSize.begin( ), windowSize.end( ) )
        {
        }

        MaxPoolingBuilder& Strides( const std::span<const UInt32>& strides ) 
        { 
            strides_.assign( strides.begin( ), strides.end( ) ); 
            return *this; 
        }
        MaxPoolingBuilder& StartPadding( const std::span<const UInt32>& startPadding ) 
        { 
            startPadding_.assign( startPadding.begin( ), startPadding.end( ) ); 
            return *this; 
        }
        MaxPoolingBuilder& EndPadding( const std::span<const UInt32>& endPadding ) 
        { 
            endPadding_.assign( endPadding.begin( ), endPadding.end( ) ); 
            return *this; 
        }
        MaxPoolingBuilder& Dilations( const std::span<const UInt32>& dilations ) 
        { 
            dilations_.assign( dilations.begin( ), dilations.end( ) ); 
            return *this; 
        }
        MaxPoolingBuilder& OutputIndices( bool outputIndices ) 
        { 
            outputIndices_ = outputIndices; 
            return *this; 
        }
        MaxPoolingBuilder& OutputSizes( const TensorDimensions& outputSizes ) 
        { 
            outputSizes_ = outputSizes; 
            return *this; 
        }

        MaxPoolingOutputs Build( ) const
        {
            return MaxPooling( input_, windowSize_, strides_, startPadding_, endPadding_, dilations_, outputIndices_, outputSizes_);
        }
    };

    // ---------------------------------------------------------------------------------------------------------------

    // 
    // TODO: MaxUnpooling
    // 

    // 
    // TODO: ROIPooling
    // 

    inline Expression Slice(
        Expression input,
        std::span<const UInt32> inputWindowOffsets,
        std::span<const UInt32> inputWindowSizes,
        std::span<const int32_t> inputWindowStrides )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDimensions outputSizes( inputTensor.Sizes );

        assert( inputWindowOffsets.size( ) == outputSizes.size( ) );
        assert( inputWindowOffsets.size( ) == inputWindowStrides.size( ) );
        assert( inputWindowOffsets.size( ) == inputWindowSizes.size( ) );

        for ( size_t i = 0; i < outputSizes.size( ); i++ )
        {
            UInt32 minimumInputSize = ( inputWindowSizes[ i ] - 1 ) / abs( inputWindowStrides[ i ] ) + 1;
            outputSizes[ i ] = minimumInputSize;
        }

        TensorDesc outputTensor( inputTensor.DataType, outputSizes, builder->GetTensorPolicy( ) );

        Slice1OperatorDesc sliceDesc;
        sliceDesc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        sliceDesc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        sliceDesc.DimensionCount = static_cast< UInt32 >( inputWindowOffsets.size( ) );
        sliceDesc.InputWindowOffsets = inputWindowOffsets.data( );
        sliceDesc.InputWindowSizes = inputWindowSizes.data( );
        sliceDesc.InputWindowStrides = inputWindowStrides.data( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( sliceDesc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression Cast( Expression input, DML::TensorDataType targetDataType )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( targetDataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        CastOperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline std::vector<Expression> Split( Expression input, UInt32 axis, std::span<const UInt32> outputAxisSizes )
    {
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        UInt32 axisSizeSum = 0;

        std::vector<TensorDesc> outputTensors;
        outputTensors.reserve( outputAxisSizes.size( ) );

        std::vector<DML::TensorDesc> outputDescs;
        outputDescs.reserve( outputAxisSizes.size( ) );

        for ( UInt32 outputAxisSize : outputAxisSizes )
        {
            TensorDimensions outputSizes = inputTensor.Sizes;
            outputSizes[ axis ] = outputAxisSize;

            TensorDesc tensorDesc( inputTensor.DataType, outputSizes, builder->GetTensorPolicy( ) );
            outputTensors.push_back( std::move( tensorDesc ) );
            outputDescs.push_back( *outputTensors.back( ).As<DML::TensorDesc>( ) );

            axisSizeSum += outputAxisSize;
        }

        assert( axisSizeSum == inputTensor.Sizes[ axis ] );

        SplitOperatorDesc desc = {};
        desc.Axis = axis;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensors = outputDescs.data( );
        desc.OutputCount = static_cast< UInt32 >( outputAxisSizes.size( ) );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );

        std::vector<Expression> outputs;
        outputs.reserve( outputAxisSizes.size( ) );

        for ( UInt32 i = 0; i < outputAxisSizes.size( ); ++i )
        {
            outputs.push_back( builder->CreateNodeOutput( node, i, std::move( outputTensors[ i ] ) ) );
        }

        return outputs;
    }

    inline Expression Join( std::span<const Expression> inputs, UInt32 axis )
    {
        assert( !inputs.empty( ) );

        Internal::GraphBuilder* builder = inputs[ 0 ].Impl( )->GetGraphBuilder( );
        DML::TensorDataType dataType = inputs[ 0 ].Impl( )->GetOutputDesc( ).DataType;

        TensorDimensions outputSizes = inputs[ 0 ].Impl( )->GetOutputDesc( ).Sizes;
        outputSizes[ axis ] = 0;

        std::vector<TensorDesc> inputTensors;
        inputTensors.reserve( inputs.size( ) );

        std::vector<DML::TensorDesc> inputDescs;
        inputDescs.reserve( inputs.size( ) );

        std::vector<Internal::NodeOutput*> inputNodes;
        inputNodes.reserve( inputs.size( ) );

        for ( Expression input : inputs )
        {
            inputTensors.push_back( input.Impl( )->GetOutputDesc( ) );
            TensorDesc& inputTensor = inputTensors.back( );
            outputSizes[ axis ] += inputTensor.Sizes[ axis ];
            inputDescs.push_back( *inputTensor.As<DML::TensorDesc>( ) );
            inputNodes.push_back( input.Impl( ) );
        }

        TensorDesc outputTensor( dataType, std::move( outputSizes ), builder->GetTensorPolicy( ) );

        JoinOperatorDesc desc = {};
        desc.Axis = axis;
        desc.InputCount = static_cast< UInt32 >( inputDescs.size( ) );
        desc.InputTensors = inputDescs.data( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );

        Internal::NodeID node = builder->CreateOperatorNode( desc, inputNodes );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression Padding( Expression input, DML::PaddingMode paddingMode, float paddingValue, std::span<const UInt32> startPadding, std::span<const UInt32> endPadding )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDimensions outputSizes = inputTensor.Sizes;

        assert( outputSizes.size( ) == startPadding.size( ) );
        assert( outputSizes.size( ) == endPadding.size( ) );

        for ( size_t i = 0; i < outputSizes.size( ); i++ )
        {
            outputSizes[ i ] += startPadding[ i ] + endPadding[ i ];
        }

        TensorDesc outputTensor( inputTensor.DataType, outputSizes, builder->GetTensorPolicy( ) );

        PaddingOperatorDesc paddingDesc;
        paddingDesc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        paddingDesc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        paddingDesc.PaddingMode = paddingMode;
        paddingDesc.PaddingValue = paddingValue;
        paddingDesc.DimensionCount = static_cast< UInt32 >( startPadding.size( ) );
        paddingDesc.StartPadding = startPadding.data( );
        paddingDesc.EndPadding = endPadding.data( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( paddingDesc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression ValueScale2D( Expression input, float scale, std::span<const float> bias )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        ValueScale2DOperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.Scale = scale;
        desc.ChannelCount = static_cast< UInt32 >( bias.size( ) );
        desc.Bias = bias.data( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression Upsample2D( Expression input, DML::Size2D scaleSize, DML::InterpolationMode interpolationMode )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        assert( inputTensor.Sizes.size( ) == 4 || inputTensor.Sizes.size( ) == 5 );

        UInt32 i = 0;
        TensorDimensions outputSizes;
        outputSizes.push_back( inputTensor.Sizes[ i++ ] );                    // output[N] = input[N]
        outputSizes.push_back( inputTensor.Sizes[ i++ ] );                    // output[C] = input[C]
        if ( inputTensor.Sizes.size( ) == 5 )
        {
            outputSizes.push_back( inputTensor.Sizes[ i++ ] );                // output[D] = input[D]
        }
        outputSizes.push_back( inputTensor.Sizes[ i++ ] * scaleSize.Height ); // output[H] = input[H] * scaleH
        outputSizes.push_back( inputTensor.Sizes[ i++ ] * scaleSize.Width );  // output[W] = input[W] * scaleW
        TensorDesc outputTensor( inputTensor.DataType, std::move( outputSizes ), builder->GetTensorPolicy( ) );

        UpSample2DOperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.ScaleSize = scaleSize;
        desc.InterpolationMode = interpolationMode;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression Gather(
        Expression input,
        Expression indices,
        UInt32 axis,
        UInt32 indexDimensions )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc indicesTensor = indices.Impl( )->GetOutputDesc( );

        UInt32 dimensionCount = static_cast< UInt32 >( inputTensor.Sizes.size( ) );
        assert( indicesTensor.Sizes.size( ) == dimensionCount );
        assert( axis < dimensionCount );
        assert( indexDimensions <= dimensionCount );

        TensorDimensions outputSizes( dimensionCount, 1 );

        // All dimensions after the axis should be the same as the input
        int outputDim = static_cast< int >( dimensionCount ) - 1;
        for ( ; static_cast< UInt32 >( outputDim ) > axis; --outputDim )
        {
            outputSizes[ outputDim ] = inputTensor.Sizes[ outputDim ];
        }

        // All dimensions within the range [axis - indexDimensions, axis] should be the same as the indices
        int indexDim = static_cast< int >( dimensionCount ) - 1;
        for ( ; outputDim > static_cast< int >( axis ) - static_cast< int >( indexDimensions ); --outputDim, --indexDim )
        {
            outputSizes[ outputDim ] = indicesTensor.Sizes[ indexDim ];
        }

        // All dimensions before (axis - indexDimensions) should be the same as the input
        int inputDim = axis - 1;
        for ( ; outputDim >= 0 && inputDim >= 0; --outputDim, --inputDim )
        {
            outputSizes[ outputDim ] = inputTensor.Sizes[ inputDim ];
        }

        TensorDesc outputTensor( inputTensor.DataType, outputSizes, builder->GetTensorPolicy( ) );

        GatherOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.IndicesTensor = indicesTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.Axis = axis;
        desc.IndexDimensions = indexDimensions;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), indices.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression GatherElements(
        Expression input,
        Expression indices,
        UInt32 axis )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc indicesTensor = indices.Impl( )->GetOutputDesc( );

        TensorDesc outputTensor( inputTensor.DataType, indicesTensor.Sizes, builder->GetTensorPolicy( ) );

        GatherElementsOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.IndicesTensor = indicesTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.Axis = axis;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), indices.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression GatherND( Expression input, Expression indices, UInt32 inputDimensionCount, UInt32 indicesDimensionCount, UInt32 batchDimensionCount )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc indicesTensor = indices.Impl( )->GetOutputDesc( );

        assert( inputDimensionCount >= 1u && inputDimensionCount <= inputTensor.Sizes.size( ) );
        assert( indicesDimensionCount >= 1u && indicesDimensionCount <= indicesTensor.Sizes.size( ) );
        assert( batchDimensionCount < inputDimensionCount );
        assert( batchDimensionCount < indicesDimensionCount );

        UInt32 numberOfCoordinatesPerIndex = indicesTensor.Sizes.back( );
        assert( numberOfCoordinatesPerIndex >= 1u && numberOfCoordinatesPerIndex <= inputDimensionCount - batchDimensionCount );

        UInt32 numberOfOutputDimensionsFromInput = inputDimensionCount - batchDimensionCount - numberOfCoordinatesPerIndex;
        UInt32 outputPaddingAmount = static_cast< UInt32 >( inputTensor.Sizes.size( ) ) - ( indicesDimensionCount + numberOfOutputDimensionsFromInput - 1 );

        TensorDimensions outputSizes( outputPaddingAmount, 1 );
        outputSizes.insert( outputSizes.end( ), indicesTensor.Sizes.end( ) - indicesDimensionCount, indicesTensor.Sizes.end( ) - 1 );
        outputSizes.insert( outputSizes.end( ), inputTensor.Sizes.end( ) - numberOfOutputDimensionsFromInput, inputTensor.Sizes.end( ) );

        TensorDesc outputTensor( inputTensor.DataType, outputSizes, builder->GetTensorPolicy( ) );

        GatherND1OperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.IndicesTensor = indicesTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.InputDimensionCount = inputDimensionCount;
        desc.IndicesDimensionCount = indicesDimensionCount;
        desc.BatchDimensionCount = batchDimensionCount;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), indices.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression ScatterElements( Expression input, Expression indices, Expression updates, UInt32 axis )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc indicesTensor = indices.Impl( )->GetOutputDesc( );
        TensorDesc updatesTensor = updates.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        ScatterElementsOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.IndicesTensor = indicesTensor.As<DML::TensorDesc>( );
        desc.UpdatesTensor = updatesTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.Axis = axis;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), indices.Impl( ), updates.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression ScatterND(
        Expression input,
        Expression indices,
        Expression updates,
        UInt32 inputDimensionCount,
        UInt32 indicesDimensionCount )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc indicesTensor = indices.Impl( )->GetOutputDesc( );
        TensorDesc updatesTensor = updates.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        ScatterNDOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.IndicesTensor = indicesTensor.As<DML::TensorDesc>( );
        desc.UpdatesTensor = updatesTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.InputDimensionCount = inputDimensionCount;
        desc.IndicesDimensionCount = indicesDimensionCount;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), indices.Impl( ), updates.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression SpaceToDepth(
        Expression input,
        UInt32 blockSize,
        DML::DepthSpaceOrder order = DML::DepthSpaceOrder::DepthColumnRow )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );

        assert( inputTensor.Sizes.size( ) == 4 );

        TensorDimensions outputSizes = {
            inputTensor.Sizes[ 0 ],
            inputTensor.Sizes[ 1 ] * blockSize * blockSize,
            inputTensor.Sizes[ 2 ] / blockSize,
            inputTensor.Sizes[ 3 ] / blockSize
        };

        TensorDesc outputTensor( inputTensor.DataType, outputSizes, builder->GetTensorPolicy( ) );

        SpaceToDepth1OperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.BlockSize = blockSize;
        desc.Order = order;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, outputTensor );

        return output;
    }

    inline Expression DepthToSpace(
        Expression input,
        UInt32 blockSize,
        DML::DepthSpaceOrder order = DML::DepthSpaceOrder::DepthColumnRow )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );

        assert( inputTensor.Sizes.size( ) == 4 );

        TensorDimensions outputSizes = {
            inputTensor.Sizes[ 0 ],
            inputTensor.Sizes[ 1 ] / ( blockSize * blockSize ),
            inputTensor.Sizes[ 2 ] * blockSize,
            inputTensor.Sizes[ 3 ] * blockSize
        };

        TensorDesc outputTensor( inputTensor.DataType, outputSizes, builder->GetTensorPolicy( ) );

        DepthToSpace1OperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.BlockSize = blockSize;
        desc.Order = order;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression Tile( Expression input, std::span<const UInt32> repeats )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDimensions outputSizes = input.GetOutputDesc( ).Sizes;

        assert( repeats.size( ) == outputSizes.size( ) );

        for ( size_t i = 0; i < repeats.size( ); ++i )
        {
            outputSizes[ i ] *= repeats[ i ];
        }

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, std::move( outputSizes ), builder->GetTensorPolicy( ) );

        TileOperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.RepeatsCount = static_cast< UInt32 >( repeats.size( ) );
        desc.Repeats = repeats.data( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, outputTensor );

        return output;
    }

    struct TopKOutputs
    {
        Expression value;
        Expression index;
    };

    inline TopKOutputs TopK( Expression input, UInt32 axis, UInt32 k, DML::AxisDirection axisDirection )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );

        TensorDimensions outputSizes = inputTensor.Sizes;
        outputSizes.back( ) = k;

        TensorDesc outputValueTensor( inputTensor.DataType, outputSizes, builder->GetTensorPolicy( ) );
        TensorDesc outputIndexTensor( DML::TensorDataType::UInt32, outputSizes, builder->GetTensorPolicy( ) );

        TopK1OperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputValueTensor = outputValueTensor.As<DML::TensorDesc>( );
        desc.OutputIndexTensor = outputIndexTensor.As<DML::TensorDesc>( );
        desc.Axis = axis;
        desc.K = k;
        desc.AxisDirection = axisDirection;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* outputValue = builder->CreateNodeOutput( node, 0, std::move( outputValueTensor ) );
        Internal::NodeOutput* outputIndex = builder->CreateNodeOutput( node, 1, std::move( outputIndexTensor ) );

        return { outputValue, outputIndex };
    }

    inline Expression BatchNormalization(
        Expression input,
        Expression mean,
        Expression variance,
        Expression scale,
        Expression bias,
        bool spatial,
        float epsilon,
        FusedActivation fusedActivation = FusedActivation::None( ) )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc meanTensor = mean.Impl( )->GetOutputDesc( );
        TensorDesc varianceTensor = variance.Impl( )->GetOutputDesc( );
        TensorDesc scaleTensor = scale.Impl( )->GetOutputDesc( );
        TensorDesc biasTensor = bias.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        Internal::FusedActivationStorage storage;

        BatchNormalizationOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.MeanTensor = meanTensor.As<DML::TensorDesc>( );
        desc.VarianceTensor = varianceTensor.As<DML::TensorDesc>( );
        desc.ScaleTensor = scaleTensor.As<DML::TensorDesc>( );
        desc.BiasTensor = biasTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.Spatial = spatial;
        desc.Epsilon = epsilon;
        desc.FusedActivation = Internal::GetFusedActivationPtr( fusedActivation, &storage );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), mean.Impl( ), variance.Impl( ), scale.Impl( ), bias.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

#if DML_TARGET_VERSION >= 0x3100

    struct BatchNormalizationGradOutputs
    {
        Expression gradient;
        Expression scaleGradient;
        Expression biasGradient;
    };

    inline BatchNormalizationGradOutputs BatchNormalizationGrad(
        Expression input,
        Expression inputGradient,
        Expression mean,
        Expression variance,
        Expression scale,
        float epsilon )
    {
        Internal::GraphBuilder* builder = mean.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc inputGradientTensor = inputGradient.Impl( )->GetOutputDesc( );
        TensorDesc meanTensor = mean.Impl( )->GetOutputDesc( );
        TensorDesc varianceTensor = variance.Impl( )->GetOutputDesc( );
        TensorDesc scaleTensor = scale.Impl( )->GetOutputDesc( );
        TensorDesc outputGradientTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );
        TensorDesc outputScaleGradientTensor( meanTensor.DataType, meanTensor.Sizes, builder->GetTensorPolicy( ) );
        TensorDesc outputBiasGradientTensor( meanTensor.DataType, meanTensor.Sizes, builder->GetTensorPolicy( ) );

        BatchNormalizationGradOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.InputGradientTensor = inputGradientTensor.As<DML::TensorDesc>( );
        desc.MeanTensor = meanTensor.As<DML::TensorDesc>( );
        desc.VarianceTensor = varianceTensor.As<DML::TensorDesc>( );
        desc.ScaleTensor = scaleTensor.As<DML::TensorDesc>( );
        desc.Epsilon = epsilon;

        desc.OutputGradientTensor = outputGradientTensor.As<DML::TensorDesc>( );
        desc.OutputScaleGradientTensor = outputScaleGradientTensor.As<DML::TensorDesc>( );
        desc.OutputBiasGradientTensor = outputBiasGradientTensor.As<DML::TensorDesc>( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), inputGradient.Impl( ), mean.Impl( ), variance.Impl( ), scale.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );

        BatchNormalizationGradOutputs outputValues;
        outputValues.gradient = builder->CreateNodeOutput( node, 0, *desc.OutputGradientTensor );
        outputValues.scaleGradient = builder->CreateNodeOutput( node, 1, *desc.OutputScaleGradientTensor );
        outputValues.biasGradient = builder->CreateNodeOutput( node, 2, *desc.OutputBiasGradientTensor );

        return outputValues;
    }

#endif // DML_TARGET_VERSION >= 0x3100

#if DML_TARGET_VERSION >= 0x4100
    struct BatchNormalizationTrainingOutputs
    {
        Expression output;
        Expression mean;
        Expression variance;
    };

    inline BatchNormalizationTrainingOutputs BatchNormalizationTraining(
        Expression input,
        Expression scale,
        Expression bias,
        std::optional<Expression> fusedAdd,
        float epsilon,
        FusedActivation fusedActivation = FusedActivation::None( ) )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc scaleTensor = scale.Impl( )->GetOutputDesc( );
        TensorDesc biasTensor = bias.Impl( )->GetOutputDesc( );

        TensorDesc fusedAddTensor;
        if ( fusedAdd )
        {
            fusedAddTensor = fusedAdd->Impl( )->GetOutputDesc( );
        }

        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );
        TensorDesc outputMeanTensor( inputTensor.DataType, scaleTensor.Sizes, builder->GetTensorPolicy( ) );
        TensorDesc outputVarianceTensor( inputTensor.DataType, scaleTensor.Sizes, builder->GetTensorPolicy( ) );

        Internal::FusedActivationStorage storage;

        BatchNormalizationTrainingOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.ScaleTensor = scaleTensor.As<DML::TensorDesc>( );
        desc.BiasTensor = biasTensor.As<DML::TensorDesc>( );
        desc.FusedAddTensor = fusedAdd.has_value( ) ? fusedAddTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.OutputMeanTensor = outputMeanTensor.As<DML::TensorDesc>( );
        desc.OutputVarianceTensor = outputVarianceTensor.As<DML::TensorDesc>( );
        desc.Epsilon = epsilon;
        desc.FusedActivation = Internal::GetFusedActivationPtr( fusedActivation, &storage );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), scale.Impl( ), bias.Impl( ), fusedAdd ? fusedAdd->Impl( ) : nullptr };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );
        Internal::NodeOutput* outputMean = builder->CreateNodeOutput( node, 1, std::move( outputMeanTensor ) );
        Internal::NodeOutput* outputVariance = builder->CreateNodeOutput( node, 2, std::move( outputVarianceTensor ) );

        return { output, outputMean, outputVariance };
    }

    inline BatchNormalizationGradOutputs BatchNormalizationTrainingGrad(
        Expression input,
        Expression inputGradient,
        Expression mean,
        Expression variance,
        Expression scale,
        float epsilon )
    {
        Internal::GraphBuilder* builder = mean.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc inputGradientTensor = inputGradient.Impl( )->GetOutputDesc( );
        TensorDesc meanTensor = mean.Impl( )->GetOutputDesc( );
        TensorDesc varianceTensor = variance.Impl( )->GetOutputDesc( );
        TensorDesc scaleTensor = scale.Impl( )->GetOutputDesc( );
        TensorDesc outputGradientTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );
        TensorDesc outputScaleGradientTensor( meanTensor.DataType, meanTensor.Sizes, builder->GetTensorPolicy( ) );
        TensorDesc outputBiasGradientTensor( meanTensor.DataType, meanTensor.Sizes, builder->GetTensorPolicy( ) );

        BatchNormalizationTrainingGradOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.InputGradientTensor = inputGradientTensor.As<DML::TensorDesc>( );
        desc.MeanTensor = meanTensor.As<DML::TensorDesc>( );
        desc.VarianceTensor = varianceTensor.As<DML::TensorDesc>( );
        desc.ScaleTensor = scaleTensor.As<DML::TensorDesc>( );
        desc.Epsilon = epsilon;

        desc.OutputGradientTensor = outputGradientTensor.As<DML::TensorDesc>( );
        desc.OutputScaleGradientTensor = outputScaleGradientTensor.As<DML::TensorDesc>( );
        desc.OutputBiasGradientTensor = outputBiasGradientTensor.As<DML::TensorDesc>( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), inputGradient.Impl( ), mean.Impl( ), variance.Impl( ), scale.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );

        BatchNormalizationGradOutputs outputValues;
        outputValues.gradient = builder->CreateNodeOutput( node, 0, *desc.OutputGradientTensor );
        outputValues.scaleGradient = builder->CreateNodeOutput( node, 1, *desc.OutputScaleGradientTensor );
        outputValues.biasGradient = builder->CreateNodeOutput( node, 2, *desc.OutputBiasGradientTensor );

        return outputValues;
    }
#endif // DML_TARGET_VERSION >= 0x4100

    inline Expression MeanVarianceNormalization(
        Expression input,
        std::optional<Expression> scale,
        std::optional<Expression> bias,
        std::span<const UInt32> axes,
        bool normalizeVariance,
#if DML_TARGET_VERSION >= 0x6300
        bool normalizeMean,
#endif
        float epsilon,
        FusedActivation fusedActivation = FusedActivation::None( ) )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );
        TensorDesc scaleTensor;
        TensorDesc biasTensor;

        if ( scale )
        {
            scaleTensor = scale->Impl( )->GetOutputDesc( );
        }
        if ( bias )
        {
            biasTensor = bias->Impl( )->GetOutputDesc( );
        }

        Internal::FusedActivationStorage storage;

#if DML_TARGET_VERSION >= 0x6300
        MeanVarianceNormalization2OperatorDesc desc = {};
        desc.UseMean = normalizeMean;
        desc.UseVariance = normalizeVariance;
#else
        MeanVarianceNormalization1OperatorDesc desc = {};
        desc.NormalizeVariance = normalizeVariance;
#endif
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.ScaleTensor = scale ? scaleTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.BiasTensor = bias ? biasTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.AxisCount = static_cast< UINT >( axes.size( ) );
        desc.Axes = axes.data( );
        desc.Epsilon = epsilon;
        desc.FusedActivation = Internal::GetFusedActivationPtr( fusedActivation, &storage );

        Internal::NodeOutput* const inputs[ ] =
        {
            input.Impl( ),
            scale ? scale->Impl( ) : nullptr,
            bias ? bias->Impl( ) : nullptr
        };

#if DML_TARGET_VERSION >= 0x6300
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
#else
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
#endif

        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression LocalResponseNormalization(
        Expression input,
        bool crossChannel,
        UInt32 localSize,
        float alpha,
        float beta,
        float bias )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        LocalResponseNormalizationOperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.CrossChannel = crossChannel;
        desc.LocalSize = localSize;
        desc.Alpha = alpha;
        desc.Beta = beta;
        desc.Bias = bias;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    // 
    // TODO: LpNormalization
    // 

    // 
    // TODO: RNN
    // 

    // 
    // TODO: LSTM
    // 

    enum class GRUOutputOptions
    {
        Both,
        Sequence,
        Single,
    };

    struct GRUOutputs
    {
        Expression sequence;
        Expression single;
    };

    inline GRUOutputs GRU(
        Expression input,
        Expression weight,
        Expression recurrence,
        std::optional<Expression> bias,
        std::optional<Expression> hiddenInit,
        std::optional<Expression> sequenceLengths,
        std::span<const FusedActivation> activationDescs,
        DML::RecurrentNetworkDirection direction,
        bool linearBeforeReset,
        GRUOutputOptions outputOptions )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc weightTensor = weight.Impl( )->GetOutputDesc( );
        TensorDesc recurrenceTensor = recurrence.Impl( )->GetOutputDesc( );
        TensorDesc biasTensor;
        TensorDesc hiddenInitTensor;
        TensorDesc sequenceLengthsTensor;
        TensorDesc outputSequenceTensor;
        TensorDesc outputSingleTensor;
        if ( bias )
        {
            biasTensor = bias->Impl( )->GetOutputDesc( );
        }
        if ( hiddenInit )
        {
            hiddenInitTensor = hiddenInit->Impl( )->GetOutputDesc( );
        }
        if ( sequenceLengths )
        {
            sequenceLengthsTensor = sequenceLengths->Impl( )->GetOutputDesc( );
        }

        TensorDimensions outputSequenceSizes( 4 );
        TensorDimensions outputSingleSizes( 4 );
        UInt32 directionCount = ( direction == DML::RecurrentNetworkDirection::Bidirectional ) ? 2 : 1;
        if ( outputOptions == GRUOutputOptions::Sequence || outputOptions == GRUOutputOptions::Both )
        {
            outputSequenceSizes[ 0 ] = inputTensor.Sizes[ 1 ]; // SequenceLength
            outputSequenceSizes[ 1 ] = directionCount;
            outputSequenceSizes[ 2 ] = inputTensor.Sizes[ 2 ]; // BatchSize
            outputSequenceSizes[ 3 ] = recurrenceTensor.Sizes[ 3 ]; // HiddenSize
            outputSequenceTensor = TensorDesc( inputTensor.DataType, outputSequenceSizes, builder->GetTensorPolicy( ) );
        }
        if ( outputOptions == GRUOutputOptions::Single || outputOptions == GRUOutputOptions::Both )
        {
            outputSingleSizes[ 0 ] = 1;
            outputSingleSizes[ 1 ] = directionCount;
            outputSingleSizes[ 2 ] = inputTensor.Sizes[ 2 ]; // BatchSize
            outputSingleSizes[ 3 ] = recurrenceTensor.Sizes[ 3 ]; // HiddenSize
            outputSingleTensor = TensorDesc( inputTensor.DataType, outputSingleSizes, builder->GetTensorPolicy( ) );
        }

        UInt32 activationCount = static_cast< UInt32 >( activationDescs.size( ) );
        if ( activationCount > 4 )
        {
            HCC_COM_CHECK_HRESULT( E_INVALIDARG );
        }

        Internal::FusedActivationStorage storage[ 4 ];
        DML::OperatorDesc activationDescArray[ 4 ];
        for ( UInt32 i = 0; i < activationCount; ++i )
        {
            activationDescArray[ i ] = *Internal::GetFusedActivationPtr( activationDescs[ i ], &storage[ i ] );
        }

        GRUOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.WeightTensor = weightTensor.As<DML::TensorDesc>( );
        desc.RecurrenceTensor = recurrenceTensor.As<DML::TensorDesc>( );
        desc.BiasTensor = bias ? biasTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.HiddenInitTensor = hiddenInit ? hiddenInitTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.SequenceLengthsTensor = sequenceLengths ? sequenceLengthsTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.OutputSequenceTensor = outputSequenceTensor.Sizes.empty( ) ? nullptr : outputSequenceTensor.As<DML::TensorDesc>( );
        desc.OutputSingleTensor = outputSingleTensor.Sizes.empty( ) ? nullptr : outputSingleTensor.As<DML::TensorDesc>( );
        desc.ActivationDescCount = activationCount;
        desc.ActivationDescs = activationDescArray;
        desc.Direction = direction;
        desc.LinearBeforeReset = linearBeforeReset;

        Internal::NodeOutput* const inputs[ ] =
        {
            input.Impl( ),
            weight.Impl( ),
            recurrence.Impl( ),
            bias ? bias->Impl( ) : nullptr,
            hiddenInit ? hiddenInit->Impl( ) : nullptr,
            sequenceLengths ? sequenceLengths->Impl( ) : nullptr
        };

        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );

        Internal::NodeOutput* outputSequenceExpr = nullptr;
        Internal::NodeOutput* outputSingleExpr = nullptr;
        if ( outputOptions == GRUOutputOptions::Sequence || outputOptions == GRUOutputOptions::Both )
        {
            outputSequenceExpr = builder->CreateNodeOutput( node, 0, std::move( outputSequenceTensor ) );
        }
        if ( outputOptions == GRUOutputOptions::Single || outputOptions == GRUOutputOptions::Both )
        {
            outputSingleExpr = builder->CreateNodeOutput( node, 1, std::move( outputSingleTensor ) );
        }
        return { outputSequenceExpr, outputSingleExpr };
    }

    // 
    // TODO: DiagonalMatrix
    //

    inline Expression OneHot(
        Expression indices,
        Expression values,
        UInt32 outputLength,
        UInt32 axis )
    {
        Internal::GraphBuilder* builder = indices.Impl( )->GetGraphBuilder( );
        TensorDesc indicesTensor = indices.Impl( )->GetOutputDesc( );
        TensorDesc valuesTensor = values.Impl( )->GetOutputDesc( );

        assert( axis < static_cast< UInt32 >( indicesTensor.Sizes.size( ) ) );

        // The output and indices sizes must all match except for the active axis, which is supplied as outputLength.
        TensorDimensions outputSizes = indicesTensor.Sizes;
        outputSizes[ axis ] = outputLength;

        TensorDesc outputTensor( valuesTensor.DataType, std::move( outputSizes ), builder->GetTensorPolicy( ) );

        OneHotOperatorDesc desc = {};
        desc.IndicesTensor = indicesTensor.As<DML::TensorDesc>( );
        desc.ValuesTensor = valuesTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.Axis = axis;

        Internal::NodeOutput* const inputs[ ] = { indices.Impl( ), values.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    // If not specified, parameters are defaulted to the following values:
    //   Scales = computed by dividing the output sizes by the input sizes
    //   InputPixelOffsets = 0.5f for each dimension
    //   OutputPixelOffsets = -0.5f for each dimension
    //   Antialiased = false
    inline Expression Resample(
        Expression input,
        TensorDimensions outputSizes,
        DML::InterpolationMode mode,
#if DML_TARGET_VERSION >= 0x5100
        DML::AxisDirection roundingDirection = DML::AxisDirection::Increasing,
#endif // DML_TARGET_VERSION >= 0x5100
        std::span<const float> scales = {},
        std::span<const float> inputPixelOffsets = {},
        std::span<const float> outputPixelOffsets = {}
#if DML_TARGET_VERSION >= 0x6400
        , bool antialiased = false
#endif
    )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        UInt32 dimensionCount = static_cast< UInt32 >( inputTensor.Sizes.size( ) );
        assert( outputSizes.size( ) == dimensionCount );
        assert( scales.empty( ) || scales.size( ) == dimensionCount );
        assert( inputPixelOffsets.empty( ) || inputPixelOffsets.size( ) == dimensionCount );
        assert( outputPixelOffsets.empty( ) || outputPixelOffsets.size( ) == dimensionCount );

        SmallVector<float, 4> defaultScales;
        if ( scales.empty( ) )
        {
            for ( UInt32 i = 0; i < dimensionCount; ++i )
            {
                defaultScales.push_back( static_cast< float >( outputSizes[ i ] ) / static_cast< float >( inputTensor.Sizes[ i ] ) );
            }
            scales = defaultScales;
        }

        SmallVector<float, 4> defaultInputPixelOffsets;
        if ( inputPixelOffsets.empty( ) )
        {
            defaultInputPixelOffsets.assign( dimensionCount, 0.5f );
            inputPixelOffsets = defaultInputPixelOffsets;
        }

        SmallVector<float, 4> defaultOutputPixelOffsets;
        if ( outputPixelOffsets.empty( ) )
        {
            defaultOutputPixelOffsets.assign( dimensionCount, -0.5f );
            outputPixelOffsets = defaultOutputPixelOffsets;
        }

        TensorDesc outputTensor( inputTensor.DataType, std::move( outputSizes ), builder->GetTensorPolicy( ) );

#if DML_TARGET_VERSION >= 0x6400
        Resample3OperatorDesc desc;
        desc.RoundingDirection = roundingDirection;
        desc.Antialiased = antialiased;
#elif DML_TARGET_VERSION >= 0x5100
        Resample2OperatorDesc desc;
        desc.RoundingDirection = roundingDirection;
#else
        Resample1OperatorDesc desc;
#endif // DML_TARGET_VERSION >= 0x5100

        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.InterpolationMode = mode;
        desc.DimensionCount = dimensionCount;
        desc.Scales = scales.data( );
        desc.InputPixelOffsets = inputPixelOffsets.data( );
        desc.OutputPixelOffsets = outputPixelOffsets.data( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };

#if DML_TARGET_VERSION >= 0x6400
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
#elif DML_TARGET_VERSION >= 0x5100
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
#else
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
#endif // DML_TARGET_VERSION >= 0x5100
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression FillValueConstant(
        Graph& graph,
        TensorDimensions outputSizes,
        DML::TensorDataType valueDataType,
        DML::ScalarUnion value )
    {
        Internal::GraphBuilder* builder = graph.Impl( );
        TensorDesc outputTensor( valueDataType, std::move( outputSizes ), builder->GetTensorPolicy( ) );

        FillValueConstantOperatorDesc desc = {};
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.ValueDataType = valueDataType;
        desc.Value = value;

        Internal::NodeID node = builder->CreateOperatorNode( desc, {} );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression FillValueSequence(
        Graph& graph,
        TensorDimensions outputSizes,
        DML::TensorDataType valueDataType,
        DML::ScalarUnion valueStart,
        DML::ScalarUnion valueDelta )
    {
        Internal::GraphBuilder* builder = graph.Impl( );
        TensorDesc outputTensor( valueDataType, std::move( outputSizes ), builder->GetTensorPolicy( ) );

        FillValueSequenceOperatorDesc desc;
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.ValueDataType = valueDataType;
        desc.ValueStart = valueStart;
        desc.ValueDelta = valueDelta;

        Internal::NodeID node = builder->CreateOperatorNode( desc, {} );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression CumulativeSummation(
        Expression input,
        UInt32 axis,
        DML::AxisDirection axisDirection,
        bool hasExclusiveSum )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        CumulativeSummationOperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.Axis = axis;
        desc.AxisDirection = axisDirection;
        desc.HasExclusiveSum = hasExclusiveSum;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

#if DML_TARGET_VERSION >= 0x3100

    inline Expression CumulativeProduct(
        Expression input,
        UInt32 axis,
        DML::AxisDirection axisDirection,
        bool hasExclusiveProduct )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        CumulativeProductOperatorDesc desc;
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.Axis = axis;
        desc.AxisDirection = axisDirection;
        desc.HasExclusiveProduct = hasExclusiveProduct;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

#endif // DML_TARGET_VERSION >= 0x3100

    inline Expression ReverseSubsequences(
        Expression input,
        Expression sequenceLengths,
        UInt32 axis )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc sequenceLengthsTensor = sequenceLengths.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( inputTensor.DataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        ReverseSubsequencesOperatorDesc reverseDesc = {};
        reverseDesc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        reverseDesc.SequenceLengthsTensor = sequenceLengthsTensor.As<DML::TensorDesc>( );
        reverseDesc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        reverseDesc.Axis = axis;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), sequenceLengths.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( reverseDesc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    // 
    // TODO: MatrixMultiplyInteger
    // 

    // 
    // TODO: QuantizedLinearMatrixMultiply
    // 

    inline Expression ConvolutionInteger(
        Expression input,
        std::optional<Expression> inputZeroPoint,
        Expression filter,
        std::optional<Expression> filterZeroPoint,
        std::span<const UInt32> strides = {},
        std::span<const UInt32> dilations = {},
        std::span<const UInt32> startPadding = {},
        std::span<const UInt32> endPadding = {},
        UInt32 groupCount = 1,
        TensorDimensions outputSizes = {} )
    {
        assert( Internal::HasSameOwner( { input, filter } ) );
        assert( !inputZeroPoint || Internal::HasSameOwner( { input, *inputZeroPoint } ) );
        assert( !filterZeroPoint || Internal::HasSameOwner( { filter, *filterZeroPoint } ) );

        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc filterTensor = filter.Impl( )->GetOutputDesc( );

        TensorDesc inputZeroPointTensor;
        if ( inputZeroPoint ) { inputZeroPointTensor = inputZeroPoint->Impl( )->GetOutputDesc( ); }

        TensorDesc filterZeroPointTensor;
        if ( filterZeroPoint ) { filterZeroPointTensor = filterZeroPoint->Impl( )->GetOutputDesc( ); }

        UInt32 dimensionCount = static_cast< UInt32 >( inputTensor.Sizes.size( ) );

        // todo: support 1d convolution?
        assert( dimensionCount == 4 || dimensionCount == 5 );
        UInt32 spatialDimensionCount = dimensionCount - 2;

        // If the spatial dimension count is 2, we'll just use the first two elements by setting
        // DimensionCount = 2 in the desc
        const UInt32 defaultStridesAndDilations[ 3 ] = { 1, 1, 1 };
        const UInt32 defaultPadding[ 3 ] = { 0, 0, 0 };

        assert( strides.empty( ) || strides.size( ) == spatialDimensionCount );
        assert( dilations.empty( ) || dilations.size( ) == spatialDimensionCount );
        assert( startPadding.empty( ) || startPadding.size( ) == spatialDimensionCount );
        assert( endPadding.empty( ) || endPadding.size( ) == spatialDimensionCount );
        assert( outputSizes.empty( ) || outputSizes.size( ) == inputTensor.Sizes.size( ) );

        strides = strides.empty( ) ? std::span<const UInt32>{ defaultStridesAndDilations } : strides;
        dilations = dilations.empty( ) ? std::span<const UInt32>{ defaultStridesAndDilations } : dilations;
        startPadding = startPadding.empty( ) ? std::span<const UInt32>{ defaultPadding } : startPadding;
        endPadding = endPadding.empty( ) ? std::span<const UInt32>{ defaultPadding } : endPadding;

        if ( outputSizes.empty( ) )
        {
            outputSizes.push_back( inputTensor.Sizes[ 0 ] ); // output[N] = input[N]
            outputSizes.push_back( filterTensor.Sizes[ 0 ] ); // output[C] = filter[N]

            for ( UInt32 dim = 0; dim < spatialDimensionCount; ++dim )
            {
                UInt32 inputSize = inputTensor.Sizes[ dim + 2 ];
                UInt32 paddedSize = inputSize + startPadding[ dim ] + endPadding[ dim ];

                UInt32 windowSize = filterTensor.Sizes[ dim + 2 ];
                UInt32 kernelSize = 1 + ( windowSize - 1 ) * dilations[ dim ];

                assert( kernelSize <= paddedSize );
                assert( strides[ dim ] != 0 );

                outputSizes.push_back( 1 + ( paddedSize - kernelSize ) / strides[ dim ] );
            }
        }

        TensorDesc outputTensor( DML::TensorDataType::Int32, std::move( outputSizes ), builder->GetTensorPolicy( ) );

        ConvolutionIntegerOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.FilterTensor = filterTensor.As<DML::TensorDesc>( );
        desc.InputZeroPointTensor = inputZeroPoint ? inputZeroPointTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.FilterZeroPointTensor = filterZeroPoint ? filterZeroPointTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.DimensionCount = spatialDimensionCount;
        desc.Strides = strides.data( );
        desc.Dilations = dilations.data( );
        desc.StartPadding = startPadding.data( );
        desc.EndPadding = endPadding.data( );
        desc.GroupCount = groupCount;

        Internal::NodeOutput* const inputs[ ] = {
            input.Impl( ),
            inputZeroPoint ? inputZeroPoint->Impl( ) : nullptr,
            filter.Impl( ),
            filterZeroPoint ? filterZeroPoint->Impl( ) : nullptr
        };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }



    inline Expression QuantizedLinearConvolution(
        Expression input,
        Expression inputScale,
        std::optional<Expression> inputZeroPoint,
        Expression filter,
        Expression filterScale,
        std::optional<Expression> filterZeroPoint,
        std::optional<Expression> bias,
        Expression outputScale,
        std::optional<Expression> outputZeroPoint,
        DML::TensorDataType outputDataType, // INT8 or UINT8, must match outputZeroPoint dtype if present
        std::span <const UInt32> strides = {},
        std::span<const UInt32> dilations = {},
        std::span<const UInt32> startPadding = {},
        std::span<const UInt32> endPadding = {},
        UInt32 groupCount = 1,
        TensorDimensions outputSizes = {} )
    {
        assert( Internal::HasSameOwner( { input, inputScale, filter, filterScale, outputScale } ) );
        assert( !inputZeroPoint || Internal::HasSameOwner( { input, *inputZeroPoint } ) );
        assert( !filterZeroPoint || Internal::HasSameOwner( { input, *filterZeroPoint } ) );
        assert( !bias || Internal::HasSameOwner( { input, *bias } ) );
        assert( !outputZeroPoint || Internal::HasSameOwner( { input, *outputZeroPoint } ) );

        if ( outputZeroPoint )
        {
            assert( outputZeroPoint->GetOutputDesc( ).DataType == outputDataType );
        }

        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        const auto getOptional = []( std::optional<Expression>& e ) {
            if ( e ) return e->Impl( )->GetOutputDesc( );
            return TensorDesc{};
            };

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc inputScaleTensor = inputScale.Impl( )->GetOutputDesc( );
        TensorDesc inputZeroPointTensor = getOptional( inputZeroPoint );
        TensorDesc filterTensor = filter.Impl( )->GetOutputDesc( );
        TensorDesc filterScaleTensor = filterScale.Impl( )->GetOutputDesc( );
        TensorDesc filterZeroPointTensor = getOptional( filterZeroPoint );
        TensorDesc biasTensor = getOptional( bias );
        TensorDesc outputScaleTensor = outputScale.Impl( )->GetOutputDesc( );
        TensorDesc outputZeroPointTensor = getOptional( outputZeroPoint );

        UInt32 dimensionCount = static_cast< UInt32 >( inputTensor.Sizes.size( ) );

        // todo: suppord 1d convolution?
        assert( dimensionCount == 4 || dimensionCount == 5 );
        const UInt32 spatialDimensionCount = dimensionCount - 2;

        // If the spatial dimension count is 2, we'll just use the first two elements by setting
        // DimensionCount = 2 in the desc
        const UInt32 defaultStridesAndDilations[ 3 ] = { 1, 1, 1 };
        const UInt32 defaultPadding[ 3 ] = { 0, 0, 0 };

        assert( strides.empty( ) || strides.size( ) == spatialDimensionCount );
        assert( dilations.empty( ) || dilations.size( ) == spatialDimensionCount );
        assert( startPadding.empty( ) || startPadding.size( ) == spatialDimensionCount );
        assert( endPadding.empty( ) || endPadding.size( ) == spatialDimensionCount );
        assert( outputSizes.empty( ) || outputSizes.size( ) == inputTensor.Sizes.size( ) );

        strides = strides.empty( ) ? std::span<const UInt32>{ defaultStridesAndDilations } : strides;
        dilations = dilations.empty( ) ? std::span<const UInt32>{ defaultStridesAndDilations } : dilations;
        startPadding = startPadding.empty( ) ? std::span<const UInt32>{ defaultPadding } : startPadding;
        endPadding = endPadding.empty( ) ? std::span<const UInt32>{ defaultPadding } : endPadding;

        if ( outputSizes.empty( ) )
        {
            outputSizes.push_back( inputTensor.Sizes[ 0 ] ); // output[N] = input[N]
            outputSizes.push_back( filterTensor.Sizes[ 0 ] ); // output[C] = filter[N]

            for ( UInt32 dim = 0; dim < spatialDimensionCount; ++dim )
            {
                UInt32 inputSize = inputTensor.Sizes[ dim + 2 ];
                UInt32 paddedSize = inputSize + startPadding[ dim ] + endPadding[ dim ];

                UInt32 windowSize = filterTensor.Sizes[ dim + 2 ];
                UInt32 kernelSize = 1 + ( windowSize - 1 ) * dilations[ dim ];

                assert( kernelSize <= paddedSize );
                assert( strides[ dim ] != 0 );

                outputSizes.push_back( 1 + ( paddedSize - kernelSize ) / strides[ dim ] );
            }
        }


        TensorDesc outputTensor( outputDataType, std::move( outputSizes ), builder->GetTensorPolicy( ) );

        QuantizedLinearConvolutionOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.InputScaleTensor = inputScaleTensor.As<DML::TensorDesc>( );
        desc.InputZeroPointTensor = inputZeroPoint ? inputZeroPointTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.FilterTensor = filterTensor.As<DML::TensorDesc>( );
        desc.FilterScaleTensor = filterScaleTensor.As<DML::TensorDesc>( );
        desc.FilterZeroPointTensor = filterZeroPoint ? filterZeroPointTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.BiasTensor = bias ? biasTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.OutputScaleTensor = outputScaleTensor.As<DML::TensorDesc>( );
        desc.OutputZeroPointTensor = outputZeroPoint ? outputZeroPointTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );

        desc.DimensionCount = spatialDimensionCount;
        desc.Strides = strides.data( );
        desc.Dilations = dilations.data( );
        desc.StartPadding = startPadding.data( );
        desc.EndPadding = endPadding.data( );
        desc.GroupCount = groupCount;

        Internal::NodeOutput* const inputs[ ] = {
            input.Impl( ),
            inputScale.Impl( ),
            inputZeroPoint ? inputZeroPoint->Impl( ) : nullptr,
            filter.Impl( ),
            filterScale.Impl( ),
            filterZeroPoint ? filterZeroPoint->Impl( ) : nullptr,
            bias ? bias->Impl( ) : nullptr,
            outputScale.Impl( ),
            outputZeroPoint ? outputZeroPoint->Impl( ) : nullptr,
        };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }


    // 
    // TODO: ReluGrad
    // 

    // 
    // TODO: AveragePoolingGrad
    // 

    // 
    // TODO: MaxPoolingGrad
    // 

    struct RandomGeneratorOutputs
    {
        Expression values;
        Expression state; // Only valid if outputState = true is supplied to RandomGenerator
    };

    inline RandomGeneratorOutputs RandomGenerator(
        Expression inputState,
        TensorDimensions outputSizes,
        bool outputState = true,
        DML::RandomGeneratorType type = DML::RandomGeneratorType::Philox4x32_10 )
    {
        Internal::GraphBuilder* builder = inputState.Impl( )->GetGraphBuilder( );

        TensorDesc inputStateTensor = inputState.Impl( )->GetOutputDesc( );
        TensorDesc outputTensor( DML::TensorDataType::UInt32, std::move( outputSizes ), builder->GetTensorPolicy( ) );

        RandomGeneratorOperatorDesc desc = {};
        desc.Type = type;
        desc.InputStateTensor = inputStateTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        if ( outputState )
        {
            // Input and output state have the same TensorDesc.
            desc.OutputStateTensor = inputStateTensor.As<DML::TensorDesc>( );
        }

        RandomGeneratorOutputs out;

        Internal::NodeOutput* const inputs[ ] = { inputState.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        out.values = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        if ( outputState )
        {
            TensorDesc outputStateTensor = inputStateTensor;
            out.state = builder->CreateNodeOutput( node, 1, std::move( outputStateTensor ) );
        }

        return out;
    }

    struct NonZeroCoordinatesOutputs
    {
        Expression count;
        Expression coordinates;
    };
    inline NonZeroCoordinatesOutputs NonZeroCoordinates( Expression input )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        const auto& inputTensorSizes = inputTensor.Sizes;
        UInt32 dimensionCount = static_cast< UInt32 >( inputTensorSizes.size( ) );

        TensorDimensions outputCountSizes = { 1 };
        UInt32 totalElements = 1;
        for ( UInt32 i = 0; i < dimensionCount; ++i )
        {
            totalElements *= inputTensorSizes[ i ];
        }
        TensorDesc outputCountTensor( DML::TensorDataType::UInt32, outputCountSizes, builder->GetTensorPolicy( ) );
        TensorDesc outputCoordinatesTensor( DML::TensorDataType::UInt32, { totalElements, dimensionCount }, builder->GetTensorPolicy( ) );

        NonZeroCoordinatesOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputCountTensor = outputCountTensor.As<DML::TensorDesc>( );
        desc.OutputCoordinatesTensor = outputCoordinatesTensor.As<DML::TensorDesc>( );

        NonZeroCoordinatesOutputs output;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        output.count = builder->CreateNodeOutput( node, 0, std::move( outputCountTensor ) );
        output.coordinates = builder->CreateNodeOutput( node, 1, std::move( outputCoordinatesTensor ) );
        return output;
    }

    // If not specified, parameters are defaulted to the following values:
    //   Scales = computed by dividing the input sizes by the output sizes
    //   InputPixelOffsets = 0.5f for each dimension
    //   OutputPixelOffsets = -0.5f for each dimension
    inline Expression ResampleGrad(
        Expression input,
        TensorDimensions outputSizes,
        DML::InterpolationMode mode,
        std::span<const float> scales = {},
        std::span<const float> inputPixelOffsets = {},
        std::span<const float> outputPixelOffsets = {} )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        UInt32 dimensionCount = static_cast< UInt32 >( inputTensor.Sizes.size( ) );
        assert( outputSizes.size( ) == dimensionCount );

        SmallVector<float, 4> defaultScales;
        if ( scales.empty( ) )
        {
            for ( UInt32 i = 0; i < dimensionCount; ++i )
            {
                defaultScales.push_back( static_cast< float >( inputTensor.Sizes[ i ] ) / static_cast< float >( outputSizes[ i ] ) );
            }
            scales = defaultScales;
        }

        SmallVector<float, 4> defaultInputPixelOffsets;
        if ( inputPixelOffsets.empty( ) )
        {
            defaultInputPixelOffsets.assign( dimensionCount, 0.5f );
            inputPixelOffsets = defaultInputPixelOffsets;
        }

        SmallVector<float, 4> defaultOutputPixelOffsets;
        if ( outputPixelOffsets.empty( ) )
        {
            defaultOutputPixelOffsets.assign( dimensionCount, -0.5f );
            outputPixelOffsets = defaultOutputPixelOffsets;
        }

        TensorDesc outputTensor( inputTensor.DataType, std::move( outputSizes ), builder->GetTensorPolicy( ) );

        ResampleGradOperatorDesc desc = {};
        desc.InputGradientTensor = inputTensor.As<DML::TensorDesc>( );
        desc.OutputGradientTensor = outputTensor.As<DML::TensorDesc>( );
        desc.InterpolationMode = mode;
        desc.DimensionCount = static_cast< UINT >( scales.size( ) );
        desc.Scales = scales.data( );
        desc.InputPixelOffsets = inputPixelOffsets.data( );
        desc.OutputPixelOffsets = outputPixelOffsets.data( );

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

    inline Expression SliceGrad(
        Expression inputGradient,
        TensorDimensions outputGradientSizes,
        std::span<const UInt32> inputWindowOffsets,
        std::span<const UInt32> inputWindowSizes,
        std::span<const int32_t> inputWindowStrides )
    {
        Internal::GraphBuilder* builder = inputGradient.Impl( )->GetGraphBuilder( );

        TensorDesc inputGradientTensor = inputGradient.Impl( )->GetOutputDesc( );

        assert( inputWindowOffsets.size( ) == inputGradientTensor.Sizes.size( ) );
        assert( inputWindowOffsets.size( ) == outputGradientSizes.size( ) );
        assert( inputWindowOffsets.size( ) == inputWindowStrides.size( ) );
        assert( inputWindowOffsets.size( ) == inputWindowSizes.size( ) );

        TensorDesc outputGradientTensor( inputGradientTensor.DataType, std::move( outputGradientSizes ), builder->GetTensorPolicy( ) );

        SliceGradOperatorDesc sliceGradDesc = {};
        sliceGradDesc.InputGradientTensor = inputGradientTensor.As<DML::TensorDesc>( );
        sliceGradDesc.OutputGradientTensor = outputGradientTensor.As<DML::TensorDesc>( );
        sliceGradDesc.DimensionCount = static_cast< UInt32 >( inputWindowOffsets.size( ) );
        sliceGradDesc.InputWindowOffsets = inputWindowOffsets.data( );
        sliceGradDesc.InputWindowSizes = inputWindowSizes.data( );
        sliceGradDesc.InputWindowStrides = inputWindowStrides.data( );

        Internal::NodeOutput* const inputs[ ] = { inputGradient.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( sliceGradDesc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputGradientTensor ) );

        return output;
    }

    // 
    // TODO: AdamOptimizer
    // 

    // 
    // TODO: Argmin
    // 

    // 
    // TODO: Argmax
    // 

#if DML_TARGET_VERSION >= 0x4000

    inline Expression RoiAlign(
        Expression input,
        Expression roi,
        Expression batchIndices,
        DML::ReduceFunction reductionFunction,
        DML::InterpolationMode interpolationMode,
        float spatialScaleX,
        float spatialScaleY,
        float inputPixelOffset,
        float outputPixelOffset,
        float outOfBoundsInputValue,
        UInt32 minimumSamplesPerOutput,
        UInt32 maximumSamplesPerOutput,
        bool alignRegionsToCorners,
        UInt32 outputHeight,
        UInt32 outputWidth )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc roiTensor = roi.Impl( )->GetOutputDesc( );
        TensorDesc batchIndicesTensor = batchIndices.Impl( )->GetOutputDesc( );

        UInt32 channelCount = inputTensor.Sizes[ 1 ];
        UInt32 roiCount = roiTensor.Sizes.size( ) < 2 ? 1u : roiTensor.Sizes[ roiTensor.Sizes.size( ) - 2 ];

        TensorDimensions outputSizes( {
            roiCount,
            channelCount,
            outputHeight,
            outputWidth,
            } );

        TensorDesc outputTensor( inputTensor.DataType, outputSizes, builder->GetTensorPolicy( ) );

        ROIAlign1OperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.ROITensor = roiTensor.As<DML::TensorDesc>( );
        desc.BatchIndicesTensor = batchIndicesTensor.As<DML::TensorDesc>( );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.ReductionFunction = reductionFunction;
        desc.InterpolationMode = interpolationMode;
        desc.SpatialScaleX = spatialScaleX;
        desc.SpatialScaleY = spatialScaleY;
        desc.InputPixelOffset = inputPixelOffset;
        desc.OutputPixelOffset = outputPixelOffset;
        desc.OutOfBoundsInputValue = outOfBoundsInputValue;
        desc.MinimumSamplesPerOutput = minimumSamplesPerOutput;
        desc.MaximumSamplesPerOutput = maximumSamplesPerOutput;
        desc.AlignRegionsToCorners = alignRegionsToCorners;

        Internal::NodeOutput* const inputs[ ] = { input.Impl( ), roi.Impl( ), batchIndices.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }

#endif // DML_TARGET_VERSION >= 0x4000

#if DML_TARGET_VERSION >= 0x4100
    struct RoiAlignGradOutputs
    {
        Expression outputGradient;
        Expression outputROIGradient;
    };

    inline RoiAlignGradOutputs RoiAlignGrad(
        std::optional<Expression> input,
        Expression inputGradient,
        Expression roi,
        Expression batchIndices,
        DML::ReduceFunction reductionFunction,
        DML::InterpolationMode interpolationMode,
        float spatialScaleX,
        float spatialScaleY,
        float inputPixelOffset,
        float outputPixelOffset,
        UInt32 minimumSamplesPerOutput,
        UInt32 maximumSamplesPerOutput,
        bool alignRegionsToCorners,
        UInt32 batchSize,
        UInt32 imageHeight,
        UInt32 imageWidth,
        bool computeOutputGradient,
        bool computeOutputROIGradient )
    {
        Internal::GraphBuilder* builder = inputGradient.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.has_value( ) ? input->Impl( )->GetOutputDesc( ) : TensorDesc( );
        TensorDesc inputGradientTensor = inputGradient.Impl( )->GetOutputDesc( );
        TensorDesc roiTensor = roi.Impl( )->GetOutputDesc( );
        TensorDesc batchIndicesTensor = batchIndices.Impl( )->GetOutputDesc( );

        assert( computeOutputGradient || computeOutputROIGradient );
        assert( inputGradientTensor.Sizes.size( ) > 1 );

        TensorDesc outputGradientTensor;
        if ( computeOutputGradient )
        {
            TensorDimensions outputGradientSizes( {
                batchSize,
                inputGradientTensor.Sizes[ 1 ],
                imageHeight,
                imageWidth,
                } );

            outputGradientTensor = TensorDesc( inputGradientTensor.DataType, outputGradientSizes, builder->GetTensorPolicy( ) );
        }

        TensorDesc outputROIGradientTensor = computeOutputROIGradient ? TensorDesc( roiTensor.DataType, roiTensor.Sizes, builder->GetTensorPolicy( ) ) : TensorDesc( );
        assert( !computeOutputROIGradient || outputROIGradientTensor.Sizes == roiTensor.Sizes );

        ROIAlignGradOperatorDesc desc = {};
        desc.InputTensor = input ? inputTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.InputGradientTensor = inputGradientTensor.As<DML::TensorDesc>( );
        desc.ROITensor = roiTensor.As<DML::TensorDesc>( );
        desc.BatchIndicesTensor = batchIndicesTensor.As<DML::TensorDesc>( );
        desc.OutputGradientTensor = computeOutputGradient ? outputGradientTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.OutputROIGradientTensor = computeOutputROIGradient ? outputROIGradientTensor.As<DML::TensorDesc>( ) : nullptr;
        desc.ReductionFunction = reductionFunction;
        desc.InterpolationMode = interpolationMode;
        desc.SpatialScaleX = spatialScaleX;
        desc.SpatialScaleY = spatialScaleY;
        desc.InputPixelOffset = inputPixelOffset;
        desc.OutputPixelOffset = outputPixelOffset;
        desc.MinimumSamplesPerOutput = minimumSamplesPerOutput;
        desc.MaximumSamplesPerOutput = maximumSamplesPerOutput;
        desc.AlignRegionsToCorners = alignRegionsToCorners;

        Internal::NodeOutput* const inputs[ ] = { input ? input->Impl( ) : nullptr, inputGradient.Impl( ), roi.Impl( ), batchIndices.Impl( ) };
        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );

        RoiAlignGradOutputs outputs{};

        if ( computeOutputGradient )
        {
            outputs.outputGradient = builder->CreateNodeOutput( node, 0, std::move( outputGradientTensor ) );
        }

        if ( computeOutputROIGradient )
        {
            outputs.outputROIGradient = builder->CreateNodeOutput( node, 1, std::move( outputROIGradientTensor ) );
        }

        return outputs;
    }
#endif

#if DML_TARGET_VERSION >= 0x5000

    inline Expression Negate( Expression input )
    {
        return Internal::UnaryImpl<ElementWiseNegateOperatorDesc>( input );
    }

#endif // DML_TARGET_VERSION >= 0x5000

#if DML_TARGET_VERSION >= 0x6300
    inline Expression Dequantize(
        Expression input,
        std::span<const Expression> quantizationParameters,
        DML::QuantizationType quantizationType )
    {
#ifdef _DEBUG
        for ( const auto& quantizationParameter : quantizationParameters )
        {
            assert( Internal::HasSameOwner( { quantizationParameter, input } ) );
        }
#endif
        assert( quantizationType != DML::QuantizationType::None );
        assert( !quantizationParameters.empty( ) );

        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );

        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );

        std::vector<Internal::NodeOutput*> inputs;
        inputs.reserve( quantizationParameters.size( ) + 1 );
        inputs.push_back( input.Impl( ) );

        std::vector<TensorDesc> quantizationParametersTensors;
        quantizationParametersTensors.reserve( quantizationParameters.size( ) );

        std::vector<DML::TensorDesc> quantizationParametersDescs;
        quantizationParametersDescs.reserve( quantizationParameters.size( ) );

        // The output data type is always the same as the data type of the scale
        assert( quantizationType == DML::QuantizationType::Scale || quantizationType == DML::QuantizationType::ScaleZeroPoint );
        DML::TensorDataType outputDataType = quantizationParameters[ 0 ].GetOutputDesc( ).DataType;

        for ( const auto& quantizationParameter : quantizationParameters )
        {
            quantizationParametersTensors.push_back( quantizationParameter.Impl( )->GetOutputDesc( ) );
            TensorDesc& quantizationParameterDesc = quantizationParametersTensors.back( );
            quantizationParametersDescs.push_back( *quantizationParameterDesc.As<DML::TensorDesc>( ) );
            inputs.push_back( quantizationParameter.Impl( ) );
        }

        TensorDesc outputTensor( outputDataType, inputTensor.Sizes, builder->GetTensorPolicy( ) );

        DequantizeOperatorDesc desc = {};
        desc.InputTensor = inputTensor.As<DML::TensorDesc>( );
        desc.QuantizationTensors = quantizationParametersDescs.data( );
        desc.QuantizationTensorCount = static_cast< UInt32 >( quantizationParametersDescs.size( ) );
        desc.OutputTensor = outputTensor.As<DML::TensorDesc>( );
        desc.QuantizationType = quantizationType;

        Internal::NodeID node = builder->CreateOperatorNode( desc, inputs );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( outputTensor ) );

        return output;
    }
#endif

    // Reinterprets the memory of a tensor with a different type and dimensions (analogously to using
    // reinterpret_cast to access raw bits). Note that this is different to the DML Cast operator, which performs
    // a type cast on the contents of a tensor (analogously to static_cast). The total tensor size of the output
    // (which depends on the supplied type/sizes/strides) must match the input.
    inline Expression Reinterpret(
        Expression input,
        DML::TensorDataType newType,
        TensorDimensions newSizes,
        std::optional<TensorStrides> newStrides )
    {
        Internal::GraphBuilder* builder = input.Impl( )->GetGraphBuilder( );
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );
        TensorDesc newTensor(
            newType,
            inputTensor.Flags,
            newSizes,
            newStrides,
            inputTensor.TotalTensorSizeInBytes,
            inputTensor.GuaranteedBaseOffsetAlignment );

        Internal::NodeID node = builder->CreateReinterpretNode( input.Impl( ) );
        Internal::NodeOutput* output = builder->CreateNodeOutput( node, 0, std::move( newTensor ) );

        return output;
    }

    // Same as Reinterpret above, but only adjusts tensor dimensions without affecting type.
    inline Expression Reinterpret(
        Expression input,
        TensorDimensions newSizes,
        std::optional<TensorStrides> newStrides )
    {
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );

        return Reinterpret( input, inputTensor.DataType, std::move( newSizes ), std::move( newStrides ) );
    }

    // Same as Reinterpret above, but only adjusts tensor type without affecting sizes or strides.
    inline Expression Reinterpret( Expression input, DML::TensorDataType newType )
    {
        TensorDesc inputTensor = input.Impl( )->GetOutputDesc( );

        return Reinterpret( input, newType, inputTensor.Sizes, inputTensor.Strides );
    }

    // Operator overloads for convenience, which merely map to one of the functions above
    inline Expression operator+( Expression a, Expression b ) 
    { 
        return Add( a, b ); 
    }
    inline Expression operator-( Expression a, Expression b ) 
    { 
        return Subtract( a, b ); 
    }
    inline Expression operator*( Expression a, Expression b ) 
    { 
        return Multiply( a, b ); 
    }
    inline Expression operator/( Expression a, Expression b ) 
    { 
        return Divide( a, b ); 
    }
    inline Expression operator%( Expression a, Expression b ) 
    { 
        return ModulusTruncate( a, b ); 
    }
    inline Expression operator&( Expression a, Expression b ) 
    { 
        return BitAnd( a, b ); 
    }
    inline Expression operator|( Expression a, Expression b ) 
    { 
        return BitOr( a, b ); 
    }
    inline Expression operator^( Expression a, Expression b ) 
    { 
        return BitXor( a, b ); 
    }
    inline Expression operator<<( Expression a, Expression b ) 
    { 
        return BitShiftLeft( a, b ); 
    }
    inline Expression operator>>( Expression a, Expression b ) 
    { 
        return BitShiftRight( a, b ); 
    }
    inline Expression& operator+=( Expression& a, Expression b ) 
    { 
        a = a + b; 
        return a; 
    }
    inline Expression& operator-=( Expression& a, Expression b ) 
    { 
        a = a - b; 
        return a; 
    }
    inline Expression& operator*=( Expression& a, Expression b ) 
    { 
        a = a * b; 
        return a; 
    }
    inline Expression& operator/=( Expression& a, Expression b ) 
    { 
        a = a / b; 
        return a; 
    }
    inline Expression& operator%=( Expression& a, Expression b ) 
    { 
        a = a % b; 
        return a; 
    }
    inline Expression& operator&=( Expression& a, Expression b ) 
    { 
        a = a & b; 
        return a; 
    }
    inline Expression& operator|=( Expression& a, Expression b ) 
    { 
        a = a | b; 
        return a; 
    }
    inline Expression& operator^=( Expression& a, Expression b ) 
    { 
        a = a ^ b; 
        return a; 
    }
    inline Expression& operator<<=( Expression& a, Expression b ) 
    { 
        a = a << b; 
        return a; 
    }
    inline Expression& operator>>=( Expression& a, Expression b ) 
    { 
        a = a >> b; 
        return a; 
    }

    // Operations involving scalars can be reduced to elementwise identity
    inline Expression operator+( Expression a, float b ) 
    { 
        return Identity( a, DML::ScaleBias{ 1.0f, b } ); 
    }
    inline Expression operator-( Expression a, float b ) 
    { 
        return Identity( a, DML::ScaleBias{ 1.0f, -b } ); 
    }
    inline Expression operator*( Expression a, float b ) 
    { 
        return Identity( a, DML::ScaleBias{ b, 0.0f } ); 
    }
    inline Expression operator/( Expression a, float b ) 
    { 
        return Identity( a, DML::ScaleBias{ 1.0f / b, 0.0f } ); 
    }
    inline Expression operator+( float a, Expression b ) 
    { 
        return Identity( b, DML::ScaleBias{ 1.0f, a } ); 
    }
    inline Expression operator-( float a, Expression b ) 
    { 
        return Identity( b, DML::ScaleBias{ -1.0f, a } ); 
    }
    inline Expression operator*( float a, Expression b ) 
    { 
        return Identity( b, DML::ScaleBias{ a, 0.0f } ); 
    }
    inline Expression operator/( float a, Expression b ) 
    { 
        return Reciprocal( b, DML::ScaleBias{ a, 0.0f } ); 
    }
    inline Expression& operator+=( Expression& a, float b ) 
    { 
        a = a + b; 
        return a; 
    }
    inline Expression& operator-=( Expression& a, float b ) 
    { 
        a = a - b; 
        return a; 
    }
    inline Expression& operator*=( Expression& a, float b ) 
    { 
        a = a * b; 
        return a; 
    }
    inline Expression& operator/=( Expression& a, float b ) 
    { 
        a = a / b; 
        return a; 
    }

    // Unary
    inline Expression operator~( Expression input ) 
    { 
        return BitNot( input ); 
    }
    inline Expression operator+( Expression input ) 
    { 
        return Identity( input ); 
    }

#if DML_TARGET_VERSION >= 0x5000

    inline Expression operator-( Expression input ) 
    { 
        return Negate( input ); 
    }

#else

    inline Expression operator-( Expression input ) 
    { 
        return Identity( input, DML::ScaleBias{ -1.0f, 0.0f } ); 
    }

#endif // DML_TARGET_VERSION >= 0x5000

    // Logical
    inline Expression operator!( Expression a ) 
    { 
        return LogicalNot( a ); 
    }
    inline Expression operator&&( Expression a, Expression b ) 
    { 
        return LogicalAnd( a, b ); 
    }
    inline Expression operator||( Expression a, Expression b ) 
    { 
        return LogicalOr( a, b ); 
    }
    inline Expression operator>( Expression a, Expression b ) 
    { 
        return GreaterThan( a, b ); 
    }
    inline Expression operator<( Expression a, Expression b ) 
    { 
        return LessThan( a, b ); 
    }
    inline Expression operator==( Expression a, Expression b ) 
    { 
        return Equals( a, b ); 
    }
    inline Expression operator!=( Expression a, Expression b ) 
    { 
        return !( a == b ); 
    }
    inline Expression operator>=( Expression a, Expression b ) 
    { 
        return GreaterThanOrEqual( a, b ); 
    }
    inline Expression operator<=( Expression a, Expression b ) 
    { 
        return LessThanOrEqual( a, b ); 
    }

    // GraphBuilder implementation details
    namespace Internal
    {
        template<typename T>
        inline NodeID GraphBuilder::CreateOperatorNode( const T& desc, std::span<NodeOutput* const> inputs )
        {
            DML::OperatorDesc opDesc = { T::OperatorType, &desc };
            auto op = m_device.CreateOperator( &opDesc );

            OperatorNode node = {};
            node.op = std::move( op );
            node.inputs.assign( inputs.begin( ), inputs.end( ) );
            if ( !m_name.empty( ) )
            {
                node.name = m_name;
            }

            UInt32 index = static_cast< UInt32 >( m_operatorNodes.size( ) );
            m_operatorNodes.push_back( std::move( node ) );

            return { NodeType::Operator, index };
        }

        inline NodeID GraphBuilder::CreateInputNode( UInt32 inputIndex )
        {
            UInt32 index = static_cast< UInt32 >( m_inputNodes.size( ) );
            m_inputNodes.push_back( InputNode{ inputIndex } );
            return { NodeType::Input, index };
        }

        inline NodeID GraphBuilder::CreateReinterpretNode( NodeOutput* input )
        {
            UInt32 index = static_cast< UInt32 >( m_reinterpretNodes.size( ) );
            m_reinterpretNodes.push_back( ReinterpretNode{ input } );
            return { NodeType::Reinterpret, index };
        }

#if DML_TARGET_VERSION >= 0x6200
        inline NodeID GraphBuilder::CreateConstantNode( std::span<const Byte> data )
        {
            UInt32 index = static_cast< UInt32 >( m_constantNodes.size( ) );
            m_constantNodes.push_back( ConstantNode{ data } );

            if ( !m_name.empty( ) )
            {
                m_constantNodes.back( ).name = m_name;
            }

            return { NodeType::Constant, index };
        }
#endif // DML_TARGET_VERSION >= 0x6200

        inline NodeOutput* GraphBuilder::CreateNodeOutput( NodeID node, UInt32 outputIndex, const TensorDesc& tensorDesc )
        {
            // Construct the object in the deque, which doesn't invalidate references to elements as it grows
            m_nodeOutputs.emplace_back( this, node, outputIndex, tensorDesc );

            return &m_nodeOutputs.back( );
        }

        inline GraphDesc GraphBuilder::GetGraphDesc( std::span<const Expression> outputs ) const
        {
            GraphDesc desc = {};
            desc.inputCount = static_cast< UInt32 >( m_inputNodes.size( ) );
            desc.outputCount = static_cast< UInt32 >( outputs.size( ) );

            // GraphDesc merges nodes into a single list, with all operator nodes appearing before constant nodes.
            constexpr UInt32 baseOperatorNodeIndex = 0;
            const UInt32 baseConstantNodeIndex = static_cast< UInt32 >( m_operatorNodes.size( ) );

            for ( const OperatorNode& node : m_operatorNodes )
            {
                UInt32 nodeIndex = static_cast< UInt32 >( desc.operatorNodes.size( ) );

                desc.operatorNodes.push_back( DML::OperatorGraphNodeDesc{ node.op.GetInterfacePointer<IDMLOperator>( ), ( !node.name.empty( ) ? node.name.c_str( ) : nullptr ) } );

                // Walk through each of this node's inputs and add it as an edge
                const UInt32 inputCount = static_cast< UInt32 >( node.inputs.size( ) );
                for ( UInt32 inputIndex = 0; inputIndex < inputCount; ++inputIndex )
                {
                    NodeOutput* input = node.inputs[ inputIndex ];
                    if ( input == nullptr )
                    {
                        continue;
                    }
                    NodeID inputNode = input->GetNode( );

                    // Reinterpret nodes aren't "real" nodes, they're just used to modify TensorDescs across
                    // edges. So we follow this node backwards until it hits a real node.
                    while ( inputNode.type == NodeType::Reinterpret )
                    {
                        input = m_reinterpretNodes[ inputNode.index ].input;
                        inputNode = input->GetNode( );
                    }

                    if ( inputNode.type == NodeType::Input )
                    {
                        DML::InputGraphEdgeDesc inputEdge = {};
                        inputEdge.GraphInputIndex = m_inputNodes[ inputNode.index ].inputIndex;
                        inputEdge.ToNodeIndex = nodeIndex;
                        inputEdge.ToNodeInputIndex = inputIndex;

                        desc.inputEdges.push_back( inputEdge );
                    }
                    else if ( inputNode.type == NodeType::Operator )
                    {
                        DML::IntermediateGraphEdgeDesc intermediateEdge = {};
                        intermediateEdge.FromNodeIndex = baseOperatorNodeIndex + inputNode.index;
                        intermediateEdge.FromNodeOutputIndex = input->GetOutputIndex( );
                        intermediateEdge.ToNodeIndex = nodeIndex;
                        intermediateEdge.ToNodeInputIndex = inputIndex;

                        desc.intermediateEdges.push_back( intermediateEdge );
                    }
                    else if ( inputNode.type == NodeType::Constant )
                    {
                        DML::IntermediateGraphEdgeDesc intermediateEdge = {};
                        intermediateEdge.FromNodeIndex = baseConstantNodeIndex + inputNode.index;
                        intermediateEdge.FromNodeOutputIndex = input->GetOutputIndex( );
                        intermediateEdge.ToNodeIndex = nodeIndex;
                        intermediateEdge.ToNodeInputIndex = inputIndex;

                        desc.intermediateEdges.push_back( intermediateEdge );
                    }
                    else
                    {
                        assert( false ); // Invalid node type
                        HCC_COM_CHECK_HRESULT( E_UNEXPECTED );
                    }
                }
            }

#if DML_TARGET_VERSION >= 0x6200
            for ( const ConstantNode& node : m_constantNodes )
            {
                desc.constantNodes.push_back( DML::ConstantDataGraphNodeDesc{ node.data.data( ), node.data.size( ), ( !node.name.empty( ) ? node.name.c_str( ) : nullptr ) } );
            }
#endif // DML_TARGET_VERSION >= 0x6200

            // Add output edges
            for ( UInt32 outputIndex = 0; outputIndex < desc.outputCount; ++outputIndex )
            {
                NodeOutput* output = outputs[ outputIndex ].Impl( );
                if ( output == nullptr )
                {
                    continue;
                }
                NodeID outputNode = output->GetNode( );

                // Reinterpret nodes are meaningless on outputs (they're no-ops), so just follow them back until we
                // get to a real operator node.
                while ( outputNode.type == NodeType::Reinterpret )
                {
                    output = m_reinterpretNodes[ outputNode.index ].input;
                    outputNode = output->GetNode( );
                }

                if ( outputNode.type == NodeType::Input )
                {
                    // It's not valid to connect an output of the graph directly to an input without an intervening
                    // node. If this behavior is desired, it should instead be accomplished with a copy e.g. using
                    // the elementwise identity operator.
                    HCC_COM_CHECK_HRESULT( E_INVALIDARG );
                }

                assert( outputNode.type == NodeType::Operator );

                DML::OutputGraphEdgeDesc outputEdge = {};
                outputEdge.FromNodeIndex = output->GetNode( ).index;
                outputEdge.FromNodeOutputIndex = output->GetOutputIndex( );
                outputEdge.GraphOutputIndex = outputIndex;

                desc.outputEdges.push_back( outputEdge );
            }

            // Sanity
            assert( desc.operatorNodes.size( ) == m_operatorNodes.size( ) );
#if DML_TARGET_VERSION >= 0x6200
            assert( desc.constantNodes.size( ) == m_constantNodes.size( ) );
#endif // DML_TARGET_VERSION >= 0x6200
            assert( desc.outputEdges.size( ) == desc.outputCount );
            assert( desc.outputCount == outputs.size( ) );
            assert( baseOperatorNodeIndex == desc.BaseOperatorNodeIndexInMergedNodes( ) );
            assert( baseConstantNodeIndex == desc.BaseConstantNodeIndexInMergedNodes( ) );

            return desc;
        }
    } // namespace Internal
}

#endif

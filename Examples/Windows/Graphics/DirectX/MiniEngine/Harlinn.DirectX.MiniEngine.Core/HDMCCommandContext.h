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
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard 
//

#pragma once

#include "HDMCCommandListManager.h"
#include "HDMCColor.h"
#include "HDMCPipelineState.h"
#include "HDMCRootSignature.h"
#include "HDMCGpuBuffer.h"
#include "HDMCTexture.h"
#include "HDMCPixelBuffer.h"
#include "HDMCDynamicDescriptorHeap.h"
#include "HDMCLinearAllocator.h"
#include "HDMCCommandSignature.h"
#include "HDMCGraphicsCore.h"
#include "HDMCUtility.h"
#include "Math/HDMCCommon.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class ColorBuffer;
    class DepthBuffer;
    class Texture;
    class GraphicsContext;
    class ComputeContext;
    class UploadBuffer;
    class ReadbackBuffer;

    struct DWParam
    {
        DWParam( FLOAT f ) : Float( f ) {}
        DWParam( UINT u ) : Uint( u ) {}
        DWParam( INT i ) : Int( i ) {}

        void operator= ( FLOAT f ) { Float = f; }
        void operator= ( UINT u ) { Uint = u; }
        void operator= ( INT i ) { Int = i; }

        union
        {
            FLOAT Float;
            UINT Uint;
            INT Int;
        };
    };

#define VALID_COMPUTE_QUEUE_RESOURCE_STATES \
    ( D3D12_RESOURCE_STATE_UNORDERED_ACCESS \
    | D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE \
    | D3D12_RESOURCE_STATE_COPY_DEST \
    | D3D12_RESOURCE_STATE_COPY_SOURCE )

    class ContextManager : public std::enable_shared_from_this<ContextManager>
    {
    private:
        std::vector<std::unique_ptr<CommandContext> > sm_ContextPool[ 4 ];
        std::queue<CommandContext*> sm_AvailableContexts[ 4 ];
        std::mutex sm_ContextAllocationMutex;
    public:
        ContextManager( ) 
        {}

        HDMC_EXPORT CommandContext* AllocateContext( D3D12_COMMAND_LIST_TYPE Type );
        HDMC_EXPORT void FreeContext( CommandContext* );
        HDMC_EXPORT void DestroyAllContexts( );
    };

    

    class CommandContext
    {
        friend ContextManager;
    protected:
        CommandListManager* m_OwningManager;
        D3D12GraphicsCommandList m_CommandList;
        D3D12CommandAllocator m_CurrentAllocator;

        D3D12RootSignature m_CurGraphicsRootSignature;
        D3D12RootSignature m_CurComputeRootSignature;
        D3D12PipelineState m_CurPipelineState;

        // HEAP_TYPE_CBV_SRV_UAV
        DynamicDescriptorHeap m_DynamicViewDescriptorHeap;

        // HEAP_TYPE_SAMPLER
        DynamicDescriptorHeap m_DynamicSamplerDescriptorHeap;

        D3D12_RESOURCE_BARRIER m_ResourceBarrierBuffer[ 16 ];
        UINT m_NumBarriersToFlush;

        D3D12DescriptorHeap m_CurrentDescriptorHeaps[ D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES ];

        LinearAllocator m_CpuLinearAllocator;
        LinearAllocator m_GpuLinearAllocator;

        std::wstring m_ID;

        D3D12_COMMAND_LIST_TYPE m_Type;

    private:

        HDMC_EXPORT CommandContext( D3D12_COMMAND_LIST_TYPE Type );

        CommandContext( const CommandContext& ) = delete;
        CommandContext( CommandContext&& ) = delete;
        CommandContext& operator=( const CommandContext& ) = delete;
        CommandContext& operator=( CommandContext&& ) = delete;

        HDMC_EXPORT void Reset( void );

    public:

        HDMC_EXPORT ~CommandContext( void );

        HDMC_EXPORT static void DestroyAllContexts( void );

        HDMC_EXPORT static CommandContext& Begin( const std::wstring ID = L"" );

        // Flush existing commands to the GPU but keep the context alive
        HDMC_EXPORT uint64_t Flush( bool WaitForCompletion = false );

        // Flush existing commands and release the current context
        HDMC_EXPORT uint64_t Finish( bool WaitForCompletion = false );

        // Prepare to render by reserving a command list and command allocator
        HDMC_EXPORT void Initialize( void );

        GraphicsContext& GetGraphicsContext( )
        {
            ASSERT( m_Type != D3D12_COMMAND_LIST_TYPE_COMPUTE, "Cannot convert async compute context to graphics" );
            return reinterpret_cast< GraphicsContext& >( *this );
        }

        ComputeContext& GetComputeContext( )
        {
            return reinterpret_cast< ComputeContext& >( *this );
        }

        const D3D12GraphicsCommandList& GetCommandList( )
        {
            return m_CommandList;
        }

        void CopyBuffer( GpuResource& Dest, GpuResource& Src )
        {
            TransitionResource( Dest, D3D12_RESOURCE_STATE_COPY_DEST );
            TransitionResource( Src, D3D12_RESOURCE_STATE_COPY_SOURCE );
            FlushResourceBarriers( );
            m_CommandList.CopyResource( Dest.GetResource( ), Src.GetResource( ) );
        }
        void CopyBufferRegion( GpuResource& Dest, size_t DestOffset, GpuResource& Src, size_t SrcOffset, size_t NumBytes )
        {
            TransitionResource( Dest, D3D12_RESOURCE_STATE_COPY_DEST );
            //TransitionResource(Src, D3D12_RESOURCE_STATE_COPY_SOURCE);
            FlushResourceBarriers( );
            m_CommandList.CopyBufferRegion( Dest.GetResource( ), DestOffset, Src.GetResource( ), SrcOffset, NumBytes );
        }
        HDMC_EXPORT void CopySubresource( GpuResource& Dest, UINT DestSubIndex, GpuResource& Src, UINT SrcSubIndex );
        void CopyCounter( GpuResource& Dest, size_t DestOffset, StructuredBuffer& Src )
        {
            TransitionResource( Dest, D3D12_RESOURCE_STATE_COPY_DEST );
            TransitionResource( Src.GetCounterBuffer( ), D3D12_RESOURCE_STATE_COPY_SOURCE );
            FlushResourceBarriers( );
            m_CommandList.CopyBufferRegion( Dest.GetResource( ), DestOffset, Src.GetCounterBuffer( ).GetResource( ), 0, 4 );
        }
        void CopyTextureRegion( GpuResource& Dest, UINT x, UINT y, UINT z, GpuResource& Source, RECT& rect )
        {
            TransitionResource( Dest, D3D12_RESOURCE_STATE_COPY_DEST );
            TransitionResource( Source, D3D12_RESOURCE_STATE_COPY_SOURCE );
            FlushResourceBarriers( );

            D3D12_TEXTURE_COPY_LOCATION destLoc = CD3DX12_TEXTURE_COPY_LOCATION( Dest.GetResource( ).GetInterfacePointer<ID3D12Resource>( ), 0 );
            D3D12_TEXTURE_COPY_LOCATION srcLoc = CD3DX12_TEXTURE_COPY_LOCATION( Source.GetResource( ).GetInterfacePointer<ID3D12Resource>( ), 0 );

            D3D12_BOX box = {};
            box.back = 1;
            box.left = rect.left;
            box.right = rect.right;
            box.top = rect.top;
            box.bottom = rect.bottom;

            m_CommandList.CopyTextureRegion( &destLoc, x, y, z, &srcLoc, &box );
        }
        void ResetCounter( StructuredBuffer& Buf, uint32_t Value = 0 )
        {
            FillBuffer( Buf.GetCounterBuffer( ), 0, Value, sizeof( uint32_t ) );
            TransitionResource( Buf.GetCounterBuffer( ), D3D12_RESOURCE_STATE_UNORDERED_ACCESS );
        }

        // Creates a readback buffer of sufficient size, copies the texture into it,
        // and returns row pitch in bytes.
        HDMC_EXPORT uint32_t ReadbackTexture( ReadbackBuffer& DstBuffer, PixelBuffer& SrcBuffer );

        DynAlloc ReserveUploadMemory( size_t SizeInBytes )
        {
            return m_CpuLinearAllocator.Allocate( SizeInBytes );
        }

        HDMC_EXPORT static void InitializeTexture( GpuResource& Dest, UINT NumSubresources, const D3D12_SUBRESOURCE_DATA* SubData );
        HDMC_EXPORT static void InitializeBuffer( GpuBuffer& Dest, const void* Data, size_t NumBytes, size_t DestOffset = 0 );
        HDMC_EXPORT static void InitializeBuffer( GpuBuffer& Dest, const UploadBuffer& Src, size_t SrcOffset, size_t NumBytes = -1, size_t DestOffset = 0 );
        HDMC_EXPORT static void InitializeTextureArraySlice( GpuResource& Dest, UINT SliceIndex, GpuResource& Src );

        HDMC_EXPORT void WriteBuffer( GpuResource& Dest, size_t DestOffset, const void* Data, size_t NumBytes );
        HDMC_EXPORT void FillBuffer( GpuResource& Dest, size_t DestOffset, DWParam Value, size_t NumBytes );

        HDMC_EXPORT void TransitionResource( GpuResource& Resource, D3D12_RESOURCE_STATES NewState, bool FlushImmediate = false );
        HDMC_EXPORT void BeginResourceTransition( GpuResource& Resource, D3D12_RESOURCE_STATES NewState, bool FlushImmediate = false );
        HDMC_EXPORT void InsertUAVBarrier( GpuResource& Resource, bool FlushImmediate = false );
        HDMC_EXPORT void InsertAliasBarrier( GpuResource& Before, GpuResource& After, bool FlushImmediate = false );
        inline void FlushResourceBarriers( )
        {
            if ( m_NumBarriersToFlush > 0 )
            {
                m_CommandList.ResourceBarrier( m_NumBarriersToFlush, m_ResourceBarrierBuffer );
                m_NumBarriersToFlush = 0;
            }
        }

        void InsertTimeStamp( const D3D12QueryHeap& pQueryHeap, uint32_t QueryIdx )
        {
            m_CommandList.EndQuery( pQueryHeap, D3D12_QUERY_TYPE_TIMESTAMP, QueryIdx );
        }
        void ResolveTimeStamps( const D3D12Resource& pReadbackHeap, const D3D12QueryHeap& pQueryHeap, uint32_t NumQueries )
        {
            m_CommandList.ResolveQueryData( pQueryHeap, D3D12_QUERY_TYPE_TIMESTAMP, 0, NumQueries, pReadbackHeap, 0 );
        }
        HDMC_EXPORT void PIXBeginEvent( const wchar_t* label );
        HDMC_EXPORT void PIXEndEvent( void );
        HDMC_EXPORT void PIXSetMarker( const wchar_t* label );

        void SetDescriptorHeap( D3D12_DESCRIPTOR_HEAP_TYPE Type, const D3D12DescriptorHeap& HeapPtr )
        {
            if ( m_CurrentDescriptorHeaps[ Type ] != HeapPtr )
            {
                m_CurrentDescriptorHeaps[ Type ] = HeapPtr;
                BindDescriptorHeaps( );
            }
        }
        void SetDescriptorHeaps( UINT HeapCount, D3D12_DESCRIPTOR_HEAP_TYPE Type[ ], D3D12DescriptorHeap HeapPtrs[ ] )
        {
            bool AnyChanged = false;

            for ( UINT i = 0; i < HeapCount; ++i )
            {
                if ( m_CurrentDescriptorHeaps[ Type[ i ] ] != HeapPtrs[ i ] )
                {
                    m_CurrentDescriptorHeaps[ Type[ i ] ] = HeapPtrs[ i ];
                    AnyChanged = true;
                }
            }

            if ( AnyChanged )
            {
                BindDescriptorHeaps( );
            }
        }
        void SetPipelineState( const PSO& PSO )
        {
            const auto& PipelineState = PSO.GetPipelineStateObject( );
            if ( PipelineState == m_CurPipelineState )
                return;

            m_CommandList.SetPipelineState( PipelineState );
            m_CurPipelineState = PipelineState;
        }

        void SetPredication( const D3D12Resource& Buffer, UINT64 BufferOffset, D3D12_PREDICATION_OP Op )
        {
            m_CommandList.SetPredication( Buffer, BufferOffset, Op );
        }

    protected:

        HDMC_EXPORT void BindDescriptorHeaps( void );

        
        void SetID( const std::wstring& ID ) 
        { 
            m_ID = ID; 
        }

        
    };


    class GraphicsContext : public CommandContext
    {
    public:

        static GraphicsContext& Begin( const std::wstring& ID = L"" )
        {
            return CommandContext::Begin( ID ).GetGraphicsContext( );
        }

        HDMC_EXPORT void ClearUAV( GpuBuffer& Target );
        HDMC_EXPORT void ClearUAV( ColorBuffer& Target );
        HDMC_EXPORT void ClearColor( ColorBuffer& Target, D3D12_RECT* Rect = nullptr );
        HDMC_EXPORT void ClearColor( ColorBuffer& Target, float Colour[ 4 ], D3D12_RECT* Rect = nullptr );
        HDMC_EXPORT void ClearDepth( DepthBuffer& Target );
        HDMC_EXPORT void ClearStencil( DepthBuffer& Target );
        HDMC_EXPORT void ClearDepthAndStencil( DepthBuffer& Target );

        HDMC_EXPORT void BeginQuery( const D3D12QueryHeap& QueryHeap, D3D12_QUERY_TYPE Type, UINT HeapIndex );
        HDMC_EXPORT void EndQuery( const D3D12QueryHeap& QueryHeap, D3D12_QUERY_TYPE Type, UINT HeapIndex );
        HDMC_EXPORT void ResolveQueryData( const D3D12QueryHeap& QueryHeap, D3D12_QUERY_TYPE Type, UINT StartIndex, UINT NumQueries, const D3D12Resource& DestinationBuffer, UINT64 DestinationBufferOffset );

        void SetRootSignature( const RootSignature& RootSig )
        {
            if ( RootSig.GetSignature( ) == m_CurGraphicsRootSignature )
            {
                return;
            }

            m_CommandList.SetGraphicsRootSignature( m_CurGraphicsRootSignature = RootSig.GetSignature( ) );

            m_DynamicViewDescriptorHeap.ParseGraphicsRootSignature( RootSig );
            m_DynamicSamplerDescriptorHeap.ParseGraphicsRootSignature( RootSig );
        }

        HDMC_EXPORT void SetRenderTargets( UINT NumRTVs, const D3D12_CPU_DESCRIPTOR_HANDLE RTVs[ ] );
        HDMC_EXPORT void SetRenderTargets( UINT NumRTVs, const D3D12_CPU_DESCRIPTOR_HANDLE RTVs[ ], D3D12_CPU_DESCRIPTOR_HANDLE DSV );
        void SetRenderTarget( D3D12_CPU_DESCRIPTOR_HANDLE RTV ) { SetRenderTargets( 1, &RTV ); }
        void SetRenderTarget( D3D12_CPU_DESCRIPTOR_HANDLE RTV, D3D12_CPU_DESCRIPTOR_HANDLE DSV ) { SetRenderTargets( 1, &RTV, DSV ); }
        void SetDepthStencilTarget( D3D12_CPU_DESCRIPTOR_HANDLE DSV ) { SetRenderTargets( 0, nullptr, DSV ); }

        HDMC_EXPORT void SetViewport( const D3D12_VIEWPORT& vp );
        HDMC_EXPORT void SetViewport( FLOAT x, FLOAT y, FLOAT w, FLOAT h, FLOAT minDepth = 0.0f, FLOAT maxDepth = 1.0f );
        HDMC_EXPORT void SetScissor( const D3D12_RECT& rect );
        void SetScissor( UINT left, UINT top, UINT right, UINT bottom )
        {
            SetScissor( CD3DX12_RECT( left, top, right, bottom ) );
        }
        HDMC_EXPORT void SetViewportAndScissor( const D3D12_VIEWPORT& vp, const D3D12_RECT& rect );
        void SetViewportAndScissor( UINT x, UINT y, UINT w, UINT h )
        {
            SetViewport( ( float )x, ( float )y, ( float )w, ( float )h );
            SetScissor( x, y, x + w, y + h );
        }
        void SetStencilRef( UINT stencilRef )
        {
            m_CommandList.OMSetStencilRef( stencilRef );
        }
        void SetBlendFactor( Color BlendFactor )
        {
#ifdef HDMC_USES_HCC_MATH
            m_CommandList.OMSetBlendFactor( BlendFactor.data( ) );
#else
            m_CommandList.OMSetBlendFactor( BlendFactor.GetPtr( ) );
#endif
        }
        void SetPrimitiveTopology( D3D12_PRIMITIVE_TOPOLOGY Topology )
        {
            m_CommandList.IASetPrimitiveTopology( Topology );
        }

        void SetConstantArray( UINT RootIndex, UINT NumConstants, const void* pConstants )
        {
            m_CommandList.SetGraphicsRoot32BitConstants( RootIndex, NumConstants, pConstants, 0 );
        }
        void SetConstant( UINT rootParameterIndex, UINT Offset, DWParam Val )
        {
            m_CommandList.SetGraphicsRoot32BitConstant( rootParameterIndex, Val.Uint, Offset );
        }
        void SetConstants( UINT RootIndex, DWParam X )
        {
            m_CommandList.SetGraphicsRoot32BitConstant( RootIndex, X.Uint, 0 );
        }
        void SetConstants( UINT RootIndex, DWParam X, DWParam Y )
        {
            m_CommandList.SetGraphicsRoot32BitConstant( RootIndex, X.Uint, 0 );
            m_CommandList.SetGraphicsRoot32BitConstant( RootIndex, Y.Uint, 1 );
        }
        void SetConstants( UINT RootIndex, DWParam X, DWParam Y, DWParam Z )
        {
            m_CommandList.SetGraphicsRoot32BitConstant( RootIndex, X.Uint, 0 );
            m_CommandList.SetGraphicsRoot32BitConstant( RootIndex, Y.Uint, 1 );
            m_CommandList.SetGraphicsRoot32BitConstant( RootIndex, Z.Uint, 2 );
        }
        void SetConstants( UINT RootIndex, DWParam X, DWParam Y, DWParam Z, DWParam W )
        {
            m_CommandList.SetGraphicsRoot32BitConstant( RootIndex, X.Uint, 0 );
            m_CommandList.SetGraphicsRoot32BitConstant( RootIndex, Y.Uint, 1 );
            m_CommandList.SetGraphicsRoot32BitConstant( RootIndex, Z.Uint, 2 );
            m_CommandList.SetGraphicsRoot32BitConstant( RootIndex, W.Uint, 3 );
        }
        void SetConstantBuffer( UINT RootIndex, D3D12_GPU_VIRTUAL_ADDRESS CBV )
        {
            m_CommandList.SetGraphicsRootConstantBufferView( RootIndex, CBV );
        }
        void SetDynamicConstantBufferView( UINT RootIndex, size_t BufferSize, const void* BufferData )
        {
            ASSERT( BufferData != nullptr && Math::IsAligned( BufferData, 16 ) );
            DynAlloc cb = m_CpuLinearAllocator.Allocate( BufferSize );
            memcpy( cb.DataPtr, BufferData, BufferSize );
            m_CommandList.SetGraphicsRootConstantBufferView( RootIndex, cb.GpuAddress );
        }
        void SetBufferSRV( UINT RootIndex, const GpuBuffer& SRV, UINT64 Offset = 0 )
        {
            ASSERT( ( SRV.m_UsageState & ( D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE ) ) != 0 );
            m_CommandList.SetGraphicsRootShaderResourceView( RootIndex, SRV.GetGpuVirtualAddress( ) + Offset );
        }
        void SetBufferUAV( UINT RootIndex, const GpuBuffer& UAV, UINT64 Offset = 0 )
        {
            ASSERT( ( UAV.m_UsageState & D3D12_RESOURCE_STATE_UNORDERED_ACCESS ) != 0 );
            m_CommandList.SetGraphicsRootUnorderedAccessView( RootIndex, UAV.GetGpuVirtualAddress( ) + Offset );
        }
        void SetDescriptorTable( UINT RootIndex, D3D12_GPU_DESCRIPTOR_HANDLE FirstHandle )
        {
            m_CommandList.SetGraphicsRootDescriptorTable( RootIndex, FirstHandle );
        }

        void SetDynamicDescriptor( UINT RootIndex, UINT Offset, D3D12_CPU_DESCRIPTOR_HANDLE Handle )
        {
            SetDynamicDescriptors( RootIndex, Offset, 1, &Handle );
        }
        void SetDynamicDescriptors( UINT RootIndex, UINT Offset, UINT Count, const D3D12_CPU_DESCRIPTOR_HANDLE Handles[ ] )
        {
            m_DynamicViewDescriptorHeap.SetGraphicsDescriptorHandles( RootIndex, Offset, Count, Handles );
        }
        void SetDynamicSampler( UINT RootIndex, UINT Offset, D3D12_CPU_DESCRIPTOR_HANDLE Handle )
        {
            SetDynamicSamplers( RootIndex, Offset, 1, &Handle );
        }
        void SetDynamicSamplers( UINT RootIndex, UINT Offset, UINT Count, const D3D12_CPU_DESCRIPTOR_HANDLE Handles[ ] )
        {
            m_DynamicSamplerDescriptorHeap.SetGraphicsDescriptorHandles( RootIndex, Offset, Count, Handles );
        }

        void SetIndexBuffer( const D3D12_INDEX_BUFFER_VIEW& IBView )
        {
            m_CommandList.IASetIndexBuffer( &IBView );
        }
        void SetVertexBuffer( UINT Slot, const D3D12_VERTEX_BUFFER_VIEW& VBView )
        {
            SetVertexBuffers( Slot, 1, &VBView );
        }
        void SetVertexBuffers( UINT StartSlot, UINT Count, const D3D12_VERTEX_BUFFER_VIEW VBViews[ ] )
        {
            m_CommandList.IASetVertexBuffers( StartSlot, Count, VBViews );
        }
        void SetDynamicVB( UINT Slot, size_t NumVertices, size_t VertexStride, const void* VertexData )
        {
            ASSERT( VertexData != nullptr && Math::IsAligned( VertexData, 16 ) );

            size_t BufferSize = Math::AlignUp( NumVertices * VertexStride, 16 );
            DynAlloc vb = m_CpuLinearAllocator.Allocate( BufferSize );

            SIMDMemCopy( vb.DataPtr, VertexData, BufferSize >> 4 );

            D3D12_VERTEX_BUFFER_VIEW VBView;
            VBView.BufferLocation = vb.GpuAddress;
            VBView.SizeInBytes = ( UINT )BufferSize;
            VBView.StrideInBytes = ( UINT )VertexStride;

            m_CommandList.IASetVertexBuffers( Slot, 1, &VBView );
        }
        void SetDynamicIB( size_t IndexCount, const uint16_t* IndexData )
        {
            ASSERT( IndexData != nullptr && Math::IsAligned( IndexData, 16 ) );

            size_t BufferSize = Math::AlignUp( IndexCount * sizeof( uint16_t ), 16 );
            DynAlloc ib = m_CpuLinearAllocator.Allocate( BufferSize );

            SIMDMemCopy( ib.DataPtr, IndexData, BufferSize >> 4 );

            D3D12_INDEX_BUFFER_VIEW IBView;
            IBView.BufferLocation = ib.GpuAddress;
            IBView.SizeInBytes = ( UINT )( IndexCount * sizeof( uint16_t ) );
            IBView.Format = DXGI_FORMAT_R16_UINT;

            m_CommandList.IASetIndexBuffer( &IBView );
        }
        void SetDynamicSRV( UINT RootIndex, size_t BufferSize, const void* BufferData )
        {
            ASSERT( BufferData != nullptr && Math::IsAligned( BufferData, 16 ) );
            DynAlloc cb = m_CpuLinearAllocator.Allocate( BufferSize );
            SIMDMemCopy( cb.DataPtr, BufferData, Math::AlignUp( BufferSize, 16 ) >> 4 );
            m_CommandList.SetGraphicsRootShaderResourceView( RootIndex, cb.GpuAddress );
        }

        void Draw( UINT VertexCount, UINT VertexStartOffset = 0 )
        {
            DrawInstanced( VertexCount, 1, VertexStartOffset, 0 );
        }
        void DrawIndexed( UINT IndexCount, UINT StartIndexLocation = 0, INT BaseVertexLocation = 0 )
        {
            DrawIndexedInstanced( IndexCount, 1, StartIndexLocation, BaseVertexLocation, 0 );
        }
        void DrawInstanced( UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation = 0, UINT StartInstanceLocation = 0 )
        {
            FlushResourceBarriers( );
            m_DynamicViewDescriptorHeap.CommitGraphicsRootDescriptorTables( m_CommandList );
            m_DynamicSamplerDescriptorHeap.CommitGraphicsRootDescriptorTables( m_CommandList );
            m_CommandList.DrawInstanced( VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation );
        }
        void DrawIndexedInstanced( UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation )
        {
            FlushResourceBarriers( );
            m_DynamicViewDescriptorHeap.CommitGraphicsRootDescriptorTables( m_CommandList );
            m_DynamicSamplerDescriptorHeap.CommitGraphicsRootDescriptorTables( m_CommandList );
            m_CommandList.DrawIndexedInstanced( IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation );
        }
        void DrawIndirect( GpuBuffer& ArgumentBuffer, uint64_t ArgumentBufferOffset = 0 )
        {
            ExecuteIndirect( Graphics::DrawIndirectCommandSignature, ArgumentBuffer, ArgumentBufferOffset );
        }
        void ExecuteIndirect( CommandSignature& CommandSig, GpuBuffer& ArgumentBuffer, uint64_t ArgumentStartOffset = 0, uint32_t MaxCommands = 1, GpuBuffer* CommandCounterBuffer = nullptr, uint64_t CounterOffset = 0 )
        {
            FlushResourceBarriers( );
            m_DynamicViewDescriptorHeap.CommitGraphicsRootDescriptorTables( m_CommandList );
            m_DynamicSamplerDescriptorHeap.CommitGraphicsRootDescriptorTables( m_CommandList );
            m_CommandList.ExecuteIndirect( CommandSig.GetSignature( ), MaxCommands, ArgumentBuffer.GetResource( ), ArgumentStartOffset, CommandCounterBuffer == nullptr ? D3D12Resource( ) : CommandCounterBuffer->GetResource( ), CounterOffset );
        }
    };

    class ComputeContext : public CommandContext
    {
    public:

        static ComputeContext& Begin( const std::wstring& ID = L"", bool Async = false );

        void ClearUAV( GpuBuffer& Target );
        void ClearUAV( ColorBuffer& Target );

        void SetRootSignature( const RootSignature& RootSig )
        {
            if ( RootSig.GetSignature( ) == m_CurComputeRootSignature )
                return;

            m_CurComputeRootSignature = RootSig.GetSignature( );
            m_CommandList.SetComputeRootSignature( m_CurComputeRootSignature );

            m_DynamicViewDescriptorHeap.ParseComputeRootSignature( RootSig );
            m_DynamicSamplerDescriptorHeap.ParseComputeRootSignature( RootSig );
        }

        void SetConstantArray( UINT RootIndex, UINT NumConstants, const void* pConstants )
        {
            m_CommandList.SetComputeRoot32BitConstants( RootIndex, NumConstants, pConstants, 0 );
        }
        void SetConstant( UINT RootIndex, UINT Offset, DWParam Val )
        {
            m_CommandList.SetComputeRoot32BitConstant( RootIndex, Val.Uint, Offset );
        }
        void SetConstants( UINT RootIndex, DWParam X )
        {
            m_CommandList.SetComputeRoot32BitConstant( RootIndex, X.Uint, 0 );
        }
        void SetConstants( UINT RootIndex, DWParam X, DWParam Y )
        {
            m_CommandList.SetComputeRoot32BitConstant( RootIndex, X.Uint, 0 );
            m_CommandList.SetComputeRoot32BitConstant( RootIndex, Y.Uint, 1 );
        }
        void SetConstants( UINT RootIndex, DWParam X, DWParam Y, DWParam Z )
        {
            m_CommandList.SetComputeRoot32BitConstant( RootIndex, X.Uint, 0 );
            m_CommandList.SetComputeRoot32BitConstant( RootIndex, Y.Uint, 1 );
            m_CommandList.SetComputeRoot32BitConstant( RootIndex, Z.Uint, 2 );
        }
        void SetConstants( UINT RootIndex, DWParam X, DWParam Y, DWParam Z, DWParam W )
        {
            m_CommandList.SetComputeRoot32BitConstant( RootIndex, X.Uint, 0 );
            m_CommandList.SetComputeRoot32BitConstant( RootIndex, Y.Uint, 1 );
            m_CommandList.SetComputeRoot32BitConstant( RootIndex, Z.Uint, 2 );
            m_CommandList.SetComputeRoot32BitConstant( RootIndex, W.Uint, 3 );
        }

        void SetConstantBuffer( UINT RootIndex, D3D12_GPU_VIRTUAL_ADDRESS CBV )
        {
            m_CommandList.SetComputeRootConstantBufferView( RootIndex, CBV );
        }
        void SetDynamicConstantBufferView( UINT RootIndex, size_t BufferSize, const void* BufferData )
        {
            ASSERT( BufferData != nullptr && Math::IsAligned( BufferData, 16 ) );
            DynAlloc cb = m_CpuLinearAllocator.Allocate( BufferSize );
            memcpy( cb.DataPtr, BufferData, BufferSize );
            m_CommandList.SetComputeRootConstantBufferView( RootIndex, cb.GpuAddress );
        }
        void SetDynamicSRV( UINT RootIndex, size_t BufferSize, const void* BufferData )
        {
            ASSERT( BufferData != nullptr && Math::IsAligned( BufferData, 16 ) );
            DynAlloc cb = m_CpuLinearAllocator.Allocate( BufferSize );
            SIMDMemCopy( cb.DataPtr, BufferData, Math::AlignUp( BufferSize, 16 ) >> 4 );
            m_CommandList.SetComputeRootShaderResourceView( RootIndex, cb.GpuAddress );
        }
        void SetBufferSRV( UINT RootIndex, const GpuBuffer& SRV, UINT64 Offset = 0 )
        {
            ASSERT( ( SRV.m_UsageState & D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE ) != 0 );
            m_CommandList.SetComputeRootShaderResourceView( RootIndex, SRV.GetGpuVirtualAddress( ) + Offset );
        }
        void SetBufferUAV( UINT RootIndex, const GpuBuffer& UAV, UINT64 Offset = 0 )
        {
            ASSERT( ( UAV.m_UsageState & D3D12_RESOURCE_STATE_UNORDERED_ACCESS ) != 0 );
            m_CommandList.SetComputeRootUnorderedAccessView( RootIndex, UAV.GetGpuVirtualAddress( ) + Offset );
        }
        void SetDescriptorTable( UINT RootIndex, D3D12_GPU_DESCRIPTOR_HANDLE FirstHandle )
        {
            m_CommandList.SetComputeRootDescriptorTable( RootIndex, FirstHandle );
        }

        void SetDynamicDescriptor( UINT RootIndex, UINT Offset, D3D12_CPU_DESCRIPTOR_HANDLE Handle )
        {
            SetDynamicDescriptors( RootIndex, Offset, 1, &Handle );
        }
        void SetDynamicDescriptors( UINT RootIndex, UINT Offset, UINT Count, const D3D12_CPU_DESCRIPTOR_HANDLE Handles[ ] )
        {
            m_DynamicViewDescriptorHeap.SetComputeDescriptorHandles( RootIndex, Offset, Count, Handles );
        }
        void SetDynamicSampler( UINT RootIndex, UINT Offset, D3D12_CPU_DESCRIPTOR_HANDLE Handle )
        {
            SetDynamicSamplers( RootIndex, Offset, 1, &Handle );
        }
        void SetDynamicSamplers( UINT RootIndex, UINT Offset, UINT Count, const D3D12_CPU_DESCRIPTOR_HANDLE Handles[ ] )
        {
            m_DynamicSamplerDescriptorHeap.SetComputeDescriptorHandles( RootIndex, Offset, Count, Handles );
        }

        void Dispatch( size_t GroupCountX = 1, size_t GroupCountY = 1, size_t GroupCountZ = 1 )
        {
            FlushResourceBarriers( );
            m_DynamicViewDescriptorHeap.CommitComputeRootDescriptorTables( m_CommandList );
            m_DynamicSamplerDescriptorHeap.CommitComputeRootDescriptorTables( m_CommandList );
            m_CommandList.Dispatch( ( UINT )GroupCountX, ( UINT )GroupCountY, ( UINT )GroupCountZ );
        }
        void Dispatch1D( size_t ThreadCountX, size_t GroupSizeX = 64 )
        {
            Dispatch( Math::DivideByMultiple( ThreadCountX, GroupSizeX ), 1, 1 );
        }
        void Dispatch2D( size_t ThreadCountX, size_t ThreadCountY, size_t GroupSizeX = 8, size_t GroupSizeY = 8 )
        {
            Dispatch( Math::DivideByMultiple( ThreadCountX, GroupSizeX ), Math::DivideByMultiple( ThreadCountY, GroupSizeY ), 1 );
        }
        void Dispatch3D( size_t ThreadCountX, size_t ThreadCountY, size_t ThreadCountZ, size_t GroupSizeX, size_t GroupSizeY, size_t GroupSizeZ )
        {
            Dispatch( Math::DivideByMultiple( ThreadCountX, GroupSizeX ), Math::DivideByMultiple( ThreadCountY, GroupSizeY ), Math::DivideByMultiple( ThreadCountZ, GroupSizeZ ) );
        }
        void DispatchIndirect( GpuBuffer& ArgumentBuffer, uint64_t ArgumentBufferOffset = 0 )
        {
            ExecuteIndirect( Graphics::DispatchIndirectCommandSignature, ArgumentBuffer, ArgumentBufferOffset );
        }
        void ExecuteIndirect( CommandSignature& CommandSig, GpuBuffer& ArgumentBuffer, uint64_t ArgumentStartOffset = 0, uint32_t MaxCommands = 1, GpuBuffer* CommandCounterBuffer = nullptr, uint64_t CounterOffset = 0 )
        {
            FlushResourceBarriers( );
            m_DynamicViewDescriptorHeap.CommitComputeRootDescriptorTables( m_CommandList );
            m_DynamicSamplerDescriptorHeap.CommitComputeRootDescriptorTables( m_CommandList );
            m_CommandList.ExecuteIndirect( CommandSig.GetSignature( ), MaxCommands, ArgumentBuffer.GetResource( ), ArgumentStartOffset, CommandCounterBuffer == nullptr ? D3D12Resource( ) : CommandCounterBuffer->GetResource( ), CounterOffset );
        }
    };
}
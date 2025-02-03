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
#include <HAIDirectML.h>

using namespace Harlinn::AI;
using namespace Harlinn::Windows::Graphics;

// Enable this to show element-wise identity multiplied by a scalar placed in a constant node.
// This only applies to the DirectMLX API that builds a graph.
#define MULTIPLY_WITH_SCALAR_CONSTANT 0

void InitializeDirect3D12( D3D12::Device& d3D12Device,
    D3D12::CommandQueue& commandQueue,
    D3D12::CommandAllocator& commandAllocator,
    D3D12::GraphicsCommandList& commandList )
{
    auto dxgiFactory = DXGI::CreateFactory<DXGI::Factory4>( );
    auto dxgiAdapter = dxgiFactory.FindAdapter( D3D_FEATURE_LEVEL_12_1 );
    d3D12Device = D3D12::CreateDevice< D3D12::Device>( dxgiAdapter, D3D_FEATURE_LEVEL_12_1 );
    
    commandQueue = d3D12Device.CreateCommandQueue( );
    commandAllocator = d3D12Device.CreateCommandAllocator( );
    commandList = d3D12Device.CreateCommandList( 0, D3D12::CommandListType::Direct, commandAllocator );
}

void CloseExecuteResetWait( D3D12::Device& d3D12Device,
    D3D12::CommandQueue& commandQueue,
    D3D12::CommandAllocator& commandAllocator,
    D3D12::GraphicsCommandList& commandList )
{
    commandList.Close( );

    commandQueue.ExecuteCommandLists( commandList );

    auto d3D12Fence = d3D12Device.CreateFence( );
    EventWaitHandle fenceEventHandle( true, false );
    commandQueue.Signal( d3D12Fence, 1 );
    d3D12Fence.SetEventOnCompletion( 1, fenceEventHandle );

    fenceEventHandle.Wait( );
    commandAllocator.Reset( );
    commandList.Reset( commandAllocator );
}

int main( )
{
    D3D12::Device d3D12Device;
    D3D12::CommandQueue commandQueue;
    D3D12::CommandAllocator commandAllocator;
    D3D12::GraphicsCommandList commandList;

    // Set up Direct3D 12.
    InitializeDirect3D12( d3D12Device, commandQueue, commandAllocator, commandList );

    // Create the DirectML device.
    auto dmlDevice = DML::CreateDevice( d3D12Device );

    constexpr UINT tensorSizes[ 4 ] = { 1, 2, 3, 4 };
    constexpr UINT tensorElementCount = tensorSizes[ 0 ] * tensorSizes[ 1 ] * tensorSizes[ 2 ] * tensorSizes[ 3 ];

    DML::BufferTensorDesc dmlBufferTensorDesc( DML::TensorDataType::Float32, tensorSizes );

    DML::Operator dmlOperator;
    {
        // Create DirectML operator(s). Operators represent abstract functions such as "multiply", "reduce", "convolution", or even
        // compound operations such as recurrent neural nets. This example creates an instance of the Identity operator,
        // which applies the function f(x) = x for all elements in a tensor.
        DML::TensorDesc dmlTensorDesc( &dmlBufferTensorDesc );

        // Input and output tensors have same size/type.
        DML::ElementWiseIdentityOperatorDesc dmlIdentityOperatorDesc( &dmlTensorDesc, &dmlTensorDesc );

        // Like Direct3D 12, these DESC structs don't need to be long-lived. This means, for example, that it's safe to place
        // the DML_OPERATOR_DESC (and all the subobjects it points to) on the stack, since they're no longer needed after
        // CreateOperator returns.
        dmlOperator = dmlDevice.CreateOperator( dmlIdentityOperatorDesc );
    }

    // Compile the operator into an object that can be dispatched to the GPU. In this step, DirectML performs operator
    // fusion and just-in-time (JIT) compilation of shader bytecode, then compiles it into a Direct3D 12 pipeline state object (PSO).
    // The resulting compiled operator is a baked, optimized form of an operator suitable for execution on the GPU.
    auto dmlCompiledOperator = dmlDevice.CompileOperator( dmlOperator );

    // 24 elements * 4 == 96 bytes.
    UInt64 tensorBufferSize = dmlBufferTensorDesc.TotalTensorSizeInBytes;

    auto dmlOperatorInitializer = dmlDevice.CreateOperatorInitializer( dmlCompiledOperator );

    // Query the operator for the required size (in descriptors) of its binding table.
    // You need to initialize an operator exactly once before it can be executed, and
    // the two stages require different numbers of descriptors for binding. For simplicity,
    // we create a single descriptor heap that's large enough to satisfy them both.
    DML::BindingProperties initializeBindingProperties = dmlOperatorInitializer.GetBindingProperties( );
    DML::BindingProperties executeBindingProperties = dmlCompiledOperator.GetBindingProperties( );
    UINT descriptorCount = std::max( initializeBindingProperties.RequiredDescriptorCount, executeBindingProperties.RequiredDescriptorCount );

    // Create descriptor heaps.
    auto descriptorHeap = d3D12Device.CreateDescriptorHeap( descriptorCount, D3D12::DescriptorHeapFlags::ShaderVisible );

    // Set the descriptor heap(s).
    commandList.SetDescriptorHeaps( descriptorHeap );

    // Create a binding table over the descriptor heap we just created.
    DML::BindingTableDesc dmlBindingTableDesc( dmlOperatorInitializer, 
                                                descriptorHeap.GetCPUDescriptorHandleForHeapStart( ), 
                                                descriptorHeap.GetGPUDescriptorHandleForHeapStart( ), 
                                                descriptorCount );
    auto dmlBindingTable = dmlDevice.CreateBindingTable( &dmlBindingTableDesc );

    // Create the temporary and persistent resources that are necessary for executing an operator.

    // The temporary resource is scratch memory (used internally by DirectML), whose contents you don't need to define.
    // The persistent resource is long-lived, and you need to initialize it using the IDMLOperatorInitializer.
    UINT64 temporaryResourceSize = std::max( initializeBindingProperties.TemporaryResourceSize, executeBindingProperties.TemporaryResourceSize );
    UINT64 persistentResourceSize = executeBindingProperties.PersistentResourceSize;

    // Bind and initialize the operator on the GPU.
    D3D12::Resource temporaryBuffer;
    if ( temporaryResourceSize != 0 )
    {
        temporaryBuffer = d3D12Device.CreateCommittedResource( D3D12::HeapProperties( D3D12::HeapType::Default ),
                                            D3D12::HeapFlags::None,
                                            D3D12::ResourceDesc( temporaryResourceSize, D3D12::ResourceFlags::AllowUnorderedAccess ),
                                            D3D12::ResourceStates::Common );

        if ( initializeBindingProperties.TemporaryResourceSize != 0 )
        {
            dmlBindingTable.BindTemporaryResource( temporaryBuffer, temporaryResourceSize );
        }
    }

    D3D12::Resource persistentBuffer;
    if ( persistentResourceSize != 0 )
    {
        persistentBuffer = d3D12Device.CreateCommittedResource( D3D12::HeapProperties( D3D12::HeapType::Default ),
                                            D3D12::HeapFlags::None,
                                            D3D12::ResourceDesc( persistentResourceSize, D3D12::ResourceFlags::AllowUnorderedAccess ),
                                            D3D12::ResourceStates::Common );

        // The persistent resource should be bound as the output to the IDMLOperatorInitializer.
        dmlBindingTable.BindOutputs( persistentBuffer, persistentResourceSize );
    }

    // The command recorder is a stateless object that records Dispatches into an existing Direct3D 12 command list.
    auto dmlCommandRecorder = dmlDevice.CreateCommandRecorder( );

    // Record execution of the operator initializer.
    dmlCommandRecorder.RecordDispatch( commandList, dmlOperatorInitializer, dmlBindingTable );

    // Close the Direct3D 12 command list, and submit it for execution as you would any other command list. You could
    // in principle record the execution into the same command list as the initialization, but you need only to Initialize
    // once, and typically you want to Execute an operator more frequently than that.
    CloseExecuteResetWait( d3D12Device, commandQueue, commandAllocator, commandList );

    // Bind and execute the operator on the GPU.
    commandList.SetDescriptorHeaps( descriptorHeap );

    // Reset the binding table to bind for the operator we want to execute (it was previously used to bind for the
    // initializer).
    dmlBindingTableDesc.Dispatchable = dmlCompiledOperator;
    dmlBindingTable.Reset( &dmlBindingTableDesc );

    if ( temporaryResourceSize != 0 )
    {
        dmlBindingTable.BindTemporaryResource( temporaryBuffer, temporaryResourceSize );
    }

    if ( persistentResourceSize != 0 )
    {
        dmlBindingTable.BindPersistentResource( persistentBuffer, persistentResourceSize );
    }

    // Create tensor buffers for upload/input/output/readback of the tensor elements.
    auto uploadBuffer = d3D12Device.CreateCommittedResource( D3D12::HeapProperties( D3D12::HeapType::Upload ),
                                            D3D12::HeapFlags::None,
                                            D3D12::ResourceDesc( tensorBufferSize ),
                                            D3D12::ResourceStates::GenericRead );

    auto inputBuffer = d3D12Device.CreateCommittedResource( D3D12::HeapProperties( D3D12::HeapType::Default ),
                                            D3D12::HeapFlags::None,
                                            D3D12::ResourceDesc( tensorBufferSize, D3D12::ResourceFlags::AllowUnorderedAccess ),
                                            D3D12::ResourceStates::CopyDest );

    std::wcout << std::fixed; std::wcout.precision( 4 );
    std::array<FLOAT, tensorElementCount> inputTensorElementArray;
    {
        std::wcout << L"input tensor: ";
        for ( auto& element : inputTensorElementArray )
        {
            element = 1.618f;
            std::wcout << element << L' ';
        };
        std::wcout << std::endl;

        D3D12::SubResourceData tensorSubResourceData( inputTensorElementArray.data( ), tensorBufferSize );

        // Upload the input tensor to the GPU.
        D3D12::UpdateSubResources( commandList, inputBuffer, uploadBuffer, 0, 0, 1, &tensorSubResourceData );
        commandList.ResourceBarrier( inputBuffer, D3D12::ResourceStates::CopyDest, D3D12::ResourceStates::UnorderedAccess );
    }

    dmlBindingTable.BindInputs( inputBuffer, tensorBufferSize );

    auto outputBuffer = d3D12Device.CreateCommittedResource( D3D12::HeapProperties( D3D12::HeapType::Default ),
                                            D3D12::HeapFlags::None,
                                            D3D12::ResourceDesc( tensorBufferSize, D3D12::ResourceFlags::AllowUnorderedAccess ),
                                            D3D12::ResourceStates::UnorderedAccess );

    dmlBindingTable.BindOutputs( outputBuffer, tensorBufferSize );

    // Record execution of the compiled operator.
    dmlCommandRecorder.RecordDispatch( commandList, dmlCompiledOperator, dmlBindingTable );
    CloseExecuteResetWait( d3D12Device, commandQueue, commandAllocator, commandList );

    // The output buffer now contains the result of the identity operator,
    // so read it back if you want the CPU to access it.
    auto readbackBuffer = d3D12Device.CreateCommittedResource( D3D12::HeapProperties( D3D12::HeapType::ReadBack ),
                                            D3D12::HeapFlags::None,
                                            D3D12::ResourceDesc( tensorBufferSize ),
                                            D3D12::ResourceStates::CopyDest );

    commandList.ResourceBarrier( outputBuffer, D3D12::ResourceStates::UnorderedAccess, D3D12::ResourceStates::CopySource );
    commandList.CopyResource( readbackBuffer, outputBuffer );

    CloseExecuteResetWait( d3D12Device, commandQueue, commandAllocator, commandList );

    D3D12::Range tensorBufferRange( 0, static_cast< SIZE_T >( tensorBufferSize ) );
    auto outputBufferData = reinterpret_cast< float* >( readbackBuffer.Map( 0, tensorBufferRange ) );

    std::wstring outputString = L"output tensor: ";
    for ( size_t tensorElementIndex{ 0 }; tensorElementIndex < tensorElementCount; ++tensorElementIndex, ++outputBufferData )
    {
        outputString += std::to_wstring( *outputBufferData ) + L' ';
    }

    std::wcout << outputString << std::endl;
    OutputDebugStringW( outputString.c_str( ) );

    D3D12::Range emptyRange;
    readbackBuffer.Unmap( 0, emptyRange );
}
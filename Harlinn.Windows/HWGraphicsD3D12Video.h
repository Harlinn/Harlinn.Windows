#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D12VIDEO_H_
#define HARLINN_WINDOWS_HWGRAPHICSD3D12VIDEO_H_
/*
   Copyright 2024 Espen Harlinn

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

#include "HWGraphicsD3D12.h"

namespace Harlinn::Windows::Graphics::D3D12::Video
{

}


namespace Harlinn::Windows::Graphics::D3D12::Video
{
    class D3D12VideoDecoderHeap : public D3D12Pageable
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoDecoderHeap, D3D12Pageable, ID3D12VideoDecoderHeap, ID3D12Pageable)
    public:
        D3D12_VIDEO_DECODER_HEAP_DESC GetDesc() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetDesc();
        }
    };
    

    class D3D12VideoDevice : public Unknown
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoDevice, Unknown, ID3D12VideoDevice, IUnknown)
    public:
        bool CheckFeatureSupport(D3D12_FEATURE_VIDEO featureVideo, void* featureSupportData, UINT featureSupportDataSize) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->CheckFeatureSupport(featureVideo, featureSupportData, featureSupportDataSize) == S_OK;
        }

        void CreateVideoDecoder(const D3D12_VIDEO_DECODER_DESC* videoDecoderDesc, REFIID riid, void** videoDecoder) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->CreateVideoDecoder(videoDecoderDesc, riid, videoDecoder);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateVideoDecoderHeap(const D3D12_VIDEO_DECODER_HEAP_DESC* videoDecoderHeapDesc, REFIID riid, void** videoDecoderHeap) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->CreateVideoDecoderHeap(videoDecoderHeapDesc, riid, videoDecoderHeap);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateVideoProcessor(UINT nodeMask, const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC* outputStreamDesc, UINT numberOfInputStreamDescs, const D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC* inputStreamDescs, REFIID riid, void** videoProcessor) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->CreateVideoProcessor(nodeMask, outputStreamDesc, numberOfInputStreamDescs, inputStreamDescs, riid, videoProcessor);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };
    

    class D3D12VideoDecoder : public D3D12Pageable
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoDecoder, D3D12Pageable, ID3D12VideoDecoder, ID3D12Pageable)
    public:
        D3D12_VIDEO_DECODER_DESC GetDesc() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetDesc();
        }
    };
    

    class D3D12VideoProcessor : public D3D12Pageable
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoProcessor, D3D12Pageable, ID3D12VideoProcessor, ID3D12Pageable)
    public:
        UINT GetNodeMask() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetNodeMask();
        }

        UINT GetNumInputStreamDescs() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetNumInputStreamDescs();
        }

        void GetInputStreamDescs(UINT numberOfInputStreamDescs, D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC* inputStreamDescs) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->GetInputStreamDescs(numberOfInputStreamDescs, inputStreamDescs);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC GetOutputStreamDesc() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetOutputStreamDesc();
        }
    };
    


    /// <summary>
    /// Encapsulates a list of graphics commands for video decoding.
    /// </summary>
    class D3D12VideoDecodeCommandList : public D3D12CommandList
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoDecodeCommandList, D3D12CommandList, ID3D12VideoDecodeCommandList, ID3D12CommandList)
    public:
        /// <summary>
        /// Indicates that recording to the command list has finished.
        /// </summary>
        void Close( ) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->Close( );
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        /// <summary>
        /// Resets a command list back to its initial state as if a new command list was just created.
        /// </summary>
        /// <param name="allocator">
        /// A pointer to the ID3D12CommandAllocator object that the device creates command lists from.
        /// </param>
        void Reset( ID3D12CommandAllocator* allocator) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->Reset(allocator);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void Reset(const D3D12CommandAllocator& allocator) const
        {
            Reset(allocator.GetInterfacePointer<ID3D12CommandAllocator>());
        }


        /// <summary>
        /// Resets the state of a direct command list back to the state it was 
        /// in when the command list was created.
        /// </summary>
        void ClearState( ) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ClearState( );
        }

        /// <summary>
        /// Notifies the driver that it needs to synchronize multiple accesses to resources.
        /// </summary>
        /// <param name="numberOfBarriers">
        /// The number of submitted barrier descriptions.
        /// </param>
        /// <param name="barriers">
        /// Pointer to an array of barrier descriptions.
        /// </param>
        void ResourceBarrier( UINT numberOfBarriers, const D3D12_RESOURCE_BARRIER* barriers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ResourceBarrier(numberOfBarriers, barriers);
        }

        /// <summary>
        /// Indicate that the current contents of a resource can be discarded. The current 
        /// contents of the resource are no longer valid allowing optimizations for subsequent 
        /// operations such as ResourceBarrier.
        /// </summary>
        /// <param name="resource">
        /// A pointer to the ID3D12Resource interface for the resource to discard.
        /// </param>
        /// <param name="region">
        /// A pointer to a D3D12_DISCARD_REGION structure that describes details for the 
        /// discard-resource operation.
        /// </param>
        void DiscardResource( ID3D12Resource* resource, const D3D12_DISCARD_REGION* region = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DiscardResource(resource, region);
        }
        void DiscardResource(const D3D12Resource& resource, const D3D12_DISCARD_REGION* region = nullptr) const
        {
            DiscardResource(resource.GetInterfacePointer<ID3D12Resource>(), region);
        }

        /// <summary>
        /// Starts a query running.
        /// </summary>
        /// <param name="queryHeap">
        /// A pointer to an ID3D12QueryHeap specifying the storage for this query.
        /// </param>
        /// <param name="queryType">
        /// A member of the D3D12_QUERY_TYPE enumeration specifying the type of the query.
        /// </param>
        /// <param name="index">
        /// The index of the query within the query heap.
        /// </param>
        void BeginQuery( ID3D12QueryHeap* queryHeap, D3D12_QUERY_TYPE queryType, UINT index) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->BeginQuery( queryHeap, queryType, index);
        }
        void BeginQuery(const D3D12QueryHeap& queryHeap, D3D12_QUERY_TYPE queryType, UINT index) const
        {
            BeginQuery(queryHeap.GetInterfacePointer<ID3D12QueryHeap>(), queryType, index);
        }


        /// <summary>
        /// Ends a query.
        /// </summary>
        /// <param name="queryHeap">
        /// A pointer to an ID3D12QueryHeap specifying the storage for this query.
        /// </param>
        /// <param name="queryType">
        /// A member of the D3D12_QUERY_TYPE enumeration specifying the type of the query.
        /// </param>
        /// <param name="index">
        /// The index of the query within the query heap.
        /// </param>
        void EndQuery( ID3D12QueryHeap* queryHeap, D3D12_QUERY_TYPE queryType, UINT index) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->EndQuery(queryHeap, queryType, index);
        }
        void EndQuery(const D3D12QueryHeap& queryHeap, D3D12_QUERY_TYPE queryType, UINT index) const
        {
            EndQuery(queryHeap.GetInterfacePointer<ID3D12QueryHeap>(), queryType, index);
        }

        /// <summary>
        /// Extracts data from a query.
        /// </summary>
        /// <param name="queryHeap">
        /// A pointer to an ID3D12QueryHeap specifying the storage containing the queries to resolve.
        /// </param>
        /// <param name="queryType">
        /// A member of the D3D12_QUERY_TYPE enumeration specifying the type of the query.
        /// </param>
        /// <param name="startIndex">
        /// The index of the first query to resolve.
        /// </param>
        /// <param name="numberOfQueries">
        /// The number of queries to resolve.
        /// </param>
        /// <param name="destinationBuffer">
        /// A pointer to an ID3D12Resource representing the destination buffer. The resource must be in 
        /// the state D3D12_RESOURCE_STATE_COPY_DEST.
        /// </param>
        /// <param name="alignedDestinationBufferOffset">
        /// The alignment offset into the destination buffer. This must be a multiple of 8 bytes.
        /// </param>
        void ResolveQueryData(ID3D12QueryHeap* queryHeap, D3D12_QUERY_TYPE queryType, UINT startIndex, UINT numberOfQueries, ID3D12Resource* destinationBuffer, UINT64 alignedDestinationBufferOffset) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ResolveQueryData(queryHeap, queryType, startIndex, numberOfQueries, destinationBuffer, alignedDestinationBufferOffset);
        }
        void ResolveQueryData(const D3D12QueryHeap& queryHeap, D3D12_QUERY_TYPE queryType, UINT startIndex, UINT numberOfQueries, const D3D12Resource& destinationBuffer, UINT64 alignedDestinationBufferOffset) const
        {
            ResolveQueryData(queryHeap.GetInterfacePointer<ID3D12QueryHeap>(), queryType, startIndex, numberOfQueries, destinationBuffer.GetInterfacePointer<ID3D12Resource>(), alignedDestinationBufferOffset);
        }


        /// <summary>
        /// Specifies that subsequent commands should not be performed if the predicate value passes 
        /// the specified operation.
        /// </summary>
        /// <param name="buffer">
        /// A pointer to an ID3D12Resource representing the buffer from which to read the 64-bit predication value.
        /// </param>
        /// <param name="alignedBufferOffset">
        /// The UINT64-aligned buffer offset.
        /// </param>
        /// <param name="operation">
        /// A member of the D3D12_PREDICATION_OP enumeration specifying the predicate operation.
        /// </param>
        void SetPredication(ID3D12Resource* buffer, UINT64 alignedBufferOffset, D3D12_PREDICATION_OP operation) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetPredication(buffer, alignedBufferOffset, operation);
        }
        void SetPredication(const D3D12Resource& buffer, UINT64 alignedBufferOffset, D3D12_PREDICATION_OP operation) const
        {
            SetPredication(buffer.GetInterfacePointer<ID3D12Resource>(), alignedBufferOffset, operation);
        }

        /// <summary>
        /// For internal use only. Not intended to be called directly.
        /// </summary>
        /// <param name="metadata">Internal.</param>
        /// <param name="data">Internal.</param>
        /// <param name="dataSize">Internal.</param>
        void SetMarker( UINT metadata, const void* data, UINT dataSize) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetMarker(metadata, data, dataSize);
        }


        /// <summary>
        /// For internal use only. Not intended to be called directly.
        /// </summary>
        /// <param name="metadata">Internal.</param>
        /// <param name="data">Internal.</param>
        /// <param name="dataSize">Internal.</param>
        void BeginEvent(UINT metadata, const void* data, UINT dataSize) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->BeginEvent(metadata, data, dataSize);
        }

        /// <summary>
        /// For internal use only. Not intended to be called directly.
        /// </summary>
        void EndEvent( ) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->EndEvent( );
        }

        /// <summary>
        /// Records a decode frame operation to the command list. Inputs, outputs, 
        /// and parameters for the decode are specified as arguments to this method.
        /// </summary>
        /// <param name="decoder">
        /// A pointer to an ID3D12VideoDecoder interface representing a decoder instance.
        /// </param>
        /// <param name="outputArguments">
        /// A D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS structure specifying the output 
        /// surface and output arguments.
        /// </param>
        /// <param name="inputArguments">
        /// A D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS structure specifying the input 
        /// bitstream, reference frames, and other input parameters.
        /// </param>
        void DecodeFrame( ID3D12VideoDecoder* decoder, const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS* outputArguments, const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS* inputArguments) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DecodeFrame(decoder, outputArguments, inputArguments);
        }
        void DecodeFrame(const D3D12VideoDecoder& decoder, const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS* outputArguments, const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS* inputArguments) const
        {
            DecodeFrame(decoder.GetInterfacePointer<ID3D12VideoDecoder>(), outputArguments, inputArguments);
        }

        /// <summary>
        /// Writes a number of 32-bit immediate values to the specified buffer locations 
        /// directly from the command stream.
        /// </summary>
        /// <param name="count">
        /// The number of elements in the params and modes arrays.
        /// </param>
        /// <param name="params">
        /// The address of an array of D3D12_WRITEBUFFERIMMEDIATE_PARAMETER structures of size count.
        /// </param>
        /// <param name="modes">
        /// The address of an array of D3D12_WRITEBUFFERIMMEDIATE_MODE structures of size count. The 
        /// default value is nullptr. Passing nullptr causes the system to write all immediate values 
        /// using D3D12_WRITEBUFFERIMMEDIATE_MODE_DEFAULT.
        /// </param>
        void WriteBufferImmediate(UINT count, const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER* params, const D3D12_WRITEBUFFERIMMEDIATE_MODE* modes = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->WriteBufferImmediate(count, params, modes);
        }
    };
    using DecodeCommandList = D3D12VideoDecodeCommandList;

    /// <summary>
    /// Encapsulates a list of graphics commands for video processing.
    /// </summary>
    class D3D12VideoProcessCommandList : public D3D12CommandList
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoProcessCommandList, D3D12CommandList, ID3D12VideoProcessCommandList, ID3D12CommandList)
    public:
        /// <summary>
        /// Indicates that recording to the command list has finished
        /// </summary>
        void Close( ) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->Close();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        /// <summary>
        /// Resets a command list back to its initial state as if a new command list was just created.
        /// </summary>
        /// <param name="allocator">
        /// A pointer to the ID3D12CommandAllocator object that the device creates command lists from.
        /// </param>
        void Reset(ID3D12CommandAllocator* allocator) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->Reset(allocator);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void Reset(const D3D12CommandAllocator& allocator) const
        {
            Reset(allocator.GetInterfacePointer<ID3D12CommandAllocator>());
        }

        /// <summary>
        /// Resets the state of a direct command list back to the state it was in when the command list 
        /// was created.
        /// </summary>
        void ClearState() const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ClearState();
        }

        /// <summary>
        /// otifies the driver that it needs to synchronize multiple accesses to resources.
        /// </summary>
        /// <param name="numberOfBarriers">
        /// The number of submitted barrier descriptions.
        /// </param>
        /// <param name="barriers">
        /// Pointer to an array of barrier descriptions.
        /// </param>
        void ResourceBarrier(UINT numberOfBarriers, const D3D12_RESOURCE_BARRIER* barriers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ResourceBarrier(numberOfBarriers, barriers);
        }

        /// <summary>
        /// Indicates that the current contents of a resource can be discarded. The current contents 
        /// of the resource are no longer valid allowing optimizations for subsequent operations such 
        /// as ResourceBarrier.
        /// </summary>
        /// <param name="resource">
        /// A pointer to the ID3D12Resource interface for the resource to discard.
        /// </param>
        /// <param name="region">
        /// A pointer to a D3D12_DISCARD_REGION structure that describes details for the discard-resource 
        /// operation.
        /// </param>
        void DiscardResource(ID3D12Resource* resource, const D3D12_DISCARD_REGION* region = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DiscardResource(resource, region);
        }
        void DiscardResource(const D3D12Resource& resource, const D3D12_DISCARD_REGION* region = nullptr) const
        {
            DiscardResource(resource.GetInterfacePointer<ID3D12Resource>(), region);
        }

        /// <summary>
        /// Starts a query running.
        /// </summary>
        /// <param name="queryHeap">
        /// A pointer to an ID3D12QueryHeap specifying the storage for this query.
        /// </param>
        /// <param name="queryType">
        /// A member of the D3D12_QUERY_TYPE enumeration specifying the type of the query.
        /// </param>
        /// <param name="index">
        /// The index of the query within the query heap.
        /// </param>
        void BeginQuery(ID3D12QueryHeap* queryHeap, D3D12_QUERY_TYPE queryType, UINT index) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->BeginQuery(queryHeap, queryType, index);
        }
        void BeginQuery(const D3D12QueryHeap& queryHeap, D3D12_QUERY_TYPE queryType, UINT index) const
        {
            BeginQuery(queryHeap.GetInterfacePointer<ID3D12QueryHeap>(), queryType, index);
        }

        /// <summary>
        /// Ends a query.
        /// </summary>
        /// <param name="queryHeap">
        /// A pointer to an ID3D12QueryHeap specifying the storage for this query.
        /// </param>
        /// <param name="queryType">
        /// A member of the D3D12_QUERY_TYPE enumeration specifying the type of 
        /// the query.
        /// </param>
        /// <param name="index">
        /// The index of the query within the query heap.
        /// </param>
        void EndQuery(ID3D12QueryHeap* queryHeap, D3D12_QUERY_TYPE queryType, UINT index) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->EndQuery(queryHeap, queryType, index);
        }
        void EndQuery(const D3D12QueryHeap& queryHeap, D3D12_QUERY_TYPE queryType, UINT index) const
        {
            EndQuery(queryHeap.GetInterfacePointer<ID3D12QueryHeap>(), queryType, index);
        }
        
        /// <summary>
        /// Extracts data from a query.
        /// </summary>
        /// <param name="queryHeap">
        /// A pointer to an ID3D12QueryHeap specifying the storage containing the 
        /// queries to resolve.
        /// </param>
        /// <param name="queryType">
        /// A member of the D3D12_QUERY_TYPE enumeration specifying the type of 
        /// the query.
        /// </param>
        /// <param name="startIndex">
        /// The index of the first query to resolve.
        /// </param>
        /// <param name="numberOfQueries">
        /// The number of queries to resolve.
        /// </param>
        /// <param name="destinationBuffer">
        /// A pointer to an ID3D12Resource representing the destination buffer. The 
        /// resource must be in the state D3D12_RESOURCE_STATE_COPY_DEST.
        /// </param>
        /// <param name="alignedDestinationBufferOffset">
        /// The alignment offset into the destination buffer. This must be a multiple 
        /// of 8 bytes.
        /// </param>
        void ResolveQueryData(ID3D12QueryHeap* queryHeap, D3D12_QUERY_TYPE queryType, UINT startIndex, UINT numberOfQueries, ID3D12Resource* destinationBuffer, UINT64 alignedDestinationBufferOffset) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ResolveQueryData(queryHeap, queryType, startIndex, numberOfQueries, destinationBuffer, alignedDestinationBufferOffset);
        }
        void ResolveQueryData(const D3D12QueryHeap& queryHeap, D3D12_QUERY_TYPE queryType, UINT startIndex, UINT numberOfQueries, const D3D12Resource& destinationBuffer, UINT64 alignedDestinationBufferOffset) const
        {
            ResolveQueryData(queryHeap.GetInterfacePointer<ID3D12QueryHeap>(), queryType, startIndex, numberOfQueries, destinationBuffer.GetInterfacePointer<ID3D12Resource>(), alignedDestinationBufferOffset);
        }

        /// <summary>
        /// Specifies that subsequent commands should not be performed if the predicate 
        /// value passes the specified operation.
        /// </summary>
        /// <param name="buffer">
        /// A pointer to an ID3D12Resource representing the buffer from which to read the 
        /// 64-bit predication value.
        /// </param>
        /// <param name="alignedBufferOffset">
        /// The UINT64-aligned buffer offset.
        /// </param>
        /// <param name="operation">
        /// A member of the D3D12_PREDICATION_OP enumeration specifying the predicate operation.
        /// </param>
        void SetPredication(ID3D12Resource* buffer, UINT64 alignedBufferOffset, D3D12_PREDICATION_OP operation) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetPredication(buffer, alignedBufferOffset, operation);
        }
        void SetPredication(const D3D12Resource& buffer, UINT64 alignedBufferOffset, D3D12_PREDICATION_OP operation) const
        {
            SetPredication(buffer.GetInterfacePointer<ID3D12Resource>(), alignedBufferOffset, operation);
        }
        
        /// <summary>
        /// For internal use only. Not intended to be called directly.
        /// </summary>
        /// <param name="metadata">Internal.</param>
        /// <param name="data">Internal.</param>
        /// <param name="dataSize">Internal.</param>
        void SetMarker(UINT metadata, const void* data, UINT dataSize) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetMarker(metadata, data, dataSize);
        }
        
        /// <summary>
        /// For internal use only. Not intended to be called directly.
        /// </summary>
        /// <param name="metadata">Internal.</param>
        /// <param name="data">Internal.</param>
        /// <param name="dataSize">Internal.</param>
        void BeginEvent(UINT metadata, const void* data, UINT dataSize) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->BeginEvent(metadata, data, dataSize);
        }

        /// <summary>
        /// For internal use only. Not intended to be called directly.
        /// </summary>
        void EndEvent() const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->EndEvent();
        }

        
        /// <summary>
        /// Records a video processing operation to the command list, operating on 
        /// one or more input samples and writing the result to an output surface.
        /// </summary>
        /// <param name="videoProcessor">
        /// A pointer to an ID3D12VideoProcessor interface representing a video processor instance.
        /// </param>
        /// <param name="outputArguments">
        /// A D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS structure specifying the output surface 
        /// and output arguments.
        /// </param>
        /// <param name="numberOfInputStreams">
        /// The count of input streams.
        /// </param>
        /// <param name="inputArguments">
        /// A pointer to an array of D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS structures specifying 
        /// the input parameters.
        /// </param>
        void ProcessFrames( ID3D12VideoProcessor* videoProcessor, const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS* outputArguments, UINT numberOfInputStreams, const D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS* inputArguments) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ProcessFrames(videoProcessor, outputArguments, numberOfInputStreams, inputArguments);
        }
        void ProcessFrames(const D3D12VideoProcessor& videoProcessor, const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS* outputArguments, UINT numberOfInputStreams, const D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS* inputArguments) const
        {
            ProcessFrames(videoProcessor.GetInterfacePointer<ID3D12VideoProcessor>(), outputArguments, numberOfInputStreams, inputArguments);
        }

        /// <summary>
        /// Writes a number of 32-bit immediate values to the specified buffer locations directly 
        /// from the command stream.
        /// </summary>
        /// <param name="count">
        /// The number of elements in the params and modes arrays.
        /// </param>
        /// <param name="params">
        /// The address of an array of D3D12_WRITEBUFFERIMMEDIATE_PARAMETER structures of size count.
        /// </param>
        /// <param name="modes">
        /// The address of an array of D3D12_WRITEBUFFERIMMEDIATE_MODE structures of size Count. The 
        /// default value is nullptr. Passing nullptr causes the system to write all immediate values 
        /// using D3D12_WRITEBUFFERIMMEDIATE_MODE_DEFAULT.
        /// </param>
        void WriteBufferImmediate( UINT count, const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER* params, const D3D12_WRITEBUFFERIMMEDIATE_MODE* modes = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->WriteBufferImmediate(count, params, modes);
        }
        
    };

    using ProcessCommandList = D3D12VideoProcessCommandList;


    /// <summary>
    /// Encapsulates a list of graphics commands for video decoding. This class inherits from D3D12VideoDecodeCommandList 
    /// and adds support for video decode histograms.
    /// </summary>
    class D3D12VideoDecodeCommandList1 : public D3D12VideoDecodeCommandList
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoDecodeCommandList1, D3D12VideoDecodeCommandList, ID3D12VideoDecodeCommandList1, ID3D12VideoDecodeCommandList)
    public:
        /// <summary>
        /// Records a decode frame operation to the command list. Inputs, outputs, and parameters 
        /// for the decode are specified as arguments to this method. Takes a 
        /// D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS1 structure to support video decode histograms.
        /// </summary>
        /// <param name="decoder">
        /// A pointer to an ID3D12VideoDecoder interface representing a decoder instance.
        /// </param>
        /// <param name="outputArguments">
        /// A D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS1 structure specifying the output surface 
        /// and output arguments.
        /// </param>
        /// <param name="inputArguments">
        /// A D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS structure specifying the input bitstream, 
        /// reference frames, and other input parameters.
        /// </param>
        void DecodeFrame1( ID3D12VideoDecoder* decoder, const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS1* outputArguments, const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS* inputArguments) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DecodeFrame1(decoder, outputArguments, inputArguments);
        }
        void DecodeFrame1(const D3D12VideoDecoder& decoder, const D3D12_VIDEO_DECODE_OUTPUT_STREAM_ARGUMENTS1* outputArguments, const D3D12_VIDEO_DECODE_INPUT_STREAM_ARGUMENTS* inputArguments) const
        {
            DecodeFrame1(decoder.GetInterfacePointer<ID3D12VideoDecoder>(), outputArguments, inputArguments);
        }
    };


    /// <summary>
    /// Encapsulates a list of graphics commands for video processing. Adds the ProcessFrames1 method 
    /// which supports changing the D3D12_VIDEO_FIELD_TYPE for each call, unlike D3D12VideoProcessCommandList::ProcessFrames.
    /// </summary>
    class D3D12VideoProcessCommandList1 : public D3D12VideoProcessCommandList
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoProcessCommandList1, D3D12VideoProcessCommandList, ID3D12VideoProcessCommandList1, ID3D12VideoProcessCommandList)
    public:
        /// <summary>
        /// Records a video processing operation to the command list, operating on one 
        /// or more input samples and writing the result to an output surface. This 
        /// version of the method supports changing the D3D12_VIDEO_FIELD_TYPE for 
        /// each call, unlike D3D12VideoProcessCommandList::ProcessFrames.
        /// </summary>
        /// <param name="videoProcessor"></param>
        /// <param name="outputArguments"></param>
        /// <param name="numberOfInputStreams"></param>
        /// <param name="inputArguments"></param>
        void ProcessFrames1( ID3D12VideoProcessor* videoProcessor, const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS* outputArguments, UINT numberOfInputStreams, const D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS1* inputArguments) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ProcessFrames1(videoProcessor, outputArguments, numberOfInputStreams, inputArguments);
        }
        void ProcessFrames1(const D3D12VideoProcessor& videoProcessor, const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_ARGUMENTS* outputArguments, UINT numberOfInputStreams, const D3D12_VIDEO_PROCESS_INPUT_STREAM_ARGUMENTS1* inputArguments) const
        {
            ProcessFrames1(videoProcessor.GetInterfacePointer<ID3D12VideoProcessor>(), outputArguments, numberOfInputStreams, inputArguments);
        }
    };


    /// <summary>
    /// This interface maintains context for video motion estimation operations.
    /// </summary>
    class D3D12VideoMotionEstimator : public D3D12Pageable
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoMotionEstimator, D3D12Pageable, ID3D12VideoMotionEstimator, ID3D12Pageable)
    public:
        /// <summary>
        /// Gets the D3D12_VIDEO_MOTION_ESTIMATOR_DESC structure that was 
        /// passed into D3D12VideoDevice1::CreateVideoMotionEstimator when 
        /// the D3D12VideoMotionEstimator was created.
        /// </summary>
        /// <returns></returns>
        D3D12_VIDEO_MOTION_ESTIMATOR_DESC GetDesc() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetDesc();
        }


        /// <summary>
        /// Gets the ID3D12ProtectedResourceSession that was passed into 
        /// D3D12VideoDevice1::CreateVideoMotionEstimator when the 
        /// D3D12VideoMotionEstimator was created.
        /// </summary>
        /// <param name="riid">
        /// The globally unique identifier (GUID) for the ID3D12ProtectedResourceSession interface.
        /// </param>
        /// <param name="protectedSession">
        /// Receives a void pointer representing the ID3D12ProtectedResourceSession interface.
        /// </param>
        void GetProtectedResourceSession(REFIID riid, void** protectedSession) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->GetProtectedResourceSession(riid, protectedSession);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        D3D12ProtectedResourceSession GetProtectedResourceSession() const
        {
            ID3D12ProtectedResourceSession* itf = nullptr;
            GetProtectedResourceSession(__uuidof(ID3D12ProtectedResourceSession), (void**)&itf);
            return D3D12ProtectedResourceSession(itf);
        }

    };

    /// <summary>
    /// Represents the storage of the motion vector output of a motion estimation 
    /// operation in an IHV-dependent layout. Call D3D12VideoEncodeCommandList::EstimateMotion 
    /// to calculate and store motion vectors. Use D3D12VideoEncodeCommandList::ResolveMotionVectorHeap 
    /// to copy and translate these results into the API-defined layout in a Texture 2D.
    /// </summary>
    class D3D12VideoMotionVectorHeap : public D3D12Pageable
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoMotionVectorHeap, D3D12Pageable, ID3D12VideoMotionVectorHeap, ID3D12Pageable)
    public:

        /// <summary>
        /// Gets the D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC structure that was passed into 
        /// D3D12VideoDevice1::CreateVideoMotionEstimatorHeap when the ID3D12VideoMotionEstimatorHeap was created.
        /// </summary>
        /// <returns>
        /// D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC
        /// </returns>
        D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC GetDesc() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetDesc();
        }

        /// <summary>
        /// Gets the ID3D12ProtectedResourceSession that was passed into 
        /// D3D12VideoDevice1::CreateVideoMotionEstimatorHeap when the 
        /// ID3D12VideoMotionEstimatorHeap was created.
        /// </summary>
        /// <param name="riid"></param>
        /// <param name="protectedSession"></param>
        void GetProtectedResourceSession(REFIID riid, void** protectedSession) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->GetProtectedResourceSession(riid, protectedSession);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        D3D12ProtectedResourceSession GetProtectedResourceSession() const
        {
            ID3D12ProtectedResourceSession* itf = nullptr;
            GetProtectedResourceSession(__uuidof(ID3D12ProtectedResourceSession), (void**)&itf);
            return D3D12ProtectedResourceSession(itf);
        }
    };


    /// <summary>
    /// Provides video decoding and processing capabilities of a Microsoft Direct3D 
    /// 12 device including the ability to query video capabilities and instantiating 
    /// video decoders and processors. This interface adds support for motion estimation.
    /// </summary>
    class D3D12VideoDevice1 : public D3D12VideoDevice
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoDevice1, D3D12VideoDevice, ID3D12VideoDevice1, ID3D12VideoDevice)
    public:
        /// <summary>
        /// Creates an ID3D12VideoMotionEstimator, which maintains context for video motion estimation operations.
        /// </summary>
        /// <param name="VideoMotionEstimatorDesc">
        /// A D3D12_VIDEO_MOTION_ESTIMATOR_DESC describing the parameters used for motion estimation. This structure 
        /// contains both input and output fields.
        /// </param>
        /// <param name="protectedResourceSession">
        /// A ID3D12ProtectedResourceSession for managing access to protected resources.
        /// </param>
        /// <param name="riid">
        /// The globally unique identifier (GUID) for the ID3D12VideoMotionEstimator interface.
        /// </param>
        /// <param name="videoMotionEstimator">
        /// A pointer to a memory block that receives a pointer to the ID3D12VideoMotionEstimator interface.
        /// </param>
        void CreateVideoMotionEstimator(const D3D12_VIDEO_MOTION_ESTIMATOR_DESC* VideoMotionEstimatorDesc, ID3D12ProtectedResourceSession* protectedResourceSession, REFIID riid, void** videoMotionEstimator) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->CreateVideoMotionEstimator(VideoMotionEstimatorDesc, protectedResourceSession, riid, videoMotionEstimator);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        D3D12VideoMotionEstimator CreateVideoMotionEstimator(const D3D12_VIDEO_MOTION_ESTIMATOR_DESC* VideoMotionEstimatorDesc, ID3D12ProtectedResourceSession* protectedResourceSession = nullptr)
        {
            ID3D12VideoMotionEstimator* itf = nullptr;
            CreateVideoMotionEstimator(VideoMotionEstimatorDesc, protectedResourceSession, __uuidof(ID3D12VideoMotionEstimator), (void**)&itf);
            return D3D12VideoMotionEstimator(itf);
        }
        D3D12VideoMotionEstimator CreateVideoMotionEstimator(const D3D12_VIDEO_MOTION_ESTIMATOR_DESC* VideoMotionEstimatorDesc, const D3D12ProtectedResourceSession& protectedResourceSession )
        {
            return CreateVideoMotionEstimator(VideoMotionEstimatorDesc, protectedResourceSession.GetInterfacePointer<ID3D12ProtectedResourceSession>());
        }


        /// <summary>
        /// Allocates heap that contains motion vectors for video motion estimation.
        /// </summary>
        /// <param name="videoMotionVectorHeapDesc">
        /// A pointer to a D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC describing the format of the heap. 
        /// This structure contains both input and output fields.
        /// </param>
        /// <param name="protectedResourceSession">
        /// A ID3D12ProtectedResourceSession for managing access to protected resources.
        /// </param>
        /// <param name="riid">
        /// The globally unique identifier (GUID) for the ID3D12VideoMotionVectorHeap interface.
        /// </param>
        /// <param name="videoMotionVectorHeap">
        /// A pointer to a memory block that receives a pointer to the ID3D12VideoMotionVectorHeap interface.
        /// </param>
        void CreateVideoMotionVectorHeap(const D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC* videoMotionVectorHeapDesc, ID3D12ProtectedResourceSession* protectedResourceSession, REFIID riid, void** videoMotionVectorHeap) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->CreateVideoMotionVectorHeap(videoMotionVectorHeapDesc, protectedResourceSession, riid, videoMotionVectorHeap);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        D3D12VideoMotionVectorHeap CreateVideoMotionVectorHeap(const D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC* videoMotionVectorHeapDesc, ID3D12ProtectedResourceSession* protectedResourceSession = nullptr)
        {
            ID3D12VideoMotionVectorHeap* itf = nullptr;
            CreateVideoMotionVectorHeap(videoMotionVectorHeapDesc, protectedResourceSession, __uuidof(ID3D12VideoMotionVectorHeap), (void**)&itf);
            return D3D12VideoMotionVectorHeap(itf);
        }

        D3D12VideoMotionVectorHeap CreateVideoMotionVectorHeap(const D3D12_VIDEO_MOTION_VECTOR_HEAP_DESC* videoMotionVectorHeapDesc, const D3D12ProtectedResourceSession& protectedResourceSession)
        {
            return CreateVideoMotionVectorHeap(videoMotionVectorHeapDesc, protectedResourceSession.GetInterfacePointer<ID3D12ProtectedResourceSession>());
        }

    };


    /// <summary>
    /// Encapsulates a list of graphics commands for video encoding, including motion estimation.
    /// </summary>
    class D3D12VideoEncodeCommandList : public D3D12CommandList
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoEncodeCommandList, D3D12CommandList, ID3D12VideoEncodeCommandList, ID3D12CommandList)
    public:
        /// <summary>
        /// Indicates that recording to the command list has finished.
        /// </summary>
        void Close() const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->Close();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        /// <summary>
        /// Resets a command list back to its initial state as if a new command list was just created.
        /// </summary>
        /// <param name="allocator">
        /// A pointer to the ID3D12CommandAllocator object that the device creates command lists from.
        /// </param>
        void Reset(ID3D12CommandAllocator* allocator) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->Reset(allocator);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void Reset(const D3D12CommandAllocator& allocator) const
        {
            Reset(allocator.GetInterfacePointer<ID3D12CommandAllocator>());
        }

        /// <summary>
        /// Resets the state of a direct command list back to the state it was in when the command list was created.
        /// </summary>
        void ClearState() const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ClearState();
        }

        /// <summary>
        /// Notifies the driver that it needs to synchronize multiple accesses to resources.
        /// </summary>
        /// <param name="numberOfBarriers">
        /// The number of submitted barrier descriptions.
        /// </param>
        /// <param name="barriers">
        /// Pointer to an array of barrier descriptions.
        /// </param>
        void ResourceBarrier(UINT numberOfBarriers, const D3D12_RESOURCE_BARRIER* barriers) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ResourceBarrier(numberOfBarriers, barriers);
        }

        /// <summary>
        /// Indicate that the current contents of a resource can be discarded. The current contents 
        /// of the resource are no longer valid allowing optimizations for subsequent operations 
        /// such as ResourceBarrier.
        /// </summary>
        /// <param name="resource"></param>
        /// <param name="region"></param>
        void DiscardResource(ID3D12Resource* resource, const D3D12_DISCARD_REGION* region = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->DiscardResource(resource, region);
        }
        void DiscardResource(const D3D12Resource& resource, const D3D12_DISCARD_REGION* region = nullptr) const
        {
            DiscardResource(resource.GetInterfacePointer<ID3D12Resource>(), region);
        }

        
        /// <summary>
        /// Starts a query running.
        /// </summary>
        /// <param name="queryHeap">
        /// A pointer to an ID3D12QueryHeap specifying the storage for this query.
        /// </param>
        /// <param name="queryType">
        /// A member of the D3D12_QUERY_TYPE enumeration specifying the type of the query.
        /// </param>
        /// <param name="index">
        /// The index of the query within the query heap.
        /// </param>
        void BeginQuery(ID3D12QueryHeap* queryHeap, D3D12_QUERY_TYPE queryType, UINT index) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->BeginQuery(queryHeap, queryType, index);
        }
        void BeginQuery(const D3D12QueryHeap& queryHeap, D3D12_QUERY_TYPE queryType, UINT index) const
        {
            BeginQuery(queryHeap.GetInterfacePointer<ID3D12QueryHeap>(), queryType, index);
        }

        /// <summary>
        /// Ends a query.
        /// </summary>
        /// <param name="queryHeap">
        /// A pointer to an ID3D12QueryHeap specifying the storage for this query.
        /// </param>
        /// <param name="queryType">
        /// A member of the D3D12_QUERY_TYPE enumeration specifying the type of the query.
        /// </param>
        /// <param name="index">
        /// The index of the query within the query heap.
        /// </param>
        void EndQuery(ID3D12QueryHeap* queryHeap, D3D12_QUERY_TYPE queryType, UINT index) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->EndQuery(queryHeap, queryType, index);
        }
        void EndQuery(const D3D12QueryHeap& queryHeap, D3D12_QUERY_TYPE queryType, UINT index) const
        {
            EndQuery(queryHeap.GetInterfacePointer<ID3D12QueryHeap>(), queryType, index);
        }

        /// <summary>
        /// Extracts data from a query.
        /// </summary>
        /// <param name="queryHeap">
        /// A pointer to an ID3D12QueryHeap specifying the storage containing the queries to resolve.
        /// </param>
        /// <param name="queryType">
        /// A member of the D3D12_QUERY_TYPE enumeration specifying the type of the query.
        /// </param>
        /// <param name="startIndex">
        /// The index of the first query to resolve.
        /// </param>
        /// <param name="numberOfQueries">
        /// The number of queries to resolve.
        /// </param>
        /// <param name="destinationBuffer">
        /// A pointer to an ID3D12Resource representing the destination buffer. The resource must be 
        /// in the state D3D12_RESOURCE_STATE_COPY_DEST.
        /// </param>
        /// <param name="alignedDestinationBufferOffset">
        /// The alignment offset into the destination buffer. This must be a multiple of 8 bytes.
        /// </param>
        void ResolveQueryData(ID3D12QueryHeap* queryHeap, D3D12_QUERY_TYPE queryType, UINT startIndex, UINT numberOfQueries, ID3D12Resource* destinationBuffer, UINT64 alignedDestinationBufferOffset) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ResolveQueryData(queryHeap, queryType, startIndex, numberOfQueries, destinationBuffer, alignedDestinationBufferOffset);
        }
        void ResolveQueryData(const D3D12QueryHeap& queryHeap, D3D12_QUERY_TYPE queryType, UINT startIndex, UINT numberOfQueries, const D3D12Resource& destinationBuffer, UINT64 alignedDestinationBufferOffset) const
        {
            ResolveQueryData(queryHeap.GetInterfacePointer<ID3D12QueryHeap>(), queryType, startIndex, numberOfQueries, destinationBuffer.GetInterfacePointer<ID3D12Resource>(), alignedDestinationBufferOffset);
        }

        /// <summary>
        /// Specifies that subsequent commands should not be performed if the predicate value passes 
        /// the specified operation.
        /// </summary>
        /// <param name="buffer">
        /// A pointer to an ID3D12Resource representing the buffer from which to read the 64-bit predication value.
        /// </param>
        /// <param name="alignedBufferOffset">
        /// The UINT64-aligned buffer offset.
        /// </param>
        /// <param name="operation">
        /// A member of the D3D12_PREDICATION_OP enumeration specifying the predicate operation.
        /// </param>
        void SetPredication(ID3D12Resource* buffer, UINT64 alignedBufferOffset, D3D12_PREDICATION_OP operation) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetPredication(buffer, alignedBufferOffset, operation);
        }
        void SetPredication(const D3D12Resource& buffer, UINT64 alignedBufferOffset, D3D12_PREDICATION_OP operation) const
        {
            SetPredication(buffer.GetInterfacePointer<ID3D12Resource>(), alignedBufferOffset, operation);
        }

        /// <summary>
        /// For internal use only. Not intended to be called directly.
        /// </summary>
        /// <param name="metadata">
        /// Internal.
        /// </param>
        /// <param name="data">
        /// Internal.
        /// </param>
        /// <param name="dataSize">
        /// Internal.
        /// </param>
        void SetMarker(UINT metadata, const void* data, UINT dataSize) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetMarker(metadata, data, dataSize);
        }

        /// <summary>
        /// For internal use only. Not intended to be called directly.
        /// </summary>
        /// <param name="metadata">
        /// Internal.
        /// </param>
        /// <param name="data">
        /// Internal.
        /// </param>
        /// <param name="dataSize">
        /// Internal.
        /// </param>
        void BeginEvent(UINT metadata, const void* data, UINT dataSize) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->BeginEvent(metadata, data, dataSize);
        }

        /// <summary>
        /// For internal use only. Not intended to be called directly.
        /// </summary>
        void EndEvent() const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->EndEvent();
        }


        /// <summary>
        /// Performs the motion estimation operation.
        /// </summary>
        /// <param name="motionEstimator">
        /// An ID3D12VideoMotionEstimator representing the video motion estimator context object.
        /// </param>
        /// <param name="outputArguments">
        /// A D3D12_VIDEO_MOTION_ESTIMATOR_OUTPUT structure representing the video motion estimation output arguments.
        /// </param>
        /// <param name="inputArguments">
        /// A D3D12_VIDEO_MOTION_ESTIMATOR_INPUT structure representing the video motion estimation input arguments.
        /// </param>
        void EstimateMotion(ID3D12VideoMotionEstimator* motionEstimator, const D3D12_VIDEO_MOTION_ESTIMATOR_OUTPUT* outputArguments, const D3D12_VIDEO_MOTION_ESTIMATOR_INPUT* inputArguments) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->EstimateMotion(motionEstimator, outputArguments, inputArguments);
        }
        void EstimateMotion(const D3D12VideoMotionEstimator& motionEstimator, const D3D12_VIDEO_MOTION_ESTIMATOR_OUTPUT* outputArguments, const D3D12_VIDEO_MOTION_ESTIMATOR_INPUT* inputArguments) const
        {
            EstimateMotion(motionEstimator.GetInterfacePointer<ID3D12VideoMotionEstimator>(), outputArguments, inputArguments);
        }

        /// <summary>
        /// Translates the motion vector output of the EstimateMotion method from hardware-dependent 
        /// formats into a consistent format defined by the video motion estimation APIs.
        /// </summary>
        /// <param name="outputArguments">
        /// A D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_OUTPUT structure containing the translated motion 
        /// vectors.
        /// </param>
        /// <param name="inputArguments">
        /// A D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_INPUT structure containing the motion vectors to 
        /// translate.
        /// </param>
        void ResolveMotionVectorHeap(const D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_OUTPUT* outputArguments, const D3D12_RESOLVE_VIDEO_MOTION_VECTOR_HEAP_INPUT* inputArguments) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ResolveMotionVectorHeap(outputArguments, inputArguments);
        }

        /// <summary>
        /// Writes a number of 32-bit immediate values to the specified buffer locations directly from the command stream.
        /// </summary>
        /// <param name="count">
        /// The number of elements in the params and modes arrays.
        /// </param>
        /// <param name="params">
        /// The address of an array of D3D12_WRITEBUFFERIMMEDIATE_PARAMETER structures of size Count.
        /// </param>
        /// <param name="modes">
        /// The address of an array of D3D12_WRITEBUFFERIMMEDIATE_MODE structures of size count. The 
        /// default value is nullptr. Passing nullptr causes the system to write all immediate values 
        /// using D3D12_WRITEBUFFERIMMEDIATE_MODE_DEFAULT.
        /// </param>
        void WriteBufferImmediate( UINT count, const D3D12_WRITEBUFFERIMMEDIATE_PARAMETER* params, const D3D12_WRITEBUFFERIMMEDIATE_MODE* modes = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->WriteBufferImmediate(count, params, modes );
        }

        /// <summary>
        /// Specifies whether or not protected resources can be accessed by subsequent commands in 
        /// the command list. By default, no protected resources are enabled. After calling 
        /// SetProtectedResourceSession with a valid session, protected resources of the same 
        /// type can refer to that session. After calling SetProtectedResourceSession with nullptr, 
        /// no protected resources can be accessed.
        /// </summary>
        /// <param name="protectedResourceSession"></param>
        void SetProtectedResourceSession(ID3D12ProtectedResourceSession* protectedResourceSession) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetProtectedResourceSession(protectedResourceSession);
        }
        void SetProtectedResourceSession(const D3D12ProtectedResourceSession& protectedResourceSession) const
        {
            SetProtectedResourceSession(protectedResourceSession.GetInterfacePointer<ID3D12ProtectedResourceSession>());
        }

    };

    /// <summary>
    /// Represents a Direct3D 12 video decoder that contains resolution-independent resources 
    /// and state for performing the decode operation. Inherits from D3D12VideoDecoder and 
    /// adds support for protected resources.
    /// </summary>
    class D3D12VideoDecoder1 : public D3D12VideoDecoder
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoDecoder1, D3D12VideoDecoder, ID3D12VideoDecoder1, ID3D12VideoDecoder)
    public:
        /// <summary>
        /// Gets the ID3D12ProtectedResourceSession that was passed into D3D12VideoDevice2::CreateVideoDecoder1 
        /// when the D3D12VideoDecoder1 was created.
        /// </summary>
        /// <param name="riid">
        /// The globally unique identifier (GUID) for the ID3D12ProtectedResourceSession interface.
        /// </param>
        /// <param name="protectedSession">
        /// Receives a void pointer representing the ID3D12ProtectedResourceSession interface.
        /// </param>
        void GetProtectedResourceSession(REFIID riid, void** protectedSession) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->GetProtectedResourceSession(riid, protectedSession);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        D3D12ProtectedResourceSession GetProtectedResourceSession() const
        {
            ID3D12ProtectedResourceSession* itf = nullptr;
            GetProtectedResourceSession(__uuidof(ID3D12ProtectedResourceSession), (void**)&itf);
            return D3D12ProtectedResourceSession(itf);
        }
    };

    /// <summary>
    /// Represents a Direct3D 12 video decoder heap that contains resolution-dependent resources 
    /// and state for performing the decode operation. Inherits from D3D12VideoDecoderHeap and 
    /// adds support for protected resources.
    /// </summary>
    class D3D12VideoDecoderHeap1 : public D3D12VideoDecoderHeap
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoDecoderHeap1, D3D12VideoDecoderHeap, ID3D12VideoDecoderHeap1, ID3D12VideoDecoderHeap)
    public:
        void GetProtectedResourceSession(REFIID riid, void** protectedSession) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->GetProtectedResourceSession(riid, protectedSession);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        D3D12ProtectedResourceSession GetProtectedResourceSession() const
        {
            ID3D12ProtectedResourceSession* itf = nullptr;
            GetProtectedResourceSession(__uuidof(ID3D12ProtectedResourceSession), (void**)&itf);
            return D3D12ProtectedResourceSession(itf);
        }
    };


    /// <summary>
    /// Provides methods for getting information about the parameters to the call to 
    /// D3D12VideoDevice2::CreateVideoProcessor1 that created the video processor.
    /// </summary>
    class D3D12VideoProcessor1 : public D3D12VideoProcessor
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoProcessor1, D3D12VideoProcessor, ID3D12VideoProcessor1, ID3D12VideoProcessor)
    public:
        /// <summary>
        /// Gets the ID3D12ProtectedResourceSession that was passed into D3D12VideoDevice2::CreateVideoProcessor1 
        /// when the ID3D12VideoProcessor1 was created.
        /// </summary>
        /// <param name="riid">
        /// The globally unique identifier (GUID) for the ID3D12ProtectedResourceSession interface.
        /// </param>
        /// <param name="protectedSession">
        /// Receives a void pointer representing the ID3D12ProtectedResourceSession interface.
        /// </param>
        void GetProtectedResourceSession(REFIID riid, void** protectedSession) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->GetProtectedResourceSession(riid, protectedSession);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        D3D12ProtectedResourceSession GetProtectedResourceSession() const
        {
            ID3D12ProtectedResourceSession* itf = nullptr;
            GetProtectedResourceSession(__uuidof(ID3D12ProtectedResourceSession), (void**)&itf);
            return D3D12ProtectedResourceSession(itf);
        }
    };


    /// <summary>
    /// Represents a video extension command.
    /// </summary>
    class D3D12VideoExtensionCommand : public D3D12Pageable
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoExtensionCommand, D3D12Pageable, ID3D12VideoExtensionCommand, ID3D12Pageable)
    public:
        /// <summary>
        /// Gets the D3D12_VIDEO_EXTENSION_COMMAND_DESC provided when the interface was created.
        /// </summary>
        /// <returns>
        /// D3D12_VIDEO_EXTENSION_COMMAND_DESC
        /// </returns>
        D3D12_VIDEO_EXTENSION_COMMAND_DESC GetDesc() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetDesc();
        }

        /// <summary>
        /// Gets the ID3D12ProtectedResourceSession that was passed into D3D12VideoDevice2::CreateVideoExtensionCommand 
        /// when the ID3D12VideoExtensionCommand was created.
        /// </summary>
        /// <param name="riid">
        /// The globally unique identifier (GUID) for the ID3D12ProtectedResourceSession interface.
        /// </param>
        /// <param name="protectedSession">
        /// Receives a void pointer representing the ID3D12ProtectedResourceSession interface.
        /// </param>
        void GetProtectedResourceSession(REFIID riid, void** protectedSession) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->GetProtectedResourceSession(riid, protectedSession);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        D3D12ProtectedResourceSession GetProtectedResourceSession() const
        {
            ID3D12ProtectedResourceSession* itf = nullptr;
            GetProtectedResourceSession(__uuidof(ID3D12ProtectedResourceSession), (void**)&itf);
            return D3D12ProtectedResourceSession(itf);
        }
    };

    /// <summary>
    /// Provides video decoding and processing capabilities of a Microsoft Direct3D 12 
    /// device including the ability to query video capabilities and instantiating video 
    /// decoders and processors. This class adds support for protected resources and video 
    /// extension commands.
    /// </summary>
    class D3D12VideoDevice2 : public D3D12VideoDevice1
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoDevice2, D3D12VideoDevice1, ID3D12VideoDevice2, ID3D12VideoDevice1)
    public:
        /// <summary>
        /// Creates a video decoder instance that contains the resolution-independent 
        /// driver resources and state, with support for protected resources.
        /// </summary>
        /// <param name="videoDecoderDesc">
        /// A pointer to a D3D12_VIDEO_DECODER_DESC structure describing the decode 
        /// profile and bitstream encryption for the decoder.
        /// </param>
        /// <param name="protectedResourceSession">
        /// A ID3D12ProtectedResourceSession for managing access to protected resources.
        /// </param>
        /// <param name="riid">
        /// The globally unique identifier (GUID) for the decode video state interface.
        /// </param>
        /// <param name="videoDecoder">
        /// A pointer to a memory block that receives a pointer to the ID3D12VideoDecoder1 interface.
        /// </param>
        void CreateVideoDecoder1( const D3D12_VIDEO_DECODER_DESC* videoDecoderDesc, ID3D12ProtectedResourceSession* protectedResourceSession, REFIID riid, void** videoDecoder) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->CreateVideoDecoder1(videoDecoderDesc, protectedResourceSession, riid, videoDecoder);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        D3D12VideoDecoder1 CreateVideoDecoder1(const D3D12_VIDEO_DECODER_DESC* videoDecoderDesc, ID3D12ProtectedResourceSession* protectedResourceSession = nullptr) const
        {
            ID3D12VideoDecoder1* itf = nullptr;
            CreateVideoDecoder1(videoDecoderDesc, protectedResourceSession, __uuidof(ID3D12VideoDecoder1), (void**)&itf);
            return D3D12VideoDecoder1(itf);
        }
        D3D12VideoDecoder1 CreateVideoDecoder1(const D3D12_VIDEO_DECODER_DESC* videoDecoderDesc, const D3D12ProtectedResourceSession& protectedResourceSession) const
        {
            return CreateVideoDecoder1(videoDecoderDesc, protectedResourceSession.GetInterfacePointer<ID3D12ProtectedResourceSession>());
        }


        /// <summary>
        /// Allocates a video decoder heap that contains the resolution-dependent driver resources 
        /// and state, with support for protected resources.
        /// </summary>
        /// <param name="videoDecoderHeapDesc">
        /// A pointer to a D3D12_VIDEO_DECODER_HEAP_DESC describing the decoding configuration.
        /// </param>
        /// <param name="protectedResourceSession">
        /// A ID3D12ProtectedResourceSession for managing access to protected resources.
        /// </param>
        /// <param name="riid">
        /// The globally unique identifier (GUID) for the decode video state interface.
        /// </param>
        /// <param name="videoDecoderHeap">
        /// A pointer to a memory block that receives a pointer to the ID3D12VideoDecoderHeap1 interface.
        /// </param>
        void CreateVideoDecoderHeap1( const D3D12_VIDEO_DECODER_HEAP_DESC* videoDecoderHeapDesc, ID3D12ProtectedResourceSession* protectedResourceSession, REFIID riid, void** videoDecoderHeap) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->CreateVideoDecoderHeap1(videoDecoderHeapDesc, protectedResourceSession, riid, videoDecoderHeap);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        D3D12VideoDecoderHeap1 CreateVideoDecoderHeap1(const D3D12_VIDEO_DECODER_HEAP_DESC* videoDecoderHeapDesc, ID3D12ProtectedResourceSession* protectedResourceSession = nullptr) const
        {
            ID3D12VideoDecoderHeap1* itf = nullptr;
            CreateVideoDecoderHeap1(videoDecoderHeapDesc, protectedResourceSession, __uuidof(ID3D12VideoDecoderHeap1), (void**)&itf);
            return D3D12VideoDecoderHeap1(itf);
        }
        D3D12VideoDecoderHeap1 CreateVideoDecoderHeap1(const D3D12_VIDEO_DECODER_HEAP_DESC* videoDecoderHeapDesc, const D3D12ProtectedResourceSession& protectedResourceSession) const
        {
            return CreateVideoDecoderHeap1(videoDecoderHeapDesc, protectedResourceSession.GetInterfacePointer<ID3D12ProtectedResourceSession>());
        }

        /// <summary>
        /// Creates a video processor instance with support for protected resources.
        /// </summary>
        /// <param name="nodeMask">
        /// The node mask specifying the physical adapter on which the video processor 
        /// will be used. For single GPU operation, set this to zero. If there are multiple 
        /// GPU nodes, set a bit to identify the node, i.e. the device's physical adapter, 
        /// to which the command queue applies. Each bit in the mask corresponds to a single 
        /// node. Only 1 bit may be set.
        /// </param>
        /// <param name="outputStreamDesc">
        /// A pointer to a D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC structure describing 
        /// the output stream.
        /// </param>
        /// <param name="numberOfInputStreamDescs">
        /// The number of input streams provided in the inputStreamDescs parameter.
        /// </param>
        /// <param name="inputStreamDescs">
        /// A pointer to a list of D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC structures the 
        /// input streams. The number of structures provided should match the value specified 
        /// in the numberOfInputStreamDescs parameter.
        /// </param>
        /// <param name="protectedResourceSession">
        /// A ID3D12ProtectedResourceSession for managing access to protected resources.
        /// </param>
        /// <param name="riid">
        /// The globally unique identifier (GUID) for the video processor interface.
        /// </param>
        /// <param name="videoProcessor">
        /// A pointer to a memory block that receives a pointer to the ID3D12VideoProcessor1 
        /// interface
        /// </param>
        void CreateVideoProcessor1(UINT nodeMask, const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC* outputStreamDesc, UINT numberOfInputStreamDescs, const D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC* inputStreamDescs, ID3D12ProtectedResourceSession* protectedResourceSession, REFIID riid, void** videoProcessor) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->CreateVideoProcessor1(nodeMask, outputStreamDesc, numberOfInputStreamDescs, inputStreamDescs, protectedResourceSession, riid, videoProcessor);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        D3D12VideoProcessor1 CreateVideoProcessor1(UINT nodeMask, const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC* outputStreamDesc, UINT numberOfInputStreamDescs, const D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC* inputStreamDescs, ID3D12ProtectedResourceSession* protectedResourceSession = nullptr) const
        {
            ID3D12VideoProcessor1* itf = nullptr;
            CreateVideoProcessor1(nodeMask, outputStreamDesc, numberOfInputStreamDescs, inputStreamDescs, protectedResourceSession, __uuidof(ID3D12VideoProcessor1), (void**)&itf);
        }
        D3D12VideoProcessor1 CreateVideoProcessor1(UINT nodeMask, const D3D12_VIDEO_PROCESS_OUTPUT_STREAM_DESC* outputStreamDesc, UINT numberOfInputStreamDescs, const D3D12_VIDEO_PROCESS_INPUT_STREAM_DESC* inputStreamDescs, const D3D12ProtectedResourceSession& protectedResourceSession) const
        {
            return CreateVideoProcessor1(nodeMask, outputStreamDesc, numberOfInputStreamDescs, inputStreamDescs, protectedResourceSession.GetInterfacePointer<ID3D12ProtectedResourceSession>());
        }

        /// <summary>
        /// Creates a video extension command.
        /// </summary>
        /// <param name="videoExtensionCommandDesc">
        /// The D3D12_VIDEO_EXTENSION_COMMAND_DESC describing the command to be created.
        /// </param>
        /// <param name="creationParameters">
        /// A pointer to the creation parameters structure, which is defined by the command. 
        /// The parameters structure must match the parameters enumerated by a call to 
        /// D3D12VideoDevice::CheckFeatureSupport with the feature value of 
        /// D3D12_FEATURE_VIDEO_EXTENSION_COMMAND_PARAMETERS and a parameter stage value 
        /// of D3D12_VIDEO_EXTENSION_COMMAND_PARAMETER_STAGE_CREATION.
        /// </param>
        /// <param name="creationParametersDataSizeInBytes">
        /// The size of the creationParameters parameter structure, in bytes.
        /// </param>
        /// <param name="protectedResourceSession">
        /// A ID3D12ProtectedResourceSession for managing access to protected resources.
        /// </param>
        /// <param name="riid">
        /// The globally unique identifier (GUID) for the ID3D12VideoExtensionCommand interface.
        /// </param>
        /// <param name="videoExtensionCommand">
        /// A pointer to a memory block that receives a pointer to the ID3D12VideoExtensionCommand 
        /// interface.
        /// </param>
        void CreateVideoExtensionCommand( const D3D12_VIDEO_EXTENSION_COMMAND_DESC* videoExtensionCommandDesc, const void* creationParameters, SIZE_T creationParametersDataSizeInBytes, ID3D12ProtectedResourceSession* protectedResourceSession, REFIID riid, void** videoExtensionCommand) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->CreateVideoExtensionCommand(videoExtensionCommandDesc, creationParameters, creationParametersDataSizeInBytes, protectedResourceSession, riid, videoExtensionCommand);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        D3D12VideoExtensionCommand CreateVideoExtensionCommand(const D3D12_VIDEO_EXTENSION_COMMAND_DESC* videoExtensionCommandDesc, const void* creationParameters, SIZE_T creationParametersDataSizeInBytes, ID3D12ProtectedResourceSession* protectedResourceSession = nullptr) const
        {
            ID3D12VideoExtensionCommand* itf = nullptr;
            CreateVideoExtensionCommand(videoExtensionCommandDesc, creationParameters, creationParametersDataSizeInBytes, protectedResourceSession, __uuidof(ID3D12VideoExtensionCommand), (void**)&itf);
            return D3D12VideoExtensionCommand(itf);
        }
        D3D12VideoExtensionCommand CreateVideoExtensionCommand(const D3D12_VIDEO_EXTENSION_COMMAND_DESC* videoExtensionCommandDesc, const void* creationParameters, SIZE_T creationParametersDataSizeInBytes, const D3D12ProtectedResourceSession& protectedResourceSession) const
        {
            return CreateVideoExtensionCommand(videoExtensionCommandDesc, creationParameters, creationParametersDataSizeInBytes, protectedResourceSession.GetInterfacePointer<ID3D12ProtectedResourceSession>());
        }

        /// <summary>
        /// Executes a video extension command.
        /// </summary>
        /// <param name="extensionCommand">
        /// Pointer to an ID3D12VideoExtensionCommand representing the video extension command to 
        /// execute. The caller is responsible for maintaining object lifetime until command 
        /// execution is complete.
        /// </param>
        /// <param name="executionParameters">
        /// A pointer to the execution input parameters structure, which is defined by the command. 
        /// The parameters structure must match the parameters enumerated by a call to 
        /// D3D12VideoDevice::CheckFeatureSupport with the feature value of 
        /// D3D12_FEATURE_VIDEO_EXTENSION_COMMAND_PARAMETERS and a parameter stage value of 
        /// D3D12_VIDEO_EXTENSION_COMMAND_PARAMETER_STAGE_EXECUTION.
        /// </param>
        /// <param name="executionParametersSizeInBytes">
        /// The size of the executionParameters parameter structure, in bytes.
        /// </param>
        /// <param name="outputData">
        /// A pointer to the execution output parameters structure, which is defined by the command.
        /// </param>
        /// <param name="outputDataSizeInBytes">
        /// The size of the output parameters structure
        /// </param>
        void ExecuteExtensionCommand( ID3D12VideoExtensionCommand* extensionCommand, const void* executionParameters, SIZE_T executionParametersSizeInBytes, void* outputData, SIZE_T outputDataSizeInBytes) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->ExecuteExtensionCommand(extensionCommand, executionParameters, executionParametersSizeInBytes, outputData, outputDataSizeInBytes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void ExecuteExtensionCommand(const D3D12VideoExtensionCommand& extensionCommand, const void* executionParameters, SIZE_T executionParametersSizeInBytes, void* outputData, SIZE_T outputDataSizeInBytes) const
        {
            ExecuteExtensionCommand(extensionCommand.GetInterfacePointer<ID3D12VideoExtensionCommand>(), executionParameters, executionParametersSizeInBytes, outputData, outputDataSizeInBytes);
        }
    };

    /// <summary>
    /// Encapsulates a list of graphics commands for video decoding. This class inherits 
    /// from D3D12VideoDecodeCommandList1 and adds support for video extension commands.
    /// </summary>
    class D3D12VideoDecodeCommandList2 : public D3D12VideoDecodeCommandList1
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoDecodeCommandList2, D3D12VideoDecodeCommandList1, ID3D12VideoDecodeCommandList2, ID3D12VideoDecodeCommandList1)
    public:
        /// <summary>
        /// Specifies whether or not protected resources can be accessed by subsequent 
        /// commands in the video decode command list. By default, no protected resources 
        /// are enabled. After calling SetProtectedResourceSession with a valid session, 
        /// protected resources of the same type can refer to that session. After calling 
        /// SetProtectedResourceSession with nullptr, no protected resources can be accessed.
        /// </summary>
        /// <param name="protectedResourceSession">
        /// An optional pointer to an ID3D12ProtectedResourceSession. You can obtain an 
        /// ID3D12ProtectedResourceSession by calling D3D12Device4::CreateProtectedResourceSession.
        /// </param>
        void SetProtectedResourceSession(ID3D12ProtectedResourceSession* protectedResourceSession) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetProtectedResourceSession(protectedResourceSession);
        }
        void SetProtectedResourceSession(const D3D12ProtectedResourceSession& protectedResourceSession) const
        {
            SetProtectedResourceSession(protectedResourceSession.GetInterfacePointer<ID3D12ProtectedResourceSession>());
        }

        /// <summary>
        /// Records a command to initializes or re-initializes a video extension command 
        /// into a video decode command list.
        /// </summary>
        /// <param name="extensionCommand">
        /// Pointer to an ID3D12VideoExtensionCommand representing the video extension 
        /// command to initialize. The caller is responsible for maintaining object 
        /// lifetime until command execution is complete.
        /// </param>
        /// <param name="initializationParameters">
        /// A pointer to the creation parameters structure, which is defined by the command. 
        /// The parameters structure must match the parameters enumerated by a call to 
        /// D3D12VideoDevice::CheckFeatureSupport with the feature value of 
        /// D3D12_FEATURE_VIDEO_EXTENSION_COMMAND_PARAMETERS and a parameter stage value 
        /// of D3D12_VIDEO_EXTENSION_COMMAND_PARAMETER_STAGE_INITIALIZATION.
        /// </param>
        /// <param name="initializationParametersSizeInBytes">
        /// The size of the initializationParameters parameter structure, in bytes.
        /// </param>
        void InitializeExtensionCommand( ID3D12VideoExtensionCommand* extensionCommand, const void* initializationParameters, SIZE_T initializationParametersSizeInBytes ) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->InitializeExtensionCommand(extensionCommand, initializationParameters, initializationParametersSizeInBytes);
        }
        void InitializeExtensionCommand(const D3D12VideoExtensionCommand& extensionCommand, const void* initializationParameters, SIZE_T initializationParametersSizeInBytes) const
        {
            InitializeExtensionCommand(extensionCommand.GetInterfacePointer<ID3D12VideoExtensionCommand>(), initializationParameters, initializationParametersSizeInBytes);
        }

        /// <summary>
        /// Records a command to execute a video extension command into a decode command list.
        /// </summary>
        /// <param name="extensionCommand">
        /// Pointer to an ID3D12VideoExtensionCommand representing the video extension command 
        /// to execute. The caller is responsible for maintaining object lifetime until command 
        /// execution is complete.
        /// </param>
        /// <param name="executionParameters">
        /// A pointer to the execution parameters structure, which is defined by the command. 
        /// The parameters structure must match the parameters enumerated by a call to 
        /// D3D12VideoDevice::CheckFeatureSupport with the feature value of 
        /// D3D12_FEATURE_VIDEO_EXTENSION_COMMAND_PARAMETERS and a parameter stage value 
        /// of D3D12_VIDEO_EXTENSION_COMMAND_PARAMETER_STAGE_EXECUTION.
        /// </param>
        /// <param name="executionParametersSizeInBytes">
        /// The size of the executionParameters parameter structure, in bytes.
        /// </param>
        void ExecuteExtensionCommand( ID3D12VideoExtensionCommand* extensionCommand, const void* executionParameters, SIZE_T executionParametersSizeInBytes) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ExecuteExtensionCommand(extensionCommand, executionParameters, executionParametersSizeInBytes);
        }
        void ExecuteExtensionCommand(const D3D12VideoExtensionCommand& extensionCommand, const void* executionParameters, SIZE_T executionParametersSizeInBytes) const
        {
            ExecuteExtensionCommand(extensionCommand.GetInterfacePointer<ID3D12VideoExtensionCommand>(), executionParameters, executionParametersSizeInBytes);
        }
    };


    /// <summary>
    /// Encapsulates a list of graphics commands for video processing. This class inherits 
    /// from D3D12VideoProcessCommandList1 and adds support for video extension commands.
    /// </summary>
    class D3D12VideoProcessCommandList2 : public D3D12VideoProcessCommandList1
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoProcessCommandList2, D3D12VideoProcessCommandList1, ID3D12VideoProcessCommandList2, ID3D12VideoProcessCommandList1)
    public:
        /// <summary>
        /// Specifies whether or not protected resources can be accessed by subsequent commands 
        /// in the video process command list. By default, no protected resources are enabled. 
        /// After calling SetProtectedResourceSession with a valid session, protected resources 
        /// of the same type can refer to that session. After calling SetProtectedResourceSession 
        /// with nullptr, no protected resources can be accessed.
        /// </summary>
        /// <param name="protectedResourceSession">
        /// An optional pointer to an ID3D12ProtectedResourceSession. You can obtain an 
        /// ID3D12ProtectedResourceSession by calling D3D12Device4::CreateProtectedResourceSession.
        /// </param>
        void SetProtectedResourceSession(ID3D12ProtectedResourceSession* protectedResourceSession) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->SetProtectedResourceSession(protectedResourceSession);
        }
        void SetProtectedResourceSession(const D3D12ProtectedResourceSession& protectedResourceSession) const
        {
            SetProtectedResourceSession(protectedResourceSession.GetInterfacePointer<ID3D12ProtectedResourceSession>());
        }

        /// <summary>
        /// Records a command to initializes or re-initializes a video extension command 
        /// into a video processor command list.
        /// </summary>
        /// <param name="extensionCommand">
        /// Pointer to an ID3D12VideoExtensionCommand representing the video extension 
        /// command to initialize. The caller is responsible for maintaining object 
        /// lifetime until command execution is complete.
        /// </param>
        /// <param name="initializationParameters">
        /// A pointer to the creation parameters structure, which is defined by the command. 
        /// The parameters structure must match the parameters enumerated by a call to 
        /// D3D12VideoDevice::CheckFeatureSupport with the feature value of 
        /// D3D12_FEATURE_VIDEO_EXTENSION_COMMAND_PARAMETERS and a parameter stage value 
        /// of D3D12_VIDEO_EXTENSION_COMMAND_PARAMETER_STAGE_INITIALIZATION.
        /// </param>
        /// <param name="initializationParametersSizeInBytes">
        /// The size of the initializationParameters parameter structure, in bytes.
        /// </param>
        void InitializeExtensionCommand(ID3D12VideoExtensionCommand* extensionCommand, const void* initializationParameters, SIZE_T initializationParametersSizeInBytes) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->InitializeExtensionCommand(extensionCommand, initializationParameters, initializationParametersSizeInBytes);
        }
        void InitializeExtensionCommand(const D3D12VideoExtensionCommand& extensionCommand, const void* initializationParameters, SIZE_T initializationParametersSizeInBytes) const
        {
            InitializeExtensionCommand(extensionCommand.GetInterfacePointer<ID3D12VideoExtensionCommand>(), initializationParameters, initializationParametersSizeInBytes);
        }

        /// <summary>
        /// Records a command to execute a video extension command into a video process 
        /// command list.
        /// </summary>
        /// <param name="extensionCommand">
        /// Pointer to an ID3D12VideoExtensionCommand representing the video extension command 
        /// to execute. The caller is responsible for maintaining object lifetime until command 
        /// execution is complete.
        /// </param>
        /// <param name="executionParameters">
        /// A pointer to the execution parameters structure, which is defined by the command. 
        /// The parameters structure must match the parameters enumerated by a call to 
        /// D3D12VideoDevice::CheckFeatureSupport with the feature value of 
        /// D3D12_FEATURE_VIDEO_EXTENSION_COMMAND_PARAMETERS and a parameter stage value 
        /// of D3D12_VIDEO_EXTENSION_COMMAND_PARAMETER_STAGE_EXECUTION.
        /// </param>
        /// <param name="executionParametersSizeInBytes">
        /// The size of the executionParameters parameter structure, in bytes.
        /// </param>
        void ExecuteExtensionCommand(ID3D12VideoExtensionCommand* extensionCommand, const void* executionParameters, SIZE_T executionParametersSizeInBytes) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ExecuteExtensionCommand(extensionCommand, executionParameters, executionParametersSizeInBytes);
        }
        void ExecuteExtensionCommand(const D3D12VideoExtensionCommand& extensionCommand, const void* executionParameters, SIZE_T executionParametersSizeInBytes) const
        {
            ExecuteExtensionCommand(extensionCommand.GetInterfacePointer<ID3D12VideoExtensionCommand>(), executionParameters, executionParametersSizeInBytes);
        }
    };

    /// <summary>
    /// Encapsulates a list of graphics commands for video encoding. This class 
    /// inherits from D3D12VideoEncodeCommandList and adds support for video 
    /// extension commands.
    /// </summary>
    class D3D12VideoEncodeCommandList1 : public D3D12VideoEncodeCommandList
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoEncodeCommandList1, D3D12VideoEncodeCommandList, ID3D12VideoEncodeCommandList1, ID3D12VideoEncodeCommandList)
    public:

        /// <summary>
        /// Records a command to initializes or re-initializes a video extension command 
        /// into an encode command list.
        /// </summary>
        /// <param name="extensionCommand">
        /// Pointer to an ID3D12VideoExtensionCommand representing the video extension 
        /// command to initialize. The caller is responsible for maintaining object 
        /// lifetime until command execution is complete.
        /// </param>
        /// <param name="initializationParameters">
        /// A pointer to the creation parameters structure, which is defined by the command. 
        /// The parameters structure must match the parameters enumerated by a call to 
        /// D3D12VideoDevice::CheckFeatureSupport with the feature value of 
        /// D3D12_FEATURE_VIDEO_EXTENSION_COMMAND_PARAMETERS and a parameter stage value 
        /// of D3D12_VIDEO_EXTENSION_COMMAND_PARAMETER_STAGE_INITIALIZATION.
        /// </param>
        /// <param name="initializationParametersSizeInBytes">
        /// The size of the initializationParameters parameter structure, in bytes.
        /// </param>
        void InitializeExtensionCommand(ID3D12VideoExtensionCommand* extensionCommand, const void* initializationParameters, SIZE_T initializationParametersSizeInBytes) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->InitializeExtensionCommand(extensionCommand, initializationParameters, initializationParametersSizeInBytes);
        }
        void InitializeExtensionCommand(const D3D12VideoExtensionCommand& extensionCommand, const void* initializationParameters, SIZE_T initializationParametersSizeInBytes) const
        {
            InitializeExtensionCommand(extensionCommand.GetInterfacePointer<ID3D12VideoExtensionCommand>(), initializationParameters, initializationParametersSizeInBytes);
        }

        /// <summary>
        /// Records a command to execute a video extension command into an encode command list.
        /// </summary>
        /// <param name="extensionCommand">
        /// Pointer to an ID3D12VideoExtensionCommand representing the video extension command 
        /// to execute. The caller is responsible for maintaining object lifetime until command 
        /// execution is complete.
        /// </param>
        /// <param name="executionParameters">
        /// A pointer to the execution parameters structure, which is defined by the command. 
        /// The parameters structure must match the parameters enumerated by a call to 
        /// D3D12VideoDevice::CheckFeatureSupport with the feature value of 
        /// D3D12_FEATURE_VIDEO_EXTENSION_COMMAND_PARAMETERS and a parameter stage value 
        /// of D3D12_VIDEO_EXTENSION_COMMAND_PARAMETER_STAGE_EXECUTION.
        /// </param>
        /// <param name="executionParametersSizeInBytes">
        /// The size of the executionParameters parameter structure, in bytes.
        /// </param>
        void ExecuteExtensionCommand(ID3D12VideoExtensionCommand* extensionCommand, const void* executionParameters, SIZE_T executionParametersSizeInBytes) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ExecuteExtensionCommand(extensionCommand, executionParameters, executionParametersSizeInBytes);
        }
        void ExecuteExtensionCommand(const D3D12VideoExtensionCommand& extensionCommand, const void* executionParameters, SIZE_T executionParametersSizeInBytes) const
        {
            ExecuteExtensionCommand(extensionCommand.GetInterfacePointer<ID3D12VideoExtensionCommand>(), executionParameters, executionParametersSizeInBytes);
        }
    };

    /// <summary>
    /// Represents a Direct3D 12 video encoder.
    /// </summary>
    class D3D12VideoEncoder : public D3D12Pageable
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoEncoder, D3D12Pageable, ID3D12VideoEncoder, ID3D12Pageable)
    public:
        /// <summary>
        /// Gets the node mask for the video encoder.
        /// </summary>
        /// <returns>
        /// The node mask value specified in the D3D12_VIDEO_ENCODER_DESC 
        /// passed into D3D12VideoDevice3::CreateVideoEncoder.
        /// </returns>
        UINT GetNodeMask() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetNodeMask( );
        }

        /// <summary>
        /// Gets the encoder flags with which the video encoder was initialized.
        /// </summary>
        /// <returns>
        /// The bitwise OR combination of values from the D3D12_VIDEO_ENCODER_FLAGS 
        /// enumeration specified in the D3D12_VIDEO_ENCODER_DESC passed into 
        /// D3D12VideoDevice3::CreateVideoEncoder.
        /// </returns>
        D3D12_VIDEO_ENCODER_FLAGS GetEncoderFlags( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetEncoderFlags();
        }

        /// <summary>
        /// Gets the codec associated with the video encoder.
        /// </summary>
        D3D12_VIDEO_ENCODER_CODEC GetCodec( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetCodec();
        }

        /// <summary>
        /// Gets the codec profile associated with the video encoder.
        /// </summary>
        /// <note>
        /// Signature does not seem to allow for the expected functionality,
        /// </note>
        void GetCodecProfile( D3D12_VIDEO_ENCODER_PROFILE_DESC destinationProfile) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->GetCodecProfile(destinationProfile);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        /// <summary>
        /// Gets the codec configuration parameters associated with the video encoder.
        /// </summary>
        /// <note>
        /// Signature does not seem to allow for the expected functionality,
        /// </note>
        void GetCodecConfiguration(D3D12_VIDEO_ENCODER_CODEC_CONFIGURATION destinationCodecConfig) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->GetCodecConfiguration(destinationCodecConfig);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        /// <summary>
        /// Gets the input format of the video encoder.
        /// </summary>
        DXGI_FORMAT GetInputFormat( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetInputFormat();
        }

        /// <summary>
        /// Gets the maximum motion estimation precision of the video encoder.
        /// </summary>
        D3D12_VIDEO_ENCODER_MOTION_ESTIMATION_PRECISION_MODE GetMaxMotionEstimationPrecision( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetMaxMotionEstimationPrecision();
        }
    };


    /// <summary>
    /// Represents a Direct3D 12 video encoder heap.
    /// </summary>
    class D3D12VideoEncoderHeap : public D3D12Pageable
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoEncoderHeap, D3D12Pageable, ID3D12VideoEncoderHeap, ID3D12Pageable)
    public:
        /// <summary>
        /// Gets the node mask for the video encoder heap.
        /// </summary>
        UINT GetNodeMask() const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetNodeMask();
        }

        /// <summary>
        /// Gets the encoder heap flags with which the video encoder heap was initialized.
        /// </summary>
        D3D12_VIDEO_ENCODER_HEAP_FLAGS GetEncoderHeapFlags( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetEncoderHeapFlags();
        }

        /// <summary>
        /// Gets the codec associated with the video encoder heap.
        /// </summary>
        /// <returns></returns>
        D3D12_VIDEO_ENCODER_CODEC GetCodec( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetCodec();
        }

        /// <summary>
        /// Gets the codec profile associated with the video encoder heap.
        /// </summary>
        /// <note>
        /// Signature does not seem to allow for the expected functionality,
        /// </note>
        void GetCodecProfile( D3D12_VIDEO_ENCODER_PROFILE_DESC destinationProfile) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->GetCodecProfile(destinationProfile);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        /// <summary>
        /// Gets the codec level associated with the video encoder heap.
        /// </summary>
        /// <note>
        /// Signature does not seem to allow for the expected functionality,
        /// </note>
        void GetCodecLevel( D3D12_VIDEO_ENCODER_LEVEL_SETTING destinationLevel) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->GetCodecLevel(destinationLevel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        /// <summary>
        /// Gets the resolution list count associated with the video encoder heap.
        /// </summary>
        UINT GetResolutionListCount( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetResolutionListCount();
        }

        /// <summary>
        /// Gets the resolution list associated with the video encoder heap.
        /// </summary>
        /// <param name="resolutionsListCount">
        /// The count of resolutions to retrieve. Get the number of resolutions with 
        /// which the encoder heap was created by calling D3D12VideoEncoderHeap::GetResolutionListCount.
        /// </param>
        /// <param name="resolutionList">
        /// Receives a pointer to an array of D3D12_VIDEO_ENCODER_PICTURE_RESOLUTION_DESC structures 
        /// representing the resolutions specified in the D3D12_VIDEO_ENCODER_HEAP_DESC passed into 
        /// D3D12VideoDevice3::CreateVideoEncoderHeap.
        /// </param>
        void GetResolutionList(const UINT resolutionsListCount, D3D12_VIDEO_ENCODER_PICTURE_RESOLUTION_DESC* resolutionList) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->GetResolutionList(resolutionsListCount, resolutionList);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    /// <summary>
    /// Extends the D3D12VideoDevice2 class to add support video encoding capabilities.
    /// </summary>
    class D3D12VideoDevice3 : public D3D12VideoDevice2
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoDevice3, D3D12VideoDevice2, ID3D12VideoDevice3, ID3D12VideoDevice2)
    public:
        /// <summary>
        /// Creates a new instance of ID3D12VideoEncoder.
        /// </summary>
        /// <param name="videoEncoderDesc">
        /// A D3D12_VIDEO_ENCODER_DESC representing the configuration parameters for the video encoder.
        /// </param>
        /// <param name="riid">
        /// The globally unique identifier (GUID) for the video encoder interface. 
        /// Expected value: IID_ID3D12VideoEncoder.
        /// </param>
        /// <param name="videoEncoder">
        /// A pointer to a memory block that receives a pointer to the video encoder interface.
        /// </param>
        void CreateVideoEncoder(const D3D12_VIDEO_ENCODER_DESC* videoEncoderDesc, REFIID riid, void** videoEncoder) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->CreateVideoEncoder(videoEncoderDesc, riid, videoEncoder);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        D3D12VideoEncoder CreateVideoEncoder(const D3D12_VIDEO_ENCODER_DESC* videoEncoderDesc) const
        {
            ID3D12VideoEncoder* itf = nullptr;
            CreateVideoEncoder(videoEncoderDesc, __uuidof(ID3D12VideoEncoder), (void**)&itf);
            return D3D12VideoEncoder(itf);
        }

        /// <summary>
        /// Creates a new instance of ID3D12VideoEncoderHeap.
        /// </summary>
        /// <param name="videoEncoderHeapDesc">
        /// A D3D12_VIDEO_ENCODER_HEAP_DESC representing the configuration parameters for the video encoder heap.
        /// </param>
        /// <param name="riid">
        /// The globally unique identifier (GUID) for the video encoder heap interface. 
        /// Expected value: IID_ID3D12VideoEncoderHeap.
        /// </param>
        /// <param name="videoEncoderHeap">
        /// A pointer to a memory block that receives a pointer to the video encoder heap interface.
        /// </param>
        void CreateVideoEncoderHeap( const D3D12_VIDEO_ENCODER_HEAP_DESC* videoEncoderHeapDesc, REFIID riid, void** videoEncoderHeap) const
        {
            InterfaceType* pInterface = GetInterface();
            auto hr = pInterface->CreateVideoEncoderHeap(videoEncoderHeapDesc, riid, videoEncoderHeap);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        D3D12VideoEncoderHeap CreateVideoEncoderHeap(const D3D12_VIDEO_ENCODER_HEAP_DESC* videoEncoderHeapDesc)
        {
            ID3D12VideoEncoderHeap* itf = nullptr;
            CreateVideoEncoderHeap(videoEncoderHeapDesc, __uuidof(ID3D12VideoEncoderHeap), (void**)&itf);
            return D3D12VideoEncoderHeap(itf);
        }
    };

    /// <summary>
    /// Encapsulates a list of graphics commands for video encoding. This class inherits from 
    /// D3D12VideoEncodeCommandList1 and adds methods for encoding video and resolving encode 
    /// operation metadata.
    /// </summary>
    class D3D12VideoEncodeCommandList2 : public D3D12VideoEncodeCommandList1
    {
    public:
        COMMON_GRAPHICS3D_STANDARD_METHODS_IMPL(D3D12VideoEncodeCommandList2, D3D12VideoEncodeCommandList1, ID3D12VideoEncodeCommandList2, ID3D12VideoEncodeCommandList1)
    public:
        /// <summary>
        /// Encodes a bitstream.
        /// </summary>
        /// <param name="encoder">
        /// A ID3D12VideoEncoder representing the video encoder to be used for the encode operation.
        /// </param>
        /// <param name="heap">
        /// <p>
        /// A ID3D12VideoEncoderHeap representing the video encoder heap to be used for this operation.
        /// </p>
        /// <p>
        /// The encoder heap object allocation must not be released before any in-flight GPU commands 
        /// that references it finish execution.
        /// </p>
        /// <p>
        /// Note that the reconfigurations in recorded commands input arguments done within allowed 
        /// bounds (e.g. different target resolutions in allowed lists of resolutions) can co-exist 
        /// in-flight with the same encoder heap instance, providing the target resolution is 
        /// supported by the given encoder heap.
        /// </p>
        /// <p>
        /// In the current release, only one execution flow at a time using the same encoder or encoder 
        /// heap instances is supported. All commands against these objects must be recorded and submitted 
        /// in a serialized order, i.e. from a single CPU thread or synchronizing multiple threads in 
        /// such way that the commands are recorded in a serialized order.
        /// </p>
        /// <p>
        /// The video encoder and video encoder heap may be used to record commands from multiple command 
        /// lists, but may only be associated with one command list at a time. The application is 
        /// responsible for synchronizing single accesses to the video encoder and video encoder heap at 
        /// a time. The application must also record video encoding commands against the video encoder 
        /// and video encoder heaps in the order that they are executed on the GPU.
        /// </p>
        /// </param>
        /// <param name="inputArguments">
        /// A D3D12_VIDEO_ENCODER_ENCODEFRAME_INPUT_ARGUMENTS representing input arguments for the encode operation.
        /// </param>
        /// <param name="outputArguments">
        /// A D3D12_VIDEO_ENCODER_ENCODEFRAME_OUTPUT_ARGUMENTS representing output arguments for the encode operation.
        /// </param>
        void EncodeFrame( ID3D12VideoEncoder* encoder, ID3D12VideoEncoderHeap* heap, const D3D12_VIDEO_ENCODER_ENCODEFRAME_INPUT_ARGUMENTS* inputArguments, const D3D12_VIDEO_ENCODER_ENCODEFRAME_OUTPUT_ARGUMENTS* outputArguments) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->EncodeFrame(encoder, heap, inputArguments, outputArguments);
        }

        /// <summary>
        /// Resolves the output metadata from a call to D3D12VideoEncodeCommandList2::EncodeFrame 
        /// to a readable format.
        /// </summary>
        /// <param name="inputArguments">
        /// A pointer to a D3D12_VIDEO_ENCODER_OUTPUT_METADATA representing the opaque output metadata 
        /// results from EncodeFrame.
        /// </param>
        /// <param name="outputArguments">
        /// A pointer to a D3D12_VIDEO_ENCODER_RESOLVE_METADATA_OUTPUT_ARGUMENTS output parameter that 
        /// receives the resolved, readable metadata.
        /// </param>
        void ResolveEncoderOutputMetadata( const D3D12_VIDEO_ENCODER_RESOLVE_METADATA_INPUT_ARGUMENTS* inputArguments, const D3D12_VIDEO_ENCODER_RESOLVE_METADATA_OUTPUT_ARGUMENTS* outputArguments) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ResolveEncoderOutputMetadata(inputArguments, outputArguments);
        }
    };


}

#endif

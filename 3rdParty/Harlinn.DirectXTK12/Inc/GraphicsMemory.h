//--------------------------------------------------------------------------------------
// File: GraphicsMemory.h
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkID=615561
//--------------------------------------------------------------------------------------

#pragma once

#include <HDirectXTK12Def.h>

#ifdef _GAMING_XBOX_SCARLETT
#include <d3d12_xs.h>
#elif (defined(_XBOX_ONE) && defined(_TITLE)) || defined(_GAMING_XBOX)
#include <d3d12_x.h>
#elif defined(USING_DIRECTX_HEADERS)
#include <directx/d3d12.h>
#include <dxguids/dxguids.h>
#else
#include <d3d12.h>
#endif

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>

#ifdef _GAMING_XBOX
#include <gxdk.h>
#endif

#if defined(_GAMING_XBOX) && (defined(_DEBUG) || defined(PROFILE)) && (_GXDK_VER >= 0x585D073C) /* GDK Edition 221000 */
#define USING_PIX_CUSTOM_MEMORY_EVENTS
#include <tuple>
#endif

namespace DirectX
{
    class LinearAllocatorPage;

    inline namespace DX12
    {
    // Works a little like a smart pointer. The memory will only be fenced by the GPU once the pointer
    // has been invalidated or the user explicitly marks it for fencing.
        class GraphicsResource
        {
        public:
            HDXTK12_EXPORT GraphicsResource() noexcept;
            HDXTK12_EXPORT GraphicsResource(
                _In_ LinearAllocatorPage* page,
                _In_ D3D12_GPU_VIRTUAL_ADDRESS gpuAddress,
                _In_ ID3D12Resource* resource,
                _In_ void* memory,
                _In_ size_t offset,
                _In_ size_t size) noexcept;

            HDXTK12_EXPORT GraphicsResource(GraphicsResource&& other) noexcept;
            HDXTK12_EXPORT GraphicsResource&& operator= (GraphicsResource&&) noexcept;

            GraphicsResource(const GraphicsResource&) = delete;
            GraphicsResource& operator= (const GraphicsResource&) = delete;

            HDXTK12_EXPORT ~GraphicsResource();

            D3D12_GPU_VIRTUAL_ADDRESS GpuAddress() const noexcept { return mGpuAddress; }
            ID3D12Resource* Resource() const noexcept { return mResource; }
            void* Memory() const noexcept { return mMemory; }
            size_t ResourceOffset() const noexcept { return mBufferOffset; }
            size_t Size() const noexcept { return mSize; }

            explicit operator bool() const noexcept { return mResource != nullptr; }

            // Clear the pointer. Using operator -> will produce bad results.
            HDXTK12_EXPORT void __cdecl Reset() noexcept;
            HDXTK12_EXPORT void __cdecl Reset(GraphicsResource&&) noexcept;

        private:
            LinearAllocatorPage*        mPage;
            D3D12_GPU_VIRTUAL_ADDRESS   mGpuAddress;
            ID3D12Resource*             mResource;
            void*                       mMemory;
            size_t                      mBufferOffset;
            size_t                      mSize;
        };

        class SharedGraphicsResource
        {
        public:
            HDXTK12_EXPORT SharedGraphicsResource() noexcept;

            HDXTK12_EXPORT SharedGraphicsResource(SharedGraphicsResource&&) noexcept;
            HDXTK12_EXPORT SharedGraphicsResource&& operator= (SharedGraphicsResource&&) noexcept;

            HDXTK12_EXPORT SharedGraphicsResource(GraphicsResource&&);
            HDXTK12_EXPORT SharedGraphicsResource&& operator= (GraphicsResource&&);

            HDXTK12_EXPORT SharedGraphicsResource(const SharedGraphicsResource&) noexcept;
            HDXTK12_EXPORT SharedGraphicsResource& operator= (const SharedGraphicsResource&) noexcept;

            SharedGraphicsResource(const GraphicsResource&) = delete;
            SharedGraphicsResource& operator= (const GraphicsResource&) = delete;

            HDXTK12_EXPORT ~SharedGraphicsResource();

            D3D12_GPU_VIRTUAL_ADDRESS GpuAddress() const noexcept { return mSharedResource->GpuAddress(); }
            ID3D12Resource* Resource() const noexcept { return mSharedResource->Resource(); }
            void* Memory() const noexcept { return mSharedResource->Memory(); }
            size_t ResourceOffset() const noexcept { return mSharedResource->ResourceOffset(); }
            size_t Size() const noexcept { return mSharedResource->Size(); }

            explicit operator bool() const noexcept { return mSharedResource != nullptr; }

            bool operator == (const SharedGraphicsResource& other) const noexcept { return mSharedResource.get() == other.mSharedResource.get(); }
            bool operator != (const SharedGraphicsResource& other) const noexcept { return mSharedResource.get() != other.mSharedResource.get(); }

            // Clear the pointer. Using operator -> will produce bad results.
            HDXTK12_EXPORT void __cdecl Reset() noexcept;
            HDXTK12_EXPORT void __cdecl Reset(GraphicsResource&&);
            HDXTK12_EXPORT void __cdecl Reset(SharedGraphicsResource&&) noexcept;
            HDXTK12_EXPORT void __cdecl Reset(const SharedGraphicsResource& resource) noexcept;

        private:
            std::shared_ptr<GraphicsResource> mSharedResource;
        };

        //------------------------------------------------------------------------------
        struct GraphicsMemoryStatistics
        {
            size_t committedMemory;     // Bytes of memory currently committed/in-flight
            size_t totalMemory;         // Total bytes of memory used by the allocators
            size_t totalPages;          // Total page count
            size_t peakCommitedMemory;  // Peak commited memory value since last reset
            size_t peakTotalMemory;     // Peak total bytes
            size_t peakTotalPages;      // Peak total page count
        };

        //------------------------------------------------------------------------------
        class GraphicsMemory
        {
        public:
            enum Tag : uint32_t
            {
                TAG_GENERIC = 0,
                TAG_CONSTANT,
                TAG_VERTEX,
                TAG_INDEX,
                TAG_SPRITES,
                TAG_TEXTURE,
                TAG_COMPUTE,
            };

            HDXTK12_EXPORT explicit GraphicsMemory(_In_ ID3D12Device* device);

            HDXTK12_EXPORT GraphicsMemory(GraphicsMemory&&) noexcept;
            HDXTK12_EXPORT GraphicsMemory& operator= (GraphicsMemory&&) noexcept;

            GraphicsMemory(GraphicsMemory const&) = delete;
            GraphicsMemory& operator=(GraphicsMemory const&) = delete;

            HDXTK12_EXPORT virtual ~GraphicsMemory();

            // Make sure to keep the GraphicsResource handle alive as long as you need to access
            // the memory on the CPU. For example, do not simply cache GpuAddress() and discard
            // the GraphicsResource object, or your memory may be overwritten later.
            GraphicsResource __cdecl Allocate(size_t size, size_t alignment = 16, uint32_t tag = TAG_GENERIC)
            {
                auto alloc = AllocateImpl(size, alignment);
#ifdef USING_PIX_CUSTOM_MEMORY_EVENTS
                std::ignore = ReportCustomMemoryAlloc(alloc.Memory(), alloc.Size(), tag);
#else
                UNREFERENCED_PARAMETER(tag);
#endif
                return alloc;
            }

            // Version of Allocate that aligns to D3D12 constant buffer requirements
            template<typename T> GraphicsResource AllocateConstant()
            {
                constexpr size_t alignment = D3D12_CONSTANT_BUFFER_DATA_PLACEMENT_ALIGNMENT;
                constexpr size_t alignedSize = (sizeof(T) + alignment - 1) & ~(alignment - 1);
                auto alloc = AllocateImpl(alignedSize, alignment);
#ifdef USING_PIX_CUSTOM_MEMORY_EVENTS
                // This cast is needed to capture the type information in the PDB
                std::ignore = reinterpret_cast<T*>(ReportCustomMemoryAlloc(alloc.Memory(), alloc.Size(), TAG_CONSTANT));
#endif
                return alloc;
            }
            template<typename T> GraphicsResource AllocateConstant(const T& setData)
            {
                GraphicsResource alloc = AllocateConstant<T>();
                memcpy(alloc.Memory(), &setData, sizeof(T));
                return alloc;
            }

            // Submits all the pending one-shot memory to the GPU.
            // The memory will be recycled once the GPU is done with it.
            HDXTK12_EXPORT void __cdecl Commit(_In_ ID3D12CommandQueue* commandQueue);

            // This frees up any unused memory.
            // If you want to make sure all memory is reclaimed, idle the GPU before calling this.
            // It is not recommended that you call this unless absolutely necessary (e.g. your
            // memory budget changes at run-time, or perhaps you're changing levels in your game.)
            HDXTK12_EXPORT void __cdecl GarbageCollect();

            // Memory statistics
            HDXTK12_EXPORT GraphicsMemoryStatistics __cdecl GetStatistics();
            HDXTK12_EXPORT void __cdecl ResetStatistics();

            // Singleton
            // Should only use nullptr for single GPU scenarios; mGPU requires a specific device
            HDXTK12_EXPORT static GraphicsMemory& __cdecl Get(_In_opt_ ID3D12Device* device = nullptr);

        private:
            // Private implementation.
            class Impl;

            HDXTK12_EXPORT GraphicsResource __cdecl AllocateImpl(size_t size, size_t alignment);

#ifdef USING_PIX_CUSTOM_MEMORY_EVENTS
            // The declspec is required to ensure the proper information is captured in the PDB
            __declspec(allocator) static void* __cdecl ReportCustomMemoryAlloc(void* pMem, size_t size, UINT64 metadata);
#endif

            std::unique_ptr<Impl> pImpl;
        };
    }
}

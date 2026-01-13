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
#pragma once
#ifndef HDMCDEF_H_
#define HDMCDEF_H_

#include <HWDef.h>

//#define HDMC_USES_HCC_MATH 1
#ifdef HDMC_USES_HCC_MATH
#define HDMC_USES_HCC_MATH_DEBUG 1
#include <HCCVectorMath.h>
#include <HWColor.h>
#endif


#include <HWGraphicsD3D12.h>
#include <HWDXGI.h>
#include <d3dx12.h>
#include <HCCThread.h>


#ifdef BUILDING_HARLINN_DIRECTX_MINIENGINE_CORE
#define HDMC_EXPORT __declspec(dllexport)
#define HDMC_TEMPLATE_EXPORT __declspec(dllexport)
#define HDMC_TEMPLATE_EXPORT_DECL
#else
#define HDMC_EXPORT __declspec(dllimport)
#define HDMC_TEMPLATE_EXPORT __declspec(dllimport)
#define HDMC_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.DirectX.MiniEngine.Core.lib")
#endif

#ifdef _DEBUG
#define HDMC_INLINE_DECL HDMC_EXPORT
#define HDMC_INLINE 
#else
#define HDMC_INLINE_DECL 
#define HDMC_INLINE inline
#endif

#define HDMC_DUMPING 1
#ifdef HDMC_DUMPING
#define HDMC_DUMP( n ) ::Harlinn::Windows::DirectX::MiniEngine::Math::Dump( #n, n, __FILE__, __LINE__, __FUNCTION__ )
#else
#define HDMC_DUMP( n )
#endif

namespace Harlinn::Windows::DirectX::MiniEngine
{
    namespace D3D12 = ::Harlinn::Windows::Graphics::D3D12;
#ifdef HDMC_USES_HCC_MATH
    namespace Math
    {
        namespace m
        {
            using namespace ::Harlinn::Common::Core::Math;

            using Traits = SIMD::Traits<float, 4>;
            using SIMDType = typename Traits::SIMDType;
        }
    }
    using XMFLOAT2 = Math::m::Vector<float, 2>;
    using XMFLOAT3 = Math::m::Vector<float, 3>;
    using XMFLOAT4 = Math::m::Vector<float, 4>;
    using XMUINT4 = Math::m::Vector<UInt32, 4>;
#else
    using XMVECTOR = ::DirectX::XMVECTOR;
    using FXMVECTOR = ::DirectX::FXMVECTOR;
    using XMFLOAT2 = ::DirectX::XMFLOAT2;
    using XMFLOAT3 = ::DirectX::XMFLOAT3;
    using XMFLOAT4 = ::DirectX::XMFLOAT4;
    using XMFLOAT4X4 = ::DirectX::XMFLOAT4X4;
    using XMMATRIX = ::DirectX::XMMATRIX;
    using XMVECTORF32 = ::DirectX::XMVECTORF32;
    using XMUINT2 = ::DirectX::XMUINT2;
    using XMUINT3 = ::DirectX::XMUINT3;
    using XMUINT4 = ::DirectX::XMUINT4;
#endif    
    using D3DBlob = ::Harlinn::Windows::Graphics::D3DBlob;
    using D3D12CommandAllocator = ::Harlinn::Windows::Graphics::D3D12CommandAllocator;
    using D3D12CommandList = ::Harlinn::Windows::Graphics::D3D12CommandList;
    using D3D12CommandQueue = ::Harlinn::Windows::Graphics::D3D12CommandQueue;
    using D3D12CommandSignature = ::Harlinn::Windows::Graphics::D3D12CommandSignature;
    using D3D12DescriptorHeap = ::Harlinn::Windows::Graphics::D3D12DescriptorHeap;
    using D3D12Device = ::Harlinn::Windows::Graphics::D3D12Device;
    using D3D12Fence = ::Harlinn::Windows::Graphics::D3D12Fence;
    using D3D12GraphicsCommandList = ::Harlinn::Windows::Graphics::D3D12GraphicsCommandList;
    using D3D12Heap = ::Harlinn::Windows::Graphics::D3D12Heap;
    using D3D12PipelineState = ::Harlinn::Windows::Graphics::D3D12PipelineState;
    using D3D12QueryHeap = ::Harlinn::Windows::Graphics::D3D12QueryHeap;
    using D3D12Resource = ::Harlinn::Windows::Graphics::D3D12Resource;
    using D3D12RootSignature = ::Harlinn::Windows::Graphics::D3D12RootSignature;
    

}

#define D3D12_GPU_VIRTUAL_ADDRESS_NULL      ((D3D12_GPU_VIRTUAL_ADDRESS)0)
#define D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN   ((D3D12_GPU_VIRTUAL_ADDRESS)-1)
#define MY_IID_PPV_ARGS                     IID_PPV_ARGS

#endif

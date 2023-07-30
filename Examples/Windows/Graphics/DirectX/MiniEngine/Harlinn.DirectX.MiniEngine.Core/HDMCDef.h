#pragma once
#ifndef HDMCDEF_H_
#define HDMCDEF_H_

#include <HWDef.h>
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

namespace Harlinn::Windows::DirectX::MiniEngine
{
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
    
    using D3DBlob = Harlinn::Windows::Graphics::D3DBlob;
    using D3D12CommandAllocator = Harlinn::Windows::Graphics::D3D12CommandAllocator;
    using D3D12CommandList = Harlinn::Windows::Graphics::D3D12CommandList;
    using D3D12CommandQueue = Harlinn::Windows::Graphics::D3D12CommandQueue;
    using D3D12CommandSignature = Harlinn::Windows::Graphics::D3D12CommandSignature;
    using D3D12DescriptorHeap = Harlinn::Windows::Graphics::D3D12DescriptorHeap;
    using D3D12Device = Harlinn::Windows::Graphics::D3D12Device;
    using D3D12Fence = Harlinn::Windows::Graphics::D3D12Fence;
    using D3D12GraphicsCommandList = Harlinn::Windows::Graphics::D3D12GraphicsCommandList;
    using D3D12Heap = Harlinn::Windows::Graphics::D3D12Heap;
    using D3D12PipelineState = Harlinn::Windows::Graphics::D3D12PipelineState;
    using D3D12QueryHeap = Harlinn::Windows::Graphics::D3D12QueryHeap;
    using D3D12Resource = Harlinn::Windows::Graphics::D3D12Resource;
    using D3D12RootSignature = Harlinn::Windows::Graphics::D3D12RootSignature;
    


}

#define D3D12_GPU_VIRTUAL_ADDRESS_NULL      ((D3D12_GPU_VIRTUAL_ADDRESS)0)
#define D3D12_GPU_VIRTUAL_ADDRESS_UNKNOWN   ((D3D12_GPU_VIRTUAL_ADDRESS)-1)
#define MY_IID_PPV_ARGS                     IID_PPV_ARGS

#endif

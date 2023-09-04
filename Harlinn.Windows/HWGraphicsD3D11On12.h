#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D11ON12_H_
#define HARLINN_WINDOWS_HWGRAPHICSD3D11ON12_H_

#include "HWGraphicsD3D11.h"
#include "HWGraphicsD3D12.h"

namespace Harlinn::Windows::Graphics::D3D11On12
{
    class D3D11On12Device : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2(D3D11On12Device, Unknown)
    public:
        void CreateWrappedResource(IUnknown* resource12, const D3D11_RESOURCE_FLAGS* flags11, D3D12_RESOURCE_STATES inState, D3D12_RESOURCE_STATES outState, const Guid& riid, void** resource11) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateWrappedResource(resource12, flags11, inState, outState, riid, resource11);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ReleaseWrappedResources(ID3D11Resource* const* resources, UINT numResources) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ReleaseWrappedResources(resources, numResources);
        }

        void AcquireWrappedResources( ID3D11Resource* const* ppResources, UINT numResources) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->AcquireWrappedResources(ppResources, numResources);
        }
    };

    class D3D11On12Device1 : public D3D11On12Device
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2(D3D11On12Device1, D3D11On12Device)
    public:
        void GetD3D12Device(const Guid& riid, void** device) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetD3D12Device(riid, device);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class D3D11On12Device2 : public D3D11On12Device1
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL2(D3D11On12Device2, D3D11On12Device1)
    public:
        void UnwrapUnderlyingResource( ID3D11Resource* resource11, ID3D12CommandQueue* commandQueue, const Guid& riid, void** resource12) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnwrapUnderlyingResource(resource11, commandQueue, riid, resource12);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ReturnUnderlyingResource( ID3D11Resource* resource11, UINT numberOfFences, UINT64* fenceSignalValues, ID3D12Fence** fences) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ReturnUnderlyingResource(resource11, numberOfFences, fenceSignalValues, fences);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


}

#endif
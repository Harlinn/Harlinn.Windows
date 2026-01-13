#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D11ON12_H_
#define HARLINN_WINDOWS_HWGRAPHICSD3D11ON12_H_
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

#include "HWGraphicsD3D11.h"
#include "HWGraphicsD3D12.h"

namespace Harlinn::Windows::Graphics::D3D11On12
{
    class Device;
    class Device1;
    class Device2;

    class Device : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Device, Unknown, ID3D11On12Device, IUnknown )
    public:
        void CreateWrappedResource(IUnknown* resource12, const D3D11_RESOURCE_FLAGS* flags11, D3D12_RESOURCE_STATES inState, D3D12_RESOURCE_STATES outState, const Guid& riid, void** resource11) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateWrappedResource(resource12, flags11, inState, outState, riid, resource11);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        template<typename T = D3D11::Resource>
            requires std::is_base_of_v<D3D11::Resource,T>
        T CreateWrappedResource( const Unknown& d3d12Resource, const D3D11_RESOURCE_FLAGS& flags11, D3D12::ResourceStates inState, D3D12::ResourceStates outState ) const
        {
            using ItfType = typename T::InterfaceType;
            ItfType* itf = nullptr;
            CreateWrappedResource( d3d12Resource.GetInterfacePointer( ), &flags11, static_cast< D3D12_RESOURCE_STATES >( inState ), static_cast< D3D12_RESOURCE_STATES >( outState ), __uuidof( ItfType ), reinterpret_cast< void** >( &itf ) );
            return T( itf );
        }


        void ReleaseWrappedResources(ID3D11Resource* const* resources, UINT numResources) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->ReleaseWrappedResources(resources, numResources);
        }

        void ReleaseWrappedResources( const D3D11::Resource* resources, UINT numResources ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->ReleaseWrappedResources( reinterpret_cast< ID3D11Resource* const* >( resources ), numResources );
        }

        void ReleaseWrappedResources( const D3D11::Resource& resource ) const
        {
            ReleaseWrappedResources( &resource, 1 );
        }

        void AcquireWrappedResources( ID3D11Resource* const* ppResources, UINT numResources) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->AcquireWrappedResources(ppResources, numResources);
        }

        void AcquireWrappedResources( const D3D11::Resource* resources, UINT numResources ) const
        {
            InterfaceType* pInterface = GetInterface( );
            pInterface->AcquireWrappedResources( reinterpret_cast< ID3D11Resource* const* >( resources ), numResources );
        }
        void AcquireWrappedResources( const D3D11::Resource& resource ) const
        {
            AcquireWrappedResources( &resource, 1 );
        }


    };

    class Device1 : public Device
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Device1, Device, ID3D11On12Device1, ID3D11On12Device )
    public:
        void GetD3D12Device(const Guid& riid, void** device) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetD3D12Device(riid, device);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class Device2 : public Device1
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Device2, Device1, ID3D11On12Device2, ID3D11On12Device1 )
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


    inline void CreateDevice( _In_ const Unknown& d3d12device,
        UINT flags,
        _In_reads_opt_( numberOfFeatureLevels ) CONST D3D_FEATURE_LEVEL* featureLevels,
        UINT numberOfFeatureLevels,
        _In_reads_opt_( nomberOfCommandQueues ) IUnknown* CONST* commandQueues,
        UINT numberOfCommandQueues,
        UINT nodeMask,
        _COM_Outptr_opt_ ID3D11Device** d3d11Device,
        _COM_Outptr_opt_ ID3D11DeviceContext** d3d11DeviceContext,
        _Out_opt_ D3D_FEATURE_LEVEL* chosenFeatureLevel )
    {
        auto hr = D3D11On12CreateDevice( d3d12device.GetInterfacePointer(), flags, featureLevels, numberOfCommandQueues, commandQueues, numberOfCommandQueues, nodeMask, d3d11Device, d3d11DeviceContext, chosenFeatureLevel );
        HCC_COM_CHECK_HRESULT( hr );
    }

    template<typename T= D3D11::Device5>
        requires std::is_base_of_v<D3D11::Device,T>
    inline T CreateDevice( _In_ const Unknown& d3d12device,
        UINT flags, 
        _In_reads_opt_( numberOfFeatureLevels ) CONST D3D_FEATURE_LEVEL* featureLevels, 
        UINT numberOfFeatureLevels, 
        _In_reads_opt_( nomberOfCommandQueues ) IUnknown* CONST* commandQueues, 
        UINT numberOfCommandQueues, 
        UINT nodeMask, 
        D3D11::DeviceContext& d3d11DeviceContext, 
        _Out_opt_ D3D_FEATURE_LEVEL* chosenFeatureLevel = nullptr )
    {
        ID3D11Device* d3d11DeviceItf = nullptr;
        ID3D11DeviceContext* d3d11DeviceContextItf = nullptr;
        CreateDevice( d3d12device, flags, featureLevels, numberOfFeatureLevels, commandQueues, numberOfCommandQueues, nodeMask, &d3d11DeviceItf, &d3d11DeviceContextItf, chosenFeatureLevel );
        D3D11::Device result( d3d11DeviceItf );
        d3d11DeviceContext = d3d11DeviceContextItf;
        
        if constexpr ( std::is_same_v<typename T::InterfaceType, ID3D11Device> )
        {
            return result;
        }
        else
        {
            return result.As<T>( );
        }
    }

    template<typename T = D3D11::Device5>
        requires std::is_base_of_v<D3D11::Device, T>
    inline T CreateDevice( _In_ const Unknown& d3d12device, UINT flags, const Unknown& commandQueue, D3D11::DeviceContext& d3d11DeviceContext, UINT nodeMask = 0, _Out_opt_ D3D_FEATURE_LEVEL* chosenFeatureLevel = nullptr )
    {
        IUnknown* commandQueuePtr = commandQueue.GetInterfacePointer( );
        return CreateDevice<T>( d3d12device, flags, nullptr, 0, &commandQueuePtr, 1, nodeMask, d3d11DeviceContext, chosenFeatureLevel );
    }

}

#endif
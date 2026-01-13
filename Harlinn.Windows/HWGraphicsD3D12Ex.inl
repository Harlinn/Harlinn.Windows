#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D12EX_INL_
#define HARLINN_WINDOWS_HWGRAPHICSD3D12EX_INL_
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

#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D12_H_
#include "HWGraphicsD3D12.h"
#endif


namespace Harlinn::Windows::Graphics::D3D12
{

    inline UInt8 GetFormatPlaneCount( const Device& device, DXGI::Format format )
    {
        FeatureDataFormatInfo formatInfo = { format, 0 };
        if ( device.CheckFeatureSupport( formatInfo ) )
        {
            return formatInfo.PlaneCount;
        }
        return 0;
    }

    //
    // TextureCopyLocation
    //
    
    inline TextureCopyLocation::TextureCopyLocation( const Resource& resource )
        : pResource( resource.GetInterfacePointer<ID3D12Resource>( ) ), PlacedFootprint{}
    { }

    inline TextureCopyLocation::TextureCopyLocation( const Resource& resource, const D3D12_PLACED_SUBRESOURCE_FOOTPRINT& footprint )
        : pResource( resource.GetInterfacePointer<ID3D12Resource>( ) ), Type( TextureCopyType::PlacedFootprint ), PlacedFootprint( reinterpret_cast< const PlacedSubresourceFootprint& >( footprint ) )
    { }

    inline TextureCopyLocation::TextureCopyLocation( const Resource& resource, const PlacedSubresourceFootprint& footprint )
        : pResource( resource.GetInterfacePointer<ID3D12Resource>( ) ), Type( TextureCopyType::PlacedFootprint ), PlacedFootprint( footprint )
    { }

    inline TextureCopyLocation::TextureCopyLocation( const Resource& resource, UINT subresourceIndex )
        : pResource( resource.GetInterfacePointer<ID3D12Resource>( ) ), SubresourceIndex( subresourceIndex )
    { }

    //
    // ResourceTransitionBarrier
    //
    inline ResourceTransitionBarrier::ResourceTransitionBarrier( const Resource& resource, UInt32 subresource, ResourceStates stateBefore, ResourceStates stateAfter ) noexcept
        : pResource( resource.GetInterfacePointer<ID3D12Resource>( ) ), Subresource( subresource ), StateBefore( stateBefore ), StateAfter( stateAfter )
    { }

    //
    // ResourceAliasingBarrier
    //
    inline ResourceAliasingBarrier::ResourceAliasingBarrier( const Resource& resourceBefore, const Resource& resourceAfter ) noexcept
        : pResourceBefore( resourceBefore.GetInterfacePointer<ID3D12Resource>( ) ), pResourceAfter( resourceAfter.GetInterfacePointer<ID3D12Resource>( ) )
    { }


    //
    // ResourceUAVBarrier
    //
    inline ResourceUAVBarrier::ResourceUAVBarrier( const Resource& resource ) noexcept
        : pResource( resource.GetInterfacePointer<ID3D12Resource>( ) )
    { }

}

#endif

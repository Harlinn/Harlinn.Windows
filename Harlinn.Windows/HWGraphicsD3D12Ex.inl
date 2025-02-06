#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3D12EX_INL_
#define HARLINN_WINDOWS_HWGRAPHICSD3D12EX_INL_

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

#pragma once
#ifndef HARLINN_WINDOWS_HWGRAPHICSD3COMMON_H_
#define HARLINN_WINDOWS_HWGRAPHICSD3COMMON_H_

#include <HWDef.h>
#include <HCCCOM.h>
#include <HCCException.h>
#include <HWCommon.h>
#include <HWControl.h>

namespace Harlinn::Windows::Graphics
{
    using namespace Harlinn::Common::Core;

    class D3D10Blob : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( D3D10Blob, Unknown, ID3D10Blob, IUnknown )
    public:
        LPVOID GetBufferPointer( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetBufferPointer( );
        }

        SIZE_T GetBufferSize( ) const
        {
            InterfaceType* pInterface = GetInterface( );
            return pInterface->GetBufferSize( );
        }
    };

    using D3DBlob = D3D10Blob;

}

#endif

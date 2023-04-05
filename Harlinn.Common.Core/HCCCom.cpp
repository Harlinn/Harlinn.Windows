#include "pch.h"
#include <HCCCom.h>

namespace Harlinn::Common::Core
{
    bool EnumString::Next( std::wstring& result ) const
    {
        InterfaceType* pInterface = GetInterface( );
        ULONG numberOfElementsFetched = 0;
        LPOLESTR oleString = nullptr;
        auto hr = pInterface->Next( 1, &oleString, &numberOfElementsFetched );
        if ( SUCCEEDED( hr ) )
        {
            result = oleString;
            CoTaskMemFree( oleString );
            return true;
        }
        return false;
    }

    bool EnumString::Next( ULONG celt, LPOLESTR* rgelt, ULONG* pceltFetched ) const
    {
        InterfaceType* pInterface = GetInterface( );
        ULONG numberOfElementsFetched = 0;
        auto hr = pInterface->Next( celt, rgelt, &numberOfElementsFetched );
        if ( SUCCEEDED( hr ) )
        {
            if ( pceltFetched )
            {
                *pceltFetched = numberOfElementsFetched;
            }
            return true;
        }
        return false;
    }
    bool EnumString::Next( ULONG celt, std::vector<std::wstring>& result ) const
    {
        
        InterfaceType* pInterface = GetInterface( );
        ULONG numberOfElementsFetched = 0;
        LPOLESTR* oleStrings = (LPOLESTR*)alloca( celt * sizeof( LPOLESTR ) );
        auto hr = pInterface->Next( celt, oleStrings, &numberOfElementsFetched );
        if ( SUCCEEDED( hr ) )
        {
            result.clear( );
            result.reserve( numberOfElementsFetched );
            for ( ULONG i = 0; i < numberOfElementsFetched; i++ )
            {
                LPOLESTR oleString = oleStrings[i];
                result.emplace_back( oleString );
                CoTaskMemFree( oleString );
            }

            return true;
        }
        return false;
    }
    void EnumString::All( std::vector<std::wstring>& result ) const
    {
        result.clear( );
        InterfaceType* pInterface = GetInterface( );

        LPOLESTR oleStrings[16];
        HRESULT hr = S_OK;
        while ( SUCCEEDED( hr ) )
        {
            ULONG numberOfElementsFetched = 0;
            hr = pInterface->Next( 16, oleStrings, &numberOfElementsFetched );
            if ( SUCCEEDED( hr ) )
            {
                for ( ULONG i = 0; i < numberOfElementsFetched; i++ )
                {
                    LPOLESTR oleString = oleStrings[i];
                    result.emplace_back( oleString );
                    CoTaskMemFree( oleString );
                }
            }
        }
    }
    void EnumString::Skip( ULONG celt ) const
    {
        InterfaceType* pInterface = GetInterface( );
        auto hr = pInterface->Skip( celt );
        CheckHRESULT( hr );
    }
    void EnumString::Reset( ) const
    {
        InterfaceType* pInterface = GetInterface( );
        auto hr = pInterface->Reset( );
        CheckHRESULT( hr );
    }
    EnumString EnumString::Clone( ) const
    {
        InterfaceType* pClone = 0;
        InterfaceType* pInterface = GetInterface( );
        auto hr = pInterface->Clone( &pClone );
        CheckHRESULT( hr );
        EnumString result( pClone );
        return result;
    }

    namespace Com
    {
        namespace Internal
        {
            template<typename T>
            bool CheckIfInterfaceIsSupported(IUnknown* unknown)
            {
                Guid iid = __uuidof(T);
                T* itf = nullptr;
                auto hr = unknown->QueryInterface(iid, (void**)&itf);
                if (hr == S_OK)
                {
                    itf->Release();
                    return true;
                }
                return false;
            }
        }
        std::vector<std::wstring> GetSupportedKnownInterfaces(IUnknown* unknown)
        {
            std::vector<std::wstring> result;
            if (unknown == nullptr)
            {
                return result;
            }
            if (Com::Internal::CheckIfInterfaceIsSupported<IUnknown>(unknown)) { result.push_back(L"IUnknown"); }

#define X( Itf, BaseItf ) if (Com::Internal::CheckIfInterfaceIsSupported<Itf>(unknown)) { result.push_back(L#Itf); }
#include "HCCComInterfaces.xm"
#undef X
            return result;
        }
        std::vector<Guid> GetSupportedKnownInterfaceIds(IUnknown* unknown)
        {
            std::vector<Guid> result;
            if (unknown == nullptr)
            {
                return result;
            }
            if (Com::Internal::CheckIfInterfaceIsSupported<IUnknown>(unknown)) { result.push_back(__uuidof(IUnknown)); }

#define X( Itf, BaseItf ) if (Com::Internal::CheckIfInterfaceIsSupported<Itf>(unknown)) { result.push_back(__uuidof(Itf)); }
#include "HCCComInterfaces.xm"
#undef X
            return result;
        }
    }

}
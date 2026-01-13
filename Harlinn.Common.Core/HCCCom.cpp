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

#include "pch.h"
#include <HCCCom.h>

namespace Harlinn::Common::Core
{
    bool EnumString::Next( WideString& result ) const
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
    bool EnumString::Next( ULONG celt, std::vector<WideString>& result ) const
    {
        
        InterfaceType* pInterface = GetInterface( );
        ULONG numberOfElementsFetched = 0;
        LPOLESTR* oleStrings = (LPOLESTR*)_malloca( celt * sizeof( LPOLESTR ) );
        std::unique_ptr<LPOLESTR, MallocaDeleter<LPOLESTR>> elementsPtr( oleStrings );
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
    void EnumString::All( std::vector<WideString>& result ) const
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

        std::vector<WideString> GetSupportedKnownInterfaces(IUnknown* unknown)
        {
            std::vector<WideString> result;
            if (unknown == nullptr)
            {
                return result;
            }
            if (Com::Internal::CheckIfInterfaceIsSupported<IUnknown>(unknown)) { result.emplace_back(WideString(L"IUnknown")); }

#define X( Itf, BaseItf ) if (Com::Internal::CheckIfInterfaceIsSupported<Itf>(unknown)) { result.emplace_back(WideString(L#Itf)); }
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
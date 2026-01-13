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

using namespace Harlinn::Common::Core;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( )
        {
        }
        ~LocalFixture( )
        {
        }
    };

    class ObjectImpl : public Com::ObjectBase<ObjectImpl, IEnumString, IEnumVARIANT>
    {
        int value_ = 0;
    public:
        using ObjectBaseType = Com::ObjectBase<ObjectImpl, IEnumString, IEnumVARIANT>;
        /*
        using ObjectBaseType::QueryInterface;
        using ObjectBaseType::AddRef;
        using ObjectBaseType::Release;
        */

        virtual HRESULT __stdcall Next( ULONG celt, LPOLESTR* rgelt, ULONG* pceltFetched )
        {
            if ( !rgelt )
            {
                return E_POINTER;
            }
            for ( ULONG i = 0; i < celt; i++ )
            {
                value_++;
                auto text = Format( L"{}", value_ );
                auto textSize = text.size( );
                LPOLESTR ptr = reinterpret_cast<LPOLESTR>(CoTaskMemAlloc( (textSize + 1)*sizeof(OLECHAR) ));
                if ( !ptr )
                {
                    for ( ULONG j = 0; j < i; j++ )
                    {
                        CoTaskMemFree( rgelt[j] );
                    }
                    return E_OUTOFMEMORY;
                }
                wmemcpy_s( ptr, textSize + 1, text.c_str(), textSize + 1 );
                rgelt[i] = ptr;
            }
            if ( pceltFetched )
            {
                *pceltFetched = celt;
            }
            return S_OK;
        }

        virtual HRESULT __stdcall Next( ULONG celt, VARIANT* rgVar, ULONG* pCeltFetched )
        {
            if ( !rgVar )
            {
                return E_POINTER;
            }
            for ( ULONG i = 0; i < celt; i++ )
            {
                value_++;
                VariantInit( &rgVar[i] );
                rgVar[i].vt = VT_I4;
                rgVar[i].intVal = value_;
            }
            if ( pCeltFetched )
            {
                *pCeltFetched = celt;
            }
            return S_OK;
        }

        virtual HRESULT __stdcall Skip( ULONG celt )
        {
            value_ += static_cast<int>( celt );
            return S_OK;
        }

        virtual HRESULT __stdcall Reset( void )
        {
            value_ = 0;
            return S_OK;
        }

        virtual HRESULT __stdcall Clone( __RPC__deref_out_opt IEnumString** ppenum )
        {
            return E_NOTIMPL;
        }

        virtual HRESULT STDMETHODCALLTYPE Clone( __RPC__deref_out_opt IEnumVARIANT** ppEnum )
        {
            return E_NOTIMPL;
        }
    };


}

BOOST_FIXTURE_TEST_SUITE( ComImplTests, LocalFixture )

// --run_test=ComImplTests/ObjectImplTest
BOOST_AUTO_TEST_CASE( ObjectImplTest )
{

    auto* impl = new Com::HeapObject<ObjectImpl>( );

    IEnumString* pEnumString = nullptr;
    IEnumVARIANT* pEnumVARIANT = nullptr;
    IUnknown* pUnknown = nullptr;
    IEnumUnknown* pEnumUnknown = nullptr;

    auto hr = impl->QueryInterface( __uuidof( IEnumString ), reinterpret_cast<void**>( &pEnumString ) );
    BOOST_CHECK( hr == S_OK );
    BOOST_CHECK( pEnumString != nullptr );
    for ( int i = 0; i < 5; i++ )
    {
        LPOLESTR str = nullptr;
        ULONG retrieved = 0;
        hr = pEnumString->Next( 1, &str, &retrieved );
        BOOST_CHECK( hr == S_OK );
        BOOST_CHECK( retrieved == 1 );
        auto expectedText = Format( L"{}", i + 1 );
        BOOST_CHECK( expectedText == str );
        CoTaskMemFree( str );
    }
    pEnumString->Release( );

    hr = impl->QueryInterface( __uuidof( IEnumVARIANT ), reinterpret_cast<void**>( &pEnumVARIANT ) );
    BOOST_CHECK( hr == S_OK );
    BOOST_CHECK( pEnumVARIANT != nullptr );
    for ( int i = 0; i < 5; i++ )
    {
        VARIANT value{};
        ULONG retrieved = 0;
        hr = pEnumVARIANT->Next( 1, &value, &retrieved );
        BOOST_CHECK( hr == S_OK );
        BOOST_CHECK( retrieved == 1 );
        auto expectedValue = i + 6;
        BOOST_CHECK( value.vt == VT_I4 );
        BOOST_CHECK( value.intVal == expectedValue );
        VariantClear( &value );
    }
    pEnumVARIANT->Release( );

    hr = impl->QueryInterface( __uuidof( IUnknown ), reinterpret_cast<void**>( &pUnknown ) );
    BOOST_CHECK( hr == S_OK );
    BOOST_CHECK( pUnknown != nullptr );

    hr = impl->QueryInterface( __uuidof( IEnumVARIANT ), reinterpret_cast<void**>( &pEnumVARIANT ) );
    pUnknown->Release( );
    pEnumVARIANT->Reset( );
    BOOST_CHECK( hr == S_OK );
    BOOST_CHECK( pEnumVARIANT != nullptr );
    for ( int i = 0; i < 5; i++ )
    {
        VARIANT value{};
        ULONG retrieved = 0;
        hr = pEnumVARIANT->Next( 1, &value, &retrieved );
        BOOST_CHECK( hr == S_OK );
        BOOST_CHECK( retrieved == 1 );
        auto expectedValue = i + 1;
        BOOST_CHECK( value.vt == VT_I4 );
        BOOST_CHECK( value.intVal == expectedValue );
        VariantClear( &value );
    }
    pEnumVARIANT->Release( );
    
    hr = impl->QueryInterface( __uuidof( IEnumUnknown ), reinterpret_cast<void**>( &pEnumUnknown ) );
    BOOST_CHECK( hr == E_NOINTERFACE );
    BOOST_CHECK( pEnumUnknown == nullptr );

    delete impl;
}

BOOST_AUTO_TEST_SUITE_END( )
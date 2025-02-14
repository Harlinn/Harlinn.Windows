#pragma once
#ifndef HARLINN_WINDOWS_HWICODECAPI_H_
#define HARLINN_WINDOWS_HWICODECAPI_H_
/*
   Copyright 2024-2025 Espen Harlinn

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

#include <HWDef.h>
#include <HCCCom.h>

namespace Harlinn::Windows::Media
{
    /// <summary>
    /// The CodecAPI class sets and retrieves settings on an encoder or decoder filter.
    /// </summary>
    class CodecAPI : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(CodecAPI, Unknown, ICodecAPI, IUnknown)
    public:
        /// <summary>
        /// The IsSupported method queries whether a codec supports a given property.
        /// </summary>
        /// <param name="api">
        /// Pointer to a GUID that specifies the property to query. 
        /// </param>
        /// <returns></returns>
        bool IsSupported( const Guid* api) const
        {
            auto itf = GetInterface( );
            auto hr = itf->IsSupported( reinterpret_cast< const GUID* >( api ) );
            HCC_COM_CHECK_HRESULT2( hr, itf );
            return hr == S_OK;
        }

        void IsModifiable( const Guid* api) const
        {
            auto itf = GetInterface( );
            auto hr = itf->IsModifiable( reinterpret_cast<const GUID*>(api) );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }

        void GetParameterRange( const Guid* api, VARIANT* valueMin, VARIANT* valueMax, VARIANT* steppingDelta) const
        {
            auto itf = GetInterface( );
            auto hr = itf->GetParameterRange( reinterpret_cast< const GUID* >( api ), valueMin, valueMax, steppingDelta );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }

        void GetParameterValues( const Guid* api, VARIANT** values, ULONG* valuesCount) const
        {
            auto itf = GetInterface( );
            auto hr = itf->GetParameterValues( reinterpret_cast< const GUID* >( api ), values, valuesCount );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }

        void GetDefaultValue( const Guid* api, VARIANT* value) const
        {
            auto itf = GetInterface( );
            auto hr = itf->GetDefaultValue( reinterpret_cast< const GUID* >( api ), value );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }

        void GetValue( const Guid* api, VARIANT* value) const
        {
            auto itf = GetInterface( );
            auto hr = itf->GetValue( reinterpret_cast< const GUID* >( api ), value );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }

        void SetValue( const Guid* api, VARIANT* value) const
        {
            auto itf = GetInterface( );
            auto hr = itf->SetValue( reinterpret_cast< const GUID* >( api ), value );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }

        void RegisterForEvent( const Guid* api, LONG_PTR userData) const
        {
            auto itf = GetInterface( );
            auto hr = itf->RegisterForEvent( reinterpret_cast< const GUID* >( api ), userData );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }

        void UnregisterForEvent( const Guid* api) const
        {
            auto itf = GetInterface( );
            auto hr = itf->UnregisterForEvent( reinterpret_cast< const GUID* >( api ) );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }

        void SetAllDefaults( ) const
        {
            auto itf = GetInterface( );
            auto hr = itf->SetAllDefaults( );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }

        void SetValueWithNotify( const Guid* api, VARIANT* value, Guid** changedParam, ULONG* changedParamCount) const
        {
            auto itf = GetInterface( );
            auto hr = itf->SetValueWithNotify( reinterpret_cast< const GUID* >( api ), value, reinterpret_cast< GUID** >( changedParam ), changedParamCount );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }

        void SetAllDefaultsWithNotify( Guid** changedParam, ULONG* changedParamCount) const
        {
            auto itf = GetInterface( );
            auto hr = itf->SetAllDefaultsWithNotify( reinterpret_cast< GUID** >( changedParam ), changedParamCount );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }

        void GetAllSettings( IStream* stream) const
        {
            auto itf = GetInterface( );
            auto hr = itf->GetAllSettings( stream );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }

        void SetAllSettings( IStream* stream) const
        {
            auto itf = GetInterface( );
            auto hr = itf->SetAllSettings( stream );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }

        void SetAllSettingsWithNotify( IStream* stream, Guid** changedParam, ULONG* changedParamCount) const
        {
            auto itf = GetInterface( );
            auto hr = itf->SetAllSettingsWithNotify( stream, reinterpret_cast< GUID** >( changedParam ), changedParamCount );
            HCC_COM_CHECK_HRESULT2( hr, itf );
        }
    };
}


#endif

#pragma once
#ifndef HARLINN_WINDOWS_HWICODECAPI_H_
#define HARLINN_WINDOWS_HWICODECAPI_H_
/*
   Copyright 2024 Espen Harlinn

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

namespace Harlinn::Windows
{
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
            HCC_COM_CHECK_HRESULT( hr );
            return hr == S_OK;
        }

        void IsModifiable( const Guid* api) const
        {
        }

        void GetParameterRange( const Guid* api, VARIANT* valueMin, VARIANT* valueMax, VARIANT* steppingDelta) const
        {
        }

        void GetParameterValues( const Guid* api, VARIANT** values, ULONG* valuesCount) const
        {
        }

        void GetDefaultValue( const Guid* api, VARIANT* value) const
        {
        }

        void GetValue( const Guid* api, VARIANT* value) const
        {
        }

        void SetValue( const Guid* api, VARIANT* value) const
        {
        }

        void RegisterForEvent( const Guid* api, LONG_PTR userData) const
        {
        }

        void UnregisterForEvent( const Guid* api) const
        {
        }

        void SetAllDefaults( ) const
        {
        }

        void SetValueWithNotify( const GUID* api, VARIANT* value, GUID** changedParam, ULONG* changedParamCount) const
        {
        }

        void SetAllDefaultsWithNotify( GUID** changedParam, ULONG* changedParamCount) const
        {
        }

        void GetAllSettings( IStream* stream) const
        {
        }

        void SetAllSettings( IStream* stream) const
        {
        }

        void SetAllSettingsWithNotify( IStream* stream, GUID** changedParam, ULONG* changedParamCount) const
        {
        }
    };
}


#endif

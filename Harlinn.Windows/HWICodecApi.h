#pragma once
#ifndef HARLINN_WINDOWS_HWICODECAPI_H_
#define HARLINN_WINDOWS_HWICODECAPI_H_

#include <HWDef.h>
#include <HCCCom.h>

namespace Harlinn::Windows
{
    class CodecAPI : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(CodecAPI, Unknown, ICodecAPI, IUnknown)
    public:
        void IsSupported( const Guid* api) const
        {
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

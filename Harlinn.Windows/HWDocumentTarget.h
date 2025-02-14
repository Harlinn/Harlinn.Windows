#pragma once
#ifndef HARLINN_WINDOWS_HWDOCUMENTTARGET_H_
#define HARLINN_WINDOWS_HWDOCUMENTTARGET_H_
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
#include <HCCCOM.h>
#include <HCCObj.h>
#include <HCCException.h>

#include <documenttarget.h>

namespace Harlinn::Windows::DocumentTarget
{
    /// <summary>
    /// 
    /// </summary>
    class PrintDocumentPackageTarget : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( PrintDocumentPackageTarget, Unknown, IPrintDocumentPackageTarget, IUnknown )
    public:
        void GetPackageTargetTypes( UINT32* targetCount, GUID** targetTypes ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetPackageTargetTypes( targetCount, targetTypes );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void GetPackageTarget( REFGUID guidTargetType, REFIID riid, void** ppvTarget ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->GetPackageTarget( guidTargetType, riid, ppvTarget );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }

        void Cancel( ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->Cancel( );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// 
    /// </summary>
    class PrintDocumentPackageStatusEvent : public Dispatch
    {
    public:
        using Base = Dispatch;

        HCC_COM_STANDARD_METHODS_IMPL( PrintDocumentPackageStatusEvent, Dispatch, IPrintDocumentPackageStatusEvent, IDispatch )
    public:
        void PackageStatusUpdated( PrintDocumentPackageStatus* packageStatus ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->PackageStatusUpdated( packageStatus );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

    /// <summary>
    /// 
    /// </summary>
    class PrintDocumentPackageTargetFactory : public Unknown
    {
    public:
        using Base = Unknown;

        HCC_COM_STANDARD_METHODS_IMPL( PrintDocumentPackageTargetFactory, Unknown, IPrintDocumentPackageTargetFactory, IUnknown )
    public:

        void CreateDocumentPackageTargetForPrintJob( LPCWSTR printerName, LPCWSTR jobName, IStream* jobOutputStream, IStream* jobPrintTicketStream, IPrintDocumentPackageTarget** docPackageTarget ) const
        {
            auto* pInterface = GetInterface( );
            auto hr = pInterface->CreateDocumentPackageTargetForPrintJob( printerName, jobName, jobOutputStream, jobPrintTicketStream, docPackageTarget );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
        }
    };

}


#endif

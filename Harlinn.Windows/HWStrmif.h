#pragma once
#ifndef HARLINN_WINDOWS_HWSTRMIF_H_
#define HARLINN_WINDOWS_HWSTRMIF_H_

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


#include "HWDef.h"
#include <HCCCom.h>
#include <HCCObj.h>
#include <strmif.h>
namespace Harlinn::Windows::DirectShow
{
    class CreateDevEnum : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(CreateDevEnum, Unknown, ICreateDevEnum, IUnknown)
    public:
        void CreateClassEnumerator(const Guid& deviceClassId, IEnumMoniker** enumMoniker, DWORD flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateClassEnumerator(deviceClassId, enumMoniker, flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class Pin : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Pin, Unknown, IPin, IUnknown)
    public:
        void Connect(IPin* receivePin, _In_opt_  const AM_MEDIA_TYPE* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Connect(receivePin, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ReceiveConnection( IPin* connector, const AM_MEDIA_TYPE* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ReceiveConnection(connector, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Disconnect( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Disconnect();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ConnectedTo( _Out_  IPin** pin) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ConnectedTo(pin);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ConnectionMediaType( _Out_  AM_MEDIA_TYPE* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ConnectionMediaType(mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void QueryPinInfo( _Out_  PIN_INFO* pinInfo) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueryPinInfo(pinInfo);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void QueryDirection( _Out_  PIN_DIRECTION* pinDirection) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueryDirection(pinDirection);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void QueryId( _Out_  LPWSTR* Id) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueryId(Id);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void QueryAccept( const AM_MEDIA_TYPE* pmt) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueryAccept(pmt);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EnumMediaTypes( _Out_  IEnumMediaTypes** ppEnum) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EnumMediaTypes(ppEnum);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void QueryInternalConnections( IPin** pins, ULONG* numberOfPins) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueryInternalConnections(pins, numberOfPins);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndOfStream( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndOfStream();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginFlush( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginFlush();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndFlush( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndFlush();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void NewSegment( REFERENCE_TIME startTime, REFERENCE_TIME stopTime, double rate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NewSegment(startTime, stopTime, rate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class EnumPins : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(EnumPins, Unknown, IEnumPins, IUnknown)
    public:
        bool Next(ULONG numberOfItemsToRetrive, IPin** items, ULONG* numberOfFetchedItems) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Next(numberOfItemsToRetrive, items, numberOfFetchedItems);
            if (hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }
        std::optional<Pin> Next() const
        {
            IPin* itf = nullptr;
            if (Next(1, &itf, nullptr))
            {
                return { Pin(itf) };
            }
            return {};
        }


        bool Skip( ULONG numberOfItemsToSkip) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Skip(numberOfItemsToSkip);
            if (hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        void Reset( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Reset();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Clone( IEnumPins** clone) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Clone(clone);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class EnumMediaTypes : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(EnumMediaTypes, Unknown, IEnumMediaTypes, IUnknown)
    public:
        bool Next(ULONG numberOfItemsToRetrive, AM_MEDIA_TYPE** items, ULONG* numberOfFetchedItems) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Next(numberOfItemsToRetrive, items, numberOfFetchedItems);
            if (hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        bool Skip(ULONG numberOfItemsToSkip) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Skip(numberOfItemsToSkip);
            if (hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        void Reset() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Reset();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Clone(IEnumMediaTypes** clone) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Clone(clone);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class FilterGraph : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(FilterGraph, Unknown, IFilterGraph, IUnknown)
    public:
        void AddFilter( IBaseFilter* filter, LPCWSTR name) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddFilter(filter, name);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RemoveFilter( IBaseFilter* filter) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveFilter(filter);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EnumFilters( _Out_  IEnumFilters** enumFilters) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EnumFilters(enumFilters);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void FindFilterByName( LPCWSTR name, _Out_  IBaseFilter** filter) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->FindFilterByName(name, filter);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ConnectDirect( IPin* pinOut, IPin* pinIn, _In_opt_  const AM_MEDIA_TYPE* mediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ConnectDirect(pinOut, pinIn, mediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Reconnect( IPin* pin) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Reconnect(pin);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Disconnect( IPin* pin) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Disconnect(pin);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetDefaultSyncSource( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDefaultSyncSource();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class EnumFilters : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(EnumFilters, Unknown, IEnumFilters, IUnknown)
    public:
        void Next(ULONG cFilters, IBaseFilter** ppFilter, _Out_opt_  ULONG* pcFetched) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Next(cFilters, ppFilter, pcFetched);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Skip( ULONG cFilters) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Skip(cFilters);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Reset( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Reset();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Clone(_Out_  IEnumFilters** ppEnum) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Clone(ppEnum);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MediaFilter : public Persist
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MediaFilter, Persist, IMediaFilter, IPersist)
    public:
        void Stop() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Stop();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Pause( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Pause();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Run( REFERENCE_TIME tStart) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Run(tStart);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetState( DWORD dwMilliSecsTimeout, _Out_  FILTER_STATE* State) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetState(dwMilliSecsTimeout, State);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetSyncSource( _In_opt_  IReferenceClock* pClock) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSyncSource(pClock);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSyncSource( _Outptr_result_maybenull_  IReferenceClock** pClock) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSyncSource(pClock);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class BaseFilter : public MediaFilter
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(BaseFilter, MediaFilter, IBaseFilter, IMediaFilter)
    public:
        void EnumPins( _Out_  IEnumPins** ppEnum) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EnumPins(ppEnum);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void FindPin( LPCWSTR Id, _Out_  IPin** ppPin) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->FindPin(Id, ppPin);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void QueryFilterInfo( _Out_  FILTER_INFO* pInfo) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueryFilterInfo(pInfo);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void JoinFilterGraph( _In_opt_  IFilterGraph* pGraph, _In_opt_  LPCWSTR pName) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->JoinFilterGraph(pGraph, pName);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void QueryVendorInfo( _Out_  LPWSTR* pVendorInfo) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueryVendorInfo(pVendorInfo);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class ReferenceClock : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ReferenceClock, Unknown, IReferenceClock, IUnknown)
    public:
        void GetTime( _Out_  REFERENCE_TIME* pTime) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTime(pTime);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AdviseTime( REFERENCE_TIME baseTime, REFERENCE_TIME streamTime, HEVENT hEvent, DWORD_PTR* pdwAdviseCookie) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AdviseTime(baseTime, streamTime, hEvent, pdwAdviseCookie);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AdvisePeriodic( REFERENCE_TIME startTime, REFERENCE_TIME periodTime, HSEMAPHORE hSemaphore, _Out_  DWORD_PTR* pdwAdviseCookie) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AdvisePeriodic(startTime, periodTime, hSemaphore, pdwAdviseCookie);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Unadvise( DWORD_PTR dwAdviseCookie) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Unadvise(dwAdviseCookie);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class ReferenceClockTimerControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ReferenceClockTimerControl, Unknown, IReferenceClockTimerControl, IUnknown)
    public:
        void SetDefaultTimerResolution(REFERENCE_TIME timerResolution) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDefaultTimerResolution(timerResolution);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDefaultTimerResolution( _Out_  REFERENCE_TIME* pTimerResolution) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDefaultTimerResolution(pTimerResolution);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class ReferenceClock2 : public ReferenceClock
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ReferenceClock2, ReferenceClock, IReferenceClock2, IReferenceClock)
    public:

    };

    class MediaSample : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MediaSample, Unknown, IMediaSample, IUnknown)
    public:
        void GetPointer(BYTE** ppBuffer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPointer(ppBuffer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        long GetSize( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetSize();
        }

        void GetTime( _Out_  REFERENCE_TIME* pTimeStart, _Out_  REFERENCE_TIME* pTimeEnd) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTime(pTimeStart, pTimeEnd);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetTime( _In_opt_  REFERENCE_TIME* pTimeStart, _In_opt_  REFERENCE_TIME* pTimeEnd) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTime(pTimeStart, pTimeEnd);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        bool IsSyncPoint( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsSyncPoint();
            if (hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        void SetSyncPoint( BOOL bIsSyncPoint) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSyncPoint(bIsSyncPoint);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        bool IsPreroll( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsPreroll();
            if (hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        void SetPreroll( BOOL bIsPreroll) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPreroll(bIsPreroll);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        long GetActualDataLength( ) const
        {
            InterfaceType* pInterface = GetInterface();
            return pInterface->GetActualDataLength();
        }

        void SetActualDataLength( long actualDataLength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetActualDataLength(actualDataLength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMediaType( _Out_  AM_MEDIA_TYPE** ppMediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMediaType(ppMediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetMediaType( _In_  AM_MEDIA_TYPE* pMediaType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMediaType(pMediaType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        bool IsDiscontinuity( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsDiscontinuity();
            if (hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        void SetDiscontinuity( BOOL bDiscontinuity) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDiscontinuity(bDiscontinuity);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMediaTime( _Out_  LONGLONG* pTimeStart, _Out_  LONGLONG* pTimeEnd) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMediaTime(pTimeStart, pTimeEnd);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetMediaTime( _In_opt_  LONGLONG* pTimeStart, _In_opt_  LONGLONG* pTimeEnd) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMediaTime(pTimeStart, pTimeEnd);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MediaSample2 : public MediaSample
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MediaSample2, MediaSample, IMediaSample2, IMediaSample)
    public:
        void GetProperties(DWORD cbProperties, BYTE* pbProperties) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProperties(cbProperties, pbProperties);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetProperties( DWORD cbProperties, const BYTE* pbProperties) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetProperties(cbProperties, pbProperties);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MediaSample2Config : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MediaSample2Config, Unknown, IMediaSample2Config, IUnknown)
    public:
        void GetSurface(__RPC__deref_out_opt IUnknown** ppDirect3DSurface9) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSurface(ppDirect3DSurface9);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MemAllocator : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MemAllocator, Unknown, IMemAllocator, IUnknown)
    public:
        void SetProperties(_In_  ALLOCATOR_PROPERTIES* pRequest, _Out_  ALLOCATOR_PROPERTIES* pActual) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetProperties(pRequest, pActual);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetProperties( _Out_  ALLOCATOR_PROPERTIES* pProps) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProperties(pProps);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Commit( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Commit();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Decommit( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Decommit();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetBuffer( _Out_  IMediaSample** ppBuffer, _In_opt_  REFERENCE_TIME* pStartTime, _In_opt_  REFERENCE_TIME* pEndTime, DWORD dwFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetBuffer(ppBuffer, pStartTime, pEndTime, dwFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ReleaseBuffer( IMediaSample* pBuffer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ReleaseBuffer(pBuffer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MemAllocatorCallbackTemp : public MemAllocator
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MemAllocatorCallbackTemp, MemAllocator, IMemAllocatorCallbackTemp, IMemAllocator)
    public:
        void SetNotify(IMemAllocatorNotifyCallbackTemp* pNotify) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetNotify(pNotify);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetFreeCount( _Out_  LONG* plBuffersFree) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFreeCount(plBuffersFree);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MemAllocatorNotifyCallbackTemp : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MemAllocatorNotifyCallbackTemp, Unknown, IMemAllocatorNotifyCallbackTemp, IUnknown)
    public:
        void NotifyRelease() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyRelease();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

    };

    class MemInputPin : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MemInputPin, Unknown, IMemInputPin, IUnknown)
    public:
        void GetAllocator( _Out_  IMemAllocator** ppAllocator) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAllocator(ppAllocator);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void NotifyAllocator( IMemAllocator* pAllocator, BOOL bReadOnly) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyAllocator(pAllocator, bReadOnly);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetAllocatorRequirements( _Out_  ALLOCATOR_PROPERTIES* pProps) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAllocatorRequirements(pProps);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Receive( IMediaSample* pSample) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Receive(pSample);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ReceiveMultiple( IMediaSample** pSamples, long nSamples, _Out_  long* nSamplesProcessed) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ReceiveMultiple(pSamples, nSamples, nSamplesProcessed);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        bool ReceiveCanBlock( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ReceiveCanBlock();
            if (hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }
    };

    class AMovieSetup : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMovieSetup, Unknown, IAMovieSetup, IUnknown)
    public:
        void Register() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Register();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Unregister( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Unregister();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MediaSeeking : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MediaSeeking, Unknown, IMediaSeeking, IUnknown)
    public:
        void GetCapabilities( _Out_  DWORD* pCapabilities) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCapabilities(pCapabilities);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CheckCapabilities( DWORD* pCapabilities) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckCapabilities(pCapabilities);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        bool IsFormatSupported( const Guid* pFormat) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsFormatSupported((const GUID*)pFormat);
            if (hr != S_OK && hr != S_FALSE && hr != E_NOTIMPL)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        void QueryPreferredFormat( _Out_  Guid* pFormat) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueryPreferredFormat((GUID *) pFormat);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetTimeFormat( _Out_  Guid* pFormat) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetTimeFormat((GUID*)pFormat);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        bool IsUsingTimeFormat( const Guid* pFormat) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsUsingTimeFormat((const GUID *)pFormat);
            if (hr != S_OK && hr != S_FALSE && hr != E_NOTIMPL)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        void SetTimeFormat( const Guid* pFormat) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTimeFormat((const GUID *) pFormat);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDuration( _Out_  LONGLONG* pDuration) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDuration(pDuration);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStopPosition( _Out_  LONGLONG* pStop) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStopPosition(pStop);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCurrentPosition( _Out_  LONGLONG* pCurrent) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurrentPosition(pCurrent);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ConvertTimeFormat( _Out_  LONGLONG* pTarget, _In_opt_  const Guid* pTargetFormat, LONGLONG Source, _In_opt_  const Guid* pSourceFormat) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ConvertTimeFormat(pTarget, (const GUID *) pTargetFormat, Source, (const GUID*) pSourceFormat);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPositions( _Inout_opt_  LONGLONG* pCurrent, DWORD dwCurrentFlags, _Inout_opt_  LONGLONG* pStop, DWORD dwStopFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPositions(pCurrent, dwCurrentFlags, pStop, dwStopFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPositions( _Out_opt_  LONGLONG* pCurrent, _Out_opt_  LONGLONG* pStop) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPositions(pCurrent, pStop);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetAvailable( _Out_opt_  LONGLONG* pEarliest, _Out_opt_  LONGLONG* pLatest) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAvailable(pEarliest, pLatest);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetRate( double dRate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRate(dRate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetRate( _Out_  double* pdRate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetRate(pdRate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetPreroll( _Out_  LONGLONG* pllPreroll) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPreroll(pllPreroll);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class CodecAPI : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(CodecAPI, Unknown, ICodecAPI, IUnknown)
    public:
        bool IsSupported( const Guid* api) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsSupported((const GUID *) api);
            if (hr != S_OK && hr != S_FALSE && hr != E_NOTIMPL)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        bool IsModifiable( const Guid* api) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsModifiable((const GUID *) api);
            if (hr != S_OK && hr != S_FALSE && hr != E_NOTIMPL)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetParameterRange( const Guid* api, _Out_  VARIANT* valueMin, _Out_  VARIANT* valueMax, _Out_  VARIANT* steppingDelta) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetParameterRange((const GUID*)api, valueMin, valueMax, steppingDelta);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetParameterValues( const Guid* api, VARIANT** values, _Out_  ULONG* valuesCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetParameterValues((const GUID*)api, values, valuesCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDefaultValue( const Guid* api, _Out_  VARIANT* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDefaultValue((const GUID *)api, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetValue( const Guid* api, _Out_  VARIANT* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetValue((const GUID*)api, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetValue( const GUID* api, _In_  VARIANT* value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetValue((const GUID*) api, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetValue( const GUID& api, bool value ) const
        {
            Variant var( value );
            SetValue( &api, &var );
        }

        void RegisterForEvent( const Guid* api, LONG_PTR userData) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterForEvent((const GUID*)api, userData);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnregisterForEvent( const Guid* api) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnregisterForEvent((const GUID*) api);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAllDefaults( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAllDefaults();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetValueWithNotify( const Guid* api, VARIANT* value, Guid** changedParam, _Out_  ULONG* changedParamCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetValueWithNotify((const GUID *)api, value, (GUID**)changedParam, changedParamCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAllDefaultsWithNotify( Guid** changedParam, _Out_  ULONG* changedParamCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAllDefaultsWithNotify((GUID**)changedParam, changedParamCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetAllSettings( IStream* stream) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAllSettings(stream);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAllSettings( IStream* stream) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAllSettings(stream);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAllSettingsWithNotify( IStream* stream, Guid** changedParam, _Out_  ULONG* changedParamCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAllSettingsWithNotify(stream, (GUID**)changedParam, changedParamCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class EnumRegFilters : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(EnumRegFilters, Unknown, IEnumRegFilters, IUnknown)
    public:
        bool Next(ULONG cFilters, REGFILTER** apRegFilter, _Inout_opt_  ULONG* pcFetched) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Next(cFilters, apRegFilter, pcFetched);
            if (hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        bool Skip( ULONG cFilters) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Skip(cFilters);
            if (hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }

        void Reset( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Reset();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Clone( _Out_  IEnumRegFilters** ppEnum) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Clone(ppEnum);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class FilterMapper : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(FilterMapper, Unknown, IFilterMapper, IUnknown)
    public:
        void RegisterFilter( const Guid& clsid, LPCWSTR Name, DWORD dwMerit) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterFilter(clsid, Name, dwMerit);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RegisterFilterInstance( const Guid& clsid, LPCWSTR Name, _Out_  Guid* MRId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterFilterInstance(clsid, Name, (GUID*)MRId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RegisterPin( const Guid& Filter, LPCWSTR Name, BOOL bRendered, BOOL bOutput, BOOL bZero, BOOL bMany, const Guid& ConnectsToFilter, LPCWSTR ConnectsToPin) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterPin(Filter, Name, bRendered, bOutput, bZero, bMany, ConnectsToFilter, ConnectsToPin);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RegisterPinType( const Guid& clsFilter, LPCWSTR strName, const Guid& clsMajorType, const Guid& clsSubType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterPinType(clsFilter, strName, clsMajorType, clsSubType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnregisterFilter( const Guid& Filter) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnregisterFilter(Filter);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnregisterFilterInstance( const Guid& MRId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnregisterFilterInstance(MRId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnregisterPin( const Guid& Filter, LPCWSTR Name) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnregisterPin(Filter, Name);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EnumMatchingFilters( _Out_  IEnumRegFilters** ppEnum, DWORD dwMerit, BOOL bInputNeeded, const Guid& clsInMaj, const Guid& clsInSub, BOOL bRender, BOOL bOututNeeded, const Guid& clsOutMaj, const Guid& clsOutSub) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EnumMatchingFilters(ppEnum, dwMerit, bInputNeeded, clsInMaj, clsInSub, bRender, bOututNeeded, clsOutMaj, clsOutSub);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class FilterMapper2 : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(FilterMapper2, Unknown, IFilterMapper2, IUnknown)
    public:
        void CreateCategory( const Guid& clsidCategory, DWORD dwCategoryMerit, LPCWSTR Description) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateCategory(clsidCategory, dwCategoryMerit, Description);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnregisterFilter( const Guid* pclsidCategory, LPCOLESTR szInstance, const Guid& Filter) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnregisterFilter((const GUID*) pclsidCategory, szInstance, Filter);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RegisterFilter( const Guid& clsidFilter, LPCWSTR Name, _Inout_opt_  IMoniker** ppMoniker, const Guid* pclsidCategory, _In_  LPCOLESTR szInstance, const REGFILTER2* prf2) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterFilter(clsidFilter, Name, ppMoniker, (const GUID*) pclsidCategory, szInstance, prf2);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EnumMatchingFilters( _Out_  IEnumMoniker** ppEnum, DWORD dwFlags, BOOL bExactMatch, DWORD dwMerit, BOOL bInputNeeded, DWORD cInputTypes, const Guid* pInputTypes, _In_opt_  const REGPINMEDIUM* pMedIn, _In_opt_  const Guid* pPinCategoryIn, BOOL bRender, BOOL bOutputNeeded, DWORD cOutputTypes, const Guid* pOutputTypes, _In_opt_  const REGPINMEDIUM* pMedOut, _In_opt_  const Guid* pPinCategoryOut) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EnumMatchingFilters(ppEnum, dwFlags, bExactMatch, dwMerit, bInputNeeded, cInputTypes, (const GUID*) pInputTypes, pMedIn, (const GUID *)pPinCategoryIn, bRender, bOutputNeeded, cOutputTypes, (const GUID*)pOutputTypes, pMedOut, (const GUID*)pPinCategoryOut);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class FilterMapper3 : public FilterMapper2
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(FilterMapper3, FilterMapper2, IFilterMapper3, IFilterMapper2)
    public:
        void GetICreateDevEnum(_Out_  ICreateDevEnum** ppEnum) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetICreateDevEnum(ppEnum);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class QualityControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(QualityControl, Unknown, IQualityControl, IUnknown)
    public:
        void Notify(IBaseFilter* pSelf, Quality q) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Notify(pSelf, q);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetSink( IQualityControl* piqc) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSink(piqc);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class OverlayNotify : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(OverlayNotify, Unknown, IOverlayNotify, IUnknown)
    public:
        void OnPaletteChange( DWORD dwColors, const PALETTEENTRY* pPalette) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnPaletteChange(dwColors, pPalette);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnClipChange( const RECT* pSourceRect, const RECT* pDestinationRect, const RGNDATA* pRgnData) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnClipChange(pSourceRect, pDestinationRect, pRgnData);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnColorKeyChange( const COLORKEY* pColorKey) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnColorKeyChange(pColorKey);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnPositionChange( const RECT* pSourceRect, const RECT* pDestinationRect) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnPositionChange(pSourceRect, pDestinationRect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class OverlayNotify2 : public OverlayNotify
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(OverlayNotify2, OverlayNotify, IOverlayNotify2, IOverlayNotify)
    public:
        void OnDisplayChange(HMONITOR hMonitor) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnDisplayChange(hMonitor);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class Overlay : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Overlay, Unknown, IOverlay, IUnknown)
    public:
        void GetPalette( _Inout_  DWORD* pdwColors, PALETTEENTRY** ppPalette) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetPalette(pdwColors, ppPalette);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetPalette( DWORD dwColors, PALETTEENTRY* pPalette) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetPalette(dwColors, pPalette);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDefaultColorKey( _Out_  COLORKEY* pColorKey) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDefaultColorKey(pColorKey);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetColorKey( _Out_  COLORKEY* pColorKey) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetColorKey(pColorKey);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetColorKey( COLORKEY* pColorKey) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetColorKey(pColorKey);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetWindowHandle( _Out_  HWND* pHwnd) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetWindowHandle(pHwnd);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetClipList( _Out_  RECT* pSourceRect, _Out_  RECT* pDestinationRect, _Out_  RGNDATA** ppRgnData) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetClipList(pSourceRect, pDestinationRect, ppRgnData);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoPosition( _Out_  RECT* pSourceRect, _Out_  RECT* pDestinationRect) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoPosition(pSourceRect, pDestinationRect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Advise( IOverlayNotify* pOverlayNotify, DWORD dwInterests) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Advise(pOverlayNotify, dwInterests);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Unadvise( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Unadvise();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MediaEventSink : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MediaEventSink, Unknown, IMediaEventSink, IUnknown)
    public:
        void Notify(long EventCode, LONG_PTR EventParam1, LONG_PTR EventParam2) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Notify(EventCode, EventParam1, EventParam2);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class FileSourceFilter : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(FileSourceFilter, Unknown, IFileSourceFilter, IUnknown)
    public:
        void Load(LPCOLESTR pszFileName, _In_opt_  const AM_MEDIA_TYPE* pmt) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Load(pszFileName, pmt);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCurFile( _Out_  LPOLESTR* ppszFileName, _Out_opt_  AM_MEDIA_TYPE* pmt) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurFile(ppszFileName, pmt);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class FileSinkFilter : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(FileSinkFilter, Unknown, IFileSinkFilter, IUnknown)
    public:
        void SetFileName( LPCOLESTR pszFileName, _In_opt_  const AM_MEDIA_TYPE* pmt) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetFileName(pszFileName, pmt);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCurFile( _Out_  LPOLESTR* ppszFileName, _Out_  AM_MEDIA_TYPE* pmt) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurFile(ppszFileName, pmt);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class FileSinkFilter2 : public FileSinkFilter
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(FileSinkFilter2, FileSinkFilter, IFileSinkFilter2, IFileSinkFilter)
    public:
        void SetMode(DWORD dwFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMode(dwFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMode( _Out_  DWORD* pdwFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMode(pdwFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class GraphBuilder : public FilterGraph
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(GraphBuilder, FilterGraph, IGraphBuilder, IFilterGraph)
    public:
        void Connect( IPin* ppinOut, IPin* ppinIn) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Connect(ppinOut, ppinIn);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Render( IPin* ppinOut) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Render(ppinOut);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RenderFile( LPCWSTR lpcwstrFile, _In_opt_  LPCWSTR lpcwstrPlayList) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RenderFile(lpcwstrFile, lpcwstrPlayList);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AddSourceFilter( LPCWSTR lpcwstrFileName, _In_opt_  LPCWSTR lpcwstrFilterName, _Out_  IBaseFilter** ppFilter) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddSourceFilter(lpcwstrFileName, lpcwstrFilterName, ppFilter);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetLogFile( DWORD_PTR hFile) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetLogFile(hFile);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Abort( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Abort();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        bool ShouldOperationContinue( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ShouldOperationContinue();
            if (hr != S_FALSE)
            {
                HCC_COM_CHECK_HRESULT2(hr, pInterface);
            }
            return hr == S_OK;
        }
    };

    class CaptureGraphBuilder : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(CaptureGraphBuilder, Unknown, ICaptureGraphBuilder, IUnknown)
    public:
        void SetFiltergraph( IGraphBuilder* pfg) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetFiltergraph(pfg);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetFiltergraph( _Out_  IGraphBuilder** ppfg) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFiltergraph(ppfg);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetOutputFileName( const Guid* pType, LPCOLESTR lpstrFile, _Out_  IBaseFilter** ppf, _Out_  IFileSinkFilter** ppSink) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOutputFileName((const GUID*)pType, lpstrFile, ppf, ppSink);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void FindInterface( _In_opt_  const Guid* pCategory, IBaseFilter* pf, const Guid& riid, _Out_  void** ppint) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->FindInterface((const GUID*)pCategory, pf, riid, ppint);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RenderStream( _In_opt_  const Guid* pCategory, IUnknown* pSource, IBaseFilter* pfCompressor, IBaseFilter* pfRenderer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RenderStream((const GUID*)pCategory, pSource, pfCompressor, pfRenderer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ControlStream( _In_opt_  const Guid* pCategory, IBaseFilter* pFilter, REFERENCE_TIME* pstart, REFERENCE_TIME* pstop, WORD wStartCookie, WORD wStopCookie) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ControlStream((const GUID*)pCategory, pFilter, pstart, pstop, wStartCookie, wStopCookie);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AllocCapFile( LPCOLESTR lpstr, DWORDLONG dwlSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AllocCapFile(lpstr, dwlSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CopyCaptureFile( _In_  LPOLESTR lpwstrOld, _In_  LPOLESTR lpwstrNew, int fAllowEscAbort, IAMCopyCaptureFileProgress* pCallback) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CopyCaptureFile(lpwstrOld, lpwstrNew, fAllowEscAbort, pCallback);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMCopyCaptureFileProgress : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMCopyCaptureFileProgress, Unknown, IAMCopyCaptureFileProgress, IUnknown)
    public:
        void Progress(int iProgress) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Progress(iProgress);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class CaptureGraphBuilder2 : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(CaptureGraphBuilder2, Unknown, ICaptureGraphBuilder2, IUnknown)
    public:
        void SetFiltergraph( IGraphBuilder* pfg) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetFiltergraph(pfg);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetFiltergraph( _Out_  IGraphBuilder** ppfg) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFiltergraph(ppfg);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetOutputFileName( const Guid* pType, LPCOLESTR lpstrFile, _Outptr_  IBaseFilter** ppf, _Outptr_opt_  IFileSinkFilter** ppSink) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOutputFileName((const GUID*)pType, lpstrFile, ppf, ppSink);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void FindInterface( _In_opt_  const Guid* pCategory, _In_opt_  const Guid* pType, IBaseFilter* pf, const Guid& riid, _Out_  void** ppint) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->FindInterface((const GUID*)pCategory, (const GUID*) pType, pf, riid, ppint);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RenderStream( _In_opt_  const Guid* pCategory, const Guid* pType, IUnknown* pSource, IBaseFilter* pfCompressor, IBaseFilter* pfRenderer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RenderStream((const GUID*) pCategory, (const GUID*)pType, pSource, pfCompressor, pfRenderer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ControlStream( const Guid* pCategory, const Guid* pType, IBaseFilter* pFilter, _In_opt_  REFERENCE_TIME* pstart, _In_opt_  REFERENCE_TIME* pstop, WORD wStartCookie, WORD wStopCookie) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ControlStream((const GUID*)pCategory, (const GUID*)pType, pFilter, pstart, pstop, wStartCookie, wStopCookie);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AllocCapFile( LPCOLESTR lpstr, DWORDLONG dwlSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AllocCapFile(lpstr, dwlSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CopyCaptureFile( _In_  LPOLESTR lpwstrOld, _In_  LPOLESTR lpwstrNew, int fAllowEscAbort, IAMCopyCaptureFileProgress* pCallback) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CopyCaptureFile(lpwstrOld, lpwstrNew, fAllowEscAbort, pCallback);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void FindPin( IUnknown* pSource, PIN_DIRECTION pindir, _In_opt_  const Guid* pCategory, _In_opt_  const Guid* pType, BOOL fUnconnected, int num, _Out_  IPin** ppPin) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->FindPin(pSource, pindir, (const GUID*)pCategory, (const GUID*)pType, fUnconnected, num, ppPin);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class FilterGraph2 : public GraphBuilder
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(FilterGraph2, GraphBuilder, IFilterGraph2, IGraphBuilder)
    public:
        void AddSourceFilterForMoniker( IMoniker* pMoniker, IBindCtx* pCtx, LPCWSTR lpcwstrFilterName, _Out_  IBaseFilter** ppFilter) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddSourceFilterForMoniker(pMoniker, pCtx, lpcwstrFilterName, ppFilter);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ReconnectEx( IPin* ppin, _In_opt_  const AM_MEDIA_TYPE* pmt) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ReconnectEx(ppin, pmt);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RenderEx( IPin* pPinOut, DWORD dwFlags, _Reserved_  DWORD* pvContext = nullptr) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RenderEx(pPinOut, dwFlags, pvContext);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class FilterGraph3 : public FilterGraph2
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(FilterGraph3, FilterGraph2, IFilterGraph3, IFilterGraph2)
    public:
        void SetSyncSourceEx( _In_  IReferenceClock* pClockForMostOfFilterGraph, _In_  IReferenceClock* pClockForFilter, _In_  IBaseFilter* pFilter) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSyncSourceEx(pClockForMostOfFilterGraph, pClockForFilter, pFilter);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class StreamBuilder : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(StreamBuilder, Unknown, IStreamBuilder, IUnknown)
    public:
        void Render( IPin* ppinOut, IGraphBuilder* pGraph) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Render(ppinOut, pGraph);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Backout( IPin* ppinOut, IGraphBuilder* pGraph) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Backout(ppinOut, pGraph);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AsyncReader : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AsyncReader, Unknown, IAsyncReader, IUnknown)
    public:
        void RequestAllocator( IMemAllocator* pPreferred, _In_  ALLOCATOR_PROPERTIES* pProps, _Out_  IMemAllocator** ppActual) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RequestAllocator(pPreferred, pProps, ppActual);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Request( IMediaSample* pSample, DWORD_PTR dwUser) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Request(pSample, dwUser);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void WaitForNext( DWORD dwTimeout, _Out_opt_  IMediaSample** ppSample, _Out_  DWORD_PTR* pdwUser) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->WaitForNext(dwTimeout, ppSample, pdwUser);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SyncReadAligned( IMediaSample* pSample) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SyncReadAligned(pSample);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SyncRead( LONGLONG llPosition, LONG lLength, BYTE* pBuffer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SyncRead(llPosition, lLength, pBuffer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Length( _Out_  LONGLONG* pTotal, _Out_  LONGLONG* pAvailable) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Length(pTotal, pAvailable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginFlush( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginFlush();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndFlush( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndFlush();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class GraphVersion : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(GraphVersion, Unknown, IGraphVersion, IUnknown)
    public:
        void QueryVersion(_Out_  LONG* pVersion) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->QueryVersion(pVersion);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class ResourceConsumer : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ResourceConsumer, Unknown, IResourceConsumer, IUnknown)
    public:
        void AcquireResource(LONG idResource) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AcquireResource(idResource);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ReleaseResource( LONG idResource) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ReleaseResource(idResource);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

    };

    class ResourceManager : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ResourceManager, Unknown, IResourceManager, IUnknown)
    public:
        void Register( LPCWSTR pName, LONG cResource, _Out_  LONG* plToken) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Register(pName, cResource, plToken);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RegisterGroup( LPCWSTR pName, LONG cResource, LONG* palTokens, _Out_  LONG* plToken) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterGroup(pName, cResource, palTokens, plToken);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RequestResource( LONG idResource, IUnknown* pFocusObject, IResourceConsumer* pConsumer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RequestResource(idResource, pFocusObject, pConsumer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void NotifyAcquire( LONG idResource, IResourceConsumer* pConsumer, HRESULT hrOp) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyAcquire(idResource, pConsumer, hrOp);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void NotifyRelease( LONG idResource, IResourceConsumer* pConsumer, BOOL bStillWant) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyRelease(idResource, pConsumer, bStillWant);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CancelRequest( LONG idResource, IResourceConsumer* pConsumer) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CancelRequest(idResource, pConsumer);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetFocus( IUnknown* pFocusObject) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetFocus(pFocusObject);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ReleaseFocus( IUnknown* pFocusObject) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ReleaseFocus(pFocusObject);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DistributorNotify : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DistributorNotify, Unknown, IDistributorNotify, IUnknown)
    public:
        void Stop() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Stop();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Pause( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Pause();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Run( REFERENCE_TIME tStart) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Run(tStart);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetSyncSource( IReferenceClock* pClock) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSyncSource(pClock);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void NotifyGraphChange( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->NotifyGraphChange();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMStreamControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMStreamControl, Unknown, IAMStreamControl, IUnknown)
    public:
        void StartAt(_In_opt_  const REFERENCE_TIME* ptStart, DWORD dwCookie) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->StartAt(ptStart, dwCookie);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void StopAt( _In_opt_  const REFERENCE_TIME* ptStop, BOOL bSendExtra, DWORD dwCookie) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->StopAt(ptStop, bSendExtra, dwCookie);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInfo( _Out_  AM_STREAM_INFO* pInfo) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInfo(pInfo);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class SeekingPassThru : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(SeekingPassThru, Unknown, ISeekingPassThru, IUnknown)
    public:
        void Init(BOOL bSupportRendering, IPin* pPin) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Init(bSupportRendering, pPin);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMStreamConfig : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMStreamConfig, Unknown, IAMStreamConfig, IUnknown)
    public:
        void SetFormat( AM_MEDIA_TYPE* pmt) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetFormat(pmt);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetFormat( _Out_  AM_MEDIA_TYPE** ppmt) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFormat(ppmt);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetNumberOfCapabilities( _Out_  int* piCount, _Out_  int* piSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetNumberOfCapabilities(piCount, piSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetStreamCaps( int iIndex, _Out_  AM_MEDIA_TYPE** ppmt, _Out_  BYTE* pSCC) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetStreamCaps(iIndex, ppmt, pSCC);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class ConfigInterleaving : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ConfigInterleaving, Unknown, IConfigInterleaving, IUnknown)
    public:
        void put_Mode(InterleavingMode mode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_Mode(mode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_Mode( _Out_  InterleavingMode* pMode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_Mode(pMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_Interleaving( const REFERENCE_TIME* prtInterleave, const REFERENCE_TIME* prtPreroll) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_Interleaving(prtInterleave, prtPreroll);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_Interleaving( _Out_  REFERENCE_TIME* prtInterleave, _Out_  REFERENCE_TIME* prtPreroll) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_Interleaving(prtInterleave, prtPreroll);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class ConfigAviMux : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ConfigAviMux, Unknown, IConfigAviMux, IUnknown)
    public:
        void SetMasterStream(LONG iStream) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMasterStream(iStream);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMasterStream( _Out_  LONG* pStream) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMasterStream(pStream);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetOutputCompatibilityIndex( BOOL fOldIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOutputCompatibilityIndex(fOldIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetOutputCompatibilityIndex( _Out_  BOOL* pfOldIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetOutputCompatibilityIndex(pfOldIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMVideoCompression : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMVideoCompression, Unknown, IAMVideoCompression, IUnknown)
    public:
        void put_KeyFrameRate(long KeyFrameRate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_KeyFrameRate(KeyFrameRate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_KeyFrameRate( _Out_  long* pKeyFrameRate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_KeyFrameRate(pKeyFrameRate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_PFramesPerKeyFrame( long PFramesPerKeyFrame) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_PFramesPerKeyFrame(PFramesPerKeyFrame);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_PFramesPerKeyFrame( _Out_  long* pPFramesPerKeyFrame) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_PFramesPerKeyFrame(pPFramesPerKeyFrame);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_Quality( double Quality) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_Quality(Quality);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_Quality( _Out_  double* pQuality) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_Quality(pQuality);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_WindowSize( DWORDLONG WindowSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_WindowSize(WindowSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_WindowSize( _Out_  DWORDLONG* pWindowSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_WindowSize(pWindowSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetInfo( LPWSTR pszVersion, _Inout_opt_  int* pcbVersion, LPWSTR pszDescription, _Inout_opt_  int* pcbDescription, _Out_opt_  long* pDefaultKeyFrameRate, _Out_opt_  long* pDefaultPFramesPerKey, _Out_opt_  double* pDefaultQuality, _Out_opt_  long* pCapabilities) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetInfo(pszVersion, pcbVersion, pszDescription, pcbDescription, pDefaultKeyFrameRate, pDefaultPFramesPerKey, pDefaultQuality, pCapabilities);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OverrideKeyFrame( long FrameNumber) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OverrideKeyFrame(FrameNumber);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OverrideFrameSize( long FrameNumber, long Size) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OverrideFrameSize(FrameNumber, Size);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMVfwCaptureDialogs : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMVfwCaptureDialogs, Unknown, IAMVfwCaptureDialogs, IUnknown)
    public:
        void HasDialog(int iDialog) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->HasDialog(iDialog);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ShowDialog( int iDialog, HWND hwnd) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ShowDialog(iDialog, hwnd);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SendDriverMessage( int iDialog, int uMsg, long dw1, long dw2) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SendDriverMessage(iDialog, uMsg, dw1, dw2);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMVfwCompressDialogs : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMVfwCompressDialogs, Unknown, IAMVfwCompressDialogs, IUnknown)
    public:
        void ShowDialog( int iDialog, HWND hwnd) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ShowDialog(iDialog, hwnd);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetState( LPVOID pState, _Inout_  int* pcbState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetState(pState, pcbState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetState( LPVOID pState, int cbState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetState(pState, cbState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SendDriverMessage( int uMsg, long dw1, long dw2) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SendDriverMessage(uMsg, dw1, dw2);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMDroppedFrames : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMDroppedFrames, Unknown, IAMDroppedFrames, IUnknown)
    public:
        void GetNumDropped( _Out_  long* plDropped) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetNumDropped(plDropped);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetNumNotDropped( _Out_  long* plNotDropped) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetNumNotDropped(plNotDropped);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDroppedInfo( long lSize, _Out_  long* plArray, _Out_  long* plNumCopied) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDroppedInfo(lSize, plArray, plNumCopied);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetAverageFrameSize( _Out_  long* plAverageSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAverageFrameSize(plAverageSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMAudioInputMixer : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMAudioInputMixer, Unknown, IAMAudioInputMixer, IUnknown)
    public:
        void put_Enable( BOOL fEnable) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_Enable(fEnable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_Enable( _Out_  BOOL* pfEnable) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_Enable(pfEnable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_Mono( BOOL fMono) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_Mono(fMono);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_Mono( _Out_  BOOL* pfMono) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_Mono(pfMono);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_MixLevel( double Level) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_MixLevel(Level);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_MixLevel( _Out_  double* pLevel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_MixLevel(pLevel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_Pan( double Pan) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_Pan(Pan);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_Pan( _Out_  double* pPan) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_Pan(pPan);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_Loudness( BOOL fLoudness) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_Loudness(fLoudness);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_Loudness( _Out_  BOOL* pfLoudness) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_Loudness(pfLoudness);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_Treble( double Treble) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_Treble(Treble);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_Treble( _Out_  double* pTreble) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_Treble(pTreble);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_TrebleRange( _Out_  double* pRange) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_TrebleRange(pRange);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_Bass( double Bass) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_Bass(Bass);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_Bass( _Out_  double* pBass) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_Bass(pBass);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_BassRange( _Out_  double* pRange) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_BassRange(pRange);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMBufferNegotiation : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMBufferNegotiation, Unknown, IAMBufferNegotiation, IUnknown)
    public:
        void SuggestAllocatorProperties( const ALLOCATOR_PROPERTIES* pprop) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SuggestAllocatorProperties(pprop);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetAllocatorProperties( _Out_  ALLOCATOR_PROPERTIES* pprop) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAllocatorProperties(pprop);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMAnalogVideoDecoder : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMAnalogVideoDecoder, Unknown, IAMAnalogVideoDecoder, IUnknown)
    public:
        void get_AvailableTVFormats(_Out_  long* lAnalogVideoStandard) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_AvailableTVFormats(lAnalogVideoStandard);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_TVFormat( long lAnalogVideoStandard) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_TVFormat(lAnalogVideoStandard);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_TVFormat( _Out_  long* plAnalogVideoStandard) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_TVFormat(plAnalogVideoStandard);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_HorizontalLocked( _Out_  long* plLocked) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_HorizontalLocked(plLocked);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_VCRHorizontalLocking( long lVCRHorizontalLocking) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_VCRHorizontalLocking(lVCRHorizontalLocking);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_VCRHorizontalLocking( _Out_  long* plVCRHorizontalLocking) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_VCRHorizontalLocking(plVCRHorizontalLocking);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_NumberOfLines( _Out_  long* plNumberOfLines) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_NumberOfLines(plNumberOfLines);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_OutputEnable( long lOutputEnable) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_OutputEnable(lOutputEnable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_OutputEnable( _Out_  long* plOutputEnable) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_OutputEnable(plOutputEnable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMVideoProcAmp : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMVideoProcAmp, Unknown, IAMVideoProcAmp, IUnknown)
    public:
        void GetRange( long Property, _Out_  long* pMin, _Out_  long* pMax, _Out_  long* pSteppingDelta, _Out_  long* pDefault, _Out_  long* pCapsFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetRange(Property, pMin, pMax, pSteppingDelta, pDefault, pCapsFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Set( long Property, long lValue, long Flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Set(Property, lValue, Flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Get( long Property, _Out_  long* lValue, _Out_  long* Flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Get(Property, lValue, Flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    enum class CameraControlFlags : long
    {
        Absolute = KSPROPERTY_CAMERACONTROL_FLAGS_ABSOLUTE,
        Auto = KSPROPERTY_CAMERACONTROL_FLAGS_AUTO,
        Manual = KSPROPERTY_CAMERACONTROL_FLAGS_MANUAL,
        Asynchronous = KSPROPERTY_CAMERACONTROL_FLAGS_ASYNCHRONOUS,
        Relative = KSPROPERTY_CAMERACONTROL_FLAGS_RELATIVE
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS(CameraControlFlags, long);

    enum class CameraControlProperty : long
    {
        /// <summary>
        /// <p>
        /// The property value (operation data) is a LONG that specifies a 
        /// camera's pan setting. This value is expressed in degrees.
        /// </p>
        /// <p>
        /// Positive values indicate that the camera is rotated clockwise. 
        /// Negative values indicate that the camera is rotated counterclockwise.
        /// </p>
        /// <p>
        /// Every video capture minidriver that supports this property must define 
        /// a range and default value for this property. The range for the device 
        /// must be -180 through +180. The default value must be 0.
        /// </p>
        /// </summary>
        Pan = KSPROPERTY_CAMERACONTROL_PAN,
        /// <summary>
        /// <p>
        /// The property value (operation data) is a LONG that specifies a 
        /// camera's tilt setting. This value is expressed in degrees.
        /// </p>
        /// <p>
        /// Positive values point the imaging plane up. Negative values 
        /// point the imaging plane down.
        /// </p>
        /// <p>
        /// Every video capture minidriver that supports this property must define 
        /// a range and default value for this property. The range for the device 
        /// must -180 through +180. The default value must be 0.
        /// </p>
        /// </summary>
        Tilt = KSPROPERTY_CAMERACONTROL_TILT,
        /// <summary>
        /// <p>
        /// The property value (operation data) is a LONG that specifies a 
        /// camera's roll setting. This value is expressed in degrees.
        /// </p>
        /// <p>
        /// Positive values cause a clockwise rotation of the camera along the 
        /// image-viewing axis. Negative values cause a counterclockwise rotation 
        /// of the camera.
        /// </p>
        /// <p>
        /// Every video capture minidriver that supports this property must define 
        /// a range and default value for this property. The range for the device 
        /// must be -180 through +180 and the default value must be 0.
        /// </p>
        /// </summary>
        Roll = KSPROPERTY_CAMERACONTROL_ROLL,
        /// <summary>
        /// <p>
        /// The property value (operation data) is a LONG that specifies a camera's 
        /// zoom setting. This value is expressed in millimeters.
        /// </p>
        /// <p>
        /// Every video capture minidriver that supports this property must define a 
        /// range and default value for this property. The range for the device must 
        /// be 10 through 600. The default value must be 10.
        /// </p>
        /// </summary>
        Zoom = KSPROPERTY_CAMERACONTROL_ZOOM,
        /// <summary>
        /// <p>
        /// The property value (operation data) is a LONG that specifies the length 
        /// of exposure.
        /// </p>
        /// <p>
        /// This value is expressed in log base 2 seconds, thus, for values 
        /// less than zero, the exposure time is 1/(2*n) seconds. For positive 
        /// values and zero, the exposure time is 2*n seconds.
        /// </p>
        /// <p>
        /// Every video capture minidriver that supports this property must define 
        /// its own range and default value for this property.
        /// </p>
        /// </summary>
        Exposure = KSPROPERTY_CAMERACONTROL_EXPOSURE,
        /// <summary>
        /// <p>
        /// The property value (operation data) is a LONG that specifies a 
        /// camera's aperture setting. This value is expressed in units of fstop * 10.
        /// </p>
        /// <p>
        /// Every video capture minidriver that supports this property must define 
        /// its own range and default value for this property.
        /// </p>
        /// </summary>
        Iris = KSPROPERTY_CAMERACONTROL_IRIS,
        /// <summary>
        /// <p>
        /// The property value (operation data) is a LONG that specifies 
        /// the focus setting. This value is expressed in millimeters.
        /// </p>
        /// <p>
        /// Every video capture minidriver that supports this property 
        /// must define its own range and default value for this property.
        /// </p>
        /// </summary>
        Focus = KSPROPERTY_CAMERACONTROL_FOCUS,
        /// <summary>
        /// <p>
        /// The property value (operation data) is a LONG that specifies 
        /// whether interlace mode should be enabled. A value of 0 indicates 
        /// that the interlace mode is enabled, and a value of 1 indicates 
        /// that the progressive (or non-interlace) mode is enabled.
        /// </p>
        /// </summary>
        ScanMode = KSPROPERTY_CAMERACONTROL_SCANMODE,
        /// <summary>
        /// <p>
        /// The property value (operation data) is a LONG that specifies 
        /// whether privacy mode is enable or disabled. A value of 0 indicates 
        /// that the camera sensor can capture video images, and a value of 1 
        /// indicates that the camera sensor is prevented from capturing video images.
        /// </p>
        /// </summary>
        Privacy = KSPROPERTY_CAMERACONTROL_PRIVACY,
        /// <summary>
        /// <p>
        /// 
        /// </p>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// </summary>
        PanTilt = KSPROPERTY_CAMERACONTROL_PANTILT,
        /// <summary>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// </summary>
        PanRelative = KSPROPERTY_CAMERACONTROL_PAN_RELATIVE,
        /// <summary>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// </summary>
        TiltRelative = KSPROPERTY_CAMERACONTROL_TILT_RELATIVE,
        /// <summary>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// </summary>
        RollRelative = KSPROPERTY_CAMERACONTROL_ROLL_RELATIVE,
        /// <summary>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// </summary>
        ZoomRelative = KSPROPERTY_CAMERACONTROL_ZOOM_RELATIVE,
        /// <summary>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// </summary>
        ExposureRelative = KSPROPERTY_CAMERACONTROL_EXPOSURE_RELATIVE,
        /// <summary>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// </summary>
        IrisRelative = KSPROPERTY_CAMERACONTROL_IRIS_RELATIVE,
        /// <summary>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// </summary>
        FocusRelative = KSPROPERTY_CAMERACONTROL_FOCUS_RELATIVE,
        /// <summary>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// </summary>
        PantiltRelative = KSPROPERTY_CAMERACONTROL_PANTILT_RELATIVE,
        /// <summary>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// </summary>
        FocalLength = KSPROPERTY_CAMERACONTROL_FOCAL_LENGTH,
        /// <summary>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// <p>
        /// </p>
        /// </summary>
        AutoExposurePriority = KSPROPERTY_CAMERACONTROL_AUTO_EXPOSURE_PRIORITY
    };

    struct CameraControlPropertySetting
    {
        CameraControlProperty Property;
        long Value;
        CameraControlFlags Flags;

        template<typename ReaderT>
        void Read(ReaderT& reader)
        {
            Property = reader.Read<CameraControlProperty>();
            Value = reader.Read<long>();
            Flags = reader.Read<CameraControlFlags>();
        }
        template<typename WriterT>
        void Write(WriterT& writer) const
        {
            writer.Write(Property);
            writer.Write(Value);
            writer.Write(Flags);
        }
    };

    struct CameraControlPropertyRange
    {
        CameraControlProperty Property;
        long MinValue;
        long MaxValue;
        long SteppingDelta;
        long DefaultValue;
        CameraControlFlags Flags;

        template<typename ReaderT>
        void Read(ReaderT& reader)
        {
            Property = reader.Read<CameraControlProperty>();
            MinValue = reader.Read<long>();
            MaxValue = reader.Read<long>();
            SteppingDelta = reader.Read<long>();
            DefaultValue = reader.Read<long>();
            Flags = reader.Read<CameraControlFlags>();
        }
        template<typename WriterT>
        void Write(WriterT& writer) const
        {
            writer.Write(Property);
            writer.Write(MinValue);
            writer.Write(MaxValue);
            writer.Write(SteppingDelta);
            writer.Write(DefaultValue);
            writer.Write(Flags);
        }


    };

    class CameraControlSettings
    {
        
    };

    class AMCameraControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMCameraControl, Unknown, IAMCameraControl, IUnknown)
    public:
        using Range = CameraControlPropertyRange;
        

        void GetRange( long Property, _Out_  long* pMin, _Out_  long* pMax, _Out_  long* pSteppingDelta, _Out_  long* pDefault, _Out_  long* pCapsFlags) const
        {
            
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetRange(Property, pMin, pMax, pSteppingDelta, pDefault, pCapsFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        Range GetRange(CameraControlProperty property) const
        {
            Range result{ property,0, };
            GetRange(static_cast<long>(property), &result.MinValue, &result.MaxValue, &result.SteppingDelta, &result.DefaultValue, reinterpret_cast<long*>(&result.Flags));
            return result;
        }

        void Set( long Property, long lValue, long Flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Set(Property, lValue, Flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void Set(CameraControlProperty property, long lValue, CameraControlFlags Flags) const
        {
            Set(static_cast<long>(property), lValue, static_cast<long>(Flags));
        }

        void Get( long Property, _Out_  long* lValue, _Out_  long* Flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Get(Property, lValue, Flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        void Get(CameraControlProperty property, _Out_  long* lValue, _Out_  CameraControlFlags* Flags) const
        {
            Get(static_cast<long>(property), lValue, reinterpret_cast<long*>(Flags));
        }

        struct Pan
        {
            long Value;
            CameraControlFlags Flags;
        };

        Pan GetPan() const
        {
            Pan result{};
            Get(CameraControlProperty::Pan, &result.Value, &result.Flags);
            return result;
        }
        void SetPan(long panInDegrees, CameraControlFlags flags)
        {
            Set(CameraControlProperty::Pan, panInDegrees, flags);
        }
        void SetPan(const Pan& pan)
        {
            Set(CameraControlProperty::Pan, pan.Value, pan.Flags);
        }

        struct Tilt
        {
            long Value;
            CameraControlFlags Flags;
        };

        Tilt GetTilt() const
        {
            Tilt result{};
            Get(CameraControlProperty::Tilt, &result.Value, &result.Flags);
            return result;
        }
        void SetTilt(long tiltInDegrees, CameraControlFlags flags)
        {
            Set(CameraControlProperty::Tilt, tiltInDegrees, flags);
        }
        void SetTilt(const Tilt& tilt)
        {
            Set(CameraControlProperty::Tilt, tilt.Value, tilt.Flags);
        }


        struct Roll
        {
            long Value;
            CameraControlFlags Flags;
        };

        Roll GetRoll() const
        {
            Roll result{};
            Get(CameraControlProperty::Roll, &result.Value, &result.Flags);
            return result;
        }

        struct Zoom
        {
            long Value;
            CameraControlFlags Flags;
        };

        Zoom GetZoom() const
        {
            Zoom result{};
            Get(CameraControlProperty::Zoom, &result.Value, &result.Flags);
            return result;
        }

        struct Exposure
        {
            long Value;
            CameraControlFlags Flags;
        };

        Exposure GetExposure() const
        {
            Exposure result{};
            Get(CameraControlProperty::Exposure, &result.Value, &result.Flags);
            return result;
        }

        struct Iris
        {
            long Value;
            CameraControlFlags Flags;
        };

        Iris GetIris() const
        {
            Iris result{};
            Get(CameraControlProperty::Iris, &result.Value, &result.Flags);
            return result;
        }


        struct Focus
        {
            long Value;
            CameraControlFlags Flags;
        };

        Focus GetFocus() const
        {
            Focus result{};
            Get(CameraControlProperty::Focus, &result.Value, &result.Flags);
            return result;
        }


        struct ScanMode
        {
            long Value;
            CameraControlFlags Flags;
        };

        ScanMode GetScanMode() const
        {
            ScanMode result{};
            Get(CameraControlProperty::ScanMode, &result.Value, &result.Flags);
            return result;
        }

        struct Privacy
        {
            long Value;
            CameraControlFlags Flags;
        };

        Privacy GetPrivacy() const
        {
            Privacy result{};
            Get(CameraControlProperty::Privacy, &result.Value, &result.Flags);
            return result;
        }

        

    };

    class AMVideoControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMVideoControl, Unknown, IAMVideoControl, IUnknown)
    public:
        void GetCaps( IPin* pPin, _Out_  long* pCapsFlags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCaps(pPin, pCapsFlags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetMode( IPin* pPin, long Mode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMode(pPin, Mode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMode( IPin* pPin, _Out_  long* Mode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMode(pPin, Mode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCurrentActualFrameRate( IPin* pPin, _Out_  LONGLONG* ActualFrameRate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurrentActualFrameRate(pPin, ActualFrameRate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetMaxAvailableFrameRate( IPin* pPin, long iIndex, SIZE Dimensions, _Out_  LONGLONG* MaxAvailableFrameRate) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetMaxAvailableFrameRate(pPin, iIndex, Dimensions, MaxAvailableFrameRate);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetFrameRateList( IPin* pPin, long iIndex, SIZE Dimensions, _Out_  long* ListSize, _Out_  LONGLONG** FrameRates) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFrameRateList(pPin, iIndex, Dimensions, ListSize, FrameRates);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMCrossbar : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMCrossbar, Unknown, IAMCrossbar, IUnknown)
    public:
        void get_PinCounts( _Out_  long* OutputPinCount, _Out_  long* InputPinCount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_PinCounts(OutputPinCount, InputPinCount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CanRoute( long OutputPinIndex, long InputPinIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CanRoute(OutputPinIndex, InputPinIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Route( long OutputPinIndex, long InputPinIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Route(OutputPinIndex, InputPinIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_IsRoutedTo( long OutputPinIndex, _Out_  long* InputPinIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_IsRoutedTo(OutputPinIndex, InputPinIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_CrossbarPinInfo( BOOL IsInputPin, long PinIndex, _Out_  long* PinIndexRelated, _Out_  long* PhysicalType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_CrossbarPinInfo(IsInputPin, PinIndex, PinIndexRelated, PhysicalType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMTuner : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMTuner, Unknown, IAMTuner, IUnknown)
    public:
        void put_Channel(long lChannel, long lVideoSubChannel, long lAudioSubChannel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_Channel(lChannel, lVideoSubChannel, lAudioSubChannel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_Channel( _Out_  long* plChannel, _Out_  long* plVideoSubChannel, _Out_  long* plAudioSubChannel) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_Channel(plChannel, plVideoSubChannel, plAudioSubChannel);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ChannelMinMax( _Out_  long* lChannelMin, _Out_  long* lChannelMax) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ChannelMinMax(lChannelMin, lChannelMax);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_CountryCode( long lCountryCode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_CountryCode(lCountryCode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_CountryCode( _Out_  long* plCountryCode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_CountryCode(plCountryCode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_TuningSpace( long lTuningSpace) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_TuningSpace(lTuningSpace);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_TuningSpace( _Out_  long* plTuningSpace) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_TuningSpace(plTuningSpace);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Logon( HANDLE hCurrentUser) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Logon(hCurrentUser);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Logout( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Logout();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SignalPresent( _Out_  long* plSignalStrength) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SignalPresent(plSignalStrength);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_Mode( AMTunerModeType lMode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_Mode(lMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_Mode( _Out_  AMTunerModeType* plMode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_Mode(plMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetAvailableModes( _Out_  long* plModes) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAvailableModes(plModes);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RegisterNotificationCallBack( IAMTunerNotification* pNotify, long lEvents) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterNotificationCallBack(pNotify, lEvents);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnRegisterNotificationCallBack( IAMTunerNotification* pNotify) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnRegisterNotificationCallBack(pNotify);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMTunerNotification : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMTunerNotification, Unknown, IAMTunerNotification, IUnknown)
    public:
        void OnEvent(AMTunerEventType Event) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnEvent(Event);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AMTVTuner : public AMTuner
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AMTVTuner, AMTuner, IAMTVTuner, IAMTuner)
    public:
        void get_AvailableTVFormats( _Out_  long* lAnalogVideoStandard) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_AvailableTVFormats(lAnalogVideoStandard);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_TVFormat( _Out_  long* plAnalogVideoStandard) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_TVFormat(plAnalogVideoStandard);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AutoTune( long lChannel, _Out_  long* plFoundSignal) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AutoTune(lChannel, plFoundSignal);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void StoreAutoTune( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->StoreAutoTune();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_NumInputConnections( _Out_  long* plNumInputConnections) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_NumInputConnections(plNumInputConnections);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_InputType( long lIndex, TunerInputType InputType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_InputType(lIndex, InputType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_InputType( long lIndex, _Out_  TunerInputType* pInputType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_InputType(lIndex, pInputType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_ConnectInput( long lIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_ConnectInput(lIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_ConnectInput( _Out_  long* plIndex) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_ConnectInput(plIndex);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_VideoFrequency( _Out_  long* lFreq) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_VideoFrequency(lFreq);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void get_AudioFrequency( _Out_  long* lFreq) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_AudioFrequency(lFreq);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class BPCSatelliteTuner : public AMTuner
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(BPCSatelliteTuner, AMTuner, IBPCSatelliteTuner, IAMTuner)
    public:
        void get_DefaultSubChannelTypes( _Out_  long* plDefaultVideoType, _Out_  long* plDefaultAudioType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->get_DefaultSubChannelTypes(plDefaultVideoType, plDefaultAudioType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void put_DefaultSubChannelTypes( long lDefaultVideoType, long lDefaultAudioType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->put_DefaultSubChannelTypes(lDefaultVideoType, lDefaultAudioType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        bool IsTapingPermitted( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->IsTapingPermitted();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
            return hr == S_OK;
        }

    };



}

#endif

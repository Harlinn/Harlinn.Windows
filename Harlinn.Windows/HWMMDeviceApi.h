#pragma once
#ifndef HARLINN_WINDOWS_HWMMDEVICEAPI_H_
#define HARLINN_WINDOWS_HWMMDEVICEAPI_H_

#include <HCCPropSys.h>
#include <HWDef.h>

namespace Harlinn::Windows
{
    class MMNotificationClient : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MMNotificationClient, Unknown, IMMNotificationClient, IUnknown)
    public:
        void OnDeviceStateChanged( LPCWSTR deviceId, DWORD newState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnDeviceStateChanged(deviceId, newState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnDeviceAdded( LPCWSTR deviceId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnDeviceAdded(deviceId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnDeviceRemoved( LPCWSTR deviceId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnDeviceRemoved(deviceId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnDefaultDeviceChanged( EDataFlow flow, ERole role, LPCWSTR defaultDeviceId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnDefaultDeviceChanged(flow, role, defaultDeviceId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OnPropertyValueChanged( LPCWSTR deviceId, const PROPERTYKEY key) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnPropertyValueChanged(deviceId, key);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class MMDevice : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MMDevice, Unknown, IMMDevice, IUnknown)
    public:
        void Activate(const Guid& iid, DWORD clsCtx, PROPVARIANT* activationParams, void** itf) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Activate(iid, clsCtx, activationParams, itf);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OpenPropertyStore( DWORD access, IPropertyStore** properties) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OpenPropertyStore(access, properties);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        PropertyStore OpenPropertyStore(DWORD access) const
        {
            IPropertyStore* itf = nullptr;
            OpenPropertyStore(access, &itf);
            return PropertyStore(itf);
        }


        void GetId( LPWSTR* id) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetId(id);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        WideString GetId( ) const
        {
            LPWSTR str = nullptr;
            GetId(&str);
            if (str)
            {
                WideString result(str);
                CoTaskMemFree(str);
                return result;
            }
            else
            {
                return WideString();
            }
        }


        void GetState( DWORD* state) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetState(state);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        DWORD GetState() const
        {
            DWORD result = 0;
            GetState(&result);
            return result;
        }

    };

    class MMDeviceCollection : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MMDeviceCollection, Unknown, IMMDeviceCollection, IUnknown)
    public:
        void GetCount(UINT* numberOfDevices) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCount(numberOfDevices);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        UINT GetCount() const
        {
            UINT result = 0;
            GetCount(&result);
            return result;
        }
        size_t size() const
        {
            return static_cast<size_t>(GetCount());
        }

        void Item( UINT deviceIndex, IMMDevice** ppDevice) const
        { 
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Item(deviceIndex, ppDevice);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MMDevice Item(UINT deviceIndex) const
        {
            IMMDevice* itf = nullptr;
            Item(deviceIndex, &itf);
            return MMDevice(itf);
        }

        MMDevice operator[](size_t deviceIndex) const
        {
            return Item(static_cast<UINT>(deviceIndex));
        }

    };

    class MMEndpoint : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MMEndpoint, Unknown, IMMEndpoint, IUnknown)
    public:
        void GetDataFlow(EDataFlow* dataFlow) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDataFlow(dataFlow);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        EDataFlow GetDataFlow() const
        {
            EDataFlow result{};
            GetDataFlow(&result);
            return result;
        }
    };

    class MMDeviceEnumerator : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MMDeviceEnumerator, Unknown, IMMDeviceEnumerator, IUnknown)
    public:
        static MMDeviceEnumerator Create(DWORD classContext = CLSCTX_ALL)
        {
            return CoCreateInstanceFromClassId<MMDeviceEnumerator>(__uuidof(::MMDeviceEnumerator), classContext);
        }

        void EnumAudioEndpoints( EDataFlow dataFlow, DWORD stateMask, IMMDeviceCollection** devices) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EnumAudioEndpoints(dataFlow, stateMask, devices);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MMDeviceCollection EnumAudioEndpoints(EDataFlow dataFlow = EDataFlow::eRender, DWORD stateMask = DEVICE_STATE_ACTIVE) const
        {
            IMMDeviceCollection* itf = nullptr;
            EnumAudioEndpoints(dataFlow, stateMask, &itf);
            return MMDeviceCollection(itf);
        }

        void GetDefaultAudioEndpoint( EDataFlow dataFlow, ERole role, IMMDevice** endpoint) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDefaultAudioEndpoint(dataFlow, role, endpoint);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MMDevice GetDefaultAudioEndpoint(EDataFlow dataFlow, ERole role) const
        {
            IMMDevice* itf = nullptr;
            GetDefaultAudioEndpoint(dataFlow, role, &itf);
            return MMDevice(itf);
        }

        void GetDevice( LPCWSTR id, IMMDevice** device) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDevice(id, device);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
        MMDevice GetDevice(LPCWSTR id) const
        {
            IMMDevice* itf = nullptr;
            GetDevice(id, &itf);
            return MMDevice(itf);
        }

        void RegisterEndpointNotificationCallback( IMMNotificationClient* client) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterEndpointNotificationCallback(client);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnregisterEndpointNotificationCallback( IMMNotificationClient* client) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnregisterEndpointNotificationCallback(client);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class MMDeviceActivator : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(MMDeviceActivator, Unknown, IMMDeviceActivator, IUnknown)
    public:
        void Activate(const Guid& iid, IMMDevice* device, PROPVARIANT* activationParams, void** itf) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Activate(iid, device, activationParams, itf);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class ActivateAudioInterfaceCompletionHandler : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ActivateAudioInterfaceCompletionHandler, Unknown, IActivateAudioInterfaceCompletionHandler, IUnknown)
    public:
        void ActivateCompleted(IActivateAudioInterfaceAsyncOperation* activateOperation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ActivateCompleted(activateOperation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class ActivateAudioInterfaceAsyncOperation : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(ActivateAudioInterfaceAsyncOperation, Unknown, IActivateAudioInterfaceAsyncOperation, IUnknown)
    public:
        void GetActivateResult(HRESULT* activateResult, IUnknown** activatedInterface) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetActivateResult(activateResult, activatedInterface);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class AudioSystemEffectsPropertyChangeNotificationClient : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AudioSystemEffectsPropertyChangeNotificationClient, Unknown, IAudioSystemEffectsPropertyChangeNotificationClient, IUnknown)
    public:
        void OnPropertyChanged(AUDIO_SYSTEMEFFECTS_PROPERTYSTORE_TYPE type, const PROPERTYKEY key) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OnPropertyChanged(type, key);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class AudioSystemEffectsPropertyStore : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(AudioSystemEffectsPropertyStore, Unknown, IAudioSystemEffectsPropertyStore, IUnknown)
    public:
        void OpenDefaultPropertyStore(DWORD access, IPropertyStore** propStore) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OpenDefaultPropertyStore(access, propStore);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OpenUserPropertyStore( DWORD access, IPropertyStore** propStore) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OpenUserPropertyStore(access, propStore);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OpenVolatilePropertyStore( DWORD access, IPropertyStore** propStore) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OpenVolatilePropertyStore(access, propStore);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ResetUserPropertyStore( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ResetUserPropertyStore();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ResetVolatilePropertyStore( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ResetVolatilePropertyStore();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RegisterPropertyChangeNotification( IAudioSystemEffectsPropertyChangeNotificationClient* callback) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterPropertyChangeNotification(callback);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnregisterPropertyChangeNotification( IAudioSystemEffectsPropertyChangeNotificationClient* callback) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnregisterPropertyChangeNotification(callback);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    



}


#endif

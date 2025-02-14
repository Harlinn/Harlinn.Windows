#pragma once
#ifndef HARLINN_WINDOWS_HWDXVA2API_H_
#define HARLINN_WINDOWS_HWDXVA2API_H_
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

namespace Harlinn::Windows
{
    class Direct3DDeviceManager9 : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Direct3DDeviceManager9, Unknown, IDirect3DDeviceManager9, IUnknown)
    public:
        static Direct3DDeviceManager9 Create(UINT* resetToken)
        {
            IDirect3DDeviceManager9* itf = nullptr;
            auto hr = DXVA2CreateDirect3DDeviceManager9(resetToken, &itf);
            HCC_COM_CHECK_HRESULT(hr);
            return Direct3DDeviceManager9(itf);
        }
        static std::pair<UINT, Direct3DDeviceManager9> Create()
        {
            UINT resetToken = 0;
            auto deviceManager = Create(&resetToken);
            return { resetToken ,deviceManager };
        }

        void ResetDevice( IDirect3DDevice9* device, UINT resetToken) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ResetDevice(device, resetToken);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void OpenDeviceHandle( HANDLE* deviceHandle) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->OpenDeviceHandle(deviceHandle);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CloseDeviceHandle( HANDLE deviceHandle) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CloseDeviceHandle(deviceHandle);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void TestDevice( HANDLE deviceHandle) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->TestDevice(deviceHandle);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void LockDevice( HANDLE deviceHandle, IDirect3DDevice9** device, BOOL block) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->LockDevice(deviceHandle, device, block);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void UnlockDevice( HANDLE deviceHandle, BOOL saveState) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->UnlockDevice(deviceHandle, saveState);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoService( HANDLE deviceHandle, const Guid& riid, void** service) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoService(deviceHandle, riid, service);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DirectXVideoAccelerationService : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DirectXVideoAccelerationService, Unknown, IDirectXVideoAccelerationService, IUnknown)
    public:
        void CreateSurface(UINT width, UINT height, UINT backBuffers, D3DFORMAT format, D3DPOOL pool, DWORD usage, DWORD dxvaType, IDirect3DSurface9** surface, HANDLE* sharedHandle) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSurface(width, height, backBuffers, format, pool, usage, dxvaType, surface, sharedHandle);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class DirectXVideoDecoderService : public DirectXVideoAccelerationService
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DirectXVideoDecoderService, DirectXVideoAccelerationService, IDirectXVideoDecoderService, IDirectXVideoAccelerationService)
    public:
        
        void GetDecoderDeviceGuids( UINT* count, Guid** guids) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDecoderDeviceGuids(count, (GUID**)guids);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDecoderRenderTargets(const Guid& guid, UINT* count, D3DFORMAT** formats) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDecoderRenderTargets(guid, count, formats);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetDecoderConfigurations( const Guid& guid, const DXVA2_VideoDesc* videoDesc, void* reserved, UINT* count, DXVA2_ConfigPictureDecode** configs) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetDecoderConfigurations(guid, videoDesc, reserved, count, configs);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateVideoDecoder( const Guid& guid, const DXVA2_VideoDesc* videoDesc, const DXVA2_ConfigPictureDecode* config, IDirect3DSurface9** decoderRenderTargets, UINT numRenderTargets, IDirectXVideoDecoder** decode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVideoDecoder(guid, videoDesc, config, decoderRenderTargets, numRenderTargets, decode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DirectXVideoProcessorService : public DirectXVideoAccelerationService
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DirectXVideoProcessorService, DirectXVideoAccelerationService, IDirectXVideoProcessorService, IDirectXVideoAccelerationService)
    public:
        void RegisterVideoProcessorSoftwareDevice( void* callbacks) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RegisterVideoProcessorSoftwareDevice(callbacks);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoProcessorDeviceGuids( const DXVA2_VideoDesc* videoDesc, UINT* count, Guid** guids) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoProcessorDeviceGuids(videoDesc, count, (GUID**)guids);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoProcessorRenderTargets( const Guid& videoProcDeviceGuid, const DXVA2_VideoDesc* videoDesc, UINT* count, D3DFORMAT** formats) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoProcessorRenderTargets(videoProcDeviceGuid, videoDesc, count, formats);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoProcessorSubStreamFormats( const Guid& videoProcDeviceGuid, const DXVA2_VideoDesc* videoDesc, D3DFORMAT renderTargetFormat, UINT* count, D3DFORMAT** formats) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoProcessorSubStreamFormats(videoProcDeviceGuid, videoDesc, renderTargetFormat, count, formats);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoProcessorCaps( const Guid& videoProcDeviceGuid, const DXVA2_VideoDesc* videoDesc, D3DFORMAT renderTargetFormat, DXVA2_VideoProcessorCaps* caps) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoProcessorCaps(videoProcDeviceGuid, videoDesc, renderTargetFormat, caps);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetProcAmpRange( const Guid& videoProcDeviceGuid, const DXVA2_VideoDesc* videoDesc, D3DFORMAT renderTargetFormat, UINT procAmpCap, DXVA2_ValueRange* range) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProcAmpRange(videoProcDeviceGuid, videoDesc, renderTargetFormat, procAmpCap, range);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetFilterPropertyRange( const Guid& videoProcDeviceGuid, const DXVA2_VideoDesc* videoDesc, D3DFORMAT renderTargetFormat, UINT filterSetting, DXVA2_ValueRange* range) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFilterPropertyRange(videoProcDeviceGuid, videoDesc, renderTargetFormat, filterSetting, range);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateVideoProcessor( const Guid& videoProcDeviceGuid, const DXVA2_VideoDesc* videoDesc, D3DFORMAT renderTargetFormat, UINT maxNumSubStreams, IDirectXVideoProcessor** vidProcess) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVideoProcessor(videoProcDeviceGuid, videoDesc, renderTargetFormat, maxNumSubStreams, vidProcess);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DirectXVideoDecoder : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DirectXVideoDecoder, Unknown, IDirectXVideoDecoder, IUnknown)
    public:
        void GetVideoDecoderService( IDirectXVideoDecoderService** service) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoDecoderService(service);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCreationParameters( Guid* deviceGuid, DXVA2_VideoDesc* videoDesc, DXVA2_ConfigPictureDecode* config, IDirect3DSurface9*** decoderRenderTargets, UINT* numSurfaces) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCreationParameters((GUID*)deviceGuid, videoDesc, config, decoderRenderTargets, numSurfaces);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetBuffer( UINT bufferType, void** buffer, UINT* bufferSize) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetBuffer(bufferType, buffer, bufferSize);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ReleaseBuffer( UINT bufferType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ReleaseBuffer(bufferType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void BeginFrame( IDirect3DSurface9* renderTarget, void* pvpData) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginFrame(renderTarget, pvpData);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndFrame( HANDLE* handleComplete) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndFrame(handleComplete);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Execute( const DXVA2_DecodeExecuteParams* executeParams) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Execute(executeParams);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DirectXVideoProcessor : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DirectXVideoProcessor, Unknown, IDirectXVideoProcessor, IUnknown)
    public:
        void GetVideoProcessorService( IDirectXVideoProcessorService** service) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoProcessorService(service);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCreationParameters( Guid* deviceGuid, DXVA2_VideoDesc* videoDesc, D3DFORMAT* renderTargetFormat, UINT* maxNumSubStreams) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCreationParameters((GUID*)deviceGuid, videoDesc, renderTargetFormat, maxNumSubStreams);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetVideoProcessorCaps( DXVA2_VideoProcessorCaps* videoProcessorCaps) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetVideoProcessorCaps(videoProcessorCaps);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetProcAmpRange( UINT procAmpCap, DXVA2_ValueRange* valueRange) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetProcAmpRange(procAmpCap, valueRange);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetFilterPropertyRange( UINT filterSetting, DXVA2_ValueRange* valueRange) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFilterPropertyRange(filterSetting, valueRange);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void VideoProcessBlt( IDirect3DSurface9* renderTarget, const DXVA2_VideoProcessBltParams* bltParams, const DXVA2_VideoSample* samples, UINT numSamples, HANDLE* handleComplete) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->VideoProcessBlt(renderTarget, bltParams, samples, numSamples, handleComplete);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DirectXVideoMemoryConfiguration : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DirectXVideoMemoryConfiguration, Unknown, IDirectXVideoMemoryConfiguration, IUnknown)
    public:
        void GetAvailableSurfaceTypeByIndex(DWORD typeIndex, DXVA2_SurfaceType* surfaceType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetAvailableSurfaceTypeByIndex(typeIndex, surfaceType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetSurfaceType( DXVA2_SurfaceType surfaceType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSurfaceType(surfaceType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


}

#endif

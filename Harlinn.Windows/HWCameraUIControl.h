#pragma once
#ifndef HARLINN_WINDOWS_HWCAMERAUICONTROL_H_
#define HARLINN_WINDOWS_HWCAMERAUICONTROL_H_

#include <HWDef.h>
#include <HCCCom.h>

namespace Harlinn::Windows
{
    class CameraUIControlEventCallback : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(CameraUIControlEventCallback, Unknown, ICameraUIControlEventCallback, IUnknown)
    public:
        void OnStartupComplete() const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->OnStartupComplete();
        }

        void OnSuspendComplete( ) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->OnSuspendComplete();
        }

        void OnItemCaptured( LPCWSTR path) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->OnItemCaptured(path);
        }

        void OnItemDeleted(LPCWSTR path) const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->OnItemDeleted(path);
        }

        void OnClosed() const
        {
            InterfaceType* pInterface = GetInterface();
            pInterface->OnClosed();
        }
    };

    class CameraUIControl : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(CameraUIControl, Unknown, ICameraUIControl, IUnknown)
    public:
        void Show( IUnknown* window, CameraUIControlMode mode, CameraUIControlLinearSelectionMode selectionMode, CameraUIControlCaptureMode captureMode, CameraUIControlPhotoFormat photoFormat, CameraUIControlVideoFormat videoFormat, BOOL hasCloseButton, ICameraUIControlEventCallback* eventCallback) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Show( window, mode, selectionMode, captureMode, photoFormat, videoFormat, hasCloseButton, eventCallback);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Close( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Close();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Suspend( BOOL* pbDeferralRequired) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Suspend(pbDeferralRequired);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Resume( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Resume();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetCurrentViewType( CameraUIControlViewType* viewType) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetCurrentViewType(viewType);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetActiveItem( BSTR* activeItemPath) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetActiveItem(activeItemPath);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void GetSelectedItems( SAFEARRAY** selectedItemPaths) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetSelectedItems(selectedItemPaths);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RemoveCapturedItem( LPCWSTR path) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveCapturedItem(path);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

}

#endif

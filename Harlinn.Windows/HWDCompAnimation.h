#pragma once
#ifndef HARLINN_WINDOWS_HWDCOMPANIMATION_H_
#define HARLINN_WINDOWS_HWDCOMPANIMATION_H_

#include <HWDef.h>
#include <HCCVariant.h>

namespace Harlinn::Windows::Graphics
{
    class DCompositionAnimation : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionAnimation, Unknown, IDCompositionAnimation, IUnknown)
    public:
        void Reset() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Reset();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAbsoluteBeginTime( LARGE_INTEGER beginTime) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAbsoluteBeginTime(beginTime);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AddCubic( double beginOffset, float constantCoefficient, float linearCoefficient, float quadraticCoefficient, float cubicCoefficient) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddCubic(beginOffset, constantCoefficient, linearCoefficient, quadraticCoefficient, cubicCoefficient);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AddSinusoidal( double beginOffset, float bias, float amplitude, float frequency, float phase) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddSinusoidal(beginOffset, bias, amplitude, frequency, phase);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void AddRepeat( double beginOffset, double durationToRepeat) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddRepeat(beginOffset, durationToRepeat);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void End( double endOffset, float endValue) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->End(endOffset, endValue);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };
}

#endif

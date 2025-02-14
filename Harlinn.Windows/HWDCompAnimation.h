#pragma once
#ifndef HARLINN_WINDOWS_HWDCOMPANIMATION_H_
#define HARLINN_WINDOWS_HWDCOMPANIMATION_H_
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
#include <HCCVariant.h>

namespace Harlinn::Windows::Graphics::DirectComposition
{
    /// <summary>
    /// Represents a function for animating one or more properties of one or 
    /// more Microsoft DirectComposition objects. Any object property that takes 
    /// a scalar value can be animated.
    /// </summary>
    class Animation : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(Animation, Unknown, IDCompositionAnimation, IUnknown)
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

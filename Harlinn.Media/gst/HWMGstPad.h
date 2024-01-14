#pragma once
#ifndef HARLINN_MEDIA_HWMGSTPAD_H_
#define HARLINN_MEDIA_HWMGSTPAD_H_
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

#include "HWMGstObject.h"

namespace Harlinn::Media::GStreamer
{
    namespace Internal
    {
        template<typename BaseT>
        class PadImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( PadImpl, GstPad )
        };
    }

    using BasicPad = Internal::PadImpl<BasicObject>;
    using Pad = Internal::PadImpl<Object>;

    static_assert( IsPad<BasicPad> );
    static_assert( IsPad<Pad> );


    namespace Internal
    {
        template<typename BaseT>
        class ProxyPadImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( ProxyPadImpl, GstProxyPad )
        };
    }
    using BasicProxyPad = Internal::ProxyPadImpl<BasicPad>;
    using ProxyPad = Internal::ProxyPadImpl<Pad>;

    static_assert( IsProxyPad<BasicProxyPad> );
    static_assert( IsProxyPad<ProxyPad> );

    namespace Internal
    {
        template<typename BaseT>
        class GhostPadImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( GhostPadImpl, GstGhostPad )
        };
    }
    using BasicGhostPad = Internal::GhostPadImpl<BasicProxyPad>;
    using GhostPad = Internal::GhostPadImpl<ProxyPad>;

    static_assert( IsGhostPad<BasicGhostPad> );
    static_assert( IsGhostPad<GhostPad> );


}


#endif

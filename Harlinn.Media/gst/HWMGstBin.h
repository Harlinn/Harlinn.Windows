#pragma once 
#ifndef HARLINN_MEDIA_GST_HWMGSTBIN_H_
#define HARLINN_MEDIA_GST_HWMGSTBIN_H_

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


#include "HWMGstElement.h"

namespace Harlinn::Media::GStreamer
{
    namespace Internal
    {
        template<typename BaseT>
        class BinImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( BinImpl, GstBin )
        };
    }

    using BasicBin = Internal::BinImpl<BasicElement>;
    using Bin = Internal::BinImpl<Element>;

    static_assert( IsBin<BasicElement> == false );
    static_assert( IsBin<Element> == false );
    static_assert( IsBin<BasicBin> );
    static_assert( IsBin<Bin> );
    static_assert( IsBin<BasicPipeline> );
    static_assert( IsBin<Pipeline> );
    static_assert( sizeof( BasicBin ) == sizeof( GstBin* ) );
    static_assert( sizeof( Bin ) == sizeof( GstBin* ) );
    static_assert( std::is_base_of_v<BasicElement, BasicBin> );
    static_assert( std::is_base_of_v<Element, Bin> );
    static_assert( std::is_base_of_v<GLib::ObjectTraits<GstElement>, GLib::ObjectTraits<GstBin>> );
}
#endif
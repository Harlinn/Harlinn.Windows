#pragma once
#ifndef HARLINN_MEDIA_GST_HWMGSTFORWARDS_H_
#define HARLINN_MEDIA_GST_HWMGSTFORWARDS_H_
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

#include <HWMDef.h>
#include "HWMGstTraits.h"

namespace Harlinn::Media::GStreamer
{
    class BasicObject;
    class Object;
    class BasicMiniObject;
    class MiniObject;

    class BasicAtomicQueue;
    class AtomicQueue;

    class Iterator;
    class Structure;

    // Objects

    namespace Internal
    {
        template<typename BaseT>
        class AllocatorImpl;
    }
    using BasicAllocator = Internal::AllocatorImpl<BasicObject>;
    using Allocator = Internal::AllocatorImpl<Object>;

    template<typename T>
    constexpr bool IsAllocator = std::is_base_of_v<BasicAllocator, T> || std::is_base_of_v<Allocator, T>;

    namespace Internal
    {
        template<typename BaseT>
        class ElementImpl;
    }
    using BasicElement = Internal::ElementImpl<BasicObject>;
    using Element = Internal::ElementImpl<Object>;

    template<typename T>
    constexpr bool IsElement = std::is_base_of_v<BasicElement, T> || std::is_base_of_v<Element, T>;

    namespace Internal
    {
        template<typename BaseT>
        class BinImpl;
    }
    using BasicBin = Internal::BinImpl<BasicElement>;
    using Bin = Internal::BinImpl<Element>;

    template<typename T>
    constexpr bool IsBin = std::is_base_of_v<BasicBin, T> || std::is_base_of_v<Bin, T>;

    namespace Internal
    {
        template<typename BaseT>
        class BusImpl;
    }
    using BasicBus = Internal::BusImpl<BasicObject>;
    using Bus = Internal::BusImpl<Object>;

    template<typename T>
    constexpr bool IsBus = std::is_base_of_v<BasicBus, T> || std::is_base_of_v<Bus, T>;


    namespace Internal
    {
        template<typename BaseT>
        class ClockImpl;
    }
    using BasicClock = Internal::ClockImpl<BasicObject>;
    using Clock = Internal::ClockImpl<Object>;

    template<typename T>
    constexpr bool IsClock = std::is_base_of_v<BasicClock, T> || std::is_base_of_v<Clock, T>;

    namespace Internal
    {
        template<typename BaseT>
        class ControlBindingImpl;
    }

    using BasicControlBinding = Internal::ControlBindingImpl<BasicObject>;
    using ControlBinding = Internal::ControlBindingImpl<Object>;

    template<typename T>
    constexpr bool IsControlBinding = std::is_base_of_v<BasicControlBinding, T> || std::is_base_of_v<ControlBinding, T>;

    namespace Internal
    {
        template<typename BaseT>
        class PluginFeatureImpl;
    }
    using BasicPluginFeature = Internal::PluginFeatureImpl<BasicObject>;
    using PluginFeature = Internal::PluginFeatureImpl<Object>;

    template<typename T>
    constexpr bool IsPluginFeature = std::is_base_of_v<BasicPluginFeature, T> || std::is_base_of_v<PluginFeature, T>;

    namespace Internal
    {
        template<typename BaseT>
        class ElementFactoryImpl;
    }
    using BasicElementFactory = Internal::ElementFactoryImpl<BasicPluginFeature>;
    using ElementFactory = Internal::ElementFactoryImpl<PluginFeature>;

    template<typename T>
    constexpr bool IsElementFactory = std::is_base_of_v<BasicElementFactory, T> || std::is_base_of_v<ElementFactory, T>;


    namespace Internal
    {
        template<typename BaseT>
        class PadImpl;
    }

    using BasicPad = Internal::PadImpl<BasicObject>;
    using Pad = Internal::PadImpl<Object>;

    template<typename T>
    constexpr bool IsPad = std::is_base_of_v<BasicPad, T> || std::is_base_of_v<Pad, T>;

    namespace Internal
    {
        template<typename BaseT>
        class PadTemplateImpl;
    }

    using BasicPadTemplate = Internal::PadTemplateImpl<BasicObject>;
    using PadTemplate = Internal::PadTemplateImpl<Object>;

    template<typename T>
    constexpr bool IsPadTemplate = std::is_base_of_v<BasicPadTemplate, T> || std::is_base_of_v<PadTemplate, T>;

    namespace Internal
    {
        template<typename BaseT>
        class PluginImpl;
    }

    using BasicPlugin = Internal::PluginImpl<BasicObject>;
    using Plugin = Internal::PluginImpl<Object>;

    template<typename T>
    constexpr bool IsPlugin = std::is_base_of_v<BasicPlugin, T> || std::is_base_of_v<Plugin, T>;


    namespace Internal
    {
        template<typename BaseT>
        class PipelineImpl;
    }

    using BasicPipeline = Internal::PipelineImpl<BasicBin>;
    using Pipeline = Internal::PipelineImpl<Bin>;

    template<typename T>
    constexpr bool IsPipeline = std::is_base_of_v<BasicPipeline, T> || std::is_base_of_v<Pipeline, T>;


    // Mini objects

    namespace Internal
    {
        template<typename BaseT>
        class MemoryImpl;
    }
    using BasicMemory = Internal::MemoryImpl<BasicMiniObject>;
    using Memory = Internal::MemoryImpl<MiniObject>;

    template<typename T>
    constexpr bool IsMemory = std::is_base_of_v<BasicMemory, T> || std::is_base_of_v<Memory, T>;

    namespace Internal
    {
        template<typename BaseT>
        class BufferImpl;
    }
    using BasicBuffer = Internal::BufferImpl<BasicMiniObject>;
    using Buffer = Internal::BufferImpl<MiniObject>;

    template<typename T>
    constexpr bool IsBuffer = std::is_base_of_v<BasicBuffer, T> || std::is_base_of_v<Buffer, T>;


    namespace Internal
    {
        template<typename BaseT>
        class MessageImpl;
    }
    using BasicMessage = Internal::MessageImpl<BasicMiniObject>;
    using Message = Internal::MessageImpl<MiniObject>;

    template<typename T>
    constexpr bool IsMessage = std::is_base_of_v<BasicMessage, T> || std::is_base_of_v<Message, T>;

    namespace Internal
    {
        template<typename BaseT>
        class TagListImpl;
    }

    using BasicTagList = Internal::TagListImpl<BasicMiniObject>;
    using TagList = Internal::TagListImpl<MiniObject>;

    template<typename T>
    constexpr bool IsTagList = std::is_base_of_v<BasicTagList, T> || std::is_base_of_v<TagList, T>;

}
#endif
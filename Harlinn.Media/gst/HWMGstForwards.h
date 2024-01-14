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

    template<typename T>
    constexpr bool IsObject = std::is_base_of_v<BasicObject, T>;

    class BasicMiniObject;
    class MiniObject;

    template<typename T>
    constexpr bool IsMiniObject = std::is_base_of_v<BasicMiniObject, T>;

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
        class BufferPoolImpl;
    }
    using BasicBufferPool = Internal::BufferPoolImpl<BasicObject>;
    using BufferPool = Internal::BufferPoolImpl<Object>;

    template<typename T>
    constexpr bool IsBufferPool = std::is_base_of_v<BasicBufferPool, T> || std::is_base_of_v<BufferPool, T>;

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
        class SystemClockImpl;
    }
    using BasicSystemClock = Internal::SystemClockImpl<BasicClock>;
    using SystemClock = Internal::SystemClockImpl<Clock>;

    template<typename T>
    constexpr bool IsSystemClock = std::is_base_of_v<BasicSystemClock, T> || std::is_base_of_v<SystemClock, T>;

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
        class ControlSourceImpl;
    }
    using BasicControlSource = Internal::ControlSourceImpl<BasicObject>;
    using ControlSource = Internal::ControlSourceImpl<Object>;

    template<typename T>
    constexpr bool IsControlSource = std::is_base_of_v<BasicControlSource, T> || std::is_base_of_v<ControlSource, T>;

    namespace Internal
    {
        template<typename BaseT>
        class DeviceImpl;
    }
    using BasicDevice = Internal::DeviceImpl<BasicObject>;
    using Device = Internal::DeviceImpl<Object>;

    template<typename T>
    constexpr bool IsDevice = std::is_base_of_v<BasicDevice, T> || std::is_base_of_v<Device, T>;

    namespace Internal
    {
        template<typename BaseT>
        class DeviceMonitorImpl;
    }
    using BasicDeviceMonitor = Internal::DeviceMonitorImpl<BasicObject>;
    using DeviceMonitor = Internal::DeviceMonitorImpl<Object>;

    template<typename T>
    constexpr bool IsDeviceMonitor = std::is_base_of_v<BasicDeviceMonitor, T> || std::is_base_of_v<DeviceMonitor, T>;

    namespace Internal
    {
        template<typename BaseT>
        class DeviceProviderImpl;
    }
    using BasicDeviceProvider = Internal::DeviceProviderImpl<BasicObject>;
    using DeviceProvider = Internal::DeviceProviderImpl<Object>;

    template<typename T>
    constexpr bool IsDeviceProvider = std::is_base_of_v<BasicDeviceProvider, T> || std::is_base_of_v<DeviceProvider, T>;

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
        class DeviceProviderFactoryImpl;
    }
    using BasicDeviceProviderFactory = Internal::DeviceProviderFactoryImpl<BasicPluginFeature>;
    using DeviceProviderFactory = Internal::DeviceProviderFactoryImpl<PluginFeature>;

    template<typename T>
    constexpr bool IsDeviceProviderFactory = std::is_base_of_v<BasicDeviceProviderFactory, T> || std::is_base_of_v<DeviceProviderFactory, T>;

    namespace Internal
    {
        template<typename BaseT>
        class DynamicTypeFactoryImpl;
    }
    using BasicDynamicTypeFactory = Internal::DynamicTypeFactoryImpl<BasicPluginFeature>;
    using DynamicTypeFactory = Internal::DynamicTypeFactoryImpl<PluginFeature>;

    template<typename T>
    constexpr bool IsDynamicTypeFactory = std::is_base_of_v<BasicDynamicTypeFactory, T> || std::is_base_of_v<DynamicTypeFactory, T>;


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
        class ProxyPadImpl;
    }
    using BasicProxyPad = Internal::ProxyPadImpl<BasicPad>;
    using ProxyPad = Internal::ProxyPadImpl<Pad>;

    template<typename T>
    constexpr bool IsProxyPad = std::is_base_of_v<BasicProxyPad, T> || std::is_base_of_v<ProxyPad, T>;

    namespace Internal
    {
        template<typename BaseT>
        class GhostPadImpl;
    }
    using BasicGhostPad = Internal::GhostPadImpl<BasicProxyPad>;
    using GhostPad = Internal::GhostPadImpl<ProxyPad>;

    template<typename T>
    constexpr bool IsGhostPad = std::is_base_of_v<BasicGhostPad, T> || std::is_base_of_v<GhostPad, T>;

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

    namespace Internal
    {
        template<typename BaseT>
        class StreamImpl;
    }
    using BasicStream = Internal::StreamImpl<BasicObject>;
    using Stream = Internal::StreamImpl<Object>;

    template<typename T>
    constexpr bool IsStream = std::is_base_of_v<BasicStream, T> || std::is_base_of_v<Stream, T>;

    namespace Internal
    {
        template<typename BaseT>
        class TaskImpl;
    }
    using BasicTask = Internal::TaskImpl<BasicObject>;
    using Task = Internal::TaskImpl<Object>;

    template<typename T>
    constexpr bool IsTask = std::is_base_of_v<BasicTask, T> || std::is_base_of_v<Task, T>;

    namespace Internal
    {
        template<typename BaseT>
        class TaskPoolImpl;
    }
    using BasicTaskPool = Internal::TaskPoolImpl<BasicObject>;
    using TaskPool = Internal::TaskPoolImpl<Object>;

    template<typename T>
    constexpr bool IsTaskPool = std::is_base_of_v<BasicTaskPool, T> || std::is_base_of_v<TaskPool, T>;

    namespace Internal
    {
        template<typename BaseT>
        class SharedTaskPoolImpl;
    }
    using BasicSharedTaskPool = Internal::SharedTaskPoolImpl<BasicTaskPool>;
    using SharedTaskPool = Internal::SharedTaskPoolImpl<TaskPool>;

    template<typename T>
    constexpr bool IsSharedTaskPool = std::is_base_of_v<BasicSharedTaskPool, T> || std::is_base_of_v<SharedTaskPool, T>;


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
        class BufferListImpl;
    }
    using BasicBufferList = Internal::BufferListImpl<BasicMiniObject>;
    using BufferList = Internal::BufferListImpl<MiniObject>;

    template<typename T>
    constexpr bool IsBufferList = std::is_base_of_v<BasicBufferList, T> || std::is_base_of_v<BufferList, T>;

    namespace Internal
    {
        template<typename BaseT>
        class CapsImpl;
    }
    using BasicCaps = Internal::CapsImpl<BasicMiniObject>;
    using Caps = Internal::CapsImpl<MiniObject>;

    template<typename T>
    constexpr bool IsCaps = std::is_base_of_v<BasicCaps, T> || std::is_base_of_v<Caps, T>;

    namespace Internal
    {
        template<typename BaseT>
        class EventImpl;
    }
    using BasicEvent = Internal::EventImpl<BasicMiniObject>;
    using Event = Internal::EventImpl<MiniObject>;

    template<typename T>
    constexpr bool IsEvent = std::is_base_of_v<BasicEvent, T> || std::is_base_of_v<Event, T>;

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
        class PromiseImpl;
    }
    using BasicPromise = Internal::PromiseImpl<BasicMiniObject>;
    using Promise = Internal::PromiseImpl<MiniObject>;

    template<typename T>
    constexpr bool IsPromise = std::is_base_of_v<BasicPromise, T> || std::is_base_of_v<Promise, T>;

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
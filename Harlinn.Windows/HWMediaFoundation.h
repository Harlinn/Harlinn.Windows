#pragma once
#ifndef HARLINN_WINDOWS_HWMEDIAFOUNDATION_H_
#define HARLINN_WINDOWS_HWMEDIAFOUNDATION_H_

#include <HWMFIDL.h>
#include <HCCComImpl.h>

namespace Harlinn::Windows::MF
{
    class MediaFoundation
    {
    public:
        MediaFoundation()
        {
            auto hr = MFStartup(MF_VERSION, MFSTARTUP_FULL);
            HCC_COM_CHECK_HRESULT(hr);
        }
        ~MediaFoundation()
        {
            auto hr = ::MFShutdown();
            HCC_COM_CHECK_HRESULT(hr);
        }
    };
    using Init = MediaFoundation;


    class IMFAsyncCallbackImplBase abstract : public Com::IUknownImpl<IMFAsyncCallbackImplBase, IMFAsyncCallback>
    {
        DWORD flags_ = 0;
        DWORD queue_ = 0;
    public:
        IMFAsyncCallbackImplBase(DWORD flags = 0, DWORD queue = MFASYNC_CALLBACK_QUEUE_MULTITHREADED)
            : flags_(flags), queue_(queue) 
        {}

        DWORD Queue() const { return queue_; }
        DWORD Flags() const { return flags_; }

        // IMFAsyncCallback methods
        IFACEMETHODIMP GetParameters(DWORD* flags, DWORD* queue)
        {
            if (flags == nullptr || queue == nullptr)
            {
                return E_POINTER;
            }
            *flags = flags_;
            *queue = queue_;
            return S_OK;
        }
    };


    namespace Internal
    {
        template <class Function, class... Args>
        class IMFAsyncCallbackFunctionImpl : public IMFAsyncCallbackImplBase
        {
        public:
            using Base = IMFAsyncCallbackImplBase;
        private:
            using TupleType = std::tuple<std::decay_t<Function>, std::decay_t<Args>...>;
            TupleType data_;

            template <class TupleType, size_t... indices>
            static void Call(TupleType& tuple) noexcept
            {
                std::invoke(std::move(std::get<indices>(tuple))...);
            }

            template <class TupleType, size_t... indices>
            static constexpr auto MakeCaller(std::index_sequence<indices...>) noexcept
            {
                return &Call<TupleType, indices...>;
            }
            
        public:

            template <class FunctionT, class... ArgsT>
            explicit IMFAsyncCallbackFunctionImpl(DWORD callbackFlags, DWORD queueId, FunctionT&& function, ArgsT&&... args)
                : Base(callbackFlags, queueId), data_(std::forward<FunctionT>(function), std::forward<ArgsT>(args)...)
            {
            }


            IFACEMETHODIMP Invoke(_In_opt_ IMFAsyncResult* /*asyncResult*/) noexcept override
            {
                try
                {
                    using Indices = std::make_index_sequence < 1 + sizeof...(Args)>;
                    constexpr auto caller = MakeCaller<TupleType>(std::make_index_sequence<1 + sizeof...(Args)>{});
                    caller(data_);
                    return S_OK;
                }
                HCC_COM_CATCH_ALL_REPORT_EXCEPTION_AND_RETURN_HRESULT();
            }
        };
    }

    template <class Function, class... Args>
    MFAsyncCallback MakeIMFAsyncCallback(DWORD callbackFlags, DWORD queueId, Function&& function, Args&&... args)
    {
        using CallbackType = Internal::IMFAsyncCallbackFunctionImpl<Function, Args...>;
        CallbackType* callbackPtr = new CallbackType(callbackFlags, queueId, std::forward<Function>(function), std::forward<Args>(args)...);
        return MFAsyncCallback(callbackPtr);
    }

    template <class Function, class... Args>
    MFAsyncCallback MakeIMFAsyncCallback(Function&& function, Args&&... args)
    {
        using CallbackType = Internal::IMFAsyncCallbackFunctionImpl<Function, Args...>;
        CallbackType* callbackPtr = new CallbackType(0, MFASYNC_CALLBACK_QUEUE_MULTITHREADED, std::forward<Function>(function), std::forward<Args>(args)...);
        return MFAsyncCallback(callbackPtr);
    }


    class DeviceSources
    {
        IMFActivate** sources_ = nullptr;
        UINT32 sourceCount_ = 0;
    public:
        DeviceSources()
        { }

        DeviceSources(IMFActivate** sources, UINT32 sourceCount)
            : sources_(sources), sourceCount_(sourceCount)
        { }

        DeviceSources(IMFAttributes* attributes)
        {
            auto hr = MFEnumDeviceSources(attributes, &sources_, &sourceCount_);
            HCC_COM_CHECK_HRESULT(hr);
        }


        DeviceSources(const DeviceSources&) = delete;
        DeviceSources& operator = (const DeviceSources&) = delete;

        DeviceSources(DeviceSources&& other) noexcept
            : sources_(other.sources_), sourceCount_(other.sourceCount_) 
        {
            other.sources_ = nullptr;
            other.sourceCount_ = 0;
        }
        DeviceSources& operator = (DeviceSources&& other) noexcept
        {
            if (&other != this)
            {
                std::swap(sources_, other.sources_);
                std::swap(sourceCount_, other.sourceCount_);
            }
            return *this;
        }

        ~DeviceSources()
        {
            clear();
        }

        static DeviceSources Create(const Guid& sourceType)
        {
            auto attributes = MFAttributes::Create(1);
            attributes.SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, sourceType);
            return DeviceSources(attributes);
        }

        static DeviceSources CreateAudioDeviceSources()
        {
            return Create(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_AUDCAP_GUID);
        }

        static DeviceSources CreateVideoDeviceSources()
        {
            return Create(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);
        }


        void clear()
        {
            if (sources_)
            {
                for (UINT32 i = 0; i < sourceCount_; i++)
                {
                    auto tmp = sources_[i];
                    sources_[i] = nullptr;
                    if (tmp)
                    {
                        tmp->Release();
                    }
                }
                CoTaskMemFree(sources_);
            }
        }

        size_t size() const
        {
            return static_cast<size_t>(sourceCount_);
        }

        MFActivate operator[](size_t index) const
        {
            if (index < sourceCount_)
            {
                auto itf = sources_[index];
                return MFActivate(itf, true);
            }
            else
            {
                return MFActivate();
            }
        }


    };


    MFMediaSource GetCameraMediaSource(DWORD cameraIndex)
    {
        auto deviceSources = MF::DeviceSources::CreateVideoDeviceSources();
        auto deviceSourceActivate = deviceSources[cameraIndex];
        auto result = deviceSourceActivate.ActivateObject<MFMediaSource>();
        return result;
    }

    
    HW_EXPORT std::wstring GetGUIDNameConst(const Guid& id);
    HW_EXPORT std::wstring GetMediaTypeDescription(const MFMediaType& mediaType);


}


#endif

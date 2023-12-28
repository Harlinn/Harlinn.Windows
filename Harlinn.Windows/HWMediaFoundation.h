#pragma once
#ifndef HARLINN_WINDOWS_HWMEDIAFOUNDATION_H_
#define HARLINN_WINDOWS_HWMEDIAFOUNDATION_H_

#include <HWMFIDL.h>
#include <HWMFReadWrite.h>
#include <HCCComImpl.h>
#include <HCCCom.h>

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


    class IMFAsyncCallbackImplBase abstract : public Com::ObjectBase<IMFAsyncCallbackImplBase, IMFAsyncCallback>,  public Com::IUnknownImpl<IMFAsyncCallbackImplBase, IMFAsyncCallback>
    {
        DWORD flags_ = 0;
        DWORD queue_ = 0;
    public:
        using ObjectBaseType = Com::ObjectBase<IMFAsyncCallbackImplBase, IMFAsyncCallback>;

        using ObjectBaseType::QueryInterface;
        using ObjectBaseType::AddRef;
        using ObjectBaseType::Release;


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
            return DeviceSources(attributes.GetInterfacePointer<IMFAttributes>());
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


    inline MFMediaSource GetCameraMediaSource(DWORD cameraIndex)
    {
        auto deviceSources = MF::DeviceSources::CreateVideoDeviceSources();
        auto deviceSourceActivate = deviceSources[cameraIndex];
        auto result = deviceSourceActivate.ActivateObject<MFMediaSource>();
        return result;
    }

    
    HW_EXPORT WideString GetGUIDNameConst(const Guid& id);
    HW_EXPORT WideString GetAttributeValue( const MFAttributes& attributes, const Guid& attributeKey );
    HW_EXPORT WideString GetMediaTypeDescription(const MFMediaType& mediaType);

    inline void PrintMediaTypeDescriptions( const std::vector<MFMediaType>& mediaTypes )
    {
        for ( const auto& mediaType : mediaTypes )
        {
            auto mediaTypeDescription = GetMediaTypeDescription( mediaType );
            _putws( mediaTypeDescription.c_str( ) );
        }
    }

    inline void PrintMediaTypeDescription( const MFMediaType& mediaType )
    {
        auto mediaTypeDescription = GetMediaTypeDescription( mediaType );
        _putws( mediaTypeDescription.c_str( ) );
    }

    inline void PrintMediaTypeDescriptions( DWORD streamIndex, const Harlinn::Windows::MFSourceReader& sourceReader )
    {
        auto nativeMediaTypes = sourceReader.GetNativeMediaTypes( streamIndex );
        PrintMediaTypeDescriptions( nativeMediaTypes );
    }

    inline void PrintInputMediaTypeDescriptions( DWORD streamIndex, const Harlinn::Windows::MFTransform& transform )
    {
        auto mediaTypes = transform.GetInputAvailableTypes( streamIndex );
        PrintMediaTypeDescriptions( mediaTypes );
    }

    inline void PrintOutputMediaTypeDescriptions( DWORD streamIndex, const Harlinn::Windows::MFTransform& transform )
    {
        auto mediaTypes = transform.GetOutputAvailableTypes( streamIndex );
        PrintMediaTypeDescriptions( mediaTypes );
    }


    enum class EnumTransformsFlags : UInt32
    {
        None = 0,
        Synchronous = _MFT_ENUM_FLAG::MFT_ENUM_FLAG_SYNCMFT,
        Asynchronous = _MFT_ENUM_FLAG::MFT_ENUM_FLAG_ASYNCMFT,
        Hardware = _MFT_ENUM_FLAG::MFT_ENUM_FLAG_HARDWARE,
        FieldOfUse = _MFT_ENUM_FLAG::MFT_ENUM_FLAG_FIELDOFUSE,
        Local = _MFT_ENUM_FLAG::MFT_ENUM_FLAG_LOCALMFT,
        TranscodeOnly = _MFT_ENUM_FLAG::MFT_ENUM_FLAG_TRANSCODE_ONLY,
        SortAndFilter = _MFT_ENUM_FLAG::MFT_ENUM_FLAG_SORTANDFILTER,
        SortAndFilterApprovedOnly = _MFT_ENUM_FLAG::MFT_ENUM_FLAG_SORTANDFILTER_APPROVED_ONLY,
        SortAndFilterWebOnly = _MFT_ENUM_FLAG::MFT_ENUM_FLAG_SORTANDFILTER_WEB_ONLY,
        SortAndFilterWebOnlyEdgeMode = _MFT_ENUM_FLAG::MFT_ENUM_FLAG_SORTANDFILTER_WEB_ONLY_EDGEMODE,
        UntrustedStore = _MFT_ENUM_FLAG::MFT_ENUM_FLAG_UNTRUSTED_STOREMFT,
        All = _MFT_ENUM_FLAG::MFT_ENUM_FLAG_ALL
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( EnumTransformsFlags, UInt32 );


    using TransformRegisterTypeInfo = MFT_REGISTER_TYPE_INFO;


    class Transforms
    {
        IMFActivate** transforms_ = nullptr;
        UINT32 transformCount_ = 0;
    public:
        Transforms( ) = default;
        Transforms( const GUID& transformCategory, EnumTransformsFlags flags, const TransformRegisterTypeInfo* inputType = nullptr, const TransformRegisterTypeInfo* outputType = nullptr )
        {
             auto hr = MFTEnumEx( transformCategory, static_cast< UINT32 >( flags ), inputType, outputType, &transforms_, &transformCount_ );
             HCC_COM_CHECK_HRESULT( hr );
        }


        Transforms( const Transforms& ) = delete;
        Transforms& operator = ( const Transforms& ) = delete;

        Transforms( Transforms&& other ) noexcept
            : transforms_( other.transforms_ ), transformCount_( other.transformCount_ )
        {
            other.transforms_ = nullptr;
            other.transformCount_ = 0;
        }
        Transforms& operator = ( Transforms&& other ) noexcept
        {
            if ( &other != this )
            {
                std::swap( transforms_, other.transforms_ );
                std::swap( transformCount_, other.transformCount_ );
            }
            return *this;
        }

        ~Transforms()
        {
            clear( );
        }

        static Transforms AudioDecoders( EnumTransformsFlags flags = EnumTransformsFlags::All, const TransformRegisterTypeInfo* inputType = nullptr, const TransformRegisterTypeInfo* outputType = nullptr )
        {
            return Transforms( MFT_CATEGORY_AUDIO_DECODER, flags, inputType, outputType );
        }
        static Transforms AudioEffects( EnumTransformsFlags flags = EnumTransformsFlags::All, const TransformRegisterTypeInfo* inputType = nullptr, const TransformRegisterTypeInfo* outputType = nullptr )
        {
            return Transforms( MFT_CATEGORY_AUDIO_EFFECT, flags, inputType, outputType );
        }
        static Transforms AudioEncoders( EnumTransformsFlags flags = EnumTransformsFlags::All, const TransformRegisterTypeInfo* inputType = nullptr, const TransformRegisterTypeInfo* outputType = nullptr )
        {
            return Transforms( MFT_CATEGORY_AUDIO_ENCODER, flags, inputType, outputType );
        }
        static Transforms Demultiplexers( EnumTransformsFlags flags = EnumTransformsFlags::All, const TransformRegisterTypeInfo* inputType = nullptr, const TransformRegisterTypeInfo* outputType = nullptr )
        {
            return Transforms( MFT_CATEGORY_DEMULTIPLEXER, flags, inputType, outputType );
        }
        static Transforms Multiplexers( EnumTransformsFlags flags = EnumTransformsFlags::All, const TransformRegisterTypeInfo* inputType = nullptr, const TransformRegisterTypeInfo* outputType = nullptr )
        {
            return Transforms( MFT_CATEGORY_MULTIPLEXER, flags, inputType, outputType );
        }
        static Transforms OtherTransforms( EnumTransformsFlags flags = EnumTransformsFlags::All, const TransformRegisterTypeInfo* inputType = nullptr, const TransformRegisterTypeInfo* outputType = nullptr )
        {
            return Transforms( MFT_CATEGORY_OTHER, flags, inputType, outputType );
        }
        static Transforms VideoDecoders( EnumTransformsFlags flags = EnumTransformsFlags::All, const TransformRegisterTypeInfo* inputType = nullptr, const TransformRegisterTypeInfo* outputType = nullptr )
        {
            return Transforms( MFT_CATEGORY_VIDEO_DECODER, flags, inputType, outputType );
        }
        static Transforms VideoEffects( EnumTransformsFlags flags = EnumTransformsFlags::All, const TransformRegisterTypeInfo* inputType = nullptr, const TransformRegisterTypeInfo* outputType = nullptr )
        {
            return Transforms( MFT_CATEGORY_VIDEO_EFFECT, flags, inputType, outputType );
        }
        static Transforms VideoRendererEffects( EnumTransformsFlags flags = EnumTransformsFlags::All, const TransformRegisterTypeInfo* inputType = nullptr, const TransformRegisterTypeInfo* outputType = nullptr )
        {
            return Transforms( MFT_CATEGORY_VIDEO_RENDERER_EFFECT, flags, inputType, outputType );
        }
        static Transforms VideoEncoders( EnumTransformsFlags flags = EnumTransformsFlags::Hardware | EnumTransformsFlags::Asynchronous | EnumTransformsFlags::Synchronous, const TransformRegisterTypeInfo* inputType = nullptr, const TransformRegisterTypeInfo* outputType = nullptr )
        {
            return Transforms( MFT_CATEGORY_VIDEO_ENCODER, flags, inputType, outputType );
        }
        static Transforms VideoProcessors( EnumTransformsFlags flags = EnumTransformsFlags::All, const TransformRegisterTypeInfo* inputType = nullptr, const TransformRegisterTypeInfo* outputType = nullptr )
        {
            return Transforms( MFT_CATEGORY_VIDEO_PROCESSOR, flags, inputType, outputType );
        }


        void clear( )
        {
            if ( transforms_ )
            {
                for ( UINT32 i = 0; i < transformCount_; i++ )
                {
                    auto tmp = transforms_[ i ];
                    transforms_[ i ] = nullptr;
                    if ( tmp )
                    {
                        tmp->Release( );
                    }
                }
                CoTaskMemFree( transforms_ );
            }
        }

        size_t size( ) const
        {
            return static_cast< size_t >( transformCount_ );
        }

        MFActivate operator[]( size_t index ) const
        {
            if ( index < transformCount_ )
            {
                auto itf = transforms_[ index ];
                return MFActivate( itf, true );
            }
            else
            {
                return MFActivate( );
            }
        }
    };


    void PrintAttribute( const MFAttributes& attributes, const Guid& attributeKey )
    {
        auto keyName = GetGUIDNameConst( attributeKey );
        if ( !keyName )
        {
            keyName = attributeKey.ToString( );
        }
        auto value = GetAttributeValue( attributes, attributeKey );
        if ( value )
        {
            auto text = Format( L"{}: {}", keyName, value );
            _putws( text.c_str() );
        }
        else
        {
            auto text = Format( L"{}: <Unsupported type>", keyName );
            _putws( text.c_str( ) );
        }
    }

    void PrintAttributes( const MFAttributes& attributes )
    {
        if ( attributes )
        {
            auto attributeCount = attributes.GetCount( );
            for ( size_t j = 0; j < attributeCount; j++ )
            {
                Guid attributeKey;
                attributes.GetItemByIndex( static_cast< UINT32 >( j ), &attributeKey, nullptr );
                PrintAttribute( attributes, attributeKey );
            }
        }
    }


    void PrintTransforms( const Transforms& transforms )
    {
        auto transformCount = transforms.size( );
        for ( size_t i = 0; i < transformCount; i++ )
        {
            auto mfActivate = transforms[ i ];
            _putws( L"mfActivate Interfaces:" );
            Com::PrintSupportedKnownInterfaces( mfActivate.GetInterfacePointer( ) );

            _putws( L"mfActivate Attributes:" );
            PrintAttributes( mfActivate );

            auto transform = mfActivate.ActivateObject<MFTransform>( );
            if ( transform )
            {
                _putws( L"transform Interfaces:" );
                Com::PrintSupportedKnownInterfaces( transform.GetInterfacePointer( ) );

                MFAttributes transformAttributes = transform.GetAttributes( );
                if ( transformAttributes )
                {
                    _putws( L"transform Attributes:" );
                    PrintAttributes( transformAttributes );
                }
            }
        }
    }

    void PrintVideoEncoders( )
    {
        auto transforms = Transforms::VideoEncoders( );
        PrintTransforms( transforms );
    }
    void PrintVideoDecoders( )
    {
        auto transforms = Transforms::VideoDecoders( );
        PrintTransforms( transforms );
    }
    

}


#endif

#pragma once
#ifndef __HCCVARIANT_H__
#define __HCCVARIANT_H__

#include <HCCLib.h>
#include <HCCCom.h>
#include <HCCDateTime.h>
#include <HCCCurrency.h>

namespace Harlinn::Common::Core
{
    class RecordInfo;

    // ----------------------------------------------------------------------
    // VariantType
    // ----------------------------------------------------------------------
    enum class VariantType : unsigned short
    {
        Empty = 0,
        Null = 1,
        Int2 = 2,
        Short = 2,
        Int16 = 2,
        Int4 = 3,
        Long = 3,
        Int32 = 3,
        Real4 = 4,
        Float = 4,
        Single = 4,
        Real8 = 5,
        Double = 5,
        Currency = 6,
        DateTime = 7,
        BStr = 8,
        Dispatch = 9,
        Error = 10,
        Bool = 11,
        Variant = 12,
        Unknown = 13,
        Decimal = 14,
        Int1 = 16,
        SByte = 16,
        UInt1 = 17,
        Byte = 17,
        UInt2 = 18,
        UShort = 18,
        UInt16 = 18,
        UInt4 = 19,
        UInt32 = 19,
        ULong = 19,
        Int8 = 20,
        Int64 = 20,
        LongLong = 20,
        UInt8 = 21,
        UInt64 = 21,
        ULongLong = 21,
        Int = 22,
        UInt = 23,
        Void = 24,
        HResult = 25,
        Pointer = 26,
        SafeArray = 27,
        CArray = 28,
        UserDefined = 29,
        LPStr = 30,
        LPWStr = 31,
        Record = 36,
        IntPtr = 37,
        UIntPtr = 38,
        FileTime = 64,
        Blob = 65,
        Stream = 66,
        Storage = 67,
        StreamedObject = 68,
        StoredObject = 69,
        BlobObject = 70,
        CF = 71,
        CLSID = 72,
        VersionedStream = 73,
        BStrBlob = 0xfff,
        Vector = 0x1000,
        Array = 0x2000,
        Byref = 0x4000,
        Reserved = 0x8000,
        Illegal = 0xffff,
        IllegalMasked = 0xfff,
        TypeMask = 0xfff
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( VariantType, unsigned short );

    class SysString;
    class SafeArray;

    template<typename T>
    struct VariantTypeTraits : std::false_type
    {
        static constexpr Core::VariantType VariantType = Core::VariantType::Empty;
        using ValueType = void;
        using VariantValueType = void;
        static constexpr bool RequiresConversion = false;
        static constexpr bool IsRecord = false;
    };


    namespace Internal
    {
        template<Core::VariantType vt, typename ValueT, typename VariantValueT = ValueT >
        struct VariantTypeTraits : public std::true_type
        {
            static constexpr Core::VariantType VariantType = vt;
            using ValueType = ValueT;
            using VariantValueType = VariantValueT;
            static constexpr bool RequiresConversion = false;
            static constexpr bool IsRecord = false;
        };

    }

    template<>
    struct VariantTypeTraits<bool> : public Internal::VariantTypeTraits<Core::VariantType::Bool, bool, VARIANT_BOOL >
    {
        using Base = Internal::VariantTypeTraits<Core::VariantType::Bool, bool, VARIANT_BOOL >;
        using ValueType = Base::ValueType;
        using VariantValueType = Base::VariantValueType;
        static constexpr bool RequiresConversion = true;

        static constexpr ValueType Convert( VariantValueType value )
        {
            return value != VARIANT_FALSE;
        }
        static constexpr VariantValueType Convert( ValueType value )
        {
            return value ? VARIANT_TRUE : VARIANT_FALSE;
        }
    };


    template<>
    struct VariantTypeTraits<signed char> : public Internal::VariantTypeTraits<Core::VariantType::SByte, signed char >
    {
    };

    template<>
    struct VariantTypeTraits<unsigned char> : public Internal::VariantTypeTraits<Core::VariantType::Byte, unsigned char >
    {
    };

    template<>
    struct VariantTypeTraits<wchar_t> : public Internal::VariantTypeTraits<Core::VariantType::UShort, wchar_t, unsigned short >
    {
        using Base = Internal::VariantTypeTraits<Core::VariantType::UShort, wchar_t, unsigned short >;
        using ValueType = Base::ValueType;
        using VariantValueType = Base::VariantValueType;
        static constexpr bool RequiresConversion = true;

        static constexpr ValueType Convert( VariantValueType value )
        {
            return static_cast< ValueType >(value);
        }
        static constexpr VariantValueType Convert( ValueType value )
        {
            return static_cast< VariantValueType >( value );
        }
    };

    template<>
    struct VariantTypeTraits<WideString> : public Internal::VariantTypeTraits<Core::VariantType::BStr, WideString, BSTR >
    {
        using Base = Internal::VariantTypeTraits<Core::VariantType::BStr, WideString, BSTR >;
        using ValueType = Base::ValueType;
        using VariantValueType = Base::VariantValueType;
        static constexpr bool RequiresConversion = true;

        static ValueType Convert( VariantValueType value )
        {
            if ( value )
            {
                auto length = static_cast<size_t>(SysStringLen( value ));
                return ValueType( reinterpret_cast< const wchar_t* >( value ), length );
            }
            else
            {
                return {};
            }
            return static_cast< ValueType >( value );
        }
        static VariantValueType Convert( const ValueType& value )
        {
            auto valueSize = value.size( );
            if ( valueSize )
            {
                return SysAllocStringLen( value.c_str( ), static_cast< UINT >( valueSize ) );
            }
            else
            {
                return nullptr;
            }
        }
    };


    template<>
    struct VariantTypeTraits<short> : public Internal::VariantTypeTraits<Core::VariantType::Short, short >
    {
    };

    template<>
    struct VariantTypeTraits<unsigned short> : public Internal::VariantTypeTraits<Core::VariantType::UShort, unsigned short >
    {
    };

    template<>
    struct VariantTypeTraits<long> : public Internal::VariantTypeTraits<Core::VariantType::Long, long >
    {
    };

    template<>
    struct VariantTypeTraits<unsigned long> : public Internal::VariantTypeTraits<Core::VariantType::ULong, unsigned long >
    {
    };

    template<>
    struct VariantTypeTraits<int> : public Internal::VariantTypeTraits<Core::VariantType::Long, int, long >
    {
    };

    template<>
    struct VariantTypeTraits<unsigned int> : public Internal::VariantTypeTraits<Core::VariantType::ULong, unsigned int, unsigned long >
    {
    };


    template<>
    struct VariantTypeTraits<long long> : public Internal::VariantTypeTraits<Core::VariantType::LongLong, long long >
    {
    };

    template<>
    struct VariantTypeTraits<unsigned long long> : public Internal::VariantTypeTraits<Core::VariantType::ULongLong, unsigned long long >
    {
    };

    template<>
    struct VariantTypeTraits<float> : public Internal::VariantTypeTraits<Core::VariantType::Real4, float >
    {
    };

    template<>
    struct VariantTypeTraits<double> : public Internal::VariantTypeTraits<Core::VariantType::Real8, double >
    {
    };



    // ----------------------------------------------------------------------
    // SysString
    // ----------------------------------------------------------------------
    class SysString
    {
        BSTR bstr_;
    public:

        static BSTR Copy( const BSTR bstr )
        {
            if ( bstr )
            {
                UINT length = SysStringLen( bstr );
                auto result = SysAllocStringLen( bstr, length );
                if ( ( !result ) && length )
                {
                    CheckHRESULT( E_OUTOFMEMORY );
                }
                return result;
            }
            return nullptr;
        }

        constexpr SysString( ) noexcept
            : bstr_( 0 )
        {
        }

        explicit SysString( const WideString& str )
            : bstr_( 0 )
        {
            bstr_ = SysAllocStringLen( str.c_str( ), UINT( str.length( ) ) );
            if ( ( bstr_ == nullptr ) && ( str.length( ) ) )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
        }


        explicit SysString( const AnsiString& str )
            : bstr_( 0 )
        {
            auto wstr = Core::ToWideString( str );
            bstr_ = SysAllocStringLen( wstr.c_str( ), UINT( wstr.length( ) ) );
            if ( ( bstr_ == nullptr ) && ( wstr.length( ) ) )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
        }


        explicit SysString( const wchar_t* str, bool attach = false )
            : bstr_( 0 )
        {
            if ( !attach )
            {
                bstr_ = SysAllocString( str );
                if ( ( bstr_ == nullptr ) && str && str[0] )
                {
                    CheckHRESULT( E_OUTOFMEMORY );
                }
            }
            else
            {
                bstr_ = (BSTR)str;
            }
        }

        explicit SysString( const wchar_t* str, size_t strLength )
            : bstr_( 0 )
        {
            bstr_ = SysAllocStringLen( str, UINT( strLength ) );
            if ( ( bstr_ == nullptr ) && str && str[0] )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
        }

        SysString( const SysString& other )
            : bstr_( Copy( other.bstr_ ) )
        {
        }

        SysString( SysString&& other ) noexcept
            : bstr_( other.bstr_ )
        {
            other.bstr_ = nullptr;
        }


        ~SysString( ) noexcept
        {
            if ( bstr_ )
            {
                SysFreeString( bstr_ );
            }
        }


        SysString& operator = ( const SysString& other )
        {
            if ( bstr_ != other.bstr_ )
            {
                if ( bstr_ )
                {
                    SysFreeString( bstr_ );
                    bstr_ = nullptr;
                }
                bstr_ = Copy( other.bstr_ );
            }
            return *this;
        }

        SysString& operator = ( SysString&& other ) noexcept
        {
            if ( this != &other )
            {
                if ( bstr_ )
                {
                    SysFreeString( bstr_ );
                }
                bstr_ = other.bstr_;
                other.bstr_ = nullptr;
            }
            return *this;
        }


        bool operator == ( const SysString& other ) const
        {
            if ( bstr_ != other.bstr_ )
            {
                if ( bstr_ && other.bstr_ )
                {
                    auto len = SysStringLen( bstr_ );
                    auto lenOther = SysStringLen( other.bstr_ );
                    if ( len == lenOther )
                    {
                        return wmemcmp( bstr_, other.bstr_, len ) == 0;
                    }
                }
                return false;
            }
            else
            {
                return true;
            }
        }

        bool operator == ( const wchar_t* other ) const
        {
            if ( bstr_ != other )
            {
                if ( bstr_ && other )
                {
                    auto len = SysStringLen( bstr_ );
                    auto lenOther = wcslen( other );
                    if ( len == lenOther )
                    {
                        return wmemcmp( bstr_, other, len ) == 0;
                    }
                }
                return false;
            }
            else
            {
                return true;
            }
        }

        bool operator == ( const WideString& other ) const
        {
            if ( bstr_ )
            {
                auto len = SysStringLen( bstr_ );
                auto lenOther = other.size();
                if ( len == lenOther )
                {
                    return wmemcmp( bstr_, other.data(), len ) == 0;
                }
                return false;
            }
            else
            {
                return other.empty( );
            }
        }

        bool empty( ) const
        {
            if ( bstr_ )
            {
                auto len = SysStringLen( bstr_ );
                return len > 0;
            }
            return true;
        }


        int CompareTo( const SysString& other ) const
        {
            if ( bstr_ != other.bstr_ )
            {
                auto len = length( );
                auto otherLen = other.length( );
                auto maxCompareLength = std::min( len, otherLen );
                auto result = wmemcmp( bstr_, other.data( ), maxCompareLength );
                if ( result == 0 )
                {
                    if ( len == otherLen )
                    {
                        return 0;
                    }
                    return len < otherLen ? -1 : 1;
                }
                return result;
            }
            else
            {
                return 0;
            }
        }

        int CompareTo( const wchar_t* other ) const
        {
            if ( bstr_ != other )
            {
                auto len = length( );
                auto otherLen = wcslen(other);
                auto maxCompareLength = std::min( len, otherLen );
                auto result = wmemcmp( bstr_, other, maxCompareLength );
                if ( result == 0 )
                {
                    if ( len == otherLen )
                    {
                        return 0;
                    }
                    return len < otherLen ? -1 : 1;
                }
                return result;
            }
            else
            {
                return 0;
            }
        }

        int CompareTo( const WideString& other ) const
        {
            if ( bstr_ != other )
            {
                auto len = length( );
                auto otherLen = other.size();
                auto maxCompareLength = std::min( len, otherLen );
                auto result = wmemcmp( bstr_, other.data(), maxCompareLength );
                if ( result == 0 )
                {
                    if ( len == otherLen )
                    {
                        return 0;
                    }
                    return len < otherLen ? -1 : 1;
                }
                return result;
            }
            else
            {
                return 0;
            }
        }




        SysString& Attach( BSTR other ) noexcept
        {
            if ( bstr_ != other )
            {
                if ( bstr_ )
                {
                    SysFreeString( bstr_ );
                }
                bstr_ = other;
            }
            return *this;
        }

        explicit operator bool( ) const noexcept
        {
            return bstr_ != nullptr;
        }

        BSTR Detach( ) noexcept
        {
            auto result = bstr_;
            bstr_ = nullptr;
            return result;
        }



        BSTR Copy( ) const
        {
            return Copy( bstr_ );
        }


        const BSTR c_str( ) const noexcept
        {
            return bstr_;
        }

        const BSTR data( ) const noexcept
        {
            return bstr_;
        }

        size_t length( ) const noexcept
        {
            if ( bstr_ )
            {
                return size_t( SysStringLen( bstr_ ) );
            }
            return 0;
        }

        size_t size( ) const noexcept
        {
            return length( );
        }


        OLECHAR At( size_t index ) const noexcept
        {
            return bstr_[index];
        }

        OLECHAR& At( size_t index ) noexcept
        {
            return bstr_[index];
        }

        OLECHAR operator []( size_t index ) const noexcept
        {
            return bstr_[index];
        }

        OLECHAR& operator []( size_t index ) noexcept
        {
            return bstr_[index];
        }

        WideString ToString( )
        {
            if ( bstr_ )
            {
                auto size = size_t( SysStringLen( bstr_ ) );
                return WideString( bstr_, size );
            }
            return {};
        }

    };

    // ----------------------------------------------------------------------
    // AttachedSysString
    // ----------------------------------------------------------------------
    class AttachedSysString : public SysString
    {
    public:
        using Base = SysString;
        explicit AttachedSysString( const wchar_t* str )
            : Base( str, true )
        { }

        ~AttachedSysString( )
        {
            Detach( );
        }

    };

    // ----------------------------------------------------------------------
    // SafeArray
    // ----------------------------------------------------------------------
    class SafeArray
    {
        template<typename T>
        friend class VariantT;
        SAFEARRAY* ptr_ = nullptr;
    public:
        class Bound : public SAFEARRAYBOUND
        {
        public:
            using Base = SAFEARRAYBOUND;
            Bound( ULONG numberOfElements, LONG lowerBound )
                : Base{ numberOfElements, lowerBound }
            { }

            size_t size( ) const
            {
                return cElements;
            }

            ptrdiff_t LowerBound( ) const
            {
                return static_cast< ptrdiff_t >( lLbound );
            }

            ptrdiff_t UpperBound( ) const
            {
                return LowerBound( ) + static_cast< ptrdiff_t >( size() );
            }


        };


        static VariantType GetElementVariantType( SAFEARRAY* safeArray )
        {
            if ( safeArray )
            {
                if ( safeArray->fFeatures & FADF_DISPATCH )
                {
                    return VariantType::Dispatch;
                }
                if ( safeArray->fFeatures & FADF_UNKNOWN )
                {
                    return VariantType::Unknown;
                }
                if ( safeArray->fFeatures & FADF_VARIANT )
                {
                    return VariantType::Variant;
                }
                if ( safeArray->fFeatures & FADF_BSTR )
                {
                    return VariantType::BStr;
                }
                VARTYPE vt = 0;
                auto hr = SafeArrayGetVartype( safeArray, &vt );
                if ( FAILED( hr ) )
                {
                    CheckHRESULT( hr );
                }
            }
            else
            {
                return VariantType::Empty;
            }
        }

        // ----------------------------------------------------------------------
        // SafeArrayLock
        // ----------------------------------------------------------------------
        friend class SafeArrayLock;
        class SafeArrayLock
        {
            SAFEARRAY* safeArray_;
        public:
            constexpr explicit SafeArrayLock( ) noexcept
                : safeArray_( nullptr )
            {
            }
            SafeArrayLock( SafeArray& safeArray )
                : safeArray_( safeArray.ptr_ )
            {
                auto hr = ::SafeArrayLock( safeArray_ );
                if ( FAILED( hr ) )
                {
                    CheckHRESULT( hr );
                }
            }
            SafeArrayLock( const SafeArrayLock& other ) = delete;
            SafeArrayLock( SafeArrayLock&& other ) = default;
            SafeArrayLock& operator = ( const SafeArrayLock& other ) = delete;
            SafeArrayLock& operator = ( SafeArrayLock&& other ) noexcept
            {
                if ( this != &other )
                {
                    if ( safeArray_ )
                    {
                        SafeArrayUnlock( safeArray_ );
                    }
                    safeArray_ = other.safeArray_;
                    other.safeArray_ = nullptr;
                }
                return *this;
            }


            ~SafeArrayLock( ) noexcept
            {
                if ( safeArray_ )
                {
                    SafeArrayUnlock( safeArray_ );
                }
            }
        };
        using Lock = SafeArrayLock;

        // ----------------------------------------------------------------------
        // DataLock
        // ----------------------------------------------------------------------
        class DataLock
        {
            SAFEARRAY* safeArray_;
            void* data_;
        public:
            constexpr DataLock( ) noexcept
                : safeArray_( nullptr ), data_( nullptr )
            {
            }

            DataLock( const SafeArray& safeArray )
                : safeArray_( const_cast< SAFEARRAY* >( safeArray.ptr_ ) )
            {
                auto hr = SafeArrayAccessData( safeArray_, &data_ );
                if ( FAILED( hr ) )
                {
                    CheckHRESULT( hr );
                }
            }

            DataLock( const DataLock& other ) = delete;
            DataLock( DataLock&& other ) = default;
            DataLock& operator = ( const DataLock& other ) = delete;
            DataLock& operator = ( DataLock&& other ) noexcept
            {
                if ( this != &other )
                {
                    if ( safeArray_ )
                    {
                        SafeArrayUnaccessData( safeArray_ );
                    }
                    safeArray_ = other.safeArray_;
                    data_ = other.data_;
                    other.safeArray_ = nullptr;
                    other.data_ = nullptr;
                }
                return *this;
            }

            ~DataLock( )
            {
                if ( safeArray_ )
                {
                    SafeArrayUnaccessData( safeArray_ );
                }
            }

            template<typename T>
            T* Data( )
            {
                return reinterpret_cast<T*>( data_ );
            }
        };



        constexpr SafeArray( ) noexcept
            : ptr_( 0 )
        {
        }

        explicit SafeArray( SAFEARRAY* ptr ) noexcept
            : ptr_( ptr )
        {
        }

        explicit SafeArray( VariantType variantType, UINT numberOfElements )
            : ptr_( 0 )
        {
            ptr_ = SafeArrayCreateVectorEx( VARTYPE( variantType ), 0, numberOfElements, nullptr );
            if ( !ptr_ )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
        }

        template<SimpleSpanLike ContainerT, typename TraitsT = VariantTypeTraits< std::remove_cvref_t<typename ContainerT::value_type>> >
        explicit SafeArray( const ContainerT& container )
            : ptr_( 0 )
        {
            using TraitsType = TraitsT;

            constexpr auto variantType = TraitsType::VariantType;
            auto containerSize = container.size( );

            ptr_ = SafeArrayCreateVectorEx( static_cast< VARTYPE >( variantType ), 0, static_cast<ULONG>( containerSize ), nullptr );
            if ( !ptr_ )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
            if ( containerSize )
            {
                DataLock dataLock( *this );
                auto containerData = container.data( );
                auto data = dataLock.Data< typename TraitsType::VariantValueType >();

                if constexpr ( TraitsType::RequiresConversion )
                {
                    for ( size_t i = 0; i < containerSize; i++ )
                    {
                        data[ i ] = TraitsType::Convert( containerData[i] );
                    }
                }
                else
                {
                    memcpy( data, containerData, containerSize * sizeof( typename TraitsType::ValueType ) );
                }
            }
        }



        explicit SafeArray( VariantType variantType, LONG lowerBound, UINT numberOfElements )
            : ptr_( 0 )
        {
            ptr_ = SafeArrayCreateVectorEx( VARTYPE( variantType ), lowerBound, numberOfElements, nullptr );
            if ( !ptr_ )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
        }

        template<typename T>
            requires std::is_base_of_v<IUnknown,std::remove_cvref_t<T>>
        explicit SafeArray( UINT numberOfElements )
        {
            GUID iid = __uuidof( std::remove_cvref_t<T> );
            if constexpr ( std::is_base_of_v<IDispatch, std::remove_cvref_t<T>> )
            {
                ptr_ = SafeArrayCreateVectorEx( VT_DISPATCH, 0, numberOfElements, &iid );
            }
            else
            {
                ptr_ = SafeArrayCreateVectorEx( VT_UNKNOWN, 0, numberOfElements, &iid );
            }
            if ( !ptr_ )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
        }

        template<typename T>
            requires std::is_base_of_v<IUnknown, std::remove_cvref_t<T>>
        explicit SafeArray( LONG lowerBound, UINT numberOfElements )
        {
            GUID iid = __uuidof( std::remove_cvref_t<T> );
            if constexpr ( std::is_base_of_v<IDispatch, std::remove_cvref_t<T>> )
            {
                ptr_ = SafeArrayCreateVectorEx( VT_DISPATCH, lowerBound, numberOfElements, &iid );
            }
            else
            {
                ptr_ = SafeArrayCreateVectorEx( VT_UNKNOWN, lowerBound, numberOfElements, &iid );
            }
            if ( !ptr_ )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
        }

        explicit SafeArray(IRecordInfo* recordInfo, UINT numberOfElements )
        {
            ptr_ = SafeArrayCreateVectorEx( VT_RECORD, 0, numberOfElements, recordInfo );
            if ( !ptr_ )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
        }

        explicit SafeArray( IRecordInfo* recordInfo, LONG lowerBound, UINT numberOfElements )
        {
            ptr_ = SafeArrayCreateVectorEx( VT_RECORD, lowerBound, numberOfElements, recordInfo );
            if ( !ptr_ )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
        }




        explicit SafeArray( VariantType variantType, UINT numberOfDimensions, const SAFEARRAYBOUND* dimensionbounds )
            : ptr_( 0 )
        {
            ptr_ = SafeArrayCreate( VARTYPE( variantType ), numberOfDimensions, const_cast< SAFEARRAYBOUND* >(dimensionbounds) );
            if ( !ptr_ )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
        }

        explicit SafeArray( VariantType variantType, UINT numberOfDimensions, const Bound* dimensionbounds )
            : SafeArray( variantType, numberOfDimensions, reinterpret_cast< const SAFEARRAYBOUND* >( dimensionbounds ) )
        { }

        explicit SafeArray( VariantType variantType, UINT numberOfDimensions, const SAFEARRAYBOUND* dimensionbounds, const Guid& iid )
            : ptr_( 0 )
        {
            ptr_ = SafeArrayCreateEx( VARTYPE( variantType ), numberOfDimensions, const_cast< SAFEARRAYBOUND* >( dimensionbounds ), const_cast<Guid*>( &iid ) );
            if ( !ptr_ )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
        }

        explicit SafeArray( VariantType variantType, UINT numberOfDimensions, const Bound* dimensionbounds, const Guid& iid )
            : SafeArray( variantType, numberOfDimensions, reinterpret_cast< const SAFEARRAYBOUND* >( dimensionbounds ), iid )
        {
        }


        explicit SafeArray( IRecordInfo* recordInfo, UINT numberOfDimensions, const SAFEARRAYBOUND* dimensionbounds )
            : ptr_( 0 )
        {
            ptr_ = SafeArrayCreateEx( VT_RECORD, numberOfDimensions, const_cast< SAFEARRAYBOUND* >( dimensionbounds ), recordInfo );
            if ( !ptr_ )
            {
                CheckHRESULT( E_OUTOFMEMORY );
            }
        }

        explicit SafeArray( IRecordInfo* recordInfo, UINT numberOfDimensions, const Bound* dimensionbounds )
            : SafeArray( recordInfo, numberOfDimensions, reinterpret_cast< const SAFEARRAYBOUND* >( dimensionbounds ) )
        {
        }



        SafeArray( const SafeArray& other )
            : ptr_( 0 )
        {
            if ( other.ptr_ )
            {
                auto hr = SafeArrayCopy( other.ptr_, &ptr_ );
                if ( FAILED( hr ) )
                {
                    CheckHRESULT( hr );
                }
            }
        }


        SafeArray( SafeArray&& other ) noexcept
            : ptr_( other.ptr_ )
        {
            other.ptr_ = nullptr;
        }


        ~SafeArray( )
        {
            if ( ptr_ )
            {
                auto hr = SafeArrayDestroy( ptr_ );
                CheckHRESULT( hr );
            }
        }

        SAFEARRAY* Release( )
        {
            auto result = ptr_;
            ptr_ = nullptr;
            return result;
        }

        SAFEARRAY* Detach( )
        {
            return Release( );
        }


        /// <summary>
        /// An array that is allocated on the stack.
        /// </summary>
        bool IsAuto( ) const
        {
            if ( ptr_ )
            {
                return ( ptr_->fFeatures & FADF_AUTO ) != 0;
            }
            return false;
        }

        /// <summary>
        /// An array that is statically allocated.
        /// </summary>
        bool IsStatic( ) const
        {
            if ( ptr_ )
            {
                return ( ptr_->fFeatures & FADF_STATIC ) != 0;
            }
            return false;
        }

        /// <summary>
        /// An array that is embedded in a structure.
        /// </summary>
        bool IsEmbedded( ) const
        {
            if ( ptr_ )
            {
                return ( ptr_->fFeatures & FADF_EMBEDDED ) != 0;
            }
            return false;
        }

        /// <summary>
        /// An array that may not be resized or reallocated.
        /// </summary>
        bool IsFixedSize( ) const
        {
            if ( ptr_ )
            {
                return ( ptr_->fFeatures & FADF_FIXEDSIZE ) != 0;
            }
            return false;
        }

        /// <summary>
        /// An array that contains records. When set, there will be a pointer 
        /// to the IRecordInfo interface at negative offset 4 in the array descriptor.
        /// </summary>
        bool IsRecord( ) const
        {
            if ( ptr_ )
            {
                return ( ptr_->fFeatures & FADF_RECORD ) != 0;
            }
            return false;
        }

        /// <summary>
        /// An array that has an IID identifying interface. When set, there will be 
        /// a GUID at negative offset 16 in the safe array descriptor. Flag is set 
        /// only when FADF_DISPATCH or FADF_UNKNOWN is also set.
        /// </summary>
        bool HaveIID( ) const
        {
            if ( ptr_ )
            {
                return ( ptr_->fFeatures & FADF_HAVEIID ) != 0;
            }
            return false;
        }

        /// <summary>
        /// An array that has a variant type.
        /// </summary>
        bool HaveVariantType( ) const
        {
            if ( ptr_ )
            {
                return ( ptr_->fFeatures & FADF_HAVEVARTYPE ) != 0;
            }
            return false;
        }

        /// <summary>
        /// An array of BSTRs.
        /// </summary>
        bool IsBSTR( ) const
        {
            if ( ptr_ )
            {
                return ( ptr_->fFeatures & FADF_BSTR ) != 0;
            }
            if ( HaveVariantType( ) )
            {
                auto variantType = GetVariantType( );
                if ( variantType == VariantType::BStr )
                {
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// An array of BSTRs.
        /// </summary>
        bool IsSysString( ) const
        {
            return IsBSTR( );
        }

        /// <summary>
        /// An array of IUnknown*
        /// </summary>
        bool IsUnknown( ) const
        {
            if ( ptr_ )
            {
                return ( ptr_->fFeatures & FADF_UNKNOWN ) != 0;
            }
            return false;
        }

        /// <summary>
        /// An array of IDispatch*.
        /// </summary>
        bool IsDispatch( ) const
        {
            if ( ptr_ )
            {
                return ( ptr_->fFeatures & FADF_DISPATCH ) != 0;
            }
            return false;
        }

        /// <summary>
        /// An array of VARIANTs.
        /// </summary>
        bool IsVariant( ) const
        {
            if ( ptr_ )
            {
                return ( ptr_->fFeatures & FADF_VARIANT ) != 0;
            }
            return false;
        }





        SafeArray& operator = ( const SafeArray& other )
        {
            if (  ptr_ != other.ptr_  )
            {
                if ( ptr_ )
                {
                    auto hr = SafeArrayDestroy( ptr_ );
                    CheckHRESULT( hr );
                    ptr_ = nullptr;
                }
                auto hr = SafeArrayCopy( other.ptr_, &ptr_ );
                if ( FAILED( hr ) )
                {
                    CheckHRESULT( hr );
                }
            }
            return *this;
        }

        SafeArray& operator = ( SafeArray&& other )
        {
            if ( this != &other )
            {
                if ( ptr_ )
                {
                    auto hr = SafeArrayDestroy( ptr_ );
                    CheckHRESULT( hr );
                    ptr_ = nullptr;
                }
                ptr_ = other.ptr_;
                other.ptr_ = nullptr;
            }
            return *this;
        }

        SAFEARRAY* AsSAFEARRAY( )
        {
            return ptr_;
        }

        operator SAFEARRAY** ( )
        {
            return &ptr_;
        }
        operator SAFEARRAY* ( )
        {
            return ptr_;
        }

        UINT Dimensions( ) const
        {
            return SafeArrayGetDim( ptr_ );
        }

        LONG LowerBound( UINT dimension ) const
        {
            LONG result = 0;
            auto hr = SafeArrayGetLBound( ptr_, dimension, &result );
            CheckHRESULT( hr );
            return result;
        }

        LONG UpperBound( UINT dimension ) const
        {
            LONG result = 0;
            auto hr = SafeArrayGetUBound( ptr_, dimension, &result );
            CheckHRESULT( hr );
            return result;
        }

        Bound* Bounds( ) const
        {
            if ( ptr_ )
            {
                return reinterpret_cast< Bound* >( ptr_->rgsabound );
            }
            return nullptr;
        }

        Bound& Bounds( UINT dimension ) const
        {
            if ( ptr_ )
            {
                if ( dimension < static_cast< UINT >( ptr_->cDims ) )
                {
                    return reinterpret_cast< Bound& >( ptr_->rgsabound[ dimension ] );
                }
                CheckHRESULT( DISP_E_BADINDEX );
            }
            CheckHRESULT( E_HANDLE );
        }

        size_t size( ) const
        {
            size_t result = 0;
            auto dimensions = Dimensions( );
            auto bounds = Bounds( );
            for ( UINT i = 0; i < dimensions; i++ )
            {
                result += bounds[ i ].size( );
            }
            return result;
        }

        size_t Length( ) const
        {
            return size( );
        }

        size_t ElementSize( ) const
        {
            if ( ptr_ )
            {
                return ptr_->cbElements;
            }
            return 0;
        }

        void* Data( ) const
        {
            if ( ptr_ )
            {
                return ptr_->pvData;
            }
            return nullptr;
        }

        Guid GetIID( ) const
        {
            if ( ptr_ )
            {
                Guid result;
                auto hr = SafeArrayGetIID( ptr_, reinterpret_cast< GUID* >( &result ) );
                CheckHRESULT( hr );
                return result;
            }
            return Guid();
        }

        void SetIID( const Guid& iid ) const
        {
            if ( ptr_ )
            {
                auto hr = SafeArraySetIID( ptr_, iid );
                CheckHRESULT( hr );
            }
            else
            {
                CheckHRESULT( E_HANDLE );
            }
        }

        inline RecordInfo GetRecordInfo( ) const;

        void SetRecordInfo( IRecordInfo* recordInfo ) const
        {
            if ( ptr_ )
            {
                auto hr = SafeArraySetRecordInfo( ptr_, recordInfo );
                CheckHRESULT( hr );
            }
            else
            {
                CheckHRESULT( E_HANDLE );
            }
        }


        VariantType GetVariantType( ) const
        {
            if ( ptr_ )
            {
                VariantType result;
                auto hr = SafeArrayGetVartype( ptr_, reinterpret_cast< VARTYPE* >( &result ) );
                CheckHRESULT( hr );
                return result;
            }
            return VariantType::Empty;
        }

        template<SimpleSpanLike ContainerT, typename TraitsT = VariantTypeTraits< std::remove_cvref_t<typename ContainerT::value_type>> >
        void AssignTo( ContainerT& container ) const
        {
            using TraitsType = TraitsT;
            if ( Dimensions( ) == 1 )
            {
                if ( HaveVariantType( ) )
                {
                    auto variantType = GetVariantType( );
                    if ( TraitsType::VariantType == variantType )
                    {
                        DataLock dataLock( *this );
                        auto length = static_cast<size_t>(Length( ));
                        auto* dataPtr = dataLock.Data<typename TraitsType::VariantValueType>( );
                        if constexpr ( TraitsType::RequiresConversion )
                        {
                            container.resize( length );
                            for ( size_t i = 0; i < length; i++ )
                            {
                                container[ i ] = TraitsType::Convert( dataPtr[ i ] );
                            }
                        }
                        else
                        {
                            container.assign( dataPtr, dataPtr + length );
                        }
                    }
                    else
                    {
                        HCC_THROW( ArgumentException, L"Unexpected variant type, does not match value type of container." );
                    }
                }
                else
                {
                    HCC_THROW( InvalidOperationException, L"Variant type is required." );
                }
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"SAFEARRAY is not a vector." );
            }
        }


        template<SimpleSpanLike ContainerT, typename TraitsT = VariantTypeTraits< std::remove_cvref_t<typename ContainerT::value_type>> >
        [[nodiscard]] bool CanCompareWith( const ContainerT& container ) const
        {
            using TraitsType = TraitsT;
            if ( Dimensions( ) == 1 )
            {
                if ( HaveVariantType( ) )
                {
                    auto variantType = GetVariantType( );
                    if ( TraitsType::VariantType == variantType )
                    {
                        return true;
                    }
                }
            }
            return false;
        }


        template<SimpleSpanLike ContainerT, typename TraitsT = VariantTypeTraits< std::remove_cvref_t<typename ContainerT::value_type>> >
        [[nodiscard]] bool EqualTo( const ContainerT& container ) const
        {
            using TraitsType = TraitsT;
            if ( Dimensions( ) == 1 )
            {
                if ( HaveVariantType( ) )
                {
                    auto variantType = GetVariantType( );
                    if ( TraitsType::VariantType == variantType )
                    {
                        auto length = static_cast< size_t >( Length( ) );
                        auto containerSize = container.size( );
                        if ( length == containerSize )
                        {
                            DataLock dataLock( *this );
                            auto* dataPtr = dataLock.Data<typename TraitsType::VariantValueType>( );
                            if constexpr ( TraitsType::RequiresConversion )
                            {
                                for ( size_t i = 0; i < containerSize; i++ )
                                {
                                    if ( container[ i ] != TraitsType::Convert( dataPtr[ i ] ) )
                                    {
                                        return false;
                                    }
                                }
                                return true;
                            }
                            else
                            {
                                return std::equal( container.begin(), container.end(), dataPtr, dataPtr + containerSize );
                            }
                        }
                    }
                }
            }
            return false;
        }

        template<SimpleSpanLike ContainerT, typename TraitsT = VariantTypeTraits< std::remove_cvref_t<typename ContainerT::value_type>> >
        [[nodiscard]] Int32 CompareTo( const ContainerT& container ) const
        {
            using TraitsType = TraitsT;
            if ( Dimensions( ) == 1 )
            {
                if ( HaveVariantType( ) )
                {
                    auto variantType = GetVariantType( );
                    if ( TraitsType::VariantType == variantType )
                    {
                        auto length = static_cast< size_t >( Length( ) );
                        auto containerSize = container.size( );
                        auto compareSize = std::min( length, containerSize );
                        Int32 result = 0;
                        DataLock dataLock( *this );
                        auto* dataPtr = dataLock.Data<typename TraitsType::VariantValueType>( );
                        if constexpr ( TraitsType::RequiresConversion )
                        {
                            return Core::Compare( container.data( ), container.size( ), dataPtr, containerSize, TraitsType::Convert );
                        }
                        else
                        {
                            return Core::Compare( container.data( ), container.size( ), dataPtr, containerSize );
                        }
                        
                    }
                    else
                    {
                        HCC_THROW( ArgumentException, L"Unexpected variant type, does not match value type of container." );
                    }
                }
                else
                {
                    HCC_THROW( InvalidOperationException, L"Variant type is required." );
                }
            }
            else
            {
                HCC_THROW( InvalidOperationException, L"SAFEARRAY is not a vector." );
            }
        }




    };

    // ----------------------------------------------------------------------
    // AttachedSafeArray
    // ----------------------------------------------------------------------
    class AttachedSafeArray : public SafeArray
    {
    public:
        using Base = SafeArray;

        AttachedSafeArray(SAFEARRAY* safearray)
            : Base( safearray )
        { }

        ~AttachedSafeArray( )
        {
            Release( );
        }

    };


    class BooleanSafeArray : public SafeArray
    {
    public:
    private:
    public:

    };

    template<typename ValueT>
    class SafeArrayT : public SafeArray
    {
    public:
        using Base = SafeArray;
        using value_type = std::remove_cvref_t<ValueT>;

        using Traits = VariantTypeTraits<value_type>;

    private:
        static SAFEARRAY* EnsureRightType( SAFEARRAY* ptr )
        {
            if ( ptr )
            {
                if ( ( ptr->fFeatures & FADF_HAVEVARTYPE ) == 0 )
                {
                    CheckHRESULT( E_INVALIDARG );
                }
                VariantType variantType;
                auto hr = SafeArrayGetVartype( ptr, reinterpret_cast< VARTYPE* >( &variantType ) );
                if ( FAILED( hr ) )
                {
                    CheckHRESULT( hr );
                }
                if ( variantType != Traits::VariantType )
                {
                    CheckHRESULT( E_INVALIDARG );
                }
                if ( ptr->cDims != 1 )
                {
                    CheckHRESULT( E_INVALIDARG );
                }
            }
            return ptr;
        }
    public:
        SafeArrayT(SAFEARRAY* ptr)
            : Base( EnsureRightType( ptr ) )
        { }



    };





    // ----------------------------------------------------------------------
    // VariantT
    // ----------------------------------------------------------------------
    template<typename BaseType>
    class VariantT : public BaseType
    {
    public:
        using Base = BaseType;
        static constexpr LANGID InvariantLanguageId = MAKELANGID( LANG_INVARIANT, SUBLANG_NEUTRAL );
        static constexpr LCID InvariantLocaleId = MAKELCID( InvariantLanguageId, SORT_DEFAULT );
    private:
        void SetVariantType( VariantType variantType ) noexcept
        {
            Base::vt = USHORT( variantType );
        }
    public:
        static int Compare( const BaseType& first, const BaseType& second )
        {
            if ( first.vt == USHORT( VariantType::Empty ) )
            {
                if ( second.vt == USHORT( VariantType::Empty ) )
                {
                    return 0;
                }
                return -1;
            }
            else if ( second.vt == USHORT( VariantType::Empty ) )
            {
                return 1;
            }
            else if ( first.vt == USHORT( VariantType::Null ) )
            {
                if ( second.vt == USHORT( VariantType::Null ) )
                {
                    return 0;
                }
                return -1;
            }
            else if ( second.vt == USHORT( VariantType::Null ) )
            {
                return 1;
            }

            auto lcid = GetUserDefaultLCID( );
            auto result = VarCmp( (VARIANT*)&first, (VARIANT*)&second, lcid );
            if ( FAILED( result ) )
            {
                CheckHRESULT( result );
            }
            return result - 1;
        }

        constexpr VariantType Type( ) const noexcept
        {
            return VariantType( Base::vt );
        }

        constexpr VariantType ElementType( ) const noexcept
        {
            return VariantType( Base::vt & VT_TYPEMASK );
        }

        constexpr bool IsEmpty( ) const noexcept
        {
            return Type( ) == VariantType::Empty;
        }

        constexpr bool IsNull( ) const noexcept
        {
            return Type( ) == VariantType::Null;
        }

        constexpr bool IsReference( ) const noexcept
        {
            return ( Type( ) & VariantType::Byref ) != VariantType::Empty;
        }

        constexpr bool IsArray( ) const noexcept
        {
            return ( Type( ) & VariantType::Array ) != VariantType::Empty;
        }



        constexpr VariantT( ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>(VariantType::Empty);
        }
        constexpr explicit VariantT( Int64 value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Int64 );
            Base::llVal = value;
        }
        constexpr explicit VariantT( UInt64 value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::UInt64 );
            Base::ullVal = value;
        }
        constexpr explicit VariantT( LONG value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Long );
            Base::lVal = value;
        }

        constexpr explicit VariantT( Int32 value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Long );
            Base::lVal = value;
        }

        explicit VariantT( LONG value, VariantType variantType )
            : Base( )
        {
            if ( variantType == VariantType::Long || variantType == VariantType::Error )
            {
                Base::vt = static_cast<USHORT>( variantType );
                Base::lVal = value;
            }
            else
            {
                Base::vt = static_cast<USHORT>( VariantType::Error );
                Base::scode = E_INVALIDARG;
                CheckHRESULT( Base::scode );
            }
        }

        constexpr explicit VariantT( BYTE value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Byte );
            Base::bVal = value;
        }
        constexpr explicit VariantT( SHORT value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Short );
            Base::iVal = value;
        }
        constexpr explicit VariantT( FLOAT Value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Float );
            Base::fltVal = Value;
        }
        constexpr explicit VariantT( DOUBLE value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Double );
            Base::dblVal = value;
        }

        explicit VariantT( DOUBLE value, VariantType variantType )
            : Base( )
        {
            if ( variantType == VariantType::Double || variantType == VariantType::DateTime )
            {
                Base::vt = static_cast<USHORT>( variantType );
                Base::dblVal = value;
            }
            else
            {
                Base::vt = static_cast<USHORT>( VariantType::Error );
                Base::scode = E_INVALIDARG;
                CheckHRESULT( Base::scode );
            }
        }

        constexpr explicit VariantT( bool value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Bool );
            Base::boolVal = value ? VARIANT_TRUE : VARIANT_FALSE;
        }

        constexpr explicit VariantT( const CY& value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Currency );
            Base::cyVal = value;
        }
        constexpr explicit VariantT( const Currency& value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Currency );
            Base::cyVal.int64 = value.Value();
        }

        explicit VariantT( const DateTime& value )
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::DateTime );
            Base::date = value.ToOADate( );
        }


        constexpr explicit VariantT( const TimeSpan& value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::DateTime );
            Base::date = value.TotalDays( );
        }


        explicit VariantT( const SysString& value )
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::BStr );
            Base::bstrVal = value.Copy( );
        }

        explicit VariantT( SysString&& value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::BStr );
            Base::bstrVal = value.Detach();
        }

        explicit VariantT( const WideString& value )
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::BStr );
            Base::bstrVal = nullptr;
            if ( value.length( ) )
            {
                Base::bstrVal = SysAllocStringLen( value.c_str( ), static_cast<UINT>( value.length( ) ) );
                if ( !Base::bstrVal )
                {
                    CheckHRESULT( E_OUTOFMEMORY );
                }
            }
        }

        explicit VariantT( const wchar_t* value )
            : Base( )
        {
            if ( value && value[0] )
            {
                auto length = wcslen( value );
                Base::vt = static_cast<USHORT>( VariantType::BStr );
                Base::bstrVal = SysAllocStringLen( value, static_cast<UINT>( length ) );
                if ( !Base::bstrVal )
                {
                    CheckHRESULT( E_OUTOFMEMORY );
                }
            }
        }



        explicit VariantT( IUnknown* pInterface ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Unknown );
            Base::punkVal = pInterface;
            if ( Base::punkVal )
            {
                Base::punkVal->AddRef( );
            }
        }

        explicit VariantT( IDispatch* pInterface ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Dispatch );
            Base::pdispVal = pInterface;
            if ( Base::pdispVal )
            {
                Base::pdispVal->AddRef( );
            }
        }

        explicit VariantT( SAFEARRAY* safeArray )
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Array );
            if ( safeArray )
            {
                auto vType = SafeArray::GetElementVariantType( safeArray );
                Base::vt |= static_cast<USHORT>( vType );
                auto hr = SafeArrayCopy( safeArray, &Base::parray );
                CheckHRESULT( hr );
            }
            else
            {
                Base::parray = nullptr;
            }
        }

        explicit VariantT( const SafeArray& safeArray )
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Array );
            if ( safeArray.ptr_ )
            {
                auto vType = SafeArray::GetElementVariantType( safeArray.ptr_ );
                Base::vt |= static_cast<USHORT>( vType );
                auto hr = SafeArrayCopy( safeArray.ptr_, &Base::parray );
                CheckHRESULT( hr );
            }
            else
            {
                Base::parray = nullptr;
            }
        }
        explicit VariantT( SafeArray&& safeArray )
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::Array );
            if ( safeArray.ptr_ )
            {
                auto vType = SafeArray::GetElementVariantType( safeArray.ptr_ );
                Base::vt |= static_cast<USHORT>( vType );
                Base::parray = safeArray.ptr_;
                safeArray.ptr_ = nullptr;
            }
            else
            {
                Base::parray = nullptr;
            }
        }



        constexpr explicit VariantT( char value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::SByte );
            Base::cVal = value;
        }
        constexpr explicit VariantT( signed char value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::SByte );
            Base::cVal = value;
        }

        constexpr explicit VariantT( USHORT value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::UShort );
            Base::uiVal = value;
        }

        constexpr explicit VariantT( ULONG value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::ULong );
            Base::ulVal = value;
        }
        constexpr explicit VariantT( UInt32 value ) noexcept
            : Base( )
        {
            Base::vt = static_cast<USHORT>( VariantType::ULong );
            Base::ulVal = value;
        }

        explicit VariantT( IRecordInfo* recordInfo, void* value, bool addRef = false ) noexcept
            : Base( )
        {
            Base::vt = static_cast< USHORT >( VariantType::Record );
            Base::pRecInfo = recordInfo;
            Base::pvRecord = value;
            if ( addRef )
            {
                recordInfo->AddRef( );
            }
        }


        VariantT( const VariantT& other )
        {
            switch ( other.vt )
            {
                case VT_EMPTY:
                case VT_NULL:
                case VT_I1:
                case VT_I2:
                case VT_I4:
                case VT_I8:
                case VT_UI1:
                case VT_UI2:
                case VT_UI4:
                case VT_UI8:
                case VT_R4:
                case VT_R8:
                case VT_CY:
                case VT_DATE:
                    Base::vt = other.vt;
                    Base::ullVal = other.ullVal;
                    break;
                default:
                    VariantInit( this );
                    auto hr = VariantCopy( (VARIANT*)this, &other );
                    CheckHRESULT( hr );
                    break;

            }
        }

        VariantT( VariantT&& other ) noexcept
        {
            Base* self = this;
            Base* otherPtr = &other;
            memcpy( self, otherPtr, sizeof( VARIANT ) );
            other.vt = static_cast<USHORT>( VariantType::Empty );
        }

        void Clear( )
        {
            switch ( Base::vt )
            {
                case VT_EMPTY:
                case VT_NULL:
                case VT_I1:
                case VT_I2:
                case VT_I4:
                case VT_I8:
                case VT_UI1:
                case VT_UI2:
                case VT_UI4:
                case VT_UI8:
                case VT_R4:
                case VT_R8:
                case VT_CY:
                case VT_DATE:
                    Base::vt = VT_EMPTY;
                    break;
                default:
                    auto hr = VariantClear( (VARIANT*)this );
                    CheckHRESULT( hr );
                    break;

            }
        }

        ~VariantT( )
        {
            if ( Base::vt != VT_EMPTY )
            {
                Clear( );
            }
        }

        VariantT& operator = ( const VariantT& other )
        {
            if ( &Base::vt != &other.vt )
            {
                if ( Base::vt != VT_EMPTY )
                {
                    Clear( );
                }
                switch ( other.vt )
                {
                    case VT_EMPTY:
                    case VT_NULL:
                    case VT_I1:
                    case VT_I2:
                    case VT_I4:
                    case VT_I8:
                    case VT_UI1:
                    case VT_UI2:
                    case VT_UI4:
                    case VT_UI8:
                    case VT_R4:
                    case VT_R8:
                    case VT_CY:
                    case VT_DATE:
                        Base::vt = other.vt;
                        Base::ullVal = other.ullVal;
                        break;
                    default:
                        auto hr = VariantCopy( this, &other );
                        CheckHRESULT( hr );
                        break;

                }
            }
            return *this;
        }

        VariantT& operator = ( VariantT&& other ) noexcept
        {
            if ( this != &other )
            {
                if ( Base::vt != VT_EMPTY )
                {
                    Clear();
                }

                Base* self = this;
                Base* otherPtr = &other;

                memcpy( self, otherPtr, sizeof( VARIANT ) );
                other.vt = VT_EMPTY;
            }
            return *this;
        }

        int CompareTo( const BaseType& other ) const
        {
            return Compare( *this, other );
        }

        int CompareTo( const VariantT& other ) const
        {
            return Compare( *this, other );
        }

        bool operator == ( const BaseType& other ) const { return CompareTo( other ) == 0; }
        bool operator != ( const BaseType& other ) const { return CompareTo( other ) != 0; }
        bool operator <= ( const BaseType& other ) const { return CompareTo( other ) <= 0; }
        bool operator <  ( const BaseType& other ) const { return CompareTo( other ) < 0; }
        bool operator >  ( const BaseType& other ) const { return CompareTo( other ) > 0; }
        bool operator >= ( const BaseType& other ) const { return CompareTo( other ) >= 0; }

        bool operator == ( const VariantT& other ) const { return CompareTo( other ) == 0; }
        bool operator != ( const VariantT& other ) const { return CompareTo( other ) != 0; }
        bool operator <= ( const VariantT& other ) const { return CompareTo( other ) <= 0; }
        bool operator <  ( const VariantT& other ) const { return CompareTo( other ) < 0; }
        bool operator >  ( const VariantT& other ) const { return CompareTo( other ) > 0; }
        bool operator >= ( const VariantT& other ) const { return CompareTo( other ) >= 0; }


        HRESULT AssignTo( VARIANT& other ) const
        {
            HRESULT result = S_OK;
            if ( other.vt != VT_EMPTY )
            {
                result = VariantClear( &other );
                if ( FAILED( result ) )
                {
                    return result;
                }
                other.vt = VT_EMPTY;
            }
            if ( IsEmpty( ) == FALSE )
            {
                result = VariantCopy( &other, this );
            }
            return result;
        }

        void Assign( Int64 value )
        {
            Clear( );
            SetVariantType( VariantType::Int64 );
            Base::llVal = value;
        }
        void Assign( UInt64 value )
        {
            Clear( );
            SetVariantType( VariantType::UInt64 );
            Base::ullVal = value;
        }
        void Assign( LONG value )
        {
            Clear( );
            SetVariantType( VariantType::Long );
            Base::lVal = value;
        }

        void Assign( LONG value, VariantType variantType )
        {
            Clear( );
            if ( variantType == VariantType::Long || variantType == VariantType::Error )
            {
                SetVariantType( variantType );
                Base::lVal = value;
            }
            else
            {
                SetVariantType( VariantType::Error );
                Base::scode = E_INVALIDARG;
                CheckHRESULT( Base::scode );
            }
        }

        void Assign( BYTE value )
        {
            Clear( );
            SetVariantType( VariantType::Byte );
            Base::bVal = value;
        }
        void Assign( SHORT value )
        {
            Clear( );
            SetVariantType( VariantType::Short );
            Base::iVal = value;
        }
        void Assign( FLOAT value )
        {
            Clear( );
            SetVariantType( VariantType::Float );
            Base::fltVal = value;
        }
        void Assign( DOUBLE value )
        {
            Clear( );
            SetVariantType( VariantType::Double );
            Base::dblVal = value;
        }

        void Assign( DOUBLE value, VariantType variantType )
        {
            Clear( );
            if ( variantType == VariantType::Double || variantType == VariantType::DateTime )
            {
                SetVariantType( variantType );
                Base::dblVal = value;
            }
            else
            {
                SetVariantType( VariantType::Error );
                Base::scode = E_INVALIDARG;
                CheckHRESULT( Base::scode );
            }
        }

        void Assign( bool value )
        {
            Clear( );
            SetVariantType( VariantType::Bool );
            Base::boolVal = value ? VARIANT_TRUE : VARIANT_FALSE;
        }

        void Assign( const CY& value )
        {
            Clear( );
            SetVariantType( VariantType::Currency );
            Base::cyVal = value;
        }
        void Assign( const Currency& value )
        {
            Clear( );
            SetVariantType( VariantType::Currency );
            Base::cyVal.int64 = value.Value();
        }

        void Assign( const DateTime& value )
        {
            Clear( );
            SetVariantType( VariantType::DateTime );
            Base::date = value.ToOADate( );
        }

        void Assign( const TimeSpan& value )
        {
            Clear( );
            SetVariantType( VariantType::Double );
            Base::date = value.TotalDays( );
        }

        void Assign( const SysString& value )
        {
            Clear( );
            SetVariantType( VariantType::BStr );
            Base::bstrVal = value.Copy( );
        }

        void Assign( const WideString& value )
        {
            Clear( );
            SetVariantType( VariantType::BStr );
            Base::bstrVal = nullptr;
            if ( value.length( ) )
            {
                Base::bstrVal = SysAllocStringLen( value.c_str( ), UINT( value.length( ) ) );
                if ( !Base::bstrVal )
                {
                    CheckHRESULT( E_OUTOFMEMORY );
                }
            }
        }


        void Assign( IUnknown* pInterface )
        {
            Clear( );
            SetVariantType( VariantType::Unknown );
            Base::punkVal = pInterface;
            if ( Base::punkVal )
            {
                Base::punkVal->AddRef( );
            }
        }

        void Assign( IDispatch* pInterface )
        {
            Clear( );
            SetVariantType( VariantType::Dispatch );
            Base::pdispVal = pInterface;
            if ( Base::pdispVal )
            {
                Base::pdispVal->AddRef( );
            }
        }

        void Assign( SAFEARRAY* safeArray )
        {
            Clear( );
            SetVariantType( VariantType::Array );
            if ( safeArray )
            {
                auto vType = SafeArray::GetElementVariantType( safeArray );
                SetVariantType( VariantType::Array | vType );
                auto hr = SafeArrayCopy( safeArray, &Base::parray );
                CheckHRESULT( hr );
            }
            else
            {
                Base::parray = nullptr;
            }
        }

        void Assign( signed char value )
        {
            Clear( );
            SetVariantType( VariantType::SByte );
            Base::cVal = value;
        }

        void Assign( USHORT value )
        {
            Clear( );
            SetVariantType( VariantType::UShort );
            Base::uiVal = value;
        }

        void Assign( wchar_t value )
        {
            Clear( );
            SetVariantType( VariantType::UShort );
            Base::uiVal = static_cast<UInt16>(value);
        }


        void Assign( ULONG value )
        {
            Clear( );
            SetVariantType( VariantType::ULong );
            Base::ulVal = value;
        }

        template <typename T>
        VariantT& operator = ( const T& value )
        {
            Assign( value );
            return *this;
        }

    private:
        template<VariantType variantType>
        void ChangeType( VARIANT& destination ) const
        {
            auto hr = VariantChangeType( &destination, (VARIANT*)this, 0, static_cast<VARTYPE>( variantType ) );
            CheckHRESULT( hr );
        }
    public:
        bool AsBoolean( ) const
        {
            if constexpr ( std::is_same_v<BaseType, PROPVARIANT> )
            {
                switch ( Type( ) )
                {
                    case VariantType::Empty:
                        return false;
                        break;
                    case VariantType::Null:
                        return false;
                        break;
                    case VariantType::Bool:
                        return Base::boolVal != VARIANT_FALSE;
                        break;
                    case VariantType::Int1:
                        return Base::cVal != 0;
                        break;
                    case VariantType::UInt1:
                        return Base::bVal != 0;
                        break;
                    case VariantType::Int2:
                        return Base::iVal != 0;
                        break;
                    case VariantType::UInt2:
                        return Base::uiVal != 0;
                        break;
                    case VariantType::Int4:
                        return Base::lVal != 0;
                        break;
                    case VariantType::UInt4:
                        return Base::ulVal != 0;
                        break;
                    case VariantType::Int8:
                        return Base::hVal.QuadPart != 0;
                        break;
                    case VariantType::UInt8:
                        return Base::uhVal.QuadPart != 0;
                        break;
                    case VariantType::Real4:
                        return Base::fltVal != 0.0f;
                        break;
                    case VariantType::Real8:
                        return Base::dblVal != 0.0;
                        break;
                    default:
                    {
                        VARIANT result = { 0, };
                        ChangeType<VariantType::Bool>( result );
                        return result.boolVal != VARIANT_FALSE;
                    }
                    break;
                }
            }
            else
            {
                switch ( Type( ) )
                {
                    case VariantType::Empty:
                        return false;
                        break;
                    case VariantType::Null:
                        return false;
                        break;
                    case VariantType::Bool:
                        return Base::boolVal != VARIANT_FALSE;
                        break;
                    case VariantType::Int1:
                        return Base::cVal != 0;
                        break;
                    case VariantType::UInt1:
                        return Base::bVal != 0;
                        break;
                    case VariantType::Int2:
                        return Base::iVal != 0;
                        break;
                    case VariantType::UInt2:
                        return Base::uiVal != 0;
                        break;
                    case VariantType::Int4:
                        return Base::lVal != 0;
                        break;
                    case VariantType::UInt4:
                        return Base::ulVal != 0;
                        break;
                    case VariantType::Int8:
                        return Base::llVal != 0;
                        break;
                    case VariantType::UInt8:
                        return Base::ullVal != 0;
                        break;
                    case VariantType::Real4:
                        return Base::fltVal != 0.0f;
                        break;
                    case VariantType::Real8:
                        return Base::dblVal != 0.0;
                        break;
                    default:
                    {
                        VARIANT result = { 0, };
                        ChangeType<VariantType::Bool>( result );
                        return result.boolVal != VARIANT_FALSE;
                    }
                    break;
                }
            }
        }
        template<typename T>
        T As( ) const
        {
            static_assert( AlwaysFalse<T>::value, "Unsupported conversion" );
        }

        template<>
        bool As<bool>( ) const
        {
            return AsBoolean( );
        }

    private:
        template<typename T>
        bool ConvertTo( T& result ) const noexcept
        {
            if constexpr ( std::is_same_v<BaseType, PROPVARIANT> )
            {
                switch ( Type( ) )
                {
                    case VariantType::Bool:
                        result = Base::boolVal != VARIANT_FALSE ? 1 : 0;
                        return true;
                        break;
                    case VariantType::Int1:
                        result = static_cast<T>( Base::cVal );
                        return true;
                        break;
                    case VariantType::UInt1:
                        result = static_cast<T>( Base::bVal );
                        return true;
                        break;
                    case VariantType::Int2:
                        result = static_cast<T>( Base::iVal );
                        return true;
                        break;
                    case VariantType::UInt2:
                        result = static_cast<T>( Base::uiVal );
                        return true;
                        break;
                    case VariantType::Int4:
                        result = static_cast<T>( Base::lVal );
                        return true;
                        break;
                    case VariantType::UInt4:
                        result = static_cast<T>( Base::ulVal );
                        return true;
                        break;
                    case VariantType::Int8:
                        result = static_cast<T>( Base::hVal.QuadPart );
                        return true;
                        break;
                    case VariantType::UInt8:
                        result = static_cast<T>( Base::uhVal.QuadPart );
                        return true;
                        break;
                    case VariantType::Real4:
                        result = static_cast<T>( Base::fltVal );
                        return true;
                        break;
                    case VariantType::Real8:
                        result = static_cast<T>( Base::dblVal );
                        return true;
                        break;
                }
            }
            else
            {
                switch ( Type( ) )
                {
                    case VariantType::Bool:
                        result = static_cast<T>( Base::boolVal != VARIANT_FALSE ? 1 : 0);
                        return true;
                        break;
                    case VariantType::Int1:
                        result = static_cast<T>( Base::cVal );
                        return true;
                        break;
                    case VariantType::UInt1:
                        result = static_cast<T>( Base::bVal );
                        return true;
                        break;
                    case VariantType::Int2:
                        result = static_cast<T>( Base::iVal );
                        return true;
                        break;
                    case VariantType::UInt2:
                        result = static_cast<T>( Base::uiVal );
                        return true;
                        break;
                    case VariantType::Int4:
                        result = static_cast<T>( Base::lVal );
                        return true;
                        break;
                    case VariantType::UInt4:
                        result = static_cast<T>( Base::ulVal );
                        return true;
                        break;
                    case VariantType::Int8:
                        result = static_cast<T>( Base::llVal );
                        return true;
                        break;
                    case VariantType::UInt8:
                        result = static_cast<T>( Base::ullVal );
                        return true;
                        break;
                    case VariantType::Real4:
                        result = static_cast<T>( Base::fltVal );
                        return true;
                        break;
                    case VariantType::Real8:
                        result = static_cast<T>( Base::dblVal );
                        return true;
                        break;
                }
            }
            return false;
        }

        

    public:
        char AsSByte( ) const
        {
            char result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                VARIANT variant = { 0, };
                ChangeType<VariantType::Int1>( variant );
                return variant.cVal;
            }
        }
        template<>
        char As<char>( ) const
        {
            return AsSByte( );
        }
        template<>
        signed char As<signed char>( ) const
        {
            return AsSByte( );
        }

        unsigned char AsByte( ) const
        {
            unsigned char result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                VARIANT variant = { 0, };
                ChangeType<VariantType::UInt1>( variant );
                return variant.bVal;
            }
        }

        template<>
        unsigned char As<unsigned char>( ) const
        {
            return AsByte( );
        }

        Int16 AsInt16( ) const
        {
            Int16 result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                VARIANT variant = { 0, };
                ChangeType<VariantType::Int2>( variant );
                return variant.iVal;
            }
        }

        

        template<>
        Int16 As<Int16>( ) const
        {
            return AsInt16( );
        }

        UInt16 AsUInt16( ) const
        {
            UInt16 result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                VARIANT variant = { 0, };
                ChangeType<VariantType::UInt2>( variant );
                return variant.uiVal;
            }
        }

        template<>
        UInt16 As<UInt16>( ) const
        {
            return AsUInt16( );
        }

        template<>
        wchar_t As<wchar_t>( ) const
        {
            return AsUInt16( );
        }

        Int32 AsInt32( ) const
        {
            Int32 result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                VARIANT variant = { 0, };
                ChangeType<VariantType::Int4>( variant );
                return variant.lVal;
            }
        }

        template<>
        Int32 As<Int32>( ) const
        {
            return AsInt32( );
        }

        UInt32 AsUInt32( ) const
        {
            UInt32 result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                VARIANT variant = { 0, };
                ChangeType<VariantType::UInt4>( variant );
                return variant.ulVal;
            }
        }

        template<>
        UInt32 As<UInt32>( ) const
        {
            return AsUInt32( );
        }

        Int64 AsInt64( ) const
        {
            Int64 result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                VARIANT variant = { 0, };
                ChangeType<VariantType::Int64>( variant );
                return variant.llVal;
            }
        }

        template<>
        Int64 As<Int64>( ) const
        {
            return AsInt64( );
        }

        UInt64 AsUInt64( ) const
        {
            UInt64 result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                VARIANT variant = { 0, };
                ChangeType<VariantType::UInt64>( variant );
                return variant.ullVal;
            }
        }

        template<>
        UInt64 As<UInt64>( ) const
        {
            return AsUInt64( );
        }

        Single AsSingle( ) const
        {
            Single result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                VARIANT variant = { 0, };
                ChangeType<VariantType::Real4>( variant );
                return variant.fltVal;
            }
        }

        template<>
        Single As<Single>( ) const
        {
            return AsSingle( );
        }

        Double AsDouble( ) const
        {
            Double result = 0;
            if ( ConvertTo( result ) )
            {
                return result;
            }
            else
            {
                VARIANT variant = { 0, };
                ChangeType<VariantType::Real8>( variant );
                return variant.dblVal;
            }
        }

        template<>
        Double As<Double>( ) const
        {
            return AsDouble( );
        }


        WideString AsWideString( ) const
        {
            if ( Type( ) == VariantType::BStr )
            {
                if ( Base::bstrVal )
                {
                    return WideString( Base::bstrVal );
                }
                else
                {
                    return {};
                }
            }
            else
            {
                VariantT result;
                auto hr = VariantChangeType( (VARIANT*)&result, (VARIANT*)this, 0, (VARTYPE)VariantType::BStr );
                CheckHRESULT( hr );
                if ( result.bstrVal )
                {
                    return WideString( result.bstrVal );
                }
                else
                {
                    return {};
                }
            }
        }
        template<>
        WideString As<WideString>( ) const
        {
            return AsWideString( );
        }

        std::wstring AsStdWideString( ) const
        {
            if ( Type( ) == VariantType::BStr )
            {
                if ( Base::bstrVal )
                {
                    return std::wstring( Base::bstrVal );
                }
                else
                {
                    return {};
                }
            }
            else
            {
                VariantT result;
                auto hr = VariantChangeType( ( VARIANT* )&result, ( VARIANT* )this, 0, ( VARTYPE )VariantType::BStr );
                CheckHRESULT( hr );
                if ( result.bstrVal )
                {
                    return std::wstring( result.bstrVal );
                }
                else
                {
                    return {};
                }
            }
        }

        template<>
        std::wstring As<std::wstring>( ) const
        {
            return AsStdWideString( );
        }


        AnsiString AsAnsiString( ) const
        {
            return ToAnsiString( AsWideString( ) );
        }

        template<>
        AnsiString As<AnsiString>( ) const
        {
            return AsAnsiString( );
        }

        std::string AsStdString( ) const
        {
            std::string result;
            ToAnsiString( AsWideString( ), result );
            return result;
        }

        template<>
        std::string As<std::string>( ) const
        {
            return AsStdString( );
        }

        SysString AsSysString( ) const
        {
            if ( Type( ) == VariantType::BStr )
            {
                if ( Base::bstrVal )
                {
                    return SysString( Base::bstrVal );
                }
                else
                {
                    return SysString( );
                }
            }
            else
            {
                VariantT result;
                auto hr = VariantChangeType( (VARIANT*)&result, (VARIANT*)this, 0, (VARTYPE)VariantType::BStr );
                CheckHRESULT( hr );
                if ( result.bstrVal )
                {
                    return SysString( result.bstrVal );
                }
                else
                {
                    return SysString( );
                }
            }
        }

        template<>
        SysString As<SysString>( ) const
        {
            return AsSysString( );
        }


        DateTime AsDateTime( LCID localeId = InvariantLocaleId ) const
        {
            if ( Type( ) == VariantType::DateTime )
            {
                return DateTime::FromOADate( Base::date );
            }
            else
            {
                VariantT result;
                auto hr = VariantChangeTypeEx( (VARIANT*)&result, (const VARIANT*)this, localeId, 0, (VARTYPE)VariantType::DateTime );
                CheckHRESULT( hr );
                return DateTime::FromOADate( result.date );
            }
        }
        template<>
        DateTime As<DateTime>( ) const
        {
            return AsDateTime( );
        }


        TimeSpan AsTimeSpan( LCID localeId = InvariantLocaleId ) const
        {
            auto type = Type( );
            if ( type == VariantType::Real8 || type == VariantType::DateTime )
            {
                return TimeSpan::FromDays( Base::dblVal );
            }
            else if ( type == VariantType::Real4 )
            {
                return TimeSpan::FromDays( Base::fltVal );
            }
            else
            {
                VariantT result;
                auto hr = VariantChangeTypeEx( (VARIANT*)&result, (const VARIANT*)this, localeId, 0, (VARTYPE)VariantType::Real8 );
                CheckHRESULT( hr );
                return TimeSpan::FromDays( result.dblVal );
            }
        }
        template<>
        TimeSpan As<TimeSpan>( ) const
        {
            return AsTimeSpan( );
        }

        Guid AsGuid( ) const
        {
            return Guid( AsWideString( ) );
        }
        template<>
        Guid As<Guid>( ) const
        {
            return AsGuid( );
        }

        Currency AsCurrency( ) const
        {
            Currency result;
            if constexpr ( std::is_same_v<BaseType, PROPVARIANT> )
            {
                switch ( Type( ) )
                {
                    case VariantType::Bool:
                        result = Base::boolVal != VARIANT_FALSE ? 1 : 0;
                        break;
                    case VariantType::Int1:
                        result = Base::cVal;
                        break;
                    case VariantType::UInt1:
                        result = Base::bVal;
                        break;
                    case VariantType::Int2:
                        result = Base::iVal;
                        break;
                    case VariantType::UInt2:
                        result = Base::uiVal;
                        break;
                    case VariantType::Int4:
                        result = Base::lVal;
                        break;
                    case VariantType::UInt4:
                        result = Base::ulVal;
                        break;
                    case VariantType::Int8:
                        result = Base::hVal.QuadPart;
                        break;
                    case VariantType::UInt8:
                        result = Base::uhVal.QuadPart;
                        break;
                    case VariantType::Real4:
                        result = Base::fltVal;
                        break;
                    case VariantType::Real8:
                        result = Base::dblVal;
                        break;
                    case VariantType::Currency:
                        result = Base::cyVal;
                        break;
                    default:
                    {
                        VARIANT variant = { 0, };
                        auto hr = VariantChangeType( &variant, (const VARIANT*)this, 0, (VARTYPE)VariantType::Currency );
                        CheckHRESULT( hr );
                        result = variant.cyVal;
                    }
                    break;
                }
            }
            else
            {
                switch ( Type( ) )
                {
                    case VariantType::Bool:
                        result = Base::boolVal != VARIANT_FALSE ? 1 : 0;
                        break;
                    case VariantType::Int1:
                        result = Base::cVal;
                        break;
                    case VariantType::UInt1:
                        result = Base::bVal;
                        break;
                    case VariantType::Int2:
                        result = Base::iVal;
                        break;
                    case VariantType::UInt2:
                        result = Base::uiVal;
                        break;
                    case VariantType::Int4:
                        result = Base::lVal;
                        break;
                    case VariantType::UInt4:
                        result = Base::ulVal;
                        break;
                    case VariantType::Int8:
                        result = Base::llVal;
                        break;
                    case VariantType::UInt8:
                        result = Base::ullVal;
                        break;
                    case VariantType::Real4:
                        result = Base::fltVal;
                        break;
                    case VariantType::Real8:
                        result = Base::dblVal;
                        break;
                    case VariantType::Currency:
                        result = Base::cyVal;
                        break;
                    default:
                    {
                        VARIANT variant = { 0, };
                        auto hr = VariantChangeType( &variant, (const VARIANT*)this, 0, (VARTYPE)VariantType::Currency );
                        CheckHRESULT( hr );
                        result = variant.cyVal;
                    }
                    break;
                }
            }
            return result;
        }

        template<>
        Currency As<Currency>( ) const
        {
            return AsCurrency( );
        }



        VariantT Abs( ) const
        {
            VariantT result;
            auto hr = VarAbs( (LPVARIANT)this, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        VariantT Add( const VariantT& other ) const
        {
            VariantT result;
            auto hr = VarAdd( (LPVARIANT)this, (LPVARIANT)&other, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        friend VariantT operator + ( const VariantT& left, const VariantT& right )
        {
            return left.Add( right );
        }

        VariantT And( const VariantT& other ) const
        {
            VariantT result;
            auto hr = VarAnd( (LPVARIANT)this, (LPVARIANT)&other, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        friend VariantT operator & ( const VariantT& left, const VariantT& right )
        {
            return left.And( right );
        }

        VariantT Concatenate( const VariantT& other ) const
        {
            VariantT result;
            auto hr = VarCat( (LPVARIANT)this, (LPVARIANT)&other, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }


        VariantT Div( const VariantT& other ) const
        {
            VariantT result;
            auto hr = VarDiv( (LPVARIANT)this, (LPVARIANT)&other, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        friend VariantT operator / ( const VariantT& left, const VariantT& right )
        {
            return left.Div( right );
        }


        VariantT IDiv( const VariantT& other ) const
        {
            VariantT result;
            auto hr = VarIdiv( (LPVARIANT)this, (LPVARIANT)&other, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        VariantT Trunc( ) const
        {
            VariantT result;
            auto hr = VarFix( (LPVARIANT)this, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        VariantT Mod( const VariantT& other ) const
        {
            VariantT result;
            auto hr = VarMod( (LPVARIANT)this, (LPVARIANT)&other, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }


        friend VariantT operator % ( const VariantT& left, const VariantT& right )
        {
            return left.Mod( right );
        }

        VariantT Mul( const VariantT& other ) const
        {
            VariantT result;
            auto hr = VarMul( (LPVARIANT)this, (LPVARIANT)&other, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        friend VariantT operator * ( const VariantT& left, const VariantT& right )
        {
            return left.Mul( right );
        }

        VariantT Neg( ) const
        {
            VariantT result;
            auto hr = VarNeg( (LPVARIANT)this, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }
        // Performs the bitwise not negation operation on a variant
        VariantT Not( ) const
        {
            VariantT result;
            auto hr = VarNot( (LPVARIANT)this, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        VariantT operator ~ ( ) const
        {
            return Not( );
        }


        VariantT Or( const VariantT& other ) const
        {
            VariantT result;
            auto hr = VarOr( (LPVARIANT)this, (LPVARIANT)&other, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        friend VariantT operator | ( const VariantT& left, const VariantT& right )
        {
            return left.Or( right );
        }

        VariantT Sub( const VariantT& other ) const
        {
            VariantT result;
            auto hr = VarSub( (LPVARIANT)this, (LPVARIANT)&other, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        friend VariantT operator - ( const VariantT& left, const VariantT& right )
        {
            return left.Sub( right );
        }

        VariantT Pow( const VariantT& other ) const
        {
            VariantT result;
            auto hr = VarPow( (LPVARIANT)this, (LPVARIANT)&other, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        // Performs a bitwise equivalence on two variants.
        VariantT Eqv( const VariantT& other ) const
        {
            VariantT result;
            auto hr = VarEqv( (LPVARIANT)this, (LPVARIANT)&other, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        /// <summary>
        /// Returns the integer portion of the variant.
        /// </summary>
        /// <remarks>
        /// If the variant is negative, then the first negative integer 
        /// greater than or equal to the variant is returned
        /// </remarks>
        /// <returns>the integer portion of the variant</returns>
        VariantT Fix( ) const
        {
            VariantT result;
            auto hr = VarFix( (LPVARIANT)this, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }

        /// <summary>
        /// Performs a bitwise implication on this and the argument variant 
        /// </summary>
        /// <param name="other">the argument variant</param>
        /// <returns>the result</returns>
        VariantT Imp( const VariantT& other ) const
        {
            VariantT result;
            auto hr = VarImp( (LPVARIANT)this, (LPVARIANT)&other, (LPVARIANT)&result );
            if ( FAILED( hr ) )
            {
                CheckHRESULT( hr );
            }
            return result;
        }


    };

    using Variant = VariantT<tagVARIANT>;
    using PropertyVariant = VariantT<PROPVARIANT>;

    static_assert(sizeof(Variant) == sizeof(PropertyVariant));



}


#endif

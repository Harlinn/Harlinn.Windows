#pragma once
#ifndef __HCCPERSISTENT2_H__
#define __HCCPERSISTENT2_H__
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

#include <HCCArray.h>
#include <HCCTuple.h>
#include <HCCVector.h>
#include <HCCString.h>

#pragma pack(push,1)

namespace Harlinn::Common::Core::Persistent
{
    class TypeDescriptorCursor;

    /// <summary>
    /// A sequence is a variable length encoding where data of the same type
    /// is stored in blocks. Each block is of the same size (SequenceBlockSize = 8)
    /// and is trailed by a byte holding the number of used slots in the 
    /// preceding block. The space not used by an element inside a bloc must
    /// be set to 0. A sequence ends with the first block that is not full, thus
    /// an empty sequence contains one block with all the bytes set to 0 and the
    /// trailing size byte set to 0.
    /// </summary>
    constexpr size_t SequenceBlockSize = 8;

    /// <summary>
    /// The minimum number of bytes required to hold a valid
    /// type description
    /// </summary>
    constexpr size_t MinimumValidTypeDescriptorDataSize = 4;

    enum class ModifierFlags : Byte
    {
        None,
        /// <summary>
        /// Indicates that type element is for an array of data. 
        /// </summary>
        /// <remarks>
        /// <p>
        /// If used without the ::Fixed modifier, the data representation
        /// starts with a 7-bit encoded number specifying the number of elements
        /// in the array.
        /// </p>
        /// <p>
        /// If used with the ::Fixed modifier the lenght of the fixed-size
        /// follows immedeately after the TypeElementHeader as a 7-bit 
        /// encoded number.
        /// </p>
        /// </remarks>
        Array = 0x01,
        /// <summary>
        /// Indicates a fixed number of elements
        /// </summary>
        Fixed = 0x02,
        /// <summary>
        /// Constant data trails the declaring type description element.
        /// </summary>
        /// <remarks>
        /// If used together with the ::Array modifier, then the
        /// ::Fixed modifier must also be specified.
        /// </remarks>
        Constant = 0x04,
        /// <summary>
        /// Indicates that the data is stored in big-endian
        /// format.
        /// </summary>
        BigEndian = 0x08,
        /// <summary>
        /// Indicates that the data is encoded in a way that allows ordering between
        /// elements to be established using memcmp.
        /// </summary>
        /// <remarks>
        /// The ::Sequence modifier requires that the ::BigEndian modifier
        /// is also specified. 
        /// </remarks>
        Sequence = 0x10
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( ModifierFlags, Byte );


    template<typename T>
    class Constant;

    namespace Internal
    {
        template<typename T>
        constexpr bool IsConstantImpl = false;

        template<typename T>
        constexpr bool IsConstantImpl<Constant<T>> = true;
    }
    template<typename T>
    constexpr bool IsConstant = Persistent::Internal::IsConstantImpl<std::remove_cvref_t<T>>;






    


    namespace Internal
    {
        template<typename T>
        struct FormatTraits;

        template<typename T, typename RT>
        struct FormatTraitsBase
        {
            using Type = T;
            using RawType = RT;
            using TypeTraits = Types::TypeTraits<T>;

            static constexpr bool IsSupported = true;
            static constexpr bool IsFixedSize = TypeTraits::IsFixedSize;

            static constexpr size_t BufferSize( const T& object ) noexcept
            {
                return sizeof( TypeTraits::Type );
            }

            template<typename Writer>
            static constexpr void Write( Writer& writer, const T& object )
            {
                writer.Write( object );
            }
            template<typename Reader>
            static constexpr void Read( Reader& reader, T& object )
            {
                reader.Read( object );
            }

        };

        template<typename WriterT, typename T>
        concept WriterCanWrite = requires ( WriterT& writer, const T& t )
        {
            { writer.Write(t) };
        };

        template<typename ReaderT, typename T>
        concept ReaderCanRead = requires ( ReaderT & reader, const T & t )
        {
            { reader.Read( t ) };
        };



        template<typename T, typename RT>
        struct UnsupportedFormatTraits : FormatTraitsBase<T, RT>
        {
            using Base = FormatTraitsBase<T,RT>;
            static constexpr bool IsSupported = false;
        };

        template<typename T, typename RT>
        struct BasicFormatTraits : FormatTraitsBase<T,RT>
        {
            using Base = FormatTraitsBase<T,RT>;
            using Base::TypeTraits;

            static constexpr Types::BasicTypeId TypeId = TypeTraits::TypeId;

            using FormatType = Tuple<Types::BasicTypeId, ModifierFlags>;
            static constexpr FormatType Format{ TypeId, ModifierFlags::None };

            using DescriptorType = Tuple<Byte, Byte, Types::BasicTypeId, ModifierFlags>;
            static constexpr DescriptorType Descriptor{ static_cast<Byte>('\x2'),static_cast<Byte>('\x1') ,TypeId, ModifierFlags::None};
        };

        template<UInt64 uint64Value>
        struct SevenBitEncodedValue
        {
            static constexpr size_t SizeOfEncodedValue = Core::SizeOf7BitEncodedValue( uint64Value );
            using ValueType = ByteArray<SizeOfEncodedValue>;
            using type = ValueType;
        private:
            static constexpr ValueType Encode( ) noexcept
            {
                ValueType result;
                result.Write7BitEncoded_( 0, uint64Value );

                return result;
            }
        public:
            static constexpr ValueType value = Encode( );
        };


        template<typename T, typename RT>
        struct BasicArrayFormatTraits : FormatTraitsBase<T, RT>
        {
            using Base = FormatTraitsBase<T,RT>;

            using Base::TypeTraits;
            static constexpr UInt64 Count = TypeTraits::Count;

            using ElementType = typename TypeTraits::ElementType;
            using ElementTypeTraits = Types::TypeTraits<ElementType>;
            static constexpr Types::BasicTypeId TypeId = ElementTypeTraits::TypeId;

            static constexpr auto Format = MakeTuple( TypeId, ModifierFlags::Array | ModifierFlags::Fixed, SevenBitEncodedValue<Count>::value );
            using FormatType = decltype( Format );

            static constexpr auto Descriptor = TupleCat(MakeTuple( SevenBitEncodedValue<sizeof( FormatType )>::value, static_cast<Byte>( '\x1' ) ), Format );
            using DescriptorType = decltype( Descriptor );

            static constexpr size_t BufferSize( const T& object ) noexcept
            {
                return TypeTraits::SizeOf( object );
            }

            template<typename Writer>
            static constexpr void Write( Writer& writer, const T& object )
            {
                if constexpr ( WriterCanWrite<Writer,T> )
                {
                    writer.Write( object );
                }
                else
                {
                    for ( UInt64 i = 0; i < Count; ++i )
                    {
                        writer.Write( object[i] );
                    }
                }
            }
            template<typename Reader>
            static constexpr void Read( Reader& reader, T& object )
            {
                if constexpr ( ReaderCanRead<Reader, T> )
                {
                    reader.Read( object );
                }
                else
                {
                    for ( UInt64 i = 0; i < Count; ++i )
                    {
                        reader.Read( object[i] );
                    }
                }
            }


        };

        template<typename T, typename RT>
        struct ArrayFormatTraits : BasicArrayFormatTraits<T, RT>
        {
            

        };


        template<typename T, typename RT>
        struct PointerFormatTraitsBase : FormatTraitsBase<T, RT>
        {
            using Base = FormatTraitsBase<T, RT>;
        };

        template<typename T, typename RT>
        struct StringPointerFormatTraits : PointerFormatTraitsBase<T, RT>
        {
            using Base = PointerFormatTraitsBase<T, RT>;
            using ElementType = std::remove_cvref_t< std::remove_pointer_t<T> >;
        private:
            static constexpr auto EvalTypeId( )
            {
                if constexpr ( std::is_same_v<char, ElementType> )
                {
                    return Types::BasicTypeId::Char;
                }
                else
                {
                    return Types::BasicTypeId::WChar;
                }
            }
            static constexpr auto TypeId = EvalTypeId( );

            static constexpr auto EvalFormat( )
            {
                return MakeTuple( TypeId, ModifierFlags::Array );
            }
        public:
            static constexpr auto Format = EvalFormat( );
            using FormatType = decltype( Format );

            static constexpr auto Descriptor = TupleCat( MakeTuple( SevenBitEncodedValue<sizeof( FormatType )>::value, static_cast<Byte>( '\x1' ) ), Format );
            using DescriptorType = decltype( Descriptor );


            static constexpr size_t BufferSize( const ElementType* str ) noexcept
            {
                size_t dataSize = LengthOf(str);
                size_t result = Core::SizeOf7BitEncodedValue( dataSize ) + ( dataSize * sizeof( ElementType ) );
                return result;
            }

            template<typename Writer>
            static void Write( Writer& writer, const ElementType* str )
            {
                if constexpr ( WriterCanWrite<Writer, ElementType*> )
                {
                    writer.Write( str );
                }
                else
                {
                    size_t count = LengthOf( str );
                    writer.Write7BitEncoded( count );
                    writer.Write( reinterpret_cast<const Byte*>( str ), count * sizeof( ElementType ) );
                }
            }
            template<typename Reader>
            static void Read( Reader& reader, ElementType* str )
            {
                if constexpr ( ReaderCanRead<Reader, ElementType*> )
                {
                    reader.Read( str );
                }
                else
                {
                    size_t count = reader.Read7BitEncoded( );
                    if ( count )
                    {
                        reader.Read( reinterpret_cast<Byte*>( str ), count * sizeof( ElementType ) );
                    }
                    str[count] = static_cast<ElementType>( 0 );
                }
            }

            template<typename Reader, typename VectorT>
                requires (IsVectorContainer<VectorT> && std::is_same_v<ElementType, VectorT::value_type> )
            static constexpr void Read( Reader& reader, VectorT& object )
            {
                if constexpr ( ReaderCanRead<Reader, ElementType*> )
                {
                    reader.Read( object );
                }
                else
                {
                    size_t count = reader.Read7BitEncoded( );
                    object.reserve( count );

                    using ElementTypeFormatTraits = FormatTraits<ElementType>;
                    for ( UInt64 i = 0; i < count; ++i )
                    {
                        ElementTypeFormatTraits::Read( reader, object.emplace_back( ) );
                    }
                }
            }


        };

        template<typename T, typename RT>
        struct UnknownPointerFormatTraits : PointerFormatTraitsBase<T, RT>
        {
            using Base = PointerFormatTraitsBase<T, RT>;
        };



        template<typename T, typename RT>
        struct PointerFormatTraits 
            : std::conditional_t
              <
                IsString<T>, StringPointerFormatTraits<T,RT>,
                UnknownPointerFormatTraits<T, RT>
              >
        {
            
        };

        template<typename T, typename RT>
        struct ContainerFormatTraitsBase : FormatTraitsBase<T, RT>
        {
            using Base = FormatTraitsBase<T, RT>;
            using Base::TypeTraits;
        };

        template<typename T, typename RT>
        struct ArrayContainerFormatTraits : ContainerFormatTraitsBase<T, RT>
        {
            using Base = ContainerFormatTraitsBase<T, RT>;
            using Base::TypeTraits;
            
        private:
            using ElementType = typename TypeTraits::ElementType;
            using ElementTypeTraits = Types::TypeTraits<ElementType>;

            static constexpr size_t Count = TypeTraits::Count;

            static constexpr auto EvalTypeId( )
            {
                if constexpr ( ElementTypeTraits::IsBasic )
                {
                    return ElementTypeTraits::TypeId;
                }
                else
                {
                    return TypeTraits::TypeId;
                }
            }
            static constexpr auto TypeId = EvalTypeId( );

            static constexpr auto EvalFormat( )
            {
                if constexpr ( ElementTypeTraits::IsBasic )
                {
                    return MakeTuple( TypeId, ModifierFlags::Array | ModifierFlags::Fixed, SevenBitEncodedValue<Count>::value );
                }
                else
                {
                    auto elementDescriptor = FormatTraits<ElementType>::Descriptor;
                    return MakeTuple( TypeId, ModifierFlags::Array | ModifierFlags::Fixed, elementDescriptor, SevenBitEncodedValue<Count>::value );
                }
            }
        public:
            static constexpr auto Format = EvalFormat( );
            using FormatType = decltype( Format );

            static constexpr auto Descriptor = TupleCat( MakeTuple( SevenBitEncodedValue<sizeof( FormatType )>::value, static_cast<Byte>( '\x1' ) ), Format );
            using DescriptorType = decltype( Descriptor );


            static constexpr size_t BufferSize( const T& object ) noexcept
            {
                if constexpr ( Types::IsFixedSize<ElementType>::value )
                {
                    return Count * Types::PackedSizeOf<T>::value;
                }
                else
                {
                    using ElementTypeFormatTraits = FormatTraits<ElementType>;

                    size_t result = 0;
                    for ( size_t i = 0; i < Count; ++i )
                    {
                        const auto& item = object[i];
                        result += ElementTypeFormatTraits::BufferSize( item );
                    }
                    return result;
                }
            }

            template<typename Writer>
            static constexpr void Write( Writer& writer, const T& object )
            {
                if constexpr ( WriterCanWrite<Writer, T> )
                {
                    writer.Write( object );
                }
                else
                {
                    using ElementTypeFormatTraits = FormatTraits<ElementType>;
                    for ( UInt64 i = 0; i < Count; ++i )
                    {
                        ElementTypeFormatTraits::Write( writer, object[i] );
                    }
                }
            }
            template<typename Reader>
            static constexpr void Read( Reader& reader, T& object )
            {
                if constexpr ( ReaderCanRead<Reader, T> )
                {
                    reader.Read( object );
                }
                else
                {
                    using ElementTypeFormatTraits = FormatTraits<ElementType>;
                    for ( UInt64 i = 0; i < Count; ++i )
                    {
                        ElementTypeFormatTraits::Read( reader, object[i] );
                    }
                }
            }
        };

        template<typename T, typename RT>
        struct VectorContainerFormatTraits : ContainerFormatTraitsBase<T, RT>
        {
            using Base = ContainerFormatTraitsBase<T, RT>;
            using Base::TypeTraits;

        private:
            using ElementType = typename TypeTraits::ElementType;
            using ElementTypeTraits = Types::TypeTraits<ElementType>;

            static constexpr size_t Count = TypeTraits::Count;

            static constexpr auto EvalTypeId( )
            {
                if constexpr ( ElementTypeTraits::IsBasic )
                {
                    return ElementTypeTraits::TypeId;
                }
                else
                {
                    return TypeTraits::TypeId;
                }
            }
            static constexpr auto TypeId = EvalTypeId( );

            static constexpr auto EvalFormat( )
            {
                if constexpr ( ElementTypeTraits::IsBasic )
                {
                    return MakeTuple( TypeId, ModifierFlags::Array );
                }
                else
                {
                    auto elementDescriptor = FormatTraits<ElementType>::Descriptor;
                    return MakeTuple( TypeId, ModifierFlags::Array, elementDescriptor );
                }
            }
        public:
            static constexpr auto Format = EvalFormat( );
            using FormatType = decltype( Format );

            static constexpr auto Descriptor = TupleCat( MakeTuple( SevenBitEncodedValue<sizeof( FormatType )>::value, static_cast<Byte>( '\x1' ) ), Format );
            using DescriptorType = decltype( Descriptor );


            static constexpr size_t BufferSize( const T& object ) noexcept
            {
                if constexpr ( Types::IsFixedSize<ElementType>::value )
                {
                    size_t dataSize = object.size() * Types::PackedSizeOf<ElementType>::value;
                    size_t result = Core::SizeOf7BitEncodedValue( dataSize ) + dataSize;
                    return result;
                }
                else
                {
                    using ElementTypeFormatTraits = FormatTraits<ElementType>;

                    size_t count = object.size( );
                    size_t dataSize = 0;
                    for ( size_t i = 0; i < count; ++i )
                    {
                        const auto& item = object[i];
                        dataSize += ElementTypeFormatTraits::BufferSize( item );
                    }

                    size_t result = Core::SizeOf7BitEncodedValue( dataSize ) + dataSize;
                    return result;
                }
            }

            template<typename Writer>
            static constexpr void Write( Writer& writer, const T& object )
            {
                if constexpr ( WriterCanWrite<Writer, T> )
                {
                    writer.Write( object );
                }
                else
                {
                    using ElementTypeFormatTraits = FormatTraits<ElementType>;
                    size_t count = object.size( );
                    writer.Write7BitEncoded( count );
                    for ( UInt64 i = 0; i < count; ++i )
                    {
                        ElementTypeFormatTraits::Write( writer, object[i] );
                    }
                }
            }
            template<typename Reader>
            static constexpr void Read( Reader& reader, T& object )
            {
                if constexpr ( ReaderCanRead<Reader, T> )
                {
                    reader.Read( object );
                }
                else
                {
                    size_t count = reader.Read7BitEncoded( );
                    object.reserve( count );

                    using ElementTypeFormatTraits = FormatTraits<ElementType>;
                    for ( UInt64 i = 0; i < count; ++i )
                    {
                        ElementTypeFormatTraits::Read( reader, object.emplace_back( ) );
                    }
                }
            }
        };

        template<typename T, typename RT>
        struct StringContainerFormatTraits : ContainerFormatTraitsBase<T, RT>
        {
            using Base = ContainerFormatTraitsBase<T, RT>;
            using Base::TypeTraits;
            using ElementType = typename TypeTraits::ElementType;

            using ElementTypeTraits = Types::TypeTraits<ElementType>;
            static constexpr Types::BasicTypeId TypeId = ElementTypeTraits::TypeId;

            static constexpr auto Format = MakeTuple( TypeId, ModifierFlags::Array );
            using FormatType = decltype( Format );

            static constexpr auto Descriptor = TupleCat( MakeTuple( SevenBitEncodedValue<sizeof( FormatType )>::value, static_cast<Byte>( '\x1' ) ), Format );
            using DescriptorType = decltype( Descriptor );

            static constexpr size_t BufferSize( const T& object ) noexcept
            {
                size_t dataSize = object.size( );
                size_t result = Core::SizeOf7BitEncodedValue( dataSize ) + dataSize;
                return result;
            }

            template<typename Writer>
            static constexpr void Write( Writer& writer, const T& object )
            {
                using ElementTypeFormatTraits = FormatTraits<ElementType>;

                size_t count = object.size( );
                writer.Write7BitEncoded( count );
                writer.Write( object.data(), count * sizeof( TypeTraits::ElementType ) );
            }
            template<typename Reader>
            static constexpr void Read( Reader& reader, T& object )
            {
                size_t count = reader.Read7BitEncoded( );
                object.resize( count );
                reader.Read( object.data(), count * sizeof( TypeTraits::ElementType ) );
            }
        };





        template<typename T, typename RT>
        struct ContainerFormatTraits 
            : std::conditional_t
              <
                IsArrayContainer<T>, ArrayContainerFormatTraits<std::remove_cvref_t<T>, T>, 
                std::conditional_t
                <
                  IsVectorContainer<T>, VectorContainerFormatTraits<std::remove_cvref_t<T>, T>,
                    std::conditional_t
                    <
                      IsBasicString<T>, StringContainerFormatTraits<std::remove_cvref_t<T>, T>,
                      ContainerFormatTraitsBase<std::remove_cvref_t<T>, T>
                    >
                >
              >
        {
            
        };



        template<size_t N, typename T, typename ...Types>
        struct FormatTypeImplHelper
        {
            using TypeFormatTraits = FormatTraits<T>;
            static constexpr auto Format = TupleCat( TypeFormatTraits::Format, FormatTypeImplHelper<N-1, Types...>::Format );
            using FormatType = decltype( Format );
        };
        template<typename T, typename ...Types>
        struct FormatTypeImplHelper<1, T, Types...>
        {
            using TypeFormatTraits = FormatTraits<T>;
            using FormatType = TypeFormatTraits::FormatType;
            static constexpr FormatType Format = TypeFormatTraits::Format;
        };

        template<typename T, typename ...Types>
        struct FormatTypeImplHelper<0, T, Types...>
        {
            using FormatType = Tuple<>;
            static constexpr FormatType Format{};
        };

        template<typename T>
        struct FormatTypeImpl
        {
            static constexpr auto Format = FormatTraits<T>::Format;

        };
        template<typename ...Types>
        struct FormatTypeImpl<Tuple<Types...>>
        {
            static constexpr auto Format = FormatTypeImplHelper<sizeof...( Types ), Types...>::Format;
        };

        template<typename ...Types>
        struct FormatTypeImpl<std::tuple<Types...>>
        {
            static constexpr auto Format = FormatTypeImplHelper<sizeof...( Types ), Types...>::Format;
        };

        template<typename ...Types>
        struct FormatTypeImpl<std::pair<Types...>>
        {
            static constexpr auto Format = FormatTypeImplHelper<sizeof...( Types ), Types...>::Format;
        };


        template<typename ...Types>
        struct FormatTypeImpl<TypeList<Types...>>
        {
            static constexpr auto Format = FormatTypeImplHelper<sizeof...( Types ), Types...>::Format;
        };


        template<typename T, typename RT>
        struct TupleFormatTraits : FormatTraitsBase<T, RT>
        {
            using Base = FormatTraitsBase<T, RT>;
        private:
            using Base::TypeTraits;
            static constexpr Types::TupleTypeId TypeId = TypeTraits::TypeId;

            using ImplType = FormatTypeImpl<std::remove_cvref_t<T>>;

            static constexpr auto HeaderByteSizeAndCount = MakeTuple( TypeId, 
                                                                        ModifierFlags::None, 
                                                                        SevenBitEncodedValue<sizeof( ImplType::Format )>::value, 
                                                                        SevenBitEncodedValue<TypeTraits::Count>::value );
        public:
            static constexpr auto Format = TupleCat( HeaderByteSizeAndCount, ImplType::Format );
            using FormatType = decltype( Format );
        private:
            static constexpr auto Sizes = MakeTuple( SevenBitEncodedValue<sizeof( FormatType )>::value, static_cast<Byte>( '\x1' ) );
        public:
            static constexpr auto Descriptor = TupleCat( Sizes, Format );
            using DescriptorType = decltype( Descriptor );


            static constexpr size_t BufferSize( const T& object ) noexcept
            {
                if constexpr ( TypeTraits::Count > 0 )
                {
                    if constexpr ( Types::IsFixedSize<T>::value )
                    {
                        return Types::PackedSizeOf<T>::value;
                    }
                    else
                    {
                        if constexpr ( IsStdTuple<T> || IsStdPair<T> )
                        {
                            size_t result = std::apply( []( auto&... v )
                            {
                                return ( FormatTraits<decltype( v )>::BufferSize( v ) + ... );
                            }, object );
                            return result;
                        }
                        else if constexpr ( IsCoreTuple<T> )
                        {
                            size_t result = Apply( []( auto&... v )
                            {
                                return ( FormatTraits<decltype( v )>::BufferSize( v ) + ... );
                            }, object );
                            return result;
                        }
                        else
                        {
                            static constexpr bool isKnownTupleType = IsStdTuple<T> || IsStdPair<T> || IsCoreTuple<T>;
                            static_assert( isKnownTupleType, "Unknown tuple type" );
                        }
                    }
                }
                else
                {
                    return 0;
                }
            }

            template<typename Writer>
            static constexpr void Write( Writer& writer, const T& object )
            {
                if constexpr ( IsStdTuple<T> || IsStdPair<T> )
                {
                    std::apply( [&writer]( auto&... v )
                    {
                        ( FormatTraits<decltype( v )>::Write( writer, v ), ... );
                    }, object );
                }
                else if constexpr ( IsCoreTuple<T> )
                {
                    Apply( [&writer]( auto&... v )
                    {
                        ( FormatTraits<decltype( v )>::Write( writer, v ),  ... );
                    }, object );
                }
                else
                {
                    static constexpr bool isKnownTupleType = IsStdTuple<T> || IsStdPair<T> || IsCoreTuple<T>;
                    static_assert( isKnownTupleType, "Unknown tuple type" );
                }
            }
            template<typename Reader>
            static constexpr void Read( Reader& reader, T& object )
            {
                if constexpr ( IsStdTuple<T> || IsStdPair<T> )
                {
                    std::apply( [&reader]( auto&... v )
                    {
                        ( FormatTraits<decltype( v )>::Read( reader, v ), ... );
                    }, object );
                }
                else if constexpr ( IsCoreTuple<T> )
                {
                    Apply( [&reader]( auto&... v )
                    {
                        ( FormatTraits<decltype( v )>::Read( reader, v ), ... );
                    }, object );
                }
                else
                {
                    static constexpr bool isKnownTupleType = IsStdTuple<T> || IsStdPair<T> || IsCoreTuple<T>;
                    static_assert( isKnownTupleType, "Unknown tuple type" );
                }
            }
        };

        // Specialization for an empty Tuple<>
        template<typename RT>
        struct TupleFormatTraits<Tuple<>, RT> : FormatTraitsBase<Tuple<>, RT>
        {
            using Base = FormatTraitsBase<Tuple<>, RT>;
            using Type = typename Base::Type;
        private:
            static constexpr Types::TupleTypeId TypeId = Types::TupleTypeId::Tuple;

            static constexpr auto HeaderByteSizeAndCount = MakeTuple( TypeId, ModifierFlags::None, static_cast<Byte>( '\x0' ), static_cast<Byte>( '\x0' ) );
        public:
            static constexpr auto Format = HeaderByteSizeAndCount;
            using FormatType = decltype( Format );
        private:
            static constexpr auto Sizes = MakeTuple( SevenBitEncodedValue<sizeof( FormatType )>::value, static_cast<Byte>( '\x1' ) );
        public:
            static constexpr auto Descriptor = TupleCat( Sizes, Format );
            using DescriptorType = decltype( Descriptor );

            static constexpr size_t BufferSize( const Type& object ) noexcept
            {
                return 0;
            }

            template<typename Writer>
            static constexpr void Write( Writer& writer, const Type& object )
            {
                // since the tuple is empty, there is nothing to write
            }

            template<typename Reader>
            static constexpr void Read( Reader& reader, Type& object )
            {
                // since the tuple is empty, there is nothing to read
            }
        };

        // Specialization for an empty std::tuple<>
        template<typename RT>
        struct TupleFormatTraits<std::tuple<>, RT> : FormatTraitsBase<std::tuple<>, RT>
        {
            using Base = FormatTraitsBase<std::tuple<>, RT>;
            using Type = typename Base::Type;
        private:
            static constexpr Types::TupleTypeId TypeId = Types::TupleTypeId::StdTuple;

            static constexpr auto HeaderByteSizeAndCount = MakeTuple( TypeId, ModifierFlags::None, static_cast<Byte>( '\x0' ), static_cast<Byte>( '\x0' ) );
        public:
            static constexpr auto Format = HeaderByteSizeAndCount;
            using FormatType = decltype( Format );
        private:
            static constexpr auto Sizes = MakeTuple( SevenBitEncodedValue<sizeof( FormatType )>::value, static_cast<Byte>( '\x1' ) );
        public:
            static constexpr auto Descriptor = TupleCat( Sizes, Format );
            using DescriptorType = decltype( Descriptor );

            static constexpr size_t BufferSize( const Type& object ) noexcept
            {
                return 0;
            }

            template<typename Writer>
            static constexpr void Write( Writer& writer, const Type& object )
            {
                // since the tuple is empty, there is nothing to write
            }

            template<typename Reader>
            static constexpr void Read( Reader& reader, Type& object )
            {
                // since the tuple is empty, there is nothing to read
            }
        };



        template<typename T, typename RT>
        struct OptionalFormatTraits : FormatTraitsBase<T, RT>
        {
            using Base = FormatTraitsBase<T, RT>;
        };

        template<typename T, typename RT>
        struct UniquePtrFormatTraits : FormatTraitsBase<T, RT>
        {
            using Base = FormatTraitsBase<T, RT>;
        };

        template<typename T, typename RT>
        struct SharedPtrFormatTraits : FormatTraitsBase<T, RT>
        {
            using Base = FormatTraitsBase<T, RT>;
        };

        template<typename T, typename RT>
        struct VariantFormatTraits : FormatTraitsBase<T, RT>
        {
            using Base = FormatTraitsBase<T, RT>;
        };

        template<typename T, typename RT>
        struct TypeListFormatTraits : FormatTraitsBase<T, RT>
        {
            using Base = FormatTraitsBase<T, RT>;

        private:
            using Base::TypeTraits;
            static constexpr auto TypeId = TypeTraits::TypeId;

            using ImplType = FormatTypeImpl<std::remove_cvref_t<T>>;

            static constexpr auto HeaderByteSizeAndCount = MakeTuple( TypeId,
                                                                ModifierFlags::None,
                                                                SevenBitEncodedValue<sizeof( ImplType::Format )>::value,
                                                                SevenBitEncodedValue<TypeTraits::Count>::value );
        public:
            static constexpr auto Format = TupleCat( HeaderByteSizeAndCount, ImplType::Format );
            using FormatType = decltype( Format );
        private:
            static constexpr auto Sizes = MakeTuple( SevenBitEncodedValue<sizeof( FormatType )>::value, static_cast<Byte>( '\x1' ) );
        public:
            static constexpr auto Descriptor = TupleCat( Sizes, Format );
            using DescriptorType = decltype( Descriptor );

        };

        template<typename T, typename RT>
        struct AdaptedFormatTraits : FormatTraitsBase<T, RT>
        {
            using Base = FormatTraitsBase<T, RT>;
            using Base::Type;
        private:
            using Base::TypeTraits;
            using TupleType = typename TypeTraits::TupleType;
            static constexpr auto TypeId = TypeTraits::TypeId;

            using ImplType = FormatTypeImpl<typename T::TypeList>;

            static constexpr auto HeaderByteSizeAndCount = MakeTuple( TypeId,
                                                                ModifierFlags::None,
                                                                SevenBitEncodedValue<sizeof( ImplType::Format )>::value,
                                                                SevenBitEncodedValue<TypeTraits::Count>::value );
        public:
            static constexpr auto Format = TupleCat( HeaderByteSizeAndCount, ImplType::Format );
            using FormatType = decltype( Format );
        private:
            static constexpr auto Sizes = MakeTuple( SevenBitEncodedValue<sizeof( FormatType )>::value, static_cast<Byte>( '\x1' ) );
        public:
            static constexpr auto Descriptor = TupleCat( Sizes, Format );
            using DescriptorType = decltype( Descriptor );
            
            static constexpr size_t BufferSize( const Type& object ) noexcept
            {
                if constexpr ( TypeTraits::Count > 0 )
                {
                    if constexpr ( Types::IsFixedSize<T>::value )
                    {
                        return Types::PackedSizeOf<T>::value;
                    }
                    else
                    {
                        size_t result = Apply( []( auto&... v )
                        {
                            return ( FormatTraits<decltype( v )>::BufferSize( v ) + ... );
                        }, reinterpret_cast<const TupleType&>(object) );
                        return result;
                    }
                }
                else
                {
                    return 0;
                }
            }

            template<typename Writer>
            static constexpr void Write( Writer& writer, const Type& object )
            {
                Apply( [&writer]( auto&... v )
                {
                    ( FormatTraits<decltype( v )>::Write( writer, v ), ... );
                }, reinterpret_cast<const TupleType&>( object ) );
            }
            template<typename Reader>
            static constexpr void Read( Reader& reader, T& object )
            {
                Apply( [&reader]( auto&... v )
                {
                    ( FormatTraits<decltype( v )>::Read( reader, v ), ... );
                }, reinterpret_cast<const TupleType&>( object ) );
            }
            

        };

    

        template<typename T, typename RT>
        struct ConstantFormatTraits : FormatTraitsBase<T, RT>
        {
            using Base = FormatTraitsBase<T, RT>;
        };



        template<typename T>
        struct FormatTraits :
            std::conditional_t
            <
              IsBasicType<T>, Persistent::Internal::BasicFormatTraits<std::remove_cvref_t<T>,T>,
              std::conditional_t
              <
                IsArray<T>, Persistent::Internal::ArrayFormatTraits<std::remove_cvref_t<T>, T>,
                std::conditional_t
                <  
                  IsPointer<T>, Persistent::Internal::PointerFormatTraits<std::remove_cvref_t<T>, T>,
                  std::conditional_t
                  <
                    IsContainer<T>, Persistent::Internal::ContainerFormatTraits<std::remove_cvref_t<T>, T>,
                    std::conditional_t
                    < 
                      IsTupleType<T>, Persistent::Internal::TupleFormatTraits<std::remove_cvref_t<T>, T>,
                      std::conditional_t
                      < 
                        IsStdOptional<T>, Persistent::Internal::OptionalFormatTraits<std::remove_cvref_t<T>, T>,
                        std::conditional_t
                        <
                          IsStdUniquePtr<T>, Persistent::Internal::UniquePtrFormatTraits<std::remove_cvref_t<T>, T>,
                          std::conditional_t
                          <
                            IsStdSharedPtr<T>, Persistent::Internal::SharedPtrFormatTraits<std::remove_cvref_t<T>, T>,
                            std::conditional_t
                            <
                              IsStdVariant<T>, Persistent::Internal::VariantFormatTraits<std::remove_cvref_t<T>, T>,
                              std::conditional_t
                              <
                                IsTypeList<T>, Persistent::Internal::TypeListFormatTraits<std::remove_cvref_t<T>, T>,
                                std::conditional_t
                                <
                                  IsConstant<T>, Persistent::Internal::ConstantFormatTraits<std::remove_cvref_t<T>, T>,
                                  std::conditional_t
                                  <
                                    Types::IsAdapted<T>, Persistent::Internal::AdaptedFormatTraits<std::remove_cvref_t<T>, T>,
                                    Persistent::Internal::UnsupportedFormatTraits<std::remove_cvref_t<T>, T> 
                                  >
                                >
                              >
                            >
                          >
                        >
                      >
                    >
                  >
                >
              > 
            >
        { };

    }

    template<typename T>
    class Constant
    {
        using RawType = T;
        using Type = std::remove_cvref_t<T>;

    };


    
    /// <summary>
    /// Computes a binary description of the arguments
    /// that can be used to decode the serialized data
    /// on the receiving end.
    /// </summary>
    template<typename ...Args>
    constexpr auto Descriptor( Args&& ... args )
    {
        if constexpr ( sizeof...( Args ) > 0 )
        {
            using Types = TypeList<Args...>;
            using FormatTraitsT = Internal::FormatTraits<Types>;
            return FormatTraitsT::Descriptor;
        }
        else
        {
            return MakeTuple( static_cast<Byte>( 4 ), static_cast<Byte>( 1 ), Types::UtilityTypeId::TypeList, ModifierFlags::None, static_cast<Byte>( 0 ), static_cast<Byte>( 0 ) );
        }
    }

    template<typename ...Types>
    struct DescriptorType
    {
    private:
        using FormatTraitsT = Internal::FormatTraits<TypeList<Types...>>;
    public:
        using type = typename FormatTraitsT::DescriptorType;
        static constexpr auto value = FormatTraitsT::Descriptor;
    };

    template<>
    struct DescriptorType<>
    {
        using type = Tuple<Byte, Byte, Types::UtilityTypeId, ModifierFlags, Byte, Byte>;
        static constexpr auto value = MakeTuple( static_cast<Byte>( 4 ), static_cast<Byte>( 1 ), Types::UtilityTypeId::TypeList, ModifierFlags::None, static_cast<Byte>( 0 ), static_cast<Byte>( 0 ) );
    };





    
    /// <summary>
    /// Returns true if the size of the buffer required to 
    /// serialize the arguments is independent of the contents
    /// of each argument.
    /// </summary>
    template<typename ...Args>
    inline constexpr bool IsFixedSize( const Args& ... args )
    {
        if constexpr ( sizeof...( Args ) > 0 )
        {
            return ( Types::IsFixedSize<Args>::value && ... );
        }
        else
        {
            return true;
        }
    }
    

    /// <summary>
    /// Calculates the size of the buffer required to serialize
    /// the data passed as arguments to the function.
    /// </summary>
    /// <remarks>
    /// if IsFixedSize( ... ) returns true for the set of arguments
    /// then none of the arguments varies in size between invocations
    /// and BufferSize( ... ) will allways return the same value
    /// </remarks>
    template<typename ...Args>
    inline constexpr size_t BufferSize( const Args& ... args )
    {
        if constexpr ( sizeof...( Args ) > 0 )
        {
            return ( Internal::FormatTraits<Args>::BufferSize( args ) + ... );
        }
        else
        {
            return 0;
        }
    }

    template<typename Writer, typename ...Args>
    inline constexpr void Write( Writer& writer, const Args& ... args )
    {
        if constexpr ( sizeof...( Args ) > 0 )
        {
            ( Internal::FormatTraits<Args>::Write( writer, args ), ... );
        }
    }

    template<typename Reader, typename ...Args>
    inline constexpr void Read( Reader& reader, Args& ... args )
    {
        if constexpr ( sizeof...( Args ) > 0 )
        {
            ( Internal::FormatTraits<Args>::Read( reader, args ), ... );
        }
    }

    
    inline bool IsBasicTypeDescriptor( const Byte* descriptor, size_t descriptorSize ) noexcept
    {
        if ( descriptorSize == 8 &&
            descriptor[0] == 6 &&
            descriptor[1] == 1 &&
            descriptor[2] == static_cast<Byte>( Types::UtilityTypeId::TypeList ) &&
            descriptor[3] == static_cast<Byte>( ModifierFlags::None ) &&
            descriptor[4] == 2 &&
            descriptor[5] == 1 &&
            descriptor[6] >= static_cast<Byte>( Types::BasicTypeIdMin ) &&
            descriptor[6] >= static_cast<Byte>( Types::BasicTypeIdMax ) &&
            ( (descriptor[7] & static_cast<Byte>( Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed | Persistent::ModifierFlags::Sequence )) == static_cast<Byte>( Persistent::ModifierFlags::None ) ) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template<typename T>
        requires ((IsStdVector<T> || IsCoreVector<T> || IsStdSpan<T>) && std::is_same_v<Byte, typename std::remove_cvref_t<T>::value_type >)
    inline bool IsBasicTypeDescriptor(const T& bytes )
    {
        return IsBasicTypeDescriptor( bytes.data(), bytes.size() );
    }


    inline bool IsIntegerBasicTypeDescriptor( const Byte* descriptor, size_t descriptorSize ) noexcept
    {
        if ( descriptorSize == 8 &&
            descriptor[0] == 6 &&
            descriptor[1] == 1 &&
            descriptor[2] == static_cast<Byte>( Types::UtilityTypeId::TypeList ) &&
            descriptor[3] == static_cast<Byte>( ModifierFlags::None ) &&
            descriptor[4] == 2 &&
            descriptor[5] == 1 &&
            ( (descriptor[7] & static_cast<Byte>( Persistent::ModifierFlags::Array | Persistent::ModifierFlags::Fixed | Persistent::ModifierFlags::Sequence )) == static_cast<Byte>( Persistent::ModifierFlags::None ) ) )
        {
            auto typeId = static_cast<Types::BasicTypeId>( descriptor[6] );
            switch ( typeId )
            {
                case Types::BasicTypeId::Unknown:
                case Types::BasicTypeId::Boolean:
                case Types::BasicTypeId::Char:
                case Types::BasicTypeId::WChar:
                case Types::BasicTypeId::Single:
                case Types::BasicTypeId::Double:
                    return false;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    template<typename T>
        requires ( ( IsStdVector<T> || IsCoreVector<T> || IsStdSpan<T> ) && std::is_same_v<Byte, typename std::remove_cvref_t<T>::value_type > )
    inline bool IsIntegerBasicTypeDescriptor( const T& bytes )
    {
        return IsIntegerBasicTypeDescriptor( bytes.data( ), bytes.size( ) );
    }

}

#pragma pack(pop)
#endif


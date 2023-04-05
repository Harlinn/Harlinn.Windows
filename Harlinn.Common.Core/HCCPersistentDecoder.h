#pragma once
#ifndef __HCCPERSISTENTDECODER_H__
#define __HCCPERSISTENTDECODER_H__

#include <HCCTypeDescriptorCursor.h>

namespace Harlinn::Common::Core::Persistent
{
    template<typename ReaderT>
    class FixedSizeBasicArrayDecoder;

    template<typename ReaderT>
    class ArrayDecoder;

    template<typename ReaderT>
    class FixedSizeArrayDecoder;

    template<typename ReaderT>
    class TupleDecoder;

    template<typename ReaderT>
    class TypeListDecoder;

    template<typename ReaderT>
    class AdaptedDecoder;

    template<typename ReaderT>
    class Decoder
    {
    public:
        using ReaderType = ReaderT;

        using FixedSizeBasicArrayDecoderType = FixedSizeBasicArrayDecoder<ReaderType>;
        using ArrayDecoderType = ArrayDecoder<ReaderType>;
        using FixedSizeArrayDecoderType = FixedSizeArrayDecoder<ReaderType>;
        using TupleDecoderType = TupleDecoder<ReaderType>;
        using TypeListDecoderType = TypeListDecoder<ReaderType>;
        using AdaptedDecoderType = AdaptedDecoder<ReaderType>;

    private:
        TypeDescriptorCursor cursor_;
        ReaderType& reader_;
    public:
        Decoder( const Byte* descriptor, ReaderType& reader )
            : cursor_( descriptor ), reader_( reader )
        {
        }

        Decoder( const TypeDescriptorCursor& cursor, ReaderType& reader )
            : cursor_( cursor ), reader_( reader )
        {
        }

        UInt32 Read7BitEncodedValue( )
        {
            return Core::Read7BitEncodedValue( reader_ );
        }

        constexpr Byte TypeId( ) const noexcept
        {
            return cursor_.IsBasicType( );
        }
        constexpr ModifierFlags Modifiers( ) const noexcept
        {
            return cursor_.IsBasicType( );
        }



        constexpr bool IsUnknown( ) const noexcept
        {
            return cursor_.IsBasicType( );
        }
        constexpr bool IsKnownBasicType( ) const noexcept
        {
            return cursor_.IsKnownBasicType( );
        }

        constexpr bool IsKnownContainerType( ) const noexcept
        {
            return cursor_.IsKnownContainerType( );
        }
        constexpr bool IsKnownTupleType( ) const noexcept
        {
            return cursor_.IsKnownTupleType( );
        }

        constexpr bool IsKnownUtilityType( ) const noexcept
        {
            return cursor_.IsKnownUtilityType( );
        }


        constexpr bool IsBasicType( ) const noexcept
        {
            return cursor_.IsBasicType( );
        }
        constexpr bool IsBasicArrayType( ) const noexcept
        {
            return cursor_.IsBasicArrayType( );
        }
        constexpr bool IsFixedSizeBasicArrayType( ) const noexcept
        {
            return cursor_.IsFixedSizeBasicArrayType( );
        }
        constexpr bool IsArrayType( ) const noexcept
        {
            return cursor_.IsArrayType( );
        }
        constexpr bool IsFixedSizeArrayType( ) const noexcept
        {
            return cursor_.IsFixedSizeArrayType( );
        }
        constexpr bool IsTupleType( ) const noexcept
        {
            return cursor_.IsTupleType( );
        }
        constexpr bool IsTypeListType( ) const noexcept
        {
            return cursor_.IsTypeListType( );
        }
        constexpr bool IsAdaptedType( ) const noexcept
        {
            return cursor_.IsAdaptedType( );
        }

        constexpr Types::BasicTypeId BasicTypeId( ) const noexcept
        {
            return cursor_.BasicTypeId( );
        }
        constexpr Types::ContainerTypeId ContainerTypeId( ) const noexcept
        {
            return cursor_.ContainerTypeId( );
        }
        constexpr Types::TupleTypeId TupleTypeId( ) const noexcept
        {
            return cursor_.TupleTypeId( );
        }
        constexpr Types::UtilityTypeId UtilityTypeId( ) const noexcept
        {
            return cursor_.UtilityTypeId( );
        }

        Persistent::BasicType ReadBasicType( ) noexcept
        {
            return cursor_.ReadBasicType( );
        }

        Persistent::BasicArrayType ReadBasicArrayType( ) noexcept
        {
            return cursor_.ReadBasicArrayType( );
        }
        FixedSizeBasicArrayType ReadFixedSizeBasicArrayType( ) noexcept
        {
            return cursor_.ReadFixedSizeBasicArrayType( );
        }

        ArrayType ReadArrayType( ) noexcept
        {
            return cursor_.ReadArrayType( );
        }

        FixedSizeArrayType ReadFixedSizeArrayType( ) noexcept
        {
            return cursor_.ReadFixedSizeArrayType( );
        }

        constexpr Persistent::TupleType ReadTupleType( ) noexcept
        {
            return cursor_.ReadTupleType( );
        }

        constexpr TypeListType ReadTypeListType( ) noexcept
        {
            return cursor_.ReadTypeListType( );
        }

        constexpr AdaptedType ReadAdaptedType( ) noexcept
        {
            return cursor_.ReadAdaptedType( );
        }

        


        template<typename T>
        std::remove_cvref_t<T> Read( )
        {
            return reader_.Read<T>( );
        }
        template<typename T>
        void Read( T& result )
        {
            reader_.Read( result );
        }
    };




}

#endif

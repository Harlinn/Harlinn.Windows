#pragma once
#ifndef HARLINN_COMMON_CORE_HCCSERIALIZATIONDATAREADER_H_
#define HARLINN_COMMON_CORE_HCCSERIALIZATIONDATAREADER_H_
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

#include "HCCSerializationDataType.h"
#include "HCCBinaryReader.h"

namespace Harlinn::Common::Core::IO::Serialization
{
    namespace Internal
    {
        template< IO::StreamReader StreamT, bool networkByteOrder = false, bool use7BitEncodedSize = false >
        class SerializationReader : public BinaryReaderBase<BinaryReader<StreamT, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize>
        {
        public:
            using Base = BinaryReaderBase<BinaryReader<StreamT, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize>;
            using StreamType = StreamT;
        protected:
            StreamType& inStream_;
        public:
            SerializationReader(StreamType& stream)
                : inStream_(stream)
            {
            }

            StreamType& BaseStream()
            {
                return inStream_;
            }
            using Base::Read;
            long long Read(void* buffer, size_t bufferSize)
            {
                return inStream_.Read(buffer, bufferSize);
            }
        };
    }

    template<typename StreamT>
    class DataReader
    {
    public:
        using StreamType = StreamT;
        using BinaryReaderType = Internal::SerializationReader<StreamT>;
    private:
        BinaryReaderType reader_;
    public:
    public:
        DataReader(StreamType& stream)
            : reader_(stream)
        {
        }
    private:
        DataType ReadDataType()
        {
            return static_cast<DataType>(reader_.Read<Byte>());
        }

        
    public:
        template<typename T>
            requires (IsBoolean<T> || IsInteger<T> || IsFloatingPoint<T> || IsTimeSpan<T> || IsDateTime<T> || IsGuid<T> || std::is_enum_v<std::remove_cvref_t<T>>)
        void Read(std::remove_cvref_t<T>& result)
        {
            using ValueType = std::remove_cvref_t<T>;
            result = Read<ValueType>();
        }

        template<typename T>
            requires IsBoolean<std::remove_cvref_t<T>>
        T Read()
        {
            using ValueType = std::remove_cvref_t<T>;

            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::BooleanFalse:
                {
                    return false;
                }
                break;
                case DataType::BooleanTrue:
                {
                    return true;
                }
                break;
                default:
                {
                    auto typeName = ToWideString( typeid(ValueType).name() );
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast<Int32>(dataType), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }
        

        template<typename T>
            requires std::is_enum_v<std::remove_cvref_t<T>>
        T Read()
        {
            using EnumType = std::remove_cvref_t<T>;
            return static_cast<EnumType>(Read<std::underlying_type_t<EnumType>>());
        }



        template<typename T>
            requires (IsStdOptional<std::remove_cvref_t<T>> && IsBoolean<typename T::value_type>)
        T Read()
        {
            using ValueType = std::remove_cvref_t<T>;

            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::Null:
                {
                    return ValueType{};
                }
                break;
                case DataType::BooleanFalse:
                {
                    return false;
                }
                break;
                case DataType::BooleanTrue:
                {
                    return true;
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(ValueType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }





        template<typename T>
            requires Serialization::Internal::TimeTypeDataTypeResolver<std::remove_cvref_t<T>>::value
        T Read()
        {
            using ValueType = std::remove_cvref_t<T>;
            using Resolver = Serialization::Internal::TimeTypeDataTypeResolver<ValueType>;

            auto dataType = ReadDataType();
            switch (dataType)
            {
                case Resolver::ZeroValue:
                {
                    return ValueType();
                }
                break;
                case Resolver::Value:
                {
                    return reader_.Read<ValueType>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(ValueType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }

        template<typename T>
            requires (IsStdOptional<std::remove_cvref_t<T>>&& Serialization::Internal::TimeTypeDataTypeResolver<std::remove_cvref_t<typename T::value_type>>::value)
        T Read()
        {
            using OptionalType = std::remove_cvref_t<T>;
            using ValueType = std::remove_cvref_t<typename T::value_type>;
            using Resolver = Serialization::Internal::TimeTypeDataTypeResolver<ValueType>;

            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::Null:
                {
                    return OptionalType{};
                }
                break;
                case Resolver::ZeroValue:
                {
                    return ValueType(static_cast<Int64>(0));
                }
                break;
                case Resolver::Value:
                {
                    return reader_.Read<ValueType>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(OptionalType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }



        template<typename T>
            requires Serialization::Internal::UnsignedDataTypeResolver<std::remove_cvref_t<T>>::value
        T Read()
        {
            using ValueType = std::remove_cvref_t<T>;
            using Resolver = Serialization::Internal::UnsignedDataTypeResolver<ValueType>;

            auto dataType = ReadDataType();
            switch (dataType)
            {
                case Resolver::ZeroValue:
                {
                    return static_cast<ValueType>(0);
                }
                break;
                case Resolver::OneValue:
                {
                    return static_cast<ValueType>(1);
                }
                break;
                case Resolver::MaxValue:
                {
                    return std::numeric_limits<ValueType>::max();
                }
                break;
                case Resolver::Value:
                {
                    return reader_.Read<ValueType>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(ValueType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }

        template<typename T>
            requires (IsStdOptional<std::remove_cvref_t<T>> && Serialization::Internal::UnsignedDataTypeResolver<std::remove_cvref_t<typename T::value_type>>::value)
        T Read()
        {
            using OptionalType = std::remove_cvref_t<T>;
            using ValueType = std::remove_cvref_t<typename T::value_type>;
            using Resolver = Serialization::Internal::UnsignedDataTypeResolver<ValueType>;

            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::Null:
                {
                    return OptionalType{};
                }
                break;
                case Resolver::ZeroValue:
                {
                    return static_cast<ValueType>(0);
                }
                break;
                case Resolver::OneValue:
                {
                    return static_cast<ValueType>(1);
                }
                break;
                case Resolver::MaxValue:
                {
                    return std::numeric_limits<ValueType>::max();
                }
                break;
                case Resolver::Value:
                {
                    return reader_.Read<ValueType>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(ValueType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }


        template<typename T>
            requires Serialization::Internal::SignedDataTypeResolver<std::remove_cvref_t<T>>::value
        T Read()
        {
            using ValueType = std::remove_cvref_t<T>;
            using Resolver = Serialization::Internal::SignedDataTypeResolver<ValueType>;

            auto dataType = ReadDataType();
            switch (dataType)
            {
                case Resolver::MinValue:
                {
                    return std::numeric_limits<ValueType>::lowest();
                }
                break;
                case Resolver::MinusOneValue:
                {
                    return static_cast<ValueType>(-1);
                }
                break;
                case Resolver::ZeroValue:
                {
                    return static_cast<ValueType>(0);
                }
                break;
                case Resolver::OneValue:
                {
                    return static_cast<ValueType>(1);
                }
                break;
                case Resolver::MaxValue:
                {
                    return std::numeric_limits<ValueType>::max();
                }
                break;
                case Resolver::Value:
                {
                    return reader_.Read<ValueType>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(ValueType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }

        template<typename T>
            requires (IsStdOptional<std::remove_cvref_t<T>> && Serialization::Internal::SignedDataTypeResolver<std::remove_cvref_t<typename T::value_type>>::value)
        T Read()
        {
            using OptionalType = std::remove_cvref_t<T>;
            using ValueType = std::remove_cvref_t<typename T::value_type>;
            using Resolver = Serialization::Internal::SignedDataTypeResolver<ValueType>;

            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::Null:
                {
                    return OptionalType{};
                }
                break;
                case Resolver::MinValue:
                {
                    return std::numeric_limits<ValueType>::lowest();
                }
                break;
                case Resolver::MinusOneValue:
                {
                    return static_cast<ValueType>(-1);
                }
                break;
                case Resolver::ZeroValue:
                {
                    return static_cast<ValueType>(0);
                }
                break;
                case Resolver::OneValue:
                {
                    return static_cast<ValueType>(1);
                }
                break;
                case Resolver::MaxValue:
                {
                    return std::numeric_limits<ValueType>::max();
                }
                break;
                case Resolver::Value:
                {
                    return reader_.Read<ValueType>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(ValueType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }

        template<typename T>
            requires IsCurrency<T>
        T Read()
        {
            using ValueType = std::remove_cvref_t<T>;

            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::MinCurrency:
                {
                    return Currency::fromValue(std::numeric_limits<typename Currency::value_type>::lowest());
                }
                break;
                case DataType::MinusOneCurrency:
                {
                    return Currency(-1LL);
                }
                break;
                case DataType::ZeroCurrency:
                {
                    return Currency(0LL);
                }
                break;
                case DataType::OneCurrency:
                {
                    return Currency(1LL);
                }
                break;
                case DataType::MaxCurrency:
                {
                    return Currency::fromValue(std::numeric_limits<typename Currency::value_type>::max());
                }
                break;
                case DataType::Currency:
                {
                    auto value = reader_.Read<typename Currency::value_type>();
                    return Currency::fromValue(value);
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(ValueType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast<Int32>(dataType), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }

        template<typename T>
            requires (IsStdOptional<std::remove_cvref_t<T>> && IsCurrency<typename T::value_type> )
        T Read()
        {
            using OptionalType = std::remove_cvref_t<T>;
            using ValueType = std::remove_cvref_t<typename T::value_type>;

            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::Null:
                {
                    return OptionalType();
                }
                break;
                case DataType::MinCurrency:
                {
                    return Currency::fromValue(std::numeric_limits<typename Currency::value_type>::lowest());
                }
                break;
                case DataType::MinusOneCurrency:
                {
                    return Currency(-1LL);
                }
                break;
                case DataType::ZeroCurrency:
                {
                    return Currency(0LL);
                }
                break;
                case DataType::OneCurrency:
                {
                    return Currency(1LL);
                }
                break;
                case DataType::MaxCurrency:
                {
                    return Currency::fromValue(std::numeric_limits<typename Currency::value_type>::max());
                }
                break;
                case DataType::Currency:
                {
                    auto value = reader_.Read<typename Currency::value_type>();
                    return Currency::fromValue(value);
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(ValueType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast<Int32>(dataType), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }



        template<typename T>
            requires Serialization::Internal::FloatDataTypeResolver<std::remove_cvref_t<T>>::value
        T Read()
        {
            using ValueType = std::remove_cvref_t<T>;
            using Resolver = Serialization::Internal::FloatDataTypeResolver<ValueType>;

            auto dataType = ReadDataType();
            switch (dataType)
            {
                
                case Resolver::ValueNegativeInfinity:
                {
                    return -std::numeric_limits<ValueType>::infinity();
                }
                break;
                case Resolver::MinValue:
                {
                    return std::numeric_limits<ValueType>::lowest();
                }
                break;
                case Resolver::MinusOneValue:
                {
                    return static_cast<ValueType>(-1.0);
                }
                break;
                case Resolver::ZeroValue:
                {
                    return static_cast<ValueType>(0.0);
                }
                break;
                case Resolver::OneValue:
                {
                    return static_cast<ValueType>(1.0);
                }
                break;
                case Resolver::MaxValue:
                {
                    return std::numeric_limits<ValueType>::max();
                }
                break;
                case Resolver::ValuePositiveInfinity:
                {
                    return std::numeric_limits<ValueType>::infinity();
                }
                break;
                case Resolver::ValueNaN:
                {
                    return std::numeric_limits<ValueType>::quiet_NaN();
                }
                break;
                case Resolver::Value:
                {
                    return reader_.Read<ValueType>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(ValueType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }

        template<typename T>
            requires (IsStdOptional<std::remove_cvref_t<T>> && Serialization::Internal::FloatDataTypeResolver<std::remove_cvref_t<typename T::value_type>>::value)
        T Read()
        {
            using OptionalType = std::remove_cvref_t<T>;
            using ValueType = std::remove_cvref_t<typename T::value_type>;
            using Resolver = Serialization::Internal::FloatDataTypeResolver<ValueType>;

            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::Null:
                {
                    return OptionalType{};
                }
                break;
                case Resolver::ValueNegativeInfinity:
                {
                    return -std::numeric_limits<ValueType>::infinity();
                }
                break;
                case Resolver::MinValue:
                {
                    return std::numeric_limits<ValueType>::lowest();
                }
                break;
                case Resolver::MinusOneValue:
                {
                    return static_cast<ValueType>(-1.0);
                }
                break;
                case Resolver::ZeroValue:
                {
                    return static_cast<ValueType>(0.0);
                }
                break;
                case Resolver::OneValue:
                {
                    return static_cast<ValueType>(1.0);
                }
                break;
                case Resolver::MaxValue:
                {
                    return std::numeric_limits<ValueType>::max();
                }
                break;
                case Resolver::ValuePositiveInfinity:
                {
                    return std::numeric_limits<ValueType>::infinity();
                }
                break;
                case Resolver::ValueNaN:
                {
                    return std::numeric_limits<ValueType>::quiet_NaN();
                }
                break;
                case Resolver::Value:
                {
                    return reader_.Read<ValueType>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(ValueType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }

        template<typename T>
            requires IsGuid<std::remove_cvref_t<T>>
        T Read()
        {
            using ValueType = std::remove_cvref_t<T>;
            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::EmptyGuid:
                {
                    return ValueType();
                }
                break;
                case DataType::Guid:
                {
                    return reader_.Read<Guid>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(ValueType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }

        template<typename T>
            requires (IsStdOptional<std::remove_cvref_t<T>> && IsGuid<std::remove_cvref_t<typename T::value_type>>)
        T Read()
        {
            using OptionalType = std::remove_cvref_t<T>;
            using ValueType = std::remove_cvref_t<typename T::value_type>;
            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::Null:
                {
                    return OptionalType();
                }
                break;
                case DataType::EmptyGuid:
                {
                    return Guid();
                }
                break;
                case DataType::Guid:
                {
                    return reader_.Read<Guid>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(OptionalType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }

        template<typename T>
            requires IsWideString<std::remove_cvref_t<T>>
        T Read()
        {
            using ValueType = std::remove_cvref_t<T>;
            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::EmptyString:
                {
                    return ValueType();
                }
                break;
                case DataType::String:
                {
                    return reader_.Read<ValueType>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(ValueType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
        }

        bool ReadBoolean()
        {
            return Read<bool>();
        }
        wchar_t ReadChar()
        {
            return Read<wchar_t>();
        }
        Byte ReadByte()
        {
            return Read<Byte>();
        }
        SByte ReadSByte()
        {
            return Read<SByte>();
        }
        Int16 ReadInt16()
        {
            return Read<Int16>();
        }
        UInt16 ReadUInt16()
        {
            return Read<UInt16>();
        }
        Int32 ReadInt32()
        {
            return Read<Int32>();
        }
        UInt32 ReadUInt32()
        {
            return Read<UInt32>();
        }
        Int64 ReadInt64()
        {
            return Read<Int64>();
        }
        UInt64 ReadUInt64()
        {
            return Read<UInt64>();
        }
        float ReadSingle()
        {
            return Read<float>();
        }
        double ReadDouble()
        {
            return Read<double>();
        }
        TimeSpan ReadTimeSpan()
        {
            return Read<TimeSpan>();
        }
        DateTime ReadDateTime()
        {
            return Read<DateTime>();
        }
        Guid ReadGuid()
        {
            return Read<Guid>();
        }
        WideString ReadString()
        {
            return Read<WideString>();
        }



        template<typename T>
            requires (IsStdVector<T>&& IsBoolean<typename T::value_type>)
        void Read(T& result)
        {
            using VectorType = std::remove_cvref_t<T>;
            using ValueType = std::remove_cvref_t<typename T::value_type>;
            using Resolver = Serialization::Internal::ArrayDataTypeResolver<bool>;

            result.clear();
            size_t count = 0;
            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::Null:
                case Resolver::EmptyArray:
                {
                    return;
                }
                break;
                case Resolver::SmallArray:
                {
                    count = reader_.Read<Byte>();
                }
                break;
                case Resolver::Array:
                {
                    count = reader_.Read<UInt16>();
                }
                break;
                case Resolver::LargeArray:
                {
                    count = reader_.Read<UInt32>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(VectorType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
            result.resize(count, false);
            static constexpr size_t bufferSize = 4096;
            Byte buffer[4096];
            size_t fullBufferCount = count / bufferSize;
            size_t remainingValueCount = count % bufferSize;

            for (size_t i = 0; i < fullBufferCount; i++)
            {
                reader_.Read(buffer, bufferSize);
                for (size_t j = 0; j < bufferSize; j++)
                {
                    ValueType value = buffer[j];
                    if (value)
                    {
                        result[(i * bufferSize) + j] = value;
                    }
                }
            }
            if (remainingValueCount)
            {
                reader_.Read(buffer, remainingValueCount);
                for (size_t j = 0; j < remainingValueCount; j++)
                {
                    ValueType value = buffer[j];
                    if (value)
                    {
                        result[(fullBufferCount * bufferSize) + j] = value;
                    }
                }
            }

        }

        template<typename T>
            requires (IsStdVector<T>&& (IsInteger<typename T::value_type> || IsFloatingPoint<typename T::value_type> || IsTimeSpan<typename T::value_type> || IsDateTime<typename T::value_type> || IsGuid<typename T::value_type>))
        void Read(T& result)
        {
            using VectorType = std::remove_cvref_t<T>;
            using ValueType = std::remove_cvref_t<typename T::value_type>;
            using Resolver = Serialization::Internal::ArrayDataTypeResolver<ValueType>;

            result.clear();
            size_t count = 0;
            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::Null:
                case Resolver::EmptyArray:
                {
                    return;
                }
                break;
                case Resolver::SmallArray:
                {
                    count = reader_.Read<Byte>();
                }
                break;
                case Resolver::Array:
                {
                    count = reader_.Read<UInt16>();
                }
                break;
                case Resolver::LargeArray:
                {
                    count = reader_.Read<UInt32>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(VectorType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
            result.resize(count);
            reader_.Read(result.data(), count * sizeof(ValueType));
        }

        template<typename T>
            requires (IsStdVector<T> && (IsInteger<typename T::value_type> || IsFloatingPoint<typename T::value_type> || IsTimeSpan<typename T::value_type> || IsDateTime<typename T::value_type> || IsGuid<typename T::value_type>))
        T Read()
        {
            using VectorType = std::remove_cvref_t<T>;
            VectorType result;
            Read(result);
            return result;
        }

        template<typename T, size_t N>
            requires (IsBoolean<T> || IsInteger<T> || IsFloatingPoint<T> || IsTimeSpan<T> || IsDateTime<T> || IsGuid<T>)
        void Read(T(&result)[N])
        {
            using ValueType = std::remove_cvref_t<T>;
            using Resolver = Serialization::Internal::ArrayDataTypeResolver<ValueType>;

            size_t count = 0;
            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::Null:
                case Resolver::EmptyArray:
                {
                    if (N != 0)
                    {
                        auto typeName = ToWideString(typeid(result).name());
                        auto message = Format(L"Invalid argument size: {}, expected: 0, while reading {}.", N, typeName);
                        HCC_THROW(ArgumentException, message);
                    }
                    return;
                }
                break;
                case Resolver::SmallArray:
                {
                    count = reader_.Read<Byte>();
                }
                break;
                case Resolver::Array:
                {
                    count = reader_.Read<UInt16>();
                }
                break;
                case Resolver::LargeArray:
                {
                    count = reader_.Read<UInt32>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(result).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
            if (N != count)
            {
                auto typeName = ToWideString(typeid(result).name());
                auto message = Format(L"Invalid argument size: {}, expected: {}, while reading {}.", N, count ,typeName);
                HCC_THROW(ArgumentException, message);
            }
            reader_.Read(result, count * sizeof(ValueType));
        }

        template<typename T, size_t N>
            requires (IsBoolean<T> || IsInteger<T> || IsFloatingPoint<T> || IsTimeSpan<T> || IsDateTime<T> || IsGuid<T>)
        void Read(std::array<T,N>& result)
        {
            using ValueType = std::remove_cvref_t<T>;
            using Resolver = Serialization::Internal::ArrayDataTypeResolver<ValueType>;

            size_t count = 0;
            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::Null:
                case Resolver::EmptyArray:
                {
                    if (N != 0)
                    {
                        auto typeName = ToWideString(typeid(result).name());
                        auto message = Format(L"Invalid argument size: {}, expected: 0, while reading {}.", N, typeName);
                        HCC_THROW(ArgumentException, message);
                    }
                    return;
                }
                break;
                case Resolver::SmallArray:
                {
                    count = reader_.Read<Byte>();
                }
                break;
                case Resolver::Array:
                {
                    count = reader_.Read<UInt16>();
                }
                break;
                case Resolver::LargeArray:
                {
                    count = reader_.Read<UInt32>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(result).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
            if (N != count)
            {
                auto typeName = ToWideString(typeid(result).name());
                auto message = Format(L"Invalid argument size: {}, expected: {}, while reading {}.", N, count, typeName);
                HCC_THROW(ArgumentException, message);
            }
            reader_.Read(result.data(), count * sizeof(ValueType));
        }

        template<typename T>
            requires (IsStdVector<T> && IsWideString<typename T::value_type>)
        void Read(T& result)
        {
            using VectorType = std::remove_cvref_t<T>;
            using ValueType = std::remove_cvref_t<T::value_type>;
            using Resolver = Serialization::Internal::ArrayDataTypeResolver<ValueType>;

            result.clear();
            size_t count = 0;
            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::Null:
                case Resolver::EmptyArray:
                {
                    return;
                }
                break;
                case Resolver::SmallArray:
                {
                    count = reader_.Read<Byte>();
                }
                break;
                case Resolver::Array:
                {
                    count = reader_.Read<UInt16>();
                }
                break;
                case Resolver::LargeArray:
                {
                    count = reader_.Read<UInt32>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(VectorType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
            result.resize(count);
            for (size_t i = 0; i < count; i++)
            {
                result[i] = reader_.Read<ValueType>();
            }
        }
        template<typename T>
            requires (IsStdVector<T>&& IsStdVector<typename T::value_type>&& std::is_same_v<typename T::value_type::value_type, Byte>)
        void Read(T& result)
        {
            using VectorType = std::remove_cvref_t<T>;
            using ValueType = std::remove_cvref_t<T::value_type>;
            using Resolver = Serialization::Internal::ArrayDataTypeResolver<ValueType>;

            result.clear();
            size_t count = 0;
            auto dataType = ReadDataType();
            switch (dataType)
            {
                case DataType::Null:
                case Resolver::EmptyArray:
                {
                    return;
                }
                break;
                case Resolver::SmallArray:
                {
                    count = reader_.Read<Byte>();
                }
                break;
                case Resolver::Array:
                {
                    count = reader_.Read<UInt16>();
                }
                break;
                case Resolver::LargeArray:
                {
                    count = reader_.Read<UInt32>();
                }
                break;
                default:
                {
                    auto typeName = ToWideString(typeid(VectorType).name());
                    auto message = Format(L"Invalid data type: {} while reading {}.", static_cast< Int32 >( dataType ), typeName);
                    HCC_THROW(Exception, message);
                }
                break;
            }
            result.resize(count);
            for (size_t i = 0; i < count; i++)
            {
                std::vector<Byte> value;
                reader_.Read(value);
                result[i] = std::move(value);
            }
        }




    };


}

#endif

#pragma once
#ifndef HARLINN_COMMON_CORE_HCCSERIALIZATIONDATAWRITER_H_
#define HARLINN_COMMON_CORE_HCCSERIALIZATIONDATAWRITER_H_
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

#include "HCCSerializationDataType.h"
#include "HCCBinaryWriter.h"

namespace Harlinn::Common::Core::IO::Serialization
{
    namespace Internal
    {
        template<IO::StreamWriter StreamT, bool networkByteOrder = false, bool use7BitEncodedSize = false>
        class SerializationWriter : public BinaryWriterBase<BinaryWriter<StreamT, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize>
        {
        public:
            using Base = BinaryWriterBase<BinaryWriter<StreamT, networkByteOrder, use7BitEncodedSize>, networkByteOrder, use7BitEncodedSize>;
            using StreamType = StreamT;
        protected:
            StreamType& outStream_;
        public:
            SerializationWriter(StreamType& output)
                : outStream_(output)
            {
            }


            /// <summary>
            /// Returns the stream associated with the writer. 
            /// </summary>
            /// <returns>the stream associated with the writer</returns>
            StreamType& BaseStream()
            {
                return outStream_;
            }

            using Base::Write;
            void Write(const void* data, size_t dataSize)
            {
                outStream_.Write(data, dataSize);
            }

        };
    }

    template<typename StreamT>
    class DataWriter
    {
    public:
        using StreamType = StreamT;
        using BinaryWriterType = Internal::SerializationWriter<StreamT>;
    private:
        BinaryWriterType writer_;
    public:
        DataWriter(StreamType& stream)
            : writer_(stream)
        { }
    private:
        void WriteDataType(DataType dataType)
        {
            Byte b = (Byte)dataType;
            writer_.Write(b);
        }
    public:

        template<typename T>
            requires IsBoolean<T>
        void Write(const T value)
        {
            WriteDataType(value ? DataType::BooleanTrue : DataType::BooleanFalse);
        }





        template<typename T>
        void Write(const std::optional<T>& v)
        {
            if (v.has_value())
            {
                Write(v.value());
            }
            else
            {
                WriteDataType(DataType::Null);
            }
        }

        template<typename T>
            requires Serialization::Internal::TimeTypeDataTypeResolver<std::remove_cvref_t<T>>::value
        void Write(const T& value)
        {
            using Resolver = Serialization::Internal::TimeTypeDataTypeResolver<std::remove_cvref_t<T>>;
            if (value.Ticks() == 0)
            {
                WriteDataType(Resolver::ZeroValue);
            }
            else
            {
                WriteDataType(Resolver::Value);
                writer_.Write(value);
            }
        }

        template<typename T>
            requires Serialization::Internal::UnsignedDataTypeResolver<std::remove_cvref_t<T>>::value
        void Write(const T value)
        {
            using Resolver = Serialization::Internal::UnsignedDataTypeResolver<std::remove_cvref_t<T>>;
            switch (value)
            {
                case static_cast<T>(0):
                {
                    WriteDataType(Resolver::ZeroValue);
                }
                break;
                case static_cast<T>(1):
                {
                    WriteDataType(Resolver::OneValue);
                }
                break;
                case std::numeric_limits<T>::max():
                {
                    WriteDataType(Resolver::MaxValue);
                }
                break;
                default:
                {
                    WriteDataType(Resolver::Value);
                    writer_.Write(value);
                }
                break;
            }
        }

        template<typename T>
            requires Serialization::Internal::SignedDataTypeResolver<std::remove_cvref_t<T>>::value
        void Write(const T value)
        {
            using Resolver = Serialization::Internal::SignedDataTypeResolver<std::remove_cvref_t<T>>;
            switch (value)
            {
                case std::numeric_limits<T>::lowest():
                {
                    WriteDataType(Resolver::MinValue);
                }
                break;
                case static_cast<T>(-1):
                {
                    WriteDataType(Resolver::MinusOneValue);
                }
                break;
                case static_cast<T>(0):
                {
                    WriteDataType(Resolver::ZeroValue);
                }
                break;
                case static_cast<T>(1):
                {
                    WriteDataType(Resolver::OneValue);
                }
                break;
                case std::numeric_limits<T>::max():
                {
                    WriteDataType(Resolver::MaxValue);
                }
                break;
                default:
                {
                    WriteDataType(Resolver::Value);
                    writer_.Write(value);
                }
                break;
            }
        }

        template<typename T>
            requires std::is_enum_v<std::remove_cvref_t<T>>
        void Write(const T value)
        {
            Write(static_cast<std::underlying_type_t<T>>(value));
        }


        template<typename T>
            requires Serialization::Internal::FloatDataTypeResolver<std::remove_cvref_t<T>>::value
        void Write(const T v)
        {
            using Resolver = Serialization::Internal::FloatDataTypeResolver<std::remove_cvref_t<T>>;
            if (v == std::numeric_limits<T>::max())
            {
                WriteDataType(Resolver::MaxValue);
            }
            else if (v == std::numeric_limits<T>::lowest())
            {
                WriteDataType(Resolver::MinValue);
            }
            else if (v == std::numeric_limits<T>::infinity())
            {
                WriteDataType(Resolver::ValuePositiveInfinity);
            }
            else if (v == -std::numeric_limits<T>::infinity())
            {
                WriteDataType(Resolver::ValueNegativeInfinity);
            }
            else if (std::isnan(v))
            {
                WriteDataType(Resolver::ValueNaN);
            }
            else if (v == static_cast<T>(0.0))
            {
                WriteDataType(Resolver::ZeroValue);
            }
            else if (v == static_cast<T>(1.0))
            {
                WriteDataType(Resolver::OneValue);
            }
            else if (v == static_cast<T>(-1.0))
            {
                WriteDataType(Resolver::MinusOneValue);
            }
            else
            {
                WriteDataType(Resolver::Value);
                writer_.Write(v);
            }
        }

        template<typename T>
            requires IsGuid<T>
        void Write(const T& value)
        {
            if (value.IsEmpty())
            {
                WriteDataType(DataType::EmptyGuid);
            }
            else
            {
                WriteDataType(DataType::Guid);
                writer_.Write(&value, sizeof(Guid));
            }
        }


        template<typename T>
            requires (IsStdBasicString<T> || IsStdBasicStringView<T> || IsBasicString<T> || IsBasicStringView<T> )
        void Write(const T& v)
        {
            if (v.size() == 0)
            {
                WriteDataType(DataType::EmptyString);
            }
            else
            {
                WriteDataType(DataType::String);
                writer_.Write(v);
            }
        }

        template<typename T>
            requires IsWideCharString<T>
        void Write(const T v)
        {
            if (v == nullptr)
            {
                WriteDataType(DataType::Null);
            }
            else
            {
                std::wstring_view wsv(v);
                if (wsv.size() == 0)
                {
                    WriteDataType(DataType::EmptyString);
                }
                else
                {
                    WriteDataType(DataType::String);
                    writer_.Write(v);
                }
            }
        }

    private:
        void WriteBooleanArray(const Byte* values, size_t numberOfValues)
        {
            if (values == nullptr)
            {
                WriteDataType(DataType::Null);
            }
            else if (numberOfValues == 0)
            {
                WriteDataType(DataType::EmptyBooleanArray);
            }
            else
            {
                if (numberOfValues <= std::numeric_limits<Byte>::max())
                {
                    WriteDataType(DataType::SmallBooleanArray);
                    Byte len = static_cast<Byte>(numberOfValues);
                    writer_.Write(len);
                }
                else if (numberOfValues <= std::numeric_limits<UInt16>::max())
                {
                    WriteDataType(DataType::BooleanArray);
                    UInt16 len = static_cast<UInt16>(numberOfValues);
                    writer_.Write(len);
                }
                else
                {
                    WriteDataType(DataType::LargeBooleanArray);
                    UInt32 len = static_cast<UInt32>(numberOfValues);
                    writer_.Write(len);
                }

                writer_.Write(values, numberOfValues);
            }
        }
        void WriteBooleanArray(const std::vector<bool>& v)
        {
            size_t numberOfValues = v.size();
            if (numberOfValues == 0)
            {
                WriteDataType(DataType::EmptyBooleanArray);
            }
            else
            {
                std::unique_ptr<Byte[]> values(new Byte[v.size()]);
                Byte* ptr = values.get();
                for (size_t i = 0; i < numberOfValues; i++)
                {
                    ptr[i] = v[i] ? 1 : 0;
                }
                WriteBooleanArray(ptr, numberOfValues);
            }
        }
        static_assert(sizeof(bool) == 1);
        void WriteBooleanArray(const bool* values, size_t numberOfValues)
        {
            WriteBooleanArray(reinterpret_cast<const Byte*>(values), numberOfValues);
        }

    public:
        template<typename T>
            requires (IsStdVector<T>&& IsBoolean<typename T::value_type>)
        void Write(const T& values)
        {
            WriteBooleanArray(values);
        }
        template<typename T, size_t N>
            requires IsBoolean<T>
        void Write(const T(&values)[N])
        {
            WriteBooleanArray(values, N);
        }
        template<typename T, size_t N>
            requires IsBoolean<T>
        void Write(const std::array<T, N>& values)
        {
            WriteBooleanArray(values.data(), N);
        }
        template<typename T>
            requires (IsStdSpan<T>&& IsBoolean<typename T::value_type>)
        void Write(const T& values)
        {
            WriteBooleanArray(values.data(), values.size());
        }
    private:
        template<typename T>
            requires (IsInteger<T> || IsFloatingPoint<T> || IsTimeSpan<T> || IsDateTime<T> || IsGuid<T>)
        void WriteArray(const T* values, size_t numberOfValues)
        {
            using ValueType = std::remove_cvref_t<T>;
            using Resolver = Serialization::Internal::ArrayDataTypeResolver<ValueType>;
            if (values == nullptr)
            {
                WriteDataType(DataType::Null);
            }
            else if (numberOfValues == 0)
            {
                WriteDataType(Resolver::EmptyArray);
            }
            else
            {
                if (numberOfValues <= std::numeric_limits<Byte>::max())
                {
                    WriteDataType(Resolver::SmallArray);
                    Byte len = static_cast<Byte>(numberOfValues);
                    writer_.Write(len);
                }
                else if (numberOfValues <= std::numeric_limits<UInt16>::max())
                {
                    WriteDataType(Resolver::Array);
                    UInt16 len = static_cast<UInt16>(numberOfValues);
                    writer_.Write(len);
                }
                else
                {
                    WriteDataType(Resolver::LargeArray);
                    UInt32 len = static_cast<UInt32>(numberOfValues);
                    writer_.Write(len);
                }
                writer_.Write(values, numberOfValues*sizeof(ValueType));
            }
        }
    public:
        template<typename T>
            requires (IsStdVector<T> && (IsInteger<typename T::value_type> || IsFloatingPoint<typename T::value_type> || IsTimeSpan<typename T::value_type> || IsDateTime<typename T::value_type> || IsGuid<typename T::value_type>))
        void Write(const T& values)
        {
            WriteArray(values.data(), values.size());
        }
        template<typename T, size_t N>
            requires (IsInteger<T> || IsFloatingPoint<T> || IsTimeSpan<T> || IsDateTime<T> || IsGuid<T>)
        void Write(const T(&values)[N])
        {
            WriteArray(values, N);
        }
        template<typename T, size_t N>
            requires (IsInteger<T> || IsFloatingPoint<T> || IsTimeSpan<T> || IsDateTime<T> || IsGuid<T>)
        void Write(const std::array<T,N>& values)
        {
            WriteArray(values.data(), N);
        }
        template<typename T>
            requires (IsStdSpan<T> && (IsInteger<typename T::value_type> || IsFloatingPoint<typename T::value_type> || IsTimeSpan<typename T::value_type> || IsDateTime<typename T::value_type> || IsGuid<typename T::value_type>))
        void Write(const T& values)
        {
            WriteArray(values.data(), values.size());
        }
    private:
        void WriteStringArray(const WideString* values, size_t numberOfValues)
        {
            using Resolver = Serialization::Internal::ArrayDataTypeResolver<WideString>;
            if (values == nullptr)
            {
                WriteDataType(DataType::Null);
            }
            else if (numberOfValues == 0)
            {
                WriteDataType(Resolver::EmptyArray);
            }
            else
            {
                if (numberOfValues <= std::numeric_limits<Byte>::max())
                {
                    WriteDataType(Resolver::SmallArray);
                    Byte len = static_cast<Byte>(numberOfValues);
                    writer_.Write(len);
                }
                else if (numberOfValues <= std::numeric_limits<UInt16>::max())
                {
                    WriteDataType(Resolver::Array);
                    UInt16 len = static_cast<UInt16>(numberOfValues);
                    writer_.Write(len);
                }
                else
                {
                    WriteDataType(Resolver::LargeArray);
                    UInt32 len = static_cast<UInt32>(numberOfValues);
                    writer_.Write(len);
                }
                for (size_t i = 0; i < numberOfValues; i++)
                {
                    writer_.Write(values[i]);
                }
            }
        }
    public:
        template<typename T>
            requires (IsStdVector<T> && IsWideString<typename T::value_type>)
        void Write(const T& values)
        {
            WriteStringArray(values.data(), values.size());
        }
        template<typename T, size_t N>
            requires IsWideString<T>
        void Write(const T(&values)[N])
        {
            WriteStringArray(values, N);
        }
        template<typename T, size_t N>
            requires IsWideString<T>
        void Write(const std::array<T, N>& values)
        {
            WriteStringArray(values.data(), N);
        }
        template<typename T>
            requires (IsStdSpan<T> && IsWideString<typename T::value_type>)
        void Write(const T& values)
        {
            WriteStringArray(values.data(), values.size());
        }
    private:
        void WriteByteArrayList(const std::vector<std::vector<Byte>>* values, size_t numberOfValues)
        {
            using Resolver = Serialization::Internal::ArrayDataTypeResolver<std::vector<Byte>>;
            if (values == nullptr)
            {
                WriteDataType(DataType::Null);
            }
            else if (numberOfValues == 0)
            {
                WriteDataType(Resolver::EmptyArray);
            }
            else
            {
                if (numberOfValues <= std::numeric_limits<Byte>::max())
                {
                    WriteDataType(Resolver::SmallArray);
                    Byte len = static_cast<Byte>(numberOfValues);
                    writer_.Write(len);
                }
                else if (numberOfValues <= std::numeric_limits<UInt16>::max())
                {
                    WriteDataType(Resolver::Array);
                    UInt16 len = static_cast<UInt16>(numberOfValues);
                    writer_.Write(len);
                }
                else
                {
                    WriteDataType(Resolver::LargeArray);
                    UInt32 len = static_cast<UInt32>(numberOfValues);
                    writer_.Write(len);
                }
                for (size_t i = 0; i < numberOfValues; i++)
                {
                    Write(values[i]);
                }
            }
        }
    public:
        template<typename T>
            requires (IsStdVector<T> && IsStdVector<typename T::value_type>&& std::is_same_v<typename T::value_type::value_type,Byte>)
        void Write(const T& values)
        {
            WriteByteArrayList(values.data(), values.size());
        }


    };
}

#endif

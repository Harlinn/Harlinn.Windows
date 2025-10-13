#pragma once
#ifndef HARLINN_COMMON_CORE_HCCSERIALIZATIONDATATYPE_H_
#define HARLINN_COMMON_CORE_HCCSERIALIZATIONDATATYPE_H_
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

#include "HCCDef.h"
#include "HCCDateTime.h"
#include "HCCGuid.h"

namespace Harlinn::Common::Core::IO::Serialization
{
    enum class DataType : Byte
    {
        Unknown,
        Eos,
        Null,
        BooleanTrue,
        BooleanFalse,

        ZeroChar,
        OneChar,
        MaxChar,
        Char,

        ZeroByte,
        OneByte,
        MaxByte,
        Byte,

        MinSByte,
        MinusOneSByte,
        ZeroSByte,
        OneSByte,
        MaxSByte,
        SByte,

        MinInt16,
        MinusOneInt16,
        ZeroInt16,
        OneInt16,
        MaxInt16,
        Int16,

        ZeroUInt16,
        OneUInt16,
        MaxUInt16,
        UInt16,

        MinInt32,
        MinusOneInt32,
        ZeroInt32,
        OneInt32,
        MaxInt32,
        Int32,

        ZeroUInt32,
        OneUInt32,
        MaxUInt32,
        UInt32,

        MinInt64,
        MinusOneInt64,
        ZeroInt64,
        OneInt64,
        MaxInt64,
        Int64,

        ZeroUInt64,
        OneUInt64,
        MaxUInt64,
        UInt64,

        SingleNegativeInfinity,
        MinSingle,
        MinusOneSingle,
        ZeroSingle,
        OneSingle,
        MaxSingle,
        SinglePositiveInfinity,
        SingleNaN,
        Single,

        DoubleNegativeInfinity,
        MinDouble,
        MinusOneDouble,
        ZeroDouble,
        OneDouble,
        MaxDouble,
        DoublePositiveInfinity,
        DoubleNaN,
        Double,

        DateTime,
        ZeroDateTime,

        TimeSpan,
        ZeroTimeSpan,

        EmptyGuid,
        Guid,
        

        EmptyString,
        // 7-bit encoded byte length. then the bytes of the string prefixed with the BOM
        StringUTF,  // <-- reserved for future
        // 7-bit encoded byte length. then the bytes of the utf 8 string
        StringUTF8,
        // 7-bit encoded byte length. then the bytes of the utf 16 string
        StringUTF16LE,
        // UInt16 code page id, then 7-bit encoded byte length. then the bytes of the string
        StringInCodePage,  // <-- reserved for future

        MinCurrency,
        MinusOneCurrency,
        ZeroCurrency,
        OneCurrency,
        MaxCurrency,
        Currency,

        SmallBooleanArray = 0x80,
        BooleanArray,
        LargeBooleanArray,
        EmptyBooleanArray,

        SmallCharArray,
        CharArray,
        LargeCharArray,
        EmptyCharArray,

        SmallSByteArray,
        SByteArray,
        LargeSByteArray,
        EmptySByteArray,

        SmallByteArray,
        ByteArray,
        LargeByteArray,
        EmptyByteArray,

        SmallInt16Array,
        Int16Array,
        LargeInt16Array,
        EmptyInt16Array,

        SmallUInt16Array,
        UInt16Array,
        LargeUInt16Array,
        EmptyUInt16Array,

        SmallInt32Array,
        Int32Array,
        LargeInt32Array,
        EmptyInt32Array,

        SmallUInt32Array,
        UInt32Array,
        LargeUInt32Array,
        EmptyUInt32Array,

        SmallInt64Array,
        Int64Array,
        LargeInt64Array,
        EmptyInt64Array,

        SmallUInt64Array,
        UInt64Array,
        LargeUInt64Array,
        EmptyUInt64Array,

        SmallSingleArray,
        SingleArray,
        LargeSingleArray,
        EmptySingleArray,

        SmallDoubleArray,
        DoubleArray,
        LargeDoubleArray,
        EmptyDoubleArray,

        SmallDateTimeArray,
        DateTimeArray,
        LargeDateTimeArray,
        EmptyDateTimeArray,

        SmallTimeSpanArray,
        TimeSpanArray,
        LargeTimeSpanArray,
        EmptyTimeSpanArray,

        SmallGuidArray,
        GuidArray,
        LargeGuidArray,
        EmptyGuidArray,

        SmallStringArray,
        StringArray,
        LargeStringArray,
        EmptyStringArray,

        SmallByteArrayList,
        ByteArrayList,
        LargeByteArrayList,
        EmptyByteArrayList,
    };

    


    namespace Internal
    {
        template<typename T>
        struct TimeTypeDataTypeResolver : std::false_type
        { };

        template<>
        struct TimeTypeDataTypeResolver<DateTime> : std::true_type
        {
            static constexpr DataType Value = DataType::DateTime;
            static constexpr DataType ZeroValue = DataType::ZeroDateTime;
        };
        template<>
        struct TimeTypeDataTypeResolver<TimeSpan> : std::true_type
        {
            static constexpr DataType Value = DataType::TimeSpan;
            static constexpr DataType ZeroValue = DataType::ZeroTimeSpan;
        };


        template<typename T>
        struct UnsignedDataTypeResolver : std::false_type
        {
        };

        template<>
        struct UnsignedDataTypeResolver<wchar_t> : std::true_type
        {
            static constexpr DataType ZeroValue = DataType::ZeroChar;
            static constexpr DataType OneValue = DataType::OneChar;
            static constexpr DataType MaxValue = DataType::MaxChar;
            static constexpr DataType Value = DataType::Char;
        };

        template<>
        struct UnsignedDataTypeResolver<unsigned char> : std::true_type
        {
            static constexpr DataType ZeroValue = DataType::ZeroByte;
            static constexpr DataType OneValue = DataType::OneByte;
            static constexpr DataType MaxValue = DataType::MaxByte;
            static constexpr DataType Value = DataType::Byte;
        };

        template<>
        struct UnsignedDataTypeResolver<unsigned short> : std::true_type
        {
            static constexpr DataType ZeroValue = DataType::ZeroUInt16;
            static constexpr DataType OneValue = DataType::OneUInt16;
            static constexpr DataType MaxValue = DataType::MaxUInt16;
            static constexpr DataType Value = DataType::UInt16;
        };
        template<>
        struct UnsignedDataTypeResolver<unsigned int> : std::true_type
        {
            static constexpr DataType ZeroValue = DataType::ZeroUInt32;
            static constexpr DataType OneValue = DataType::OneUInt32;
            static constexpr DataType MaxValue = DataType::MaxUInt32;
            static constexpr DataType Value = DataType::UInt32;
        };
        template<>
        struct UnsignedDataTypeResolver<unsigned long> : UnsignedDataTypeResolver<unsigned int>
        {
        };
        template<>
        struct UnsignedDataTypeResolver<unsigned long long> : std::true_type
        {
            static constexpr DataType ZeroValue = DataType::ZeroUInt64;
            static constexpr DataType OneValue = DataType::OneUInt64;
            static constexpr DataType MaxValue = DataType::MaxUInt64;
            static constexpr DataType Value = DataType::UInt64;
        };



        template<typename T>
        struct SignedDataTypeResolver : std::false_type
        {
        };

        template<>
        struct SignedDataTypeResolver<signed char> : std::true_type
        {
            static constexpr DataType MinValue = DataType::MinSByte;
            static constexpr DataType MinusOneValue = DataType::MinusOneSByte;
            static constexpr DataType ZeroValue = DataType::ZeroSByte;
            static constexpr DataType OneValue = DataType::OneSByte;
            static constexpr DataType MaxValue = DataType::MaxSByte;
            static constexpr DataType Value = DataType::SByte;
        };
        template<>
        struct SignedDataTypeResolver<char> : SignedDataTypeResolver<signed char>
        {
        };
        template<>
        struct SignedDataTypeResolver<short> : std::true_type
        {
            static constexpr DataType MinValue = DataType::MinInt16;
            static constexpr DataType MinusOneValue = DataType::MinusOneInt16;
            static constexpr DataType ZeroValue = DataType::ZeroInt16;
            static constexpr DataType OneValue = DataType::OneInt16;
            static constexpr DataType MaxValue = DataType::MaxInt16;
            static constexpr DataType Value = DataType::Int16;
        };
        template<>
        struct SignedDataTypeResolver<int> : std::true_type
        {
            static constexpr DataType MinValue = DataType::MinInt32;
            static constexpr DataType MinusOneValue = DataType::MinusOneInt32;
            static constexpr DataType ZeroValue = DataType::ZeroInt32;
            static constexpr DataType OneValue = DataType::OneInt32;
            static constexpr DataType MaxValue = DataType::MaxInt32;
            static constexpr DataType Value = DataType::Int32;
        };
        template<>
        struct SignedDataTypeResolver<long> : SignedDataTypeResolver<int>
        { };

        template<>
        struct SignedDataTypeResolver<long long> : std::true_type
        {
            static constexpr DataType MinValue = DataType::MinInt64;
            static constexpr DataType MinusOneValue = DataType::MinusOneInt64;
            static constexpr DataType ZeroValue = DataType::ZeroInt64;
            static constexpr DataType OneValue = DataType::OneInt64;
            static constexpr DataType MaxValue = DataType::MaxInt64;
            static constexpr DataType Value = DataType::Int64;
        };

        template<typename T>
        struct FloatDataTypeResolver : std::false_type
        {
        };

        template<>
        struct FloatDataTypeResolver<float> : std::true_type
        {
            static constexpr DataType ValueNegativeInfinity = DataType::SingleNegativeInfinity;
            static constexpr DataType MinValue = DataType::MinSingle;
            static constexpr DataType MinusOneValue = DataType::MinusOneSingle;
            static constexpr DataType ZeroValue = DataType::ZeroSingle;
            static constexpr DataType OneValue = DataType::OneSingle;
            static constexpr DataType MaxValue = DataType::MaxSingle;
            static constexpr DataType ValuePositiveInfinity = DataType::SinglePositiveInfinity;
            static constexpr DataType ValueNaN = DataType::SingleNaN;
            static constexpr DataType Value = DataType::Single;
        };
        template<>
        struct FloatDataTypeResolver<double> : std::true_type
        {
            static constexpr DataType ValueNegativeInfinity = DataType::DoubleNegativeInfinity;
            static constexpr DataType MinValue = DataType::MinDouble;
            static constexpr DataType MinusOneValue = DataType::MinusOneDouble;
            static constexpr DataType ZeroValue = DataType::ZeroDouble;
            static constexpr DataType OneValue = DataType::OneDouble;
            static constexpr DataType MaxValue = DataType::MaxDouble;
            static constexpr DataType ValuePositiveInfinity = DataType::DoublePositiveInfinity;
            static constexpr DataType ValueNaN = DataType::DoubleNaN;
            static constexpr DataType Value = DataType::Double;
        };





        template<typename T>
        struct ArrayDataTypeResolver : std::false_type
        {
        };
        
        template<>
        struct ArrayDataTypeResolver<bool> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallBooleanArray;
            static constexpr DataType Array = DataType::BooleanArray;
            static constexpr DataType LargeArray = DataType::LargeBooleanArray;
            static constexpr DataType EmptyArray = DataType::EmptyBooleanArray;
        };

        template<>
        struct ArrayDataTypeResolver<wchar_t> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallCharArray;
            static constexpr DataType Array = DataType::CharArray;
            static constexpr DataType LargeArray = DataType::LargeCharArray;
            static constexpr DataType EmptyArray = DataType::EmptyCharArray;
        };


        template<>
        struct ArrayDataTypeResolver<signed char> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallSByteArray;
            static constexpr DataType Array = DataType::SByteArray;
            static constexpr DataType LargeArray = DataType::LargeSByteArray;
            static constexpr DataType EmptyArray = DataType::EmptySByteArray;
        };

        template<>
        struct ArrayDataTypeResolver<unsigned char> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallByteArray;
            static constexpr DataType Array = DataType::ByteArray;
            static constexpr DataType LargeArray = DataType::LargeByteArray;
            static constexpr DataType EmptyArray = DataType::EmptyByteArray;
        };

        template<>
        struct ArrayDataTypeResolver<short> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallInt16Array;
            static constexpr DataType Array = DataType::Int16Array;
            static constexpr DataType LargeArray = DataType::LargeInt16Array;
            static constexpr DataType EmptyArray = DataType::EmptyInt16Array;
        };
        template<>
        struct ArrayDataTypeResolver<unsigned short> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallUInt16Array;
            static constexpr DataType Array = DataType::UInt16Array;
            static constexpr DataType LargeArray = DataType::LargeUInt16Array;
            static constexpr DataType EmptyArray = DataType::EmptyUInt16Array;
        };
        template<>
        struct ArrayDataTypeResolver<int> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallInt32Array;
            static constexpr DataType Array = DataType::Int32Array;
            static constexpr DataType LargeArray = DataType::LargeInt32Array;
            static constexpr DataType EmptyArray = DataType::EmptyInt32Array;
        };
        template<>
        struct ArrayDataTypeResolver<long> : public ArrayDataTypeResolver<int> 
        {
            
        };
        template<>
        struct ArrayDataTypeResolver<unsigned int> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallUInt32Array;
            static constexpr DataType Array = DataType::UInt32Array;
            static constexpr DataType LargeArray = DataType::LargeUInt32Array;
            static constexpr DataType EmptyArray = DataType::EmptyUInt32Array;
        };
        template<>
        struct ArrayDataTypeResolver<unsigned long> : public ArrayDataTypeResolver<unsigned int>
        {

        };
        template<>
        struct ArrayDataTypeResolver<long long> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallInt64Array;
            static constexpr DataType Array = DataType::Int64Array;
            static constexpr DataType LargeArray = DataType::LargeInt64Array;
            static constexpr DataType EmptyArray = DataType::EmptyInt64Array;
        };
        template<>
        struct ArrayDataTypeResolver<unsigned long long> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallUInt64Array;
            static constexpr DataType Array = DataType::UInt64Array;
            static constexpr DataType LargeArray = DataType::LargeUInt64Array;
            static constexpr DataType EmptyArray = DataType::EmptyUInt64Array;
        };

        template<>
        struct ArrayDataTypeResolver<float> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallSingleArray;
            static constexpr DataType Array = DataType::SingleArray;
            static constexpr DataType LargeArray = DataType::LargeSingleArray;
            static constexpr DataType EmptyArray = DataType::EmptySingleArray;
        };
        template<>
        struct ArrayDataTypeResolver<double> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallDoubleArray;
            static constexpr DataType Array = DataType::DoubleArray;
            static constexpr DataType LargeArray = DataType::LargeDoubleArray;
            static constexpr DataType EmptyArray = DataType::EmptyDoubleArray;
        };
        template<>
        struct ArrayDataTypeResolver<DateTime> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallDateTimeArray;
            static constexpr DataType Array = DataType::DateTimeArray;
            static constexpr DataType LargeArray = DataType::LargeDateTimeArray;
            static constexpr DataType EmptyArray = DataType::EmptyDateTimeArray;
        };
        template<>
        struct ArrayDataTypeResolver<TimeSpan> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallTimeSpanArray;
            static constexpr DataType Array = DataType::TimeSpanArray;
            static constexpr DataType LargeArray = DataType::LargeTimeSpanArray;
            static constexpr DataType EmptyArray = DataType::EmptyTimeSpanArray;
        };
        template<>
        struct ArrayDataTypeResolver<Guid> : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallGuidArray;
            static constexpr DataType Array = DataType::GuidArray;
            static constexpr DataType LargeArray = DataType::LargeGuidArray;
            static constexpr DataType EmptyArray = DataType::EmptyGuidArray;
        };

        
        struct StringArrayTypeResolver : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallStringArray;
            static constexpr DataType Array = DataType::StringArray;
            static constexpr DataType LargeArray = DataType::LargeStringArray;
            static constexpr DataType EmptyArray = DataType::EmptyStringArray;
        };

        template<>
        struct ArrayDataTypeResolver<WideString> : StringArrayTypeResolver
        {
        };
        template<>
        struct ArrayDataTypeResolver<std::wstring_view> : StringArrayTypeResolver
        {
        };
        template<>
        struct ArrayDataTypeResolver<wchar_t*> : StringArrayTypeResolver
        {
        };


        struct ByteArrayTypeResolver : std::true_type
        {
            static constexpr DataType SmallArray = DataType::SmallByteArrayList;
            static constexpr DataType Array = DataType::ByteArrayList;
            static constexpr DataType LargeArray = DataType::LargeByteArrayList;
            static constexpr DataType EmptyArray = DataType::EmptyByteArrayList;
        };

        template<typename AllocatorT>
        struct ArrayDataTypeResolver<std::vector<Byte, AllocatorT>> : ByteArrayTypeResolver
        {
            
        };

        template<size_t size>
        struct ArrayDataTypeResolver<std::span<Byte, size>> : ByteArrayTypeResolver
        {

        };




    }

}

#endif


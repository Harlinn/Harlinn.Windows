#pragma once
#ifndef __HOCITRAITS_H__
#define __HOCITRAITS_H__
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

#include <HOCIForwards.h>

namespace Harlinn::OCI::Internal
{
    template<typename T>
    struct Traits
    {
    };

    template<typename BT, typename ABT, typename DT, typename ADT>
    struct TraitsImpl
    {
        using BindType = BT;
        using ArrayBindType = ABT;
        using DefineType = DT;
        using ArrayDefineType = ADT;
    };
    template<>
    struct Traits<bool> : TraitsImpl<BooleanBind, BooleanArrayBind, BooleanDefine, BooleanArrayDefine> { };
    template<>
    struct Traits<SByte> : TraitsImpl<SByteBind, SByteArrayBind, SByteDefine, SByteArrayDefine> {};
    template<>
    struct Traits<Byte> : TraitsImpl<ByteBind, ByteArrayBind, ByteDefine, ByteArrayDefine> {};
    template<>
    struct Traits<Int16> : TraitsImpl<Int16Bind, Int16ArrayBind, Int16Define, Int16ArrayDefine> {};
    template<>
    struct Traits<UInt16> : TraitsImpl<UInt16Bind, UInt16ArrayBind, UInt16Define, UInt16ArrayDefine> {};
    template<>
    struct Traits<Int32> : TraitsImpl<Int32Bind, Int32ArrayBind, Int32Define, Int32ArrayDefine> {};
    template<>
    struct Traits<UInt32> : TraitsImpl<UInt32Bind, UInt32ArrayBind, UInt32Define, UInt32ArrayDefine> {};
    template<>
    struct Traits<Int64> : TraitsImpl<Int64Bind, Int64ArrayBind, Int64Define, Int64ArrayDefine> {};
    template<>
    struct Traits<UInt64> : TraitsImpl<UInt64Bind, UInt64ArrayBind, UInt64Define, UInt64ArrayDefine> {};
    template<>
    struct Traits<Single> : TraitsImpl<SingleBind, SingleArrayBind, SingleDefine, SingleArrayDefine> {};
    template<>
    struct Traits<Double> : TraitsImpl<DoubleBind, DoubleArrayBind, DoubleDefine, DoubleArrayDefine> {};

    template<>
    struct Traits<DateTime> : TraitsImpl<TimestampBind, TimestampArrayBind, TimestampDefine, TimestampArrayDefine> {};
    template<>
    struct Traits<Guid> : TraitsImpl<GuidBind, GuidArrayBind, GuidDefine, GuidArrayDefine> {};
    template<>
    struct Traits<WideString> : TraitsImpl<CStringBind, CStringArrayBind, CStringDefine, CStringArrayDefine> {};
    template<>
    struct Traits<wchar_t*> : TraitsImpl<CStringBind, CStringArrayBind, CStringDefine, CStringArrayDefine> {};

    

    template<typename T>
    inline constexpr bool IsSimple = IsAnyOf_v<T, bool, SByte, Byte, Int16, UInt16, Int32, UInt32, Int64, UInt64, Single, Double>;

    template<typename T>
    inline constexpr bool HasTraits = IsAnyOf_v<T, bool, SByte, Byte, Int16, UInt16, Int32, UInt32, Int64, UInt64, Single, Double, DateTime, Guid, WideString>;

    template<typename T>
    concept SimpleBindableType = HasTraits<T> || ( IsSpecializationOf<T,std::optional> && HasTraits<typename T::value_type> );



}

#endif

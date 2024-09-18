﻿/*
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

using System;

namespace Harlinn.Common.Core.Net.Data
{
    public interface IBaseDataFactory<TEnum> where TEnum : struct, Enum
    {
        BaseDataGuid<TEnum> Create(TEnum objectType);
        BaseDataGuid<TEnum> ReadFrom(BinaryReader source);
        BaseDataGuid<TEnum>? ReadNullableFrom(BinaryReader source);
        IList<BaseDataGuid<TEnum>> ReadStreamFrom(BinaryReader source);
        IList<BaseDataGuid<TEnum>> ReadListFrom(BinaryReader source);
    }
}

/*
    Copyright 2024-2026 Espen Harlinn
 
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
﻿using System;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data
{
    public interface IDataContextBase<TKind> : IDisposable where TKind : struct, Enum
    {
        Guid SessionId { get; }
        bool Update([DisallowNull] UpdateData<TKind> updateData);

        bool Merge([DisallowNull] BaseDataGuid<TKind> dataObject);
        bool Insert([DisallowNull] BaseDataGuid<TKind> dataObject);
        bool Update([DisallowNull] BaseDataGuid<TKind> dataObject);
        bool Delete([DisallowNull] BaseDataGuid<TKind> dataObject);



    }
}

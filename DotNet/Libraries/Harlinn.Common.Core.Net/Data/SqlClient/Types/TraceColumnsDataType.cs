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
using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class TraceColumnsDataType
{
    readonly short _traceColumnId = 0;
    readonly string? _name;
    readonly string? _typeName;
    readonly int? _maxSize;
    readonly bool _isFilterable = false;
    readonly bool _isRepeatable = false;
    readonly bool _isRepeatedBase = false;

    public TraceColumnsDataType( )
    {
    }

    public TraceColumnsDataType(short traceColumnId,
        string? name,
        string? typeName,
        int? maxSize,
        bool isFilterable,
        bool isRepeatable,
        bool isRepeatedBase)
    {
        _traceColumnId = traceColumnId;
        _name = name;
        _typeName = typeName;
        _maxSize = maxSize;
        _isFilterable = isFilterable;
        _isRepeatable = isRepeatable;
        _isRepeatedBase = isRepeatedBase;
    }

    public short TraceColumnId => _traceColumnId;
    public string? Name => _name;
    public string? TypeName => _typeName;
    public int? MaxSize => _maxSize;
    public bool IsFilterable => _isFilterable;
    public bool IsRepeatable => _isRepeatable;
    public bool IsRepeatedBase => _isRepeatedBase;
}

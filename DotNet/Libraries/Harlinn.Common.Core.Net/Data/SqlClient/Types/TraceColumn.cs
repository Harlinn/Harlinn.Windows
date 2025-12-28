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

/// <summary>
/// Represents a column definition used in trace data, including metadata such as name, type, and filtering
/// capabilities.
/// </summary>
/// <remarks>
/// Use this class to describe the properties and characteristics of a trace column when working with
/// trace data or event logging systems. Instances of this class are typically used to convey schema information for
/// trace records.
/// </remarks>
public class TraceColumn
{
    readonly short _traceColumnId = 0;
    readonly string? _name;
    readonly string? _typeName;
    readonly int? _maxSize;
    readonly bool _isFilterable = false;
    readonly bool _isRepeatable = false;
    readonly bool _isRepeatedBase = false;

    public TraceColumn( )
    {
    }

    public TraceColumn(short traceColumnId,
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

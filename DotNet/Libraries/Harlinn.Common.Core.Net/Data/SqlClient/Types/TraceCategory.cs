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
/// Represents a row from the sys.trace_categories catalog view.
/// </summary>
public class TraceCategory
{
    readonly short _categoryId = 0;
    readonly string? _name;
    readonly byte _type = 0;

    public TraceCategory( )
    {
    }

    public TraceCategory(short categoryId,
        string? name,
        byte type)
    {
        _categoryId = categoryId;
        _name = name;
        _type = type;
    }

    public short CategoryId => _categoryId;
    public string? Name => _name;
    public byte Type => _type;
}

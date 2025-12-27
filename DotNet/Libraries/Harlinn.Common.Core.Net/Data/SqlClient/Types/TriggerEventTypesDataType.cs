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

public class TriggerEventTypesDataType
{
    readonly int _type = 0;
    readonly string? _typeName;
    readonly int? _parentType;

    public TriggerEventTypesDataType( )
    {
    }

    public TriggerEventTypesDataType(int type,
        string? typeName,
        int? parentType)
    {
        _type = type;
        _typeName = typeName;
        _parentType = parentType;
    }

    public int Type => _type;
    public string? TypeName => _typeName;
    public int? ParentType => _parentType;
}

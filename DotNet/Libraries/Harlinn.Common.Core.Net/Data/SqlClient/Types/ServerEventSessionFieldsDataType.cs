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

public class ServerEventSessionFieldsDataType
{
    readonly int _eventSessionId = 0;
    readonly int _objectId = 0;
    readonly string? _name;
    readonly object? _value;

    public ServerEventSessionFieldsDataType( )
    {
    }

    public ServerEventSessionFieldsDataType(int eventSessionId,
        int objectId,
        string? name,
        object? value)
    {
        _eventSessionId = eventSessionId;
        _objectId = objectId;
        _name = name;
        _value = value;
    }

    public int EventSessionId => _eventSessionId;
    public int ObjectId => _objectId;
    public string? Name => _name;
    public object? Value => _value;
}

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
using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class SystemComponentsSurfaceAreaConfigurationDataType
{
    readonly string? _componentName;
    readonly string? _databaseName;
    readonly string? _schemaName;
    readonly string _objectName = string.Empty;
    readonly byte? _state;
    readonly string _type = string.Empty;
    readonly string? _typeDesc;

    public SystemComponentsSurfaceAreaConfigurationDataType( )
    {
    }

    public SystemComponentsSurfaceAreaConfigurationDataType(string? componentName,
        string? databaseName,
        string? schemaName,
        string objectName,
        byte? state,
        string type,
        string? typeDesc)
    {
        _componentName = componentName;
        _databaseName = databaseName;
        _schemaName = schemaName;
        _objectName = objectName;
        _state = state;
        _type = type;
        _typeDesc = typeDesc;
    }

    public string? ComponentName => _componentName;
    public string? DatabaseName => _databaseName;
    public string? SchemaName => _schemaName;
    public string ObjectName => _objectName;
    public byte? State => _state;
    public string Type => _type;
    public string? TypeDesc => _typeDesc;
}

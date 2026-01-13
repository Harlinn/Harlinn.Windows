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

public class DmXeObjectColumnsDataType
{
    readonly string _name = string.Empty;
    readonly int _columnId = 0;
    readonly string _objectName = string.Empty;
    readonly Guid _objectPackageGuid;
    readonly string _typeName = string.Empty;
    readonly Guid _typePackageGuid;
    readonly string _columnType = string.Empty;
    readonly string? _columnValue;
    readonly int? _capabilities;
    readonly string? _capabilitiesDesc;
    readonly string? _description;

    public DmXeObjectColumnsDataType( )
    {
    }

    public DmXeObjectColumnsDataType(string name,
        int columnId,
        string objectName,
        Guid objectPackageGuid,
        string typeName,
        Guid typePackageGuid,
        string columnType,
        string? columnValue,
        int? capabilities,
        string? capabilitiesDesc,
        string? description)
    {
        _name = name;
        _columnId = columnId;
        _objectName = objectName;
        _objectPackageGuid = objectPackageGuid;
        _typeName = typeName;
        _typePackageGuid = typePackageGuid;
        _columnType = columnType;
        _columnValue = columnValue;
        _capabilities = capabilities;
        _capabilitiesDesc = capabilitiesDesc;
        _description = description;
    }

    public string Name => _name;
    public int ColumnId => _columnId;
    public string ObjectName => _objectName;
    public Guid ObjectPackageGuid => _objectPackageGuid;
    public string TypeName => _typeName;
    public Guid TypePackageGuid => _typePackageGuid;
    public string ColumnType => _columnType;
    public string? ColumnValue => _columnValue;
    public int? Capabilities => _capabilities;
    public string? CapabilitiesDesc => _capabilitiesDesc;
    public string? Description => _description;
}

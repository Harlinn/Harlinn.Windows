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

public class DmXeSessionObjectColumnsDataType
{
    readonly byte[] _eventSessionAddress = Array.Empty<byte>();
    readonly string _columnName = string.Empty;
    readonly int _columnId = 0;
    readonly string? _columnValue;
    readonly string _objectType = string.Empty;
    readonly string _objectName = string.Empty;
    readonly Guid _objectPackageGuid;

    public DmXeSessionObjectColumnsDataType( )
    {
    }

    public DmXeSessionObjectColumnsDataType(byte[] eventSessionAddress,
        string columnName,
        int columnId,
        string? columnValue,
        string objectType,
        string objectName,
        Guid objectPackageGuid)
    {
        _eventSessionAddress = eventSessionAddress;
        _columnName = columnName;
        _columnId = columnId;
        _columnValue = columnValue;
        _objectType = objectType;
        _objectName = objectName;
        _objectPackageGuid = objectPackageGuid;
    }

    public byte[] EventSessionAddress => _eventSessionAddress;
    public string ColumnName => _columnName;
    public int ColumnId => _columnId;
    public string? ColumnValue => _columnValue;
    public string ObjectType => _objectType;
    public string ObjectName => _objectName;
    public Guid ObjectPackageGuid => _objectPackageGuid;
}

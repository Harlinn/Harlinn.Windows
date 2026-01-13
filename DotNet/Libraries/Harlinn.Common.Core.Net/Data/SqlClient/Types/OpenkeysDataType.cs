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

public class OpenkeysDataType
{
    readonly int? _databaseId;
    readonly string? _databaseName;
    readonly int? _keyId;
    readonly string? _keyName;
    readonly Guid? _keyGuid;
    readonly DateTime? _openedDate;
    readonly short? _status;

    public OpenkeysDataType( )
    {
    }

    public OpenkeysDataType(int? databaseId,
        string? databaseName,
        int? keyId,
        string? keyName,
        Guid? keyGuid,
        DateTime? openedDate,
        short? status)
    {
        _databaseId = databaseId;
        _databaseName = databaseName;
        _keyId = keyId;
        _keyName = keyName;
        _keyGuid = keyGuid;
        _openedDate = openedDate;
        _status = status;
    }

    public int? DatabaseId => _databaseId;
    public string? DatabaseName => _databaseName;
    public int? KeyId => _keyId;
    public string? KeyName => _keyName;
    public Guid? KeyGuid => _keyGuid;
    public DateTime? OpenedDate => _openedDate;
    public short? Status => _status;
}

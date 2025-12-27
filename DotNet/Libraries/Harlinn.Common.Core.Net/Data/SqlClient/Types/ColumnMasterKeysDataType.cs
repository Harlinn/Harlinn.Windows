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

public class ColumnMasterKeysDataType
{
    readonly string _name = string.Empty;
    readonly int _columnMasterKeyId = 0;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;
    readonly string? _keyStoreProviderName;
    readonly string? _keyPath;
    readonly int _allowEnclaveComputations = 0;
    readonly byte[]? _signature;

    public ColumnMasterKeysDataType( )
    {
    }

    public ColumnMasterKeysDataType(string name,
        int columnMasterKeyId,
        DateTime createDate,
        DateTime modifyDate,
        string? keyStoreProviderName,
        string? keyPath,
        int allowEnclaveComputations,
        byte[]? signature)
    {
        _name = name;
        _columnMasterKeyId = columnMasterKeyId;
        _createDate = createDate;
        _modifyDate = modifyDate;
        _keyStoreProviderName = keyStoreProviderName;
        _keyPath = keyPath;
        _allowEnclaveComputations = allowEnclaveComputations;
        _signature = signature;
    }

    public string Name => _name;
    public int ColumnMasterKeyId => _columnMasterKeyId;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
    public string? KeyStoreProviderName => _keyStoreProviderName;
    public string? KeyPath => _keyPath;
    public int AllowEnclaveComputations => _allowEnclaveComputations;
    public byte[]? Signature => _signature;
}

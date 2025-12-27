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

public class ColumnEncryptionKeyValuesDataType
{
    readonly int _columnEncryptionKeyId = 0;
    readonly int _columnMasterKeyId = 0;
    readonly byte[]? _encryptedValue;
    readonly string? _encryptionAlgorithmName;

    public ColumnEncryptionKeyValuesDataType( )
    {
    }

    public ColumnEncryptionKeyValuesDataType(int columnEncryptionKeyId,
        int columnMasterKeyId,
        byte[]? encryptedValue,
        string? encryptionAlgorithmName)
    {
        _columnEncryptionKeyId = columnEncryptionKeyId;
        _columnMasterKeyId = columnMasterKeyId;
        _encryptedValue = encryptedValue;
        _encryptionAlgorithmName = encryptionAlgorithmName;
    }

    public int ColumnEncryptionKeyId => _columnEncryptionKeyId;
    public int ColumnMasterKeyId => _columnMasterKeyId;
    public byte[]? EncryptedValue => _encryptedValue;
    public string? EncryptionAlgorithmName => _encryptionAlgorithmName;
}

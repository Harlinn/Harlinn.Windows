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

public class DmDatabaseEncryptionKeysDataType
{
    readonly int? _databaseId;
    readonly int? _encryptionState;
    readonly DateTime? _createDate;
    readonly DateTime? _regenerateDate;
    readonly DateTime? _modifyDate;
    readonly DateTime? _setDate;
    readonly DateTime? _openedDate;
    readonly string? _keyAlgorithm;
    readonly int? _keyLength;
    readonly byte[]? _encryptorThumbprint;
    readonly string? _encryptorType;
    readonly float? _percentComplete;
    readonly string? _encryptionStateDesc;
    readonly int? _encryptionScanState;
    readonly string? _encryptionScanStateDesc;
    readonly DateTime? _encryptionScanModifyDate;

    public DmDatabaseEncryptionKeysDataType( )
    {
    }

    public DmDatabaseEncryptionKeysDataType(int? databaseId,
        int? encryptionState,
        DateTime? createDate,
        DateTime? regenerateDate,
        DateTime? modifyDate,
        DateTime? setDate,
        DateTime? openedDate,
        string? keyAlgorithm,
        int? keyLength,
        byte[]? encryptorThumbprint,
        string? encryptorType,
        float? percentComplete,
        string? encryptionStateDesc,
        int? encryptionScanState,
        string? encryptionScanStateDesc,
        DateTime? encryptionScanModifyDate)
    {
        _databaseId = databaseId;
        _encryptionState = encryptionState;
        _createDate = createDate;
        _regenerateDate = regenerateDate;
        _modifyDate = modifyDate;
        _setDate = setDate;
        _openedDate = openedDate;
        _keyAlgorithm = keyAlgorithm;
        _keyLength = keyLength;
        _encryptorThumbprint = encryptorThumbprint;
        _encryptorType = encryptorType;
        _percentComplete = percentComplete;
        _encryptionStateDesc = encryptionStateDesc;
        _encryptionScanState = encryptionScanState;
        _encryptionScanStateDesc = encryptionScanStateDesc;
        _encryptionScanModifyDate = encryptionScanModifyDate;
    }

    public int? DatabaseId => _databaseId;
    public int? EncryptionState => _encryptionState;
    public DateTime? CreateDate => _createDate;
    public DateTime? RegenerateDate => _regenerateDate;
    public DateTime? ModifyDate => _modifyDate;
    public DateTime? SetDate => _setDate;
    public DateTime? OpenedDate => _openedDate;
    public string? KeyAlgorithm => _keyAlgorithm;
    public int? KeyLength => _keyLength;
    public byte[]? EncryptorThumbprint => _encryptorThumbprint;
    public string? EncryptorType => _encryptorType;
    public float? PercentComplete => _percentComplete;
    public string? EncryptionStateDesc => _encryptionStateDesc;
    public int? EncryptionScanState => _encryptionScanState;
    public string? EncryptionScanStateDesc => _encryptionScanStateDesc;
    public DateTime? EncryptionScanModifyDate => _encryptionScanModifyDate;
}

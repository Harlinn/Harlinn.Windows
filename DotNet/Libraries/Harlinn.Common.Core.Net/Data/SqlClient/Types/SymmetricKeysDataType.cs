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

public class SymmetricKeysDataType
{
    readonly string _name = string.Empty;
    readonly int? _principalId;
    readonly int _symmetricKeyId = 0;
    readonly int _keyLength = 0;
    readonly string _keyAlgorithm = string.Empty;
    readonly string? _algorithmDesc;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;
    readonly Guid? _keyGuid;
    readonly object? _keyThumbprint;
    readonly string? _providerType;
    readonly Guid? _cryptographicProviderGuid;
    readonly object? _cryptographicProviderAlgid;

    public SymmetricKeysDataType( )
    {
    }

    public SymmetricKeysDataType(string name,
        int? principalId,
        int symmetricKeyId,
        int keyLength,
        string keyAlgorithm,
        string? algorithmDesc,
        DateTime createDate,
        DateTime modifyDate,
        Guid? keyGuid,
        object? keyThumbprint,
        string? providerType,
        Guid? cryptographicProviderGuid,
        object? cryptographicProviderAlgid)
    {
        _name = name;
        _principalId = principalId;
        _symmetricKeyId = symmetricKeyId;
        _keyLength = keyLength;
        _keyAlgorithm = keyAlgorithm;
        _algorithmDesc = algorithmDesc;
        _createDate = createDate;
        _modifyDate = modifyDate;
        _keyGuid = keyGuid;
        _keyThumbprint = keyThumbprint;
        _providerType = providerType;
        _cryptographicProviderGuid = cryptographicProviderGuid;
        _cryptographicProviderAlgid = cryptographicProviderAlgid;
    }

    public string Name => _name;
    public int? PrincipalId => _principalId;
    public int SymmetricKeyId => _symmetricKeyId;
    public int KeyLength => _keyLength;
    public string KeyAlgorithm => _keyAlgorithm;
    public string? AlgorithmDesc => _algorithmDesc;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
    public Guid? KeyGuid => _keyGuid;
    public object? KeyThumbprint => _keyThumbprint;
    public string? ProviderType => _providerType;
    public Guid? CryptographicProviderGuid => _cryptographicProviderGuid;
    public object? CryptographicProviderAlgid => _cryptographicProviderAlgid;
}

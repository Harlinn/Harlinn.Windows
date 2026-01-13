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

public class AsymmetricKeysDataType
{
    readonly string _name = string.Empty;
    readonly int? _principalId;
    readonly int _asymmetricKeyId = 0;
    readonly string _pvtKeyEncryptionType = string.Empty;
    readonly string? _pvtKeyEncryptionTypeDesc;
    readonly byte[] _thumbprint = Array.Empty<byte>();
    readonly string _algorithm = string.Empty;
    readonly string? _algorithmDesc;
    readonly int _keyLength = 0;
    readonly byte[]? _sid;
    readonly string? _stringSid;
    readonly byte[] _publicKey = Array.Empty<byte>();
    readonly string? _attestedBy;
    readonly string? _providerType;
    readonly Guid? _cryptographicProviderGuid;
    readonly object? _cryptographicProviderAlgid;

    public AsymmetricKeysDataType( )
    {
    }

    public AsymmetricKeysDataType(string name,
        int? principalId,
        int asymmetricKeyId,
        string pvtKeyEncryptionType,
        string? pvtKeyEncryptionTypeDesc,
        byte[] thumbprint,
        string algorithm,
        string? algorithmDesc,
        int keyLength,
        byte[]? sid,
        string? stringSid,
        byte[] publicKey,
        string? attestedBy,
        string? providerType,
        Guid? cryptographicProviderGuid,
        object? cryptographicProviderAlgid)
    {
        _name = name;
        _principalId = principalId;
        _asymmetricKeyId = asymmetricKeyId;
        _pvtKeyEncryptionType = pvtKeyEncryptionType;
        _pvtKeyEncryptionTypeDesc = pvtKeyEncryptionTypeDesc;
        _thumbprint = thumbprint;
        _algorithm = algorithm;
        _algorithmDesc = algorithmDesc;
        _keyLength = keyLength;
        _sid = sid;
        _stringSid = stringSid;
        _publicKey = publicKey;
        _attestedBy = attestedBy;
        _providerType = providerType;
        _cryptographicProviderGuid = cryptographicProviderGuid;
        _cryptographicProviderAlgid = cryptographicProviderAlgid;
    }

    public string Name => _name;
    public int? PrincipalId => _principalId;
    public int AsymmetricKeyId => _asymmetricKeyId;
    public string PvtKeyEncryptionType => _pvtKeyEncryptionType;
    public string? PvtKeyEncryptionTypeDesc => _pvtKeyEncryptionTypeDesc;
    public byte[] Thumbprint => _thumbprint;
    public string Algorithm => _algorithm;
    public string? AlgorithmDesc => _algorithmDesc;
    public int KeyLength => _keyLength;
    public byte[]? Sid => _sid;
    public string? StringSid => _stringSid;
    public byte[] PublicKey => _publicKey;
    public string? AttestedBy => _attestedBy;
    public string? ProviderType => _providerType;
    public Guid? CryptographicProviderGuid => _cryptographicProviderGuid;
    public object? CryptographicProviderAlgid => _cryptographicProviderAlgid;
}

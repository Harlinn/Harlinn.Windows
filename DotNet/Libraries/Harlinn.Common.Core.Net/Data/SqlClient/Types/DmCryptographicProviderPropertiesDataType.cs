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

public class DmCryptographicProviderPropertiesDataType
{
    readonly int? _providerId;
    readonly Guid? _guid;
    readonly string? _providerVersion;
    readonly string? _sqlcryptVersion;
    readonly string? _friendlyName;
    readonly string? _authenticationType;
    readonly byte? _symmetricKeySupport;
    readonly byte? _symmetricKeyPersistance;
    readonly byte? _symmetricKeyExport;
    readonly byte? _symmetricKeyImport;
    readonly byte? _asymmetricKeySupport;
    readonly byte? _asymmetricKeyPersistance;
    readonly byte? _asymmetricKeyExport;
    readonly byte? _asymmetricKeyImport;

    public DmCryptographicProviderPropertiesDataType( )
    {
    }

    public DmCryptographicProviderPropertiesDataType(int? providerId,
        Guid? guid,
        string? providerVersion,
        string? sqlcryptVersion,
        string? friendlyName,
        string? authenticationType,
        byte? symmetricKeySupport,
        byte? symmetricKeyPersistance,
        byte? symmetricKeyExport,
        byte? symmetricKeyImport,
        byte? asymmetricKeySupport,
        byte? asymmetricKeyPersistance,
        byte? asymmetricKeyExport,
        byte? asymmetricKeyImport)
    {
        _providerId = providerId;
        _guid = guid;
        _providerVersion = providerVersion;
        _sqlcryptVersion = sqlcryptVersion;
        _friendlyName = friendlyName;
        _authenticationType = authenticationType;
        _symmetricKeySupport = symmetricKeySupport;
        _symmetricKeyPersistance = symmetricKeyPersistance;
        _symmetricKeyExport = symmetricKeyExport;
        _symmetricKeyImport = symmetricKeyImport;
        _asymmetricKeySupport = asymmetricKeySupport;
        _asymmetricKeyPersistance = asymmetricKeyPersistance;
        _asymmetricKeyExport = asymmetricKeyExport;
        _asymmetricKeyImport = asymmetricKeyImport;
    }

    public int? ProviderId => _providerId;
    public Guid? Guid => _guid;
    public string? ProviderVersion => _providerVersion;
    public string? SqlcryptVersion => _sqlcryptVersion;
    public string? FriendlyName => _friendlyName;
    public string? AuthenticationType => _authenticationType;
    public byte? SymmetricKeySupport => _symmetricKeySupport;
    public byte? SymmetricKeyPersistance => _symmetricKeyPersistance;
    public byte? SymmetricKeyExport => _symmetricKeyExport;
    public byte? SymmetricKeyImport => _symmetricKeyImport;
    public byte? AsymmetricKeySupport => _asymmetricKeySupport;
    public byte? AsymmetricKeyPersistance => _asymmetricKeyPersistance;
    public byte? AsymmetricKeyExport => _asymmetricKeyExport;
    public byte? AsymmetricKeyImport => _asymmetricKeyImport;
}

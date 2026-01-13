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

public class DatabasePrincipalsDataType
{
    readonly string _name = string.Empty;
    readonly int _principalId = 0;
    readonly string _type = string.Empty;
    readonly string? _typeDesc;
    readonly string? _defaultSchemaName;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;
    readonly int? _owningPrincipalId;
    readonly byte[]? _sid;
    readonly bool _isFixedRole = false;
    readonly int _authenticationType = 0;
    readonly string? _authenticationTypeDesc;
    readonly string? _defaultLanguageName;
    readonly int? _defaultLanguageLcid;
    readonly bool _allowEncryptedValueModifications = false;

    public DatabasePrincipalsDataType( )
    {
    }

    public DatabasePrincipalsDataType(string name,
        int principalId,
        string type,
        string? typeDesc,
        string? defaultSchemaName,
        DateTime createDate,
        DateTime modifyDate,
        int? owningPrincipalId,
        byte[]? sid,
        bool isFixedRole,
        int authenticationType,
        string? authenticationTypeDesc,
        string? defaultLanguageName,
        int? defaultLanguageLcid,
        bool allowEncryptedValueModifications)
    {
        _name = name;
        _principalId = principalId;
        _type = type;
        _typeDesc = typeDesc;
        _defaultSchemaName = defaultSchemaName;
        _createDate = createDate;
        _modifyDate = modifyDate;
        _owningPrincipalId = owningPrincipalId;
        _sid = sid;
        _isFixedRole = isFixedRole;
        _authenticationType = authenticationType;
        _authenticationTypeDesc = authenticationTypeDesc;
        _defaultLanguageName = defaultLanguageName;
        _defaultLanguageLcid = defaultLanguageLcid;
        _allowEncryptedValueModifications = allowEncryptedValueModifications;
    }

    public string Name => _name;
    public int PrincipalId => _principalId;
    public string Type => _type;
    public string? TypeDesc => _typeDesc;
    public string? DefaultSchemaName => _defaultSchemaName;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
    public int? OwningPrincipalId => _owningPrincipalId;
    public byte[]? Sid => _sid;
    public bool IsFixedRole => _isFixedRole;
    public int AuthenticationType => _authenticationType;
    public string? AuthenticationTypeDesc => _authenticationTypeDesc;
    public string? DefaultLanguageName => _defaultLanguageName;
    public int? DefaultLanguageLcid => _defaultLanguageLcid;
    public bool AllowEncryptedValueModifications => _allowEncryptedValueModifications;
}

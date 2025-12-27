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

public class ServerPrincipalsDataType
{
    readonly string _name = string.Empty;
    readonly int _principalId = 0;
    readonly byte[]? _sid;
    readonly string _type = string.Empty;
    readonly string? _typeDesc;
    readonly bool? _isDisabled;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;
    readonly string? _defaultDatabaseName;
    readonly string? _defaultLanguageName;
    readonly int? _credentialId;
    readonly int? _owningPrincipalId;
    readonly bool _isFixedRole = false;

    public ServerPrincipalsDataType( )
    {
    }

    public ServerPrincipalsDataType(string name,
        int principalId,
        byte[]? sid,
        string type,
        string? typeDesc,
        bool? isDisabled,
        DateTime createDate,
        DateTime modifyDate,
        string? defaultDatabaseName,
        string? defaultLanguageName,
        int? credentialId,
        int? owningPrincipalId,
        bool isFixedRole)
    {
        _name = name;
        _principalId = principalId;
        _sid = sid;
        _type = type;
        _typeDesc = typeDesc;
        _isDisabled = isDisabled;
        _createDate = createDate;
        _modifyDate = modifyDate;
        _defaultDatabaseName = defaultDatabaseName;
        _defaultLanguageName = defaultLanguageName;
        _credentialId = credentialId;
        _owningPrincipalId = owningPrincipalId;
        _isFixedRole = isFixedRole;
    }

    public string Name => _name;
    public int PrincipalId => _principalId;
    public byte[]? Sid => _sid;
    public string Type => _type;
    public string? TypeDesc => _typeDesc;
    public bool? IsDisabled => _isDisabled;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
    public string? DefaultDatabaseName => _defaultDatabaseName;
    public string? DefaultLanguageName => _defaultLanguageName;
    public int? CredentialId => _credentialId;
    public int? OwningPrincipalId => _owningPrincipalId;
    public bool IsFixedRole => _isFixedRole;
}

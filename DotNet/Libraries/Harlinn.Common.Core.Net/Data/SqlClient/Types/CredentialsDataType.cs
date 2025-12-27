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

public class CredentialsDataType
{
    readonly int _credentialId = 0;
    readonly string _name = string.Empty;
    readonly string? _credentialIdentity;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;
    readonly string? _targetType;
    readonly int? _targetId;

    public CredentialsDataType( )
    {
    }

    public CredentialsDataType(int credentialId,
        string name,
        string? credentialIdentity,
        DateTime createDate,
        DateTime modifyDate,
        string? targetType,
        int? targetId)
    {
        _credentialId = credentialId;
        _name = name;
        _credentialIdentity = credentialIdentity;
        _createDate = createDate;
        _modifyDate = modifyDate;
        _targetType = targetType;
        _targetId = targetId;
    }

    public int CredentialId => _credentialId;
    public string Name => _name;
    public string? CredentialIdentity => _credentialIdentity;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
    public string? TargetType => _targetType;
    public int? TargetId => _targetId;
}

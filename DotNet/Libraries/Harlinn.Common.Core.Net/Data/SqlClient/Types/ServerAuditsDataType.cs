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

public class ServerAuditsDataType
{
    readonly int _auditId = 0;
    readonly string _name = string.Empty;
    readonly Guid? _auditGuid;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;
    readonly int? _principalId;
    readonly string _type = string.Empty;
    readonly string? _typeDesc;
    readonly byte? _onFailure;
    readonly string? _onFailureDesc;
    readonly bool? _isStateEnabled;
    readonly int? _queueDelay;
    readonly string? _predicate;

    public ServerAuditsDataType( )
    {
    }

    public ServerAuditsDataType(int auditId,
        string name,
        Guid? auditGuid,
        DateTime createDate,
        DateTime modifyDate,
        int? principalId,
        string type,
        string? typeDesc,
        byte? onFailure,
        string? onFailureDesc,
        bool? isStateEnabled,
        int? queueDelay,
        string? predicate)
    {
        _auditId = auditId;
        _name = name;
        _auditGuid = auditGuid;
        _createDate = createDate;
        _modifyDate = modifyDate;
        _principalId = principalId;
        _type = type;
        _typeDesc = typeDesc;
        _onFailure = onFailure;
        _onFailureDesc = onFailureDesc;
        _isStateEnabled = isStateEnabled;
        _queueDelay = queueDelay;
        _predicate = predicate;
    }

    public int AuditId => _auditId;
    public string Name => _name;
    public Guid? AuditGuid => _auditGuid;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
    public int? PrincipalId => _principalId;
    public string Type => _type;
    public string? TypeDesc => _typeDesc;
    public byte? OnFailure => _onFailure;
    public string? OnFailureDesc => _onFailureDesc;
    public bool? IsStateEnabled => _isStateEnabled;
    public int? QueueDelay => _queueDelay;
    public string? Predicate => _predicate;
}

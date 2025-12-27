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

public class ServerFileAuditsDataType
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
    readonly long? _maxFileSize;
    readonly int? _maxRolloverFiles;
    readonly int? _maxFiles;
    readonly bool? _reserveDiskSpace;
    readonly string? _logFilePath;
    readonly string? _logFileName;
    readonly int? _retentionDays;

    public ServerFileAuditsDataType( )
    {
    }

    public ServerFileAuditsDataType(int auditId,
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
        string? predicate,
        long? maxFileSize,
        int? maxRolloverFiles,
        int? maxFiles,
        bool? reserveDiskSpace,
        string? logFilePath,
        string? logFileName,
        int? retentionDays)
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
        _maxFileSize = maxFileSize;
        _maxRolloverFiles = maxRolloverFiles;
        _maxFiles = maxFiles;
        _reserveDiskSpace = reserveDiskSpace;
        _logFilePath = logFilePath;
        _logFileName = logFileName;
        _retentionDays = retentionDays;
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
    public long? MaxFileSize => _maxFileSize;
    public int? MaxRolloverFiles => _maxRolloverFiles;
    public int? MaxFiles => _maxFiles;
    public bool? ReserveDiskSpace => _reserveDiskSpace;
    public string? LogFilePath => _logFilePath;
    public string? LogFileName => _logFileName;
    public int? RetentionDays => _retentionDays;
}

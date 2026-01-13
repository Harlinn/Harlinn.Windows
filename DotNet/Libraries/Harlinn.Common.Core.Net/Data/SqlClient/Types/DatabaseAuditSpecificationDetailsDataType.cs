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

public class DatabaseAuditSpecificationDetailsDataType
{
    readonly int _databaseSpecificationId = 0;
    readonly string _auditActionId = string.Empty;
    readonly string? _auditActionName;
    readonly byte _class = 0;
    readonly string? _classDesc;
    readonly int _majorId = 0;
    readonly int _minorId = 0;
    readonly int _auditedPrincipalId = 0;
    readonly string? _auditedResult;
    readonly bool? _isGroup;

    public DatabaseAuditSpecificationDetailsDataType( )
    {
    }

    public DatabaseAuditSpecificationDetailsDataType(int databaseSpecificationId,
        string auditActionId,
        string? auditActionName,
        byte class__,
        string? classDesc,
        int majorId,
        int minorId,
        int auditedPrincipalId,
        string? auditedResult,
        bool? isGroup)
    {
        _databaseSpecificationId = databaseSpecificationId;
        _auditActionId = auditActionId;
        _auditActionName = auditActionName;
        _class = class__;
        _classDesc = classDesc;
        _majorId = majorId;
        _minorId = minorId;
        _auditedPrincipalId = auditedPrincipalId;
        _auditedResult = auditedResult;
        _isGroup = isGroup;
    }

    public int DatabaseSpecificationId => _databaseSpecificationId;
    public string AuditActionId => _auditActionId;
    public string? AuditActionName => _auditActionName;
    public byte Class => _class;
    public string? ClassDesc => _classDesc;
    public int MajorId => _majorId;
    public int MinorId => _minorId;
    public int AuditedPrincipalId => _auditedPrincipalId;
    public string? AuditedResult => _auditedResult;
    public bool? IsGroup => _isGroup;
}

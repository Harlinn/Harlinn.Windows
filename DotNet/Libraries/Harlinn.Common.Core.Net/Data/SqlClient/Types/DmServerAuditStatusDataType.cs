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

public class DmServerAuditStatusDataType
{
    readonly int _auditId = 0;
    readonly string _name = string.Empty;
    readonly short _status = 0;
    readonly string _statusDesc = string.Empty;
    readonly DateTime _statusTime;
    readonly byte[]? _eventSessionAddress;
    readonly string? _auditFilePath;
    readonly long? _auditFileSize;

    public DmServerAuditStatusDataType( )
    {
    }

    public DmServerAuditStatusDataType(int auditId,
        string name,
        short status,
        string statusDesc,
        DateTime statusTime,
        byte[]? eventSessionAddress,
        string? auditFilePath,
        long? auditFileSize)
    {
        _auditId = auditId;
        _name = name;
        _status = status;
        _statusDesc = statusDesc;
        _statusTime = statusTime;
        _eventSessionAddress = eventSessionAddress;
        _auditFilePath = auditFilePath;
        _auditFileSize = auditFileSize;
    }

    public int AuditId => _auditId;
    public string Name => _name;
    public short Status => _status;
    public string StatusDesc => _statusDesc;
    public DateTime StatusTime => _statusTime;
    public byte[]? EventSessionAddress => _eventSessionAddress;
    public string? AuditFilePath => _auditFilePath;
    public long? AuditFileSize => _auditFileSize;
}

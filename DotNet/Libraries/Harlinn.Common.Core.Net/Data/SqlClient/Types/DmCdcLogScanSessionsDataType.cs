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

public class DmCdcLogScanSessionsDataType
{
    readonly int? _sessionId;
    readonly DateTime? _startTime;
    readonly DateTime? _endTime;
    readonly int? _duration;
    readonly string? _scanPhase;
    readonly int? _errorCount;
    readonly string? _startLsn;
    readonly string? _currentLsn;
    readonly string? _endLsn;
    readonly long? _tranCount;
    readonly string? _lastCommitLsn;
    readonly DateTime? _lastCommitTime;
    readonly long? _logRecordCount;
    readonly int? _schemaChangeCount;
    readonly long? _commandCount;
    readonly string? _firstBeginCdcLsn;
    readonly string? _lastCommitCdcLsn;
    readonly DateTime? _lastCommitCdcTime;
    readonly int? _latency;
    readonly int? _emptyScanCount;
    readonly int? _failedSessionsCount;

    public DmCdcLogScanSessionsDataType( )
    {
    }

    public DmCdcLogScanSessionsDataType(int? sessionId,
        DateTime? startTime,
        DateTime? endTime,
        int? duration,
        string? scanPhase,
        int? errorCount,
        string? startLsn,
        string? currentLsn,
        string? endLsn,
        long? tranCount,
        string? lastCommitLsn,
        DateTime? lastCommitTime,
        long? logRecordCount,
        int? schemaChangeCount,
        long? commandCount,
        string? firstBeginCdcLsn,
        string? lastCommitCdcLsn,
        DateTime? lastCommitCdcTime,
        int? latency,
        int? emptyScanCount,
        int? failedSessionsCount)
    {
        _sessionId = sessionId;
        _startTime = startTime;
        _endTime = endTime;
        _duration = duration;
        _scanPhase = scanPhase;
        _errorCount = errorCount;
        _startLsn = startLsn;
        _currentLsn = currentLsn;
        _endLsn = endLsn;
        _tranCount = tranCount;
        _lastCommitLsn = lastCommitLsn;
        _lastCommitTime = lastCommitTime;
        _logRecordCount = logRecordCount;
        _schemaChangeCount = schemaChangeCount;
        _commandCount = commandCount;
        _firstBeginCdcLsn = firstBeginCdcLsn;
        _lastCommitCdcLsn = lastCommitCdcLsn;
        _lastCommitCdcTime = lastCommitCdcTime;
        _latency = latency;
        _emptyScanCount = emptyScanCount;
        _failedSessionsCount = failedSessionsCount;
    }

    public int? SessionId => _sessionId;
    public DateTime? StartTime => _startTime;
    public DateTime? EndTime => _endTime;
    public int? Duration => _duration;
    public string? ScanPhase => _scanPhase;
    public int? ErrorCount => _errorCount;
    public string? StartLsn => _startLsn;
    public string? CurrentLsn => _currentLsn;
    public string? EndLsn => _endLsn;
    public long? TranCount => _tranCount;
    public string? LastCommitLsn => _lastCommitLsn;
    public DateTime? LastCommitTime => _lastCommitTime;
    public long? LogRecordCount => _logRecordCount;
    public int? SchemaChangeCount => _schemaChangeCount;
    public long? CommandCount => _commandCount;
    public string? FirstBeginCdcLsn => _firstBeginCdcLsn;
    public string? LastCommitCdcLsn => _lastCommitCdcLsn;
    public DateTime? LastCommitCdcTime => _lastCommitCdcTime;
    public int? Latency => _latency;
    public int? EmptyScanCount => _emptyScanCount;
    public int? FailedSessionsCount => _failedSessionsCount;
}

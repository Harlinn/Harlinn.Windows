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

public class DmExecRequestsDataType
{
    readonly short _sessionId = 0;
    readonly int _requestId = 0;
    readonly DateTime _startTime;
    readonly string _status = string.Empty;
    readonly string _command = string.Empty;
    readonly byte[]? _sqlHandle;
    readonly int? _statementStartOffset;
    readonly int? _statementEndOffset;
    readonly byte[]? _planHandle;
    readonly short _databaseId = 0;
    readonly int _userId = 0;
    readonly Guid? _connectionId;
    readonly short? _blockingSessionId;
    readonly string? _waitType;
    readonly int _waitTime = 0;
    readonly string _lastWaitType = string.Empty;
    readonly string _waitResource = string.Empty;
    readonly int _openTransactionCount = 0;
    readonly int _openResultsetCount = 0;
    readonly long _transactionId = 0;
    readonly byte[]? _contextInfo;
    readonly float _percentComplete = 0.0f;
    readonly long _estimatedCompletionTime = 0;
    readonly int _cpuTime = 0;
    readonly int _totalElapsedTime = 0;
    readonly int? _schedulerId;
    readonly byte[]? _taskAddress;
    readonly long _reads = 0;
    readonly long _writes = 0;
    readonly long _logicalReads = 0;
    readonly int _textSize = 0;
    readonly string? _language;
    readonly string? _dateFormat;
    readonly short _dateFirst = 0;
    readonly bool _quotedIdentifier = false;
    readonly bool _arithabort = false;
    readonly bool _ansiNullDfltOn = false;
    readonly bool _ansiDefaults = false;
    readonly bool _ansiWarnings = false;
    readonly bool _ansiPadding = false;
    readonly bool _ansiNulls = false;
    readonly bool _concatNullYieldsNull = false;
    readonly short _transactionIsolationLevel = 0;
    readonly int _lockTimeout = 0;
    readonly int _deadlockPriority = 0;
    readonly long _rowCount = 0;
    readonly int _prevError = 0;
    readonly int _nestLevel = 0;
    readonly int _grantedQueryMemory = 0;
    readonly bool _executingManagedCode = false;
    readonly int _groupId = 0;
    readonly byte[]? _queryHash;
    readonly byte[]? _queryPlanHash;
    readonly byte[]? _statementSqlHandle;
    readonly long? _statementContextId;
    readonly int _dop = 0;
    readonly int? _parallelWorkerCount;
    readonly Guid? _externalScriptRequestId;
    readonly bool _isResumable = false;
    readonly byte[]? _pageResource;
    readonly long _pageServerReads = 0;

    public DmExecRequestsDataType( )
    {
    }

    public DmExecRequestsDataType(short sessionId,
        int requestId,
        DateTime startTime,
        string status,
        string command,
        byte[]? sqlHandle,
        int? statementStartOffset,
        int? statementEndOffset,
        byte[]? planHandle,
        short databaseId,
        int userId,
        Guid? connectionId,
        short? blockingSessionId,
        string? waitType,
        int waitTime,
        string lastWaitType,
        string waitResource,
        int openTransactionCount,
        int openResultsetCount,
        long transactionId,
        byte[]? contextInfo,
        float percentComplete,
        long estimatedCompletionTime,
        int cpuTime,
        int totalElapsedTime,
        int? schedulerId,
        byte[]? taskAddress,
        long reads,
        long writes,
        long logicalReads,
        int textSize,
        string? language,
        string? dateFormat,
        short dateFirst,
        bool quotedIdentifier,
        bool arithabort,
        bool ansiNullDfltOn,
        bool ansiDefaults,
        bool ansiWarnings,
        bool ansiPadding,
        bool ansiNulls,
        bool concatNullYieldsNull,
        short transactionIsolationLevel,
        int lockTimeout,
        int deadlockPriority,
        long rowCount,
        int prevError,
        int nestLevel,
        int grantedQueryMemory,
        bool executingManagedCode,
        int groupId,
        byte[]? queryHash,
        byte[]? queryPlanHash,
        byte[]? statementSqlHandle,
        long? statementContextId,
        int dop,
        int? parallelWorkerCount,
        Guid? externalScriptRequestId,
        bool isResumable,
        byte[]? pageResource,
        long pageServerReads)
    {
        _sessionId = sessionId;
        _requestId = requestId;
        _startTime = startTime;
        _status = status;
        _command = command;
        _sqlHandle = sqlHandle;
        _statementStartOffset = statementStartOffset;
        _statementEndOffset = statementEndOffset;
        _planHandle = planHandle;
        _databaseId = databaseId;
        _userId = userId;
        _connectionId = connectionId;
        _blockingSessionId = blockingSessionId;
        _waitType = waitType;
        _waitTime = waitTime;
        _lastWaitType = lastWaitType;
        _waitResource = waitResource;
        _openTransactionCount = openTransactionCount;
        _openResultsetCount = openResultsetCount;
        _transactionId = transactionId;
        _contextInfo = contextInfo;
        _percentComplete = percentComplete;
        _estimatedCompletionTime = estimatedCompletionTime;
        _cpuTime = cpuTime;
        _totalElapsedTime = totalElapsedTime;
        _schedulerId = schedulerId;
        _taskAddress = taskAddress;
        _reads = reads;
        _writes = writes;
        _logicalReads = logicalReads;
        _textSize = textSize;
        _language = language;
        _dateFormat = dateFormat;
        _dateFirst = dateFirst;
        _quotedIdentifier = quotedIdentifier;
        _arithabort = arithabort;
        _ansiNullDfltOn = ansiNullDfltOn;
        _ansiDefaults = ansiDefaults;
        _ansiWarnings = ansiWarnings;
        _ansiPadding = ansiPadding;
        _ansiNulls = ansiNulls;
        _concatNullYieldsNull = concatNullYieldsNull;
        _transactionIsolationLevel = transactionIsolationLevel;
        _lockTimeout = lockTimeout;
        _deadlockPriority = deadlockPriority;
        _rowCount = rowCount;
        _prevError = prevError;
        _nestLevel = nestLevel;
        _grantedQueryMemory = grantedQueryMemory;
        _executingManagedCode = executingManagedCode;
        _groupId = groupId;
        _queryHash = queryHash;
        _queryPlanHash = queryPlanHash;
        _statementSqlHandle = statementSqlHandle;
        _statementContextId = statementContextId;
        _dop = dop;
        _parallelWorkerCount = parallelWorkerCount;
        _externalScriptRequestId = externalScriptRequestId;
        _isResumable = isResumable;
        _pageResource = pageResource;
        _pageServerReads = pageServerReads;
    }

    public short SessionId => _sessionId;
    public int RequestId => _requestId;
    public DateTime StartTime => _startTime;
    public string Status => _status;
    public string Command => _command;
    public byte[]? SqlHandle => _sqlHandle;
    public int? StatementStartOffset => _statementStartOffset;
    public int? StatementEndOffset => _statementEndOffset;
    public byte[]? PlanHandle => _planHandle;
    public short DatabaseId => _databaseId;
    public int UserId => _userId;
    public Guid? ConnectionId => _connectionId;
    public short? BlockingSessionId => _blockingSessionId;
    public string? WaitType => _waitType;
    public int WaitTime => _waitTime;
    public string LastWaitType => _lastWaitType;
    public string WaitResource => _waitResource;
    public int OpenTransactionCount => _openTransactionCount;
    public int OpenResultsetCount => _openResultsetCount;
    public long TransactionId => _transactionId;
    public byte[]? ContextInfo => _contextInfo;
    public float PercentComplete => _percentComplete;
    public long EstimatedCompletionTime => _estimatedCompletionTime;
    public int CpuTime => _cpuTime;
    public int TotalElapsedTime => _totalElapsedTime;
    public int? SchedulerId => _schedulerId;
    public byte[]? TaskAddress => _taskAddress;
    public long Reads => _reads;
    public long Writes => _writes;
    public long LogicalReads => _logicalReads;
    public int TextSize => _textSize;
    public string? Language => _language;
    public string? DateFormat => _dateFormat;
    public short DateFirst => _dateFirst;
    public bool QuotedIdentifier => _quotedIdentifier;
    public bool Arithabort => _arithabort;
    public bool AnsiNullDfltOn => _ansiNullDfltOn;
    public bool AnsiDefaults => _ansiDefaults;
    public bool AnsiWarnings => _ansiWarnings;
    public bool AnsiPadding => _ansiPadding;
    public bool AnsiNulls => _ansiNulls;
    public bool ConcatNullYieldsNull => _concatNullYieldsNull;
    public short TransactionIsolationLevel => _transactionIsolationLevel;
    public int LockTimeout => _lockTimeout;
    public int DeadlockPriority => _deadlockPriority;
    public long RowCount => _rowCount;
    public int PrevError => _prevError;
    public int NestLevel => _nestLevel;
    public int GrantedQueryMemory => _grantedQueryMemory;
    public bool ExecutingManagedCode => _executingManagedCode;
    public int GroupId => _groupId;
    public byte[]? QueryHash => _queryHash;
    public byte[]? QueryPlanHash => _queryPlanHash;
    public byte[]? StatementSqlHandle => _statementSqlHandle;
    public long? StatementContextId => _statementContextId;
    public int Dop => _dop;
    public int? ParallelWorkerCount => _parallelWorkerCount;
    public Guid? ExternalScriptRequestId => _externalScriptRequestId;
    public bool IsResumable => _isResumable;
    public byte[]? PageResource => _pageResource;
    public long PageServerReads => _pageServerReads;
}

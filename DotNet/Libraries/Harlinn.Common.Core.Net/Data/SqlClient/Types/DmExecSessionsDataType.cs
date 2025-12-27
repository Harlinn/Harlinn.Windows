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

public class DmExecSessionsDataType
{
    readonly short _sessionId = 0;
    readonly DateTime _loginTime;
    readonly string? _hostName;
    readonly string? _programName;
    readonly int? _hostProcessId;
    readonly int? _clientVersion;
    readonly string? _clientInterfaceName;
    readonly byte[] _securityId = Array.Empty<byte>();
    readonly string _loginName = string.Empty;
    readonly string? _ntDomain;
    readonly string? _ntUserName;
    readonly string _status = string.Empty;
    readonly byte[]? _contextInfo;
    readonly int _cpuTime = 0;
    readonly int _memoryUsage = 0;
    readonly int _totalScheduledTime = 0;
    readonly int _totalElapsedTime = 0;
    readonly int _endpointId = 0;
    readonly DateTime _lastRequestStartTime;
    readonly DateTime? _lastRequestEndTime;
    readonly long _reads = 0;
    readonly long _writes = 0;
    readonly long _logicalReads = 0;
    readonly bool _isUserProcess = false;
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
    readonly byte[] _originalSecurityId = Array.Empty<byte>();
    readonly string _originalLoginName = string.Empty;
    readonly DateTime? _lastSuccessfulLogon;
    readonly DateTime? _lastUnsuccessfulLogon;
    readonly long? _unsuccessfulLogons;
    readonly int _groupId = 0;
    readonly short _databaseId = 0;
    readonly int? _authenticatingDatabaseId;
    readonly int _openTransactionCount = 0;
    readonly long _pageServerReads = 0;

    public DmExecSessionsDataType( )
    {
    }

    public DmExecSessionsDataType(short sessionId,
        DateTime loginTime,
        string? hostName,
        string? programName,
        int? hostProcessId,
        int? clientVersion,
        string? clientInterfaceName,
        byte[] securityId,
        string loginName,
        string? ntDomain,
        string? ntUserName,
        string status,
        byte[]? contextInfo,
        int cpuTime,
        int memoryUsage,
        int totalScheduledTime,
        int totalElapsedTime,
        int endpointId,
        DateTime lastRequestStartTime,
        DateTime? lastRequestEndTime,
        long reads,
        long writes,
        long logicalReads,
        bool isUserProcess,
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
        byte[] originalSecurityId,
        string originalLoginName,
        DateTime? lastSuccessfulLogon,
        DateTime? lastUnsuccessfulLogon,
        long? unsuccessfulLogons,
        int groupId,
        short databaseId,
        int? authenticatingDatabaseId,
        int openTransactionCount,
        long pageServerReads)
    {
        _sessionId = sessionId;
        _loginTime = loginTime;
        _hostName = hostName;
        _programName = programName;
        _hostProcessId = hostProcessId;
        _clientVersion = clientVersion;
        _clientInterfaceName = clientInterfaceName;
        _securityId = securityId;
        _loginName = loginName;
        _ntDomain = ntDomain;
        _ntUserName = ntUserName;
        _status = status;
        _contextInfo = contextInfo;
        _cpuTime = cpuTime;
        _memoryUsage = memoryUsage;
        _totalScheduledTime = totalScheduledTime;
        _totalElapsedTime = totalElapsedTime;
        _endpointId = endpointId;
        _lastRequestStartTime = lastRequestStartTime;
        _lastRequestEndTime = lastRequestEndTime;
        _reads = reads;
        _writes = writes;
        _logicalReads = logicalReads;
        _isUserProcess = isUserProcess;
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
        _originalSecurityId = originalSecurityId;
        _originalLoginName = originalLoginName;
        _lastSuccessfulLogon = lastSuccessfulLogon;
        _lastUnsuccessfulLogon = lastUnsuccessfulLogon;
        _unsuccessfulLogons = unsuccessfulLogons;
        _groupId = groupId;
        _databaseId = databaseId;
        _authenticatingDatabaseId = authenticatingDatabaseId;
        _openTransactionCount = openTransactionCount;
        _pageServerReads = pageServerReads;
    }

    public short SessionId => _sessionId;
    public DateTime LoginTime => _loginTime;
    public string? HostName => _hostName;
    public string? ProgramName => _programName;
    public int? HostProcessId => _hostProcessId;
    public int? ClientVersion => _clientVersion;
    public string? ClientInterfaceName => _clientInterfaceName;
    public byte[] SecurityId => _securityId;
    public string LoginName => _loginName;
    public string? NtDomain => _ntDomain;
    public string? NtUserName => _ntUserName;
    public string Status => _status;
    public byte[]? ContextInfo => _contextInfo;
    public int CpuTime => _cpuTime;
    public int MemoryUsage => _memoryUsage;
    public int TotalScheduledTime => _totalScheduledTime;
    public int TotalElapsedTime => _totalElapsedTime;
    public int EndpointId => _endpointId;
    public DateTime LastRequestStartTime => _lastRequestStartTime;
    public DateTime? LastRequestEndTime => _lastRequestEndTime;
    public long Reads => _reads;
    public long Writes => _writes;
    public long LogicalReads => _logicalReads;
    public bool IsUserProcess => _isUserProcess;
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
    public byte[] OriginalSecurityId => _originalSecurityId;
    public string OriginalLoginName => _originalLoginName;
    public DateTime? LastSuccessfulLogon => _lastSuccessfulLogon;
    public DateTime? LastUnsuccessfulLogon => _lastUnsuccessfulLogon;
    public long? UnsuccessfulLogons => _unsuccessfulLogons;
    public int GroupId => _groupId;
    public short DatabaseId => _databaseId;
    public int? AuthenticatingDatabaseId => _authenticatingDatabaseId;
    public int OpenTransactionCount => _openTransactionCount;
    public long PageServerReads => _pageServerReads;
}

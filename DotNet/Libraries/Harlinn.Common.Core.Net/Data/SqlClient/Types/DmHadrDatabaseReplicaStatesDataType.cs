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

public class DmHadrDatabaseReplicaStatesDataType
{
    readonly int _databaseId = 0;
    readonly Guid _groupId;
    readonly Guid _replicaId;
    readonly Guid _groupDatabaseId;
    readonly bool? _isLocal;
    readonly bool? _isPrimaryReplica;
    readonly byte? _synchronizationState;
    readonly string? _synchronizationStateDesc;
    readonly bool? _isCommitParticipant;
    readonly byte? _synchronizationHealth;
    readonly string? _synchronizationHealthDesc;
    readonly byte? _databaseState;
    readonly string? _databaseStateDesc;
    readonly bool? _isSuspended;
    readonly byte? _suspendReason;
    readonly string? _suspendReasonDesc;
    readonly object? _recoveryLsn;
    readonly object? _truncationLsn;
    readonly object? _lastSentLsn;
    readonly DateTime? _lastSentTime;
    readonly object? _lastReceivedLsn;
    readonly DateTime? _lastReceivedTime;
    readonly object? _lastHardenedLsn;
    readonly DateTime? _lastHardenedTime;
    readonly object? _lastRedoneLsn;
    readonly DateTime? _lastRedoneTime;
    readonly long? _logSendQueueSize;
    readonly long? _logSendRate;
    readonly long? _redoQueueSize;
    readonly long? _redoRate;
    readonly long? _filestreamSendRate;
    readonly object? _endOfLogLsn;
    readonly object? _lastCommitLsn;
    readonly DateTime? _lastCommitTime;
    readonly long? _lowWaterMarkForGhosts;
    readonly long? _secondaryLagSeconds;
    readonly object? _quorumCommitLsn;
    readonly DateTime? _quorumCommitTime;

    public DmHadrDatabaseReplicaStatesDataType( )
    {
    }

    public DmHadrDatabaseReplicaStatesDataType(int databaseId,
        Guid groupId,
        Guid replicaId,
        Guid groupDatabaseId,
        bool? isLocal,
        bool? isPrimaryReplica,
        byte? synchronizationState,
        string? synchronizationStateDesc,
        bool? isCommitParticipant,
        byte? synchronizationHealth,
        string? synchronizationHealthDesc,
        byte? databaseState,
        string? databaseStateDesc,
        bool? isSuspended,
        byte? suspendReason,
        string? suspendReasonDesc,
        object? recoveryLsn,
        object? truncationLsn,
        object? lastSentLsn,
        DateTime? lastSentTime,
        object? lastReceivedLsn,
        DateTime? lastReceivedTime,
        object? lastHardenedLsn,
        DateTime? lastHardenedTime,
        object? lastRedoneLsn,
        DateTime? lastRedoneTime,
        long? logSendQueueSize,
        long? logSendRate,
        long? redoQueueSize,
        long? redoRate,
        long? filestreamSendRate,
        object? endOfLogLsn,
        object? lastCommitLsn,
        DateTime? lastCommitTime,
        long? lowWaterMarkForGhosts,
        long? secondaryLagSeconds,
        object? quorumCommitLsn,
        DateTime? quorumCommitTime)
    {
        _databaseId = databaseId;
        _groupId = groupId;
        _replicaId = replicaId;
        _groupDatabaseId = groupDatabaseId;
        _isLocal = isLocal;
        _isPrimaryReplica = isPrimaryReplica;
        _synchronizationState = synchronizationState;
        _synchronizationStateDesc = synchronizationStateDesc;
        _isCommitParticipant = isCommitParticipant;
        _synchronizationHealth = synchronizationHealth;
        _synchronizationHealthDesc = synchronizationHealthDesc;
        _databaseState = databaseState;
        _databaseStateDesc = databaseStateDesc;
        _isSuspended = isSuspended;
        _suspendReason = suspendReason;
        _suspendReasonDesc = suspendReasonDesc;
        _recoveryLsn = recoveryLsn;
        _truncationLsn = truncationLsn;
        _lastSentLsn = lastSentLsn;
        _lastSentTime = lastSentTime;
        _lastReceivedLsn = lastReceivedLsn;
        _lastReceivedTime = lastReceivedTime;
        _lastHardenedLsn = lastHardenedLsn;
        _lastHardenedTime = lastHardenedTime;
        _lastRedoneLsn = lastRedoneLsn;
        _lastRedoneTime = lastRedoneTime;
        _logSendQueueSize = logSendQueueSize;
        _logSendRate = logSendRate;
        _redoQueueSize = redoQueueSize;
        _redoRate = redoRate;
        _filestreamSendRate = filestreamSendRate;
        _endOfLogLsn = endOfLogLsn;
        _lastCommitLsn = lastCommitLsn;
        _lastCommitTime = lastCommitTime;
        _lowWaterMarkForGhosts = lowWaterMarkForGhosts;
        _secondaryLagSeconds = secondaryLagSeconds;
        _quorumCommitLsn = quorumCommitLsn;
        _quorumCommitTime = quorumCommitTime;
    }

    public int DatabaseId => _databaseId;
    public Guid GroupId => _groupId;
    public Guid ReplicaId => _replicaId;
    public Guid GroupDatabaseId => _groupDatabaseId;
    public bool? IsLocal => _isLocal;
    public bool? IsPrimaryReplica => _isPrimaryReplica;
    public byte? SynchronizationState => _synchronizationState;
    public string? SynchronizationStateDesc => _synchronizationStateDesc;
    public bool? IsCommitParticipant => _isCommitParticipant;
    public byte? SynchronizationHealth => _synchronizationHealth;
    public string? SynchronizationHealthDesc => _synchronizationHealthDesc;
    public byte? DatabaseState => _databaseState;
    public string? DatabaseStateDesc => _databaseStateDesc;
    public bool? IsSuspended => _isSuspended;
    public byte? SuspendReason => _suspendReason;
    public string? SuspendReasonDesc => _suspendReasonDesc;
    public object? RecoveryLsn => _recoveryLsn;
    public object? TruncationLsn => _truncationLsn;
    public object? LastSentLsn => _lastSentLsn;
    public DateTime? LastSentTime => _lastSentTime;
    public object? LastReceivedLsn => _lastReceivedLsn;
    public DateTime? LastReceivedTime => _lastReceivedTime;
    public object? LastHardenedLsn => _lastHardenedLsn;
    public DateTime? LastHardenedTime => _lastHardenedTime;
    public object? LastRedoneLsn => _lastRedoneLsn;
    public DateTime? LastRedoneTime => _lastRedoneTime;
    public long? LogSendQueueSize => _logSendQueueSize;
    public long? LogSendRate => _logSendRate;
    public long? RedoQueueSize => _redoQueueSize;
    public long? RedoRate => _redoRate;
    public long? FilestreamSendRate => _filestreamSendRate;
    public object? EndOfLogLsn => _endOfLogLsn;
    public object? LastCommitLsn => _lastCommitLsn;
    public DateTime? LastCommitTime => _lastCommitTime;
    public long? LowWaterMarkForGhosts => _lowWaterMarkForGhosts;
    public long? SecondaryLagSeconds => _secondaryLagSeconds;
    public object? QuorumCommitLsn => _quorumCommitLsn;
    public DateTime? QuorumCommitTime => _quorumCommitTime;
}

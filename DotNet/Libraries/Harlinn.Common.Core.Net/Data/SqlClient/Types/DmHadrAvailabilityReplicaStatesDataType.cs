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

public class DmHadrAvailabilityReplicaStatesDataType
{
    readonly Guid _replicaId;
    readonly Guid _groupId;
    readonly bool _isLocal = false;
    readonly byte? _role;
    readonly string? _roleDesc;
    readonly byte? _operationalState;
    readonly string? _operationalStateDesc;
    readonly byte? _connectedState;
    readonly string? _connectedStateDesc;
    readonly byte? _recoveryHealth;
    readonly string? _recoveryHealthDesc;
    readonly byte? _synchronizationHealth;
    readonly string? _synchronizationHealthDesc;
    readonly int? _lastConnectErrorNumber;
    readonly string? _lastConnectErrorDescription;
    readonly DateTime? _lastConnectErrorTimestamp;
    readonly long? _writeLeaseRemainingTicks;
    readonly DateTime? _currentConfigurationCommitStartTimeUtc;

    public DmHadrAvailabilityReplicaStatesDataType( )
    {
    }

    public DmHadrAvailabilityReplicaStatesDataType(Guid replicaId,
        Guid groupId,
        bool isLocal,
        byte? role,
        string? roleDesc,
        byte? operationalState,
        string? operationalStateDesc,
        byte? connectedState,
        string? connectedStateDesc,
        byte? recoveryHealth,
        string? recoveryHealthDesc,
        byte? synchronizationHealth,
        string? synchronizationHealthDesc,
        int? lastConnectErrorNumber,
        string? lastConnectErrorDescription,
        DateTime? lastConnectErrorTimestamp,
        long? writeLeaseRemainingTicks,
        DateTime? currentConfigurationCommitStartTimeUtc)
    {
        _replicaId = replicaId;
        _groupId = groupId;
        _isLocal = isLocal;
        _role = role;
        _roleDesc = roleDesc;
        _operationalState = operationalState;
        _operationalStateDesc = operationalStateDesc;
        _connectedState = connectedState;
        _connectedStateDesc = connectedStateDesc;
        _recoveryHealth = recoveryHealth;
        _recoveryHealthDesc = recoveryHealthDesc;
        _synchronizationHealth = synchronizationHealth;
        _synchronizationHealthDesc = synchronizationHealthDesc;
        _lastConnectErrorNumber = lastConnectErrorNumber;
        _lastConnectErrorDescription = lastConnectErrorDescription;
        _lastConnectErrorTimestamp = lastConnectErrorTimestamp;
        _writeLeaseRemainingTicks = writeLeaseRemainingTicks;
        _currentConfigurationCommitStartTimeUtc = currentConfigurationCommitStartTimeUtc;
    }

    public Guid ReplicaId => _replicaId;
    public Guid GroupId => _groupId;
    public bool IsLocal => _isLocal;
    public byte? Role => _role;
    public string? RoleDesc => _roleDesc;
    public byte? OperationalState => _operationalState;
    public string? OperationalStateDesc => _operationalStateDesc;
    public byte? ConnectedState => _connectedState;
    public string? ConnectedStateDesc => _connectedStateDesc;
    public byte? RecoveryHealth => _recoveryHealth;
    public string? RecoveryHealthDesc => _recoveryHealthDesc;
    public byte? SynchronizationHealth => _synchronizationHealth;
    public string? SynchronizationHealthDesc => _synchronizationHealthDesc;
    public int? LastConnectErrorNumber => _lastConnectErrorNumber;
    public string? LastConnectErrorDescription => _lastConnectErrorDescription;
    public DateTime? LastConnectErrorTimestamp => _lastConnectErrorTimestamp;
    public long? WriteLeaseRemainingTicks => _writeLeaseRemainingTicks;
    public DateTime? CurrentConfigurationCommitStartTimeUtc => _currentConfigurationCommitStartTimeUtc;
}

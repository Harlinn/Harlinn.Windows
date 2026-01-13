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

public class AvailabilityReplicasDataType
{
    readonly Guid? _replicaId;
    readonly Guid? _groupId;
    readonly int? _replicaMetadataId;
    readonly string? _replicaServerName;
    readonly byte[]? _ownerSid;
    readonly string? _endpointUrl;
    readonly byte? _availabilityMode;
    readonly string? _availabilityModeDesc;
    readonly byte? _failoverMode;
    readonly string? _failoverModeDesc;
    readonly int? _sessionTimeout;
    readonly byte? _primaryRoleAllowConnections;
    readonly string? _primaryRoleAllowConnectionsDesc;
    readonly byte? _secondaryRoleAllowConnections;
    readonly string? _secondaryRoleAllowConnectionsDesc;
    readonly DateTime? _createDate;
    readonly DateTime? _modifyDate;
    readonly int? _backupPriority;
    readonly string? _readOnlyRoutingUrl;
    readonly byte? _seedingMode;
    readonly string? _seedingModeDesc;
    readonly string? _readWriteRoutingUrl;

    public AvailabilityReplicasDataType( )
    {
    }

    public AvailabilityReplicasDataType(Guid? replicaId,
        Guid? groupId,
        int? replicaMetadataId,
        string? replicaServerName,
        byte[]? ownerSid,
        string? endpointUrl,
        byte? availabilityMode,
        string? availabilityModeDesc,
        byte? failoverMode,
        string? failoverModeDesc,
        int? sessionTimeout,
        byte? primaryRoleAllowConnections,
        string? primaryRoleAllowConnectionsDesc,
        byte? secondaryRoleAllowConnections,
        string? secondaryRoleAllowConnectionsDesc,
        DateTime? createDate,
        DateTime? modifyDate,
        int? backupPriority,
        string? readOnlyRoutingUrl,
        byte? seedingMode,
        string? seedingModeDesc,
        string? readWriteRoutingUrl)
    {
        _replicaId = replicaId;
        _groupId = groupId;
        _replicaMetadataId = replicaMetadataId;
        _replicaServerName = replicaServerName;
        _ownerSid = ownerSid;
        _endpointUrl = endpointUrl;
        _availabilityMode = availabilityMode;
        _availabilityModeDesc = availabilityModeDesc;
        _failoverMode = failoverMode;
        _failoverModeDesc = failoverModeDesc;
        _sessionTimeout = sessionTimeout;
        _primaryRoleAllowConnections = primaryRoleAllowConnections;
        _primaryRoleAllowConnectionsDesc = primaryRoleAllowConnectionsDesc;
        _secondaryRoleAllowConnections = secondaryRoleAllowConnections;
        _secondaryRoleAllowConnectionsDesc = secondaryRoleAllowConnectionsDesc;
        _createDate = createDate;
        _modifyDate = modifyDate;
        _backupPriority = backupPriority;
        _readOnlyRoutingUrl = readOnlyRoutingUrl;
        _seedingMode = seedingMode;
        _seedingModeDesc = seedingModeDesc;
        _readWriteRoutingUrl = readWriteRoutingUrl;
    }

    public Guid? ReplicaId => _replicaId;
    public Guid? GroupId => _groupId;
    public int? ReplicaMetadataId => _replicaMetadataId;
    public string? ReplicaServerName => _replicaServerName;
    public byte[]? OwnerSid => _ownerSid;
    public string? EndpointUrl => _endpointUrl;
    public byte? AvailabilityMode => _availabilityMode;
    public string? AvailabilityModeDesc => _availabilityModeDesc;
    public byte? FailoverMode => _failoverMode;
    public string? FailoverModeDesc => _failoverModeDesc;
    public int? SessionTimeout => _sessionTimeout;
    public byte? PrimaryRoleAllowConnections => _primaryRoleAllowConnections;
    public string? PrimaryRoleAllowConnectionsDesc => _primaryRoleAllowConnectionsDesc;
    public byte? SecondaryRoleAllowConnections => _secondaryRoleAllowConnections;
    public string? SecondaryRoleAllowConnectionsDesc => _secondaryRoleAllowConnectionsDesc;
    public DateTime? CreateDate => _createDate;
    public DateTime? ModifyDate => _modifyDate;
    public int? BackupPriority => _backupPriority;
    public string? ReadOnlyRoutingUrl => _readOnlyRoutingUrl;
    public byte? SeedingMode => _seedingMode;
    public string? SeedingModeDesc => _seedingModeDesc;
    public string? ReadWriteRoutingUrl => _readWriteRoutingUrl;
}

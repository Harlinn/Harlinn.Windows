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

public class DmHadrAvailabilityReplicaClusterStatesDataType
{
    readonly Guid _replicaId;
    readonly string _replicaServerName = string.Empty;
    readonly Guid _groupId;
    readonly byte _joinState = 0;
    readonly string? _joinStateDesc;

    public DmHadrAvailabilityReplicaClusterStatesDataType( )
    {
    }

    public DmHadrAvailabilityReplicaClusterStatesDataType(Guid replicaId,
        string replicaServerName,
        Guid groupId,
        byte joinState,
        string? joinStateDesc)
    {
        _replicaId = replicaId;
        _replicaServerName = replicaServerName;
        _groupId = groupId;
        _joinState = joinState;
        _joinStateDesc = joinStateDesc;
    }

    public Guid ReplicaId => _replicaId;
    public string ReplicaServerName => _replicaServerName;
    public Guid GroupId => _groupId;
    public byte JoinState => _joinState;
    public string? JoinStateDesc => _joinStateDesc;
}

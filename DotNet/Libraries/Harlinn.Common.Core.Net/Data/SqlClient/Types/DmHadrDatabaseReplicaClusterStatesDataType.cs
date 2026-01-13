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

public class DmHadrDatabaseReplicaClusterStatesDataType
{
    readonly Guid _replicaId;
    readonly Guid _groupDatabaseId;
    readonly string? _databaseName;
    readonly bool _isFailoverReady = false;
    readonly bool _isPendingSecondarySuspend = false;
    readonly bool _isDatabaseJoined = false;
    readonly object? _recoveryLsn;
    readonly object? _truncationLsn;

    public DmHadrDatabaseReplicaClusterStatesDataType( )
    {
    }

    public DmHadrDatabaseReplicaClusterStatesDataType(Guid replicaId,
        Guid groupDatabaseId,
        string? databaseName,
        bool isFailoverReady,
        bool isPendingSecondarySuspend,
        bool isDatabaseJoined,
        object? recoveryLsn,
        object? truncationLsn)
    {
        _replicaId = replicaId;
        _groupDatabaseId = groupDatabaseId;
        _databaseName = databaseName;
        _isFailoverReady = isFailoverReady;
        _isPendingSecondarySuspend = isPendingSecondarySuspend;
        _isDatabaseJoined = isDatabaseJoined;
        _recoveryLsn = recoveryLsn;
        _truncationLsn = truncationLsn;
    }

    public Guid ReplicaId => _replicaId;
    public Guid GroupDatabaseId => _groupDatabaseId;
    public string? DatabaseName => _databaseName;
    public bool IsFailoverReady => _isFailoverReady;
    public bool IsPendingSecondarySuspend => _isPendingSecondarySuspend;
    public bool IsDatabaseJoined => _isDatabaseJoined;
    public object? RecoveryLsn => _recoveryLsn;
    public object? TruncationLsn => _truncationLsn;
}

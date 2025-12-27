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
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers;

public class DmHadrDatabaseReplicaClusterStatesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_database_replica_cluster_states]";
    public const string TableName = "dm_hadr_database_replica_cluster_states";
    public const string ShortName = "dhdrcs";
    public const string Sql = """
        SELECT
          dhdrcs.[replica_id],
          dhdrcs.[group_database_id],
          dhdrcs.[database_name],
          dhdrcs.[is_failover_ready],
          dhdrcs.[is_pending_secondary_suspend],
          dhdrcs.[is_database_joined],
          dhdrcs.[recovery_lsn],
          dhdrcs.[truncation_lsn]
        FROM
          [sys].[dm_hadr_database_replica_cluster_states] dhdrcs
        """;

    public const int REPLICAID_FIELD_ID = 0;
    public const int GROUPDATABASEID_FIELD_ID = 1;
    public const int DATABASENAME_FIELD_ID = 2;
    public const int ISFAILOVERREADY_FIELD_ID = 3;
    public const int ISPENDINGSECONDARYSUSPEND_FIELD_ID = 4;
    public const int ISDATABASEJOINED_FIELD_ID = 5;
    public const int RECOVERYLSN_FIELD_ID = 6;
    public const int TRUNCATIONLSN_FIELD_ID = 7;


    public DmHadrDatabaseReplicaClusterStatesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrDatabaseReplicaClusterStatesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrDatabaseReplicaClusterStatesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid ReplicaId
    {
        get
        {
            return base.GetGuid(REPLICAID_FIELD_ID);
        }
    }

    public Guid GroupDatabaseId
    {
        get
        {
            return base.GetGuid(GROUPDATABASEID_FIELD_ID);
        }
    }

    public string? DatabaseName
    {
        get
        {
            return base.GetNullableString(DATABASENAME_FIELD_ID);
        }
    }

    public bool IsFailoverReady
    {
        get
        {
            return base.GetBoolean(ISFAILOVERREADY_FIELD_ID);
        }
    }

    public bool IsPendingSecondarySuspend
    {
        get
        {
            return base.GetBoolean(ISPENDINGSECONDARYSUSPEND_FIELD_ID);
        }
    }

    public bool IsDatabaseJoined
    {
        get
        {
            return base.GetBoolean(ISDATABASEJOINED_FIELD_ID);
        }
    }

    public decimal? RecoveryLsn
    {
        get
        {
            return base.GetNullableDecimal(RECOVERYLSN_FIELD_ID);
        }
    }

    public decimal? TruncationLsn
    {
        get
        {
            return base.GetNullableDecimal(TRUNCATIONLSN_FIELD_ID);
        }
    }


    public Types.DmHadrDatabaseReplicaClusterStatesDataType ToDataObject()
    {
        return new Types.DmHadrDatabaseReplicaClusterStatesDataType(ReplicaId,
            GroupDatabaseId,
            DatabaseName,
            IsFailoverReady,
            IsPendingSecondarySuspend,
            IsDatabaseJoined,
            RecoveryLsn,
            TruncationLsn);
    }

    public List<Types.DmHadrDatabaseReplicaClusterStatesDataType> ToList()
    {
        var list = new List<Types.DmHadrDatabaseReplicaClusterStatesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

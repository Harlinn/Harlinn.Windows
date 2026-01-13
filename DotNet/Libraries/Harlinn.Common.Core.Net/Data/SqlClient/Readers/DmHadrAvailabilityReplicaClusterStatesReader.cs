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
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers;

public class DmHadrAvailabilityReplicaClusterStatesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_availability_replica_cluster_states]";
    public const string TableName = "dm_hadr_availability_replica_cluster_states";
    public const string ShortName = "dharcs";
    public const string Sql = """
        SELECT
          dharcs.[replica_id],
          dharcs.[replica_server_name],
          dharcs.[group_id],
          dharcs.[join_state],
          dharcs.[join_state_desc]
        FROM
          [sys].[dm_hadr_availability_replica_cluster_states] dharcs
        """;

    public const int REPLICAID_FIELD_ID = 0;
    public const int REPLICASERVERNAME_FIELD_ID = 1;
    public const int GROUPID_FIELD_ID = 2;
    public const int JOINSTATE_FIELD_ID = 3;
    public const int JOINSTATEDESC_FIELD_ID = 4;


    public DmHadrAvailabilityReplicaClusterStatesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrAvailabilityReplicaClusterStatesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrAvailabilityReplicaClusterStatesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public string ReplicaServerName
    {
        get
        {
            return base.GetString(REPLICASERVERNAME_FIELD_ID);
        }
    }

    public Guid GroupId
    {
        get
        {
            return base.GetGuid(GROUPID_FIELD_ID);
        }
    }

    public byte JoinState
    {
        get
        {
            return base.GetByte(JOINSTATE_FIELD_ID);
        }
    }

    public string? JoinStateDesc
    {
        get
        {
            return base.GetNullableString(JOINSTATEDESC_FIELD_ID);
        }
    }


    public Types.DmHadrAvailabilityReplicaClusterStatesDataType ToDataObject()
    {
        return new Types.DmHadrAvailabilityReplicaClusterStatesDataType(ReplicaId,
            ReplicaServerName,
            GroupId,
            JoinState,
            JoinStateDesc);
    }

    public List<Types.DmHadrAvailabilityReplicaClusterStatesDataType> ToList()
    {
        var list = new List<Types.DmHadrAvailabilityReplicaClusterStatesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class AvailabilityReadOnlyRoutingListsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[availability_read_only_routing_lists]";
    public const string TableName = "availability_read_only_routing_lists";
    public const string ShortName = "arorl";
    public const string Sql = """
        SELECT
          arorl.[replica_id],
          arorl.[routing_priority],
          arorl.[read_only_replica_id]
        FROM
          [sys].[availability_read_only_routing_lists] arorl
        """;

    public const int REPLICAID_FIELD_ID = 0;
    public const int ROUTINGPRIORITY_FIELD_ID = 1;
    public const int READONLYREPLICAID_FIELD_ID = 2;


    public AvailabilityReadOnlyRoutingListsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AvailabilityReadOnlyRoutingListsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AvailabilityReadOnlyRoutingListsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int RoutingPriority
    {
        get
        {
            return base.GetInt32(ROUTINGPRIORITY_FIELD_ID);
        }
    }

    public Guid ReadOnlyReplicaId
    {
        get
        {
            return base.GetGuid(READONLYREPLICAID_FIELD_ID);
        }
    }


    public Types.AvailabilityReadOnlyRoutingListsDataType ToDataObject()
    {
        return new Types.AvailabilityReadOnlyRoutingListsDataType(ReplicaId,
            RoutingPriority,
            ReadOnlyReplicaId);
    }

    public List<Types.AvailabilityReadOnlyRoutingListsDataType> ToList()
    {
        var list = new List<Types.AvailabilityReadOnlyRoutingListsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

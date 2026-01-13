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

public class AvailabilityReplicasReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[availability_replicas]";
    public const string TableName = "availability_replicas";
    public const string ShortName = "ar";
    public const string Sql = """
        SELECT
          ar.[replica_id],
          ar.[group_id],
          ar.[replica_metadata_id],
          ar.[replica_server_name],
          ar.[owner_sid],
          ar.[endpoint_url],
          ar.[availability_mode],
          ar.[availability_mode_desc],
          ar.[failover_mode],
          ar.[failover_mode_desc],
          ar.[session_timeout],
          ar.[primary_role_allow_connections],
          ar.[primary_role_allow_connections_desc],
          ar.[secondary_role_allow_connections],
          ar.[secondary_role_allow_connections_desc],
          ar.[create_date],
          ar.[modify_date],
          ar.[backup_priority],
          ar.[read_only_routing_url],
          ar.[seeding_mode],
          ar.[seeding_mode_desc],
          ar.[read_write_routing_url]
        FROM
          [sys].[availability_replicas] ar
        """;

    public const int REPLICAID_FIELD_ID = 0;
    public const int GROUPID_FIELD_ID = 1;
    public const int REPLICAMETADATAID_FIELD_ID = 2;
    public const int REPLICASERVERNAME_FIELD_ID = 3;
    public const int OWNERSID_FIELD_ID = 4;
    public const int ENDPOINTURL_FIELD_ID = 5;
    public const int AVAILABILITYMODE_FIELD_ID = 6;
    public const int AVAILABILITYMODEDESC_FIELD_ID = 7;
    public const int FAILOVERMODE_FIELD_ID = 8;
    public const int FAILOVERMODEDESC_FIELD_ID = 9;
    public const int SESSIONTIMEOUT_FIELD_ID = 10;
    public const int PRIMARYROLEALLOWCONNECTIONS_FIELD_ID = 11;
    public const int PRIMARYROLEALLOWCONNECTIONSDESC_FIELD_ID = 12;
    public const int SECONDARYROLEALLOWCONNECTIONS_FIELD_ID = 13;
    public const int SECONDARYROLEALLOWCONNECTIONSDESC_FIELD_ID = 14;
    public const int CREATEDATE_FIELD_ID = 15;
    public const int MODIFYDATE_FIELD_ID = 16;
    public const int BACKUPPRIORITY_FIELD_ID = 17;
    public const int READONLYROUTINGURL_FIELD_ID = 18;
    public const int SEEDINGMODE_FIELD_ID = 19;
    public const int SEEDINGMODEDESC_FIELD_ID = 20;
    public const int READWRITEROUTINGURL_FIELD_ID = 21;


    public AvailabilityReplicasReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AvailabilityReplicasReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AvailabilityReplicasReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid? ReplicaId
    {
        get
        {
            return base.GetNullableGuid(REPLICAID_FIELD_ID);
        }
    }

    public Guid? GroupId
    {
        get
        {
            return base.GetNullableGuid(GROUPID_FIELD_ID);
        }
    }

    public int? ReplicaMetadataId
    {
        get
        {
            return base.GetNullableInt32(REPLICAMETADATAID_FIELD_ID);
        }
    }

    public string? ReplicaServerName
    {
        get
        {
            return base.GetNullableString(REPLICASERVERNAME_FIELD_ID);
        }
    }

    public byte[]? OwnerSid
    {
        get
        {
            return base.GetNullableBinary(OWNERSID_FIELD_ID);
        }
    }

    public string? EndpointUrl
    {
        get
        {
            return base.GetNullableString(ENDPOINTURL_FIELD_ID);
        }
    }

    public byte? AvailabilityMode
    {
        get
        {
            return base.GetNullableByte(AVAILABILITYMODE_FIELD_ID);
        }
    }

    public string? AvailabilityModeDesc
    {
        get
        {
            return base.GetNullableString(AVAILABILITYMODEDESC_FIELD_ID);
        }
    }

    public byte? FailoverMode
    {
        get
        {
            return base.GetNullableByte(FAILOVERMODE_FIELD_ID);
        }
    }

    public string? FailoverModeDesc
    {
        get
        {
            return base.GetNullableString(FAILOVERMODEDESC_FIELD_ID);
        }
    }

    public int? SessionTimeout
    {
        get
        {
            return base.GetNullableInt32(SESSIONTIMEOUT_FIELD_ID);
        }
    }

    public byte? PrimaryRoleAllowConnections
    {
        get
        {
            return base.GetNullableByte(PRIMARYROLEALLOWCONNECTIONS_FIELD_ID);
        }
    }

    public string? PrimaryRoleAllowConnectionsDesc
    {
        get
        {
            return base.GetNullableString(PRIMARYROLEALLOWCONNECTIONSDESC_FIELD_ID);
        }
    }

    public byte? SecondaryRoleAllowConnections
    {
        get
        {
            return base.GetNullableByte(SECONDARYROLEALLOWCONNECTIONS_FIELD_ID);
        }
    }

    public string? SecondaryRoleAllowConnectionsDesc
    {
        get
        {
            return base.GetNullableString(SECONDARYROLEALLOWCONNECTIONSDESC_FIELD_ID);
        }
    }

    public DateTime? CreateDate
    {
        get
        {
            return base.GetNullableDateTime(CREATEDATE_FIELD_ID);
        }
    }

    public DateTime? ModifyDate
    {
        get
        {
            return base.GetNullableDateTime(MODIFYDATE_FIELD_ID);
        }
    }

    public int? BackupPriority
    {
        get
        {
            return base.GetNullableInt32(BACKUPPRIORITY_FIELD_ID);
        }
    }

    public string? ReadOnlyRoutingUrl
    {
        get
        {
            return base.GetNullableString(READONLYROUTINGURL_FIELD_ID);
        }
    }

    public byte? SeedingMode
    {
        get
        {
            return base.GetNullableByte(SEEDINGMODE_FIELD_ID);
        }
    }

    public string? SeedingModeDesc
    {
        get
        {
            return base.GetNullableString(SEEDINGMODEDESC_FIELD_ID);
        }
    }

    public string? ReadWriteRoutingUrl
    {
        get
        {
            return base.GetNullableString(READWRITEROUTINGURL_FIELD_ID);
        }
    }


    public Types.AvailabilityReplicasDataType ToDataObject()
    {
        return new Types.AvailabilityReplicasDataType(ReplicaId,
            GroupId,
            ReplicaMetadataId,
            ReplicaServerName,
            OwnerSid,
            EndpointUrl,
            AvailabilityMode,
            AvailabilityModeDesc,
            FailoverMode,
            FailoverModeDesc,
            SessionTimeout,
            PrimaryRoleAllowConnections,
            PrimaryRoleAllowConnectionsDesc,
            SecondaryRoleAllowConnections,
            SecondaryRoleAllowConnectionsDesc,
            CreateDate,
            ModifyDate,
            BackupPriority,
            ReadOnlyRoutingUrl,
            SeedingMode,
            SeedingModeDesc,
            ReadWriteRoutingUrl);
    }

    public List<Types.AvailabilityReplicasDataType> ToList()
    {
        var list = new List<Types.AvailabilityReplicasDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

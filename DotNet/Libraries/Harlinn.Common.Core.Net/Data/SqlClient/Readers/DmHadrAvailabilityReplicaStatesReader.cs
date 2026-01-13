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

public class DmHadrAvailabilityReplicaStatesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_availability_replica_states]";
    public const string TableName = "dm_hadr_availability_replica_states";
    public const string ShortName = "dhars";
    public const string Sql = """
        SELECT
          dhars.[replica_id],
          dhars.[group_id],
          dhars.[is_local],
          dhars.[Role],
          dhars.[role_desc],
          dhars.[operational_state],
          dhars.[operational_state_desc],
          dhars.[connected_state],
          dhars.[connected_state_desc],
          dhars.[recovery_health],
          dhars.[recovery_health_desc],
          dhars.[synchronization_health],
          dhars.[synchronization_health_desc],
          dhars.[last_connect_error_number],
          dhars.[last_connect_error_description],
          dhars.[last_connect_error_timestamp],
          dhars.[write_lease_remaining_ticks],
          dhars.[current_configuration_commit_start_time_utc]
        FROM
          [sys].[dm_hadr_availability_replica_states] dhars
        """;

    public const int REPLICAID_FIELD_ID = 0;
    public const int GROUPID_FIELD_ID = 1;
    public const int ISLOCAL_FIELD_ID = 2;
    public const int ROLE_FIELD_ID = 3;
    public const int ROLEDESC_FIELD_ID = 4;
    public const int OPERATIONALSTATE_FIELD_ID = 5;
    public const int OPERATIONALSTATEDESC_FIELD_ID = 6;
    public const int CONNECTEDSTATE_FIELD_ID = 7;
    public const int CONNECTEDSTATEDESC_FIELD_ID = 8;
    public const int RECOVERYHEALTH_FIELD_ID = 9;
    public const int RECOVERYHEALTHDESC_FIELD_ID = 10;
    public const int SYNCHRONIZATIONHEALTH_FIELD_ID = 11;
    public const int SYNCHRONIZATIONHEALTHDESC_FIELD_ID = 12;
    public const int LASTCONNECTERRORNUMBER_FIELD_ID = 13;
    public const int LASTCONNECTERRORDESCRIPTION_FIELD_ID = 14;
    public const int LASTCONNECTERRORTIMESTAMP_FIELD_ID = 15;
    public const int WRITELEASEREMAININGTICKS_FIELD_ID = 16;
    public const int CURRENTCONFIGURATIONCOMMITSTARTTIMEUTC_FIELD_ID = 17;


    public DmHadrAvailabilityReplicaStatesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrAvailabilityReplicaStatesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrAvailabilityReplicaStatesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public Guid GroupId
    {
        get
        {
            return base.GetGuid(GROUPID_FIELD_ID);
        }
    }

    public bool IsLocal
    {
        get
        {
            return base.GetBoolean(ISLOCAL_FIELD_ID);
        }
    }

    public byte? Role
    {
        get
        {
            return base.GetNullableByte(ROLE_FIELD_ID);
        }
    }

    public string? RoleDesc
    {
        get
        {
            return base.GetNullableString(ROLEDESC_FIELD_ID);
        }
    }

    public byte? OperationalState
    {
        get
        {
            return base.GetNullableByte(OPERATIONALSTATE_FIELD_ID);
        }
    }

    public string? OperationalStateDesc
    {
        get
        {
            return base.GetNullableString(OPERATIONALSTATEDESC_FIELD_ID);
        }
    }

    public byte? ConnectedState
    {
        get
        {
            return base.GetNullableByte(CONNECTEDSTATE_FIELD_ID);
        }
    }

    public string? ConnectedStateDesc
    {
        get
        {
            return base.GetNullableString(CONNECTEDSTATEDESC_FIELD_ID);
        }
    }

    public byte? RecoveryHealth
    {
        get
        {
            return base.GetNullableByte(RECOVERYHEALTH_FIELD_ID);
        }
    }

    public string? RecoveryHealthDesc
    {
        get
        {
            return base.GetNullableString(RECOVERYHEALTHDESC_FIELD_ID);
        }
    }

    public byte? SynchronizationHealth
    {
        get
        {
            return base.GetNullableByte(SYNCHRONIZATIONHEALTH_FIELD_ID);
        }
    }

    public string? SynchronizationHealthDesc
    {
        get
        {
            return base.GetNullableString(SYNCHRONIZATIONHEALTHDESC_FIELD_ID);
        }
    }

    public int? LastConnectErrorNumber
    {
        get
        {
            return base.GetNullableInt32(LASTCONNECTERRORNUMBER_FIELD_ID);
        }
    }

    public string? LastConnectErrorDescription
    {
        get
        {
            return base.GetNullableString(LASTCONNECTERRORDESCRIPTION_FIELD_ID);
        }
    }

    public DateTime? LastConnectErrorTimestamp
    {
        get
        {
            return base.GetNullableDateTime(LASTCONNECTERRORTIMESTAMP_FIELD_ID);
        }
    }

    public long? WriteLeaseRemainingTicks
    {
        get
        {
            return base.GetNullableInt64(WRITELEASEREMAININGTICKS_FIELD_ID);
        }
    }

    public DateTime? CurrentConfigurationCommitStartTimeUtc
    {
        get
        {
            return base.GetNullableDateTime(CURRENTCONFIGURATIONCOMMITSTARTTIMEUTC_FIELD_ID);
        }
    }


    public Types.DmHadrAvailabilityReplicaStatesDataType ToDataObject()
    {
        return new Types.DmHadrAvailabilityReplicaStatesDataType(ReplicaId,
            GroupId,
            IsLocal,
            Role,
            RoleDesc,
            OperationalState,
            OperationalStateDesc,
            ConnectedState,
            ConnectedStateDesc,
            RecoveryHealth,
            RecoveryHealthDesc,
            SynchronizationHealth,
            SynchronizationHealthDesc,
            LastConnectErrorNumber,
            LastConnectErrorDescription,
            LastConnectErrorTimestamp,
            WriteLeaseRemainingTicks,
            CurrentConfigurationCommitStartTimeUtc);
    }

    public List<Types.DmHadrAvailabilityReplicaStatesDataType> ToList()
    {
        var list = new List<Types.DmHadrAvailabilityReplicaStatesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

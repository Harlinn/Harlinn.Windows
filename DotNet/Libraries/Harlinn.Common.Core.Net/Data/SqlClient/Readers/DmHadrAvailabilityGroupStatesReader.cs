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

public class DmHadrAvailabilityGroupStatesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_availability_group_states]";
    public const string TableName = "dm_hadr_availability_group_states";
    public const string ShortName = "dhags";
    public const string Sql = """
        SELECT
          dhags.[group_id],
          dhags.[primary_replica],
          dhags.[primary_recovery_health],
          dhags.[primary_recovery_health_desc],
          dhags.[secondary_recovery_health],
          dhags.[secondary_recovery_health_desc],
          dhags.[synchronization_health],
          dhags.[synchronization_health_desc]
        FROM
          [sys].[dm_hadr_availability_group_states] dhags
        """;

    public const int GROUPID_FIELD_ID = 0;
    public const int PRIMARYREPLICA_FIELD_ID = 1;
    public const int PRIMARYRECOVERYHEALTH_FIELD_ID = 2;
    public const int PRIMARYRECOVERYHEALTHDESC_FIELD_ID = 3;
    public const int SECONDARYRECOVERYHEALTH_FIELD_ID = 4;
    public const int SECONDARYRECOVERYHEALTHDESC_FIELD_ID = 5;
    public const int SYNCHRONIZATIONHEALTH_FIELD_ID = 6;
    public const int SYNCHRONIZATIONHEALTHDESC_FIELD_ID = 7;


    public DmHadrAvailabilityGroupStatesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrAvailabilityGroupStatesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrAvailabilityGroupStatesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid GroupId
    {
        get
        {
            return base.GetGuid(GROUPID_FIELD_ID);
        }
    }

    public string? PrimaryReplica
    {
        get
        {
            return base.GetNullableString(PRIMARYREPLICA_FIELD_ID);
        }
    }

    public byte? PrimaryRecoveryHealth
    {
        get
        {
            return base.GetNullableByte(PRIMARYRECOVERYHEALTH_FIELD_ID);
        }
    }

    public string? PrimaryRecoveryHealthDesc
    {
        get
        {
            return base.GetNullableString(PRIMARYRECOVERYHEALTHDESC_FIELD_ID);
        }
    }

    public byte? SecondaryRecoveryHealth
    {
        get
        {
            return base.GetNullableByte(SECONDARYRECOVERYHEALTH_FIELD_ID);
        }
    }

    public string? SecondaryRecoveryHealthDesc
    {
        get
        {
            return base.GetNullableString(SECONDARYRECOVERYHEALTHDESC_FIELD_ID);
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


    public Types.DmHadrAvailabilityGroupStatesDataType ToDataObject()
    {
        return new Types.DmHadrAvailabilityGroupStatesDataType(GroupId,
            PrimaryReplica,
            PrimaryRecoveryHealth,
            PrimaryRecoveryHealthDesc,
            SecondaryRecoveryHealth,
            SecondaryRecoveryHealthDesc,
            SynchronizationHealth,
            SynchronizationHealthDesc);
    }

    public List<Types.DmHadrAvailabilityGroupStatesDataType> ToList()
    {
        var list = new List<Types.DmHadrAvailabilityGroupStatesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

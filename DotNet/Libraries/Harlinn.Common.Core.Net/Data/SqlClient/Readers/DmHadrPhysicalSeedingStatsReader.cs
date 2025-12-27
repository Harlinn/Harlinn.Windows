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

public class DmHadrPhysicalSeedingStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_physical_seeding_stats]";
    public const string TableName = "dm_hadr_physical_seeding_stats";
    public const string ShortName = "dhpss";
    public const string Sql = """
        SELECT
          dhpss.[local_physical_seeding_id],
          dhpss.[remote_physical_seeding_id],
          dhpss.[local_database_id],
          dhpss.[local_database_name],
          dhpss.[remote_machine_name],
          dhpss.[role_desc],
          dhpss.[internal_state_desc],
          dhpss.[transfer_rate_bytes_per_second],
          dhpss.[transferred_size_bytes],
          dhpss.[database_size_bytes],
          dhpss.[start_time_utc],
          dhpss.[end_time_utc],
          dhpss.[estimate_time_complete_utc],
          dhpss.[total_disk_io_wait_time_ms],
          dhpss.[total_network_wait_time_ms],
          dhpss.[failure_code],
          dhpss.[failure_message],
          dhpss.[failure_time_utc],
          dhpss.[is_compression_enabled]
        FROM
          [sys].[dm_hadr_physical_seeding_stats] dhpss
        """;

    public const int LOCALPHYSICALSEEDINGID_FIELD_ID = 0;
    public const int REMOTEPHYSICALSEEDINGID_FIELD_ID = 1;
    public const int LOCALDATABASEID_FIELD_ID = 2;
    public const int LOCALDATABASENAME_FIELD_ID = 3;
    public const int REMOTEMACHINENAME_FIELD_ID = 4;
    public const int ROLEDESC_FIELD_ID = 5;
    public const int INTERNALSTATEDESC_FIELD_ID = 6;
    public const int TRANSFERRATEBYTESPERSECOND_FIELD_ID = 7;
    public const int TRANSFERREDSIZEBYTES_FIELD_ID = 8;
    public const int DATABASESIZEBYTES_FIELD_ID = 9;
    public const int STARTTIMEUTC_FIELD_ID = 10;
    public const int ENDTIMEUTC_FIELD_ID = 11;
    public const int ESTIMATETIMECOMPLETEUTC_FIELD_ID = 12;
    public const int TOTALDISKIOWAITTIMEMS_FIELD_ID = 13;
    public const int TOTALNETWORKWAITTIMEMS_FIELD_ID = 14;
    public const int FAILURECODE_FIELD_ID = 15;
    public const int FAILUREMESSAGE_FIELD_ID = 16;
    public const int FAILURETIMEUTC_FIELD_ID = 17;
    public const int ISCOMPRESSIONENABLED_FIELD_ID = 18;


    public DmHadrPhysicalSeedingStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrPhysicalSeedingStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrPhysicalSeedingStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid LocalPhysicalSeedingId
    {
        get
        {
            return base.GetGuid(LOCALPHYSICALSEEDINGID_FIELD_ID);
        }
    }

    public Guid? RemotePhysicalSeedingId
    {
        get
        {
            return base.GetNullableGuid(REMOTEPHYSICALSEEDINGID_FIELD_ID);
        }
    }

    public int LocalDatabaseId
    {
        get
        {
            return base.GetInt32(LOCALDATABASEID_FIELD_ID);
        }
    }

    public string? LocalDatabaseName
    {
        get
        {
            return base.GetNullableString(LOCALDATABASENAME_FIELD_ID);
        }
    }

    public string? RemoteMachineName
    {
        get
        {
            return base.GetNullableString(REMOTEMACHINENAME_FIELD_ID);
        }
    }

    public string? RoleDesc
    {
        get
        {
            return base.GetNullableString(ROLEDESC_FIELD_ID);
        }
    }

    public string? InternalStateDesc
    {
        get
        {
            return base.GetNullableString(INTERNALSTATEDESC_FIELD_ID);
        }
    }

    public long? TransferRateBytesPerSecond
    {
        get
        {
            return base.GetNullableInt64(TRANSFERRATEBYTESPERSECOND_FIELD_ID);
        }
    }

    public long? TransferredSizeBytes
    {
        get
        {
            return base.GetNullableInt64(TRANSFERREDSIZEBYTES_FIELD_ID);
        }
    }

    public long? DatabaseSizeBytes
    {
        get
        {
            return base.GetNullableInt64(DATABASESIZEBYTES_FIELD_ID);
        }
    }

    public DateTime? StartTimeUtc
    {
        get
        {
            return base.GetNullableDateTime(STARTTIMEUTC_FIELD_ID);
        }
    }

    public DateTime? EndTimeUtc
    {
        get
        {
            return base.GetNullableDateTime(ENDTIMEUTC_FIELD_ID);
        }
    }

    public DateTime? EstimateTimeCompleteUtc
    {
        get
        {
            return base.GetNullableDateTime(ESTIMATETIMECOMPLETEUTC_FIELD_ID);
        }
    }

    public long? TotalDiskIoWaitTimeMs
    {
        get
        {
            return base.GetNullableInt64(TOTALDISKIOWAITTIMEMS_FIELD_ID);
        }
    }

    public long? TotalNetworkWaitTimeMs
    {
        get
        {
            return base.GetNullableInt64(TOTALNETWORKWAITTIMEMS_FIELD_ID);
        }
    }

    public int? FailureCode
    {
        get
        {
            return base.GetNullableInt32(FAILURECODE_FIELD_ID);
        }
    }

    public string? FailureMessage
    {
        get
        {
            return base.GetNullableString(FAILUREMESSAGE_FIELD_ID);
        }
    }

    public DateTime? FailureTimeUtc
    {
        get
        {
            return base.GetNullableDateTime(FAILURETIMEUTC_FIELD_ID);
        }
    }

    public bool? IsCompressionEnabled
    {
        get
        {
            return base.GetNullableBoolean(ISCOMPRESSIONENABLED_FIELD_ID);
        }
    }


    public Types.DmHadrPhysicalSeedingStatsDataType ToDataObject()
    {
        return new Types.DmHadrPhysicalSeedingStatsDataType(LocalPhysicalSeedingId,
            RemotePhysicalSeedingId,
            LocalDatabaseId,
            LocalDatabaseName,
            RemoteMachineName,
            RoleDesc,
            InternalStateDesc,
            TransferRateBytesPerSecond,
            TransferredSizeBytes,
            DatabaseSizeBytes,
            StartTimeUtc,
            EndTimeUtc,
            EstimateTimeCompleteUtc,
            TotalDiskIoWaitTimeMs,
            TotalNetworkWaitTimeMs,
            FailureCode,
            FailureMessage,
            FailureTimeUtc,
            IsCompressionEnabled);
    }

    public List<Types.DmHadrPhysicalSeedingStatsDataType> ToList()
    {
        var list = new List<Types.DmHadrPhysicalSeedingStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

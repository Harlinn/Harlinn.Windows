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

public class DmHadrDatabaseReplicaStatesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_database_replica_states]";
    public const string TableName = "dm_hadr_database_replica_states";
    public const string ShortName = "dhdrs";
    public const string Sql = """
        SELECT
          dhdrs.[database_id],
          dhdrs.[group_id],
          dhdrs.[replica_id],
          dhdrs.[group_database_id],
          dhdrs.[is_local],
          dhdrs.[is_primary_replica],
          dhdrs.[synchronization_state],
          dhdrs.[synchronization_state_desc],
          dhdrs.[is_commit_participant],
          dhdrs.[synchronization_health],
          dhdrs.[synchronization_health_desc],
          dhdrs.[database_state],
          dhdrs.[database_state_desc],
          dhdrs.[is_suspended],
          dhdrs.[suspend_reason],
          dhdrs.[suspend_reason_desc],
          dhdrs.[recovery_lsn],
          dhdrs.[truncation_lsn],
          dhdrs.[last_sent_lsn],
          dhdrs.[last_sent_time],
          dhdrs.[last_received_lsn],
          dhdrs.[last_received_time],
          dhdrs.[last_hardened_lsn],
          dhdrs.[last_hardened_time],
          dhdrs.[last_redone_lsn],
          dhdrs.[last_redone_time],
          dhdrs.[log_send_queue_size],
          dhdrs.[log_send_rate],
          dhdrs.[redo_queue_size],
          dhdrs.[redo_rate],
          dhdrs.[filestream_send_rate],
          dhdrs.[end_of_log_lsn],
          dhdrs.[last_commit_lsn],
          dhdrs.[last_commit_time],
          dhdrs.[low_water_mark_for_ghosts],
          dhdrs.[secondary_lag_seconds],
          dhdrs.[quorum_commit_lsn],
          dhdrs.[quorum_commit_time]
        FROM
          [sys].[dm_hadr_database_replica_states] dhdrs
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int GROUPID_FIELD_ID = 1;
    public const int REPLICAID_FIELD_ID = 2;
    public const int GROUPDATABASEID_FIELD_ID = 3;
    public const int ISLOCAL_FIELD_ID = 4;
    public const int ISPRIMARYREPLICA_FIELD_ID = 5;
    public const int SYNCHRONIZATIONSTATE_FIELD_ID = 6;
    public const int SYNCHRONIZATIONSTATEDESC_FIELD_ID = 7;
    public const int ISCOMMITPARTICIPANT_FIELD_ID = 8;
    public const int SYNCHRONIZATIONHEALTH_FIELD_ID = 9;
    public const int SYNCHRONIZATIONHEALTHDESC_FIELD_ID = 10;
    public const int DATABASESTATE_FIELD_ID = 11;
    public const int DATABASESTATEDESC_FIELD_ID = 12;
    public const int ISSUSPENDED_FIELD_ID = 13;
    public const int SUSPENDREASON_FIELD_ID = 14;
    public const int SUSPENDREASONDESC_FIELD_ID = 15;
    public const int RECOVERYLSN_FIELD_ID = 16;
    public const int TRUNCATIONLSN_FIELD_ID = 17;
    public const int LASTSENTLSN_FIELD_ID = 18;
    public const int LASTSENTTIME_FIELD_ID = 19;
    public const int LASTRECEIVEDLSN_FIELD_ID = 20;
    public const int LASTRECEIVEDTIME_FIELD_ID = 21;
    public const int LASTHARDENEDLSN_FIELD_ID = 22;
    public const int LASTHARDENEDTIME_FIELD_ID = 23;
    public const int LASTREDONELSN_FIELD_ID = 24;
    public const int LASTREDONETIME_FIELD_ID = 25;
    public const int LOGSENDQUEUESIZE_FIELD_ID = 26;
    public const int LOGSENDRATE_FIELD_ID = 27;
    public const int REDOQUEUESIZE_FIELD_ID = 28;
    public const int REDORATE_FIELD_ID = 29;
    public const int FILESTREAMSENDRATE_FIELD_ID = 30;
    public const int ENDOFLOGLSN_FIELD_ID = 31;
    public const int LASTCOMMITLSN_FIELD_ID = 32;
    public const int LASTCOMMITTIME_FIELD_ID = 33;
    public const int LOWWATERMARKFORGHOSTS_FIELD_ID = 34;
    public const int SECONDARYLAGSECONDS_FIELD_ID = 35;
    public const int QUORUMCOMMITLSN_FIELD_ID = 36;
    public const int QUORUMCOMMITTIME_FIELD_ID = 37;


    public DmHadrDatabaseReplicaStatesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrDatabaseReplicaStatesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrDatabaseReplicaStatesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public Guid GroupId
    {
        get
        {
            return base.GetGuid(GROUPID_FIELD_ID);
        }
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

    public bool? IsLocal
    {
        get
        {
            return base.GetNullableBoolean(ISLOCAL_FIELD_ID);
        }
    }

    public bool? IsPrimaryReplica
    {
        get
        {
            return base.GetNullableBoolean(ISPRIMARYREPLICA_FIELD_ID);
        }
    }

    public byte? SynchronizationState
    {
        get
        {
            return base.GetNullableByte(SYNCHRONIZATIONSTATE_FIELD_ID);
        }
    }

    public string? SynchronizationStateDesc
    {
        get
        {
            return base.GetNullableString(SYNCHRONIZATIONSTATEDESC_FIELD_ID);
        }
    }

    public bool? IsCommitParticipant
    {
        get
        {
            return base.GetNullableBoolean(ISCOMMITPARTICIPANT_FIELD_ID);
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

    public byte? DatabaseState
    {
        get
        {
            return base.GetNullableByte(DATABASESTATE_FIELD_ID);
        }
    }

    public string? DatabaseStateDesc
    {
        get
        {
            return base.GetNullableString(DATABASESTATEDESC_FIELD_ID);
        }
    }

    public bool? IsSuspended
    {
        get
        {
            return base.GetNullableBoolean(ISSUSPENDED_FIELD_ID);
        }
    }

    public byte? SuspendReason
    {
        get
        {
            return base.GetNullableByte(SUSPENDREASON_FIELD_ID);
        }
    }

    public string? SuspendReasonDesc
    {
        get
        {
            return base.GetNullableString(SUSPENDREASONDESC_FIELD_ID);
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

    public decimal? LastSentLsn
    {
        get
        {
            return base.GetNullableDecimal(LASTSENTLSN_FIELD_ID);
        }
    }

    public DateTime? LastSentTime
    {
        get
        {
            return base.GetNullableDateTime(LASTSENTTIME_FIELD_ID);
        }
    }

    public decimal? LastReceivedLsn
    {
        get
        {
            return base.GetNullableDecimal(LASTRECEIVEDLSN_FIELD_ID);
        }
    }

    public DateTime? LastReceivedTime
    {
        get
        {
            return base.GetNullableDateTime(LASTRECEIVEDTIME_FIELD_ID);
        }
    }

    public decimal? LastHardenedLsn
    {
        get
        {
            return base.GetNullableDecimal(LASTHARDENEDLSN_FIELD_ID);
        }
    }

    public DateTime? LastHardenedTime
    {
        get
        {
            return base.GetNullableDateTime(LASTHARDENEDTIME_FIELD_ID);
        }
    }

    public decimal? LastRedoneLsn
    {
        get
        {
            return base.GetNullableDecimal(LASTREDONELSN_FIELD_ID);
        }
    }

    public DateTime? LastRedoneTime
    {
        get
        {
            return base.GetNullableDateTime(LASTREDONETIME_FIELD_ID);
        }
    }

    public long? LogSendQueueSize
    {
        get
        {
            return base.GetNullableInt64(LOGSENDQUEUESIZE_FIELD_ID);
        }
    }

    public long? LogSendRate
    {
        get
        {
            return base.GetNullableInt64(LOGSENDRATE_FIELD_ID);
        }
    }

    public long? RedoQueueSize
    {
        get
        {
            return base.GetNullableInt64(REDOQUEUESIZE_FIELD_ID);
        }
    }

    public long? RedoRate
    {
        get
        {
            return base.GetNullableInt64(REDORATE_FIELD_ID);
        }
    }

    public long? FilestreamSendRate
    {
        get
        {
            return base.GetNullableInt64(FILESTREAMSENDRATE_FIELD_ID);
        }
    }

    public decimal? EndOfLogLsn
    {
        get
        {
            return base.GetNullableDecimal(ENDOFLOGLSN_FIELD_ID);
        }
    }

    public decimal? LastCommitLsn
    {
        get
        {
            return base.GetNullableDecimal(LASTCOMMITLSN_FIELD_ID);
        }
    }

    public DateTime? LastCommitTime
    {
        get
        {
            return base.GetNullableDateTime(LASTCOMMITTIME_FIELD_ID);
        }
    }

    public long? LowWaterMarkForGhosts
    {
        get
        {
            return base.GetNullableInt64(LOWWATERMARKFORGHOSTS_FIELD_ID);
        }
    }

    public long? SecondaryLagSeconds
    {
        get
        {
            return base.GetNullableInt64(SECONDARYLAGSECONDS_FIELD_ID);
        }
    }

    public decimal? QuorumCommitLsn
    {
        get
        {
            return base.GetNullableDecimal(QUORUMCOMMITLSN_FIELD_ID);
        }
    }

    public DateTime? QuorumCommitTime
    {
        get
        {
            return base.GetNullableDateTime(QUORUMCOMMITTIME_FIELD_ID);
        }
    }


    public Types.DmHadrDatabaseReplicaStatesDataType ToDataObject()
    {
        return new Types.DmHadrDatabaseReplicaStatesDataType(DatabaseId,
            GroupId,
            ReplicaId,
            GroupDatabaseId,
            IsLocal,
            IsPrimaryReplica,
            SynchronizationState,
            SynchronizationStateDesc,
            IsCommitParticipant,
            SynchronizationHealth,
            SynchronizationHealthDesc,
            DatabaseState,
            DatabaseStateDesc,
            IsSuspended,
            SuspendReason,
            SuspendReasonDesc,
            RecoveryLsn,
            TruncationLsn,
            LastSentLsn,
            LastSentTime,
            LastReceivedLsn,
            LastReceivedTime,
            LastHardenedLsn,
            LastHardenedTime,
            LastRedoneLsn,
            LastRedoneTime,
            LogSendQueueSize,
            LogSendRate,
            RedoQueueSize,
            RedoRate,
            FilestreamSendRate,
            EndOfLogLsn,
            LastCommitLsn,
            LastCommitTime,
            LowWaterMarkForGhosts,
            SecondaryLagSeconds,
            QuorumCommitLsn,
            QuorumCommitTime);
    }

    public List<Types.DmHadrDatabaseReplicaStatesDataType> ToList()
    {
        var list = new List<Types.DmHadrDatabaseReplicaStatesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class DatabaseMirroringReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[database_mirroring]";
    public const string TableName = "database_mirroring";
    public const string ShortName = "dm";
    public const string Sql = """
        SELECT
          dm.[database_id],
          dm.[mirroring_guid],
          dm.[mirroring_state],
          dm.[mirroring_state_desc],
          dm.[mirroring_role],
          dm.[mirroring_role_desc],
          dm.[mirroring_role_sequence],
          dm.[mirroring_safety_level],
          dm.[mirroring_safety_level_desc],
          dm.[mirroring_safety_sequence],
          dm.[mirroring_partner_name],
          dm.[mirroring_partner_instance],
          dm.[mirroring_witness_name],
          dm.[mirroring_witness_state],
          dm.[mirroring_witness_state_desc],
          dm.[mirroring_failover_lsn],
          dm.[mirroring_connection_timeout],
          dm.[mirroring_redo_queue],
          dm.[mirroring_redo_queue_type],
          dm.[mirroring_end_of_log_lsn],
          dm.[mirroring_replication_lsn]
        FROM
          [sys].[database_mirroring] dm
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int MIRRORINGGUID_FIELD_ID = 1;
    public const int MIRRORINGSTATE_FIELD_ID = 2;
    public const int MIRRORINGSTATEDESC_FIELD_ID = 3;
    public const int MIRRORINGROLE_FIELD_ID = 4;
    public const int MIRRORINGROLEDESC_FIELD_ID = 5;
    public const int MIRRORINGROLESEQUENCE_FIELD_ID = 6;
    public const int MIRRORINGSAFETYLEVEL_FIELD_ID = 7;
    public const int MIRRORINGSAFETYLEVELDESC_FIELD_ID = 8;
    public const int MIRRORINGSAFETYSEQUENCE_FIELD_ID = 9;
    public const int MIRRORINGPARTNERNAME_FIELD_ID = 10;
    public const int MIRRORINGPARTNERINSTANCE_FIELD_ID = 11;
    public const int MIRRORINGWITNESSNAME_FIELD_ID = 12;
    public const int MIRRORINGWITNESSSTATE_FIELD_ID = 13;
    public const int MIRRORINGWITNESSSTATEDESC_FIELD_ID = 14;
    public const int MIRRORINGFAILOVERLSN_FIELD_ID = 15;
    public const int MIRRORINGCONNECTIONTIMEOUT_FIELD_ID = 16;
    public const int MIRRORINGREDOQUEUE_FIELD_ID = 17;
    public const int MIRRORINGREDOQUEUETYPE_FIELD_ID = 18;
    public const int MIRRORINGENDOFLOGLSN_FIELD_ID = 19;
    public const int MIRRORINGREPLICATIONLSN_FIELD_ID = 20;


    public DatabaseMirroringReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DatabaseMirroringReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DatabaseMirroringReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public Guid? MirroringGuid
    {
        get
        {
            return base.GetNullableGuid(MIRRORINGGUID_FIELD_ID);
        }
    }

    public byte? MirroringState
    {
        get
        {
            return base.GetNullableByte(MIRRORINGSTATE_FIELD_ID);
        }
    }

    public string? MirroringStateDesc
    {
        get
        {
            return base.GetNullableString(MIRRORINGSTATEDESC_FIELD_ID);
        }
    }

    public byte? MirroringRole
    {
        get
        {
            return base.GetNullableByte(MIRRORINGROLE_FIELD_ID);
        }
    }

    public string? MirroringRoleDesc
    {
        get
        {
            return base.GetNullableString(MIRRORINGROLEDESC_FIELD_ID);
        }
    }

    public int? MirroringRoleSequence
    {
        get
        {
            return base.GetNullableInt32(MIRRORINGROLESEQUENCE_FIELD_ID);
        }
    }

    public byte? MirroringSafetyLevel
    {
        get
        {
            return base.GetNullableByte(MIRRORINGSAFETYLEVEL_FIELD_ID);
        }
    }

    public string? MirroringSafetyLevelDesc
    {
        get
        {
            return base.GetNullableString(MIRRORINGSAFETYLEVELDESC_FIELD_ID);
        }
    }

    public int? MirroringSafetySequence
    {
        get
        {
            return base.GetNullableInt32(MIRRORINGSAFETYSEQUENCE_FIELD_ID);
        }
    }

    public string? MirroringPartnerName
    {
        get
        {
            return base.GetNullableString(MIRRORINGPARTNERNAME_FIELD_ID);
        }
    }

    public string? MirroringPartnerInstance
    {
        get
        {
            return base.GetNullableString(MIRRORINGPARTNERINSTANCE_FIELD_ID);
        }
    }

    public string? MirroringWitnessName
    {
        get
        {
            return base.GetNullableString(MIRRORINGWITNESSNAME_FIELD_ID);
        }
    }

    public byte? MirroringWitnessState
    {
        get
        {
            return base.GetNullableByte(MIRRORINGWITNESSSTATE_FIELD_ID);
        }
    }

    public string? MirroringWitnessStateDesc
    {
        get
        {
            return base.GetNullableString(MIRRORINGWITNESSSTATEDESC_FIELD_ID);
        }
    }

    public decimal? MirroringFailoverLsn
    {
        get
        {
            return base.GetNullableDecimal(MIRRORINGFAILOVERLSN_FIELD_ID);
        }
    }

    public int? MirroringConnectionTimeout
    {
        get
        {
            return base.GetNullableInt32(MIRRORINGCONNECTIONTIMEOUT_FIELD_ID);
        }
    }

    public int? MirroringRedoQueue
    {
        get
        {
            return base.GetNullableInt32(MIRRORINGREDOQUEUE_FIELD_ID);
        }
    }

    public string? MirroringRedoQueueType
    {
        get
        {
            return base.GetNullableString(MIRRORINGREDOQUEUETYPE_FIELD_ID);
        }
    }

    public decimal? MirroringEndOfLogLsn
    {
        get
        {
            return base.GetNullableDecimal(MIRRORINGENDOFLOGLSN_FIELD_ID);
        }
    }

    public decimal? MirroringReplicationLsn
    {
        get
        {
            return base.GetNullableDecimal(MIRRORINGREPLICATIONLSN_FIELD_ID);
        }
    }


    public Types.DatabaseMirroringDataType ToDataObject()
    {
        return new Types.DatabaseMirroringDataType(DatabaseId,
            MirroringGuid,
            MirroringState,
            MirroringStateDesc,
            MirroringRole,
            MirroringRoleDesc,
            MirroringRoleSequence,
            MirroringSafetyLevel,
            MirroringSafetyLevelDesc,
            MirroringSafetySequence,
            MirroringPartnerName,
            MirroringPartnerInstance,
            MirroringWitnessName,
            MirroringWitnessState,
            MirroringWitnessStateDesc,
            MirroringFailoverLsn,
            MirroringConnectionTimeout,
            MirroringRedoQueue,
            MirroringRedoQueueType,
            MirroringEndOfLogLsn,
            MirroringReplicationLsn);
    }

    public List<Types.DatabaseMirroringDataType> ToList()
    {
        var list = new List<Types.DatabaseMirroringDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

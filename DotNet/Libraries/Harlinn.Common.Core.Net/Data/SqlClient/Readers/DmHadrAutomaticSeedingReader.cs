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

public class DmHadrAutomaticSeedingReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_automatic_seeding]";
    public const string TableName = "dm_hadr_automatic_seeding";
    public const string ShortName = "dhas";
    public const string Sql = """
        SELECT
          dhas.[start_time],
          dhas.[completion_time],
          dhas.[ag_id],
          dhas.[ag_db_id],
          dhas.[ag_remote_replica_id],
          dhas.[operation_id],
          dhas.[is_source],
          dhas.[current_state],
          dhas.[performed_seeding],
          dhas.[failure_state],
          dhas.[failure_state_desc],
          dhas.[error_code],
          dhas.[number_of_attempts]
        FROM
          [sys].[dm_hadr_automatic_seeding] dhas
        """;

    public const int STARTTIME_FIELD_ID = 0;
    public const int COMPLETIONTIME_FIELD_ID = 1;
    public const int AGID_FIELD_ID = 2;
    public const int AGDBID_FIELD_ID = 3;
    public const int AGREMOTEREPLICAID_FIELD_ID = 4;
    public const int OPERATIONID_FIELD_ID = 5;
    public const int ISSOURCE_FIELD_ID = 6;
    public const int CURRENTSTATE_FIELD_ID = 7;
    public const int PERFORMEDSEEDING_FIELD_ID = 8;
    public const int FAILURESTATE_FIELD_ID = 9;
    public const int FAILURESTATEDESC_FIELD_ID = 10;
    public const int ERRORCODE_FIELD_ID = 11;
    public const int NUMBEROFATTEMPTS_FIELD_ID = 12;


    public DmHadrAutomaticSeedingReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrAutomaticSeedingReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrAutomaticSeedingReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public DateTime StartTime
    {
        get
        {
            return base.GetDateTime(STARTTIME_FIELD_ID);
        }
    }

    public DateTime? CompletionTime
    {
        get
        {
            return base.GetNullableDateTime(COMPLETIONTIME_FIELD_ID);
        }
    }

    public Guid AgId
    {
        get
        {
            return base.GetGuid(AGID_FIELD_ID);
        }
    }

    public Guid AgDbId
    {
        get
        {
            return base.GetGuid(AGDBID_FIELD_ID);
        }
    }

    public Guid AgRemoteReplicaId
    {
        get
        {
            return base.GetGuid(AGREMOTEREPLICAID_FIELD_ID);
        }
    }

    public Guid OperationId
    {
        get
        {
            return base.GetGuid(OPERATIONID_FIELD_ID);
        }
    }

    public bool IsSource
    {
        get
        {
            return base.GetBoolean(ISSOURCE_FIELD_ID);
        }
    }

    public string CurrentState
    {
        get
        {
            return base.GetString(CURRENTSTATE_FIELD_ID);
        }
    }

    public bool PerformedSeeding
    {
        get
        {
            return base.GetBoolean(PERFORMEDSEEDING_FIELD_ID);
        }
    }

    public int? FailureState
    {
        get
        {
            return base.GetNullableInt32(FAILURESTATE_FIELD_ID);
        }
    }

    public string? FailureStateDesc
    {
        get
        {
            return base.GetNullableString(FAILURESTATEDESC_FIELD_ID);
        }
    }

    public int? ErrorCode
    {
        get
        {
            return base.GetNullableInt32(ERRORCODE_FIELD_ID);
        }
    }

    public int NumberOfAttempts
    {
        get
        {
            return base.GetInt32(NUMBEROFATTEMPTS_FIELD_ID);
        }
    }


    public Types.DmHadrAutomaticSeedingDataType ToDataObject()
    {
        return new Types.DmHadrAutomaticSeedingDataType(StartTime,
            CompletionTime,
            AgId,
            AgDbId,
            AgRemoteReplicaId,
            OperationId,
            IsSource,
            CurrentState,
            PerformedSeeding,
            FailureState,
            FailureStateDesc,
            ErrorCode,
            NumberOfAttempts);
    }

    public List<Types.DmHadrAutomaticSeedingDataType> ToList()
    {
        var list = new List<Types.DmHadrAutomaticSeedingDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

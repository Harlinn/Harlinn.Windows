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

public class DmDbTuningRecommendationsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_tuning_recommendations]";
    public const string TableName = "dm_db_tuning_recommendations";
    public const string ShortName = "ddtr";
    public const string Sql = """
        SELECT
          ddtr.[Name],
          ddtr.[Type],
          ddtr.[Reason],
          ddtr.[valid_since],
          ddtr.[last_refresh],
          ddtr.[State],
          ddtr.[is_executable_action],
          ddtr.[is_revertable_action],
          ddtr.[execute_action_start_time],
          ddtr.[execute_action_duration],
          ddtr.[execute_action_initiated_by],
          ddtr.[execute_action_initiated_time],
          ddtr.[revert_action_start_time],
          ddtr.[revert_action_duration],
          ddtr.[revert_action_initiated_by],
          ddtr.[revert_action_initiated_time],
          ddtr.[Score],
          ddtr.[Details]
        FROM
          [sys].[dm_db_tuning_recommendations] ddtr
        """;

    public const int NAME_FIELD_ID = 0;
    public const int TYPE_FIELD_ID = 1;
    public const int REASON_FIELD_ID = 2;
    public const int VALIDSINCE_FIELD_ID = 3;
    public const int LASTREFRESH_FIELD_ID = 4;
    public const int STATE_FIELD_ID = 5;
    public const int ISEXECUTABLEACTION_FIELD_ID = 6;
    public const int ISREVERTABLEACTION_FIELD_ID = 7;
    public const int EXECUTEACTIONSTARTTIME_FIELD_ID = 8;
    public const int EXECUTEACTIONDURATION_FIELD_ID = 9;
    public const int EXECUTEACTIONINITIATEDBY_FIELD_ID = 10;
    public const int EXECUTEACTIONINITIATEDTIME_FIELD_ID = 11;
    public const int REVERTACTIONSTARTTIME_FIELD_ID = 12;
    public const int REVERTACTIONDURATION_FIELD_ID = 13;
    public const int REVERTACTIONINITIATEDBY_FIELD_ID = 14;
    public const int REVERTACTIONINITIATEDTIME_FIELD_ID = 15;
    public const int SCORE_FIELD_ID = 16;
    public const int DETAILS_FIELD_ID = 17;


    public DmDbTuningRecommendationsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbTuningRecommendationsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbTuningRecommendationsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
        }
    }

    public string? Reason
    {
        get
        {
            return base.GetNullableString(REASON_FIELD_ID);
        }
    }

    public DateTime? ValidSince
    {
        get
        {
            return base.GetNullableDateTime(VALIDSINCE_FIELD_ID);
        }
    }

    public DateTime? LastRefresh
    {
        get
        {
            return base.GetNullableDateTime(LASTREFRESH_FIELD_ID);
        }
    }

    public string? State
    {
        get
        {
            return base.GetNullableString(STATE_FIELD_ID);
        }
    }

    public bool? IsExecutableAction
    {
        get
        {
            return base.GetNullableBoolean(ISEXECUTABLEACTION_FIELD_ID);
        }
    }

    public bool? IsRevertableAction
    {
        get
        {
            return base.GetNullableBoolean(ISREVERTABLEACTION_FIELD_ID);
        }
    }

    public DateTime? ExecuteActionStartTime
    {
        get
        {
            return base.GetNullableDateTime(EXECUTEACTIONSTARTTIME_FIELD_ID);
        }
    }

    public DateTime? ExecuteActionDuration
    {
        get
        {
            return base.GetNullableDateTime(EXECUTEACTIONDURATION_FIELD_ID);
        }
    }

    public string? ExecuteActionInitiatedBy
    {
        get
        {
            return base.GetNullableString(EXECUTEACTIONINITIATEDBY_FIELD_ID);
        }
    }

    public DateTime? ExecuteActionInitiatedTime
    {
        get
        {
            return base.GetNullableDateTime(EXECUTEACTIONINITIATEDTIME_FIELD_ID);
        }
    }

    public DateTime? RevertActionStartTime
    {
        get
        {
            return base.GetNullableDateTime(REVERTACTIONSTARTTIME_FIELD_ID);
        }
    }

    public DateTime? RevertActionDuration
    {
        get
        {
            return base.GetNullableDateTime(REVERTACTIONDURATION_FIELD_ID);
        }
    }

    public string? RevertActionInitiatedBy
    {
        get
        {
            return base.GetNullableString(REVERTACTIONINITIATEDBY_FIELD_ID);
        }
    }

    public DateTime? RevertActionInitiatedTime
    {
        get
        {
            return base.GetNullableDateTime(REVERTACTIONINITIATEDTIME_FIELD_ID);
        }
    }

    public int? Score
    {
        get
        {
            return base.GetNullableInt32(SCORE_FIELD_ID);
        }
    }

    public string? Details
    {
        get
        {
            return base.GetNullableString(DETAILS_FIELD_ID);
        }
    }


    public Types.DmDbTuningRecommendationsDataType ToDataObject()
    {
        return new Types.DmDbTuningRecommendationsDataType(Name,
            Type,
            Reason,
            ValidSince,
            LastRefresh,
            State,
            IsExecutableAction,
            IsRevertableAction,
            ExecuteActionStartTime,
            ExecuteActionDuration,
            ExecuteActionInitiatedBy,
            ExecuteActionInitiatedTime,
            RevertActionStartTime,
            RevertActionDuration,
            RevertActionInitiatedBy,
            RevertActionInitiatedTime,
            Score,
            Details);
    }

    public List<Types.DmDbTuningRecommendationsDataType> ToList()
    {
        var list = new List<Types.DmDbTuningRecommendationsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

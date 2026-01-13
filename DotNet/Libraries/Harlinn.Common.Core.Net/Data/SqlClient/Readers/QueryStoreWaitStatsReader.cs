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

public class QueryStoreWaitStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[query_store_wait_stats]";
    public const string TableName = "query_store_wait_stats";
    public const string ShortName = "qsws";
    public const string Sql = """
        SELECT
          qsws.[wait_stats_id],
          qsws.[plan_id],
          qsws.[runtime_stats_interval_id],
          qsws.[wait_category],
          qsws.[wait_category_desc],
          qsws.[execution_type],
          qsws.[execution_type_desc],
          qsws.[total_query_wait_time_ms],
          qsws.[avg_query_wait_time_ms],
          qsws.[last_query_wait_time_ms],
          qsws.[min_query_wait_time_ms],
          qsws.[max_query_wait_time_ms],
          qsws.[stdev_query_wait_time_ms]
        FROM
          [sys].[query_store_wait_stats] qsws
        """;

    public const int WAITSTATSID_FIELD_ID = 0;
    public const int PLANID_FIELD_ID = 1;
    public const int RUNTIMESTATSINTERVALID_FIELD_ID = 2;
    public const int WAITCATEGORY_FIELD_ID = 3;
    public const int WAITCATEGORYDESC_FIELD_ID = 4;
    public const int EXECUTIONTYPE_FIELD_ID = 5;
    public const int EXECUTIONTYPEDESC_FIELD_ID = 6;
    public const int TOTALQUERYWAITTIMEMS_FIELD_ID = 7;
    public const int AVGQUERYWAITTIMEMS_FIELD_ID = 8;
    public const int LASTQUERYWAITTIMEMS_FIELD_ID = 9;
    public const int MINQUERYWAITTIMEMS_FIELD_ID = 10;
    public const int MAXQUERYWAITTIMEMS_FIELD_ID = 11;
    public const int STDEVQUERYWAITTIMEMS_FIELD_ID = 12;


    public QueryStoreWaitStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public QueryStoreWaitStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public QueryStoreWaitStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long WaitStatsId
    {
        get
        {
            return base.GetInt64(WAITSTATSID_FIELD_ID);
        }
    }

    public long PlanId
    {
        get
        {
            return base.GetInt64(PLANID_FIELD_ID);
        }
    }

    public long RuntimeStatsIntervalId
    {
        get
        {
            return base.GetInt64(RUNTIMESTATSINTERVALID_FIELD_ID);
        }
    }

    public short WaitCategory
    {
        get
        {
            return base.GetInt16(WAITCATEGORY_FIELD_ID);
        }
    }

    public string? WaitCategoryDesc
    {
        get
        {
            return base.GetNullableString(WAITCATEGORYDESC_FIELD_ID);
        }
    }

    public byte ExecutionType
    {
        get
        {
            return base.GetByte(EXECUTIONTYPE_FIELD_ID);
        }
    }

    public string? ExecutionTypeDesc
    {
        get
        {
            return base.GetNullableString(EXECUTIONTYPEDESC_FIELD_ID);
        }
    }

    public long TotalQueryWaitTimeMs
    {
        get
        {
            return base.GetInt64(TOTALQUERYWAITTIMEMS_FIELD_ID);
        }
    }

    public double? AvgQueryWaitTimeMs
    {
        get
        {
            return base.GetNullableDouble(AVGQUERYWAITTIMEMS_FIELD_ID);
        }
    }

    public long LastQueryWaitTimeMs
    {
        get
        {
            return base.GetInt64(LASTQUERYWAITTIMEMS_FIELD_ID);
        }
    }

    public long MinQueryWaitTimeMs
    {
        get
        {
            return base.GetInt64(MINQUERYWAITTIMEMS_FIELD_ID);
        }
    }

    public long MaxQueryWaitTimeMs
    {
        get
        {
            return base.GetInt64(MAXQUERYWAITTIMEMS_FIELD_ID);
        }
    }

    public double? StdevQueryWaitTimeMs
    {
        get
        {
            return base.GetNullableDouble(STDEVQUERYWAITTIMEMS_FIELD_ID);
        }
    }


    public Types.QueryStoreWaitStatsDataType ToDataObject()
    {
        return new Types.QueryStoreWaitStatsDataType(WaitStatsId,
            PlanId,
            RuntimeStatsIntervalId,
            WaitCategory,
            WaitCategoryDesc,
            ExecutionType,
            ExecutionTypeDesc,
            TotalQueryWaitTimeMs,
            AvgQueryWaitTimeMs,
            LastQueryWaitTimeMs,
            MinQueryWaitTimeMs,
            MaxQueryWaitTimeMs,
            StdevQueryWaitTimeMs);
    }

    public List<Types.QueryStoreWaitStatsDataType> ToList()
    {
        var list = new List<Types.QueryStoreWaitStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

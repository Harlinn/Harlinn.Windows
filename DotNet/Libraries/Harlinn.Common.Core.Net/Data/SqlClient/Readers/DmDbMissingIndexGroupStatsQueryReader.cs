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

public class DmDbMissingIndexGroupStatsQueryReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_missing_index_group_stats_query]";
    public const string TableName = "dm_db_missing_index_group_stats_query";
    public const string ShortName = "ddmigsq";
    public const string Sql = """
        SELECT
          ddmigsq.[group_handle],
          ddmigsq.[query_hash],
          ddmigsq.[query_plan_hash],
          ddmigsq.[last_sql_handle],
          ddmigsq.[last_statement_start_offset],
          ddmigsq.[last_statement_end_offset],
          ddmigsq.[last_statement_sql_handle],
          ddmigsq.[user_seeks],
          ddmigsq.[user_scans],
          ddmigsq.[last_user_seek],
          ddmigsq.[last_user_scan],
          ddmigsq.[avg_total_user_cost],
          ddmigsq.[avg_user_impact],
          ddmigsq.[system_seeks],
          ddmigsq.[system_scans],
          ddmigsq.[last_system_seek],
          ddmigsq.[last_system_scan],
          ddmigsq.[avg_total_system_cost],
          ddmigsq.[avg_system_impact]
        FROM
          [sys].[dm_db_missing_index_group_stats_query] ddmigsq
        """;

    public const int GROUPHANDLE_FIELD_ID = 0;
    public const int QUERYHASH_FIELD_ID = 1;
    public const int QUERYPLANHASH_FIELD_ID = 2;
    public const int LASTSQLHANDLE_FIELD_ID = 3;
    public const int LASTSTATEMENTSTARTOFFSET_FIELD_ID = 4;
    public const int LASTSTATEMENTENDOFFSET_FIELD_ID = 5;
    public const int LASTSTATEMENTSQLHANDLE_FIELD_ID = 6;
    public const int USERSEEKS_FIELD_ID = 7;
    public const int USERSCANS_FIELD_ID = 8;
    public const int LASTUSERSEEK_FIELD_ID = 9;
    public const int LASTUSERSCAN_FIELD_ID = 10;
    public const int AVGTOTALUSERCOST_FIELD_ID = 11;
    public const int AVGUSERIMPACT_FIELD_ID = 12;
    public const int SYSTEMSEEKS_FIELD_ID = 13;
    public const int SYSTEMSCANS_FIELD_ID = 14;
    public const int LASTSYSTEMSEEK_FIELD_ID = 15;
    public const int LASTSYSTEMSCAN_FIELD_ID = 16;
    public const int AVGTOTALSYSTEMCOST_FIELD_ID = 17;
    public const int AVGSYSTEMIMPACT_FIELD_ID = 18;


    public DmDbMissingIndexGroupStatsQueryReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbMissingIndexGroupStatsQueryReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbMissingIndexGroupStatsQueryReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int GroupHandle
    {
        get
        {
            return base.GetInt32(GROUPHANDLE_FIELD_ID);
        }
    }

    public byte[] QueryHash
    {
        get
        {
            return base.GetBinary(QUERYHASH_FIELD_ID);
        }
    }

    public byte[] QueryPlanHash
    {
        get
        {
            return base.GetBinary(QUERYPLANHASH_FIELD_ID);
        }
    }

    public byte[] LastSqlHandle
    {
        get
        {
            return base.GetBinary(LASTSQLHANDLE_FIELD_ID);
        }
    }

    public int LastStatementStartOffset
    {
        get
        {
            return base.GetInt32(LASTSTATEMENTSTARTOFFSET_FIELD_ID);
        }
    }

    public int LastStatementEndOffset
    {
        get
        {
            return base.GetInt32(LASTSTATEMENTENDOFFSET_FIELD_ID);
        }
    }

    public byte[]? LastStatementSqlHandle
    {
        get
        {
            return base.GetNullableBinary(LASTSTATEMENTSQLHANDLE_FIELD_ID);
        }
    }

    public long UserSeeks
    {
        get
        {
            return base.GetInt64(USERSEEKS_FIELD_ID);
        }
    }

    public long UserScans
    {
        get
        {
            return base.GetInt64(USERSCANS_FIELD_ID);
        }
    }

    public DateTime? LastUserSeek
    {
        get
        {
            return base.GetNullableDateTime(LASTUSERSEEK_FIELD_ID);
        }
    }

    public DateTime? LastUserScan
    {
        get
        {
            return base.GetNullableDateTime(LASTUSERSCAN_FIELD_ID);
        }
    }

    public double? AvgTotalUserCost
    {
        get
        {
            return base.GetNullableDouble(AVGTOTALUSERCOST_FIELD_ID);
        }
    }

    public double AvgUserImpact
    {
        get
        {
            return base.GetDouble(AVGUSERIMPACT_FIELD_ID);
        }
    }

    public long SystemSeeks
    {
        get
        {
            return base.GetInt64(SYSTEMSEEKS_FIELD_ID);
        }
    }

    public long SystemScans
    {
        get
        {
            return base.GetInt64(SYSTEMSCANS_FIELD_ID);
        }
    }

    public DateTime? LastSystemSeek
    {
        get
        {
            return base.GetNullableDateTime(LASTSYSTEMSEEK_FIELD_ID);
        }
    }

    public DateTime? LastSystemScan
    {
        get
        {
            return base.GetNullableDateTime(LASTSYSTEMSCAN_FIELD_ID);
        }
    }

    public double? AvgTotalSystemCost
    {
        get
        {
            return base.GetNullableDouble(AVGTOTALSYSTEMCOST_FIELD_ID);
        }
    }

    public double AvgSystemImpact
    {
        get
        {
            return base.GetDouble(AVGSYSTEMIMPACT_FIELD_ID);
        }
    }


    public Types.DmDbMissingIndexGroupStatsQueryDataType ToDataObject()
    {
        return new Types.DmDbMissingIndexGroupStatsQueryDataType(GroupHandle,
            QueryHash,
            QueryPlanHash,
            LastSqlHandle,
            LastStatementStartOffset,
            LastStatementEndOffset,
            LastStatementSqlHandle,
            UserSeeks,
            UserScans,
            LastUserSeek,
            LastUserScan,
            AvgTotalUserCost,
            AvgUserImpact,
            SystemSeeks,
            SystemScans,
            LastSystemSeek,
            LastSystemScan,
            AvgTotalSystemCost,
            AvgSystemImpact);
    }

    public List<Types.DmDbMissingIndexGroupStatsQueryDataType> ToList()
    {
        var list = new List<Types.DmDbMissingIndexGroupStatsQueryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

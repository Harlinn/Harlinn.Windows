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

public class DmDbXtpGcCycleStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_xtp_gc_cycle_stats]";
    public const string TableName = "dm_db_xtp_gc_cycle_stats";
    public const string ShortName = "ddxgcs";
    public const string Sql = """
        SELECT
          ddxgcs.[cycle_id],
          ddxgcs.[ticks_at_cycle_start],
          ddxgcs.[ticks_at_cycle_end],
          ddxgcs.[node_id],
          ddxgcs.[base_generation],
          ddxgcs.[xacts_copied_to_local],
          ddxgcs.[xacts_in_gen_0],
          ddxgcs.[xacts_in_gen_1],
          ddxgcs.[xacts_in_gen_2],
          ddxgcs.[xacts_in_gen_3],
          ddxgcs.[xacts_in_gen_4],
          ddxgcs.[xacts_in_gen_5],
          ddxgcs.[xacts_in_gen_6],
          ddxgcs.[xacts_in_gen_7],
          ddxgcs.[xacts_in_gen_8],
          ddxgcs.[xacts_in_gen_9],
          ddxgcs.[xacts_in_gen_10],
          ddxgcs.[xacts_in_gen_11],
          ddxgcs.[xacts_in_gen_12],
          ddxgcs.[xacts_in_gen_13],
          ddxgcs.[xacts_in_gen_14],
          ddxgcs.[xacts_in_gen_15]
        FROM
          [sys].[dm_db_xtp_gc_cycle_stats] ddxgcs
        """;

    public const int CYCLEID_FIELD_ID = 0;
    public const int TICKSATCYCLESTART_FIELD_ID = 1;
    public const int TICKSATCYCLEEND_FIELD_ID = 2;
    public const int NODEID_FIELD_ID = 3;
    public const int BASEGENERATION_FIELD_ID = 4;
    public const int XACTSCOPIEDTOLOCAL_FIELD_ID = 5;
    public const int XACTSINGEN0_FIELD_ID = 6;
    public const int XACTSINGEN1_FIELD_ID = 7;
    public const int XACTSINGEN2_FIELD_ID = 8;
    public const int XACTSINGEN3_FIELD_ID = 9;
    public const int XACTSINGEN4_FIELD_ID = 10;
    public const int XACTSINGEN5_FIELD_ID = 11;
    public const int XACTSINGEN6_FIELD_ID = 12;
    public const int XACTSINGEN7_FIELD_ID = 13;
    public const int XACTSINGEN8_FIELD_ID = 14;
    public const int XACTSINGEN9_FIELD_ID = 15;
    public const int XACTSINGEN10_FIELD_ID = 16;
    public const int XACTSINGEN11_FIELD_ID = 17;
    public const int XACTSINGEN12_FIELD_ID = 18;
    public const int XACTSINGEN13_FIELD_ID = 19;
    public const int XACTSINGEN14_FIELD_ID = 20;
    public const int XACTSINGEN15_FIELD_ID = 21;


    public DmDbXtpGcCycleStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpGcCycleStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpGcCycleStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long CycleId
    {
        get
        {
            return base.GetInt64(CYCLEID_FIELD_ID);
        }
    }

    public long TicksAtCycleStart
    {
        get
        {
            return base.GetInt64(TICKSATCYCLESTART_FIELD_ID);
        }
    }

    public long TicksAtCycleEnd
    {
        get
        {
            return base.GetInt64(TICKSATCYCLEEND_FIELD_ID);
        }
    }

    public int NodeId
    {
        get
        {
            return base.GetInt32(NODEID_FIELD_ID);
        }
    }

    public long BaseGeneration
    {
        get
        {
            return base.GetInt64(BASEGENERATION_FIELD_ID);
        }
    }

    public long XactsCopiedToLocal
    {
        get
        {
            return base.GetInt64(XACTSCOPIEDTOLOCAL_FIELD_ID);
        }
    }

    public long XactsInGen0
    {
        get
        {
            return base.GetInt64(XACTSINGEN0_FIELD_ID);
        }
    }

    public long XactsInGen1
    {
        get
        {
            return base.GetInt64(XACTSINGEN1_FIELD_ID);
        }
    }

    public long XactsInGen2
    {
        get
        {
            return base.GetInt64(XACTSINGEN2_FIELD_ID);
        }
    }

    public long XactsInGen3
    {
        get
        {
            return base.GetInt64(XACTSINGEN3_FIELD_ID);
        }
    }

    public long XactsInGen4
    {
        get
        {
            return base.GetInt64(XACTSINGEN4_FIELD_ID);
        }
    }

    public long XactsInGen5
    {
        get
        {
            return base.GetInt64(XACTSINGEN5_FIELD_ID);
        }
    }

    public long XactsInGen6
    {
        get
        {
            return base.GetInt64(XACTSINGEN6_FIELD_ID);
        }
    }

    public long XactsInGen7
    {
        get
        {
            return base.GetInt64(XACTSINGEN7_FIELD_ID);
        }
    }

    public long XactsInGen8
    {
        get
        {
            return base.GetInt64(XACTSINGEN8_FIELD_ID);
        }
    }

    public long XactsInGen9
    {
        get
        {
            return base.GetInt64(XACTSINGEN9_FIELD_ID);
        }
    }

    public long XactsInGen10
    {
        get
        {
            return base.GetInt64(XACTSINGEN10_FIELD_ID);
        }
    }

    public long XactsInGen11
    {
        get
        {
            return base.GetInt64(XACTSINGEN11_FIELD_ID);
        }
    }

    public long XactsInGen12
    {
        get
        {
            return base.GetInt64(XACTSINGEN12_FIELD_ID);
        }
    }

    public long XactsInGen13
    {
        get
        {
            return base.GetInt64(XACTSINGEN13_FIELD_ID);
        }
    }

    public long XactsInGen14
    {
        get
        {
            return base.GetInt64(XACTSINGEN14_FIELD_ID);
        }
    }

    public long XactsInGen15
    {
        get
        {
            return base.GetInt64(XACTSINGEN15_FIELD_ID);
        }
    }


    public Types.DmDbXtpGcCycleStatsDataType ToDataObject()
    {
        return new Types.DmDbXtpGcCycleStatsDataType(CycleId,
            TicksAtCycleStart,
            TicksAtCycleEnd,
            NodeId,
            BaseGeneration,
            XactsCopiedToLocal,
            XactsInGen0,
            XactsInGen1,
            XactsInGen2,
            XactsInGen3,
            XactsInGen4,
            XactsInGen5,
            XactsInGen6,
            XactsInGen7,
            XactsInGen8,
            XactsInGen9,
            XactsInGen10,
            XactsInGen11,
            XactsInGen12,
            XactsInGen13,
            XactsInGen14,
            XactsInGen15);
    }

    public List<Types.DmDbXtpGcCycleStatsDataType> ToList()
    {
        var list = new List<Types.DmDbXtpGcCycleStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class DmPalCpuStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_pal_cpu_stats]";
    public const string TableName = "dm_pal_cpu_stats";
    public const string ShortName = "dpcs";
    public const string Sql = """
        SELECT
          dpcs.[uptime_secs],
          dpcs.[loadavg_1min],
          dpcs.[user_time_cs],
          dpcs.[nice_time_cs],
          dpcs.[system_time_cs],
          dpcs.[idle_time_cs],
          dpcs.[iowait_time_cs],
          dpcs.[irq_time_cs],
          dpcs.[softirq_time_cs],
          dpcs.[interrupt_cnt],
          dpcs.[csw_cnt],
          dpcs.[boot_time_secs],
          dpcs.[total_forks_cnt],
          dpcs.[proc_runable_cnt],
          dpcs.[proc_ioblocked_cnt],
          dpcs.[C3_time],
          dpcs.[C2_time],
          dpcs.[C1_time],
          dpcs.[C3_count],
          dpcs.[C2_count],
          dpcs.[C1_count]
        FROM
          [sys].[dm_pal_cpu_stats] dpcs
        """;

    public const int UPTIMESECS_FIELD_ID = 0;
    public const int LOADAVG1MIN_FIELD_ID = 1;
    public const int USERTIMECS_FIELD_ID = 2;
    public const int NICETIMECS_FIELD_ID = 3;
    public const int SYSTEMTIMECS_FIELD_ID = 4;
    public const int IDLETIMECS_FIELD_ID = 5;
    public const int IOWAITTIMECS_FIELD_ID = 6;
    public const int IRQTIMECS_FIELD_ID = 7;
    public const int SOFTIRQTIMECS_FIELD_ID = 8;
    public const int INTERRUPTCNT_FIELD_ID = 9;
    public const int CSWCNT_FIELD_ID = 10;
    public const int BOOTTIMESECS_FIELD_ID = 11;
    public const int TOTALFORKSCNT_FIELD_ID = 12;
    public const int PROCRUNABLECNT_FIELD_ID = 13;
    public const int PROCIOBLOCKEDCNT_FIELD_ID = 14;
    public const int C3TIME_FIELD_ID = 15;
    public const int C2TIME_FIELD_ID = 16;
    public const int C1TIME_FIELD_ID = 17;
    public const int C3COUNT_FIELD_ID = 18;
    public const int C2COUNT_FIELD_ID = 19;
    public const int C1COUNT_FIELD_ID = 20;


    public DmPalCpuStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmPalCpuStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmPalCpuStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long UptimeSecs
    {
        get
        {
            return base.GetInt64(UPTIMESECS_FIELD_ID);
        }
    }

    public double Loadavg1min
    {
        get
        {
            return base.GetDouble(LOADAVG1MIN_FIELD_ID);
        }
    }

    public long UserTimeCs
    {
        get
        {
            return base.GetInt64(USERTIMECS_FIELD_ID);
        }
    }

    public long NiceTimeCs
    {
        get
        {
            return base.GetInt64(NICETIMECS_FIELD_ID);
        }
    }

    public long SystemTimeCs
    {
        get
        {
            return base.GetInt64(SYSTEMTIMECS_FIELD_ID);
        }
    }

    public long IdleTimeCs
    {
        get
        {
            return base.GetInt64(IDLETIMECS_FIELD_ID);
        }
    }

    public long IowaitTimeCs
    {
        get
        {
            return base.GetInt64(IOWAITTIMECS_FIELD_ID);
        }
    }

    public long IrqTimeCs
    {
        get
        {
            return base.GetInt64(IRQTIMECS_FIELD_ID);
        }
    }

    public long SoftirqTimeCs
    {
        get
        {
            return base.GetInt64(SOFTIRQTIMECS_FIELD_ID);
        }
    }

    public long InterruptCnt
    {
        get
        {
            return base.GetInt64(INTERRUPTCNT_FIELD_ID);
        }
    }

    public long CswCnt
    {
        get
        {
            return base.GetInt64(CSWCNT_FIELD_ID);
        }
    }

    public long BootTimeSecs
    {
        get
        {
            return base.GetInt64(BOOTTIMESECS_FIELD_ID);
        }
    }

    public long TotalForksCnt
    {
        get
        {
            return base.GetInt64(TOTALFORKSCNT_FIELD_ID);
        }
    }

    public long ProcRunableCnt
    {
        get
        {
            return base.GetInt64(PROCRUNABLECNT_FIELD_ID);
        }
    }

    public long ProcIoblockedCnt
    {
        get
        {
            return base.GetInt64(PROCIOBLOCKEDCNT_FIELD_ID);
        }
    }

    public long C3Time
    {
        get
        {
            return base.GetInt64(C3TIME_FIELD_ID);
        }
    }

    public long C2Time
    {
        get
        {
            return base.GetInt64(C2TIME_FIELD_ID);
        }
    }

    public long C1Time
    {
        get
        {
            return base.GetInt64(C1TIME_FIELD_ID);
        }
    }

    public long C3Count
    {
        get
        {
            return base.GetInt64(C3COUNT_FIELD_ID);
        }
    }

    public long C2Count
    {
        get
        {
            return base.GetInt64(C2COUNT_FIELD_ID);
        }
    }

    public long C1Count
    {
        get
        {
            return base.GetInt64(C1COUNT_FIELD_ID);
        }
    }


    public Types.DmPalCpuStatsDataType ToDataObject()
    {
        return new Types.DmPalCpuStatsDataType(UptimeSecs,
            Loadavg1min,
            UserTimeCs,
            NiceTimeCs,
            SystemTimeCs,
            IdleTimeCs,
            IowaitTimeCs,
            IrqTimeCs,
            SoftirqTimeCs,
            InterruptCnt,
            CswCnt,
            BootTimeSecs,
            TotalForksCnt,
            ProcRunableCnt,
            ProcIoblockedCnt,
            C3Time,
            C2Time,
            C1Time,
            C3Count,
            C2Count,
            C1Count);
    }

    public List<Types.DmPalCpuStatsDataType> ToList()
    {
        var list = new List<Types.DmPalCpuStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class DmPalDiskStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_pal_disk_stats]";
    public const string TableName = "dm_pal_disk_stats";
    public const string ShortName = "dpds";
    public const string Sql = """
        SELECT
          dpds.[dev_name],
          dpds.[major_num],
          dpds.[minor_num],
          dpds.[reads_completed],
          dpds.[reads_merged],
          dpds.[sectors_read],
          dpds.[read_time_ms],
          dpds.[writes_completed],
          dpds.[writes_merged],
          dpds.[sectors_written],
          dpds.[write_time_ms],
          dpds.[ios_in_progess],
          dpds.[io_time_ms],
          dpds.[weighted_io_time_ms]
        FROM
          [sys].[dm_pal_disk_stats] dpds
        """;

    public const int DEVNAME_FIELD_ID = 0;
    public const int MAJORNUM_FIELD_ID = 1;
    public const int MINORNUM_FIELD_ID = 2;
    public const int READSCOMPLETED_FIELD_ID = 3;
    public const int READSMERGED_FIELD_ID = 4;
    public const int SECTORSREAD_FIELD_ID = 5;
    public const int READTIMEMS_FIELD_ID = 6;
    public const int WRITESCOMPLETED_FIELD_ID = 7;
    public const int WRITESMERGED_FIELD_ID = 8;
    public const int SECTORSWRITTEN_FIELD_ID = 9;
    public const int WRITETIMEMS_FIELD_ID = 10;
    public const int IOSINPROGESS_FIELD_ID = 11;
    public const int IOTIMEMS_FIELD_ID = 12;
    public const int WEIGHTEDIOTIMEMS_FIELD_ID = 13;


    public DmPalDiskStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmPalDiskStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmPalDiskStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string DevName
    {
        get
        {
            return base.GetString(DEVNAME_FIELD_ID);
        }
    }

    public long MajorNum
    {
        get
        {
            return base.GetInt64(MAJORNUM_FIELD_ID);
        }
    }

    public long MinorNum
    {
        get
        {
            return base.GetInt64(MINORNUM_FIELD_ID);
        }
    }

    public long ReadsCompleted
    {
        get
        {
            return base.GetInt64(READSCOMPLETED_FIELD_ID);
        }
    }

    public long ReadsMerged
    {
        get
        {
            return base.GetInt64(READSMERGED_FIELD_ID);
        }
    }

    public long SectorsRead
    {
        get
        {
            return base.GetInt64(SECTORSREAD_FIELD_ID);
        }
    }

    public long ReadTimeMs
    {
        get
        {
            return base.GetInt64(READTIMEMS_FIELD_ID);
        }
    }

    public long WritesCompleted
    {
        get
        {
            return base.GetInt64(WRITESCOMPLETED_FIELD_ID);
        }
    }

    public long WritesMerged
    {
        get
        {
            return base.GetInt64(WRITESMERGED_FIELD_ID);
        }
    }

    public long SectorsWritten
    {
        get
        {
            return base.GetInt64(SECTORSWRITTEN_FIELD_ID);
        }
    }

    public long WriteTimeMs
    {
        get
        {
            return base.GetInt64(WRITETIMEMS_FIELD_ID);
        }
    }

    public long IosInProgess
    {
        get
        {
            return base.GetInt64(IOSINPROGESS_FIELD_ID);
        }
    }

    public long IoTimeMs
    {
        get
        {
            return base.GetInt64(IOTIMEMS_FIELD_ID);
        }
    }

    public long WeightedIoTimeMs
    {
        get
        {
            return base.GetInt64(WEIGHTEDIOTIMEMS_FIELD_ID);
        }
    }


    public Types.DmPalDiskStatsDataType ToDataObject()
    {
        return new Types.DmPalDiskStatsDataType(DevName,
            MajorNum,
            MinorNum,
            ReadsCompleted,
            ReadsMerged,
            SectorsRead,
            ReadTimeMs,
            WritesCompleted,
            WritesMerged,
            SectorsWritten,
            WriteTimeMs,
            IosInProgess,
            IoTimeMs,
            WeightedIoTimeMs);
    }

    public List<Types.DmPalDiskStatsDataType> ToList()
    {
        var list = new List<Types.DmPalDiskStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

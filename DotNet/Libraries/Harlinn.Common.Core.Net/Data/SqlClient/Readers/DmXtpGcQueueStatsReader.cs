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

public class DmXtpGcQueueStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_xtp_gc_queue_stats]";
    public const string TableName = "dm_xtp_gc_queue_stats";
    public const string ShortName = "dxgqs";
    public const string Sql = """
        SELECT
          dxgqs.[queue_id],
          dxgqs.[total_enqueues],
          dxgqs.[total_dequeues],
          dxgqs.[current_queue_depth],
          dxgqs.[maximum_queue_depth],
          dxgqs.[last_service_ticks]
        FROM
          [sys].[dm_xtp_gc_queue_stats] dxgqs
        """;

    public const int QUEUEID_FIELD_ID = 0;
    public const int TOTALENQUEUES_FIELD_ID = 1;
    public const int TOTALDEQUEUES_FIELD_ID = 2;
    public const int CURRENTQUEUEDEPTH_FIELD_ID = 3;
    public const int MAXIMUMQUEUEDEPTH_FIELD_ID = 4;
    public const int LASTSERVICETICKS_FIELD_ID = 5;


    public DmXtpGcQueueStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmXtpGcQueueStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmXtpGcQueueStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int QueueId
    {
        get
        {
            return base.GetInt32(QUEUEID_FIELD_ID);
        }
    }

    public long TotalEnqueues
    {
        get
        {
            return base.GetInt64(TOTALENQUEUES_FIELD_ID);
        }
    }

    public long TotalDequeues
    {
        get
        {
            return base.GetInt64(TOTALDEQUEUES_FIELD_ID);
        }
    }

    public long CurrentQueueDepth
    {
        get
        {
            return base.GetInt64(CURRENTQUEUEDEPTH_FIELD_ID);
        }
    }

    public long MaximumQueueDepth
    {
        get
        {
            return base.GetInt64(MAXIMUMQUEUEDEPTH_FIELD_ID);
        }
    }

    public long LastServiceTicks
    {
        get
        {
            return base.GetInt64(LASTSERVICETICKS_FIELD_ID);
        }
    }


    public Types.DmXtpGcQueueStatsDataType ToDataObject()
    {
        return new Types.DmXtpGcQueueStatsDataType(QueueId,
            TotalEnqueues,
            TotalDequeues,
            CurrentQueueDepth,
            MaximumQueueDepth,
            LastServiceTicks);
    }

    public List<Types.DmXtpGcQueueStatsDataType> ToList()
    {
        var list = new List<Types.DmXtpGcQueueStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

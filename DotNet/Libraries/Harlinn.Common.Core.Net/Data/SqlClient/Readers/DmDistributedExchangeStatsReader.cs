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

public class DmDistributedExchangeStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_distributed_exchange_stats]";
    public const string TableName = "dm_distributed_exchange_stats";
    public const string ShortName = "ddes";
    public const string Sql = """
        SELECT
          ddes.[request_id],
          ddes.[step_index],
          ddes.[dms_step_index],
          ddes.[source_distribution_id],
          ddes.[destination_distribution_id],
          ddes.[Type],
          ddes.[Status],
          ddes.[bytes_per_sec],
          ddes.[bytes_processed],
          ddes.[rows_processed],
          ddes.[start_time],
          ddes.[end_time],
          ddes.[total_elapsed_time],
          ddes.[cpu_time],
          ddes.[query_time],
          ddes.[buffers_available],
          ddes.[sql_spid],
          ddes.[dms_cpid],
          ddes.[error_id],
          ddes.[source_info],
          ddes.[destination_info]
        FROM
          [sys].[dm_distributed_exchange_stats] ddes
        """;

    public const int REQUESTID_FIELD_ID = 0;
    public const int STEPINDEX_FIELD_ID = 1;
    public const int DMSSTEPINDEX_FIELD_ID = 2;
    public const int SOURCEDISTRIBUTIONID_FIELD_ID = 3;
    public const int DESTINATIONDISTRIBUTIONID_FIELD_ID = 4;
    public const int TYPE_FIELD_ID = 5;
    public const int STATUS_FIELD_ID = 6;
    public const int BYTESPERSEC_FIELD_ID = 7;
    public const int BYTESPROCESSED_FIELD_ID = 8;
    public const int ROWSPROCESSED_FIELD_ID = 9;
    public const int STARTTIME_FIELD_ID = 10;
    public const int ENDTIME_FIELD_ID = 11;
    public const int TOTALELAPSEDTIME_FIELD_ID = 12;
    public const int CPUTIME_FIELD_ID = 13;
    public const int QUERYTIME_FIELD_ID = 14;
    public const int BUFFERSAVAILABLE_FIELD_ID = 15;
    public const int SQLSPID_FIELD_ID = 16;
    public const int DMSCPID_FIELD_ID = 17;
    public const int ERRORID_FIELD_ID = 18;
    public const int SOURCEINFO_FIELD_ID = 19;
    public const int DESTINATIONINFO_FIELD_ID = 20;


    public DmDistributedExchangeStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDistributedExchangeStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDistributedExchangeStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? RequestId
    {
        get
        {
            return base.GetNullableString(REQUESTID_FIELD_ID);
        }
    }

    public int StepIndex
    {
        get
        {
            return base.GetInt32(STEPINDEX_FIELD_ID);
        }
    }

    public int? DmsStepIndex
    {
        get
        {
            return base.GetNullableInt32(DMSSTEPINDEX_FIELD_ID);
        }
    }

    public int SourceDistributionId
    {
        get
        {
            return base.GetInt32(SOURCEDISTRIBUTIONID_FIELD_ID);
        }
    }

    public int? DestinationDistributionId
    {
        get
        {
            return base.GetNullableInt32(DESTINATIONDISTRIBUTIONID_FIELD_ID);
        }
    }

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
        }
    }

    public string? Status
    {
        get
        {
            return base.GetNullableString(STATUS_FIELD_ID);
        }
    }

    public long BytesPerSec
    {
        get
        {
            return base.GetInt64(BYTESPERSEC_FIELD_ID);
        }
    }

    public long BytesProcessed
    {
        get
        {
            return base.GetInt64(BYTESPROCESSED_FIELD_ID);
        }
    }

    public long RowsProcessed
    {
        get
        {
            return base.GetInt64(ROWSPROCESSED_FIELD_ID);
        }
    }

    public DateTime StartTime
    {
        get
        {
            return base.GetDateTime(STARTTIME_FIELD_ID);
        }
    }

    public DateTime? EndTime
    {
        get
        {
            return base.GetNullableDateTime(ENDTIME_FIELD_ID);
        }
    }

    public int TotalElapsedTime
    {
        get
        {
            return base.GetInt32(TOTALELAPSEDTIME_FIELD_ID);
        }
    }

    public long? CpuTime
    {
        get
        {
            return base.GetNullableInt64(CPUTIME_FIELD_ID);
        }
    }

    public int QueryTime
    {
        get
        {
            return base.GetInt32(QUERYTIME_FIELD_ID);
        }
    }

    public int? BuffersAvailable
    {
        get
        {
            return base.GetNullableInt32(BUFFERSAVAILABLE_FIELD_ID);
        }
    }

    public int SqlSpid
    {
        get
        {
            return base.GetInt32(SQLSPID_FIELD_ID);
        }
    }

    public int? DmsCpid
    {
        get
        {
            return base.GetNullableInt32(DMSCPID_FIELD_ID);
        }
    }

    public string? ErrorId
    {
        get
        {
            return base.GetNullableString(ERRORID_FIELD_ID);
        }
    }

    public string? SourceInfo
    {
        get
        {
            return base.GetNullableString(SOURCEINFO_FIELD_ID);
        }
    }

    public string? DestinationInfo
    {
        get
        {
            return base.GetNullableString(DESTINATIONINFO_FIELD_ID);
        }
    }


    public Types.DmDistributedExchangeStatsDataType ToDataObject()
    {
        return new Types.DmDistributedExchangeStatsDataType(RequestId,
            StepIndex,
            DmsStepIndex,
            SourceDistributionId,
            DestinationDistributionId,
            Type,
            Status,
            BytesPerSec,
            BytesProcessed,
            RowsProcessed,
            StartTime,
            EndTime,
            TotalElapsedTime,
            CpuTime,
            QueryTime,
            BuffersAvailable,
            SqlSpid,
            DmsCpid,
            ErrorId,
            SourceInfo,
            DestinationInfo);
    }

    public List<Types.DmDistributedExchangeStatsDataType> ToList()
    {
        var list = new List<Types.DmDistributedExchangeStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

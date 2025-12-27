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

public class DmResourceGovernorResourcePoolVolumesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_resource_governor_resource_pool_volumes]";
    public const string TableName = "dm_resource_governor_resource_pool_volumes";
    public const string ShortName = "drgrpv";
    public const string Sql = """
        SELECT
          drgrpv.[pool_id],
          drgrpv.[volume_name],
          drgrpv.[read_io_queued_total],
          drgrpv.[read_io_issued_total],
          drgrpv.[read_io_completed_total],
          drgrpv.[read_io_throttled_total],
          drgrpv.[read_bytes_total],
          drgrpv.[read_io_stall_total_ms],
          drgrpv.[read_io_stall_queued_ms],
          drgrpv.[write_io_queued_total],
          drgrpv.[write_io_issued_total],
          drgrpv.[write_io_completed_total],
          drgrpv.[write_io_throttled_total],
          drgrpv.[write_bytes_total],
          drgrpv.[write_io_stall_total_ms],
          drgrpv.[write_io_stall_queued_ms],
          drgrpv.[io_issue_violations_total],
          drgrpv.[io_issue_delay_total_ms],
          drgrpv.[io_issue_ahead_total_ms],
          drgrpv.[reserved_io_limited_by_volume_total],
          drgrpv.[io_issue_delay_non_throttled_total_ms]
        FROM
          [sys].[dm_resource_governor_resource_pool_volumes] drgrpv
        """;

    public const int POOLID_FIELD_ID = 0;
    public const int VOLUMENAME_FIELD_ID = 1;
    public const int READIOQUEUEDTOTAL_FIELD_ID = 2;
    public const int READIOISSUEDTOTAL_FIELD_ID = 3;
    public const int READIOCOMPLETEDTOTAL_FIELD_ID = 4;
    public const int READIOTHROTTLEDTOTAL_FIELD_ID = 5;
    public const int READBYTESTOTAL_FIELD_ID = 6;
    public const int READIOSTALLTOTALMS_FIELD_ID = 7;
    public const int READIOSTALLQUEUEDMS_FIELD_ID = 8;
    public const int WRITEIOQUEUEDTOTAL_FIELD_ID = 9;
    public const int WRITEIOISSUEDTOTAL_FIELD_ID = 10;
    public const int WRITEIOCOMPLETEDTOTAL_FIELD_ID = 11;
    public const int WRITEIOTHROTTLEDTOTAL_FIELD_ID = 12;
    public const int WRITEBYTESTOTAL_FIELD_ID = 13;
    public const int WRITEIOSTALLTOTALMS_FIELD_ID = 14;
    public const int WRITEIOSTALLQUEUEDMS_FIELD_ID = 15;
    public const int IOISSUEVIOLATIONSTOTAL_FIELD_ID = 16;
    public const int IOISSUEDELAYTOTALMS_FIELD_ID = 17;
    public const int IOISSUEAHEADTOTALMS_FIELD_ID = 18;
    public const int RESERVEDIOLIMITEDBYVOLUMETOTAL_FIELD_ID = 19;
    public const int IOISSUEDELAYNONTHROTTLEDTOTALMS_FIELD_ID = 20;


    public DmResourceGovernorResourcePoolVolumesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmResourceGovernorResourcePoolVolumesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmResourceGovernorResourcePoolVolumesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int PoolId
    {
        get
        {
            return base.GetInt32(POOLID_FIELD_ID);
        }
    }

    public string VolumeName
    {
        get
        {
            return base.GetString(VOLUMENAME_FIELD_ID);
        }
    }

    public int ReadIoQueuedTotal
    {
        get
        {
            return base.GetInt32(READIOQUEUEDTOTAL_FIELD_ID);
        }
    }

    public int ReadIoIssuedTotal
    {
        get
        {
            return base.GetInt32(READIOISSUEDTOTAL_FIELD_ID);
        }
    }

    public int ReadIoCompletedTotal
    {
        get
        {
            return base.GetInt32(READIOCOMPLETEDTOTAL_FIELD_ID);
        }
    }

    public int ReadIoThrottledTotal
    {
        get
        {
            return base.GetInt32(READIOTHROTTLEDTOTAL_FIELD_ID);
        }
    }

    public long ReadBytesTotal
    {
        get
        {
            return base.GetInt64(READBYTESTOTAL_FIELD_ID);
        }
    }

    public long ReadIoStallTotalMs
    {
        get
        {
            return base.GetInt64(READIOSTALLTOTALMS_FIELD_ID);
        }
    }

    public long ReadIoStallQueuedMs
    {
        get
        {
            return base.GetInt64(READIOSTALLQUEUEDMS_FIELD_ID);
        }
    }

    public int WriteIoQueuedTotal
    {
        get
        {
            return base.GetInt32(WRITEIOQUEUEDTOTAL_FIELD_ID);
        }
    }

    public int WriteIoIssuedTotal
    {
        get
        {
            return base.GetInt32(WRITEIOISSUEDTOTAL_FIELD_ID);
        }
    }

    public int WriteIoCompletedTotal
    {
        get
        {
            return base.GetInt32(WRITEIOCOMPLETEDTOTAL_FIELD_ID);
        }
    }

    public int WriteIoThrottledTotal
    {
        get
        {
            return base.GetInt32(WRITEIOTHROTTLEDTOTAL_FIELD_ID);
        }
    }

    public long WriteBytesTotal
    {
        get
        {
            return base.GetInt64(WRITEBYTESTOTAL_FIELD_ID);
        }
    }

    public long WriteIoStallTotalMs
    {
        get
        {
            return base.GetInt64(WRITEIOSTALLTOTALMS_FIELD_ID);
        }
    }

    public long WriteIoStallQueuedMs
    {
        get
        {
            return base.GetInt64(WRITEIOSTALLQUEUEDMS_FIELD_ID);
        }
    }

    public int IoIssueViolationsTotal
    {
        get
        {
            return base.GetInt32(IOISSUEVIOLATIONSTOTAL_FIELD_ID);
        }
    }

    public long IoIssueDelayTotalMs
    {
        get
        {
            return base.GetInt64(IOISSUEDELAYTOTALMS_FIELD_ID);
        }
    }

    public long IoIssueAheadTotalMs
    {
        get
        {
            return base.GetInt64(IOISSUEAHEADTOTALMS_FIELD_ID);
        }
    }

    public int ReservedIoLimitedByVolumeTotal
    {
        get
        {
            return base.GetInt32(RESERVEDIOLIMITEDBYVOLUMETOTAL_FIELD_ID);
        }
    }

    public long? IoIssueDelayNonThrottledTotalMs
    {
        get
        {
            return base.GetNullableInt64(IOISSUEDELAYNONTHROTTLEDTOTALMS_FIELD_ID);
        }
    }


    public Types.DmResourceGovernorResourcePoolVolumesDataType ToDataObject()
    {
        return new Types.DmResourceGovernorResourcePoolVolumesDataType(PoolId,
            VolumeName,
            ReadIoQueuedTotal,
            ReadIoIssuedTotal,
            ReadIoCompletedTotal,
            ReadIoThrottledTotal,
            ReadBytesTotal,
            ReadIoStallTotalMs,
            ReadIoStallQueuedMs,
            WriteIoQueuedTotal,
            WriteIoIssuedTotal,
            WriteIoCompletedTotal,
            WriteIoThrottledTotal,
            WriteBytesTotal,
            WriteIoStallTotalMs,
            WriteIoStallQueuedMs,
            IoIssueViolationsTotal,
            IoIssueDelayTotalMs,
            IoIssueAheadTotalMs,
            ReservedIoLimitedByVolumeTotal,
            IoIssueDelayNonThrottledTotalMs);
    }

    public List<Types.DmResourceGovernorResourcePoolVolumesDataType> ToList()
    {
        var list = new List<Types.DmResourceGovernorResourcePoolVolumesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

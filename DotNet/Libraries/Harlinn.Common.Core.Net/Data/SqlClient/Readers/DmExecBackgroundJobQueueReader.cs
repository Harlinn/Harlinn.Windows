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

public class DmExecBackgroundJobQueueReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_background_job_queue]";
    public const string TableName = "dm_exec_background_job_queue";
    public const string ShortName = "debjq";
    public const string Sql = """
        SELECT
          debjq.[time_queued],
          debjq.[job_id],
          debjq.[database_id],
          debjq.[object_id1],
          debjq.[object_id2],
          debjq.[object_id3],
          debjq.[object_id4],
          debjq.[error_code],
          debjq.[request_type],
          debjq.[retry_count],
          debjq.[in_progress],
          debjq.[session_id]
        FROM
          [sys].[dm_exec_background_job_queue] debjq
        """;

    public const int TIMEQUEUED_FIELD_ID = 0;
    public const int JOBID_FIELD_ID = 1;
    public const int DATABASEID_FIELD_ID = 2;
    public const int OBJECTID1_FIELD_ID = 3;
    public const int OBJECTID2_FIELD_ID = 4;
    public const int OBJECTID3_FIELD_ID = 5;
    public const int OBJECTID4_FIELD_ID = 6;
    public const int ERRORCODE_FIELD_ID = 7;
    public const int REQUESTTYPE_FIELD_ID = 8;
    public const int RETRYCOUNT_FIELD_ID = 9;
    public const int INPROGRESS_FIELD_ID = 10;
    public const int SESSIONID_FIELD_ID = 11;


    public DmExecBackgroundJobQueueReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecBackgroundJobQueueReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecBackgroundJobQueueReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public DateTime TimeQueued
    {
        get
        {
            return base.GetDateTime(TIMEQUEUED_FIELD_ID);
        }
    }

    public int JobId
    {
        get
        {
            return base.GetInt32(JOBID_FIELD_ID);
        }
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public int ObjectId1
    {
        get
        {
            return base.GetInt32(OBJECTID1_FIELD_ID);
        }
    }

    public int ObjectId2
    {
        get
        {
            return base.GetInt32(OBJECTID2_FIELD_ID);
        }
    }

    public int ObjectId3
    {
        get
        {
            return base.GetInt32(OBJECTID3_FIELD_ID);
        }
    }

    public int ObjectId4
    {
        get
        {
            return base.GetInt32(OBJECTID4_FIELD_ID);
        }
    }

    public int? ErrorCode
    {
        get
        {
            return base.GetNullableInt32(ERRORCODE_FIELD_ID);
        }
    }

    public short RequestType
    {
        get
        {
            return base.GetInt16(REQUESTTYPE_FIELD_ID);
        }
    }

    public short RetryCount
    {
        get
        {
            return base.GetInt16(RETRYCOUNT_FIELD_ID);
        }
    }

    public short InProgress
    {
        get
        {
            return base.GetInt16(INPROGRESS_FIELD_ID);
        }
    }

    public short? SessionId
    {
        get
        {
            return base.GetNullableInt16(SESSIONID_FIELD_ID);
        }
    }


    public Types.DmExecBackgroundJobQueueDataType ToDataObject()
    {
        return new Types.DmExecBackgroundJobQueueDataType(TimeQueued,
            JobId,
            DatabaseId,
            ObjectId1,
            ObjectId2,
            ObjectId3,
            ObjectId4,
            ErrorCode,
            RequestType,
            RetryCount,
            InProgress,
            SessionId);
    }

    public List<Types.DmExecBackgroundJobQueueDataType> ToList()
    {
        var list = new List<Types.DmExecBackgroundJobQueueDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

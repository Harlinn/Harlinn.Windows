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

public class DmDbTaskSpaceUsageReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_task_space_usage]";
    public const string TableName = "dm_db_task_space_usage";
    public const string ShortName = "ddtsu";
    public const string Sql = """
        SELECT
          ddtsu.[task_address],
          ddtsu.[is_remote_task],
          ddtsu.[session_id],
          ddtsu.[request_id],
          ddtsu.[exec_context_id],
          ddtsu.[database_id],
          ddtsu.[user_objects_alloc_page_count],
          ddtsu.[user_objects_dealloc_page_count],
          ddtsu.[internal_objects_alloc_page_count],
          ddtsu.[internal_objects_dealloc_page_count]
        FROM
          [sys].[dm_db_task_space_usage] ddtsu
        """;

    public const int TASKADDRESS_FIELD_ID = 0;
    public const int ISREMOTETASK_FIELD_ID = 1;
    public const int SESSIONID_FIELD_ID = 2;
    public const int REQUESTID_FIELD_ID = 3;
    public const int EXECCONTEXTID_FIELD_ID = 4;
    public const int DATABASEID_FIELD_ID = 5;
    public const int USEROBJECTSALLOCPAGECOUNT_FIELD_ID = 6;
    public const int USEROBJECTSDEALLOCPAGECOUNT_FIELD_ID = 7;
    public const int INTERNALOBJECTSALLOCPAGECOUNT_FIELD_ID = 8;
    public const int INTERNALOBJECTSDEALLOCPAGECOUNT_FIELD_ID = 9;


    public DmDbTaskSpaceUsageReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbTaskSpaceUsageReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbTaskSpaceUsageReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[]? TaskAddress
    {
        get
        {
            return base.GetNullableBinary(TASKADDRESS_FIELD_ID);
        }
    }

    public bool IsRemoteTask
    {
        get
        {
            return base.GetBoolean(ISREMOTETASK_FIELD_ID);
        }
    }

    public short? SessionId
    {
        get
        {
            return base.GetNullableInt16(SESSIONID_FIELD_ID);
        }
    }

    public int? RequestId
    {
        get
        {
            return base.GetNullableInt32(REQUESTID_FIELD_ID);
        }
    }

    public int? ExecContextId
    {
        get
        {
            return base.GetNullableInt32(EXECCONTEXTID_FIELD_ID);
        }
    }

    public int? DatabaseId
    {
        get
        {
            return base.GetNullableInt32(DATABASEID_FIELD_ID);
        }
    }

    public long? UserObjectsAllocPageCount
    {
        get
        {
            return base.GetNullableInt64(USEROBJECTSALLOCPAGECOUNT_FIELD_ID);
        }
    }

    public long? UserObjectsDeallocPageCount
    {
        get
        {
            return base.GetNullableInt64(USEROBJECTSDEALLOCPAGECOUNT_FIELD_ID);
        }
    }

    public long? InternalObjectsAllocPageCount
    {
        get
        {
            return base.GetNullableInt64(INTERNALOBJECTSALLOCPAGECOUNT_FIELD_ID);
        }
    }

    public long? InternalObjectsDeallocPageCount
    {
        get
        {
            return base.GetNullableInt64(INTERNALOBJECTSDEALLOCPAGECOUNT_FIELD_ID);
        }
    }


    public Types.DmDbTaskSpaceUsageDataType ToDataObject()
    {
        return new Types.DmDbTaskSpaceUsageDataType(TaskAddress,
            IsRemoteTask,
            SessionId,
            RequestId,
            ExecContextId,
            DatabaseId,
            UserObjectsAllocPageCount,
            UserObjectsDeallocPageCount,
            InternalObjectsAllocPageCount,
            InternalObjectsDeallocPageCount);
    }

    public List<Types.DmDbTaskSpaceUsageDataType> ToList()
    {
        var list = new List<Types.DmDbTaskSpaceUsageDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

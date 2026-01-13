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

public class DmDbSessionSpaceUsageReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_session_space_usage]";
    public const string TableName = "dm_db_session_space_usage";
    public const string ShortName = "ddssu";
    public const string Sql = """
        SELECT
          ddssu.[session_id],
          ddssu.[database_id],
          ddssu.[user_objects_alloc_page_count],
          ddssu.[user_objects_dealloc_page_count],
          ddssu.[internal_objects_alloc_page_count],
          ddssu.[internal_objects_dealloc_page_count],
          ddssu.[user_objects_deferred_dealloc_page_count]
        FROM
          [sys].[dm_db_session_space_usage] ddssu
        """;

    public const int SESSIONID_FIELD_ID = 0;
    public const int DATABASEID_FIELD_ID = 1;
    public const int USEROBJECTSALLOCPAGECOUNT_FIELD_ID = 2;
    public const int USEROBJECTSDEALLOCPAGECOUNT_FIELD_ID = 3;
    public const int INTERNALOBJECTSALLOCPAGECOUNT_FIELD_ID = 4;
    public const int INTERNALOBJECTSDEALLOCPAGECOUNT_FIELD_ID = 5;
    public const int USEROBJECTSDEFERREDDEALLOCPAGECOUNT_FIELD_ID = 6;


    public DmDbSessionSpaceUsageReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbSessionSpaceUsageReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbSessionSpaceUsageReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short? SessionId
    {
        get
        {
            return base.GetNullableInt16(SESSIONID_FIELD_ID);
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

    public long? UserObjectsDeferredDeallocPageCount
    {
        get
        {
            return base.GetNullableInt64(USEROBJECTSDEFERREDDEALLOCPAGECOUNT_FIELD_ID);
        }
    }


    public Types.DmDbSessionSpaceUsageDataType ToDataObject()
    {
        return new Types.DmDbSessionSpaceUsageDataType(SessionId,
            DatabaseId,
            UserObjectsAllocPageCount,
            UserObjectsDeallocPageCount,
            InternalObjectsAllocPageCount,
            InternalObjectsDeallocPageCount,
            UserObjectsDeferredDeallocPageCount);
    }

    public List<Types.DmDbSessionSpaceUsageDataType> ToList()
    {
        var list = new List<Types.DmDbSessionSpaceUsageDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

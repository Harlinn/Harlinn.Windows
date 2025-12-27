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

public class DmTranVersionStoreSpaceUsageReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_version_store_space_usage]";
    public const string TableName = "dm_tran_version_store_space_usage";
    public const string ShortName = "dtvssu";
    public const string Sql = """
        SELECT
          dtvssu.[database_id],
          dtvssu.[reserved_page_count],
          dtvssu.[reserved_space_kb]
        FROM
          [sys].[dm_tran_version_store_space_usage] dtvssu
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int RESERVEDPAGECOUNT_FIELD_ID = 1;
    public const int RESERVEDSPACEKB_FIELD_ID = 2;


    public DmTranVersionStoreSpaceUsageReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranVersionStoreSpaceUsageReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranVersionStoreSpaceUsageReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? DatabaseId
    {
        get
        {
            return base.GetNullableInt32(DATABASEID_FIELD_ID);
        }
    }

    public long? ReservedPageCount
    {
        get
        {
            return base.GetNullableInt64(RESERVEDPAGECOUNT_FIELD_ID);
        }
    }

    public long? ReservedSpaceKb
    {
        get
        {
            return base.GetNullableInt64(RESERVEDSPACEKB_FIELD_ID);
        }
    }


    public Types.DmTranVersionStoreSpaceUsageDataType ToDataObject()
    {
        return new Types.DmTranVersionStoreSpaceUsageDataType(DatabaseId,
            ReservedPageCount,
            ReservedSpaceKb);
    }

    public List<Types.DmTranVersionStoreSpaceUsageDataType> ToList()
    {
        var list = new List<Types.DmTranVersionStoreSpaceUsageDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

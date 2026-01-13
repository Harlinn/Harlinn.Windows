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

public class StatsColumnsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[stats_columns]";
    public const string TableName = "stats_columns";
    public const string ShortName = "sc2";
    public const string Sql = """
        SELECT
          sc2.[object_id],
          sc2.[stats_id],
          sc2.[stats_column_id],
          sc2.[column_id]
        FROM
          [sys].[stats_columns] sc2
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int STATSID_FIELD_ID = 1;
    public const int STATSCOLUMNID_FIELD_ID = 2;
    public const int COLUMNID_FIELD_ID = 3;


    public StatsColumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public StatsColumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public StatsColumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int StatsId
    {
        get
        {
            return base.GetInt32(STATSID_FIELD_ID);
        }
    }

    public int? StatsColumnId
    {
        get
        {
            return base.GetNullableInt32(STATSCOLUMNID_FIELD_ID);
        }
    }

    public int? ColumnId
    {
        get
        {
            return base.GetNullableInt32(COLUMNID_FIELD_ID);
        }
    }


    public Types.StatsColumnsDataType ToDataObject()
    {
        return new Types.StatsColumnsDataType(ObjectId,
            StatsId,
            StatsColumnId,
            ColumnId);
    }

    public List<Types.StatsColumnsDataType> ToList()
    {
        var list = new List<Types.StatsColumnsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

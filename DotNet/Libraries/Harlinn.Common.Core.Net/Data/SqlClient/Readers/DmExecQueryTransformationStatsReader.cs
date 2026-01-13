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

public class DmExecQueryTransformationStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_query_transformation_stats]";
    public const string TableName = "dm_exec_query_transformation_stats";
    public const string ShortName = "deqts";
    public const string Sql = """
        SELECT
          deqts.[Name],
          deqts.[promise_total],
          deqts.[promise_avg],
          deqts.[Promised],
          deqts.[built_substitute],
          deqts.[Succeeded]
        FROM
          [sys].[dm_exec_query_transformation_stats] deqts
        """;

    public const int NAME_FIELD_ID = 0;
    public const int PROMISETOTAL_FIELD_ID = 1;
    public const int PROMISEAVG_FIELD_ID = 2;
    public const int PROMISED_FIELD_ID = 3;
    public const int BUILTSUBSTITUTE_FIELD_ID = 4;
    public const int SUCCEEDED_FIELD_ID = 5;


    public DmExecQueryTransformationStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryTransformationStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryTransformationStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public long PromiseTotal
    {
        get
        {
            return base.GetInt64(PROMISETOTAL_FIELD_ID);
        }
    }

    public double PromiseAvg
    {
        get
        {
            return base.GetDouble(PROMISEAVG_FIELD_ID);
        }
    }

    public long Promised
    {
        get
        {
            return base.GetInt64(PROMISED_FIELD_ID);
        }
    }

    public long BuiltSubstitute
    {
        get
        {
            return base.GetInt64(BUILTSUBSTITUTE_FIELD_ID);
        }
    }

    public long Succeeded
    {
        get
        {
            return base.GetInt64(SUCCEEDED_FIELD_ID);
        }
    }


    public Types.DmExecQueryTransformationStatsDataType ToDataObject()
    {
        return new Types.DmExecQueryTransformationStatsDataType(Name,
            PromiseTotal,
            PromiseAvg,
            Promised,
            BuiltSubstitute,
            Succeeded);
    }

    public List<Types.DmExecQueryTransformationStatsDataType> ToList()
    {
        var list = new List<Types.DmExecQueryTransformationStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

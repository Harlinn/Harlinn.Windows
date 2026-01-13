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

public class DmExecQueryOptimizerInfoReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_query_optimizer_info]";
    public const string TableName = "dm_exec_query_optimizer_info";
    public const string ShortName = "deqoi";
    public const string Sql = """
        SELECT
          deqoi.[Counter],
          deqoi.[Occurrence],
          deqoi.[Value]
        FROM
          [sys].[dm_exec_query_optimizer_info] deqoi
        """;

    public const int COUNTER_FIELD_ID = 0;
    public const int OCCURRENCE_FIELD_ID = 1;
    public const int VALUE_FIELD_ID = 2;


    public DmExecQueryOptimizerInfoReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryOptimizerInfoReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecQueryOptimizerInfoReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Counter
    {
        get
        {
            return base.GetString(COUNTER_FIELD_ID);
        }
    }

    public long Occurrence
    {
        get
        {
            return base.GetInt64(OCCURRENCE_FIELD_ID);
        }
    }

    public double? Value
    {
        get
        {
            return base.GetNullableDouble(VALUE_FIELD_ID);
        }
    }


    public Types.DmExecQueryOptimizerInfoDataType ToDataObject()
    {
        return new Types.DmExecQueryOptimizerInfoDataType(Counter,
            Occurrence,
            Value);
    }

    public List<Types.DmExecQueryOptimizerInfoDataType> ToList()
    {
        var list = new List<Types.DmExecQueryOptimizerInfoDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

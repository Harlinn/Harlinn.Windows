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

public class TraceSubclassValuesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[trace_subclass_values]";
    public const string TableName = "trace_subclass_values";
    public const string ShortName = "tsv";
    public const string Sql = """
        SELECT
          tsv.[trace_event_id],
          tsv.[trace_column_id],
          tsv.[subclass_name],
          tsv.[subclass_value]
        FROM
          [sys].[trace_subclass_values] tsv
        """;

    public const int TRACEEVENTID_FIELD_ID = 0;
    public const int TRACECOLUMNID_FIELD_ID = 1;
    public const int SUBCLASSNAME_FIELD_ID = 2;
    public const int SUBCLASSVALUE_FIELD_ID = 3;


    public TraceSubclassValuesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public TraceSubclassValuesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public TraceSubclassValuesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short TraceEventId
    {
        get
        {
            return base.GetInt16(TRACEEVENTID_FIELD_ID);
        }
    }

    public short TraceColumnId
    {
        get
        {
            return base.GetInt16(TRACECOLUMNID_FIELD_ID);
        }
    }

    public string? SubclassName
    {
        get
        {
            return base.GetNullableString(SUBCLASSNAME_FIELD_ID);
        }
    }

    public short? SubclassValue
    {
        get
        {
            return base.GetNullableInt16(SUBCLASSVALUE_FIELD_ID);
        }
    }


    public Types.TraceSubclassValue ToDataObject()
    {
        return new Types.TraceSubclassValue(TraceEventId,
            TraceColumnId,
            SubclassName,
            SubclassValue);
    }

    public List<Types.TraceSubclassValue> ToList()
    {
        var list = new List<Types.TraceSubclassValue>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

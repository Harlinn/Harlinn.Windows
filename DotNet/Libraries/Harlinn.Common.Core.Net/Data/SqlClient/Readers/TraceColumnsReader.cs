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

public class TraceColumnsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[trace_columns]";
    public const string TableName = "trace_columns";
    public const string ShortName = "tc";
    public const string Sql = """
        SELECT
          tc.[trace_column_id],
          tc.[Name],
          tc.[type_name],
          tc.[max_size],
          tc.[is_filterable],
          tc.[is_repeatable],
          tc.[is_repeated_base]
        FROM
          [sys].[trace_columns] tc
        """;

    public const int TRACECOLUMNID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int TYPENAME_FIELD_ID = 2;
    public const int MAXSIZE_FIELD_ID = 3;
    public const int ISFILTERABLE_FIELD_ID = 4;
    public const int ISREPEATABLE_FIELD_ID = 5;
    public const int ISREPEATEDBASE_FIELD_ID = 6;


    public TraceColumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public TraceColumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public TraceColumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short TraceColumnId
    {
        get
        {
            return base.GetInt16(TRACECOLUMNID_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public string? TypeName
    {
        get
        {
            return base.GetNullableString(TYPENAME_FIELD_ID);
        }
    }

    public int? MaxSize
    {
        get
        {
            return base.GetNullableInt32(MAXSIZE_FIELD_ID);
        }
    }

    public bool IsFilterable
    {
        get
        {
            return base.GetBoolean(ISFILTERABLE_FIELD_ID);
        }
    }

    public bool IsRepeatable
    {
        get
        {
            return base.GetBoolean(ISREPEATABLE_FIELD_ID);
        }
    }

    public bool IsRepeatedBase
    {
        get
        {
            return base.GetBoolean(ISREPEATEDBASE_FIELD_ID);
        }
    }


    public Types.TraceColumn ToDataObject()
    {
        return new Types.TraceColumn(TraceColumnId,
            Name,
            TypeName,
            MaxSize,
            IsFilterable,
            IsRepeatable,
            IsRepeatedBase);
    }

    public List<Types.TraceColumn> ToList()
    {
        var list = new List<Types.TraceColumn>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

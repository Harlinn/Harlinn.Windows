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

public class TraceEventBindingsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[trace_event_bindings]";
    public const string TableName = "trace_event_bindings";
    public const string ShortName = "teb";
    public const string Sql = """
        SELECT
          teb.[trace_event_id],
          teb.[trace_column_id]
        FROM
          [sys].[trace_event_bindings] teb
        """;

    public const int TRACEEVENTID_FIELD_ID = 0;
    public const int TRACECOLUMNID_FIELD_ID = 1;


    public TraceEventBindingsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public TraceEventBindingsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public TraceEventBindingsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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


    public Types.TraceEventBinding ToDataObject()
    {
        return new Types.TraceEventBinding(TraceEventId,
            TraceColumnId);
    }

    public List<Types.TraceEventBinding> ToList()
    {
        var list = new List<Types.TraceEventBinding>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

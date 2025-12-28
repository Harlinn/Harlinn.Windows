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

public class TraceCategoriesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[trace_categories]";
    public const string TableName = "trace_categories";
    public const string ShortName = "tc0";
    public const string Sql = """
        SELECT
          tc0.[category_id],
          tc0.[Name],
          tc0.[Type]
        FROM
          [sys].[trace_categories] tc0
        """;

    public const int CATEGORYID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int TYPE_FIELD_ID = 2;


    public TraceCategoriesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public TraceCategoriesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public TraceCategoriesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short CategoryId
    {
        get
        {
            return base.GetInt16(CATEGORYID_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public byte Type
    {
        get
        {
            return base.GetByte(TYPE_FIELD_ID);
        }
    }


    public Types.TraceCategory ToDataObject()
    {
        return new Types.TraceCategory(CategoryId,
            Name,
            Type);
    }

    public List<Types.TraceCategory> ToList()
    {
        var list = new List<Types.TraceCategory>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class FunctionOrderColumnsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[function_order_columns]";
    public const string TableName = "function_order_columns";
    public const string ShortName = "foc";
    public const string Sql = """
        SELECT
          foc.[object_id],
          foc.[order_column_id],
          foc.[column_id],
          foc.[is_descending]
        FROM
          [sys].[function_order_columns] foc
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int ORDERCOLUMNID_FIELD_ID = 1;
    public const int COLUMNID_FIELD_ID = 2;
    public const int ISDESCENDING_FIELD_ID = 3;


    public FunctionOrderColumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FunctionOrderColumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FunctionOrderColumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int OrderColumnId
    {
        get
        {
            return base.GetInt32(ORDERCOLUMNID_FIELD_ID);
        }
    }

    public int ColumnId
    {
        get
        {
            return base.GetInt32(COLUMNID_FIELD_ID);
        }
    }

    public bool? IsDescending
    {
        get
        {
            return base.GetNullableBoolean(ISDESCENDING_FIELD_ID);
        }
    }


    public Types.FunctionOrderColumnsDataType ToDataObject()
    {
        return new Types.FunctionOrderColumnsDataType(ObjectId,
            OrderColumnId,
            ColumnId,
            IsDescending);
    }

    public List<Types.FunctionOrderColumnsDataType> ToList()
    {
        var list = new List<Types.FunctionOrderColumnsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class ExternalTableColumnsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[external_table_columns]";
    public const string TableName = "external_table_columns";
    public const string ShortName = "etc";
    public const string Sql = """
        SELECT
          etc.[object_id],
          etc.[column_id],
          etc.[partition_column_ordinal],
          etc.[hash_column_ordinal]
        FROM
          [sys].[external_table_columns] etc
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int COLUMNID_FIELD_ID = 1;
    public const int PARTITIONCOLUMNORDINAL_FIELD_ID = 2;
    public const int HASHCOLUMNORDINAL_FIELD_ID = 3;


    public ExternalTableColumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ExternalTableColumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ExternalTableColumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int ColumnId
    {
        get
        {
            return base.GetInt32(COLUMNID_FIELD_ID);
        }
    }

    public int? PartitionColumnOrdinal
    {
        get
        {
            return base.GetNullableInt32(PARTITIONCOLUMNORDINAL_FIELD_ID);
        }
    }

    public int? HashColumnOrdinal
    {
        get
        {
            return base.GetNullableInt32(HASHCOLUMNORDINAL_FIELD_ID);
        }
    }


    public Types.ExternalTableColumnsDataType ToDataObject()
    {
        return new Types.ExternalTableColumnsDataType(ObjectId,
            ColumnId,
            PartitionColumnOrdinal,
            HashColumnOrdinal);
    }

    public List<Types.ExternalTableColumnsDataType> ToList()
    {
        var list = new List<Types.ExternalTableColumnsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

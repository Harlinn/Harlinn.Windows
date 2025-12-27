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

public class FulltextIndexColumnsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[fulltext_index_columns]";
    public const string TableName = "fulltext_index_columns";
    public const string ShortName = "fic";
    public const string Sql = """
        SELECT
          fic.[object_id],
          fic.[column_id],
          fic.[type_column_id],
          fic.[language_id],
          fic.[statistical_semantics]
        FROM
          [sys].[fulltext_index_columns] fic
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int COLUMNID_FIELD_ID = 1;
    public const int TYPECOLUMNID_FIELD_ID = 2;
    public const int LANGUAGEID_FIELD_ID = 3;
    public const int STATISTICALSEMANTICS_FIELD_ID = 4;


    public FulltextIndexColumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FulltextIndexColumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FulltextIndexColumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int? TypeColumnId
    {
        get
        {
            return base.GetNullableInt32(TYPECOLUMNID_FIELD_ID);
        }
    }

    public int LanguageId
    {
        get
        {
            return base.GetInt32(LANGUAGEID_FIELD_ID);
        }
    }

    public int StatisticalSemantics
    {
        get
        {
            return base.GetInt32(STATISTICALSEMANTICS_FIELD_ID);
        }
    }


    public Types.FulltextIndexColumnsDataType ToDataObject()
    {
        return new Types.FulltextIndexColumnsDataType(ObjectId,
            ColumnId,
            TypeColumnId,
            LanguageId,
            StatisticalSemantics);
    }

    public List<Types.FulltextIndexColumnsDataType> ToList()
    {
        var list = new List<Types.FulltextIndexColumnsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

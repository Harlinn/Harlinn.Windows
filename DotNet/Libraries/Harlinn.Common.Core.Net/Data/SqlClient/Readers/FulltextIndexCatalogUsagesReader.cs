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

public class FulltextIndexCatalogUsagesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[fulltext_index_catalog_usages]";
    public const string TableName = "fulltext_index_catalog_usages";
    public const string ShortName = "ficu";
    public const string Sql = """
        SELECT
          ficu.[object_id],
          ficu.[index_id],
          ficu.[fulltext_catalog_id]
        FROM
          [sys].[fulltext_index_catalog_usages] ficu
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int INDEXID_FIELD_ID = 1;
    public const int FULLTEXTCATALOGID_FIELD_ID = 2;


    public FulltextIndexCatalogUsagesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FulltextIndexCatalogUsagesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FulltextIndexCatalogUsagesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int? IndexId
    {
        get
        {
            return base.GetNullableInt32(INDEXID_FIELD_ID);
        }
    }

    public int FulltextCatalogId
    {
        get
        {
            return base.GetInt32(FULLTEXTCATALOGID_FIELD_ID);
        }
    }


    public Types.FulltextIndexCatalogUsagesDataType ToDataObject()
    {
        return new Types.FulltextIndexCatalogUsagesDataType(ObjectId,
            IndexId,
            FulltextCatalogId);
    }

    public List<Types.FulltextIndexCatalogUsagesDataType> ToList()
    {
        var list = new List<Types.FulltextIndexCatalogUsagesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

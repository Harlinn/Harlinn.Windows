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

public class FulltextSemanticLanguageStatisticsDatabaseReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[fulltext_semantic_language_statistics_database]";
    public const string TableName = "fulltext_semantic_language_statistics_database";
    public const string ShortName = "fslsd";
    public const string Sql = """
        SELECT
          fslsd.[database_id],
          fslsd.[register_date],
          fslsd.[registered_by],
          fslsd.[Version]
        FROM
          [sys].[fulltext_semantic_language_statistics_database] fslsd
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int REGISTERDATE_FIELD_ID = 1;
    public const int REGISTEREDBY_FIELD_ID = 2;
    public const int VERSION_FIELD_ID = 3;


    public FulltextSemanticLanguageStatisticsDatabaseReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FulltextSemanticLanguageStatisticsDatabaseReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FulltextSemanticLanguageStatisticsDatabaseReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public DateTime RegisterDate
    {
        get
        {
            return base.GetDateTime(REGISTERDATE_FIELD_ID);
        }
    }

    public int RegisteredBy
    {
        get
        {
            return base.GetInt32(REGISTEREDBY_FIELD_ID);
        }
    }

    public string Version
    {
        get
        {
            return base.GetString(VERSION_FIELD_ID);
        }
    }


    public Types.FulltextSemanticLanguageStatisticsDatabaseDataType ToDataObject()
    {
        return new Types.FulltextSemanticLanguageStatisticsDatabaseDataType(DatabaseId,
            RegisterDate,
            RegisteredBy,
            Version);
    }

    public List<Types.FulltextSemanticLanguageStatisticsDatabaseDataType> ToList()
    {
        var list = new List<Types.FulltextSemanticLanguageStatisticsDatabaseDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

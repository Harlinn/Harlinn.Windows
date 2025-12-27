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

public class FulltextSystemStopwordsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[fulltext_system_stopwords]";
    public const string TableName = "fulltext_system_stopwords";
    public const string ShortName = "fss";
    public const string Sql = """
        SELECT
          fss.[Stopword],
          fss.[language_id]
        FROM
          [sys].[fulltext_system_stopwords] fss
        """;

    public const int STOPWORD_FIELD_ID = 0;
    public const int LANGUAGEID_FIELD_ID = 1;


    public FulltextSystemStopwordsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FulltextSystemStopwordsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FulltextSystemStopwordsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? Stopword
    {
        get
        {
            return base.GetNullableString(STOPWORD_FIELD_ID);
        }
    }

    public int LanguageId
    {
        get
        {
            return base.GetInt32(LANGUAGEID_FIELD_ID);
        }
    }


    public Types.FulltextSystemStopwordsDataType ToDataObject()
    {
        return new Types.FulltextSystemStopwordsDataType(Stopword,
            LanguageId);
    }

    public List<Types.FulltextSystemStopwordsDataType> ToList()
    {
        var list = new List<Types.FulltextSystemStopwordsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

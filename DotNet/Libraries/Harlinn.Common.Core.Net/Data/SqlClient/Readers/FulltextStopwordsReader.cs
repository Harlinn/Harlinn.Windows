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

public class FulltextStopwordsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[fulltext_stopwords]";
    public const string TableName = "fulltext_stopwords";
    public const string ShortName = "fs";
    public const string Sql = """
        SELECT
          fs.[stoplist_id],
          fs.[Stopword],
          fs.[Language],
          fs.[language_id]
        FROM
          [sys].[fulltext_stopwords] fs
        """;

    public const int STOPLISTID_FIELD_ID = 0;
    public const int STOPWORD_FIELD_ID = 1;
    public const int LANGUAGE_FIELD_ID = 2;
    public const int LANGUAGEID_FIELD_ID = 3;


    public FulltextStopwordsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FulltextStopwordsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FulltextStopwordsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int StoplistId
    {
        get
        {
            return base.GetInt32(STOPLISTID_FIELD_ID);
        }
    }

    public string Stopword
    {
        get
        {
            return base.GetString(STOPWORD_FIELD_ID);
        }
    }

    public string Language
    {
        get
        {
            return base.GetString(LANGUAGE_FIELD_ID);
        }
    }

    public int LanguageId
    {
        get
        {
            return base.GetInt32(LANGUAGEID_FIELD_ID);
        }
    }


    public Types.FulltextStopwordsDataType ToDataObject()
    {
        return new Types.FulltextStopwordsDataType(StoplistId,
            Stopword,
            Language,
            LanguageId);
    }

    public List<Types.FulltextStopwordsDataType> ToList()
    {
        var list = new List<Types.FulltextStopwordsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

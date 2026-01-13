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

public class FulltextLanguagesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[fulltext_languages]";
    public const string TableName = "fulltext_languages";
    public const string ShortName = "fl";
    public const string Sql = """
        SELECT
          fl.[Lcid],
          fl.[Name]
        FROM
          [sys].[fulltext_languages] fl
        """;

    public const int LCID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;


    public FulltextLanguagesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FulltextLanguagesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FulltextLanguagesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Lcid
    {
        get
        {
            return base.GetInt32(LCID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }


    public Types.FulltextLanguagesDataType ToDataObject()
    {
        return new Types.FulltextLanguagesDataType(Lcid,
            Name);
    }

    public List<Types.FulltextLanguagesDataType> ToList()
    {
        var list = new List<Types.FulltextLanguagesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

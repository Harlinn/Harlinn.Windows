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

public class DmDbExternalLanguageStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_external_language_stats]";
    public const string TableName = "dm_db_external_language_stats";
    public const string ShortName = "ddels";
    public const string Sql = """
        SELECT
          ddels.[external_language_id],
          ddels.[is_installed]
        FROM
          [sys].[dm_db_external_language_stats] ddels
        """;

    public const int EXTERNALLANGUAGEID_FIELD_ID = 0;
    public const int ISINSTALLED_FIELD_ID = 1;


    public DmDbExternalLanguageStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbExternalLanguageStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbExternalLanguageStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ExternalLanguageId
    {
        get
        {
            return base.GetInt32(EXTERNALLANGUAGEID_FIELD_ID);
        }
    }

    public bool IsInstalled
    {
        get
        {
            return base.GetBoolean(ISINSTALLED_FIELD_ID);
        }
    }


    public Types.DmDbExternalLanguageStatsDataType ToDataObject()
    {
        return new Types.DmDbExternalLanguageStatsDataType(ExternalLanguageId,
            IsInstalled);
    }

    public List<Types.DmDbExternalLanguageStatsDataType> ToList()
    {
        var list = new List<Types.DmDbExternalLanguageStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class QueryStoreQueryTextReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[query_store_query_text]";
    public const string TableName = "query_store_query_text";
    public const string ShortName = "qsqt";
    public const string Sql = """
        SELECT
          qsqt.[query_text_id],
          qsqt.[query_sql_text],
          qsqt.[statement_sql_handle],
          qsqt.[is_part_of_encrypted_module],
          qsqt.[has_restricted_text]
        FROM
          [sys].[query_store_query_text] qsqt
        """;

    public const int QUERYTEXTID_FIELD_ID = 0;
    public const int QUERYSQLTEXT_FIELD_ID = 1;
    public const int STATEMENTSQLHANDLE_FIELD_ID = 2;
    public const int ISPARTOFENCRYPTEDMODULE_FIELD_ID = 3;
    public const int HASRESTRICTEDTEXT_FIELD_ID = 4;


    public QueryStoreQueryTextReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public QueryStoreQueryTextReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public QueryStoreQueryTextReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long QueryTextId
    {
        get
        {
            return base.GetInt64(QUERYTEXTID_FIELD_ID);
        }
    }

    public string? QuerySqlText
    {
        get
        {
            return base.GetNullableString(QUERYSQLTEXT_FIELD_ID);
        }
    }

    public byte[]? StatementSqlHandle
    {
        get
        {
            return base.GetNullableBinary(STATEMENTSQLHANDLE_FIELD_ID);
        }
    }

    public bool IsPartOfEncryptedModule
    {
        get
        {
            return base.GetBoolean(ISPARTOFENCRYPTEDMODULE_FIELD_ID);
        }
    }

    public bool HasRestrictedText
    {
        get
        {
            return base.GetBoolean(HASRESTRICTEDTEXT_FIELD_ID);
        }
    }


    public Types.QueryStoreQueryTextDataType ToDataObject()
    {
        return new Types.QueryStoreQueryTextDataType(QueryTextId,
            QuerySqlText,
            StatementSqlHandle,
            IsPartOfEncryptedModule,
            HasRestrictedText);
    }

    public List<Types.QueryStoreQueryTextDataType> ToList()
    {
        var list = new List<Types.QueryStoreQueryTextDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

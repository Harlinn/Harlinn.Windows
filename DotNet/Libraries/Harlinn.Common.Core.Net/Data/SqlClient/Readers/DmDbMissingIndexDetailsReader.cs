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

public class DmDbMissingIndexDetailsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_missing_index_details]";
    public const string TableName = "dm_db_missing_index_details";
    public const string ShortName = "ddmid";
    public const string Sql = """
        SELECT
          ddmid.[index_handle],
          ddmid.[database_id],
          ddmid.[object_id],
          ddmid.[equality_columns],
          ddmid.[inequality_columns],
          ddmid.[included_columns],
          ddmid.[Statement]
        FROM
          [sys].[dm_db_missing_index_details] ddmid
        """;

    public const int INDEXHANDLE_FIELD_ID = 0;
    public const int DATABASEID_FIELD_ID = 1;
    public const int OBJECTID_FIELD_ID = 2;
    public const int EQUALITYCOLUMNS_FIELD_ID = 3;
    public const int INEQUALITYCOLUMNS_FIELD_ID = 4;
    public const int INCLUDEDCOLUMNS_FIELD_ID = 5;
    public const int STATEMENT_FIELD_ID = 6;


    public DmDbMissingIndexDetailsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbMissingIndexDetailsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbMissingIndexDetailsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int IndexHandle
    {
        get
        {
            return base.GetInt32(INDEXHANDLE_FIELD_ID);
        }
    }

    public short DatabaseId
    {
        get
        {
            return base.GetInt16(DATABASEID_FIELD_ID);
        }
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public string? EqualityColumns
    {
        get
        {
            return base.GetNullableString(EQUALITYCOLUMNS_FIELD_ID);
        }
    }

    public string? InequalityColumns
    {
        get
        {
            return base.GetNullableString(INEQUALITYCOLUMNS_FIELD_ID);
        }
    }

    public string? IncludedColumns
    {
        get
        {
            return base.GetNullableString(INCLUDEDCOLUMNS_FIELD_ID);
        }
    }

    public string? Statement
    {
        get
        {
            return base.GetNullableString(STATEMENT_FIELD_ID);
        }
    }


    public Types.DmDbMissingIndexDetailsDataType ToDataObject()
    {
        return new Types.DmDbMissingIndexDetailsDataType(IndexHandle,
            DatabaseId,
            ObjectId,
            EqualityColumns,
            InequalityColumns,
            IncludedColumns,
            Statement);
    }

    public List<Types.DmDbMissingIndexDetailsDataType> ToList()
    {
        var list = new List<Types.DmDbMissingIndexDetailsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class PeriodsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[periods]";
    public const string TableName = "periods";
    public const string ShortName = "p";
    public const string Sql = """
        SELECT
          p.[Name],
          p.[period_type],
          p.[period_type_desc],
          p.[object_id],
          p.[start_column_id],
          p.[end_column_id]
        FROM
          [sys].[periods] p
        """;

    public const int NAME_FIELD_ID = 0;
    public const int PERIODTYPE_FIELD_ID = 1;
    public const int PERIODTYPEDESC_FIELD_ID = 2;
    public const int OBJECTID_FIELD_ID = 3;
    public const int STARTCOLUMNID_FIELD_ID = 4;
    public const int ENDCOLUMNID_FIELD_ID = 5;


    public PeriodsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public PeriodsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public PeriodsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public byte? PeriodType
    {
        get
        {
            return base.GetNullableByte(PERIODTYPE_FIELD_ID);
        }
    }

    public string? PeriodTypeDesc
    {
        get
        {
            return base.GetNullableString(PERIODTYPEDESC_FIELD_ID);
        }
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int StartColumnId
    {
        get
        {
            return base.GetInt32(STARTCOLUMNID_FIELD_ID);
        }
    }

    public int EndColumnId
    {
        get
        {
            return base.GetInt32(ENDCOLUMNID_FIELD_ID);
        }
    }


    public Types.PeriodsDataType ToDataObject()
    {
        return new Types.PeriodsDataType(Name,
            PeriodType,
            PeriodTypeDesc,
            ObjectId,
            StartColumnId,
            EndColumnId);
    }

    public List<Types.PeriodsDataType> ToList()
    {
        var list = new List<Types.PeriodsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

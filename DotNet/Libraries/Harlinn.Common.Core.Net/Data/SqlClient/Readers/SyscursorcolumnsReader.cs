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

public class SyscursorcolumnsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syscursorcolumns]";
    public const string TableName = "syscursorcolumns";
    public const string ShortName = "s20";
    public const string Sql = """
        SELECT
          s20.[cursor_handle],
          s20.[column_name],
          s20.[ordinal_position],
          s20.[column_characteristics_flags],
          s20.[column_size],
          s20.[data_type_sql],
          s20.[column_precision],
          s20.[column_scale],
          s20.[order_position],
          s20.[order_direction],
          s20.[hidden_column],
          s20.[Columnid],
          s20.[Objectid],
          s20.[Dbid],
          s20.[Dbname]
        FROM
          [sys].[syscursorcolumns] s20
        """;

    public const int CURSORHANDLE_FIELD_ID = 0;
    public const int COLUMNNAME_FIELD_ID = 1;
    public const int ORDINALPOSITION_FIELD_ID = 2;
    public const int COLUMNCHARACTERISTICSFLAGS_FIELD_ID = 3;
    public const int COLUMNSIZE_FIELD_ID = 4;
    public const int DATATYPESQL_FIELD_ID = 5;
    public const int COLUMNPRECISION_FIELD_ID = 6;
    public const int COLUMNSCALE_FIELD_ID = 7;
    public const int ORDERPOSITION_FIELD_ID = 8;
    public const int ORDERDIRECTION_FIELD_ID = 9;
    public const int HIDDENCOLUMN_FIELD_ID = 10;
    public const int COLUMNID_FIELD_ID = 11;
    public const int OBJECTID_FIELD_ID = 12;
    public const int DBID_FIELD_ID = 13;
    public const int DBNAME_FIELD_ID = 14;


    public SyscursorcolumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SyscursorcolumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SyscursorcolumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int CursorHandle
    {
        get
        {
            return base.GetInt32(CURSORHANDLE_FIELD_ID);
        }
    }

    public string? ColumnName
    {
        get
        {
            return base.GetNullableString(COLUMNNAME_FIELD_ID);
        }
    }

    public int OrdinalPosition
    {
        get
        {
            return base.GetInt32(ORDINALPOSITION_FIELD_ID);
        }
    }

    public int ColumnCharacteristicsFlags
    {
        get
        {
            return base.GetInt32(COLUMNCHARACTERISTICSFLAGS_FIELD_ID);
        }
    }

    public int ColumnSize
    {
        get
        {
            return base.GetInt32(COLUMNSIZE_FIELD_ID);
        }
    }

    public int DataTypeSql
    {
        get
        {
            return base.GetInt32(DATATYPESQL_FIELD_ID);
        }
    }

    public byte ColumnPrecision
    {
        get
        {
            return base.GetByte(COLUMNPRECISION_FIELD_ID);
        }
    }

    public byte ColumnScale
    {
        get
        {
            return base.GetByte(COLUMNSCALE_FIELD_ID);
        }
    }

    public int OrderPosition
    {
        get
        {
            return base.GetInt32(ORDERPOSITION_FIELD_ID);
        }
    }

    public string? OrderDirection
    {
        get
        {
            return base.GetNullableString(ORDERDIRECTION_FIELD_ID);
        }
    }

    public short HiddenColumn
    {
        get
        {
            return base.GetInt16(HIDDENCOLUMN_FIELD_ID);
        }
    }

    public int Columnid
    {
        get
        {
            return base.GetInt32(COLUMNID_FIELD_ID);
        }
    }

    public int Objectid
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int Dbid
    {
        get
        {
            return base.GetInt32(DBID_FIELD_ID);
        }
    }

    public string? Dbname
    {
        get
        {
            return base.GetNullableString(DBNAME_FIELD_ID);
        }
    }


    public Types.SyscursorcolumnsDataType ToDataObject()
    {
        return new Types.SyscursorcolumnsDataType(CursorHandle,
            ColumnName,
            OrdinalPosition,
            ColumnCharacteristicsFlags,
            ColumnSize,
            DataTypeSql,
            ColumnPrecision,
            ColumnScale,
            OrderPosition,
            OrderDirection,
            HiddenColumn,
            Columnid,
            Objectid,
            Dbid,
            Dbname);
    }

    public List<Types.SyscursorcolumnsDataType> ToList()
    {
        var list = new List<Types.SyscursorcolumnsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

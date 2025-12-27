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

public class SyscursorsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syscursors]";
    public const string TableName = "syscursors";
    public const string ShortName = "s18";
    public const string Sql = """
        SELECT
          s18.[cursor_handle],
          s18.[cursor_name],
          s18.[Status],
          s18.[Model],
          s18.[Concurrency],
          s18.[Scrollable],
          s18.[open_status],
          s18.[cursor_rows],
          s18.[fetch_status],
          s18.[column_count],
          s18.[row_count],
          s18.[last_operation]
        FROM
          [sys].[syscursors] s18
        """;

    public const int CURSORHANDLE_FIELD_ID = 0;
    public const int CURSORNAME_FIELD_ID = 1;
    public const int STATUS_FIELD_ID = 2;
    public const int MODEL_FIELD_ID = 3;
    public const int CONCURRENCY_FIELD_ID = 4;
    public const int SCROLLABLE_FIELD_ID = 5;
    public const int OPENSTATUS_FIELD_ID = 6;
    public const int CURSORROWS_FIELD_ID = 7;
    public const int FETCHSTATUS_FIELD_ID = 8;
    public const int COLUMNCOUNT_FIELD_ID = 9;
    public const int ROWCOUNT_FIELD_ID = 10;
    public const int LASTOPERATION_FIELD_ID = 11;


    public SyscursorsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SyscursorsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SyscursorsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public string? CursorName
    {
        get
        {
            return base.GetNullableString(CURSORNAME_FIELD_ID);
        }
    }

    public int Status
    {
        get
        {
            return base.GetInt32(STATUS_FIELD_ID);
        }
    }

    public byte Model
    {
        get
        {
            return base.GetByte(MODEL_FIELD_ID);
        }
    }

    public byte Concurrency
    {
        get
        {
            return base.GetByte(CONCURRENCY_FIELD_ID);
        }
    }

    public byte Scrollable
    {
        get
        {
            return base.GetByte(SCROLLABLE_FIELD_ID);
        }
    }

    public byte OpenStatus
    {
        get
        {
            return base.GetByte(OPENSTATUS_FIELD_ID);
        }
    }

    public decimal? CursorRows
    {
        get
        {
            return base.GetNullableDecimal(CURSORROWS_FIELD_ID);
        }
    }

    public short FetchStatus
    {
        get
        {
            return base.GetInt16(FETCHSTATUS_FIELD_ID);
        }
    }

    public short ColumnCount
    {
        get
        {
            return base.GetInt16(COLUMNCOUNT_FIELD_ID);
        }
    }

    public decimal? RowCount
    {
        get
        {
            return base.GetNullableDecimal(ROWCOUNT_FIELD_ID);
        }
    }

    public byte LastOperation
    {
        get
        {
            return base.GetByte(LASTOPERATION_FIELD_ID);
        }
    }


    public Types.SyscursorsDataType ToDataObject()
    {
        return new Types.SyscursorsDataType(CursorHandle,
            CursorName,
            Status,
            Model,
            Concurrency,
            Scrollable,
            OpenStatus,
            CursorRows,
            FetchStatus,
            ColumnCount,
            RowCount,
            LastOperation);
    }

    public List<Types.SyscursorsDataType> ToList()
    {
        var list = new List<Types.SyscursorsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

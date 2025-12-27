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

public class SysindexesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysindexes]";
    public const string TableName = "sysindexes";
    public const string ShortName = "s36";
    public const string Sql = """
        SELECT
          s36.[Id],
          s36.[Status],
          s36.[First],
          s36.[Indid],
          s36.[Root],
          s36.[Minlen],
          s36.[Keycnt],
          s36.[Groupid],
          s36.[Dpages],
          s36.[Reserved],
          s36.[Used],
          s36.[Rowcnt],
          s36.[Rowmodctr],
          s36.[Reserved3],
          s36.[Reserved4],
          s36.[Xmaxlen],
          s36.[Maxirow],
          s36.[Origfillfactor],
          s36.[Statversion],
          s36.[Reserved2],
          s36.[Firstiam],
          s36.[Impid],
          s36.[Lockflags],
          s36.[Pgmodctr],
          s36.[Keys],
          s36.[Name],
          s36.[Statblob],
          s36.[Maxlen],
          s36.[Rows]
        FROM
          [sys].[sysindexes] s36
        """;

    public const int ID_FIELD_ID = 0;
    public const int STATUS_FIELD_ID = 1;
    public const int FIRST_FIELD_ID = 2;
    public const int INDID_FIELD_ID = 3;
    public const int ROOT_FIELD_ID = 4;
    public const int MINLEN_FIELD_ID = 5;
    public const int KEYCNT_FIELD_ID = 6;
    public const int GROUPID_FIELD_ID = 7;
    public const int DPAGES_FIELD_ID = 8;
    public const int RESERVED_FIELD_ID = 9;
    public const int USED_FIELD_ID = 10;
    public const int ROWCNT_FIELD_ID = 11;
    public const int ROWMODCTR_FIELD_ID = 12;
    public const int RESERVED3_FIELD_ID = 13;
    public const int RESERVED4_FIELD_ID = 14;
    public const int XMAXLEN_FIELD_ID = 15;
    public const int MAXIROW_FIELD_ID = 16;
    public const int ORIGFILLFACTOR_FIELD_ID = 17;
    public const int STATVERSION_FIELD_ID = 18;
    public const int RESERVED2_FIELD_ID = 19;
    public const int FIRSTIAM_FIELD_ID = 20;
    public const int IMPID_FIELD_ID = 21;
    public const int LOCKFLAGS_FIELD_ID = 22;
    public const int PGMODCTR_FIELD_ID = 23;
    public const int KEYS_FIELD_ID = 24;
    public const int NAME_FIELD_ID = 25;
    public const int STATBLOB_FIELD_ID = 26;
    public const int MAXLEN_FIELD_ID = 27;
    public const int ROWS_FIELD_ID = 28;


    public SysindexesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysindexesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysindexesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Id
    {
        get
        {
            return base.GetInt32(ID_FIELD_ID);
        }
    }

    public int? Status
    {
        get
        {
            return base.GetNullableInt32(STATUS_FIELD_ID);
        }
    }

    public byte[]? First
    {
        get
        {
            return base.GetNullableBinary(FIRST_FIELD_ID);
        }
    }

    public short? Indid
    {
        get
        {
            return base.GetNullableInt16(INDID_FIELD_ID);
        }
    }

    public byte[]? Root
    {
        get
        {
            return base.GetNullableBinary(ROOT_FIELD_ID);
        }
    }

    public short? Minlen
    {
        get
        {
            return base.GetNullableInt16(MINLEN_FIELD_ID);
        }
    }

    public short? Keycnt
    {
        get
        {
            return base.GetNullableInt16(KEYCNT_FIELD_ID);
        }
    }

    public short? Groupid
    {
        get
        {
            return base.GetNullableInt16(GROUPID_FIELD_ID);
        }
    }

    public int? Dpages
    {
        get
        {
            return base.GetNullableInt32(DPAGES_FIELD_ID);
        }
    }

    public int? Reserved
    {
        get
        {
            return base.GetNullableInt32(RESERVED_FIELD_ID);
        }
    }

    public int? Used
    {
        get
        {
            return base.GetNullableInt32(USED_FIELD_ID);
        }
    }

    public long? Rowcnt
    {
        get
        {
            return base.GetNullableInt64(ROWCNT_FIELD_ID);
        }
    }

    public int? Rowmodctr
    {
        get
        {
            return base.GetNullableInt32(ROWMODCTR_FIELD_ID);
        }
    }

    public byte? Reserved3
    {
        get
        {
            return base.GetNullableByte(RESERVED3_FIELD_ID);
        }
    }

    public byte? Reserved4
    {
        get
        {
            return base.GetNullableByte(RESERVED4_FIELD_ID);
        }
    }

    public short? Xmaxlen
    {
        get
        {
            return base.GetNullableInt16(XMAXLEN_FIELD_ID);
        }
    }

    public short? Maxirow
    {
        get
        {
            return base.GetNullableInt16(MAXIROW_FIELD_ID);
        }
    }

    public byte? Origfillfactor
    {
        get
        {
            return base.GetNullableByte(ORIGFILLFACTOR_FIELD_ID);
        }
    }

    public byte? Statversion
    {
        get
        {
            return base.GetNullableByte(STATVERSION_FIELD_ID);
        }
    }

    public int? Reserved2
    {
        get
        {
            return base.GetNullableInt32(RESERVED2_FIELD_ID);
        }
    }

    public byte[]? Firstiam
    {
        get
        {
            return base.GetNullableBinary(FIRSTIAM_FIELD_ID);
        }
    }

    public short? Impid
    {
        get
        {
            return base.GetNullableInt16(IMPID_FIELD_ID);
        }
    }

    public short? Lockflags
    {
        get
        {
            return base.GetNullableInt16(LOCKFLAGS_FIELD_ID);
        }
    }

    public int? Pgmodctr
    {
        get
        {
            return base.GetNullableInt32(PGMODCTR_FIELD_ID);
        }
    }

    public byte[]? Keys
    {
        get
        {
            return base.GetNullableBinary(KEYS_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public byte[]? Statblob
    {
        get
        {
            return base.GetNullableBinary(STATBLOB_FIELD_ID);
        }
    }

    public int? Maxlen
    {
        get
        {
            return base.GetNullableInt32(MAXLEN_FIELD_ID);
        }
    }

    public int? Rows
    {
        get
        {
            return base.GetNullableInt32(ROWS_FIELD_ID);
        }
    }


    public Types.SysindexesDataType ToDataObject()
    {
        return new Types.SysindexesDataType(Id,
            Status,
            First,
            Indid,
            Root,
            Minlen,
            Keycnt,
            Groupid,
            Dpages,
            Reserved,
            Used,
            Rowcnt,
            Rowmodctr,
            Reserved3,
            Reserved4,
            Xmaxlen,
            Maxirow,
            Origfillfactor,
            Statversion,
            Reserved2,
            Firstiam,
            Impid,
            Lockflags,
            Pgmodctr,
            Keys,
            Name,
            Statblob,
            Maxlen,
            Rows);
    }

    public List<Types.SysindexesDataType> ToList()
    {
        var list = new List<Types.SysindexesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

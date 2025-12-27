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

public class SyscolumnsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syscolumns]";
    public const string TableName = "syscolumns";
    public const string ShortName = "s42";
    public const string Sql = """
        SELECT
          s42.[Name],
          s42.[Id],
          s42.[Xtype],
          s42.[Typestat],
          s42.[Xusertype],
          s42.[Length],
          s42.[Xprec],
          s42.[Xscale],
          s42.[Colid],
          s42.[Xoffset],
          s42.[Bitpos],
          s42.[Reserved],
          s42.[Colstat],
          s42.[Cdefault],
          s42.[Domain],
          s42.[Number],
          s42.[Colorder],
          s42.[Autoval],
          s42.[Offset],
          s42.[Collationid],
          s42.[Language],
          s42.[Status],
          s42.[Type],
          s42.[Usertype],
          s42.[Printfmt],
          s42.[Prec],
          s42.[Scale],
          s42.[Iscomputed],
          s42.[Isoutparam],
          s42.[Isnullable],
          s42.[Collation],
          s42.[Tdscollation]
        FROM
          [sys].[syscolumns] s42
        """;

    public const int NAME_FIELD_ID = 0;
    public const int ID_FIELD_ID = 1;
    public const int XTYPE_FIELD_ID = 2;
    public const int TYPESTAT_FIELD_ID = 3;
    public const int XUSERTYPE_FIELD_ID = 4;
    public const int LENGTH_FIELD_ID = 5;
    public const int XPREC_FIELD_ID = 6;
    public const int XSCALE_FIELD_ID = 7;
    public const int COLID_FIELD_ID = 8;
    public const int XOFFSET_FIELD_ID = 9;
    public const int BITPOS_FIELD_ID = 10;
    public const int RESERVED_FIELD_ID = 11;
    public const int COLSTAT_FIELD_ID = 12;
    public const int CDEFAULT_FIELD_ID = 13;
    public const int DOMAIN_FIELD_ID = 14;
    public const int NUMBER_FIELD_ID = 15;
    public const int COLORDER_FIELD_ID = 16;
    public const int AUTOVAL_FIELD_ID = 17;
    public const int OFFSET_FIELD_ID = 18;
    public const int COLLATIONID_FIELD_ID = 19;
    public const int LANGUAGE_FIELD_ID = 20;
    public const int STATUS_FIELD_ID = 21;
    public const int TYPE_FIELD_ID = 22;
    public const int USERTYPE_FIELD_ID = 23;
    public const int PRINTFMT_FIELD_ID = 24;
    public const int PREC_FIELD_ID = 25;
    public const int SCALE_FIELD_ID = 26;
    public const int ISCOMPUTED_FIELD_ID = 27;
    public const int ISOUTPARAM_FIELD_ID = 28;
    public const int ISNULLABLE_FIELD_ID = 29;
    public const int COLLATION_FIELD_ID = 30;
    public const int TDSCOLLATION_FIELD_ID = 31;


    public SyscolumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SyscolumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SyscolumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int Id
    {
        get
        {
            return base.GetInt32(ID_FIELD_ID);
        }
    }

    public byte Xtype
    {
        get
        {
            return base.GetByte(XTYPE_FIELD_ID);
        }
    }

    public byte? Typestat
    {
        get
        {
            return base.GetNullableByte(TYPESTAT_FIELD_ID);
        }
    }

    public short? Xusertype
    {
        get
        {
            return base.GetNullableInt16(XUSERTYPE_FIELD_ID);
        }
    }

    public short Length
    {
        get
        {
            return base.GetInt16(LENGTH_FIELD_ID);
        }
    }

    public byte Xprec
    {
        get
        {
            return base.GetByte(XPREC_FIELD_ID);
        }
    }

    public byte Xscale
    {
        get
        {
            return base.GetByte(XSCALE_FIELD_ID);
        }
    }

    public short? Colid
    {
        get
        {
            return base.GetNullableInt16(COLID_FIELD_ID);
        }
    }

    public short? Xoffset
    {
        get
        {
            return base.GetNullableInt16(XOFFSET_FIELD_ID);
        }
    }

    public byte? Bitpos
    {
        get
        {
            return base.GetNullableByte(BITPOS_FIELD_ID);
        }
    }

    public byte? Reserved
    {
        get
        {
            return base.GetNullableByte(RESERVED_FIELD_ID);
        }
    }

    public short? Colstat
    {
        get
        {
            return base.GetNullableInt16(COLSTAT_FIELD_ID);
        }
    }

    public int Cdefault
    {
        get
        {
            return base.GetInt32(CDEFAULT_FIELD_ID);
        }
    }

    public int Domain
    {
        get
        {
            return base.GetInt32(DOMAIN_FIELD_ID);
        }
    }

    public short? Number
    {
        get
        {
            return base.GetNullableInt16(NUMBER_FIELD_ID);
        }
    }

    public short? Colorder
    {
        get
        {
            return base.GetNullableInt16(COLORDER_FIELD_ID);
        }
    }

    public byte[]? Autoval
    {
        get
        {
            return base.GetNullableBinary(AUTOVAL_FIELD_ID);
        }
    }

    public short? Offset
    {
        get
        {
            return base.GetNullableInt16(OFFSET_FIELD_ID);
        }
    }

    public int? Collationid
    {
        get
        {
            return base.GetNullableInt32(COLLATIONID_FIELD_ID);
        }
    }

    public int? Language
    {
        get
        {
            return base.GetNullableInt32(LANGUAGE_FIELD_ID);
        }
    }

    public byte? Status
    {
        get
        {
            return base.GetNullableByte(STATUS_FIELD_ID);
        }
    }

    public byte Type
    {
        get
        {
            return base.GetByte(TYPE_FIELD_ID);
        }
    }

    public short? Usertype
    {
        get
        {
            return base.GetNullableInt16(USERTYPE_FIELD_ID);
        }
    }

    public string? Printfmt
    {
        get
        {
            return base.GetNullableString(PRINTFMT_FIELD_ID);
        }
    }

    public short? Prec
    {
        get
        {
            return base.GetNullableInt16(PREC_FIELD_ID);
        }
    }

    public int? Scale
    {
        get
        {
            return base.GetNullableInt32(SCALE_FIELD_ID);
        }
    }

    public int? Iscomputed
    {
        get
        {
            return base.GetNullableInt32(ISCOMPUTED_FIELD_ID);
        }
    }

    public int? Isoutparam
    {
        get
        {
            return base.GetNullableInt32(ISOUTPARAM_FIELD_ID);
        }
    }

    public int? Isnullable
    {
        get
        {
            return base.GetNullableInt32(ISNULLABLE_FIELD_ID);
        }
    }

    public string? Collation
    {
        get
        {
            return base.GetNullableString(COLLATION_FIELD_ID);
        }
    }

    public byte[]? Tdscollation
    {
        get
        {
            return base.GetNullableBinary(TDSCOLLATION_FIELD_ID);
        }
    }


    public Types.SyscolumnsDataType ToDataObject()
    {
        return new Types.SyscolumnsDataType(Name,
            Id,
            Xtype,
            Typestat,
            Xusertype,
            Length,
            Xprec,
            Xscale,
            Colid,
            Xoffset,
            Bitpos,
            Reserved,
            Colstat,
            Cdefault,
            Domain,
            Number,
            Colorder,
            Autoval,
            Offset,
            Collationid,
            Language,
            Status,
            Type,
            Usertype,
            Printfmt,
            Prec,
            Scale,
            Iscomputed,
            Isoutparam,
            Isnullable,
            Collation,
            Tdscollation);
    }

    public List<Types.SyscolumnsDataType> ToList()
    {
        var list = new List<Types.SyscolumnsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

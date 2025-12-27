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

public class SystypesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[systypes]";
    public const string TableName = "systypes";
    public const string ShortName = "s31";
    public const string Sql = """
        SELECT
          s31.[Name],
          s31.[Xtype],
          s31.[Status],
          s31.[Xusertype],
          s31.[Length],
          s31.[Xprec],
          s31.[Xscale],
          s31.[Tdefault],
          s31.[Domain],
          s31.[Uid],
          s31.[Reserved],
          s31.[Collationid],
          s31.[Usertype],
          s31.[Variable],
          s31.[Allownulls],
          s31.[Type],
          s31.[Printfmt],
          s31.[Prec],
          s31.[Scale],
          s31.[Collation]
        FROM
          [sys].[systypes] s31
        """;

    public const int NAME_FIELD_ID = 0;
    public const int XTYPE_FIELD_ID = 1;
    public const int STATUS_FIELD_ID = 2;
    public const int XUSERTYPE_FIELD_ID = 3;
    public const int LENGTH_FIELD_ID = 4;
    public const int XPREC_FIELD_ID = 5;
    public const int XSCALE_FIELD_ID = 6;
    public const int TDEFAULT_FIELD_ID = 7;
    public const int DOMAIN_FIELD_ID = 8;
    public const int UID_FIELD_ID = 9;
    public const int RESERVED_FIELD_ID = 10;
    public const int COLLATIONID_FIELD_ID = 11;
    public const int USERTYPE_FIELD_ID = 12;
    public const int VARIABLE_FIELD_ID = 13;
    public const int ALLOWNULLS_FIELD_ID = 14;
    public const int TYPE_FIELD_ID = 15;
    public const int PRINTFMT_FIELD_ID = 16;
    public const int PREC_FIELD_ID = 17;
    public const int SCALE_FIELD_ID = 18;
    public const int COLLATION_FIELD_ID = 19;


    public SystypesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SystypesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SystypesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public byte Xtype
    {
        get
        {
            return base.GetByte(XTYPE_FIELD_ID);
        }
    }

    public byte? Status
    {
        get
        {
            return base.GetNullableByte(STATUS_FIELD_ID);
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

    public int Tdefault
    {
        get
        {
            return base.GetInt32(TDEFAULT_FIELD_ID);
        }
    }

    public int Domain
    {
        get
        {
            return base.GetInt32(DOMAIN_FIELD_ID);
        }
    }

    public short? Uid
    {
        get
        {
            return base.GetNullableInt16(UID_FIELD_ID);
        }
    }

    public short? Reserved
    {
        get
        {
            return base.GetNullableInt16(RESERVED_FIELD_ID);
        }
    }

    public int? Collationid
    {
        get
        {
            return base.GetNullableInt32(COLLATIONID_FIELD_ID);
        }
    }

    public short? Usertype
    {
        get
        {
            return base.GetNullableInt16(USERTYPE_FIELD_ID);
        }
    }

    public bool Variable
    {
        get
        {
            return base.GetBoolean(VARIABLE_FIELD_ID);
        }
    }

    public bool? Allownulls
    {
        get
        {
            return base.GetNullableBoolean(ALLOWNULLS_FIELD_ID);
        }
    }

    public byte Type
    {
        get
        {
            return base.GetByte(TYPE_FIELD_ID);
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

    public byte? Scale
    {
        get
        {
            return base.GetNullableByte(SCALE_FIELD_ID);
        }
    }

    public string? Collation
    {
        get
        {
            return base.GetNullableString(COLLATION_FIELD_ID);
        }
    }


    public Types.SystypesDataType ToDataObject()
    {
        return new Types.SystypesDataType(Name,
            Xtype,
            Status,
            Xusertype,
            Length,
            Xprec,
            Xscale,
            Tdefault,
            Domain,
            Uid,
            Reserved,
            Collationid,
            Usertype,
            Variable,
            Allownulls,
            Type,
            Printfmt,
            Prec,
            Scale,
            Collation);
    }

    public List<Types.SystypesDataType> ToList()
    {
        var list = new List<Types.SystypesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

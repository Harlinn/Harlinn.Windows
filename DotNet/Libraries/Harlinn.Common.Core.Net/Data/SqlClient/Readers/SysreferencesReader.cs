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

public class SysreferencesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysreferences]";
    public const string TableName = "sysreferences";
    public const string ShortName = "s32";
    public const string Sql = """
        SELECT
          s32.[Constid],
          s32.[Fkeyid],
          s32.[Rkeyid],
          s32.[Rkeyindid],
          s32.[Keycnt],
          s32.[Forkeys],
          s32.[Refkeys],
          s32.[Fkeydbid],
          s32.[Rkeydbid],
          s32.[Fkey1],
          s32.[Fkey2],
          s32.[Fkey3],
          s32.[Fkey4],
          s32.[Fkey5],
          s32.[Fkey6],
          s32.[Fkey7],
          s32.[Fkey8],
          s32.[Fkey9],
          s32.[Fkey10],
          s32.[Fkey11],
          s32.[Fkey12],
          s32.[Fkey13],
          s32.[Fkey14],
          s32.[Fkey15],
          s32.[Fkey16],
          s32.[Rkey1],
          s32.[Rkey2],
          s32.[Rkey3],
          s32.[Rkey4],
          s32.[Rkey5],
          s32.[Rkey6],
          s32.[Rkey7],
          s32.[Rkey8],
          s32.[Rkey9],
          s32.[Rkey10],
          s32.[Rkey11],
          s32.[Rkey12],
          s32.[Rkey13],
          s32.[Rkey14],
          s32.[Rkey15],
          s32.[Rkey16]
        FROM
          [sys].[sysreferences] s32
        """;

    public const int CONSTID_FIELD_ID = 0;
    public const int FKEYID_FIELD_ID = 1;
    public const int RKEYID_FIELD_ID = 2;
    public const int RKEYINDID_FIELD_ID = 3;
    public const int KEYCNT_FIELD_ID = 4;
    public const int FORKEYS_FIELD_ID = 5;
    public const int REFKEYS_FIELD_ID = 6;
    public const int FKEYDBID_FIELD_ID = 7;
    public const int RKEYDBID_FIELD_ID = 8;
    public const int FKEY1_FIELD_ID = 9;
    public const int FKEY2_FIELD_ID = 10;
    public const int FKEY3_FIELD_ID = 11;
    public const int FKEY4_FIELD_ID = 12;
    public const int FKEY5_FIELD_ID = 13;
    public const int FKEY6_FIELD_ID = 14;
    public const int FKEY7_FIELD_ID = 15;
    public const int FKEY8_FIELD_ID = 16;
    public const int FKEY9_FIELD_ID = 17;
    public const int FKEY10_FIELD_ID = 18;
    public const int FKEY11_FIELD_ID = 19;
    public const int FKEY12_FIELD_ID = 20;
    public const int FKEY13_FIELD_ID = 21;
    public const int FKEY14_FIELD_ID = 22;
    public const int FKEY15_FIELD_ID = 23;
    public const int FKEY16_FIELD_ID = 24;
    public const int RKEY1_FIELD_ID = 25;
    public const int RKEY2_FIELD_ID = 26;
    public const int RKEY3_FIELD_ID = 27;
    public const int RKEY4_FIELD_ID = 28;
    public const int RKEY5_FIELD_ID = 29;
    public const int RKEY6_FIELD_ID = 30;
    public const int RKEY7_FIELD_ID = 31;
    public const int RKEY8_FIELD_ID = 32;
    public const int RKEY9_FIELD_ID = 33;
    public const int RKEY10_FIELD_ID = 34;
    public const int RKEY11_FIELD_ID = 35;
    public const int RKEY12_FIELD_ID = 36;
    public const int RKEY13_FIELD_ID = 37;
    public const int RKEY14_FIELD_ID = 38;
    public const int RKEY15_FIELD_ID = 39;
    public const int RKEY16_FIELD_ID = 40;


    public SysreferencesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysreferencesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysreferencesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Constid
    {
        get
        {
            return base.GetInt32(CONSTID_FIELD_ID);
        }
    }

    public int Fkeyid
    {
        get
        {
            return base.GetInt32(FKEYID_FIELD_ID);
        }
    }

    public int? Rkeyid
    {
        get
        {
            return base.GetNullableInt32(RKEYID_FIELD_ID);
        }
    }

    public short? Rkeyindid
    {
        get
        {
            return base.GetNullableInt16(RKEYINDID_FIELD_ID);
        }
    }

    public short? Keycnt
    {
        get
        {
            return base.GetNullableInt16(KEYCNT_FIELD_ID);
        }
    }

    public byte[]? Forkeys
    {
        get
        {
            return base.GetNullableBinary(FORKEYS_FIELD_ID);
        }
    }

    public byte[]? Refkeys
    {
        get
        {
            return base.GetNullableBinary(REFKEYS_FIELD_ID);
        }
    }

    public short? Fkeydbid
    {
        get
        {
            return base.GetNullableInt16(FKEYDBID_FIELD_ID);
        }
    }

    public short? Rkeydbid
    {
        get
        {
            return base.GetNullableInt16(RKEYDBID_FIELD_ID);
        }
    }

    public short? Fkey1
    {
        get
        {
            return base.GetNullableInt16(FKEY1_FIELD_ID);
        }
    }

    public short? Fkey2
    {
        get
        {
            return base.GetNullableInt16(FKEY2_FIELD_ID);
        }
    }

    public short? Fkey3
    {
        get
        {
            return base.GetNullableInt16(FKEY3_FIELD_ID);
        }
    }

    public short? Fkey4
    {
        get
        {
            return base.GetNullableInt16(FKEY4_FIELD_ID);
        }
    }

    public short? Fkey5
    {
        get
        {
            return base.GetNullableInt16(FKEY5_FIELD_ID);
        }
    }

    public short? Fkey6
    {
        get
        {
            return base.GetNullableInt16(FKEY6_FIELD_ID);
        }
    }

    public short? Fkey7
    {
        get
        {
            return base.GetNullableInt16(FKEY7_FIELD_ID);
        }
    }

    public short? Fkey8
    {
        get
        {
            return base.GetNullableInt16(FKEY8_FIELD_ID);
        }
    }

    public short? Fkey9
    {
        get
        {
            return base.GetNullableInt16(FKEY9_FIELD_ID);
        }
    }

    public short? Fkey10
    {
        get
        {
            return base.GetNullableInt16(FKEY10_FIELD_ID);
        }
    }

    public short? Fkey11
    {
        get
        {
            return base.GetNullableInt16(FKEY11_FIELD_ID);
        }
    }

    public short? Fkey12
    {
        get
        {
            return base.GetNullableInt16(FKEY12_FIELD_ID);
        }
    }

    public short? Fkey13
    {
        get
        {
            return base.GetNullableInt16(FKEY13_FIELD_ID);
        }
    }

    public short? Fkey14
    {
        get
        {
            return base.GetNullableInt16(FKEY14_FIELD_ID);
        }
    }

    public short? Fkey15
    {
        get
        {
            return base.GetNullableInt16(FKEY15_FIELD_ID);
        }
    }

    public short? Fkey16
    {
        get
        {
            return base.GetNullableInt16(FKEY16_FIELD_ID);
        }
    }

    public short? Rkey1
    {
        get
        {
            return base.GetNullableInt16(RKEY1_FIELD_ID);
        }
    }

    public short? Rkey2
    {
        get
        {
            return base.GetNullableInt16(RKEY2_FIELD_ID);
        }
    }

    public short? Rkey3
    {
        get
        {
            return base.GetNullableInt16(RKEY3_FIELD_ID);
        }
    }

    public short? Rkey4
    {
        get
        {
            return base.GetNullableInt16(RKEY4_FIELD_ID);
        }
    }

    public short? Rkey5
    {
        get
        {
            return base.GetNullableInt16(RKEY5_FIELD_ID);
        }
    }

    public short? Rkey6
    {
        get
        {
            return base.GetNullableInt16(RKEY6_FIELD_ID);
        }
    }

    public short? Rkey7
    {
        get
        {
            return base.GetNullableInt16(RKEY7_FIELD_ID);
        }
    }

    public short? Rkey8
    {
        get
        {
            return base.GetNullableInt16(RKEY8_FIELD_ID);
        }
    }

    public short? Rkey9
    {
        get
        {
            return base.GetNullableInt16(RKEY9_FIELD_ID);
        }
    }

    public short? Rkey10
    {
        get
        {
            return base.GetNullableInt16(RKEY10_FIELD_ID);
        }
    }

    public short? Rkey11
    {
        get
        {
            return base.GetNullableInt16(RKEY11_FIELD_ID);
        }
    }

    public short? Rkey12
    {
        get
        {
            return base.GetNullableInt16(RKEY12_FIELD_ID);
        }
    }

    public short? Rkey13
    {
        get
        {
            return base.GetNullableInt16(RKEY13_FIELD_ID);
        }
    }

    public short? Rkey14
    {
        get
        {
            return base.GetNullableInt16(RKEY14_FIELD_ID);
        }
    }

    public short? Rkey15
    {
        get
        {
            return base.GetNullableInt16(RKEY15_FIELD_ID);
        }
    }

    public short? Rkey16
    {
        get
        {
            return base.GetNullableInt16(RKEY16_FIELD_ID);
        }
    }


    public Types.SysreferencesDataType ToDataObject()
    {
        return new Types.SysreferencesDataType(Constid,
            Fkeyid,
            Rkeyid,
            Rkeyindid,
            Keycnt,
            Forkeys,
            Refkeys,
            Fkeydbid,
            Rkeydbid,
            Fkey1,
            Fkey2,
            Fkey3,
            Fkey4,
            Fkey5,
            Fkey6,
            Fkey7,
            Fkey8,
            Fkey9,
            Fkey10,
            Fkey11,
            Fkey12,
            Fkey13,
            Fkey14,
            Fkey15,
            Fkey16,
            Rkey1,
            Rkey2,
            Rkey3,
            Rkey4,
            Rkey5,
            Rkey6,
            Rkey7,
            Rkey8,
            Rkey9,
            Rkey10,
            Rkey11,
            Rkey12,
            Rkey13,
            Rkey14,
            Rkey15,
            Rkey16);
    }

    public List<Types.SysreferencesDataType> ToList()
    {
        var list = new List<Types.SysreferencesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

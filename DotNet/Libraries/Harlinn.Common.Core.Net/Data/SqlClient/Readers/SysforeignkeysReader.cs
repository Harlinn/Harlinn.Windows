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

public class SysforeignkeysReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysforeignkeys]";
    public const string TableName = "sysforeignkeys";
    public const string ShortName = "s39";
    public const string Sql = """
        SELECT
          s39.[Constid],
          s39.[Fkeyid],
          s39.[Rkeyid],
          s39.[Fkey],
          s39.[Rkey],
          s39.[Keyno]
        FROM
          [sys].[sysforeignkeys] s39
        """;

    public const int CONSTID_FIELD_ID = 0;
    public const int FKEYID_FIELD_ID = 1;
    public const int RKEYID_FIELD_ID = 2;
    public const int FKEY_FIELD_ID = 3;
    public const int RKEY_FIELD_ID = 4;
    public const int KEYNO_FIELD_ID = 5;


    public SysforeignkeysReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysforeignkeysReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysforeignkeysReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int Rkeyid
    {
        get
        {
            return base.GetInt32(RKEYID_FIELD_ID);
        }
    }

    public short? Fkey
    {
        get
        {
            return base.GetNullableInt16(FKEY_FIELD_ID);
        }
    }

    public short? Rkey
    {
        get
        {
            return base.GetNullableInt16(RKEY_FIELD_ID);
        }
    }

    public short? Keyno
    {
        get
        {
            return base.GetNullableInt16(KEYNO_FIELD_ID);
        }
    }


    public Types.SysforeignkeysDataType ToDataObject()
    {
        return new Types.SysforeignkeysDataType(Constid,
            Fkeyid,
            Rkeyid,
            Fkey,
            Rkey,
            Keyno);
    }

    public List<Types.SysforeignkeysDataType> ToList()
    {
        var list = new List<Types.SysforeignkeysDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

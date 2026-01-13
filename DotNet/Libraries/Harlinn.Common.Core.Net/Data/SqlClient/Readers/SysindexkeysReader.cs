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

public class SysindexkeysReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysindexkeys]";
    public const string TableName = "sysindexkeys";
    public const string ShortName = "s35";
    public const string Sql = """
        SELECT
          s35.[Id],
          s35.[Indid],
          s35.[Colid],
          s35.[Keyno]
        FROM
          [sys].[sysindexkeys] s35
        """;

    public const int ID_FIELD_ID = 0;
    public const int INDID_FIELD_ID = 1;
    public const int COLID_FIELD_ID = 2;
    public const int KEYNO_FIELD_ID = 3;


    public SysindexkeysReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysindexkeysReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysindexkeysReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public short? Indid
    {
        get
        {
            return base.GetNullableInt16(INDID_FIELD_ID);
        }
    }

    public short? Colid
    {
        get
        {
            return base.GetNullableInt16(COLID_FIELD_ID);
        }
    }

    public short? Keyno
    {
        get
        {
            return base.GetNullableInt16(KEYNO_FIELD_ID);
        }
    }


    public Types.SysindexkeysDataType ToDataObject()
    {
        return new Types.SysindexkeysDataType(Id,
            Indid,
            Colid,
            Keyno);
    }

    public List<Types.SysindexkeysDataType> ToList()
    {
        var list = new List<Types.SysindexkeysDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

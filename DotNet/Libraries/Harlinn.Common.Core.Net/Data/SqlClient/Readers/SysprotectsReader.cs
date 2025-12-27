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

public class SysprotectsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysprotects]";
    public const string TableName = "sysprotects";
    public const string ShortName = "s33";
    public const string Sql = """
        SELECT
          s33.[Id],
          s33.[Uid],
          s33.[Action],
          s33.[Protecttype],
          s33.[Columns],
          s33.[Grantor]
        FROM
          [sys].[sysprotects] s33
        """;

    public const int ID_FIELD_ID = 0;
    public const int UID_FIELD_ID = 1;
    public const int ACTION_FIELD_ID = 2;
    public const int PROTECTTYPE_FIELD_ID = 3;
    public const int COLUMNS_FIELD_ID = 4;
    public const int GRANTOR_FIELD_ID = 5;


    public SysprotectsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysprotectsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysprotectsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public short? Uid
    {
        get
        {
            return base.GetNullableInt16(UID_FIELD_ID);
        }
    }

    public byte? Action
    {
        get
        {
            return base.GetNullableByte(ACTION_FIELD_ID);
        }
    }

    public byte? Protecttype
    {
        get
        {
            return base.GetNullableByte(PROTECTTYPE_FIELD_ID);
        }
    }

    public byte[]? Columns
    {
        get
        {
            return base.GetNullableBinary(COLUMNS_FIELD_ID);
        }
    }

    public short? Grantor
    {
        get
        {
            return base.GetNullableInt16(GRANTOR_FIELD_ID);
        }
    }


    public Types.SysprotectsDataType ToDataObject()
    {
        return new Types.SysprotectsDataType(Id,
            Uid,
            Action,
            Protecttype,
            Columns,
            Grantor);
    }

    public List<Types.SysprotectsDataType> ToList()
    {
        var list = new List<Types.SysprotectsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

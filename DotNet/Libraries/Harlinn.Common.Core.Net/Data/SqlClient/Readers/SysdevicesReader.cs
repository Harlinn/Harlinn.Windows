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

public class SysdevicesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysdevices]";
    public const string TableName = "sysdevices";
    public const string ShortName = "s15";
    public const string Sql = """
        SELECT
          s15.[Name],
          s15.[Size],
          s15.[Low],
          s15.[High],
          s15.[Status],
          s15.[Cntrltype],
          s15.[Phyname]
        FROM
          [sys].[sysdevices] s15
        """;

    public const int NAME_FIELD_ID = 0;
    public const int SIZE_FIELD_ID = 1;
    public const int LOW_FIELD_ID = 2;
    public const int HIGH_FIELD_ID = 3;
    public const int STATUS_FIELD_ID = 4;
    public const int CNTRLTYPE_FIELD_ID = 5;
    public const int PHYNAME_FIELD_ID = 6;


    public SysdevicesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysdevicesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysdevicesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int? Size
    {
        get
        {
            return base.GetNullableInt32(SIZE_FIELD_ID);
        }
    }

    public int? Low
    {
        get
        {
            return base.GetNullableInt32(LOW_FIELD_ID);
        }
    }

    public int? High
    {
        get
        {
            return base.GetNullableInt32(HIGH_FIELD_ID);
        }
    }

    public short? Status
    {
        get
        {
            return base.GetNullableInt16(STATUS_FIELD_ID);
        }
    }

    public short? Cntrltype
    {
        get
        {
            return base.GetNullableInt16(CNTRLTYPE_FIELD_ID);
        }
    }

    public string? Phyname
    {
        get
        {
            return base.GetNullableString(PHYNAME_FIELD_ID);
        }
    }


    public Types.SysdevicesDataType ToDataObject()
    {
        return new Types.SysdevicesDataType(Name,
            Size,
            Low,
            High,
            Status,
            Cntrltype,
            Phyname);
    }

    public List<Types.SysdevicesDataType> ToList()
    {
        var list = new List<Types.SysdevicesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

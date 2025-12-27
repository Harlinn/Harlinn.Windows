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

public class SysoledbusersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysoledbusers]";
    public const string TableName = "sysoledbusers";
    public const string ShortName = "s11";
    public const string Sql = """
        SELECT
          s11.[Rmtsrvid],
          s11.[Rmtloginame],
          s11.[Rmtpassword],
          s11.[Loginsid],
          s11.[Status],
          s11.[Changedate]
        FROM
          [sys].[sysoledbusers] s11
        """;

    public const int RMTSRVID_FIELD_ID = 0;
    public const int RMTLOGINAME_FIELD_ID = 1;
    public const int RMTPASSWORD_FIELD_ID = 2;
    public const int LOGINSID_FIELD_ID = 3;
    public const int STATUS_FIELD_ID = 4;
    public const int CHANGEDATE_FIELD_ID = 5;


    public SysoledbusersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysoledbusersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysoledbusersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short? Rmtsrvid
    {
        get
        {
            return base.GetNullableInt16(RMTSRVID_FIELD_ID);
        }
    }

    public string? Rmtloginame
    {
        get
        {
            return base.GetNullableString(RMTLOGINAME_FIELD_ID);
        }
    }

    public string? Rmtpassword
    {
        get
        {
            return base.GetNullableString(RMTPASSWORD_FIELD_ID);
        }
    }

    public byte[]? Loginsid
    {
        get
        {
            return base.GetNullableBinary(LOGINSID_FIELD_ID);
        }
    }

    public short? Status
    {
        get
        {
            return base.GetNullableInt16(STATUS_FIELD_ID);
        }
    }

    public DateTime Changedate
    {
        get
        {
            return base.GetDateTime(CHANGEDATE_FIELD_ID);
        }
    }


    public Types.SysoledbusersDataType ToDataObject()
    {
        return new Types.SysoledbusersDataType(Rmtsrvid,
            Rmtloginame,
            Rmtpassword,
            Loginsid,
            Status,
            Changedate);
    }

    public List<Types.SysoledbusersDataType> ToList()
    {
        var list = new List<Types.SysoledbusersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

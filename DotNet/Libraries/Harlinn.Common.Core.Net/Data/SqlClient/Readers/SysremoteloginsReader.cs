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

public class SysremoteloginsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysremotelogins]";
    public const string TableName = "sysremotelogins";
    public const string ShortName = "s7";
    public const string Sql = """
        SELECT
          s7.[Remoteserverid],
          s7.[Remoteusername],
          s7.[Status],
          s7.[Sid],
          s7.[Changedate]
        FROM
          [sys].[sysremotelogins] s7
        """;

    public const int REMOTESERVERID_FIELD_ID = 0;
    public const int REMOTEUSERNAME_FIELD_ID = 1;
    public const int STATUS_FIELD_ID = 2;
    public const int SID_FIELD_ID = 3;
    public const int CHANGEDATE_FIELD_ID = 4;


    public SysremoteloginsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysremoteloginsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysremoteloginsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short? Remoteserverid
    {
        get
        {
            return base.GetNullableInt16(REMOTESERVERID_FIELD_ID);
        }
    }

    public string? Remoteusername
    {
        get
        {
            return base.GetNullableString(REMOTEUSERNAME_FIELD_ID);
        }
    }

    public short? Status
    {
        get
        {
            return base.GetNullableInt16(STATUS_FIELD_ID);
        }
    }

    public byte[]? Sid
    {
        get
        {
            return base.GetNullableBinary(SID_FIELD_ID);
        }
    }

    public DateTime Changedate
    {
        get
        {
            return base.GetDateTime(CHANGEDATE_FIELD_ID);
        }
    }


    public Types.SysremoteloginsDataType ToDataObject()
    {
        return new Types.SysremoteloginsDataType(Remoteserverid,
            Remoteusername,
            Status,
            Sid,
            Changedate);
    }

    public List<Types.SysremoteloginsDataType> ToList()
    {
        var list = new List<Types.SysremoteloginsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

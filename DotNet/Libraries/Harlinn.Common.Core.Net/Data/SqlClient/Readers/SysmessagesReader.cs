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

public class SysmessagesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysmessages]";
    public const string TableName = "sysmessages";
    public const string ShortName = "s12";
    public const string Sql = """
        SELECT
          s12.[Error],
          s12.[Severity],
          s12.[Dlevel],
          s12.[Description],
          s12.[Msglangid]
        FROM
          [sys].[sysmessages] s12
        """;

    public const int ERROR_FIELD_ID = 0;
    public const int SEVERITY_FIELD_ID = 1;
    public const int DLEVEL_FIELD_ID = 2;
    public const int DESCRIPTION_FIELD_ID = 3;
    public const int MSGLANGID_FIELD_ID = 4;


    public SysmessagesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysmessagesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysmessagesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Error
    {
        get
        {
            return base.GetInt32(ERROR_FIELD_ID);
        }
    }

    public byte? Severity
    {
        get
        {
            return base.GetNullableByte(SEVERITY_FIELD_ID);
        }
    }

    public short? Dlevel
    {
        get
        {
            return base.GetNullableInt16(DLEVEL_FIELD_ID);
        }
    }

    public string? Description
    {
        get
        {
            return base.GetNullableString(DESCRIPTION_FIELD_ID);
        }
    }

    public short Msglangid
    {
        get
        {
            return base.GetInt16(MSGLANGID_FIELD_ID);
        }
    }


    public Types.SysmessagesDataType ToDataObject()
    {
        return new Types.SysmessagesDataType(Error,
            Severity,
            Dlevel,
            Description,
            Msglangid);
    }

    public List<Types.SysmessagesDataType> ToList()
    {
        var list = new List<Types.SysmessagesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

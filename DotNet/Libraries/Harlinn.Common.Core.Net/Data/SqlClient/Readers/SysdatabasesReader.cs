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

public class SysdatabasesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysdatabases]";
    public const string TableName = "sysdatabases";
    public const string ShortName = "s16";
    public const string Sql = """
        SELECT
          s16.[Name],
          s16.[Dbid],
          s16.[Sid],
          s16.[Mode],
          s16.[Status],
          s16.[Status2],
          s16.[Crdate],
          s16.[Reserved],
          s16.[Category],
          s16.[Cmptlevel],
          s16.[Filename],
          s16.[Version]
        FROM
          [sys].[sysdatabases] s16
        """;

    public const int NAME_FIELD_ID = 0;
    public const int DBID_FIELD_ID = 1;
    public const int SID_FIELD_ID = 2;
    public const int MODE_FIELD_ID = 3;
    public const int STATUS_FIELD_ID = 4;
    public const int STATUS2_FIELD_ID = 5;
    public const int CRDATE_FIELD_ID = 6;
    public const int RESERVED_FIELD_ID = 7;
    public const int CATEGORY_FIELD_ID = 8;
    public const int CMPTLEVEL_FIELD_ID = 9;
    public const int FILENAME_FIELD_ID = 10;
    public const int VERSION_FIELD_ID = 11;


    public SysdatabasesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysdatabasesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysdatabasesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public short? Dbid
    {
        get
        {
            return base.GetNullableInt16(DBID_FIELD_ID);
        }
    }

    public byte[]? Sid
    {
        get
        {
            return base.GetNullableBinary(SID_FIELD_ID);
        }
    }

    public short? Mode
    {
        get
        {
            return base.GetNullableInt16(MODE_FIELD_ID);
        }
    }

    public int? Status
    {
        get
        {
            return base.GetNullableInt32(STATUS_FIELD_ID);
        }
    }

    public int? Status2
    {
        get
        {
            return base.GetNullableInt32(STATUS2_FIELD_ID);
        }
    }

    public DateTime Crdate
    {
        get
        {
            return base.GetDateTime(CRDATE_FIELD_ID);
        }
    }

    public DateTime? Reserved
    {
        get
        {
            return base.GetNullableDateTime(RESERVED_FIELD_ID);
        }
    }

    public int? Category
    {
        get
        {
            return base.GetNullableInt32(CATEGORY_FIELD_ID);
        }
    }

    public byte Cmptlevel
    {
        get
        {
            return base.GetByte(CMPTLEVEL_FIELD_ID);
        }
    }

    public string? Filename
    {
        get
        {
            return base.GetNullableString(FILENAME_FIELD_ID);
        }
    }

    public short? Version
    {
        get
        {
            return base.GetNullableInt16(VERSION_FIELD_ID);
        }
    }


    public Types.SysdatabasesDataType ToDataObject()
    {
        return new Types.SysdatabasesDataType(Name,
            Dbid,
            Sid,
            Mode,
            Status,
            Status2,
            Crdate,
            Reserved,
            Category,
            Cmptlevel,
            Filename,
            Version);
    }

    public List<Types.SysdatabasesDataType> ToList()
    {
        var list = new List<Types.SysdatabasesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

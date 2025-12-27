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

public class SysaltfilesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysaltfiles]";
    public const string TableName = "sysaltfiles";
    public const string ShortName = "s26";
    public const string Sql = """
        SELECT
          s26.[Fileid],
          s26.[Groupid],
          s26.[Size],
          s26.[Maxsize],
          s26.[Growth],
          s26.[Status],
          s26.[Perf],
          s26.[Dbid],
          s26.[Name],
          s26.[Filename]
        FROM
          [sys].[sysaltfiles] s26
        """;

    public const int FILEID_FIELD_ID = 0;
    public const int GROUPID_FIELD_ID = 1;
    public const int SIZE_FIELD_ID = 2;
    public const int MAXSIZE_FIELD_ID = 3;
    public const int GROWTH_FIELD_ID = 4;
    public const int STATUS_FIELD_ID = 5;
    public const int PERF_FIELD_ID = 6;
    public const int DBID_FIELD_ID = 7;
    public const int NAME_FIELD_ID = 8;
    public const int FILENAME_FIELD_ID = 9;


    public SysaltfilesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysaltfilesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysaltfilesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short? Fileid
    {
        get
        {
            return base.GetNullableInt16(FILEID_FIELD_ID);
        }
    }

    public short? Groupid
    {
        get
        {
            return base.GetNullableInt16(GROUPID_FIELD_ID);
        }
    }

    public int Size
    {
        get
        {
            return base.GetInt32(SIZE_FIELD_ID);
        }
    }

    public int Maxsize
    {
        get
        {
            return base.GetInt32(MAXSIZE_FIELD_ID);
        }
    }

    public int Growth
    {
        get
        {
            return base.GetInt32(GROWTH_FIELD_ID);
        }
    }

    public int? Status
    {
        get
        {
            return base.GetNullableInt32(STATUS_FIELD_ID);
        }
    }

    public int? Perf
    {
        get
        {
            return base.GetNullableInt32(PERF_FIELD_ID);
        }
    }

    public short? Dbid
    {
        get
        {
            return base.GetNullableInt16(DBID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public string? Filename
    {
        get
        {
            return base.GetNullableString(FILENAME_FIELD_ID);
        }
    }


    public Types.SysaltfilesDataType ToDataObject()
    {
        return new Types.SysaltfilesDataType(Fileid,
            Groupid,
            Size,
            Maxsize,
            Growth,
            Status,
            Perf,
            Dbid,
            Name,
            Filename);
    }

    public List<Types.SysaltfilesDataType> ToList()
    {
        var list = new List<Types.SysaltfilesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

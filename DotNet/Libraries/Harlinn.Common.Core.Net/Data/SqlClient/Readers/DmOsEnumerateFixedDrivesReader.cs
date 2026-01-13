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

public class DmOsEnumerateFixedDrivesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_enumerate_fixed_drives]";
    public const string TableName = "dm_os_enumerate_fixed_drives";
    public const string ShortName = "doefd";
    public const string Sql = """
        SELECT
          doefd.[fixed_drive_path],
          doefd.[drive_type],
          doefd.[drive_type_desc],
          doefd.[free_space_in_bytes]
        FROM
          [sys].[dm_os_enumerate_fixed_drives] doefd
        """;

    public const int FIXEDDRIVEPATH_FIELD_ID = 0;
    public const int DRIVETYPE_FIELD_ID = 1;
    public const int DRIVETYPEDESC_FIELD_ID = 2;
    public const int FREESPACEINBYTES_FIELD_ID = 3;


    public DmOsEnumerateFixedDrivesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsEnumerateFixedDrivesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsEnumerateFixedDrivesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? FixedDrivePath
    {
        get
        {
            return base.GetNullableString(FIXEDDRIVEPATH_FIELD_ID);
        }
    }

    public int DriveType
    {
        get
        {
            return base.GetInt32(DRIVETYPE_FIELD_ID);
        }
    }

    public string? DriveTypeDesc
    {
        get
        {
            return base.GetNullableString(DRIVETYPEDESC_FIELD_ID);
        }
    }

    public long FreeSpaceInBytes
    {
        get
        {
            return base.GetInt64(FREESPACEINBYTES_FIELD_ID);
        }
    }


    public Types.DmOsEnumerateFixedDrivesDataType ToDataObject()
    {
        return new Types.DmOsEnumerateFixedDrivesDataType(FixedDrivePath,
            DriveType,
            DriveTypeDesc,
            FreeSpaceInBytes);
    }

    public List<Types.DmOsEnumerateFixedDrivesDataType> ToList()
    {
        var list = new List<Types.DmOsEnumerateFixedDrivesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

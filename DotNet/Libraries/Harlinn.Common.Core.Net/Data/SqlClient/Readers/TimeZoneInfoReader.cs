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

public class TimeZoneInfoReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[time_zone_info]";
    public const string TableName = "time_zone_info";
    public const string ShortName = "tzi";
    public const string Sql = """
        SELECT
          tzi.[Name],
          tzi.[current_utc_offset],
          tzi.[is_currently_dst]
        FROM
          [sys].[time_zone_info] tzi
        """;

    public const int NAME_FIELD_ID = 0;
    public const int CURRENTUTCOFFSET_FIELD_ID = 1;
    public const int ISCURRENTLYDST_FIELD_ID = 2;


    public TimeZoneInfoReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public TimeZoneInfoReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public TimeZoneInfoReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public string CurrentUtcOffset
    {
        get
        {
            return base.GetString(CURRENTUTCOFFSET_FIELD_ID);
        }
    }

    public bool IsCurrentlyDst
    {
        get
        {
            return base.GetBoolean(ISCURRENTLYDST_FIELD_ID);
        }
    }


    public Types.TimeZoneInfoDataType ToDataObject()
    {
        return new Types.TimeZoneInfoDataType(Name,
            CurrentUtcOffset,
            IsCurrentlyDst);
    }

    public List<Types.TimeZoneInfoDataType> ToList()
    {
        var list = new List<Types.TimeZoneInfoDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

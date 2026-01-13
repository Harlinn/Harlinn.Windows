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

public class DmOsWindowsInfoReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_windows_info]";
    public const string TableName = "dm_os_windows_info";
    public const string ShortName = "dowi";
    public const string Sql = """
        SELECT
          dowi.[windows_release],
          dowi.[windows_service_pack_level],
          dowi.[windows_sku],
          dowi.[os_language_version]
        FROM
          [sys].[dm_os_windows_info] dowi
        """;

    public const int WINDOWSRELEASE_FIELD_ID = 0;
    public const int WINDOWSSERVICEPACKLEVEL_FIELD_ID = 1;
    public const int WINDOWSSKU_FIELD_ID = 2;
    public const int OSLANGUAGEVERSION_FIELD_ID = 3;


    public DmOsWindowsInfoReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsWindowsInfoReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsWindowsInfoReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string WindowsRelease
    {
        get
        {
            return base.GetString(WINDOWSRELEASE_FIELD_ID);
        }
    }

    public string WindowsServicePackLevel
    {
        get
        {
            return base.GetString(WINDOWSSERVICEPACKLEVEL_FIELD_ID);
        }
    }

    public int? WindowsSku
    {
        get
        {
            return base.GetNullableInt32(WINDOWSSKU_FIELD_ID);
        }
    }

    public int OsLanguageVersion
    {
        get
        {
            return base.GetInt32(OSLANGUAGEVERSION_FIELD_ID);
        }
    }


    public Types.DmOsWindowsInfoDataType ToDataObject()
    {
        return new Types.DmOsWindowsInfoDataType(WindowsRelease,
            WindowsServicePackLevel,
            WindowsSku,
            OsLanguageVersion);
    }

    public List<Types.DmOsWindowsInfoDataType> ToList()
    {
        var list = new List<Types.DmOsWindowsInfoDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

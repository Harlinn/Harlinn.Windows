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

public class DmOsHostInfoReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_host_info]";
    public const string TableName = "dm_os_host_info";
    public const string ShortName = "dohi";
    public const string Sql = """
        SELECT
          dohi.[host_platform],
          dohi.[host_distribution],
          dohi.[host_release],
          dohi.[host_service_pack_level],
          dohi.[host_sku],
          dohi.[os_language_version],
          dohi.[host_architecture]
        FROM
          [sys].[dm_os_host_info] dohi
        """;

    public const int HOSTPLATFORM_FIELD_ID = 0;
    public const int HOSTDISTRIBUTION_FIELD_ID = 1;
    public const int HOSTRELEASE_FIELD_ID = 2;
    public const int HOSTSERVICEPACKLEVEL_FIELD_ID = 3;
    public const int HOSTSKU_FIELD_ID = 4;
    public const int OSLANGUAGEVERSION_FIELD_ID = 5;
    public const int HOSTARCHITECTURE_FIELD_ID = 6;


    public DmOsHostInfoReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsHostInfoReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsHostInfoReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string HostPlatform
    {
        get
        {
            return base.GetString(HOSTPLATFORM_FIELD_ID);
        }
    }

    public string HostDistribution
    {
        get
        {
            return base.GetString(HOSTDISTRIBUTION_FIELD_ID);
        }
    }

    public string HostRelease
    {
        get
        {
            return base.GetString(HOSTRELEASE_FIELD_ID);
        }
    }

    public string HostServicePackLevel
    {
        get
        {
            return base.GetString(HOSTSERVICEPACKLEVEL_FIELD_ID);
        }
    }

    public int? HostSku
    {
        get
        {
            return base.GetNullableInt32(HOSTSKU_FIELD_ID);
        }
    }

    public int OsLanguageVersion
    {
        get
        {
            return base.GetInt32(OSLANGUAGEVERSION_FIELD_ID);
        }
    }

    public string HostArchitecture
    {
        get
        {
            return base.GetString(HOSTARCHITECTURE_FIELD_ID);
        }
    }


    public Types.DmOsHostInfoDataType ToDataObject()
    {
        return new Types.DmOsHostInfoDataType(HostPlatform,
            HostDistribution,
            HostRelease,
            HostServicePackLevel,
            HostSku,
            OsLanguageVersion,
            HostArchitecture);
    }

    public List<Types.DmOsHostInfoDataType> ToList()
    {
        var list = new List<Types.DmOsHostInfoDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

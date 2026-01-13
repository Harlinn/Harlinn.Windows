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

public class DmOsClusterPropertiesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_cluster_properties]";
    public const string TableName = "dm_os_cluster_properties";
    public const string ShortName = "docp";
    public const string Sql = """
        SELECT
          docp.[Verboselogging],
          docp.[Sqldumperdumpflags],
          docp.[Sqldumperdumppath],
          docp.[Sqldumperdumptimeout],
          docp.[Failureconditionlevel],
          docp.[Healthchecktimeout]
        FROM
          [sys].[dm_os_cluster_properties] docp
        """;

    public const int VERBOSELOGGING_FIELD_ID = 0;
    public const int SQLDUMPERDUMPFLAGS_FIELD_ID = 1;
    public const int SQLDUMPERDUMPPATH_FIELD_ID = 2;
    public const int SQLDUMPERDUMPTIMEOUT_FIELD_ID = 3;
    public const int FAILURECONDITIONLEVEL_FIELD_ID = 4;
    public const int HEALTHCHECKTIMEOUT_FIELD_ID = 5;


    public DmOsClusterPropertiesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsClusterPropertiesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsClusterPropertiesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long? Verboselogging
    {
        get
        {
            return base.GetNullableInt64(VERBOSELOGGING_FIELD_ID);
        }
    }

    public long? Sqldumperdumpflags
    {
        get
        {
            return base.GetNullableInt64(SQLDUMPERDUMPFLAGS_FIELD_ID);
        }
    }

    public string Sqldumperdumppath
    {
        get
        {
            return base.GetString(SQLDUMPERDUMPPATH_FIELD_ID);
        }
    }

    public long? Sqldumperdumptimeout
    {
        get
        {
            return base.GetNullableInt64(SQLDUMPERDUMPTIMEOUT_FIELD_ID);
        }
    }

    public long? Failureconditionlevel
    {
        get
        {
            return base.GetNullableInt64(FAILURECONDITIONLEVEL_FIELD_ID);
        }
    }

    public long? Healthchecktimeout
    {
        get
        {
            return base.GetNullableInt64(HEALTHCHECKTIMEOUT_FIELD_ID);
        }
    }


    public Types.DmOsClusterPropertiesDataType ToDataObject()
    {
        return new Types.DmOsClusterPropertiesDataType(Verboselogging,
            Sqldumperdumpflags,
            Sqldumperdumppath,
            Sqldumperdumptimeout,
            Failureconditionlevel,
            Healthchecktimeout);
    }

    public List<Types.DmOsClusterPropertiesDataType> ToList()
    {
        var list = new List<Types.DmOsClusterPropertiesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

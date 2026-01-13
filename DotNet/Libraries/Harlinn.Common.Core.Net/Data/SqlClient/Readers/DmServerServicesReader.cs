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

public class DmServerServicesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_server_services]";
    public const string TableName = "dm_server_services";
    public const string ShortName = "dss";
    public const string Sql = """
        SELECT
          dss.[Servicename],
          dss.[startup_type],
          dss.[startup_type_desc],
          dss.[Status],
          dss.[status_desc],
          dss.[process_id],
          dss.[last_startup_time],
          dss.[service_account],
          dss.[Filename],
          dss.[is_clustered],
          dss.[cluster_nodename],
          dss.[instant_file_initialization_enabled]
        FROM
          [sys].[dm_server_services] dss
        """;

    public const int SERVICENAME_FIELD_ID = 0;
    public const int STARTUPTYPE_FIELD_ID = 1;
    public const int STARTUPTYPEDESC_FIELD_ID = 2;
    public const int STATUS_FIELD_ID = 3;
    public const int STATUSDESC_FIELD_ID = 4;
    public const int PROCESSID_FIELD_ID = 5;
    public const int LASTSTARTUPTIME_FIELD_ID = 6;
    public const int SERVICEACCOUNT_FIELD_ID = 7;
    public const int FILENAME_FIELD_ID = 8;
    public const int ISCLUSTERED_FIELD_ID = 9;
    public const int CLUSTERNODENAME_FIELD_ID = 10;
    public const int INSTANTFILEINITIALIZATIONENABLED_FIELD_ID = 11;


    public DmServerServicesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmServerServicesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmServerServicesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Servicename
    {
        get
        {
            return base.GetString(SERVICENAME_FIELD_ID);
        }
    }

    public int? StartupType
    {
        get
        {
            return base.GetNullableInt32(STARTUPTYPE_FIELD_ID);
        }
    }

    public string StartupTypeDesc
    {
        get
        {
            return base.GetString(STARTUPTYPEDESC_FIELD_ID);
        }
    }

    public int? Status
    {
        get
        {
            return base.GetNullableInt32(STATUS_FIELD_ID);
        }
    }

    public string StatusDesc
    {
        get
        {
            return base.GetString(STATUSDESC_FIELD_ID);
        }
    }

    public int? ProcessId
    {
        get
        {
            return base.GetNullableInt32(PROCESSID_FIELD_ID);
        }
    }

    public DateTime? LastStartupTime
    {
        get
        {
            return base.GetNullableDateTime(LASTSTARTUPTIME_FIELD_ID);
        }
    }

    public string ServiceAccount
    {
        get
        {
            return base.GetString(SERVICEACCOUNT_FIELD_ID);
        }
    }

    public string Filename
    {
        get
        {
            return base.GetString(FILENAME_FIELD_ID);
        }
    }

    public string IsClustered
    {
        get
        {
            return base.GetString(ISCLUSTERED_FIELD_ID);
        }
    }

    public string? ClusterNodename
    {
        get
        {
            return base.GetNullableString(CLUSTERNODENAME_FIELD_ID);
        }
    }

    public string InstantFileInitializationEnabled
    {
        get
        {
            return base.GetString(INSTANTFILEINITIALIZATIONENABLED_FIELD_ID);
        }
    }


    public Types.DmServerServicesDataType ToDataObject()
    {
        return new Types.DmServerServicesDataType(Servicename,
            StartupType,
            StartupTypeDesc,
            Status,
            StatusDesc,
            ProcessId,
            LastStartupTime,
            ServiceAccount,
            Filename,
            IsClustered,
            ClusterNodename,
            InstantFileInitializationEnabled);
    }

    public List<Types.DmServerServicesDataType> ToList()
    {
        var list = new List<Types.DmServerServicesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

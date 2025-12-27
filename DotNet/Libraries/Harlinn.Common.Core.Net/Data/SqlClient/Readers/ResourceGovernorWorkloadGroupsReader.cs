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

public class ResourceGovernorWorkloadGroupsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[resource_governor_workload_groups]";
    public const string TableName = "resource_governor_workload_groups";
    public const string ShortName = "rgwg";
    public const string Sql = """
        SELECT
          rgwg.[group_id],
          rgwg.[Name],
          rgwg.[Importance],
          rgwg.[request_max_memory_grant_percent],
          rgwg.[request_max_cpu_time_sec],
          rgwg.[request_memory_grant_timeout_sec],
          rgwg.[max_dop],
          rgwg.[group_max_requests],
          rgwg.[pool_id],
          rgwg.[external_pool_id],
          rgwg.[request_max_memory_grant_percent_numeric]
        FROM
          [sys].[resource_governor_workload_groups] rgwg
        """;

    public const int GROUPID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int IMPORTANCE_FIELD_ID = 2;
    public const int REQUESTMAXMEMORYGRANTPERCENT_FIELD_ID = 3;
    public const int REQUESTMAXCPUTIMESEC_FIELD_ID = 4;
    public const int REQUESTMEMORYGRANTTIMEOUTSEC_FIELD_ID = 5;
    public const int MAXDOP_FIELD_ID = 6;
    public const int GROUPMAXREQUESTS_FIELD_ID = 7;
    public const int POOLID_FIELD_ID = 8;
    public const int EXTERNALPOOLID_FIELD_ID = 9;
    public const int REQUESTMAXMEMORYGRANTPERCENTNUMERIC_FIELD_ID = 10;


    public ResourceGovernorWorkloadGroupsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ResourceGovernorWorkloadGroupsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ResourceGovernorWorkloadGroupsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int GroupId
    {
        get
        {
            return base.GetInt32(GROUPID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public string Importance
    {
        get
        {
            return base.GetString(IMPORTANCE_FIELD_ID);
        }
    }

    public int RequestMaxMemoryGrantPercent
    {
        get
        {
            return base.GetInt32(REQUESTMAXMEMORYGRANTPERCENT_FIELD_ID);
        }
    }

    public int RequestMaxCpuTimeSec
    {
        get
        {
            return base.GetInt32(REQUESTMAXCPUTIMESEC_FIELD_ID);
        }
    }

    public int RequestMemoryGrantTimeoutSec
    {
        get
        {
            return base.GetInt32(REQUESTMEMORYGRANTTIMEOUTSEC_FIELD_ID);
        }
    }

    public int MaxDop
    {
        get
        {
            return base.GetInt32(MAXDOP_FIELD_ID);
        }
    }

    public int GroupMaxRequests
    {
        get
        {
            return base.GetInt32(GROUPMAXREQUESTS_FIELD_ID);
        }
    }

    public int PoolId
    {
        get
        {
            return base.GetInt32(POOLID_FIELD_ID);
        }
    }

    public int ExternalPoolId
    {
        get
        {
            return base.GetInt32(EXTERNALPOOLID_FIELD_ID);
        }
    }

    public double RequestMaxMemoryGrantPercentNumeric
    {
        get
        {
            return base.GetDouble(REQUESTMAXMEMORYGRANTPERCENTNUMERIC_FIELD_ID);
        }
    }


    public Types.ResourceGovernorWorkloadGroupsDataType ToDataObject()
    {
        return new Types.ResourceGovernorWorkloadGroupsDataType(GroupId,
            Name,
            Importance,
            RequestMaxMemoryGrantPercent,
            RequestMaxCpuTimeSec,
            RequestMemoryGrantTimeoutSec,
            MaxDop,
            GroupMaxRequests,
            PoolId,
            ExternalPoolId,
            RequestMaxMemoryGrantPercentNumeric);
    }

    public List<Types.ResourceGovernorWorkloadGroupsDataType> ToList()
    {
        var list = new List<Types.ResourceGovernorWorkloadGroupsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

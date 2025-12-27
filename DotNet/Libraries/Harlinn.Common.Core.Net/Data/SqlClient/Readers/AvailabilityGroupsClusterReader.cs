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

public class AvailabilityGroupsClusterReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[availability_groups_cluster]";
    public const string TableName = "availability_groups_cluster";
    public const string ShortName = "agc";
    public const string Sql = """
        SELECT
          agc.[group_id],
          agc.[Name],
          agc.[resource_id],
          agc.[resource_group_id],
          agc.[failure_condition_level],
          agc.[health_check_timeout],
          agc.[automated_backup_preference],
          agc.[automated_backup_preference_desc]
        FROM
          [sys].[availability_groups_cluster] agc
        """;

    public const int GROUPID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int RESOURCEID_FIELD_ID = 2;
    public const int RESOURCEGROUPID_FIELD_ID = 3;
    public const int FAILURECONDITIONLEVEL_FIELD_ID = 4;
    public const int HEALTHCHECKTIMEOUT_FIELD_ID = 5;
    public const int AUTOMATEDBACKUPPREFERENCE_FIELD_ID = 6;
    public const int AUTOMATEDBACKUPPREFERENCEDESC_FIELD_ID = 7;


    public AvailabilityGroupsClusterReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AvailabilityGroupsClusterReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AvailabilityGroupsClusterReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid GroupId
    {
        get
        {
            return base.GetGuid(GROUPID_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public string? ResourceId
    {
        get
        {
            return base.GetNullableString(RESOURCEID_FIELD_ID);
        }
    }

    public string? ResourceGroupId
    {
        get
        {
            return base.GetNullableString(RESOURCEGROUPID_FIELD_ID);
        }
    }

    public int? FailureConditionLevel
    {
        get
        {
            return base.GetNullableInt32(FAILURECONDITIONLEVEL_FIELD_ID);
        }
    }

    public int? HealthCheckTimeout
    {
        get
        {
            return base.GetNullableInt32(HEALTHCHECKTIMEOUT_FIELD_ID);
        }
    }

    public byte? AutomatedBackupPreference
    {
        get
        {
            return base.GetNullableByte(AUTOMATEDBACKUPPREFERENCE_FIELD_ID);
        }
    }

    public string? AutomatedBackupPreferenceDesc
    {
        get
        {
            return base.GetNullableString(AUTOMATEDBACKUPPREFERENCEDESC_FIELD_ID);
        }
    }


    public Types.AvailabilityGroupsClusterDataType ToDataObject()
    {
        return new Types.AvailabilityGroupsClusterDataType(GroupId,
            Name,
            ResourceId,
            ResourceGroupId,
            FailureConditionLevel,
            HealthCheckTimeout,
            AutomatedBackupPreference,
            AutomatedBackupPreferenceDesc);
    }

    public List<Types.AvailabilityGroupsClusterDataType> ToList()
    {
        var list = new List<Types.AvailabilityGroupsClusterDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

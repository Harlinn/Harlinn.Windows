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

public class AvailabilityGroupsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[availability_groups]";
    public const string TableName = "availability_groups";
    public const string ShortName = "ag";
    public const string Sql = """
        SELECT
          ag.[group_id],
          ag.[Name],
          ag.[resource_id],
          ag.[resource_group_id],
          ag.[failure_condition_level],
          ag.[health_check_timeout],
          ag.[automated_backup_preference],
          ag.[automated_backup_preference_desc],
          ag.[Version],
          ag.[basic_features],
          ag.[dtc_support],
          ag.[db_failover],
          ag.[is_distributed],
          ag.[cluster_type],
          ag.[cluster_type_desc],
          ag.[required_synchronized_secondaries_to_commit],
          ag.[sequence_number],
          ag.[is_contained]
        FROM
          [sys].[availability_groups] ag
        """;

    public const int GROUPID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int RESOURCEID_FIELD_ID = 2;
    public const int RESOURCEGROUPID_FIELD_ID = 3;
    public const int FAILURECONDITIONLEVEL_FIELD_ID = 4;
    public const int HEALTHCHECKTIMEOUT_FIELD_ID = 5;
    public const int AUTOMATEDBACKUPPREFERENCE_FIELD_ID = 6;
    public const int AUTOMATEDBACKUPPREFERENCEDESC_FIELD_ID = 7;
    public const int VERSION_FIELD_ID = 8;
    public const int BASICFEATURES_FIELD_ID = 9;
    public const int DTCSUPPORT_FIELD_ID = 10;
    public const int DBFAILOVER_FIELD_ID = 11;
    public const int ISDISTRIBUTED_FIELD_ID = 12;
    public const int CLUSTERTYPE_FIELD_ID = 13;
    public const int CLUSTERTYPEDESC_FIELD_ID = 14;
    public const int REQUIREDSYNCHRONIZEDSECONDARIESTOCOMMIT_FIELD_ID = 15;
    public const int SEQUENCENUMBER_FIELD_ID = 16;
    public const int ISCONTAINED_FIELD_ID = 17;


    public AvailabilityGroupsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AvailabilityGroupsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AvailabilityGroupsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public short? Version
    {
        get
        {
            return base.GetNullableInt16(VERSION_FIELD_ID);
        }
    }

    public bool? BasicFeatures
    {
        get
        {
            return base.GetNullableBoolean(BASICFEATURES_FIELD_ID);
        }
    }

    public bool? DtcSupport
    {
        get
        {
            return base.GetNullableBoolean(DTCSUPPORT_FIELD_ID);
        }
    }

    public bool? DbFailover
    {
        get
        {
            return base.GetNullableBoolean(DBFAILOVER_FIELD_ID);
        }
    }

    public bool? IsDistributed
    {
        get
        {
            return base.GetNullableBoolean(ISDISTRIBUTED_FIELD_ID);
        }
    }

    public byte? ClusterType
    {
        get
        {
            return base.GetNullableByte(CLUSTERTYPE_FIELD_ID);
        }
    }

    public string? ClusterTypeDesc
    {
        get
        {
            return base.GetNullableString(CLUSTERTYPEDESC_FIELD_ID);
        }
    }

    public int? RequiredSynchronizedSecondariesToCommit
    {
        get
        {
            return base.GetNullableInt32(REQUIREDSYNCHRONIZEDSECONDARIESTOCOMMIT_FIELD_ID);
        }
    }

    public long? SequenceNumber
    {
        get
        {
            return base.GetNullableInt64(SEQUENCENUMBER_FIELD_ID);
        }
    }

    public bool? IsContained
    {
        get
        {
            return base.GetNullableBoolean(ISCONTAINED_FIELD_ID);
        }
    }


    public Types.AvailabilityGroupsDataType ToDataObject()
    {
        return new Types.AvailabilityGroupsDataType(GroupId,
            Name,
            ResourceId,
            ResourceGroupId,
            FailureConditionLevel,
            HealthCheckTimeout,
            AutomatedBackupPreference,
            AutomatedBackupPreferenceDesc,
            Version,
            BasicFeatures,
            DtcSupport,
            DbFailover,
            IsDistributed,
            ClusterType,
            ClusterTypeDesc,
            RequiredSynchronizedSecondariesToCommit,
            SequenceNumber,
            IsContained);
    }

    public List<Types.AvailabilityGroupsDataType> ToList()
    {
        var list = new List<Types.AvailabilityGroupsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

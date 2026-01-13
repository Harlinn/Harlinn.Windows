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

public class DatabaseMirroringWitnessesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[database_mirroring_witnesses]";
    public const string TableName = "database_mirroring_witnesses";
    public const string ShortName = "dmw";
    public const string Sql = """
        SELECT
          dmw.[database_name],
          dmw.[principal_server_name],
          dmw.[mirror_server_name],
          dmw.[safety_level],
          dmw.[safety_level_desc],
          dmw.[safety_sequence_number],
          dmw.[role_sequence_number],
          dmw.[mirroring_guid],
          dmw.[family_guid],
          dmw.[is_suspended],
          dmw.[is_suspended_sequence_number],
          dmw.[partner_sync_state],
          dmw.[partner_sync_state_desc]
        FROM
          [sys].[database_mirroring_witnesses] dmw
        """;

    public const int DATABASENAME_FIELD_ID = 0;
    public const int PRINCIPALSERVERNAME_FIELD_ID = 1;
    public const int MIRRORSERVERNAME_FIELD_ID = 2;
    public const int SAFETYLEVEL_FIELD_ID = 3;
    public const int SAFETYLEVELDESC_FIELD_ID = 4;
    public const int SAFETYSEQUENCENUMBER_FIELD_ID = 5;
    public const int ROLESEQUENCENUMBER_FIELD_ID = 6;
    public const int MIRRORINGGUID_FIELD_ID = 7;
    public const int FAMILYGUID_FIELD_ID = 8;
    public const int ISSUSPENDED_FIELD_ID = 9;
    public const int ISSUSPENDEDSEQUENCENUMBER_FIELD_ID = 10;
    public const int PARTNERSYNCSTATE_FIELD_ID = 11;
    public const int PARTNERSYNCSTATEDESC_FIELD_ID = 12;


    public DatabaseMirroringWitnessesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DatabaseMirroringWitnessesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DatabaseMirroringWitnessesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string DatabaseName
    {
        get
        {
            return base.GetString(DATABASENAME_FIELD_ID);
        }
    }

    public string? PrincipalServerName
    {
        get
        {
            return base.GetNullableString(PRINCIPALSERVERNAME_FIELD_ID);
        }
    }

    public string? MirrorServerName
    {
        get
        {
            return base.GetNullableString(MIRRORSERVERNAME_FIELD_ID);
        }
    }

    public byte SafetyLevel
    {
        get
        {
            return base.GetByte(SAFETYLEVEL_FIELD_ID);
        }
    }

    public string? SafetyLevelDesc
    {
        get
        {
            return base.GetNullableString(SAFETYLEVELDESC_FIELD_ID);
        }
    }

    public int SafetySequenceNumber
    {
        get
        {
            return base.GetInt32(SAFETYSEQUENCENUMBER_FIELD_ID);
        }
    }

    public int RoleSequenceNumber
    {
        get
        {
            return base.GetInt32(ROLESEQUENCENUMBER_FIELD_ID);
        }
    }

    public Guid MirroringGuid
    {
        get
        {
            return base.GetGuid(MIRRORINGGUID_FIELD_ID);
        }
    }

    public Guid FamilyGuid
    {
        get
        {
            return base.GetGuid(FAMILYGUID_FIELD_ID);
        }
    }

    public bool? IsSuspended
    {
        get
        {
            return base.GetNullableBoolean(ISSUSPENDED_FIELD_ID);
        }
    }

    public int IsSuspendedSequenceNumber
    {
        get
        {
            return base.GetInt32(ISSUSPENDEDSEQUENCENUMBER_FIELD_ID);
        }
    }

    public byte? PartnerSyncState
    {
        get
        {
            return base.GetNullableByte(PARTNERSYNCSTATE_FIELD_ID);
        }
    }

    public string? PartnerSyncStateDesc
    {
        get
        {
            return base.GetNullableString(PARTNERSYNCSTATEDESC_FIELD_ID);
        }
    }


    public Types.DatabaseMirroringWitnessesDataType ToDataObject()
    {
        return new Types.DatabaseMirroringWitnessesDataType(DatabaseName,
            PrincipalServerName,
            MirrorServerName,
            SafetyLevel,
            SafetyLevelDesc,
            SafetySequenceNumber,
            RoleSequenceNumber,
            MirroringGuid,
            FamilyGuid,
            IsSuspended,
            IsSuspendedSequenceNumber,
            PartnerSyncState,
            PartnerSyncStateDesc);
    }

    public List<Types.DatabaseMirroringWitnessesDataType> ToList()
    {
        var list = new List<Types.DatabaseMirroringWitnessesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

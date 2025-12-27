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

public class DatabaseRecoveryStatusReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[database_recovery_status]";
    public const string TableName = "database_recovery_status";
    public const string ShortName = "drs0";
    public const string Sql = """
        SELECT
          drs0.[database_id],
          drs0.[database_guid],
          drs0.[family_guid],
          drs0.[last_log_backup_lsn],
          drs0.[recovery_fork_guid],
          drs0.[first_recovery_fork_guid],
          drs0.[fork_point_lsn]
        FROM
          [sys].[database_recovery_status] drs0
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int DATABASEGUID_FIELD_ID = 1;
    public const int FAMILYGUID_FIELD_ID = 2;
    public const int LASTLOGBACKUPLSN_FIELD_ID = 3;
    public const int RECOVERYFORKGUID_FIELD_ID = 4;
    public const int FIRSTRECOVERYFORKGUID_FIELD_ID = 5;
    public const int FORKPOINTLSN_FIELD_ID = 6;


    public DatabaseRecoveryStatusReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DatabaseRecoveryStatusReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DatabaseRecoveryStatusReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public Guid? DatabaseGuid
    {
        get
        {
            return base.GetNullableGuid(DATABASEGUID_FIELD_ID);
        }
    }

    public Guid? FamilyGuid
    {
        get
        {
            return base.GetNullableGuid(FAMILYGUID_FIELD_ID);
        }
    }

    public decimal? LastLogBackupLsn
    {
        get
        {
            return base.GetNullableDecimal(LASTLOGBACKUPLSN_FIELD_ID);
        }
    }

    public Guid? RecoveryForkGuid
    {
        get
        {
            return base.GetNullableGuid(RECOVERYFORKGUID_FIELD_ID);
        }
    }

    public Guid? FirstRecoveryForkGuid
    {
        get
        {
            return base.GetNullableGuid(FIRSTRECOVERYFORKGUID_FIELD_ID);
        }
    }

    public decimal? ForkPointLsn
    {
        get
        {
            return base.GetNullableDecimal(FORKPOINTLSN_FIELD_ID);
        }
    }


    public Types.DatabaseRecoveryStatusDataType ToDataObject()
    {
        return new Types.DatabaseRecoveryStatusDataType(DatabaseId,
            DatabaseGuid,
            FamilyGuid,
            LastLogBackupLsn,
            RecoveryForkGuid,
            FirstRecoveryForkGuid,
            ForkPointLsn);
    }

    public List<Types.DatabaseRecoveryStatusDataType> ToList()
    {
        var list = new List<Types.DatabaseRecoveryStatusDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

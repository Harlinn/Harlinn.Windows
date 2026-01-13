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

public class DmDbRdaMigrationStatusReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_rda_migration_status]";
    public const string TableName = "dm_db_rda_migration_status";
    public const string ShortName = "ddrms";
    public const string Sql = """
        SELECT
          ddrms.[table_id],
          ddrms.[database_id],
          ddrms.[migrated_rows],
          ddrms.[start_time_utc],
          ddrms.[end_time_utc],
          ddrms.[error_number],
          ddrms.[error_severity],
          ddrms.[error_state]
        FROM
          [sys].[dm_db_rda_migration_status] ddrms
        """;

    public const int TABLEID_FIELD_ID = 0;
    public const int DATABASEID_FIELD_ID = 1;
    public const int MIGRATEDROWS_FIELD_ID = 2;
    public const int STARTTIMEUTC_FIELD_ID = 3;
    public const int ENDTIMEUTC_FIELD_ID = 4;
    public const int ERRORNUMBER_FIELD_ID = 5;
    public const int ERRORSEVERITY_FIELD_ID = 6;
    public const int ERRORSTATE_FIELD_ID = 7;


    public DmDbRdaMigrationStatusReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbRdaMigrationStatusReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbRdaMigrationStatusReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? TableId
    {
        get
        {
            return base.GetNullableInt32(TABLEID_FIELD_ID);
        }
    }

    public int? DatabaseId
    {
        get
        {
            return base.GetNullableInt32(DATABASEID_FIELD_ID);
        }
    }

    public long? MigratedRows
    {
        get
        {
            return base.GetNullableInt64(MIGRATEDROWS_FIELD_ID);
        }
    }

    public DateTime? StartTimeUtc
    {
        get
        {
            return base.GetNullableDateTime(STARTTIMEUTC_FIELD_ID);
        }
    }

    public DateTime? EndTimeUtc
    {
        get
        {
            return base.GetNullableDateTime(ENDTIMEUTC_FIELD_ID);
        }
    }

    public int? ErrorNumber
    {
        get
        {
            return base.GetNullableInt32(ERRORNUMBER_FIELD_ID);
        }
    }

    public int? ErrorSeverity
    {
        get
        {
            return base.GetNullableInt32(ERRORSEVERITY_FIELD_ID);
        }
    }

    public int? ErrorState
    {
        get
        {
            return base.GetNullableInt32(ERRORSTATE_FIELD_ID);
        }
    }


    public Types.DmDbRdaMigrationStatusDataType ToDataObject()
    {
        return new Types.DmDbRdaMigrationStatusDataType(TableId,
            DatabaseId,
            MigratedRows,
            StartTimeUtc,
            EndTimeUtc,
            ErrorNumber,
            ErrorSeverity,
            ErrorState);
    }

    public List<Types.DmDbRdaMigrationStatusDataType> ToList()
    {
        var list = new List<Types.DmDbRdaMigrationStatusDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

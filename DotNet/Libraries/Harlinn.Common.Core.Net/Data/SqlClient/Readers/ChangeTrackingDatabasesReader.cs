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

public class ChangeTrackingDatabasesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[change_tracking_databases]";
    public const string TableName = "change_tracking_databases";
    public const string ShortName = "ctd";
    public const string Sql = """
        SELECT
          ctd.[database_id],
          ctd.[is_auto_cleanup_on],
          ctd.[retention_period],
          ctd.[retention_period_units],
          ctd.[retention_period_units_desc],
          ctd.[max_cleanup_version]
        FROM
          [sys].[change_tracking_databases] ctd
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int ISAUTOCLEANUPON_FIELD_ID = 1;
    public const int RETENTIONPERIOD_FIELD_ID = 2;
    public const int RETENTIONPERIODUNITS_FIELD_ID = 3;
    public const int RETENTIONPERIODUNITSDESC_FIELD_ID = 4;
    public const int MAXCLEANUPVERSION_FIELD_ID = 5;


    public ChangeTrackingDatabasesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ChangeTrackingDatabasesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ChangeTrackingDatabasesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public byte? IsAutoCleanupOn
    {
        get
        {
            return base.GetNullableByte(ISAUTOCLEANUPON_FIELD_ID);
        }
    }

    public int? RetentionPeriod
    {
        get
        {
            return base.GetNullableInt32(RETENTIONPERIOD_FIELD_ID);
        }
    }

    public byte? RetentionPeriodUnits
    {
        get
        {
            return base.GetNullableByte(RETENTIONPERIODUNITS_FIELD_ID);
        }
    }

    public string? RetentionPeriodUnitsDesc
    {
        get
        {
            return base.GetNullableString(RETENTIONPERIODUNITSDESC_FIELD_ID);
        }
    }

    public long? MaxCleanupVersion
    {
        get
        {
            return base.GetNullableInt64(MAXCLEANUPVERSION_FIELD_ID);
        }
    }


    public Types.ChangeTrackingDatabasesDataType ToDataObject()
    {
        return new Types.ChangeTrackingDatabasesDataType(DatabaseId,
            IsAutoCleanupOn,
            RetentionPeriod,
            RetentionPeriodUnits,
            RetentionPeriodUnitsDesc,
            MaxCleanupVersion);
    }

    public List<Types.ChangeTrackingDatabasesDataType> ToList()
    {
        var list = new List<Types.ChangeTrackingDatabasesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

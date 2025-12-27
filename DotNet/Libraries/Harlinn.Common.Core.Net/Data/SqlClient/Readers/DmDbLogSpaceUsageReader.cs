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

public class DmDbLogSpaceUsageReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_log_space_usage]";
    public const string TableName = "dm_db_log_space_usage";
    public const string ShortName = "ddlsu";
    public const string Sql = """
        SELECT
          ddlsu.[database_id],
          ddlsu.[total_log_size_in_bytes],
          ddlsu.[used_log_space_in_bytes],
          ddlsu.[used_log_space_in_percent],
          ddlsu.[log_space_in_bytes_since_last_backup]
        FROM
          [sys].[dm_db_log_space_usage] ddlsu
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int TOTALLOGSIZEINBYTES_FIELD_ID = 1;
    public const int USEDLOGSPACEINBYTES_FIELD_ID = 2;
    public const int USEDLOGSPACEINPERCENT_FIELD_ID = 3;
    public const int LOGSPACEINBYTESSINCELASTBACKUP_FIELD_ID = 4;


    public DmDbLogSpaceUsageReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbLogSpaceUsageReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbLogSpaceUsageReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? DatabaseId
    {
        get
        {
            return base.GetNullableInt32(DATABASEID_FIELD_ID);
        }
    }

    public long? TotalLogSizeInBytes
    {
        get
        {
            return base.GetNullableInt64(TOTALLOGSIZEINBYTES_FIELD_ID);
        }
    }

    public long? UsedLogSpaceInBytes
    {
        get
        {
            return base.GetNullableInt64(USEDLOGSPACEINBYTES_FIELD_ID);
        }
    }

    public float? UsedLogSpaceInPercent
    {
        get
        {
            return base.GetNullableSingle(USEDLOGSPACEINPERCENT_FIELD_ID);
        }
    }

    public long? LogSpaceInBytesSinceLastBackup
    {
        get
        {
            return base.GetNullableInt64(LOGSPACEINBYTESSINCELASTBACKUP_FIELD_ID);
        }
    }


    public Types.DmDbLogSpaceUsageDataType ToDataObject()
    {
        return new Types.DmDbLogSpaceUsageDataType(DatabaseId,
            TotalLogSizeInBytes,
            UsedLogSpaceInBytes,
            UsedLogSpaceInPercent,
            LogSpaceInBytesSinceLastBackup);
    }

    public List<Types.DmDbLogSpaceUsageDataType> ToList()
    {
        var list = new List<Types.DmDbLogSpaceUsageDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

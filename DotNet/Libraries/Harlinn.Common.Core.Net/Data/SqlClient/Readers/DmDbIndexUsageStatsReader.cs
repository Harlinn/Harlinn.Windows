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

public class DmDbIndexUsageStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_index_usage_stats]";
    public const string TableName = "dm_db_index_usage_stats";
    public const string ShortName = "ddius";
    public const string Sql = """
        SELECT
          ddius.[database_id],
          ddius.[object_id],
          ddius.[index_id],
          ddius.[user_seeks],
          ddius.[user_scans],
          ddius.[user_lookups],
          ddius.[user_updates],
          ddius.[last_user_seek],
          ddius.[last_user_scan],
          ddius.[last_user_lookup],
          ddius.[last_user_update],
          ddius.[system_seeks],
          ddius.[system_scans],
          ddius.[system_lookups],
          ddius.[system_updates],
          ddius.[last_system_seek],
          ddius.[last_system_scan],
          ddius.[last_system_lookup],
          ddius.[last_system_update]
        FROM
          [sys].[dm_db_index_usage_stats] ddius
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int OBJECTID_FIELD_ID = 1;
    public const int INDEXID_FIELD_ID = 2;
    public const int USERSEEKS_FIELD_ID = 3;
    public const int USERSCANS_FIELD_ID = 4;
    public const int USERLOOKUPS_FIELD_ID = 5;
    public const int USERUPDATES_FIELD_ID = 6;
    public const int LASTUSERSEEK_FIELD_ID = 7;
    public const int LASTUSERSCAN_FIELD_ID = 8;
    public const int LASTUSERLOOKUP_FIELD_ID = 9;
    public const int LASTUSERUPDATE_FIELD_ID = 10;
    public const int SYSTEMSEEKS_FIELD_ID = 11;
    public const int SYSTEMSCANS_FIELD_ID = 12;
    public const int SYSTEMLOOKUPS_FIELD_ID = 13;
    public const int SYSTEMUPDATES_FIELD_ID = 14;
    public const int LASTSYSTEMSEEK_FIELD_ID = 15;
    public const int LASTSYSTEMSCAN_FIELD_ID = 16;
    public const int LASTSYSTEMLOOKUP_FIELD_ID = 17;
    public const int LASTSYSTEMUPDATE_FIELD_ID = 18;


    public DmDbIndexUsageStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbIndexUsageStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbIndexUsageStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short DatabaseId
    {
        get
        {
            return base.GetInt16(DATABASEID_FIELD_ID);
        }
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int IndexId
    {
        get
        {
            return base.GetInt32(INDEXID_FIELD_ID);
        }
    }

    public long UserSeeks
    {
        get
        {
            return base.GetInt64(USERSEEKS_FIELD_ID);
        }
    }

    public long UserScans
    {
        get
        {
            return base.GetInt64(USERSCANS_FIELD_ID);
        }
    }

    public long UserLookups
    {
        get
        {
            return base.GetInt64(USERLOOKUPS_FIELD_ID);
        }
    }

    public long UserUpdates
    {
        get
        {
            return base.GetInt64(USERUPDATES_FIELD_ID);
        }
    }

    public DateTime? LastUserSeek
    {
        get
        {
            return base.GetNullableDateTime(LASTUSERSEEK_FIELD_ID);
        }
    }

    public DateTime? LastUserScan
    {
        get
        {
            return base.GetNullableDateTime(LASTUSERSCAN_FIELD_ID);
        }
    }

    public DateTime? LastUserLookup
    {
        get
        {
            return base.GetNullableDateTime(LASTUSERLOOKUP_FIELD_ID);
        }
    }

    public DateTime? LastUserUpdate
    {
        get
        {
            return base.GetNullableDateTime(LASTUSERUPDATE_FIELD_ID);
        }
    }

    public long SystemSeeks
    {
        get
        {
            return base.GetInt64(SYSTEMSEEKS_FIELD_ID);
        }
    }

    public long SystemScans
    {
        get
        {
            return base.GetInt64(SYSTEMSCANS_FIELD_ID);
        }
    }

    public long SystemLookups
    {
        get
        {
            return base.GetInt64(SYSTEMLOOKUPS_FIELD_ID);
        }
    }

    public long SystemUpdates
    {
        get
        {
            return base.GetInt64(SYSTEMUPDATES_FIELD_ID);
        }
    }

    public DateTime? LastSystemSeek
    {
        get
        {
            return base.GetNullableDateTime(LASTSYSTEMSEEK_FIELD_ID);
        }
    }

    public DateTime? LastSystemScan
    {
        get
        {
            return base.GetNullableDateTime(LASTSYSTEMSCAN_FIELD_ID);
        }
    }

    public DateTime? LastSystemLookup
    {
        get
        {
            return base.GetNullableDateTime(LASTSYSTEMLOOKUP_FIELD_ID);
        }
    }

    public DateTime? LastSystemUpdate
    {
        get
        {
            return base.GetNullableDateTime(LASTSYSTEMUPDATE_FIELD_ID);
        }
    }


    public Types.DmDbIndexUsageStatsDataType ToDataObject()
    {
        return new Types.DmDbIndexUsageStatsDataType(DatabaseId,
            ObjectId,
            IndexId,
            UserSeeks,
            UserScans,
            UserLookups,
            UserUpdates,
            LastUserSeek,
            LastUserScan,
            LastUserLookup,
            LastUserUpdate,
            SystemSeeks,
            SystemScans,
            SystemLookups,
            SystemUpdates,
            LastSystemSeek,
            LastSystemScan,
            LastSystemLookup,
            LastSystemUpdate);
    }

    public List<Types.DmDbIndexUsageStatsDataType> ToList()
    {
        var list = new List<Types.DmDbIndexUsageStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

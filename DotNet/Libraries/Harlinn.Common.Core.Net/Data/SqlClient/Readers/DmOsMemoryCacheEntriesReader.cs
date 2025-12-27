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

public class DmOsMemoryCacheEntriesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_memory_cache_entries]";
    public const string TableName = "dm_os_memory_cache_entries";
    public const string ShortName = "domce";
    public const string Sql = """
        SELECT
          domce.[cache_address],
          domce.[Name],
          domce.[Type],
          domce.[entry_address],
          domce.[entry_data_address],
          domce.[in_use_count],
          domce.[is_dirty],
          domce.[disk_ios_count],
          domce.[context_switches_count],
          domce.[original_cost],
          domce.[current_cost],
          domce.[memory_object_address],
          domce.[pages_kb],
          domce.[entry_data],
          domce.[pool_id],
          domce.[time_to_generate],
          domce.[use_count],
          domce.[average_time_between_uses],
          domce.[time_since_last_use],
          domce.[probability_of_reuse],
          domce.[Value]
        FROM
          [sys].[dm_os_memory_cache_entries] domce
        """;

    public const int CACHEADDRESS_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int TYPE_FIELD_ID = 2;
    public const int ENTRYADDRESS_FIELD_ID = 3;
    public const int ENTRYDATAADDRESS_FIELD_ID = 4;
    public const int INUSECOUNT_FIELD_ID = 5;
    public const int ISDIRTY_FIELD_ID = 6;
    public const int DISKIOSCOUNT_FIELD_ID = 7;
    public const int CONTEXTSWITCHESCOUNT_FIELD_ID = 8;
    public const int ORIGINALCOST_FIELD_ID = 9;
    public const int CURRENTCOST_FIELD_ID = 10;
    public const int MEMORYOBJECTADDRESS_FIELD_ID = 11;
    public const int PAGESKB_FIELD_ID = 12;
    public const int ENTRYDATA_FIELD_ID = 13;
    public const int POOLID_FIELD_ID = 14;
    public const int TIMETOGENERATE_FIELD_ID = 15;
    public const int USECOUNT_FIELD_ID = 16;
    public const int AVERAGETIMEBETWEENUSES_FIELD_ID = 17;
    public const int TIMESINCELASTUSE_FIELD_ID = 18;
    public const int PROBABILITYOFREUSE_FIELD_ID = 19;
    public const int VALUE_FIELD_ID = 20;


    public DmOsMemoryCacheEntriesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryCacheEntriesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryCacheEntriesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] CacheAddress
    {
        get
        {
            return base.GetBinary(CACHEADDRESS_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return base.GetString(TYPE_FIELD_ID);
        }
    }

    public byte[] EntryAddress
    {
        get
        {
            return base.GetBinary(ENTRYADDRESS_FIELD_ID);
        }
    }

    public byte[] EntryDataAddress
    {
        get
        {
            return base.GetBinary(ENTRYDATAADDRESS_FIELD_ID);
        }
    }

    public int InUseCount
    {
        get
        {
            return base.GetInt32(INUSECOUNT_FIELD_ID);
        }
    }

    public bool IsDirty
    {
        get
        {
            return base.GetBoolean(ISDIRTY_FIELD_ID);
        }
    }

    public int DiskIosCount
    {
        get
        {
            return base.GetInt32(DISKIOSCOUNT_FIELD_ID);
        }
    }

    public int ContextSwitchesCount
    {
        get
        {
            return base.GetInt32(CONTEXTSWITCHESCOUNT_FIELD_ID);
        }
    }

    public int OriginalCost
    {
        get
        {
            return base.GetInt32(ORIGINALCOST_FIELD_ID);
        }
    }

    public int CurrentCost
    {
        get
        {
            return base.GetInt32(CURRENTCOST_FIELD_ID);
        }
    }

    public byte[]? MemoryObjectAddress
    {
        get
        {
            return base.GetNullableBinary(MEMORYOBJECTADDRESS_FIELD_ID);
        }
    }

    public long PagesKb
    {
        get
        {
            return base.GetInt64(PAGESKB_FIELD_ID);
        }
    }

    public string? EntryData
    {
        get
        {
            return base.GetNullableString(ENTRYDATA_FIELD_ID);
        }
    }

    public int? PoolId
    {
        get
        {
            return base.GetNullableInt32(POOLID_FIELD_ID);
        }
    }

    public double? TimeToGenerate
    {
        get
        {
            return base.GetNullableDouble(TIMETOGENERATE_FIELD_ID);
        }
    }

    public long? UseCount
    {
        get
        {
            return base.GetNullableInt64(USECOUNT_FIELD_ID);
        }
    }

    public double? AverageTimeBetweenUses
    {
        get
        {
            return base.GetNullableDouble(AVERAGETIMEBETWEENUSES_FIELD_ID);
        }
    }

    public double? TimeSinceLastUse
    {
        get
        {
            return base.GetNullableDouble(TIMESINCELASTUSE_FIELD_ID);
        }
    }

    public double? ProbabilityOfReuse
    {
        get
        {
            return base.GetNullableDouble(PROBABILITYOFREUSE_FIELD_ID);
        }
    }

    public double? Value
    {
        get
        {
            return base.GetNullableDouble(VALUE_FIELD_ID);
        }
    }


    public Types.DmOsMemoryCacheEntriesDataType ToDataObject()
    {
        return new Types.DmOsMemoryCacheEntriesDataType(CacheAddress,
            Name,
            Type,
            EntryAddress,
            EntryDataAddress,
            InUseCount,
            IsDirty,
            DiskIosCount,
            ContextSwitchesCount,
            OriginalCost,
            CurrentCost,
            MemoryObjectAddress,
            PagesKb,
            EntryData,
            PoolId,
            TimeToGenerate,
            UseCount,
            AverageTimeBetweenUses,
            TimeSinceLastUse,
            ProbabilityOfReuse,
            Value);
    }

    public List<Types.DmOsMemoryCacheEntriesDataType> ToList()
    {
        var list = new List<Types.DmOsMemoryCacheEntriesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

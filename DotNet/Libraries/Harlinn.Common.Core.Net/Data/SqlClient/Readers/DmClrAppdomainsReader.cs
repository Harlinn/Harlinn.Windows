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

public class DmClrAppdomainsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_clr_appdomains]";
    public const string TableName = "dm_clr_appdomains";
    public const string ShortName = "dca";
    public const string Sql = """
        SELECT
          dca.[appdomain_address],
          dca.[appdomain_id],
          dca.[appdomain_name],
          dca.[creation_time],
          dca.[db_id],
          dca.[user_id],
          dca.[State],
          dca.[strong_refcount],
          dca.[weak_refcount],
          dca.[Cost],
          dca.[Value],
          dca.[compatibility_level],
          dca.[total_processor_time_ms],
          dca.[total_allocated_memory_kb],
          dca.[survived_memory_kb]
        FROM
          [sys].[dm_clr_appdomains] dca
        """;

    public const int APPDOMAINADDRESS_FIELD_ID = 0;
    public const int APPDOMAINID_FIELD_ID = 1;
    public const int APPDOMAINNAME_FIELD_ID = 2;
    public const int CREATIONTIME_FIELD_ID = 3;
    public const int DBID_FIELD_ID = 4;
    public const int USERID_FIELD_ID = 5;
    public const int STATE_FIELD_ID = 6;
    public const int STRONGREFCOUNT_FIELD_ID = 7;
    public const int WEAKREFCOUNT_FIELD_ID = 8;
    public const int COST_FIELD_ID = 9;
    public const int VALUE_FIELD_ID = 10;
    public const int COMPATIBILITYLEVEL_FIELD_ID = 11;
    public const int TOTALPROCESSORTIMEMS_FIELD_ID = 12;
    public const int TOTALALLOCATEDMEMORYKB_FIELD_ID = 13;
    public const int SURVIVEDMEMORYKB_FIELD_ID = 14;


    public DmClrAppdomainsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmClrAppdomainsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmClrAppdomainsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[]? AppdomainAddress
    {
        get
        {
            return base.GetNullableBinary(APPDOMAINADDRESS_FIELD_ID);
        }
    }

    public int? AppdomainId
    {
        get
        {
            return base.GetNullableInt32(APPDOMAINID_FIELD_ID);
        }
    }

    public string? AppdomainName
    {
        get
        {
            return base.GetNullableString(APPDOMAINNAME_FIELD_ID);
        }
    }

    public DateTime? CreationTime
    {
        get
        {
            return base.GetNullableDateTime(CREATIONTIME_FIELD_ID);
        }
    }

    public int? DbId
    {
        get
        {
            return base.GetNullableInt32(DBID_FIELD_ID);
        }
    }

    public int? UserId
    {
        get
        {
            return base.GetNullableInt32(USERID_FIELD_ID);
        }
    }

    public string? State
    {
        get
        {
            return base.GetNullableString(STATE_FIELD_ID);
        }
    }

    public int? StrongRefcount
    {
        get
        {
            return base.GetNullableInt32(STRONGREFCOUNT_FIELD_ID);
        }
    }

    public int? WeakRefcount
    {
        get
        {
            return base.GetNullableInt32(WEAKREFCOUNT_FIELD_ID);
        }
    }

    public int? Cost
    {
        get
        {
            return base.GetNullableInt32(COST_FIELD_ID);
        }
    }

    public int? Value
    {
        get
        {
            return base.GetNullableInt32(VALUE_FIELD_ID);
        }
    }

    public int? CompatibilityLevel
    {
        get
        {
            return base.GetNullableInt32(COMPATIBILITYLEVEL_FIELD_ID);
        }
    }

    public long? TotalProcessorTimeMs
    {
        get
        {
            return base.GetNullableInt64(TOTALPROCESSORTIMEMS_FIELD_ID);
        }
    }

    public long? TotalAllocatedMemoryKb
    {
        get
        {
            return base.GetNullableInt64(TOTALALLOCATEDMEMORYKB_FIELD_ID);
        }
    }

    public long? SurvivedMemoryKb
    {
        get
        {
            return base.GetNullableInt64(SURVIVEDMEMORYKB_FIELD_ID);
        }
    }


    public Types.DmClrAppdomainsDataType ToDataObject()
    {
        return new Types.DmClrAppdomainsDataType(AppdomainAddress,
            AppdomainId,
            AppdomainName,
            CreationTime,
            DbId,
            UserId,
            State,
            StrongRefcount,
            WeakRefcount,
            Cost,
            Value,
            CompatibilityLevel,
            TotalProcessorTimeMs,
            TotalAllocatedMemoryKb,
            SurvivedMemoryKb);
    }

    public List<Types.DmClrAppdomainsDataType> ToList()
    {
        var list = new List<Types.DmClrAppdomainsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

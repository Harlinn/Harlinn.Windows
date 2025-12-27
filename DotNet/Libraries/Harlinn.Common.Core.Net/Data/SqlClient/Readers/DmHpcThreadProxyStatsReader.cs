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

public class DmHpcThreadProxyStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hpc_thread_proxy_stats]";
    public const string TableName = "dm_hpc_thread_proxy_stats";
    public const string ShortName = "dhtps";
    public const string Sql = """
        SELECT
          dhtps.[device_logical_id],
          dhtps.[device_type],
          dhtps.[device_provider],
          dhtps.[proxy_id],
          dhtps.[rows_handled],
          dhtps.[cycles_used],
          dhtps.[host_to_device_bytes],
          dhtps.[device_to_host_bytes],
          dhtps.[device_memory_bytes],
          dhtps.[session_id],
          dhtps.[request_id],
          dhtps.[Active]
        FROM
          [sys].[dm_hpc_thread_proxy_stats] dhtps
        """;

    public const int DEVICELOGICALID_FIELD_ID = 0;
    public const int DEVICETYPE_FIELD_ID = 1;
    public const int DEVICEPROVIDER_FIELD_ID = 2;
    public const int PROXYID_FIELD_ID = 3;
    public const int ROWSHANDLED_FIELD_ID = 4;
    public const int CYCLESUSED_FIELD_ID = 5;
    public const int HOSTTODEVICEBYTES_FIELD_ID = 6;
    public const int DEVICETOHOSTBYTES_FIELD_ID = 7;
    public const int DEVICEMEMORYBYTES_FIELD_ID = 8;
    public const int SESSIONID_FIELD_ID = 9;
    public const int REQUESTID_FIELD_ID = 10;
    public const int ACTIVE_FIELD_ID = 11;


    public DmHpcThreadProxyStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHpcThreadProxyStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHpcThreadProxyStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DeviceLogicalId
    {
        get
        {
            return base.GetInt32(DEVICELOGICALID_FIELD_ID);
        }
    }

    public int DeviceType
    {
        get
        {
            return base.GetInt32(DEVICETYPE_FIELD_ID);
        }
    }

    public int DeviceProvider
    {
        get
        {
            return base.GetInt32(DEVICEPROVIDER_FIELD_ID);
        }
    }

    public int ProxyId
    {
        get
        {
            return base.GetInt32(PROXYID_FIELD_ID);
        }
    }

    public long RowsHandled
    {
        get
        {
            return base.GetInt64(ROWSHANDLED_FIELD_ID);
        }
    }

    public long CyclesUsed
    {
        get
        {
            return base.GetInt64(CYCLESUSED_FIELD_ID);
        }
    }

    public long HostToDeviceBytes
    {
        get
        {
            return base.GetInt64(HOSTTODEVICEBYTES_FIELD_ID);
        }
    }

    public long DeviceToHostBytes
    {
        get
        {
            return base.GetInt64(DEVICETOHOSTBYTES_FIELD_ID);
        }
    }

    public long DeviceMemoryBytes
    {
        get
        {
            return base.GetInt64(DEVICEMEMORYBYTES_FIELD_ID);
        }
    }

    public short SessionId
    {
        get
        {
            return base.GetInt16(SESSIONID_FIELD_ID);
        }
    }

    public int RequestId
    {
        get
        {
            return base.GetInt32(REQUESTID_FIELD_ID);
        }
    }

    public bool Active
    {
        get
        {
            return base.GetBoolean(ACTIVE_FIELD_ID);
        }
    }


    public Types.DmHpcThreadProxyStatsDataType ToDataObject()
    {
        return new Types.DmHpcThreadProxyStatsDataType(DeviceLogicalId,
            DeviceType,
            DeviceProvider,
            ProxyId,
            RowsHandled,
            CyclesUsed,
            HostToDeviceBytes,
            DeviceToHostBytes,
            DeviceMemoryBytes,
            SessionId,
            RequestId,
            Active);
    }

    public List<Types.DmHpcThreadProxyStatsDataType> ToList()
    {
        var list = new List<Types.DmHpcThreadProxyStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class DmHpcDeviceStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hpc_device_stats]";
    public const string TableName = "dm_hpc_device_stats";
    public const string ShortName = "dhds";
    public const string Sql = """
        SELECT
          dhds.[device_logical_id],
          dhds.[device_type],
          dhds.[device_provider],
          dhds.[device_physical_id],
          dhds.[Version],
          dhds.[compute_units],
          dhds.[max_thread_proxies],
          dhds.[clock_frequency],
          dhds.[device_memory_bytes],
          dhds.[rows_handled],
          dhds.[cycles_used],
          dhds.[device_to_host_bytes],
          dhds.[host_to_device_bytes],
          dhds.[device_ready]
        FROM
          [sys].[dm_hpc_device_stats] dhds
        """;

    public const int DEVICELOGICALID_FIELD_ID = 0;
    public const int DEVICETYPE_FIELD_ID = 1;
    public const int DEVICEPROVIDER_FIELD_ID = 2;
    public const int DEVICEPHYSICALID_FIELD_ID = 3;
    public const int VERSION_FIELD_ID = 4;
    public const int COMPUTEUNITS_FIELD_ID = 5;
    public const int MAXTHREADPROXIES_FIELD_ID = 6;
    public const int CLOCKFREQUENCY_FIELD_ID = 7;
    public const int DEVICEMEMORYBYTES_FIELD_ID = 8;
    public const int ROWSHANDLED_FIELD_ID = 9;
    public const int CYCLESUSED_FIELD_ID = 10;
    public const int DEVICETOHOSTBYTES_FIELD_ID = 11;
    public const int HOSTTODEVICEBYTES_FIELD_ID = 12;
    public const int DEVICEREADY_FIELD_ID = 13;


    public DmHpcDeviceStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHpcDeviceStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHpcDeviceStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public long DevicePhysicalId
    {
        get
        {
            return base.GetInt64(DEVICEPHYSICALID_FIELD_ID);
        }
    }

    public long Version
    {
        get
        {
            return base.GetInt64(VERSION_FIELD_ID);
        }
    }

    public int ComputeUnits
    {
        get
        {
            return base.GetInt32(COMPUTEUNITS_FIELD_ID);
        }
    }

    public int MaxThreadProxies
    {
        get
        {
            return base.GetInt32(MAXTHREADPROXIES_FIELD_ID);
        }
    }

    public long ClockFrequency
    {
        get
        {
            return base.GetInt64(CLOCKFREQUENCY_FIELD_ID);
        }
    }

    public long DeviceMemoryBytes
    {
        get
        {
            return base.GetInt64(DEVICEMEMORYBYTES_FIELD_ID);
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

    public long DeviceToHostBytes
    {
        get
        {
            return base.GetInt64(DEVICETOHOSTBYTES_FIELD_ID);
        }
    }

    public long HostToDeviceBytes
    {
        get
        {
            return base.GetInt64(HOSTTODEVICEBYTES_FIELD_ID);
        }
    }

    public bool DeviceReady
    {
        get
        {
            return base.GetBoolean(DEVICEREADY_FIELD_ID);
        }
    }


    public Types.DmHpcDeviceStatsDataType ToDataObject()
    {
        return new Types.DmHpcDeviceStatsDataType(DeviceLogicalId,
            DeviceType,
            DeviceProvider,
            DevicePhysicalId,
            Version,
            ComputeUnits,
            MaxThreadProxies,
            ClockFrequency,
            DeviceMemoryBytes,
            RowsHandled,
            CyclesUsed,
            DeviceToHostBytes,
            HostToDeviceBytes,
            DeviceReady);
    }

    public List<Types.DmHpcDeviceStatsDataType> ToList()
    {
        var list = new List<Types.DmHpcDeviceStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

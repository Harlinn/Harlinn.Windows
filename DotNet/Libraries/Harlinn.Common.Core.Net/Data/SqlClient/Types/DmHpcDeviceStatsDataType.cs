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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class DmHpcDeviceStatsDataType
{
    readonly int _deviceLogicalId = 0;
    readonly int _deviceType = 0;
    readonly int _deviceProvider = 0;
    readonly long _devicePhysicalId = 0;
    readonly long _version = 0;
    readonly int _computeUnits = 0;
    readonly int _maxThreadProxies = 0;
    readonly long _clockFrequency = 0;
    readonly long _deviceMemoryBytes = 0;
    readonly long _rowsHandled = 0;
    readonly long _cyclesUsed = 0;
    readonly long _deviceToHostBytes = 0;
    readonly long _hostToDeviceBytes = 0;
    readonly bool _deviceReady = false;

    public DmHpcDeviceStatsDataType( )
    {
    }

    public DmHpcDeviceStatsDataType(int deviceLogicalId,
        int deviceType,
        int deviceProvider,
        long devicePhysicalId,
        long version,
        int computeUnits,
        int maxThreadProxies,
        long clockFrequency,
        long deviceMemoryBytes,
        long rowsHandled,
        long cyclesUsed,
        long deviceToHostBytes,
        long hostToDeviceBytes,
        bool deviceReady)
    {
        _deviceLogicalId = deviceLogicalId;
        _deviceType = deviceType;
        _deviceProvider = deviceProvider;
        _devicePhysicalId = devicePhysicalId;
        _version = version;
        _computeUnits = computeUnits;
        _maxThreadProxies = maxThreadProxies;
        _clockFrequency = clockFrequency;
        _deviceMemoryBytes = deviceMemoryBytes;
        _rowsHandled = rowsHandled;
        _cyclesUsed = cyclesUsed;
        _deviceToHostBytes = deviceToHostBytes;
        _hostToDeviceBytes = hostToDeviceBytes;
        _deviceReady = deviceReady;
    }

    public int DeviceLogicalId => _deviceLogicalId;
    public int DeviceType => _deviceType;
    public int DeviceProvider => _deviceProvider;
    public long DevicePhysicalId => _devicePhysicalId;
    public long Version => _version;
    public int ComputeUnits => _computeUnits;
    public int MaxThreadProxies => _maxThreadProxies;
    public long ClockFrequency => _clockFrequency;
    public long DeviceMemoryBytes => _deviceMemoryBytes;
    public long RowsHandled => _rowsHandled;
    public long CyclesUsed => _cyclesUsed;
    public long DeviceToHostBytes => _deviceToHostBytes;
    public long HostToDeviceBytes => _hostToDeviceBytes;
    public bool DeviceReady => _deviceReady;
}

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

public class DmHpcThreadProxyStatsDataType
{
    readonly int _deviceLogicalId = 0;
    readonly int _deviceType = 0;
    readonly int _deviceProvider = 0;
    readonly int _proxyId = 0;
    readonly long _rowsHandled = 0;
    readonly long _cyclesUsed = 0;
    readonly long _hostToDeviceBytes = 0;
    readonly long _deviceToHostBytes = 0;
    readonly long _deviceMemoryBytes = 0;
    readonly short _sessionId = 0;
    readonly int _requestId = 0;
    readonly bool _active = false;

    public DmHpcThreadProxyStatsDataType( )
    {
    }

    public DmHpcThreadProxyStatsDataType(int deviceLogicalId,
        int deviceType,
        int deviceProvider,
        int proxyId,
        long rowsHandled,
        long cyclesUsed,
        long hostToDeviceBytes,
        long deviceToHostBytes,
        long deviceMemoryBytes,
        short sessionId,
        int requestId,
        bool active)
    {
        _deviceLogicalId = deviceLogicalId;
        _deviceType = deviceType;
        _deviceProvider = deviceProvider;
        _proxyId = proxyId;
        _rowsHandled = rowsHandled;
        _cyclesUsed = cyclesUsed;
        _hostToDeviceBytes = hostToDeviceBytes;
        _deviceToHostBytes = deviceToHostBytes;
        _deviceMemoryBytes = deviceMemoryBytes;
        _sessionId = sessionId;
        _requestId = requestId;
        _active = active;
    }

    public int DeviceLogicalId => _deviceLogicalId;
    public int DeviceType => _deviceType;
    public int DeviceProvider => _deviceProvider;
    public int ProxyId => _proxyId;
    public long RowsHandled => _rowsHandled;
    public long CyclesUsed => _cyclesUsed;
    public long HostToDeviceBytes => _hostToDeviceBytes;
    public long DeviceToHostBytes => _deviceToHostBytes;
    public long DeviceMemoryBytes => _deviceMemoryBytes;
    public short SessionId => _sessionId;
    public int RequestId => _requestId;
    public bool Active => _active;
}

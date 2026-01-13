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

public class DmOsRingBuffersDataType
{
    readonly byte[] _ringBufferAddress = Array.Empty<byte>();
    readonly string _ringBufferType = string.Empty;
    readonly long _timestamp = 0;
    readonly string? _record;

    public DmOsRingBuffersDataType( )
    {
    }

    public DmOsRingBuffersDataType(byte[] ringBufferAddress,
        string ringBufferType,
        long timestamp,
        string? record)
    {
        _ringBufferAddress = ringBufferAddress;
        _ringBufferType = ringBufferType;
        _timestamp = timestamp;
        _record = record;
    }

    public byte[] RingBufferAddress => _ringBufferAddress;
    public string RingBufferType => _ringBufferType;
    public long Timestamp => _timestamp;
    public string? Record => _record;
}

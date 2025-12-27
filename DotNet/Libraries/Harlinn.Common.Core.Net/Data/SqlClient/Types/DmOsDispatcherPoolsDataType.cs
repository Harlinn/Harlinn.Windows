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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class DmOsDispatcherPoolsDataType
{
    readonly byte[] _dispatcherPoolAddress = Array.Empty<byte>();
    readonly string _type = string.Empty;
    readonly string _name = string.Empty;
    readonly int _dispatcherCount = 0;
    readonly int _dispatcherIdealCount = 0;
    readonly int _dispatcherTimeoutMs = 0;
    readonly int _dispatcherWaitingCount = 0;
    readonly int _queueLength = 0;

    public DmOsDispatcherPoolsDataType( )
    {
    }

    public DmOsDispatcherPoolsDataType(byte[] dispatcherPoolAddress,
        string type,
        string name,
        int dispatcherCount,
        int dispatcherIdealCount,
        int dispatcherTimeoutMs,
        int dispatcherWaitingCount,
        int queueLength)
    {
        _dispatcherPoolAddress = dispatcherPoolAddress;
        _type = type;
        _name = name;
        _dispatcherCount = dispatcherCount;
        _dispatcherIdealCount = dispatcherIdealCount;
        _dispatcherTimeoutMs = dispatcherTimeoutMs;
        _dispatcherWaitingCount = dispatcherWaitingCount;
        _queueLength = queueLength;
    }

    public byte[] DispatcherPoolAddress => _dispatcherPoolAddress;
    public string Type => _type;
    public string Name => _name;
    public int DispatcherCount => _dispatcherCount;
    public int DispatcherIdealCount => _dispatcherIdealCount;
    public int DispatcherTimeoutMs => _dispatcherTimeoutMs;
    public int DispatcherWaitingCount => _dispatcherWaitingCount;
    public int QueueLength => _queueLength;
}

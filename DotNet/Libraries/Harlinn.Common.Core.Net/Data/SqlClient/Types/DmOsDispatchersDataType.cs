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

public class DmOsDispatchersDataType
{
    readonly byte[] _dispatcherPoolAddress = Array.Empty<byte>();
    readonly byte[] _taskAddress = Array.Empty<byte>();
    readonly string _state = string.Empty;
    readonly long? _waitDuration;
    readonly long? _currentItemDuration;
    readonly long _itemsProcessed = 0;
    readonly int? _fadeEndTime;

    public DmOsDispatchersDataType( )
    {
    }

    public DmOsDispatchersDataType(byte[] dispatcherPoolAddress,
        byte[] taskAddress,
        string state,
        long? waitDuration,
        long? currentItemDuration,
        long itemsProcessed,
        int? fadeEndTime)
    {
        _dispatcherPoolAddress = dispatcherPoolAddress;
        _taskAddress = taskAddress;
        _state = state;
        _waitDuration = waitDuration;
        _currentItemDuration = currentItemDuration;
        _itemsProcessed = itemsProcessed;
        _fadeEndTime = fadeEndTime;
    }

    public byte[] DispatcherPoolAddress => _dispatcherPoolAddress;
    public byte[] TaskAddress => _taskAddress;
    public string State => _state;
    public long? WaitDuration => _waitDuration;
    public long? CurrentItemDuration => _currentItemDuration;
    public long ItemsProcessed => _itemsProcessed;
    public int? FadeEndTime => _fadeEndTime;
}

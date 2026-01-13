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

public class DmOsHostsDataType
{
    readonly byte[] _hostAddress = Array.Empty<byte>();
    readonly string? _type;
    readonly string _name = string.Empty;
    readonly int? _enqueuedTasksCount;
    readonly int? _activeTasksCount;
    readonly int? _completedIosCount;
    readonly long? _completedIosInBytes;
    readonly int? _activeIosCount;
    readonly byte[] _defaultMemoryClerkAddress = Array.Empty<byte>();

    public DmOsHostsDataType( )
    {
    }

    public DmOsHostsDataType(byte[] hostAddress,
        string? type,
        string name,
        int? enqueuedTasksCount,
        int? activeTasksCount,
        int? completedIosCount,
        long? completedIosInBytes,
        int? activeIosCount,
        byte[] defaultMemoryClerkAddress)
    {
        _hostAddress = hostAddress;
        _type = type;
        _name = name;
        _enqueuedTasksCount = enqueuedTasksCount;
        _activeTasksCount = activeTasksCount;
        _completedIosCount = completedIosCount;
        _completedIosInBytes = completedIosInBytes;
        _activeIosCount = activeIosCount;
        _defaultMemoryClerkAddress = defaultMemoryClerkAddress;
    }

    public byte[] HostAddress => _hostAddress;
    public string? Type => _type;
    public string Name => _name;
    public int? EnqueuedTasksCount => _enqueuedTasksCount;
    public int? ActiveTasksCount => _activeTasksCount;
    public int? CompletedIosCount => _completedIosCount;
    public long? CompletedIosInBytes => _completedIosInBytes;
    public int? ActiveIosCount => _activeIosCount;
    public byte[] DefaultMemoryClerkAddress => _defaultMemoryClerkAddress;
}

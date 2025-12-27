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

public class DmOsMemoryNodeAccessStatsDataType
{
    readonly int? _localNode;
    readonly int? _remoteNode;
    readonly string? _pageClass;
    readonly long? _readCount;
    readonly long? _writeCount;

    public DmOsMemoryNodeAccessStatsDataType( )
    {
    }

    public DmOsMemoryNodeAccessStatsDataType(int? localNode,
        int? remoteNode,
        string? pageClass,
        long? readCount,
        long? writeCount)
    {
        _localNode = localNode;
        _remoteNode = remoteNode;
        _pageClass = pageClass;
        _readCount = readCount;
        _writeCount = writeCount;
    }

    public int? LocalNode => _localNode;
    public int? RemoteNode => _remoteNode;
    public string? PageClass => _pageClass;
    public long? ReadCount => _readCount;
    public long? WriteCount => _writeCount;
}

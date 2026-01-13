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

public class DmOsMemoryPoolsDataType
{
    readonly byte[] _memoryPoolAddress = Array.Empty<byte>();
    readonly int _poolId = 0;
    readonly string _type = string.Empty;
    readonly string _name = string.Empty;
    readonly long _maxFreeEntriesCount = 0;
    readonly long _freeEntriesCount = 0;
    readonly long _removedInAllRoundsCount = 0;

    public DmOsMemoryPoolsDataType( )
    {
    }

    public DmOsMemoryPoolsDataType(byte[] memoryPoolAddress,
        int poolId,
        string type,
        string name,
        long maxFreeEntriesCount,
        long freeEntriesCount,
        long removedInAllRoundsCount)
    {
        _memoryPoolAddress = memoryPoolAddress;
        _poolId = poolId;
        _type = type;
        _name = name;
        _maxFreeEntriesCount = maxFreeEntriesCount;
        _freeEntriesCount = freeEntriesCount;
        _removedInAllRoundsCount = removedInAllRoundsCount;
    }

    public byte[] MemoryPoolAddress => _memoryPoolAddress;
    public int PoolId => _poolId;
    public string Type => _type;
    public string Name => _name;
    public long MaxFreeEntriesCount => _maxFreeEntriesCount;
    public long FreeEntriesCount => _freeEntriesCount;
    public long RemovedInAllRoundsCount => _removedInAllRoundsCount;
}

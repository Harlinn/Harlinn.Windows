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

public class DmFtsMemoryBuffersDataType
{
    readonly int _poolId = 0;
    readonly byte[] _memoryAddress = Array.Empty<byte>();
    readonly string _name = string.Empty;
    readonly bool _isFree = false;
    readonly int _rowCount = 0;
    readonly int _bytesUsed = 0;
    readonly int _percentUsed = 0;

    public DmFtsMemoryBuffersDataType( )
    {
    }

    public DmFtsMemoryBuffersDataType(int poolId,
        byte[] memoryAddress,
        string name,
        bool isFree,
        int rowCount,
        int bytesUsed,
        int percentUsed)
    {
        _poolId = poolId;
        _memoryAddress = memoryAddress;
        _name = name;
        _isFree = isFree;
        _rowCount = rowCount;
        _bytesUsed = bytesUsed;
        _percentUsed = percentUsed;
    }

    public int PoolId => _poolId;
    public byte[] MemoryAddress => _memoryAddress;
    public string Name => _name;
    public bool IsFree => _isFree;
    public int RowCount => _rowCount;
    public int BytesUsed => _bytesUsed;
    public int PercentUsed => _percentUsed;
}

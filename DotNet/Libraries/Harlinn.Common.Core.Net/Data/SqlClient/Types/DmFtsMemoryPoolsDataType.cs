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

public class DmFtsMemoryPoolsDataType
{
    readonly int _poolId = 0;
    readonly int _bufferSize = 0;
    readonly int _minBufferLimit = 0;
    readonly int _maxBufferLimit = 0;
    readonly int _bufferCount = 0;

    public DmFtsMemoryPoolsDataType( )
    {
    }

    public DmFtsMemoryPoolsDataType(int poolId,
        int bufferSize,
        int minBufferLimit,
        int maxBufferLimit,
        int bufferCount)
    {
        _poolId = poolId;
        _bufferSize = bufferSize;
        _minBufferLimit = minBufferLimit;
        _maxBufferLimit = maxBufferLimit;
        _bufferCount = bufferCount;
    }

    public int PoolId => _poolId;
    public int BufferSize => _bufferSize;
    public int MinBufferLimit => _minBufferLimit;
    public int MaxBufferLimit => _maxBufferLimit;
    public int BufferCount => _bufferCount;
}

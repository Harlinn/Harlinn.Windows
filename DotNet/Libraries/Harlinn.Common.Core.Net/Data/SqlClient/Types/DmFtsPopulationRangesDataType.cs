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

public class DmFtsPopulationRangesDataType
{
    readonly byte[] _memoryAddress = Array.Empty<byte>();
    readonly byte[] _parentMemoryAddress = Array.Empty<byte>();
    readonly bool _isRetry = false;
    readonly short _sessionId = 0;
    readonly int _processedRowCount = 0;
    readonly int _errorCount = 0;

    public DmFtsPopulationRangesDataType( )
    {
    }

    public DmFtsPopulationRangesDataType(byte[] memoryAddress,
        byte[] parentMemoryAddress,
        bool isRetry,
        short sessionId,
        int processedRowCount,
        int errorCount)
    {
        _memoryAddress = memoryAddress;
        _parentMemoryAddress = parentMemoryAddress;
        _isRetry = isRetry;
        _sessionId = sessionId;
        _processedRowCount = processedRowCount;
        _errorCount = errorCount;
    }

    public byte[] MemoryAddress => _memoryAddress;
    public byte[] ParentMemoryAddress => _parentMemoryAddress;
    public bool IsRetry => _isRetry;
    public short SessionId => _sessionId;
    public int ProcessedRowCount => _processedRowCount;
    public int ErrorCount => _errorCount;
}

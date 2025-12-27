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

public class DmXtpSystemMemoryConsumersDataType
{
    readonly long _memoryConsumerId = 0;
    readonly int _memoryConsumerType = 0;
    readonly string _memoryConsumerTypeDesc = string.Empty;
    readonly string? _memoryConsumerDesc;
    readonly long? _lookasideId;
    readonly long _allocatedBytes = 0;
    readonly long _usedBytes = 0;
    readonly long _allocationCount = 0;
    readonly int _partitionCount = 0;
    readonly int _sizeclassCount = 0;
    readonly int _minSizeclass = 0;
    readonly int _maxSizeclass = 0;
    readonly byte[] _memoryConsumerAddress = Array.Empty<byte>();

    public DmXtpSystemMemoryConsumersDataType( )
    {
    }

    public DmXtpSystemMemoryConsumersDataType(long memoryConsumerId,
        int memoryConsumerType,
        string memoryConsumerTypeDesc,
        string? memoryConsumerDesc,
        long? lookasideId,
        long allocatedBytes,
        long usedBytes,
        long allocationCount,
        int partitionCount,
        int sizeclassCount,
        int minSizeclass,
        int maxSizeclass,
        byte[] memoryConsumerAddress)
    {
        _memoryConsumerId = memoryConsumerId;
        _memoryConsumerType = memoryConsumerType;
        _memoryConsumerTypeDesc = memoryConsumerTypeDesc;
        _memoryConsumerDesc = memoryConsumerDesc;
        _lookasideId = lookasideId;
        _allocatedBytes = allocatedBytes;
        _usedBytes = usedBytes;
        _allocationCount = allocationCount;
        _partitionCount = partitionCount;
        _sizeclassCount = sizeclassCount;
        _minSizeclass = minSizeclass;
        _maxSizeclass = maxSizeclass;
        _memoryConsumerAddress = memoryConsumerAddress;
    }

    public long MemoryConsumerId => _memoryConsumerId;
    public int MemoryConsumerType => _memoryConsumerType;
    public string MemoryConsumerTypeDesc => _memoryConsumerTypeDesc;
    public string? MemoryConsumerDesc => _memoryConsumerDesc;
    public long? LookasideId => _lookasideId;
    public long AllocatedBytes => _allocatedBytes;
    public long UsedBytes => _usedBytes;
    public long AllocationCount => _allocationCount;
    public int PartitionCount => _partitionCount;
    public int SizeclassCount => _sizeclassCount;
    public int MinSizeclass => _minSizeclass;
    public int MaxSizeclass => _maxSizeclass;
    public byte[] MemoryConsumerAddress => _memoryConsumerAddress;
}

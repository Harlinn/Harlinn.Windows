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

public class DmDbXtpMemoryConsumersDataType
{
    readonly long _memoryConsumerId = 0;
    readonly int _memoryConsumerType = 0;
    readonly string _memoryConsumerTypeDesc = string.Empty;
    readonly string? _memoryConsumerDesc;
    readonly int? _objectId;
    readonly int? _xtpObjectId;
    readonly int? _indexId;
    readonly long _allocatedBytes = 0;
    readonly long _usedBytes = 0;
    readonly long _allocationCount = 0;
    readonly int _partitionCount = 0;
    readonly int _sizeclassCount = 0;
    readonly int _minSizeclass = 0;
    readonly int _maxSizeclass = 0;
    readonly byte[] _memoryConsumerAddress = Array.Empty<byte>();

    public DmDbXtpMemoryConsumersDataType( )
    {
    }

    public DmDbXtpMemoryConsumersDataType(long memoryConsumerId,
        int memoryConsumerType,
        string memoryConsumerTypeDesc,
        string? memoryConsumerDesc,
        int? objectId,
        int? xtpObjectId,
        int? indexId,
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
        _objectId = objectId;
        _xtpObjectId = xtpObjectId;
        _indexId = indexId;
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
    public int? ObjectId => _objectId;
    public int? XtpObjectId => _xtpObjectId;
    public int? IndexId => _indexId;
    public long AllocatedBytes => _allocatedBytes;
    public long UsedBytes => _usedBytes;
    public long AllocationCount => _allocationCount;
    public int PartitionCount => _partitionCount;
    public int SizeclassCount => _sizeclassCount;
    public int MinSizeclass => _minSizeclass;
    public int MaxSizeclass => _maxSizeclass;
    public byte[] MemoryConsumerAddress => _memoryConsumerAddress;
}

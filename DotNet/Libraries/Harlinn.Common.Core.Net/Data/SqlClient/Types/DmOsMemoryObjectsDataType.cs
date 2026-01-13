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

public class DmOsMemoryObjectsDataType
{
    readonly byte[] _memoryObjectAddress = Array.Empty<byte>();
    readonly byte[]? _parentAddress;
    readonly long _pagesInBytes = 0;
    readonly int? _creationOptions;
    readonly long? _bytesUsed;
    readonly string _type = string.Empty;
    readonly string? _name;
    readonly short _memoryNodeId = 0;
    readonly DateTime? _creationTime;
    readonly int _pageSizeInBytes = 0;
    readonly long _maxPagesInBytes = 0;
    readonly byte[] _pageAllocatorAddress = Array.Empty<byte>();
    readonly byte[]? _creationStackAddress;
    readonly int? _sequenceNum;
    readonly int _partitionType = 0;
    readonly string _partitionTypeDesc = string.Empty;
    readonly float? _contentionFactor;
    readonly long? _waitingTasksCount;
    readonly long? _exclusiveAccessCount;

    public DmOsMemoryObjectsDataType( )
    {
    }

    public DmOsMemoryObjectsDataType(byte[] memoryObjectAddress,
        byte[]? parentAddress,
        long pagesInBytes,
        int? creationOptions,
        long? bytesUsed,
        string type,
        string? name,
        short memoryNodeId,
        DateTime? creationTime,
        int pageSizeInBytes,
        long maxPagesInBytes,
        byte[] pageAllocatorAddress,
        byte[]? creationStackAddress,
        int? sequenceNum,
        int partitionType,
        string partitionTypeDesc,
        float? contentionFactor,
        long? waitingTasksCount,
        long? exclusiveAccessCount)
    {
        _memoryObjectAddress = memoryObjectAddress;
        _parentAddress = parentAddress;
        _pagesInBytes = pagesInBytes;
        _creationOptions = creationOptions;
        _bytesUsed = bytesUsed;
        _type = type;
        _name = name;
        _memoryNodeId = memoryNodeId;
        _creationTime = creationTime;
        _pageSizeInBytes = pageSizeInBytes;
        _maxPagesInBytes = maxPagesInBytes;
        _pageAllocatorAddress = pageAllocatorAddress;
        _creationStackAddress = creationStackAddress;
        _sequenceNum = sequenceNum;
        _partitionType = partitionType;
        _partitionTypeDesc = partitionTypeDesc;
        _contentionFactor = contentionFactor;
        _waitingTasksCount = waitingTasksCount;
        _exclusiveAccessCount = exclusiveAccessCount;
    }

    public byte[] MemoryObjectAddress => _memoryObjectAddress;
    public byte[]? ParentAddress => _parentAddress;
    public long PagesInBytes => _pagesInBytes;
    public int? CreationOptions => _creationOptions;
    public long? BytesUsed => _bytesUsed;
    public string Type => _type;
    public string? Name => _name;
    public short MemoryNodeId => _memoryNodeId;
    public DateTime? CreationTime => _creationTime;
    public int PageSizeInBytes => _pageSizeInBytes;
    public long MaxPagesInBytes => _maxPagesInBytes;
    public byte[] PageAllocatorAddress => _pageAllocatorAddress;
    public byte[]? CreationStackAddress => _creationStackAddress;
    public int? SequenceNum => _sequenceNum;
    public int PartitionType => _partitionType;
    public string PartitionTypeDesc => _partitionTypeDesc;
    public float? ContentionFactor => _contentionFactor;
    public long? WaitingTasksCount => _waitingTasksCount;
    public long? ExclusiveAccessCount => _exclusiveAccessCount;
}

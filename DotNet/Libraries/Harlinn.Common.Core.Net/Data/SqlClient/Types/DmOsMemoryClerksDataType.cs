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

public class DmOsMemoryClerksDataType
{
    readonly byte[] _memoryClerkAddress = Array.Empty<byte>();
    readonly string _type = string.Empty;
    readonly string _name = string.Empty;
    readonly short _memoryNodeId = 0;
    readonly long _pagesKb = 0;
    readonly long _virtualMemoryReservedKb = 0;
    readonly long _virtualMemoryCommittedKb = 0;
    readonly long _aweAllocatedKb = 0;
    readonly long _sharedMemoryReservedKb = 0;
    readonly long _sharedMemoryCommittedKb = 0;
    readonly long _pageSizeInBytes = 0;
    readonly byte[] _pageAllocatorAddress = Array.Empty<byte>();
    readonly byte[] _hostAddress = Array.Empty<byte>();
    readonly string? _parentMemoryBrokerType;

    public DmOsMemoryClerksDataType( )
    {
    }

    public DmOsMemoryClerksDataType(byte[] memoryClerkAddress,
        string type,
        string name,
        short memoryNodeId,
        long pagesKb,
        long virtualMemoryReservedKb,
        long virtualMemoryCommittedKb,
        long aweAllocatedKb,
        long sharedMemoryReservedKb,
        long sharedMemoryCommittedKb,
        long pageSizeInBytes,
        byte[] pageAllocatorAddress,
        byte[] hostAddress,
        string? parentMemoryBrokerType)
    {
        _memoryClerkAddress = memoryClerkAddress;
        _type = type;
        _name = name;
        _memoryNodeId = memoryNodeId;
        _pagesKb = pagesKb;
        _virtualMemoryReservedKb = virtualMemoryReservedKb;
        _virtualMemoryCommittedKb = virtualMemoryCommittedKb;
        _aweAllocatedKb = aweAllocatedKb;
        _sharedMemoryReservedKb = sharedMemoryReservedKb;
        _sharedMemoryCommittedKb = sharedMemoryCommittedKb;
        _pageSizeInBytes = pageSizeInBytes;
        _pageAllocatorAddress = pageAllocatorAddress;
        _hostAddress = hostAddress;
        _parentMemoryBrokerType = parentMemoryBrokerType;
    }

    public byte[] MemoryClerkAddress => _memoryClerkAddress;
    public string Type => _type;
    public string Name => _name;
    public short MemoryNodeId => _memoryNodeId;
    public long PagesKb => _pagesKb;
    public long VirtualMemoryReservedKb => _virtualMemoryReservedKb;
    public long VirtualMemoryCommittedKb => _virtualMemoryCommittedKb;
    public long AweAllocatedKb => _aweAllocatedKb;
    public long SharedMemoryReservedKb => _sharedMemoryReservedKb;
    public long SharedMemoryCommittedKb => _sharedMemoryCommittedKb;
    public long PageSizeInBytes => _pageSizeInBytes;
    public byte[] PageAllocatorAddress => _pageAllocatorAddress;
    public byte[] HostAddress => _hostAddress;
    public string? ParentMemoryBrokerType => _parentMemoryBrokerType;
}

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

public class DmOsMemoryAllocationsDataType
{
    readonly byte[] _memoryAllocationAddress = Array.Empty<byte>();
    readonly long _sizeInBytes = 0;
    readonly DateTime _creationTime;
    readonly byte[] _memoryObjectAddress = Array.Empty<byte>();
    readonly short _memoryNodeId = 0;
    readonly byte[] _allocatorStackAddress = Array.Empty<byte>();
    readonly string? _sourceFile;
    readonly int _lineNum = 0;
    readonly int _sequenceNum = 0;
    readonly int _tag = 0;

    public DmOsMemoryAllocationsDataType( )
    {
    }

    public DmOsMemoryAllocationsDataType(byte[] memoryAllocationAddress,
        long sizeInBytes,
        DateTime creationTime,
        byte[] memoryObjectAddress,
        short memoryNodeId,
        byte[] allocatorStackAddress,
        string? sourceFile,
        int lineNum,
        int sequenceNum,
        int tag)
    {
        _memoryAllocationAddress = memoryAllocationAddress;
        _sizeInBytes = sizeInBytes;
        _creationTime = creationTime;
        _memoryObjectAddress = memoryObjectAddress;
        _memoryNodeId = memoryNodeId;
        _allocatorStackAddress = allocatorStackAddress;
        _sourceFile = sourceFile;
        _lineNum = lineNum;
        _sequenceNum = sequenceNum;
        _tag = tag;
    }

    public byte[] MemoryAllocationAddress => _memoryAllocationAddress;
    public long SizeInBytes => _sizeInBytes;
    public DateTime CreationTime => _creationTime;
    public byte[] MemoryObjectAddress => _memoryObjectAddress;
    public short MemoryNodeId => _memoryNodeId;
    public byte[] AllocatorStackAddress => _allocatorStackAddress;
    public string? SourceFile => _sourceFile;
    public int LineNum => _lineNum;
    public int SequenceNum => _sequenceNum;
    public int Tag => _tag;
}

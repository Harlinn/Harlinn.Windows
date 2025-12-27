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

public class DmXeSessionsDataType
{
    readonly byte[] _address = Array.Empty<byte>();
    readonly string _name = string.Empty;
    readonly int _pendingBuffers = 0;
    readonly int _totalRegularBuffers = 0;
    readonly long _regularBufferSize = 0;
    readonly int _totalLargeBuffers = 0;
    readonly long _largeBufferSize = 0;
    readonly long _totalBufferSize = 0;
    readonly int _bufferPolicyFlags = 0;
    readonly string _bufferPolicyDesc = string.Empty;
    readonly int _flags = 0;
    readonly string _flagDesc = string.Empty;
    readonly int _droppedEventCount = 0;
    readonly int _droppedBufferCount = 0;
    readonly int _blockedEventFireTime = 0;
    readonly DateTime _createTime;
    readonly int _largestEventDroppedSize = 0;
    readonly string _sessionSource = string.Empty;
    readonly long _bufferProcessedCount = 0;
    readonly long _bufferFullCount = 0;
    readonly long _totalBytesGenerated = 0;

    public DmXeSessionsDataType( )
    {
    }

    public DmXeSessionsDataType(byte[] address,
        string name,
        int pendingBuffers,
        int totalRegularBuffers,
        long regularBufferSize,
        int totalLargeBuffers,
        long largeBufferSize,
        long totalBufferSize,
        int bufferPolicyFlags,
        string bufferPolicyDesc,
        int flags,
        string flagDesc,
        int droppedEventCount,
        int droppedBufferCount,
        int blockedEventFireTime,
        DateTime createTime,
        int largestEventDroppedSize,
        string sessionSource,
        long bufferProcessedCount,
        long bufferFullCount,
        long totalBytesGenerated)
    {
        _address = address;
        _name = name;
        _pendingBuffers = pendingBuffers;
        _totalRegularBuffers = totalRegularBuffers;
        _regularBufferSize = regularBufferSize;
        _totalLargeBuffers = totalLargeBuffers;
        _largeBufferSize = largeBufferSize;
        _totalBufferSize = totalBufferSize;
        _bufferPolicyFlags = bufferPolicyFlags;
        _bufferPolicyDesc = bufferPolicyDesc;
        _flags = flags;
        _flagDesc = flagDesc;
        _droppedEventCount = droppedEventCount;
        _droppedBufferCount = droppedBufferCount;
        _blockedEventFireTime = blockedEventFireTime;
        _createTime = createTime;
        _largestEventDroppedSize = largestEventDroppedSize;
        _sessionSource = sessionSource;
        _bufferProcessedCount = bufferProcessedCount;
        _bufferFullCount = bufferFullCount;
        _totalBytesGenerated = totalBytesGenerated;
    }

    public byte[] Address => _address;
    public string Name => _name;
    public int PendingBuffers => _pendingBuffers;
    public int TotalRegularBuffers => _totalRegularBuffers;
    public long RegularBufferSize => _regularBufferSize;
    public int TotalLargeBuffers => _totalLargeBuffers;
    public long LargeBufferSize => _largeBufferSize;
    public long TotalBufferSize => _totalBufferSize;
    public int BufferPolicyFlags => _bufferPolicyFlags;
    public string BufferPolicyDesc => _bufferPolicyDesc;
    public int Flags => _flags;
    public string FlagDesc => _flagDesc;
    public int DroppedEventCount => _droppedEventCount;
    public int DroppedBufferCount => _droppedBufferCount;
    public int BlockedEventFireTime => _blockedEventFireTime;
    public DateTime CreateTime => _createTime;
    public int LargestEventDroppedSize => _largestEventDroppedSize;
    public string SessionSource => _sessionSource;
    public long BufferProcessedCount => _bufferProcessedCount;
    public long BufferFullCount => _bufferFullCount;
    public long TotalBytesGenerated => _totalBytesGenerated;
}

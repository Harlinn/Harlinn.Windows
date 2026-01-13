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

public class DmDbTaskSpaceUsageDataType
{
    readonly byte[]? _taskAddress;
    readonly bool _isRemoteTask = false;
    readonly short? _sessionId;
    readonly int? _requestId;
    readonly int? _execContextId;
    readonly int? _databaseId;
    readonly long? _userObjectsAllocPageCount;
    readonly long? _userObjectsDeallocPageCount;
    readonly long? _internalObjectsAllocPageCount;
    readonly long? _internalObjectsDeallocPageCount;

    public DmDbTaskSpaceUsageDataType( )
    {
    }

    public DmDbTaskSpaceUsageDataType(byte[]? taskAddress,
        bool isRemoteTask,
        short? sessionId,
        int? requestId,
        int? execContextId,
        int? databaseId,
        long? userObjectsAllocPageCount,
        long? userObjectsDeallocPageCount,
        long? internalObjectsAllocPageCount,
        long? internalObjectsDeallocPageCount)
    {
        _taskAddress = taskAddress;
        _isRemoteTask = isRemoteTask;
        _sessionId = sessionId;
        _requestId = requestId;
        _execContextId = execContextId;
        _databaseId = databaseId;
        _userObjectsAllocPageCount = userObjectsAllocPageCount;
        _userObjectsDeallocPageCount = userObjectsDeallocPageCount;
        _internalObjectsAllocPageCount = internalObjectsAllocPageCount;
        _internalObjectsDeallocPageCount = internalObjectsDeallocPageCount;
    }

    public byte[]? TaskAddress => _taskAddress;
    public bool IsRemoteTask => _isRemoteTask;
    public short? SessionId => _sessionId;
    public int? RequestId => _requestId;
    public int? ExecContextId => _execContextId;
    public int? DatabaseId => _databaseId;
    public long? UserObjectsAllocPageCount => _userObjectsAllocPageCount;
    public long? UserObjectsDeallocPageCount => _userObjectsDeallocPageCount;
    public long? InternalObjectsAllocPageCount => _internalObjectsAllocPageCount;
    public long? InternalObjectsDeallocPageCount => _internalObjectsDeallocPageCount;
}

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

public class DmExecBackgroundJobQueueDataType
{
    readonly DateTime _timeQueued;
    readonly int _jobId = 0;
    readonly int _databaseId = 0;
    readonly int _objectId1 = 0;
    readonly int _objectId2 = 0;
    readonly int _objectId3 = 0;
    readonly int _objectId4 = 0;
    readonly int? _errorCode;
    readonly short _requestType = 0;
    readonly short _retryCount = 0;
    readonly short _inProgress = 0;
    readonly short? _sessionId;

    public DmExecBackgroundJobQueueDataType( )
    {
    }

    public DmExecBackgroundJobQueueDataType(DateTime timeQueued,
        int jobId,
        int databaseId,
        int objectId1,
        int objectId2,
        int objectId3,
        int objectId4,
        int? errorCode,
        short requestType,
        short retryCount,
        short inProgress,
        short? sessionId)
    {
        _timeQueued = timeQueued;
        _jobId = jobId;
        _databaseId = databaseId;
        _objectId1 = objectId1;
        _objectId2 = objectId2;
        _objectId3 = objectId3;
        _objectId4 = objectId4;
        _errorCode = errorCode;
        _requestType = requestType;
        _retryCount = retryCount;
        _inProgress = inProgress;
        _sessionId = sessionId;
    }

    public DateTime TimeQueued => _timeQueued;
    public int JobId => _jobId;
    public int DatabaseId => _databaseId;
    public int ObjectId1 => _objectId1;
    public int ObjectId2 => _objectId2;
    public int ObjectId3 => _objectId3;
    public int ObjectId4 => _objectId4;
    public int? ErrorCode => _errorCode;
    public short RequestType => _requestType;
    public short RetryCount => _retryCount;
    public short InProgress => _inProgress;
    public short? SessionId => _sessionId;
}

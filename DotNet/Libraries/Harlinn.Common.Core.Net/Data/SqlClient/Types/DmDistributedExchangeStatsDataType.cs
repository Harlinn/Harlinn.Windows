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

public class DmDistributedExchangeStatsDataType
{
    readonly string? _requestId;
    readonly int _stepIndex = 0;
    readonly int? _dmsStepIndex;
    readonly int _sourceDistributionId = 0;
    readonly int? _destinationDistributionId;
    readonly string? _type;
    readonly string? _status;
    readonly long _bytesPerSec = 0;
    readonly long _bytesProcessed = 0;
    readonly long _rowsProcessed = 0;
    readonly DateTime _startTime;
    readonly DateTime? _endTime;
    readonly int _totalElapsedTime = 0;
    readonly long? _cpuTime;
    readonly int _queryTime = 0;
    readonly int? _buffersAvailable;
    readonly int _sqlSpid = 0;
    readonly int? _dmsCpid;
    readonly string? _errorId;
    readonly string? _sourceInfo;
    readonly string? _destinationInfo;

    public DmDistributedExchangeStatsDataType( )
    {
    }

    public DmDistributedExchangeStatsDataType(string? requestId,
        int stepIndex,
        int? dmsStepIndex,
        int sourceDistributionId,
        int? destinationDistributionId,
        string? type,
        string? status,
        long bytesPerSec,
        long bytesProcessed,
        long rowsProcessed,
        DateTime startTime,
        DateTime? endTime,
        int totalElapsedTime,
        long? cpuTime,
        int queryTime,
        int? buffersAvailable,
        int sqlSpid,
        int? dmsCpid,
        string? errorId,
        string? sourceInfo,
        string? destinationInfo)
    {
        _requestId = requestId;
        _stepIndex = stepIndex;
        _dmsStepIndex = dmsStepIndex;
        _sourceDistributionId = sourceDistributionId;
        _destinationDistributionId = destinationDistributionId;
        _type = type;
        _status = status;
        _bytesPerSec = bytesPerSec;
        _bytesProcessed = bytesProcessed;
        _rowsProcessed = rowsProcessed;
        _startTime = startTime;
        _endTime = endTime;
        _totalElapsedTime = totalElapsedTime;
        _cpuTime = cpuTime;
        _queryTime = queryTime;
        _buffersAvailable = buffersAvailable;
        _sqlSpid = sqlSpid;
        _dmsCpid = dmsCpid;
        _errorId = errorId;
        _sourceInfo = sourceInfo;
        _destinationInfo = destinationInfo;
    }

    public string? RequestId => _requestId;
    public int StepIndex => _stepIndex;
    public int? DmsStepIndex => _dmsStepIndex;
    public int SourceDistributionId => _sourceDistributionId;
    public int? DestinationDistributionId => _destinationDistributionId;
    public string? Type => _type;
    public string? Status => _status;
    public long BytesPerSec => _bytesPerSec;
    public long BytesProcessed => _bytesProcessed;
    public long RowsProcessed => _rowsProcessed;
    public DateTime StartTime => _startTime;
    public DateTime? EndTime => _endTime;
    public int TotalElapsedTime => _totalElapsedTime;
    public long? CpuTime => _cpuTime;
    public int QueryTime => _queryTime;
    public int? BuffersAvailable => _buffersAvailable;
    public int SqlSpid => _sqlSpid;
    public int? DmsCpid => _dmsCpid;
    public string? ErrorId => _errorId;
    public string? SourceInfo => _sourceInfo;
    public string? DestinationInfo => _destinationInfo;
}

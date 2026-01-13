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

public class DmExecDmsWorkersDataType
{
    readonly string? _executionId;
    readonly int? _stepIndex;
    readonly int? _dmsStepIndex;
    readonly int? _computeNodeId;
    readonly int? _distributionId;
    readonly string? _type;
    readonly string? _status;
    readonly long? _bytesPerSec;
    readonly long? _bytesProcessed;
    readonly long? _rowsProcessed;
    readonly DateTime? _startTime;
    readonly DateTime? _endTime;
    readonly int? _totalElapsedTime;
    readonly long? _cpuTime;
    readonly int? _queryTime;
    readonly int? _buffersAvailable;
    readonly int? _dmsCpid;
    readonly int? _sqlSpid;
    readonly string? _errorId;
    readonly string? _sourceInfo;
    readonly string? _destinationInfo;
    readonly string? _command;
    readonly int _computePoolId = 0;

    public DmExecDmsWorkersDataType( )
    {
    }

    public DmExecDmsWorkersDataType(string? executionId,
        int? stepIndex,
        int? dmsStepIndex,
        int? computeNodeId,
        int? distributionId,
        string? type,
        string? status,
        long? bytesPerSec,
        long? bytesProcessed,
        long? rowsProcessed,
        DateTime? startTime,
        DateTime? endTime,
        int? totalElapsedTime,
        long? cpuTime,
        int? queryTime,
        int? buffersAvailable,
        int? dmsCpid,
        int? sqlSpid,
        string? errorId,
        string? sourceInfo,
        string? destinationInfo,
        string? command,
        int computePoolId)
    {
        _executionId = executionId;
        _stepIndex = stepIndex;
        _dmsStepIndex = dmsStepIndex;
        _computeNodeId = computeNodeId;
        _distributionId = distributionId;
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
        _dmsCpid = dmsCpid;
        _sqlSpid = sqlSpid;
        _errorId = errorId;
        _sourceInfo = sourceInfo;
        _destinationInfo = destinationInfo;
        _command = command;
        _computePoolId = computePoolId;
    }

    public string? ExecutionId => _executionId;
    public int? StepIndex => _stepIndex;
    public int? DmsStepIndex => _dmsStepIndex;
    public int? ComputeNodeId => _computeNodeId;
    public int? DistributionId => _distributionId;
    public string? Type => _type;
    public string? Status => _status;
    public long? BytesPerSec => _bytesPerSec;
    public long? BytesProcessed => _bytesProcessed;
    public long? RowsProcessed => _rowsProcessed;
    public DateTime? StartTime => _startTime;
    public DateTime? EndTime => _endTime;
    public int? TotalElapsedTime => _totalElapsedTime;
    public long? CpuTime => _cpuTime;
    public int? QueryTime => _queryTime;
    public int? BuffersAvailable => _buffersAvailable;
    public int? DmsCpid => _dmsCpid;
    public int? SqlSpid => _sqlSpid;
    public string? ErrorId => _errorId;
    public string? SourceInfo => _sourceInfo;
    public string? DestinationInfo => _destinationInfo;
    public string? Command => _command;
    public int ComputePoolId => _computePoolId;
}

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

public class DmExecExternalWorkDataType
{
    readonly string? _executionId;
    readonly int? _stepIndex;
    readonly int? _dmsStepIndex;
    readonly int? _workId;
    readonly int? _computeNodeId;
    readonly string? _type;
    readonly string? _inputName;
    readonly long? _readLocation;
    readonly string? _readCommand;
    readonly long? _bytesProcessed;
    readonly long? _length;
    readonly DateTime? _startTime;
    readonly DateTime? _endTime;
    readonly int? _totalElapsedTime;
    readonly string? _status;
    readonly int _computePoolId = 0;

    public DmExecExternalWorkDataType( )
    {
    }

    public DmExecExternalWorkDataType(string? executionId,
        int? stepIndex,
        int? dmsStepIndex,
        int? workId,
        int? computeNodeId,
        string? type,
        string? inputName,
        long? readLocation,
        string? readCommand,
        long? bytesProcessed,
        long? length,
        DateTime? startTime,
        DateTime? endTime,
        int? totalElapsedTime,
        string? status,
        int computePoolId)
    {
        _executionId = executionId;
        _stepIndex = stepIndex;
        _dmsStepIndex = dmsStepIndex;
        _workId = workId;
        _computeNodeId = computeNodeId;
        _type = type;
        _inputName = inputName;
        _readLocation = readLocation;
        _readCommand = readCommand;
        _bytesProcessed = bytesProcessed;
        _length = length;
        _startTime = startTime;
        _endTime = endTime;
        _totalElapsedTime = totalElapsedTime;
        _status = status;
        _computePoolId = computePoolId;
    }

    public string? ExecutionId => _executionId;
    public int? StepIndex => _stepIndex;
    public int? DmsStepIndex => _dmsStepIndex;
    public int? WorkId => _workId;
    public int? ComputeNodeId => _computeNodeId;
    public string? Type => _type;
    public string? InputName => _inputName;
    public long? ReadLocation => _readLocation;
    public string? ReadCommand => _readCommand;
    public long? BytesProcessed => _bytesProcessed;
    public long? Length => _length;
    public DateTime? StartTime => _startTime;
    public DateTime? EndTime => _endTime;
    public int? TotalElapsedTime => _totalElapsedTime;
    public string? Status => _status;
    public int ComputePoolId => _computePoolId;
}

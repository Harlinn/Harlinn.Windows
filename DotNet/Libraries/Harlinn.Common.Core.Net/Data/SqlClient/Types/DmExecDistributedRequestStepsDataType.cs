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

public class DmExecDistributedRequestStepsDataType
{
    readonly string? _executionId;
    readonly int? _stepIndex;
    readonly string? _operationType;
    readonly string? _distributionType;
    readonly string? _locationType;
    readonly string? _status;
    readonly string? _errorId;
    readonly DateTime? _startTime;
    readonly DateTime? _endTime;
    readonly int? _totalElapsedTime;
    readonly long? _rowCount;
    readonly string? _command;
    readonly int _computePoolId = 0;

    public DmExecDistributedRequestStepsDataType( )
    {
    }

    public DmExecDistributedRequestStepsDataType(string? executionId,
        int? stepIndex,
        string? operationType,
        string? distributionType,
        string? locationType,
        string? status,
        string? errorId,
        DateTime? startTime,
        DateTime? endTime,
        int? totalElapsedTime,
        long? rowCount,
        string? command,
        int computePoolId)
    {
        _executionId = executionId;
        _stepIndex = stepIndex;
        _operationType = operationType;
        _distributionType = distributionType;
        _locationType = locationType;
        _status = status;
        _errorId = errorId;
        _startTime = startTime;
        _endTime = endTime;
        _totalElapsedTime = totalElapsedTime;
        _rowCount = rowCount;
        _command = command;
        _computePoolId = computePoolId;
    }

    public string? ExecutionId => _executionId;
    public int? StepIndex => _stepIndex;
    public string? OperationType => _operationType;
    public string? DistributionType => _distributionType;
    public string? LocationType => _locationType;
    public string? Status => _status;
    public string? ErrorId => _errorId;
    public DateTime? StartTime => _startTime;
    public DateTime? EndTime => _endTime;
    public int? TotalElapsedTime => _totalElapsedTime;
    public long? RowCount => _rowCount;
    public string? Command => _command;
    public int ComputePoolId => _computePoolId;
}

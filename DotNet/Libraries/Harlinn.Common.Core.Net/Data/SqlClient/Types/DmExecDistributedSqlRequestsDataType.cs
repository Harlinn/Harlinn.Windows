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

public class DmExecDistributedSqlRequestsDataType
{
    readonly string? _executionId;
    readonly int? _stepIndex;
    readonly int? _computeNodeId;
    readonly int? _distributionId;
    readonly string? _status;
    readonly string? _errorId;
    readonly DateTime? _startTime;
    readonly DateTime? _endTime;
    readonly int? _totalElapsedTime;
    readonly long? _rowCount;
    readonly int? _spid;
    readonly string? _command;
    readonly int _computePoolId = 0;

    public DmExecDistributedSqlRequestsDataType( )
    {
    }

    public DmExecDistributedSqlRequestsDataType(string? executionId,
        int? stepIndex,
        int? computeNodeId,
        int? distributionId,
        string? status,
        string? errorId,
        DateTime? startTime,
        DateTime? endTime,
        int? totalElapsedTime,
        long? rowCount,
        int? spid,
        string? command,
        int computePoolId)
    {
        _executionId = executionId;
        _stepIndex = stepIndex;
        _computeNodeId = computeNodeId;
        _distributionId = distributionId;
        _status = status;
        _errorId = errorId;
        _startTime = startTime;
        _endTime = endTime;
        _totalElapsedTime = totalElapsedTime;
        _rowCount = rowCount;
        _spid = spid;
        _command = command;
        _computePoolId = computePoolId;
    }

    public string? ExecutionId => _executionId;
    public int? StepIndex => _stepIndex;
    public int? ComputeNodeId => _computeNodeId;
    public int? DistributionId => _distributionId;
    public string? Status => _status;
    public string? ErrorId => _errorId;
    public DateTime? StartTime => _startTime;
    public DateTime? EndTime => _endTime;
    public int? TotalElapsedTime => _totalElapsedTime;
    public long? RowCount => _rowCount;
    public int? Spid => _spid;
    public string? Command => _command;
    public int ComputePoolId => _computePoolId;
}

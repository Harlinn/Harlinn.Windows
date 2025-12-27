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

public class DmExecExternalOperationsDataType
{
    readonly string? _executionId;
    readonly int? _stepIndex;
    readonly string? _operationType;
    readonly string? _operationName;
    readonly double? _mapProgress;
    readonly double? _reduceProgress;
    readonly int _computePoolId = 0;

    public DmExecExternalOperationsDataType( )
    {
    }

    public DmExecExternalOperationsDataType(string? executionId,
        int? stepIndex,
        string? operationType,
        string? operationName,
        double? mapProgress,
        double? reduceProgress,
        int computePoolId)
    {
        _executionId = executionId;
        _stepIndex = stepIndex;
        _operationType = operationType;
        _operationName = operationName;
        _mapProgress = mapProgress;
        _reduceProgress = reduceProgress;
        _computePoolId = computePoolId;
    }

    public string? ExecutionId => _executionId;
    public int? StepIndex => _stepIndex;
    public string? OperationType => _operationType;
    public string? OperationName => _operationName;
    public double? MapProgress => _mapProgress;
    public double? ReduceProgress => _reduceProgress;
    public int ComputePoolId => _computePoolId;
}

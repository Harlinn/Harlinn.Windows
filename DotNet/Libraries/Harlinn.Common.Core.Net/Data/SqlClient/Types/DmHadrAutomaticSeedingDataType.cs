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

public class DmHadrAutomaticSeedingDataType
{
    readonly DateTime _startTime;
    readonly DateTime? _completionTime;
    readonly Guid _agId;
    readonly Guid _agDbId;
    readonly Guid _agRemoteReplicaId;
    readonly Guid _operationId;
    readonly bool _isSource = false;
    readonly string _currentState = string.Empty;
    readonly bool _performedSeeding = false;
    readonly int? _failureState;
    readonly string? _failureStateDesc;
    readonly int? _errorCode;
    readonly int _numberOfAttempts = 0;

    public DmHadrAutomaticSeedingDataType( )
    {
    }

    public DmHadrAutomaticSeedingDataType(DateTime startTime,
        DateTime? completionTime,
        Guid agId,
        Guid agDbId,
        Guid agRemoteReplicaId,
        Guid operationId,
        bool isSource,
        string currentState,
        bool performedSeeding,
        int? failureState,
        string? failureStateDesc,
        int? errorCode,
        int numberOfAttempts)
    {
        _startTime = startTime;
        _completionTime = completionTime;
        _agId = agId;
        _agDbId = agDbId;
        _agRemoteReplicaId = agRemoteReplicaId;
        _operationId = operationId;
        _isSource = isSource;
        _currentState = currentState;
        _performedSeeding = performedSeeding;
        _failureState = failureState;
        _failureStateDesc = failureStateDesc;
        _errorCode = errorCode;
        _numberOfAttempts = numberOfAttempts;
    }

    public DateTime StartTime => _startTime;
    public DateTime? CompletionTime => _completionTime;
    public Guid AgId => _agId;
    public Guid AgDbId => _agDbId;
    public Guid AgRemoteReplicaId => _agRemoteReplicaId;
    public Guid OperationId => _operationId;
    public bool IsSource => _isSource;
    public string CurrentState => _currentState;
    public bool PerformedSeeding => _performedSeeding;
    public int? FailureState => _failureState;
    public string? FailureStateDesc => _failureStateDesc;
    public int? ErrorCode => _errorCode;
    public int NumberOfAttempts => _numberOfAttempts;
}

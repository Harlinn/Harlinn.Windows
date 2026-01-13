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

public class DmCdcErrorsDataType
{
    readonly int? _sessionId;
    readonly int? _phaseNumber;
    readonly DateTime? _entryTime;
    readonly int? _errorNumber;
    readonly int? _errorSeverity;
    readonly int? _errorState;
    readonly string? _errorMessage;
    readonly string? _startLsn;
    readonly string? _beginLsn;
    readonly string? _sequenceValue;

    public DmCdcErrorsDataType( )
    {
    }

    public DmCdcErrorsDataType(int? sessionId,
        int? phaseNumber,
        DateTime? entryTime,
        int? errorNumber,
        int? errorSeverity,
        int? errorState,
        string? errorMessage,
        string? startLsn,
        string? beginLsn,
        string? sequenceValue)
    {
        _sessionId = sessionId;
        _phaseNumber = phaseNumber;
        _entryTime = entryTime;
        _errorNumber = errorNumber;
        _errorSeverity = errorSeverity;
        _errorState = errorState;
        _errorMessage = errorMessage;
        _startLsn = startLsn;
        _beginLsn = beginLsn;
        _sequenceValue = sequenceValue;
    }

    public int? SessionId => _sessionId;
    public int? PhaseNumber => _phaseNumber;
    public DateTime? EntryTime => _entryTime;
    public int? ErrorNumber => _errorNumber;
    public int? ErrorSeverity => _errorSeverity;
    public int? ErrorState => _errorState;
    public string? ErrorMessage => _errorMessage;
    public string? StartLsn => _startLsn;
    public string? BeginLsn => _beginLsn;
    public string? SequenceValue => _sequenceValue;
}

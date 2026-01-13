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

public class DmDbRdaSchemaUpdateStatusDataType
{
    readonly int? _tableId;
    readonly int? _databaseId;
    readonly long? _taskId;
    readonly int? _taskType;
    readonly string? _taskTypeDesc;
    readonly int? _taskState;
    readonly string? _taskStateDesc;
    readonly DateTime? _startTimeUtc;
    readonly DateTime? _endTimeUtc;
    readonly int? _errorNumber;
    readonly int? _errorSeverity;
    readonly int? _errorState;

    public DmDbRdaSchemaUpdateStatusDataType( )
    {
    }

    public DmDbRdaSchemaUpdateStatusDataType(int? tableId,
        int? databaseId,
        long? taskId,
        int? taskType,
        string? taskTypeDesc,
        int? taskState,
        string? taskStateDesc,
        DateTime? startTimeUtc,
        DateTime? endTimeUtc,
        int? errorNumber,
        int? errorSeverity,
        int? errorState)
    {
        _tableId = tableId;
        _databaseId = databaseId;
        _taskId = taskId;
        _taskType = taskType;
        _taskTypeDesc = taskTypeDesc;
        _taskState = taskState;
        _taskStateDesc = taskStateDesc;
        _startTimeUtc = startTimeUtc;
        _endTimeUtc = endTimeUtc;
        _errorNumber = errorNumber;
        _errorSeverity = errorSeverity;
        _errorState = errorState;
    }

    public int? TableId => _tableId;
    public int? DatabaseId => _databaseId;
    public long? TaskId => _taskId;
    public int? TaskType => _taskType;
    public string? TaskTypeDesc => _taskTypeDesc;
    public int? TaskState => _taskState;
    public string? TaskStateDesc => _taskStateDesc;
    public DateTime? StartTimeUtc => _startTimeUtc;
    public DateTime? EndTimeUtc => _endTimeUtc;
    public int? ErrorNumber => _errorNumber;
    public int? ErrorSeverity => _errorSeverity;
    public int? ErrorState => _errorState;
}

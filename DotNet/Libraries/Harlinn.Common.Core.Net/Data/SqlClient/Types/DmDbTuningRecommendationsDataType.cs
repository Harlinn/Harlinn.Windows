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

public class DmDbTuningRecommendationsDataType
{
    readonly string? _name;
    readonly string? _type;
    readonly string? _reason;
    readonly DateTime? _validSince;
    readonly DateTime? _lastRefresh;
    readonly string? _state;
    readonly bool? _isExecutableAction;
    readonly bool? _isRevertableAction;
    readonly DateTime? _executeActionStartTime;
    readonly DateTime? _executeActionDuration;
    readonly string? _executeActionInitiatedBy;
    readonly DateTime? _executeActionInitiatedTime;
    readonly DateTime? _revertActionStartTime;
    readonly DateTime? _revertActionDuration;
    readonly string? _revertActionInitiatedBy;
    readonly DateTime? _revertActionInitiatedTime;
    readonly int? _score;
    readonly string? _details;

    public DmDbTuningRecommendationsDataType( )
    {
    }

    public DmDbTuningRecommendationsDataType(string? name,
        string? type,
        string? reason,
        DateTime? validSince,
        DateTime? lastRefresh,
        string? state,
        bool? isExecutableAction,
        bool? isRevertableAction,
        DateTime? executeActionStartTime,
        DateTime? executeActionDuration,
        string? executeActionInitiatedBy,
        DateTime? executeActionInitiatedTime,
        DateTime? revertActionStartTime,
        DateTime? revertActionDuration,
        string? revertActionInitiatedBy,
        DateTime? revertActionInitiatedTime,
        int? score,
        string? details)
    {
        _name = name;
        _type = type;
        _reason = reason;
        _validSince = validSince;
        _lastRefresh = lastRefresh;
        _state = state;
        _isExecutableAction = isExecutableAction;
        _isRevertableAction = isRevertableAction;
        _executeActionStartTime = executeActionStartTime;
        _executeActionDuration = executeActionDuration;
        _executeActionInitiatedBy = executeActionInitiatedBy;
        _executeActionInitiatedTime = executeActionInitiatedTime;
        _revertActionStartTime = revertActionStartTime;
        _revertActionDuration = revertActionDuration;
        _revertActionInitiatedBy = revertActionInitiatedBy;
        _revertActionInitiatedTime = revertActionInitiatedTime;
        _score = score;
        _details = details;
    }

    public string? Name => _name;
    public string? Type => _type;
    public string? Reason => _reason;
    public DateTime? ValidSince => _validSince;
    public DateTime? LastRefresh => _lastRefresh;
    public string? State => _state;
    public bool? IsExecutableAction => _isExecutableAction;
    public bool? IsRevertableAction => _isRevertableAction;
    public DateTime? ExecuteActionStartTime => _executeActionStartTime;
    public DateTime? ExecuteActionDuration => _executeActionDuration;
    public string? ExecuteActionInitiatedBy => _executeActionInitiatedBy;
    public DateTime? ExecuteActionInitiatedTime => _executeActionInitiatedTime;
    public DateTime? RevertActionStartTime => _revertActionStartTime;
    public DateTime? RevertActionDuration => _revertActionDuration;
    public string? RevertActionInitiatedBy => _revertActionInitiatedBy;
    public DateTime? RevertActionInitiatedTime => _revertActionInitiatedTime;
    public int? Score => _score;
    public string? Details => _details;
}

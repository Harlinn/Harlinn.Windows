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

public class ServerEventSessionsDataType
{
    readonly int _eventSessionId = 0;
    readonly string? _name;
    readonly string? _eventRetentionMode;
    readonly string? _eventRetentionModeDesc;
    readonly int? _maxDispatchLatency;
    readonly int? _maxMemory;
    readonly int? _maxEventSize;
    readonly string? _memoryPartitionMode;
    readonly string? _memoryPartitionModeDesc;
    readonly bool? _trackCausality;
    readonly bool? _startupState;
    readonly bool? _hasLongRunningTarget;

    public ServerEventSessionsDataType( )
    {
    }

    public ServerEventSessionsDataType(int eventSessionId,
        string? name,
        string? eventRetentionMode,
        string? eventRetentionModeDesc,
        int? maxDispatchLatency,
        int? maxMemory,
        int? maxEventSize,
        string? memoryPartitionMode,
        string? memoryPartitionModeDesc,
        bool? trackCausality,
        bool? startupState,
        bool? hasLongRunningTarget)
    {
        _eventSessionId = eventSessionId;
        _name = name;
        _eventRetentionMode = eventRetentionMode;
        _eventRetentionModeDesc = eventRetentionModeDesc;
        _maxDispatchLatency = maxDispatchLatency;
        _maxMemory = maxMemory;
        _maxEventSize = maxEventSize;
        _memoryPartitionMode = memoryPartitionMode;
        _memoryPartitionModeDesc = memoryPartitionModeDesc;
        _trackCausality = trackCausality;
        _startupState = startupState;
        _hasLongRunningTarget = hasLongRunningTarget;
    }

    public int EventSessionId => _eventSessionId;
    public string? Name => _name;
    public string? EventRetentionMode => _eventRetentionMode;
    public string? EventRetentionModeDesc => _eventRetentionModeDesc;
    public int? MaxDispatchLatency => _maxDispatchLatency;
    public int? MaxMemory => _maxMemory;
    public int? MaxEventSize => _maxEventSize;
    public string? MemoryPartitionMode => _memoryPartitionMode;
    public string? MemoryPartitionModeDesc => _memoryPartitionModeDesc;
    public bool? TrackCausality => _trackCausality;
    public bool? StartupState => _startupState;
    public bool? HasLongRunningTarget => _hasLongRunningTarget;
}

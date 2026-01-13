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

public class DatabaseQueryStoreOptionsDataType
{
    readonly short _desiredState = 0;
    readonly string? _desiredStateDesc;
    readonly short _actualState = 0;
    readonly string? _actualStateDesc;
    readonly int? _readonlyReason;
    readonly long? _currentStorageSizeMb;
    readonly long? _flushIntervalSeconds;
    readonly long? _intervalLengthMinutes;
    readonly long? _maxStorageSizeMb;
    readonly long? _staleQueryThresholdDays;
    readonly long? _maxPlansPerQuery;
    readonly short _queryCaptureMode = 0;
    readonly string? _queryCaptureModeDesc;
    readonly int? _capturePolicyExecutionCount;
    readonly long? _capturePolicyTotalCompileCpuTimeMs;
    readonly long? _capturePolicyTotalExecutionCpuTimeMs;
    readonly int? _capturePolicyStaleThresholdHours;
    readonly short _sizeBasedCleanupMode = 0;
    readonly string? _sizeBasedCleanupModeDesc;
    readonly short _waitStatsCaptureMode = 0;
    readonly string? _waitStatsCaptureModeDesc;
    readonly string? _actualStateAdditionalInfo;

    public DatabaseQueryStoreOptionsDataType( )
    {
    }

    public DatabaseQueryStoreOptionsDataType(short desiredState,
        string? desiredStateDesc,
        short actualState,
        string? actualStateDesc,
        int? readonlyReason,
        long? currentStorageSizeMb,
        long? flushIntervalSeconds,
        long? intervalLengthMinutes,
        long? maxStorageSizeMb,
        long? staleQueryThresholdDays,
        long? maxPlansPerQuery,
        short queryCaptureMode,
        string? queryCaptureModeDesc,
        int? capturePolicyExecutionCount,
        long? capturePolicyTotalCompileCpuTimeMs,
        long? capturePolicyTotalExecutionCpuTimeMs,
        int? capturePolicyStaleThresholdHours,
        short sizeBasedCleanupMode,
        string? sizeBasedCleanupModeDesc,
        short waitStatsCaptureMode,
        string? waitStatsCaptureModeDesc,
        string? actualStateAdditionalInfo)
    {
        _desiredState = desiredState;
        _desiredStateDesc = desiredStateDesc;
        _actualState = actualState;
        _actualStateDesc = actualStateDesc;
        _readonlyReason = readonlyReason;
        _currentStorageSizeMb = currentStorageSizeMb;
        _flushIntervalSeconds = flushIntervalSeconds;
        _intervalLengthMinutes = intervalLengthMinutes;
        _maxStorageSizeMb = maxStorageSizeMb;
        _staleQueryThresholdDays = staleQueryThresholdDays;
        _maxPlansPerQuery = maxPlansPerQuery;
        _queryCaptureMode = queryCaptureMode;
        _queryCaptureModeDesc = queryCaptureModeDesc;
        _capturePolicyExecutionCount = capturePolicyExecutionCount;
        _capturePolicyTotalCompileCpuTimeMs = capturePolicyTotalCompileCpuTimeMs;
        _capturePolicyTotalExecutionCpuTimeMs = capturePolicyTotalExecutionCpuTimeMs;
        _capturePolicyStaleThresholdHours = capturePolicyStaleThresholdHours;
        _sizeBasedCleanupMode = sizeBasedCleanupMode;
        _sizeBasedCleanupModeDesc = sizeBasedCleanupModeDesc;
        _waitStatsCaptureMode = waitStatsCaptureMode;
        _waitStatsCaptureModeDesc = waitStatsCaptureModeDesc;
        _actualStateAdditionalInfo = actualStateAdditionalInfo;
    }

    public short DesiredState => _desiredState;
    public string? DesiredStateDesc => _desiredStateDesc;
    public short ActualState => _actualState;
    public string? ActualStateDesc => _actualStateDesc;
    public int? ReadonlyReason => _readonlyReason;
    public long? CurrentStorageSizeMb => _currentStorageSizeMb;
    public long? FlushIntervalSeconds => _flushIntervalSeconds;
    public long? IntervalLengthMinutes => _intervalLengthMinutes;
    public long? MaxStorageSizeMb => _maxStorageSizeMb;
    public long? StaleQueryThresholdDays => _staleQueryThresholdDays;
    public long? MaxPlansPerQuery => _maxPlansPerQuery;
    public short QueryCaptureMode => _queryCaptureMode;
    public string? QueryCaptureModeDesc => _queryCaptureModeDesc;
    public int? CapturePolicyExecutionCount => _capturePolicyExecutionCount;
    public long? CapturePolicyTotalCompileCpuTimeMs => _capturePolicyTotalCompileCpuTimeMs;
    public long? CapturePolicyTotalExecutionCpuTimeMs => _capturePolicyTotalExecutionCpuTimeMs;
    public int? CapturePolicyStaleThresholdHours => _capturePolicyStaleThresholdHours;
    public short SizeBasedCleanupMode => _sizeBasedCleanupMode;
    public string? SizeBasedCleanupModeDesc => _sizeBasedCleanupModeDesc;
    public short WaitStatsCaptureMode => _waitStatsCaptureMode;
    public string? WaitStatsCaptureModeDesc => _waitStatsCaptureModeDesc;
    public string? ActualStateAdditionalInfo => _actualStateAdditionalInfo;
}

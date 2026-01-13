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

public class DmHadrPhysicalSeedingStatsDataType
{
    readonly Guid _localPhysicalSeedingId;
    readonly Guid? _remotePhysicalSeedingId;
    readonly int _localDatabaseId = 0;
    readonly string? _localDatabaseName;
    readonly string? _remoteMachineName;
    readonly string? _roleDesc;
    readonly string? _internalStateDesc;
    readonly long? _transferRateBytesPerSecond;
    readonly long? _transferredSizeBytes;
    readonly long? _databaseSizeBytes;
    readonly DateTime? _startTimeUtc;
    readonly DateTime? _endTimeUtc;
    readonly DateTime? _estimateTimeCompleteUtc;
    readonly long? _totalDiskIoWaitTimeMs;
    readonly long? _totalNetworkWaitTimeMs;
    readonly int? _failureCode;
    readonly string? _failureMessage;
    readonly DateTime? _failureTimeUtc;
    readonly bool? _isCompressionEnabled;

    public DmHadrPhysicalSeedingStatsDataType( )
    {
    }

    public DmHadrPhysicalSeedingStatsDataType(Guid localPhysicalSeedingId,
        Guid? remotePhysicalSeedingId,
        int localDatabaseId,
        string? localDatabaseName,
        string? remoteMachineName,
        string? roleDesc,
        string? internalStateDesc,
        long? transferRateBytesPerSecond,
        long? transferredSizeBytes,
        long? databaseSizeBytes,
        DateTime? startTimeUtc,
        DateTime? endTimeUtc,
        DateTime? estimateTimeCompleteUtc,
        long? totalDiskIoWaitTimeMs,
        long? totalNetworkWaitTimeMs,
        int? failureCode,
        string? failureMessage,
        DateTime? failureTimeUtc,
        bool? isCompressionEnabled)
    {
        _localPhysicalSeedingId = localPhysicalSeedingId;
        _remotePhysicalSeedingId = remotePhysicalSeedingId;
        _localDatabaseId = localDatabaseId;
        _localDatabaseName = localDatabaseName;
        _remoteMachineName = remoteMachineName;
        _roleDesc = roleDesc;
        _internalStateDesc = internalStateDesc;
        _transferRateBytesPerSecond = transferRateBytesPerSecond;
        _transferredSizeBytes = transferredSizeBytes;
        _databaseSizeBytes = databaseSizeBytes;
        _startTimeUtc = startTimeUtc;
        _endTimeUtc = endTimeUtc;
        _estimateTimeCompleteUtc = estimateTimeCompleteUtc;
        _totalDiskIoWaitTimeMs = totalDiskIoWaitTimeMs;
        _totalNetworkWaitTimeMs = totalNetworkWaitTimeMs;
        _failureCode = failureCode;
        _failureMessage = failureMessage;
        _failureTimeUtc = failureTimeUtc;
        _isCompressionEnabled = isCompressionEnabled;
    }

    public Guid LocalPhysicalSeedingId => _localPhysicalSeedingId;
    public Guid? RemotePhysicalSeedingId => _remotePhysicalSeedingId;
    public int LocalDatabaseId => _localDatabaseId;
    public string? LocalDatabaseName => _localDatabaseName;
    public string? RemoteMachineName => _remoteMachineName;
    public string? RoleDesc => _roleDesc;
    public string? InternalStateDesc => _internalStateDesc;
    public long? TransferRateBytesPerSecond => _transferRateBytesPerSecond;
    public long? TransferredSizeBytes => _transferredSizeBytes;
    public long? DatabaseSizeBytes => _databaseSizeBytes;
    public DateTime? StartTimeUtc => _startTimeUtc;
    public DateTime? EndTimeUtc => _endTimeUtc;
    public DateTime? EstimateTimeCompleteUtc => _estimateTimeCompleteUtc;
    public long? TotalDiskIoWaitTimeMs => _totalDiskIoWaitTimeMs;
    public long? TotalNetworkWaitTimeMs => _totalNetworkWaitTimeMs;
    public int? FailureCode => _failureCode;
    public string? FailureMessage => _failureMessage;
    public DateTime? FailureTimeUtc => _failureTimeUtc;
    public bool? IsCompressionEnabled => _isCompressionEnabled;
}

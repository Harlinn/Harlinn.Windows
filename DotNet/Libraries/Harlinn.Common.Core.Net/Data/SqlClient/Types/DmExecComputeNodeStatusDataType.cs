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

public class DmExecComputeNodeStatusDataType
{
    readonly int? _computeNodeId;
    readonly int? _processId;
    readonly string? _processName;
    readonly long? _allocatedMemory;
    readonly long? _availableMemory;
    readonly long? _processCpuUsage;
    readonly long? _totalCpuUsage;
    readonly long? _threadCount;
    readonly long? _handleCount;
    readonly long? _totalElapsedTime;
    readonly bool? _isAvailable;
    readonly DateTime? _sentTime;
    readonly DateTime? _receivedTime;
    readonly string? _errorId;
    readonly int _computePoolId = 0;

    public DmExecComputeNodeStatusDataType( )
    {
    }

    public DmExecComputeNodeStatusDataType(int? computeNodeId,
        int? processId,
        string? processName,
        long? allocatedMemory,
        long? availableMemory,
        long? processCpuUsage,
        long? totalCpuUsage,
        long? threadCount,
        long? handleCount,
        long? totalElapsedTime,
        bool? isAvailable,
        DateTime? sentTime,
        DateTime? receivedTime,
        string? errorId,
        int computePoolId)
    {
        _computeNodeId = computeNodeId;
        _processId = processId;
        _processName = processName;
        _allocatedMemory = allocatedMemory;
        _availableMemory = availableMemory;
        _processCpuUsage = processCpuUsage;
        _totalCpuUsage = totalCpuUsage;
        _threadCount = threadCount;
        _handleCount = handleCount;
        _totalElapsedTime = totalElapsedTime;
        _isAvailable = isAvailable;
        _sentTime = sentTime;
        _receivedTime = receivedTime;
        _errorId = errorId;
        _computePoolId = computePoolId;
    }

    public int? ComputeNodeId => _computeNodeId;
    public int? ProcessId => _processId;
    public string? ProcessName => _processName;
    public long? AllocatedMemory => _allocatedMemory;
    public long? AvailableMemory => _availableMemory;
    public long? ProcessCpuUsage => _processCpuUsage;
    public long? TotalCpuUsage => _totalCpuUsage;
    public long? ThreadCount => _threadCount;
    public long? HandleCount => _handleCount;
    public long? TotalElapsedTime => _totalElapsedTime;
    public bool? IsAvailable => _isAvailable;
    public DateTime? SentTime => _sentTime;
    public DateTime? ReceivedTime => _receivedTime;
    public string? ErrorId => _errorId;
    public int ComputePoolId => _computePoolId;
}

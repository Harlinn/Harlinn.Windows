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

public class DmOsNodesDataType
{
    readonly short _nodeId = 0;
    readonly string _nodeStateDesc = string.Empty;
    readonly byte[] _memoryObjectAddress = Array.Empty<byte>();
    readonly byte[] _memoryClerkAddress = Array.Empty<byte>();
    readonly byte[]? _ioCompletionWorkerAddress;
    readonly short _memoryNodeId = 0;
    readonly long _cpuAffinityMask = 0;
    readonly short _onlineSchedulerCount = 0;
    readonly short _idleSchedulerCount = 0;
    readonly int _activeWorkerCount = 0;
    readonly int _avgLoadBalance = 0;
    readonly long _timerTaskAffinityMask = 0;
    readonly long _permanentTaskAffinityMask = 0;
    readonly bool _resourceMonitorState = false;
    readonly long _onlineSchedulerMask = 0;
    readonly short _processorGroup = 0;
    readonly int _cpuCount = 0;

    public DmOsNodesDataType( )
    {
    }

    public DmOsNodesDataType(short nodeId,
        string nodeStateDesc,
        byte[] memoryObjectAddress,
        byte[] memoryClerkAddress,
        byte[]? ioCompletionWorkerAddress,
        short memoryNodeId,
        long cpuAffinityMask,
        short onlineSchedulerCount,
        short idleSchedulerCount,
        int activeWorkerCount,
        int avgLoadBalance,
        long timerTaskAffinityMask,
        long permanentTaskAffinityMask,
        bool resourceMonitorState,
        long onlineSchedulerMask,
        short processorGroup,
        int cpuCount)
    {
        _nodeId = nodeId;
        _nodeStateDesc = nodeStateDesc;
        _memoryObjectAddress = memoryObjectAddress;
        _memoryClerkAddress = memoryClerkAddress;
        _ioCompletionWorkerAddress = ioCompletionWorkerAddress;
        _memoryNodeId = memoryNodeId;
        _cpuAffinityMask = cpuAffinityMask;
        _onlineSchedulerCount = onlineSchedulerCount;
        _idleSchedulerCount = idleSchedulerCount;
        _activeWorkerCount = activeWorkerCount;
        _avgLoadBalance = avgLoadBalance;
        _timerTaskAffinityMask = timerTaskAffinityMask;
        _permanentTaskAffinityMask = permanentTaskAffinityMask;
        _resourceMonitorState = resourceMonitorState;
        _onlineSchedulerMask = onlineSchedulerMask;
        _processorGroup = processorGroup;
        _cpuCount = cpuCount;
    }

    public short NodeId => _nodeId;
    public string NodeStateDesc => _nodeStateDesc;
    public byte[] MemoryObjectAddress => _memoryObjectAddress;
    public byte[] MemoryClerkAddress => _memoryClerkAddress;
    public byte[]? IoCompletionWorkerAddress => _ioCompletionWorkerAddress;
    public short MemoryNodeId => _memoryNodeId;
    public long CpuAffinityMask => _cpuAffinityMask;
    public short OnlineSchedulerCount => _onlineSchedulerCount;
    public short IdleSchedulerCount => _idleSchedulerCount;
    public int ActiveWorkerCount => _activeWorkerCount;
    public int AvgLoadBalance => _avgLoadBalance;
    public long TimerTaskAffinityMask => _timerTaskAffinityMask;
    public long PermanentTaskAffinityMask => _permanentTaskAffinityMask;
    public bool ResourceMonitorState => _resourceMonitorState;
    public long OnlineSchedulerMask => _onlineSchedulerMask;
    public short ProcessorGroup => _processorGroup;
    public int CpuCount => _cpuCount;
}

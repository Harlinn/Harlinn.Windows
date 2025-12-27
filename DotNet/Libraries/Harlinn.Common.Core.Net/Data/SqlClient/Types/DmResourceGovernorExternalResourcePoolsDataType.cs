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

public class DmResourceGovernorExternalResourcePoolsDataType
{
    readonly int _externalPoolId = 0;
    readonly string _name = string.Empty;
    readonly long _poolVersion = 0;
    readonly int _maxCpuPercent = 0;
    readonly int _maxProcesses = 0;
    readonly int _maxMemoryPercent = 0;
    readonly DateTime _statisticsStartTime;
    readonly long _peakMemoryKb = 0;
    readonly long _writeIoCount = 0;
    readonly long _readIoCount = 0;
    readonly long _totalCpuKernelMs = 0;
    readonly long _totalCpuUserMs = 0;
    readonly long _activeProcessesCount = 0;

    public DmResourceGovernorExternalResourcePoolsDataType( )
    {
    }

    public DmResourceGovernorExternalResourcePoolsDataType(int externalPoolId,
        string name,
        long poolVersion,
        int maxCpuPercent,
        int maxProcesses,
        int maxMemoryPercent,
        DateTime statisticsStartTime,
        long peakMemoryKb,
        long writeIoCount,
        long readIoCount,
        long totalCpuKernelMs,
        long totalCpuUserMs,
        long activeProcessesCount)
    {
        _externalPoolId = externalPoolId;
        _name = name;
        _poolVersion = poolVersion;
        _maxCpuPercent = maxCpuPercent;
        _maxProcesses = maxProcesses;
        _maxMemoryPercent = maxMemoryPercent;
        _statisticsStartTime = statisticsStartTime;
        _peakMemoryKb = peakMemoryKb;
        _writeIoCount = writeIoCount;
        _readIoCount = readIoCount;
        _totalCpuKernelMs = totalCpuKernelMs;
        _totalCpuUserMs = totalCpuUserMs;
        _activeProcessesCount = activeProcessesCount;
    }

    public int ExternalPoolId => _externalPoolId;
    public string Name => _name;
    public long PoolVersion => _poolVersion;
    public int MaxCpuPercent => _maxCpuPercent;
    public int MaxProcesses => _maxProcesses;
    public int MaxMemoryPercent => _maxMemoryPercent;
    public DateTime StatisticsStartTime => _statisticsStartTime;
    public long PeakMemoryKb => _peakMemoryKb;
    public long WriteIoCount => _writeIoCount;
    public long ReadIoCount => _readIoCount;
    public long TotalCpuKernelMs => _totalCpuKernelMs;
    public long TotalCpuUserMs => _totalCpuUserMs;
    public long ActiveProcessesCount => _activeProcessesCount;
}

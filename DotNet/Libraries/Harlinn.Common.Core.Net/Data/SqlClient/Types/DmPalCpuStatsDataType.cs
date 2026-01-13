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

public class DmPalCpuStatsDataType
{
    readonly long _uptimeSecs = 0;
    readonly double _loadavg1min = 0.0;
    readonly long _userTimeCs = 0;
    readonly long _niceTimeCs = 0;
    readonly long _systemTimeCs = 0;
    readonly long _idleTimeCs = 0;
    readonly long _iowaitTimeCs = 0;
    readonly long _irqTimeCs = 0;
    readonly long _softirqTimeCs = 0;
    readonly long _interruptCnt = 0;
    readonly long _cswCnt = 0;
    readonly long _bootTimeSecs = 0;
    readonly long _totalForksCnt = 0;
    readonly long _procRunableCnt = 0;
    readonly long _procIoblockedCnt = 0;
    readonly long _c3Time = 0;
    readonly long _c2Time = 0;
    readonly long _c1Time = 0;
    readonly long _c3Count = 0;
    readonly long _c2Count = 0;
    readonly long _c1Count = 0;

    public DmPalCpuStatsDataType( )
    {
    }

    public DmPalCpuStatsDataType(long uptimeSecs,
        double loadavg1min,
        long userTimeCs,
        long niceTimeCs,
        long systemTimeCs,
        long idleTimeCs,
        long iowaitTimeCs,
        long irqTimeCs,
        long softirqTimeCs,
        long interruptCnt,
        long cswCnt,
        long bootTimeSecs,
        long totalForksCnt,
        long procRunableCnt,
        long procIoblockedCnt,
        long c3Time,
        long c2Time,
        long c1Time,
        long c3Count,
        long c2Count,
        long c1Count)
    {
        _uptimeSecs = uptimeSecs;
        _loadavg1min = loadavg1min;
        _userTimeCs = userTimeCs;
        _niceTimeCs = niceTimeCs;
        _systemTimeCs = systemTimeCs;
        _idleTimeCs = idleTimeCs;
        _iowaitTimeCs = iowaitTimeCs;
        _irqTimeCs = irqTimeCs;
        _softirqTimeCs = softirqTimeCs;
        _interruptCnt = interruptCnt;
        _cswCnt = cswCnt;
        _bootTimeSecs = bootTimeSecs;
        _totalForksCnt = totalForksCnt;
        _procRunableCnt = procRunableCnt;
        _procIoblockedCnt = procIoblockedCnt;
        _c3Time = c3Time;
        _c2Time = c2Time;
        _c1Time = c1Time;
        _c3Count = c3Count;
        _c2Count = c2Count;
        _c1Count = c1Count;
    }

    public long UptimeSecs => _uptimeSecs;
    public double Loadavg1min => _loadavg1min;
    public long UserTimeCs => _userTimeCs;
    public long NiceTimeCs => _niceTimeCs;
    public long SystemTimeCs => _systemTimeCs;
    public long IdleTimeCs => _idleTimeCs;
    public long IowaitTimeCs => _iowaitTimeCs;
    public long IrqTimeCs => _irqTimeCs;
    public long SoftirqTimeCs => _softirqTimeCs;
    public long InterruptCnt => _interruptCnt;
    public long CswCnt => _cswCnt;
    public long BootTimeSecs => _bootTimeSecs;
    public long TotalForksCnt => _totalForksCnt;
    public long ProcRunableCnt => _procRunableCnt;
    public long ProcIoblockedCnt => _procIoblockedCnt;
    public long C3Time => _c3Time;
    public long C2Time => _c2Time;
    public long C1Time => _c1Time;
    public long C3Count => _c3Count;
    public long C2Count => _c2Count;
    public long C1Count => _c1Count;
}

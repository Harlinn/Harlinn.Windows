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

public class DmDbXtpGcCycleStatsDataType
{
    readonly long _cycleId = 0;
    readonly long _ticksAtCycleStart = 0;
    readonly long _ticksAtCycleEnd = 0;
    readonly int _nodeId = 0;
    readonly long _baseGeneration = 0;
    readonly long _xactsCopiedToLocal = 0;
    readonly long _xactsInGen0 = 0;
    readonly long _xactsInGen1 = 0;
    readonly long _xactsInGen2 = 0;
    readonly long _xactsInGen3 = 0;
    readonly long _xactsInGen4 = 0;
    readonly long _xactsInGen5 = 0;
    readonly long _xactsInGen6 = 0;
    readonly long _xactsInGen7 = 0;
    readonly long _xactsInGen8 = 0;
    readonly long _xactsInGen9 = 0;
    readonly long _xactsInGen10 = 0;
    readonly long _xactsInGen11 = 0;
    readonly long _xactsInGen12 = 0;
    readonly long _xactsInGen13 = 0;
    readonly long _xactsInGen14 = 0;
    readonly long _xactsInGen15 = 0;

    public DmDbXtpGcCycleStatsDataType( )
    {
    }

    public DmDbXtpGcCycleStatsDataType(long cycleId,
        long ticksAtCycleStart,
        long ticksAtCycleEnd,
        int nodeId,
        long baseGeneration,
        long xactsCopiedToLocal,
        long xactsInGen0,
        long xactsInGen1,
        long xactsInGen2,
        long xactsInGen3,
        long xactsInGen4,
        long xactsInGen5,
        long xactsInGen6,
        long xactsInGen7,
        long xactsInGen8,
        long xactsInGen9,
        long xactsInGen10,
        long xactsInGen11,
        long xactsInGen12,
        long xactsInGen13,
        long xactsInGen14,
        long xactsInGen15)
    {
        _cycleId = cycleId;
        _ticksAtCycleStart = ticksAtCycleStart;
        _ticksAtCycleEnd = ticksAtCycleEnd;
        _nodeId = nodeId;
        _baseGeneration = baseGeneration;
        _xactsCopiedToLocal = xactsCopiedToLocal;
        _xactsInGen0 = xactsInGen0;
        _xactsInGen1 = xactsInGen1;
        _xactsInGen2 = xactsInGen2;
        _xactsInGen3 = xactsInGen3;
        _xactsInGen4 = xactsInGen4;
        _xactsInGen5 = xactsInGen5;
        _xactsInGen6 = xactsInGen6;
        _xactsInGen7 = xactsInGen7;
        _xactsInGen8 = xactsInGen8;
        _xactsInGen9 = xactsInGen9;
        _xactsInGen10 = xactsInGen10;
        _xactsInGen11 = xactsInGen11;
        _xactsInGen12 = xactsInGen12;
        _xactsInGen13 = xactsInGen13;
        _xactsInGen14 = xactsInGen14;
        _xactsInGen15 = xactsInGen15;
    }

    public long CycleId => _cycleId;
    public long TicksAtCycleStart => _ticksAtCycleStart;
    public long TicksAtCycleEnd => _ticksAtCycleEnd;
    public int NodeId => _nodeId;
    public long BaseGeneration => _baseGeneration;
    public long XactsCopiedToLocal => _xactsCopiedToLocal;
    public long XactsInGen0 => _xactsInGen0;
    public long XactsInGen1 => _xactsInGen1;
    public long XactsInGen2 => _xactsInGen2;
    public long XactsInGen3 => _xactsInGen3;
    public long XactsInGen4 => _xactsInGen4;
    public long XactsInGen5 => _xactsInGen5;
    public long XactsInGen6 => _xactsInGen6;
    public long XactsInGen7 => _xactsInGen7;
    public long XactsInGen8 => _xactsInGen8;
    public long XactsInGen9 => _xactsInGen9;
    public long XactsInGen10 => _xactsInGen10;
    public long XactsInGen11 => _xactsInGen11;
    public long XactsInGen12 => _xactsInGen12;
    public long XactsInGen13 => _xactsInGen13;
    public long XactsInGen14 => _xactsInGen14;
    public long XactsInGen15 => _xactsInGen15;
}

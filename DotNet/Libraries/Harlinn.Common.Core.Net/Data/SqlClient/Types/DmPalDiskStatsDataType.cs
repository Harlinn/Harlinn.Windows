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

public class DmPalDiskStatsDataType
{
    readonly string _devName = string.Empty;
    readonly long _majorNum = 0;
    readonly long _minorNum = 0;
    readonly long _readsCompleted = 0;
    readonly long _readsMerged = 0;
    readonly long _sectorsRead = 0;
    readonly long _readTimeMs = 0;
    readonly long _writesCompleted = 0;
    readonly long _writesMerged = 0;
    readonly long _sectorsWritten = 0;
    readonly long _writeTimeMs = 0;
    readonly long _iosInProgess = 0;
    readonly long _ioTimeMs = 0;
    readonly long _weightedIoTimeMs = 0;

    public DmPalDiskStatsDataType( )
    {
    }

    public DmPalDiskStatsDataType(string devName,
        long majorNum,
        long minorNum,
        long readsCompleted,
        long readsMerged,
        long sectorsRead,
        long readTimeMs,
        long writesCompleted,
        long writesMerged,
        long sectorsWritten,
        long writeTimeMs,
        long iosInProgess,
        long ioTimeMs,
        long weightedIoTimeMs)
    {
        _devName = devName;
        _majorNum = majorNum;
        _minorNum = minorNum;
        _readsCompleted = readsCompleted;
        _readsMerged = readsMerged;
        _sectorsRead = sectorsRead;
        _readTimeMs = readTimeMs;
        _writesCompleted = writesCompleted;
        _writesMerged = writesMerged;
        _sectorsWritten = sectorsWritten;
        _writeTimeMs = writeTimeMs;
        _iosInProgess = iosInProgess;
        _ioTimeMs = ioTimeMs;
        _weightedIoTimeMs = weightedIoTimeMs;
    }

    public string DevName => _devName;
    public long MajorNum => _majorNum;
    public long MinorNum => _minorNum;
    public long ReadsCompleted => _readsCompleted;
    public long ReadsMerged => _readsMerged;
    public long SectorsRead => _sectorsRead;
    public long ReadTimeMs => _readTimeMs;
    public long WritesCompleted => _writesCompleted;
    public long WritesMerged => _writesMerged;
    public long SectorsWritten => _sectorsWritten;
    public long WriteTimeMs => _writeTimeMs;
    public long IosInProgess => _iosInProgess;
    public long IoTimeMs => _ioTimeMs;
    public long WeightedIoTimeMs => _weightedIoTimeMs;
}

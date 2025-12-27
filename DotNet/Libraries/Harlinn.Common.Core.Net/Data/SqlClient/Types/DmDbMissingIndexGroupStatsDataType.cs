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

public class DmDbMissingIndexGroupStatsDataType
{
    readonly int _groupHandle = 0;
    readonly long? _uniqueCompiles;
    readonly long? _userSeeks;
    readonly long? _userScans;
    readonly DateTime? _lastUserSeek;
    readonly DateTime? _lastUserScan;
    readonly double? _avgTotalUserCost;
    readonly double? _avgUserImpact;
    readonly long? _systemSeeks;
    readonly long? _systemScans;
    readonly DateTime? _lastSystemSeek;
    readonly DateTime? _lastSystemScan;
    readonly double? _avgTotalSystemCost;
    readonly double? _avgSystemImpact;

    public DmDbMissingIndexGroupStatsDataType( )
    {
    }

    public DmDbMissingIndexGroupStatsDataType(int groupHandle,
        long? uniqueCompiles,
        long? userSeeks,
        long? userScans,
        DateTime? lastUserSeek,
        DateTime? lastUserScan,
        double? avgTotalUserCost,
        double? avgUserImpact,
        long? systemSeeks,
        long? systemScans,
        DateTime? lastSystemSeek,
        DateTime? lastSystemScan,
        double? avgTotalSystemCost,
        double? avgSystemImpact)
    {
        _groupHandle = groupHandle;
        _uniqueCompiles = uniqueCompiles;
        _userSeeks = userSeeks;
        _userScans = userScans;
        _lastUserSeek = lastUserSeek;
        _lastUserScan = lastUserScan;
        _avgTotalUserCost = avgTotalUserCost;
        _avgUserImpact = avgUserImpact;
        _systemSeeks = systemSeeks;
        _systemScans = systemScans;
        _lastSystemSeek = lastSystemSeek;
        _lastSystemScan = lastSystemScan;
        _avgTotalSystemCost = avgTotalSystemCost;
        _avgSystemImpact = avgSystemImpact;
    }

    public int GroupHandle => _groupHandle;
    public long? UniqueCompiles => _uniqueCompiles;
    public long? UserSeeks => _userSeeks;
    public long? UserScans => _userScans;
    public DateTime? LastUserSeek => _lastUserSeek;
    public DateTime? LastUserScan => _lastUserScan;
    public double? AvgTotalUserCost => _avgTotalUserCost;
    public double? AvgUserImpact => _avgUserImpact;
    public long? SystemSeeks => _systemSeeks;
    public long? SystemScans => _systemScans;
    public DateTime? LastSystemSeek => _lastSystemSeek;
    public DateTime? LastSystemScan => _lastSystemScan;
    public double? AvgTotalSystemCost => _avgTotalSystemCost;
    public double? AvgSystemImpact => _avgSystemImpact;
}

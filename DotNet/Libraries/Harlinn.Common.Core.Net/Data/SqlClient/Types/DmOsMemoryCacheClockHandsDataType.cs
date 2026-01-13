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

public class DmOsMemoryCacheClockHandsDataType
{
    readonly byte[] _cacheAddress = Array.Empty<byte>();
    readonly string _name = string.Empty;
    readonly string _type = string.Empty;
    readonly string _clockHand = string.Empty;
    readonly string _clockStatus = string.Empty;
    readonly long _roundsCount = 0;
    readonly long _removedAllRoundsCount = 0;
    readonly long _updatedLastRoundCount = 0;
    readonly long _removedLastRoundCount = 0;
    readonly long _lastTickTime = 0;
    readonly long _roundStartTime = 0;
    readonly long _lastRoundStartTime = 0;

    public DmOsMemoryCacheClockHandsDataType( )
    {
    }

    public DmOsMemoryCacheClockHandsDataType(byte[] cacheAddress,
        string name,
        string type,
        string clockHand,
        string clockStatus,
        long roundsCount,
        long removedAllRoundsCount,
        long updatedLastRoundCount,
        long removedLastRoundCount,
        long lastTickTime,
        long roundStartTime,
        long lastRoundStartTime)
    {
        _cacheAddress = cacheAddress;
        _name = name;
        _type = type;
        _clockHand = clockHand;
        _clockStatus = clockStatus;
        _roundsCount = roundsCount;
        _removedAllRoundsCount = removedAllRoundsCount;
        _updatedLastRoundCount = updatedLastRoundCount;
        _removedLastRoundCount = removedLastRoundCount;
        _lastTickTime = lastTickTime;
        _roundStartTime = roundStartTime;
        _lastRoundStartTime = lastRoundStartTime;
    }

    public byte[] CacheAddress => _cacheAddress;
    public string Name => _name;
    public string Type => _type;
    public string ClockHand => _clockHand;
    public string ClockStatus => _clockStatus;
    public long RoundsCount => _roundsCount;
    public long RemovedAllRoundsCount => _removedAllRoundsCount;
    public long UpdatedLastRoundCount => _updatedLastRoundCount;
    public long RemovedLastRoundCount => _removedLastRoundCount;
    public long LastTickTime => _lastTickTime;
    public long RoundStartTime => _roundStartTime;
    public long LastRoundStartTime => _lastRoundStartTime;
}

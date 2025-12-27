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

public class DmOsSpinlockStatsDataType
{
    readonly string _name = string.Empty;
    readonly long? _collisions;
    readonly long? _spins;
    readonly float? _spinsPerCollision;
    readonly long? _sleepTime;
    readonly long? _backoffs;

    public DmOsSpinlockStatsDataType( )
    {
    }

    public DmOsSpinlockStatsDataType(string name,
        long? collisions,
        long? spins,
        float? spinsPerCollision,
        long? sleepTime,
        long? backoffs)
    {
        _name = name;
        _collisions = collisions;
        _spins = spins;
        _spinsPerCollision = spinsPerCollision;
        _sleepTime = sleepTime;
        _backoffs = backoffs;
    }

    public string Name => _name;
    public long? Collisions => _collisions;
    public long? Spins => _spins;
    public float? SpinsPerCollision => _spinsPerCollision;
    public long? SleepTime => _sleepTime;
    public long? Backoffs => _backoffs;
}

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

public class DmPalSpinlockStatsDataType
{
    readonly string _name = string.Empty;
    readonly long _collisions = 0;
    readonly long _spins = 0;
    readonly double _spinsPerCollision = 0.0;
    readonly long _sleepTime = 0;
    readonly long _backoffs = 0;

    public DmPalSpinlockStatsDataType( )
    {
    }

    public DmPalSpinlockStatsDataType(string name,
        long collisions,
        long spins,
        double spinsPerCollision,
        long sleepTime,
        long backoffs)
    {
        _name = name;
        _collisions = collisions;
        _spins = spins;
        _spinsPerCollision = spinsPerCollision;
        _sleepTime = sleepTime;
        _backoffs = backoffs;
    }

    public string Name => _name;
    public long Collisions => _collisions;
    public long Spins => _spins;
    public double SpinsPerCollision => _spinsPerCollision;
    public long SleepTime => _sleepTime;
    public long Backoffs => _backoffs;
}

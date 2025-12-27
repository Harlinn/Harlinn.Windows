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

public class DmOsMemoryBrokerClerksDataType
{
    readonly string _clerkName = string.Empty;
    readonly long _totalKb = 0;
    readonly long _simulatedKb = 0;
    readonly double _simulationBenefit = 0.0;
    readonly double _internalBenefit = 0.0;
    readonly double _externalBenefit = 0.0;
    readonly double _valueOfMemory = 0.0;
    readonly long _periodicFreedKb = 0;
    readonly long _internalFreedKb = 0;

    public DmOsMemoryBrokerClerksDataType( )
    {
    }

    public DmOsMemoryBrokerClerksDataType(string clerkName,
        long totalKb,
        long simulatedKb,
        double simulationBenefit,
        double internalBenefit,
        double externalBenefit,
        double valueOfMemory,
        long periodicFreedKb,
        long internalFreedKb)
    {
        _clerkName = clerkName;
        _totalKb = totalKb;
        _simulatedKb = simulatedKb;
        _simulationBenefit = simulationBenefit;
        _internalBenefit = internalBenefit;
        _externalBenefit = externalBenefit;
        _valueOfMemory = valueOfMemory;
        _periodicFreedKb = periodicFreedKb;
        _internalFreedKb = internalFreedKb;
    }

    public string ClerkName => _clerkName;
    public long TotalKb => _totalKb;
    public long SimulatedKb => _simulatedKb;
    public double SimulationBenefit => _simulationBenefit;
    public double InternalBenefit => _internalBenefit;
    public double ExternalBenefit => _externalBenefit;
    public double ValueOfMemory => _valueOfMemory;
    public long PeriodicFreedKb => _periodicFreedKb;
    public long InternalFreedKb => _internalFreedKb;
}

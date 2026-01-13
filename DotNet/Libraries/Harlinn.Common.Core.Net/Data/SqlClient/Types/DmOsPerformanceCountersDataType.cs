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

public class DmOsPerformanceCountersDataType
{
    readonly string _objectName = string.Empty;
    readonly string _counterName = string.Empty;
    readonly string? _instanceName;
    readonly long _cntrValue = 0;
    readonly int _cntrType = 0;

    public DmOsPerformanceCountersDataType( )
    {
    }

    public DmOsPerformanceCountersDataType(string objectName,
        string counterName,
        string? instanceName,
        long cntrValue,
        int cntrType)
    {
        _objectName = objectName;
        _counterName = counterName;
        _instanceName = instanceName;
        _cntrValue = cntrValue;
        _cntrType = cntrType;
    }

    public string ObjectName => _objectName;
    public string CounterName => _counterName;
    public string? InstanceName => _instanceName;
    public long CntrValue => _cntrValue;
    public int CntrType => _cntrType;
}

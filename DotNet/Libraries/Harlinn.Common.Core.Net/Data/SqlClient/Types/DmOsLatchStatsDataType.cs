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

public class DmOsLatchStatsDataType
{
    readonly string _latchClass = string.Empty;
    readonly long? _waitingRequestsCount;
    readonly long? _waitTimeMs;
    readonly long? _maxWaitTimeMs;

    public DmOsLatchStatsDataType( )
    {
    }

    public DmOsLatchStatsDataType(string latchClass,
        long? waitingRequestsCount,
        long? waitTimeMs,
        long? maxWaitTimeMs)
    {
        _latchClass = latchClass;
        _waitingRequestsCount = waitingRequestsCount;
        _waitTimeMs = waitTimeMs;
        _maxWaitTimeMs = maxWaitTimeMs;
    }

    public string LatchClass => _latchClass;
    public long? WaitingRequestsCount => _waitingRequestsCount;
    public long? WaitTimeMs => _waitTimeMs;
    public long? MaxWaitTimeMs => _maxWaitTimeMs;
}

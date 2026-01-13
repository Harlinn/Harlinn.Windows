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

public class DmPalWaitStatsDataType
{
    readonly string _waitType = string.Empty;
    readonly long _waitingThreadsCount = 0;
    readonly long _waitTimeMs = 0;
    readonly long _maxWaitTimeMs = 0;

    public DmPalWaitStatsDataType( )
    {
    }

    public DmPalWaitStatsDataType(string waitType,
        long waitingThreadsCount,
        long waitTimeMs,
        long maxWaitTimeMs)
    {
        _waitType = waitType;
        _waitingThreadsCount = waitingThreadsCount;
        _waitTimeMs = waitTimeMs;
        _maxWaitTimeMs = maxWaitTimeMs;
    }

    public string WaitType => _waitType;
    public long WaitingThreadsCount => _waitingThreadsCount;
    public long WaitTimeMs => _waitTimeMs;
    public long MaxWaitTimeMs => _maxWaitTimeMs;
}

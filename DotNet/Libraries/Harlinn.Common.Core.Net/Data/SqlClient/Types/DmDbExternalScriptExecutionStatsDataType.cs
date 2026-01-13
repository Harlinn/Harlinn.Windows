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

public class DmDbExternalScriptExecutionStatsDataType
{
    readonly int _externalLanguageId = 0;
    readonly string _counterName = string.Empty;
    readonly long _counterValue = 0;

    public DmDbExternalScriptExecutionStatsDataType( )
    {
    }

    public DmDbExternalScriptExecutionStatsDataType(int externalLanguageId,
        string counterName,
        long counterValue)
    {
        _externalLanguageId = externalLanguageId;
        _counterName = counterName;
        _counterValue = counterValue;
    }

    public int ExternalLanguageId => _externalLanguageId;
    public string CounterName => _counterName;
    public long CounterValue => _counterValue;
}

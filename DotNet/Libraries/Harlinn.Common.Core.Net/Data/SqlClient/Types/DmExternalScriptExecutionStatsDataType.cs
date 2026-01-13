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

public class DmExternalScriptExecutionStatsDataType
{
    readonly string? _language;
    readonly string _counterName = string.Empty;
    readonly long _counterValue = 0;

    public DmExternalScriptExecutionStatsDataType( )
    {
    }

    public DmExternalScriptExecutionStatsDataType(string? language,
        string counterName,
        long counterValue)
    {
        _language = language;
        _counterName = counterName;
        _counterValue = counterValue;
    }

    public string? Language => _language;
    public string CounterName => _counterName;
    public long CounterValue => _counterValue;
}

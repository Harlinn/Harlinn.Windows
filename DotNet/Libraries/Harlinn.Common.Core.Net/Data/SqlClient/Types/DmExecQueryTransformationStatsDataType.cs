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

public class DmExecQueryTransformationStatsDataType
{
    readonly string _name = string.Empty;
    readonly long _promiseTotal = 0;
    readonly double _promiseAvg = 0.0;
    readonly long _promised = 0;
    readonly long _builtSubstitute = 0;
    readonly long _succeeded = 0;

    public DmExecQueryTransformationStatsDataType( )
    {
    }

    public DmExecQueryTransformationStatsDataType(string name,
        long promiseTotal,
        double promiseAvg,
        long promised,
        long builtSubstitute,
        long succeeded)
    {
        _name = name;
        _promiseTotal = promiseTotal;
        _promiseAvg = promiseAvg;
        _promised = promised;
        _builtSubstitute = builtSubstitute;
        _succeeded = succeeded;
    }

    public string Name => _name;
    public long PromiseTotal => _promiseTotal;
    public double PromiseAvg => _promiseAvg;
    public long Promised => _promised;
    public long BuiltSubstitute => _builtSubstitute;
    public long Succeeded => _succeeded;
}

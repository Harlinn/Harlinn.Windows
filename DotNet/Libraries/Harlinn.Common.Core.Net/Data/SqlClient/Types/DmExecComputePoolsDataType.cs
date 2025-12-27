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

public class DmExecComputePoolsDataType
{
    readonly int _computePoolId = 0;
    readonly string? _name;
    readonly string _location = string.Empty;

    public DmExecComputePoolsDataType( )
    {
    }

    public DmExecComputePoolsDataType(int computePoolId,
        string? name,
        string location)
    {
        _computePoolId = computePoolId;
        _name = name;
        _location = location;
    }

    public int ComputePoolId => _computePoolId;
    public string? Name => _name;
    public string Location => _location;
}

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

public class DmExecComputeNodesDataType
{
    readonly int? _computeNodeId;
    readonly string? _type;
    readonly string? _name;
    readonly string? _address;
    readonly int _computePoolId = 0;

    public DmExecComputeNodesDataType( )
    {
    }

    public DmExecComputeNodesDataType(int? computeNodeId,
        string? type,
        string? name,
        string? address,
        int computePoolId)
    {
        _computeNodeId = computeNodeId;
        _type = type;
        _name = name;
        _address = address;
        _computePoolId = computePoolId;
    }

    public int? ComputeNodeId => _computeNodeId;
    public string? Type => _type;
    public string? Name => _name;
    public string? Address => _address;
    public int ComputePoolId => _computePoolId;
}

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

public class DmExecDmsServicesDataType
{
    readonly int? _dmsCoreId;
    readonly int? _computeNodeId;
    readonly string? _status;
    readonly int _computePoolId = 0;

    public DmExecDmsServicesDataType( )
    {
    }

    public DmExecDmsServicesDataType(int? dmsCoreId,
        int? computeNodeId,
        string? status,
        int computePoolId)
    {
        _dmsCoreId = dmsCoreId;
        _computeNodeId = computeNodeId;
        _status = status;
        _computePoolId = computePoolId;
    }

    public int? DmsCoreId => _dmsCoreId;
    public int? ComputeNodeId => _computeNodeId;
    public string? Status => _status;
    public int ComputePoolId => _computePoolId;
}

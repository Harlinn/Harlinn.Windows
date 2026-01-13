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

public class DmClrTasksDataType
{
    readonly byte[]? _taskAddress;
    readonly byte[]? _sosTaskAddress;
    readonly byte[]? _appdomainAddress;
    readonly string? _state;
    readonly string? _abortState;
    readonly string? _type;
    readonly int? _affinityCount;
    readonly int? _forcedYieldCount;

    public DmClrTasksDataType( )
    {
    }

    public DmClrTasksDataType(byte[]? taskAddress,
        byte[]? sosTaskAddress,
        byte[]? appdomainAddress,
        string? state,
        string? abortState,
        string? type,
        int? affinityCount,
        int? forcedYieldCount)
    {
        _taskAddress = taskAddress;
        _sosTaskAddress = sosTaskAddress;
        _appdomainAddress = appdomainAddress;
        _state = state;
        _abortState = abortState;
        _type = type;
        _affinityCount = affinityCount;
        _forcedYieldCount = forcedYieldCount;
    }

    public byte[]? TaskAddress => _taskAddress;
    public byte[]? SosTaskAddress => _sosTaskAddress;
    public byte[]? AppdomainAddress => _appdomainAddress;
    public string? State => _state;
    public string? AbortState => _abortState;
    public string? Type => _type;
    public int? AffinityCount => _affinityCount;
    public int? ForcedYieldCount => _forcedYieldCount;
}

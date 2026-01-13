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

public class DmExecComputeNodeErrorsDataType
{
    readonly string? _errorId;
    readonly string? _source;
    readonly string? _type;
    readonly DateTime? _createTime;
    readonly int? _computeNodeId;
    readonly string? _executionId;
    readonly int? _spid;
    readonly int? _threadId;
    readonly string? _details;
    readonly int _computePoolId = 0;

    public DmExecComputeNodeErrorsDataType( )
    {
    }

    public DmExecComputeNodeErrorsDataType(string? errorId,
        string? source,
        string? type,
        DateTime? createTime,
        int? computeNodeId,
        string? executionId,
        int? spid,
        int? threadId,
        string? details,
        int computePoolId)
    {
        _errorId = errorId;
        _source = source;
        _type = type;
        _createTime = createTime;
        _computeNodeId = computeNodeId;
        _executionId = executionId;
        _spid = spid;
        _threadId = threadId;
        _details = details;
        _computePoolId = computePoolId;
    }

    public string? ErrorId => _errorId;
    public string? Source => _source;
    public string? Type => _type;
    public DateTime? CreateTime => _createTime;
    public int? ComputeNodeId => _computeNodeId;
    public string? ExecutionId => _executionId;
    public int? Spid => _spid;
    public int? ThreadId => _threadId;
    public string? Details => _details;
    public int ComputePoolId => _computePoolId;
}

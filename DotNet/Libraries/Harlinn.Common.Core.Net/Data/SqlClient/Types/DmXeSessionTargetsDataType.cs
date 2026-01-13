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

public class DmXeSessionTargetsDataType
{
    readonly byte[] _eventSessionAddress = Array.Empty<byte>();
    readonly string _targetName = string.Empty;
    readonly Guid _targetPackageGuid;
    readonly long _executionCount = 0;
    readonly long _executionDurationMs = 0;
    readonly string? _targetData;
    readonly long _bytesWritten = 0;

    public DmXeSessionTargetsDataType( )
    {
    }

    public DmXeSessionTargetsDataType(byte[] eventSessionAddress,
        string targetName,
        Guid targetPackageGuid,
        long executionCount,
        long executionDurationMs,
        string? targetData,
        long bytesWritten)
    {
        _eventSessionAddress = eventSessionAddress;
        _targetName = targetName;
        _targetPackageGuid = targetPackageGuid;
        _executionCount = executionCount;
        _executionDurationMs = executionDurationMs;
        _targetData = targetData;
        _bytesWritten = bytesWritten;
    }

    public byte[] EventSessionAddress => _eventSessionAddress;
    public string TargetName => _targetName;
    public Guid TargetPackageGuid => _targetPackageGuid;
    public long ExecutionCount => _executionCount;
    public long ExecutionDurationMs => _executionDurationMs;
    public string? TargetData => _targetData;
    public long BytesWritten => _bytesWritten;
}

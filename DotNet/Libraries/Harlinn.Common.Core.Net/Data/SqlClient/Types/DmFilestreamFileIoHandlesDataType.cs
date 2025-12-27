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

public class DmFilestreamFileIoHandlesDataType
{
    readonly byte[]? _handleContextAddress;
    readonly int _creationRequestId = 0;
    readonly int _creationIrpId = 0;
    readonly int _handleId = 0;
    readonly byte[]? _creationClientThreadId;
    readonly byte[]? _creationClientProcessId;
    readonly byte[]? _filestreamTransactionId;
    readonly string _accessType = string.Empty;
    readonly string? _logicalPath;
    readonly string? _physicalPath;

    public DmFilestreamFileIoHandlesDataType( )
    {
    }

    public DmFilestreamFileIoHandlesDataType(byte[]? handleContextAddress,
        int creationRequestId,
        int creationIrpId,
        int handleId,
        byte[]? creationClientThreadId,
        byte[]? creationClientProcessId,
        byte[]? filestreamTransactionId,
        string accessType,
        string? logicalPath,
        string? physicalPath)
    {
        _handleContextAddress = handleContextAddress;
        _creationRequestId = creationRequestId;
        _creationIrpId = creationIrpId;
        _handleId = handleId;
        _creationClientThreadId = creationClientThreadId;
        _creationClientProcessId = creationClientProcessId;
        _filestreamTransactionId = filestreamTransactionId;
        _accessType = accessType;
        _logicalPath = logicalPath;
        _physicalPath = physicalPath;
    }

    public byte[]? HandleContextAddress => _handleContextAddress;
    public int CreationRequestId => _creationRequestId;
    public int CreationIrpId => _creationIrpId;
    public int HandleId => _handleId;
    public byte[]? CreationClientThreadId => _creationClientThreadId;
    public byte[]? CreationClientProcessId => _creationClientProcessId;
    public byte[]? FilestreamTransactionId => _filestreamTransactionId;
    public string AccessType => _accessType;
    public string? LogicalPath => _logicalPath;
    public string? PhysicalPath => _physicalPath;
}

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

public class DmFilestreamNonTransactedHandlesDataType
{
    readonly int? _databaseId;
    readonly int? _objectId;
    readonly int? _handleId;
    readonly int? _fileObjectType;
    readonly string? _fileObjectTypeDesc;
    readonly byte[]? _correlationProcessId;
    readonly byte[]? _correlationThreadId;
    readonly byte[]? _fileContext;
    readonly int? _state;
    readonly string? _stateDesc;
    readonly int? _currentWorkitemType;
    readonly string? _currentWorkitemTypeDesc;
    readonly long? _fcbId;
    readonly byte[]? _itemId;
    readonly bool? _isDirectory;
    readonly string? _itemName;
    readonly string? _openedFileName;
    readonly string? _databaseDirectoryName;
    readonly string? _tableDirectoryName;
    readonly string? _remainingFileName;
    readonly DateTime _openTime;
    readonly int? _flags;
    readonly int? _loginId;
    readonly string? _loginName;
    readonly byte[]? _loginSid;
    readonly bool? _readAccess;
    readonly bool? _writeAccess;
    readonly bool? _deleteAccess;
    readonly bool? _shareRead;
    readonly bool? _shareWrite;
    readonly bool? _shareDelete;
    readonly int? _createDisposition;

    public DmFilestreamNonTransactedHandlesDataType( )
    {
    }

    public DmFilestreamNonTransactedHandlesDataType(int? databaseId,
        int? objectId,
        int? handleId,
        int? fileObjectType,
        string? fileObjectTypeDesc,
        byte[]? correlationProcessId,
        byte[]? correlationThreadId,
        byte[]? fileContext,
        int? state,
        string? stateDesc,
        int? currentWorkitemType,
        string? currentWorkitemTypeDesc,
        long? fcbId,
        byte[]? itemId,
        bool? isDirectory,
        string? itemName,
        string? openedFileName,
        string? databaseDirectoryName,
        string? tableDirectoryName,
        string? remainingFileName,
        DateTime openTime,
        int? flags,
        int? loginId,
        string? loginName,
        byte[]? loginSid,
        bool? readAccess,
        bool? writeAccess,
        bool? deleteAccess,
        bool? shareRead,
        bool? shareWrite,
        bool? shareDelete,
        int? createDisposition)
    {
        _databaseId = databaseId;
        _objectId = objectId;
        _handleId = handleId;
        _fileObjectType = fileObjectType;
        _fileObjectTypeDesc = fileObjectTypeDesc;
        _correlationProcessId = correlationProcessId;
        _correlationThreadId = correlationThreadId;
        _fileContext = fileContext;
        _state = state;
        _stateDesc = stateDesc;
        _currentWorkitemType = currentWorkitemType;
        _currentWorkitemTypeDesc = currentWorkitemTypeDesc;
        _fcbId = fcbId;
        _itemId = itemId;
        _isDirectory = isDirectory;
        _itemName = itemName;
        _openedFileName = openedFileName;
        _databaseDirectoryName = databaseDirectoryName;
        _tableDirectoryName = tableDirectoryName;
        _remainingFileName = remainingFileName;
        _openTime = openTime;
        _flags = flags;
        _loginId = loginId;
        _loginName = loginName;
        _loginSid = loginSid;
        _readAccess = readAccess;
        _writeAccess = writeAccess;
        _deleteAccess = deleteAccess;
        _shareRead = shareRead;
        _shareWrite = shareWrite;
        _shareDelete = shareDelete;
        _createDisposition = createDisposition;
    }

    public int? DatabaseId => _databaseId;
    public int? ObjectId => _objectId;
    public int? HandleId => _handleId;
    public int? FileObjectType => _fileObjectType;
    public string? FileObjectTypeDesc => _fileObjectTypeDesc;
    public byte[]? CorrelationProcessId => _correlationProcessId;
    public byte[]? CorrelationThreadId => _correlationThreadId;
    public byte[]? FileContext => _fileContext;
    public int? State => _state;
    public string? StateDesc => _stateDesc;
    public int? CurrentWorkitemType => _currentWorkitemType;
    public string? CurrentWorkitemTypeDesc => _currentWorkitemTypeDesc;
    public long? FcbId => _fcbId;
    public byte[]? ItemId => _itemId;
    public bool? IsDirectory => _isDirectory;
    public string? ItemName => _itemName;
    public string? OpenedFileName => _openedFileName;
    public string? DatabaseDirectoryName => _databaseDirectoryName;
    public string? TableDirectoryName => _tableDirectoryName;
    public string? RemainingFileName => _remainingFileName;
    public DateTime OpenTime => _openTime;
    public int? Flags => _flags;
    public int? LoginId => _loginId;
    public string? LoginName => _loginName;
    public byte[]? LoginSid => _loginSid;
    public bool? ReadAccess => _readAccess;
    public bool? WriteAccess => _writeAccess;
    public bool? DeleteAccess => _deleteAccess;
    public bool? ShareRead => _shareRead;
    public bool? ShareWrite => _shareWrite;
    public bool? ShareDelete => _shareDelete;
    public int? CreateDisposition => _createDisposition;
}

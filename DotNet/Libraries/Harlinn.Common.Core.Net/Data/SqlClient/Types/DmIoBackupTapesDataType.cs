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

public class DmIoBackupTapesDataType
{
    readonly string _physicalDeviceName = string.Empty;
    readonly string? _logicalDeviceName;
    readonly int _status = 0;
    readonly string _statusDesc = string.Empty;
    readonly DateTime? _mountRequestTime;
    readonly DateTime? _mountExpirationTime;
    readonly string? _databaseName;
    readonly int? _spid;
    readonly int? _command;
    readonly string? _commandDesc;
    readonly int? _mediaFamilyId;
    readonly string? _mediaSetName;
    readonly Guid? _mediaSetGuid;
    readonly int? _mediaSequenceNumber;
    readonly int? _tapeOperation;
    readonly string? _tapeOperationDesc;
    readonly int? _mountRequestType;
    readonly string? _mountRequestTypeDesc;

    public DmIoBackupTapesDataType( )
    {
    }

    public DmIoBackupTapesDataType(string physicalDeviceName,
        string? logicalDeviceName,
        int status,
        string statusDesc,
        DateTime? mountRequestTime,
        DateTime? mountExpirationTime,
        string? databaseName,
        int? spid,
        int? command,
        string? commandDesc,
        int? mediaFamilyId,
        string? mediaSetName,
        Guid? mediaSetGuid,
        int? mediaSequenceNumber,
        int? tapeOperation,
        string? tapeOperationDesc,
        int? mountRequestType,
        string? mountRequestTypeDesc)
    {
        _physicalDeviceName = physicalDeviceName;
        _logicalDeviceName = logicalDeviceName;
        _status = status;
        _statusDesc = statusDesc;
        _mountRequestTime = mountRequestTime;
        _mountExpirationTime = mountExpirationTime;
        _databaseName = databaseName;
        _spid = spid;
        _command = command;
        _commandDesc = commandDesc;
        _mediaFamilyId = mediaFamilyId;
        _mediaSetName = mediaSetName;
        _mediaSetGuid = mediaSetGuid;
        _mediaSequenceNumber = mediaSequenceNumber;
        _tapeOperation = tapeOperation;
        _tapeOperationDesc = tapeOperationDesc;
        _mountRequestType = mountRequestType;
        _mountRequestTypeDesc = mountRequestTypeDesc;
    }

    public string PhysicalDeviceName => _physicalDeviceName;
    public string? LogicalDeviceName => _logicalDeviceName;
    public int Status => _status;
    public string StatusDesc => _statusDesc;
    public DateTime? MountRequestTime => _mountRequestTime;
    public DateTime? MountExpirationTime => _mountExpirationTime;
    public string? DatabaseName => _databaseName;
    public int? Spid => _spid;
    public int? Command => _command;
    public string? CommandDesc => _commandDesc;
    public int? MediaFamilyId => _mediaFamilyId;
    public string? MediaSetName => _mediaSetName;
    public Guid? MediaSetGuid => _mediaSetGuid;
    public int? MediaSequenceNumber => _mediaSequenceNumber;
    public int? TapeOperation => _tapeOperation;
    public string? TapeOperationDesc => _tapeOperationDesc;
    public int? MountRequestType => _mountRequestType;
    public string? MountRequestTypeDesc => _mountRequestTypeDesc;
}

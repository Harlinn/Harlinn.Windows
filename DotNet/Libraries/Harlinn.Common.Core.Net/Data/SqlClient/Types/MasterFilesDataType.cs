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

public class MasterFilesDataType
{
    readonly int _databaseId = 0;
    readonly int _fileId = 0;
    readonly Guid? _fileGuid;
    readonly byte _type = 0;
    readonly string? _typeDesc;
    readonly int _dataSpaceId = 0;
    readonly string _name = string.Empty;
    readonly string _physicalName = string.Empty;
    readonly byte? _state;
    readonly string? _stateDesc;
    readonly int _size = 0;
    readonly int _maxSize = 0;
    readonly int _growth = 0;
    readonly bool _isMediaReadOnly = false;
    readonly bool _isReadOnly = false;
    readonly bool _isSparse = false;
    readonly bool _isPercentGrowth = false;
    readonly bool _isNameReserved = false;
    readonly bool _isPersistentLogBuffer = false;
    readonly object? _createLsn;
    readonly object? _dropLsn;
    readonly object? _readOnlyLsn;
    readonly object? _readWriteLsn;
    readonly object? _differentialBaseLsn;
    readonly Guid? _differentialBaseGuid;
    readonly DateTime? _differentialBaseTime;
    readonly object? _redoStartLsn;
    readonly Guid? _redoStartForkGuid;
    readonly object? _redoTargetLsn;
    readonly Guid? _redoTargetForkGuid;
    readonly object? _backupLsn;
    readonly int? _credentialId;

    public MasterFilesDataType( )
    {
    }

    public MasterFilesDataType(int databaseId,
        int fileId,
        Guid? fileGuid,
        byte type,
        string? typeDesc,
        int dataSpaceId,
        string name,
        string physicalName,
        byte? state,
        string? stateDesc,
        int size,
        int maxSize,
        int growth,
        bool isMediaReadOnly,
        bool isReadOnly,
        bool isSparse,
        bool isPercentGrowth,
        bool isNameReserved,
        bool isPersistentLogBuffer,
        object? createLsn,
        object? dropLsn,
        object? readOnlyLsn,
        object? readWriteLsn,
        object? differentialBaseLsn,
        Guid? differentialBaseGuid,
        DateTime? differentialBaseTime,
        object? redoStartLsn,
        Guid? redoStartForkGuid,
        object? redoTargetLsn,
        Guid? redoTargetForkGuid,
        object? backupLsn,
        int? credentialId)
    {
        _databaseId = databaseId;
        _fileId = fileId;
        _fileGuid = fileGuid;
        _type = type;
        _typeDesc = typeDesc;
        _dataSpaceId = dataSpaceId;
        _name = name;
        _physicalName = physicalName;
        _state = state;
        _stateDesc = stateDesc;
        _size = size;
        _maxSize = maxSize;
        _growth = growth;
        _isMediaReadOnly = isMediaReadOnly;
        _isReadOnly = isReadOnly;
        _isSparse = isSparse;
        _isPercentGrowth = isPercentGrowth;
        _isNameReserved = isNameReserved;
        _isPersistentLogBuffer = isPersistentLogBuffer;
        _createLsn = createLsn;
        _dropLsn = dropLsn;
        _readOnlyLsn = readOnlyLsn;
        _readWriteLsn = readWriteLsn;
        _differentialBaseLsn = differentialBaseLsn;
        _differentialBaseGuid = differentialBaseGuid;
        _differentialBaseTime = differentialBaseTime;
        _redoStartLsn = redoStartLsn;
        _redoStartForkGuid = redoStartForkGuid;
        _redoTargetLsn = redoTargetLsn;
        _redoTargetForkGuid = redoTargetForkGuid;
        _backupLsn = backupLsn;
        _credentialId = credentialId;
    }

    public int DatabaseId => _databaseId;
    public int FileId => _fileId;
    public Guid? FileGuid => _fileGuid;
    public byte Type => _type;
    public string? TypeDesc => _typeDesc;
    public int DataSpaceId => _dataSpaceId;
    public string Name => _name;
    public string PhysicalName => _physicalName;
    public byte? State => _state;
    public string? StateDesc => _stateDesc;
    public int Size => _size;
    public int MaxSize => _maxSize;
    public int Growth => _growth;
    public bool IsMediaReadOnly => _isMediaReadOnly;
    public bool IsReadOnly => _isReadOnly;
    public bool IsSparse => _isSparse;
    public bool IsPercentGrowth => _isPercentGrowth;
    public bool IsNameReserved => _isNameReserved;
    public bool IsPersistentLogBuffer => _isPersistentLogBuffer;
    public object? CreateLsn => _createLsn;
    public object? DropLsn => _dropLsn;
    public object? ReadOnlyLsn => _readOnlyLsn;
    public object? ReadWriteLsn => _readWriteLsn;
    public object? DifferentialBaseLsn => _differentialBaseLsn;
    public Guid? DifferentialBaseGuid => _differentialBaseGuid;
    public DateTime? DifferentialBaseTime => _differentialBaseTime;
    public object? RedoStartLsn => _redoStartLsn;
    public Guid? RedoStartForkGuid => _redoStartForkGuid;
    public object? RedoTargetLsn => _redoTargetLsn;
    public Guid? RedoTargetForkGuid => _redoTargetForkGuid;
    public object? BackupLsn => _backupLsn;
    public int? CredentialId => _credentialId;
}

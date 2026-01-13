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

public class DmDbXtpCheckpointFilesDataType
{
    readonly int _containerId = 0;
    readonly Guid _containerGuid;
    readonly Guid _checkpointFileId;
    readonly string _relativeFilePath = string.Empty;
    readonly short _fileType = 0;
    readonly string _fileTypeDesc = string.Empty;
    readonly int? _internalStorageSlot;
    readonly Guid? _checkpointPairFileId;
    readonly long _fileSizeInBytes = 0;
    readonly long? _fileSizeUsedInBytes;
    readonly long? _logicalRowCount;
    readonly short _state = 0;
    readonly string _stateDesc = string.Empty;
    readonly long? _lowerBoundTsn;
    readonly long? _upperBoundTsn;
    readonly long? _beginCheckpointId;
    readonly long? _endCheckpointId;
    readonly long? _lastUpdatedCheckpointId;
    readonly short? _encryptionStatus;
    readonly string? _encryptionStatusDesc;

    public DmDbXtpCheckpointFilesDataType( )
    {
    }

    public DmDbXtpCheckpointFilesDataType(int containerId,
        Guid containerGuid,
        Guid checkpointFileId,
        string relativeFilePath,
        short fileType,
        string fileTypeDesc,
        int? internalStorageSlot,
        Guid? checkpointPairFileId,
        long fileSizeInBytes,
        long? fileSizeUsedInBytes,
        long? logicalRowCount,
        short state,
        string stateDesc,
        long? lowerBoundTsn,
        long? upperBoundTsn,
        long? beginCheckpointId,
        long? endCheckpointId,
        long? lastUpdatedCheckpointId,
        short? encryptionStatus,
        string? encryptionStatusDesc)
    {
        _containerId = containerId;
        _containerGuid = containerGuid;
        _checkpointFileId = checkpointFileId;
        _relativeFilePath = relativeFilePath;
        _fileType = fileType;
        _fileTypeDesc = fileTypeDesc;
        _internalStorageSlot = internalStorageSlot;
        _checkpointPairFileId = checkpointPairFileId;
        _fileSizeInBytes = fileSizeInBytes;
        _fileSizeUsedInBytes = fileSizeUsedInBytes;
        _logicalRowCount = logicalRowCount;
        _state = state;
        _stateDesc = stateDesc;
        _lowerBoundTsn = lowerBoundTsn;
        _upperBoundTsn = upperBoundTsn;
        _beginCheckpointId = beginCheckpointId;
        _endCheckpointId = endCheckpointId;
        _lastUpdatedCheckpointId = lastUpdatedCheckpointId;
        _encryptionStatus = encryptionStatus;
        _encryptionStatusDesc = encryptionStatusDesc;
    }

    public int ContainerId => _containerId;
    public Guid ContainerGuid => _containerGuid;
    public Guid CheckpointFileId => _checkpointFileId;
    public string RelativeFilePath => _relativeFilePath;
    public short FileType => _fileType;
    public string FileTypeDesc => _fileTypeDesc;
    public int? InternalStorageSlot => _internalStorageSlot;
    public Guid? CheckpointPairFileId => _checkpointPairFileId;
    public long FileSizeInBytes => _fileSizeInBytes;
    public long? FileSizeUsedInBytes => _fileSizeUsedInBytes;
    public long? LogicalRowCount => _logicalRowCount;
    public short State => _state;
    public string StateDesc => _stateDesc;
    public long? LowerBoundTsn => _lowerBoundTsn;
    public long? UpperBoundTsn => _upperBoundTsn;
    public long? BeginCheckpointId => _beginCheckpointId;
    public long? EndCheckpointId => _endCheckpointId;
    public long? LastUpdatedCheckpointId => _lastUpdatedCheckpointId;
    public short? EncryptionStatus => _encryptionStatus;
    public string? EncryptionStatusDesc => _encryptionStatusDesc;
}

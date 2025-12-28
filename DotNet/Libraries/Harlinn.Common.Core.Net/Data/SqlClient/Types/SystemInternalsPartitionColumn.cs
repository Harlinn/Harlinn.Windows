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

public class SystemInternalsPartitionColumn
{
    readonly long _partitionId = 0;
    readonly int _partitionColumnId = 0;
    readonly long _modifiedCount = 0;
    readonly short? _maxInrowLength;
    readonly bool? _isReplicated;
    readonly bool? _isLoggedForReplication;
    readonly bool? _isDropped;
    readonly byte? _systemTypeId;
    readonly short? _maxLength;
    readonly byte? _precision;
    readonly byte? _scale;
    readonly string? _collationName;
    readonly bool? _isFilestream;
    readonly short _keyOrdinal = 0;
    readonly bool? _isNullable;
    readonly bool? _isDescendingKey;
    readonly bool? _isUniqueifier;
    readonly short? _leafOffset;
    readonly short? _internalOffset;
    readonly byte? _leafBitPosition;
    readonly byte? _internalBitPosition;
    readonly short? _leafNullBit;
    readonly short? _internalNullBit;
    readonly bool? _isAntiMatter;
    readonly Guid? _partitionColumnGuid;
    readonly bool? _isSparse;
    readonly bool _hasDefault = false;
    readonly object? _defaultValue;

    public SystemInternalsPartitionColumn( )
    {
    }

    public SystemInternalsPartitionColumn(long partitionId,
        int partitionColumnId,
        long modifiedCount,
        short? maxInrowLength,
        bool? isReplicated,
        bool? isLoggedForReplication,
        bool? isDropped,
        byte? systemTypeId,
        short? maxLength,
        byte? precision,
        byte? scale,
        string? collationName,
        bool? isFilestream,
        short keyOrdinal,
        bool? isNullable,
        bool? isDescendingKey,
        bool? isUniqueifier,
        short? leafOffset,
        short? internalOffset,
        byte? leafBitPosition,
        byte? internalBitPosition,
        short? leafNullBit,
        short? internalNullBit,
        bool? isAntiMatter,
        Guid? partitionColumnGuid,
        bool? isSparse,
        bool hasDefault,
        object? defaultValue)
    {
        _partitionId = partitionId;
        _partitionColumnId = partitionColumnId;
        _modifiedCount = modifiedCount;
        _maxInrowLength = maxInrowLength;
        _isReplicated = isReplicated;
        _isLoggedForReplication = isLoggedForReplication;
        _isDropped = isDropped;
        _systemTypeId = systemTypeId;
        _maxLength = maxLength;
        _precision = precision;
        _scale = scale;
        _collationName = collationName;
        _isFilestream = isFilestream;
        _keyOrdinal = keyOrdinal;
        _isNullable = isNullable;
        _isDescendingKey = isDescendingKey;
        _isUniqueifier = isUniqueifier;
        _leafOffset = leafOffset;
        _internalOffset = internalOffset;
        _leafBitPosition = leafBitPosition;
        _internalBitPosition = internalBitPosition;
        _leafNullBit = leafNullBit;
        _internalNullBit = internalNullBit;
        _isAntiMatter = isAntiMatter;
        _partitionColumnGuid = partitionColumnGuid;
        _isSparse = isSparse;
        _hasDefault = hasDefault;
        _defaultValue = defaultValue;
    }

    public long PartitionId => _partitionId;
    public int PartitionColumnId => _partitionColumnId;
    public long ModifiedCount => _modifiedCount;
    public short? MaxInrowLength => _maxInrowLength;
    public bool? IsReplicated => _isReplicated;
    public bool? IsLoggedForReplication => _isLoggedForReplication;
    public bool? IsDropped => _isDropped;
    public byte? SystemTypeId => _systemTypeId;
    public short? MaxLength => _maxLength;
    public byte? Precision => _precision;
    public byte? Scale => _scale;
    public string? CollationName => _collationName;
    public bool? IsFilestream => _isFilestream;
    public short KeyOrdinal => _keyOrdinal;
    public bool? IsNullable => _isNullable;
    public bool? IsDescendingKey => _isDescendingKey;
    public bool? IsUniqueifier => _isUniqueifier;
    public short? LeafOffset => _leafOffset;
    public short? InternalOffset => _internalOffset;
    public byte? LeafBitPosition => _leafBitPosition;
    public byte? InternalBitPosition => _internalBitPosition;
    public short? LeafNullBit => _leafNullBit;
    public short? InternalNullBit => _internalNullBit;
    public bool? IsAntiMatter => _isAntiMatter;
    public Guid? PartitionColumnGuid => _partitionColumnGuid;
    public bool? IsSparse => _isSparse;
    public bool HasDefault => _hasDefault;
    public object? DefaultValue => _defaultValue;
}

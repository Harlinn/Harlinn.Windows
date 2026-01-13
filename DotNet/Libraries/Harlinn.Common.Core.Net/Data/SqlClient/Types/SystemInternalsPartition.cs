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

public class SystemInternalsPartition
{
    readonly long _partitionId = 0;
    readonly int _objectId = 0;
    readonly int _indexId = 0;
    readonly int _partitionNumber = 0;
    readonly long _rows = 0;
    readonly short _filestreamFilegroupId = 0;
    readonly bool? _isOrphaned;
    readonly byte? _droppedLobColumnState;
    readonly bool? _isUnique;
    readonly bool? _isReplicated;
    readonly bool? _isLoggedForReplication;
    readonly bool _isSereplicated = false;
    readonly short _maxNullBitUsed = 0;
    readonly int _maxLeafLength = 0;
    readonly short _minLeafLength = 0;
    readonly short _maxInternalLength = 0;
    readonly short _minInternalLength = 0;
    readonly bool? _allowsNullableKeys;
    readonly bool? _allowRowLocks;
    readonly bool? _allowPageLocks;
    readonly bool? _isDataRowFormat;
    readonly bool? _isNotVersioned;
    readonly Guid? _filestreamGuid;
    readonly byte _ownertype = 0;
    readonly bool? _isColumnstore;
    readonly bool? _optimizeForSequentialKey;

    public SystemInternalsPartition( )
    {
    }

    public SystemInternalsPartition(long partitionId,
        int objectId,
        int indexId,
        int partitionNumber,
        long rows,
        short filestreamFilegroupId,
        bool? isOrphaned,
        byte? droppedLobColumnState,
        bool? isUnique,
        bool? isReplicated,
        bool? isLoggedForReplication,
        bool isSereplicated,
        short maxNullBitUsed,
        int maxLeafLength,
        short minLeafLength,
        short maxInternalLength,
        short minInternalLength,
        bool? allowsNullableKeys,
        bool? allowRowLocks,
        bool? allowPageLocks,
        bool? isDataRowFormat,
        bool? isNotVersioned,
        Guid? filestreamGuid,
        byte ownertype,
        bool? isColumnstore,
        bool? optimizeForSequentialKey)
    {
        _partitionId = partitionId;
        _objectId = objectId;
        _indexId = indexId;
        _partitionNumber = partitionNumber;
        _rows = rows;
        _filestreamFilegroupId = filestreamFilegroupId;
        _isOrphaned = isOrphaned;
        _droppedLobColumnState = droppedLobColumnState;
        _isUnique = isUnique;
        _isReplicated = isReplicated;
        _isLoggedForReplication = isLoggedForReplication;
        _isSereplicated = isSereplicated;
        _maxNullBitUsed = maxNullBitUsed;
        _maxLeafLength = maxLeafLength;
        _minLeafLength = minLeafLength;
        _maxInternalLength = maxInternalLength;
        _minInternalLength = minInternalLength;
        _allowsNullableKeys = allowsNullableKeys;
        _allowRowLocks = allowRowLocks;
        _allowPageLocks = allowPageLocks;
        _isDataRowFormat = isDataRowFormat;
        _isNotVersioned = isNotVersioned;
        _filestreamGuid = filestreamGuid;
        _ownertype = ownertype;
        _isColumnstore = isColumnstore;
        _optimizeForSequentialKey = optimizeForSequentialKey;
    }

    public long PartitionId => _partitionId;
    public int ObjectId => _objectId;
    public int IndexId => _indexId;
    public int PartitionNumber => _partitionNumber;
    public long Rows => _rows;
    public short FilestreamFilegroupId => _filestreamFilegroupId;
    public bool? IsOrphaned => _isOrphaned;
    public byte? DroppedLobColumnState => _droppedLobColumnState;
    public bool? IsUnique => _isUnique;
    public bool? IsReplicated => _isReplicated;
    public bool? IsLoggedForReplication => _isLoggedForReplication;
    public bool IsSereplicated => _isSereplicated;
    public short MaxNullBitUsed => _maxNullBitUsed;
    public int MaxLeafLength => _maxLeafLength;
    public short MinLeafLength => _minLeafLength;
    public short MaxInternalLength => _maxInternalLength;
    public short MinInternalLength => _minInternalLength;
    public bool? AllowsNullableKeys => _allowsNullableKeys;
    public bool? AllowRowLocks => _allowRowLocks;
    public bool? AllowPageLocks => _allowPageLocks;
    public bool? IsDataRowFormat => _isDataRowFormat;
    public bool? IsNotVersioned => _isNotVersioned;
    public Guid? FilestreamGuid => _filestreamGuid;
    public byte Ownertype => _ownertype;
    public bool? IsColumnstore => _isColumnstore;
    public bool? OptimizeForSequentialKey => _optimizeForSequentialKey;
}

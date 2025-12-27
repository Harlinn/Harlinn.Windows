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

public class DmDbPartitionStatsDataType
{
    readonly long? _partitionId;
    readonly int _objectId = 0;
    readonly int _indexId = 0;
    readonly int _partitionNumber = 0;
    readonly long? _inRowDataPageCount;
    readonly long? _inRowUsedPageCount;
    readonly long? _inRowReservedPageCount;
    readonly long? _lobUsedPageCount;
    readonly long? _lobReservedPageCount;
    readonly long? _rowOverflowUsedPageCount;
    readonly long? _rowOverflowReservedPageCount;
    readonly long? _usedPageCount;
    readonly long? _reservedPageCount;
    readonly long? _rowCount;

    public DmDbPartitionStatsDataType( )
    {
    }

    public DmDbPartitionStatsDataType(long? partitionId,
        int objectId,
        int indexId,
        int partitionNumber,
        long? inRowDataPageCount,
        long? inRowUsedPageCount,
        long? inRowReservedPageCount,
        long? lobUsedPageCount,
        long? lobReservedPageCount,
        long? rowOverflowUsedPageCount,
        long? rowOverflowReservedPageCount,
        long? usedPageCount,
        long? reservedPageCount,
        long? rowCount)
    {
        _partitionId = partitionId;
        _objectId = objectId;
        _indexId = indexId;
        _partitionNumber = partitionNumber;
        _inRowDataPageCount = inRowDataPageCount;
        _inRowUsedPageCount = inRowUsedPageCount;
        _inRowReservedPageCount = inRowReservedPageCount;
        _lobUsedPageCount = lobUsedPageCount;
        _lobReservedPageCount = lobReservedPageCount;
        _rowOverflowUsedPageCount = rowOverflowUsedPageCount;
        _rowOverflowReservedPageCount = rowOverflowReservedPageCount;
        _usedPageCount = usedPageCount;
        _reservedPageCount = reservedPageCount;
        _rowCount = rowCount;
    }

    public long? PartitionId => _partitionId;
    public int ObjectId => _objectId;
    public int IndexId => _indexId;
    public int PartitionNumber => _partitionNumber;
    public long? InRowDataPageCount => _inRowDataPageCount;
    public long? InRowUsedPageCount => _inRowUsedPageCount;
    public long? InRowReservedPageCount => _inRowReservedPageCount;
    public long? LobUsedPageCount => _lobUsedPageCount;
    public long? LobReservedPageCount => _lobReservedPageCount;
    public long? RowOverflowUsedPageCount => _rowOverflowUsedPageCount;
    public long? RowOverflowReservedPageCount => _rowOverflowReservedPageCount;
    public long? UsedPageCount => _usedPageCount;
    public long? ReservedPageCount => _reservedPageCount;
    public long? RowCount => _rowCount;
}

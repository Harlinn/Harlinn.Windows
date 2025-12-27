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

public class DmDbColumnStoreRowGroupOperationalStatsDataType
{
    readonly int _objectId = 0;
    readonly int _indexId = 0;
    readonly int _partitionNumber = 0;
    readonly int _rowGroupId = 0;
    readonly long _indexScanCount = 0;
    readonly long _scanCount = 0;
    readonly long _deleteBufferScanCount = 0;
    readonly long _rowGroupLockCount = 0;
    readonly long _rowGroupLockWaitCount = 0;
    readonly long _rowGroupLockWaitInMs = 0;
    readonly long _returnedRowCount = 0;
    readonly long _returnedAggregateCount = 0;
    readonly long _returnedGroupCount = 0;
    readonly long _inputGroupbyRowCount = 0;

    public DmDbColumnStoreRowGroupOperationalStatsDataType( )
    {
    }

    public DmDbColumnStoreRowGroupOperationalStatsDataType(int objectId,
        int indexId,
        int partitionNumber,
        int rowGroupId,
        long indexScanCount,
        long scanCount,
        long deleteBufferScanCount,
        long rowGroupLockCount,
        long rowGroupLockWaitCount,
        long rowGroupLockWaitInMs,
        long returnedRowCount,
        long returnedAggregateCount,
        long returnedGroupCount,
        long inputGroupbyRowCount)
    {
        _objectId = objectId;
        _indexId = indexId;
        _partitionNumber = partitionNumber;
        _rowGroupId = rowGroupId;
        _indexScanCount = indexScanCount;
        _scanCount = scanCount;
        _deleteBufferScanCount = deleteBufferScanCount;
        _rowGroupLockCount = rowGroupLockCount;
        _rowGroupLockWaitCount = rowGroupLockWaitCount;
        _rowGroupLockWaitInMs = rowGroupLockWaitInMs;
        _returnedRowCount = returnedRowCount;
        _returnedAggregateCount = returnedAggregateCount;
        _returnedGroupCount = returnedGroupCount;
        _inputGroupbyRowCount = inputGroupbyRowCount;
    }

    public int ObjectId => _objectId;
    public int IndexId => _indexId;
    public int PartitionNumber => _partitionNumber;
    public int RowGroupId => _rowGroupId;
    public long IndexScanCount => _indexScanCount;
    public long ScanCount => _scanCount;
    public long DeleteBufferScanCount => _deleteBufferScanCount;
    public long RowGroupLockCount => _rowGroupLockCount;
    public long RowGroupLockWaitCount => _rowGroupLockWaitCount;
    public long RowGroupLockWaitInMs => _rowGroupLockWaitInMs;
    public long ReturnedRowCount => _returnedRowCount;
    public long ReturnedAggregateCount => _returnedAggregateCount;
    public long ReturnedGroupCount => _returnedGroupCount;
    public long InputGroupbyRowCount => _inputGroupbyRowCount;
}

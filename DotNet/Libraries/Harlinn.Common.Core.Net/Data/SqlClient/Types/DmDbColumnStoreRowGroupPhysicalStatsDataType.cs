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

public class DmDbColumnStoreRowGroupPhysicalStatsDataType
{
    readonly int? _objectId;
    readonly int? _indexId;
    readonly int? _partitionNumber;
    readonly int? _rowGroupId;
    readonly long? _deltaStoreHobtId;
    readonly byte? _state;
    readonly string _stateDesc = string.Empty;
    readonly long? _totalRows;
    readonly long? _deletedRows;
    readonly long? _sizeInBytes;
    readonly byte? _trimReason;
    readonly string? _trimReasonDesc;
    readonly byte? _transitionToCompressedState;
    readonly string? _transitionToCompressedStateDesc;
    readonly bool? _hasVertipaqOptimization;
    readonly long? _generation;
    readonly DateTime? _createdTime;
    readonly DateTime? _closedTime;

    public DmDbColumnStoreRowGroupPhysicalStatsDataType( )
    {
    }

    public DmDbColumnStoreRowGroupPhysicalStatsDataType(int? objectId,
        int? indexId,
        int? partitionNumber,
        int? rowGroupId,
        long? deltaStoreHobtId,
        byte? state,
        string stateDesc,
        long? totalRows,
        long? deletedRows,
        long? sizeInBytes,
        byte? trimReason,
        string? trimReasonDesc,
        byte? transitionToCompressedState,
        string? transitionToCompressedStateDesc,
        bool? hasVertipaqOptimization,
        long? generation,
        DateTime? createdTime,
        DateTime? closedTime)
    {
        _objectId = objectId;
        _indexId = indexId;
        _partitionNumber = partitionNumber;
        _rowGroupId = rowGroupId;
        _deltaStoreHobtId = deltaStoreHobtId;
        _state = state;
        _stateDesc = stateDesc;
        _totalRows = totalRows;
        _deletedRows = deletedRows;
        _sizeInBytes = sizeInBytes;
        _trimReason = trimReason;
        _trimReasonDesc = trimReasonDesc;
        _transitionToCompressedState = transitionToCompressedState;
        _transitionToCompressedStateDesc = transitionToCompressedStateDesc;
        _hasVertipaqOptimization = hasVertipaqOptimization;
        _generation = generation;
        _createdTime = createdTime;
        _closedTime = closedTime;
    }

    public int? ObjectId => _objectId;
    public int? IndexId => _indexId;
    public int? PartitionNumber => _partitionNumber;
    public int? RowGroupId => _rowGroupId;
    public long? DeltaStoreHobtId => _deltaStoreHobtId;
    public byte? State => _state;
    public string StateDesc => _stateDesc;
    public long? TotalRows => _totalRows;
    public long? DeletedRows => _deletedRows;
    public long? SizeInBytes => _sizeInBytes;
    public byte? TrimReason => _trimReason;
    public string? TrimReasonDesc => _trimReasonDesc;
    public byte? TransitionToCompressedState => _transitionToCompressedState;
    public string? TransitionToCompressedStateDesc => _transitionToCompressedStateDesc;
    public bool? HasVertipaqOptimization => _hasVertipaqOptimization;
    public long? Generation => _generation;
    public DateTime? CreatedTime => _createdTime;
    public DateTime? ClosedTime => _closedTime;
}

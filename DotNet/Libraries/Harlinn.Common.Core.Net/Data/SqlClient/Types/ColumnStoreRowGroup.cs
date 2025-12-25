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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{
    /// <summary>
    /// Represents a row from the <c>sys.column_store_row_groups</c> catalog view.
    /// Immutable type with private readonly backing fields prefixed with '_'.
    /// </summary>
    public sealed class ColumnStoreRowGroup
    {
        private readonly int _objectId;
        private readonly int _indexId;
        private readonly int _partitionNumber;
        private readonly int _rowGroupId;
        private readonly long? _deltaStoreHobtId;
        private readonly byte _state;
        private readonly string? _stateDescription;
        private readonly long _totalRows;
        private readonly long _deletedRows;
        private readonly long _sizeInBytes;

        /// <summary>
        /// Initializes a new instance of the <see cref="ColumnStoreRowGroup"/> class.
        /// </summary>
        public ColumnStoreRowGroup(
            int objectId,
            int indexId,
            int partitionNumber,
            int rowGroupId,
            long? deltaStoreHobtId,
            byte state,
            string? stateDescription,
            long totalRows,
            long deletedRows,
            long sizeInBytes)
        {
            _objectId = objectId;
            _indexId = indexId;
            _partitionNumber = partitionNumber;
            _rowGroupId = rowGroupId;
            _deltaStoreHobtId = deltaStoreHobtId;
            _state = state;
            _stateDescription = stateDescription;
            _totalRows = totalRows;
            _deletedRows = deletedRows;
            _sizeInBytes = sizeInBytes;
        }

        /// <summary>
        /// ID of the object that contains the columnstore index. (sys.column_store_row_groups.object_id)
        /// </summary>
        public int ObjectId => _objectId;

        /// <summary>
        /// ID of the index containing the row group. (sys.column_store_row_groups.index_id)
        /// </summary>
        public int IndexId => _indexId;

        /// <summary>
        /// Partition number within the index. (sys.column_store_row_groups.partition_number)
        /// </summary>
        public int PartitionNumber => _partitionNumber;

        /// <summary>
        /// Row group identifier. (sys.column_store_row_groups.row_group_id)
        /// </summary>
        public int RowGroupId => _rowGroupId;

        /// <summary>
        /// HOBT id for the delta store that contains the delta rows for this row group, if any. (sys.column_store_row_groups.delta_store_hobt_id)
        /// May be NULL when there is no associated delta store.
        /// </summary>
        public long? DeltaStoreHobtId => _deltaStoreHobtId;

        /// <summary>
        /// Numeric state code for the row group. (sys.column_store_row_groups.state)
        /// Indicates the internal state of the row group.
        /// </summary>
        public byte State => _state;

        /// <summary>
        /// Human readable description of the row group state. (sys.column_store_row_groups.state_description)
        /// </summary>
        public string? StateDescription => _stateDescription;

        /// <summary>
        /// Total number of rows in the row group. (sys.column_store_row_groups.total_rows)
        /// </summary>
        public long TotalRows => _totalRows;

        /// <summary>
        /// Number of deleted rows in the row group. (sys.column_store_row_groups.deleted_rows)
        /// </summary>
        public long DeletedRows => _deletedRows;

        /// <summary>
        /// Size on disk for the row group, in bytes. (sys.column_store_row_groups.size_in_bytes)
        /// </summary>
        public long SizeInBytes => _sizeInBytes;
    }
}
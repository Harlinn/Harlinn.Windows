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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{
    public class IndexColumn
    {
        readonly int _objectId;
        readonly int _indexId;
        readonly int _indexColumnId;
        readonly int _columnId;
        readonly sbyte _keyOrdinal;
        readonly sbyte _partitionOrdinal;
        readonly bool _isDescendingKey;
        readonly bool _isIncludedColumn;
        readonly byte _columnStoreOrderOrdinal;
        readonly string _columnName;

        public IndexColumn(int objectId, int indexId, int indexColumnId, int columnId, sbyte keyOrdinal, sbyte partitionOrdinal, bool isDescendingKey, bool isIncludedColumn, byte columnStoreOrderOrdinal, string columnName)
        {
            _objectId = objectId;
            _indexId = indexId;
            _indexColumnId = indexColumnId;
            _columnId = columnId;
            _keyOrdinal = keyOrdinal;
            _partitionOrdinal = partitionOrdinal;
            _isDescendingKey = isDescendingKey;
            _isIncludedColumn = isIncludedColumn;
            _columnStoreOrderOrdinal = columnStoreOrderOrdinal;
            _columnName = columnName;
        }

        /// <summary>
        /// ID of the object the index is defined on.
        /// </summary>
        public int ObjectId => _objectId;

        /// <summary>
        /// ID of the index in which the column is defined.
        /// </summary>
        public int IndexId => _indexId;

        /// <summary>
        /// ID of the index column. index_column_id is unique only within index_id.
        /// </summary>
        public int IndexColumnId => _indexColumnId;

        /// <summary>
        /// ID of the column in object_id.
        /// </summary>
        public int ColumnId => _columnId;

        /// <summary>
        /// Ordinal (1-based) within set of key-columns.
        /// </summary>
        public sbyte KeyOrdinal => _keyOrdinal;

        /// <summary>
        /// Ordinal (1-based) within set of partitioning columns. A clustered columnstore index can have at most one partitioning column.
        /// </summary>
        public sbyte PartitionOrdinal => _partitionOrdinal;

        /// <summary>
        /// Index key column has a descending sort direction.
        /// </summary>
        public bool IsDescendingKey => _isDescendingKey;

        /// <summary>
        /// Column is a nonkey column added to the index by using the CREATE INDEX INCLUDE clause, or the column is part of a columnstore index.
        /// </summary>
        public bool IsIncludedColumn => _isIncludedColumn;

        /// <summary>
        /// Ordinal (1-based) within set of order columns in an ordered columnstore index. For more on ordered columnstore indexes
        /// </summary>
        public byte ColumnStoreOrderOrdinal => _columnStoreOrderOrdinal;

        /// <summary>
        /// Gets the name of the column associated with this index column.
        /// </summary>
        public string ColumnName => _columnName;
    }

}

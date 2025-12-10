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

        public IndexColumn(int objectId, int indexId, int indexColumnId, int columnId, sbyte keyOrdinal, sbyte partitionOrdinal, bool isDescendingKey, bool isIncludedColumn, byte columnStoreOrderOrdinal)
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
        }

        public int ObjectId => _objectId;

        public int IndexId => _indexId;

        public int IndexColumnId => _indexColumnId;

        public int ColumnId => _columnId;

        public sbyte KeyOrdinal => _keyOrdinal;

        public sbyte PartitionOrdinal => _partitionOrdinal;

        public bool IsDescendingKey => _isDescendingKey;

        public bool IsIncludedColumn => _isIncludedColumn;

        public byte ColumnStoreOrderOrdinal => _columnStoreOrderOrdinal;
    }

}

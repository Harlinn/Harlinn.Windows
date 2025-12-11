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

using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{

    public class IndexColumnsReader : DataReaderWrapper
    {
        public const string Sql = """
        SELECT ic.[object_id]
            ,ic.[index_id]
            ,ic.[index_column_id]
            ,ic.[column_id]
            ,ic.[key_ordinal]
            ,ic.[partition_ordinal]
            ,ic.[is_descending_key]
            ,ic.[is_included_column]
            ,ic.[column_store_order_ordinal]
            , c.[name] AS [column_name]
        FROM [sys].[index_columns] ic
        INNER JOIN sys.columns c ON ic.object_id = c.object_id AND ic.column_id = c.column_id
        """;

        public const int ObjectIdOrdinal = 0;
        public const int IndexIdOrdinal = 1;
        public const int IndexColumnIdOrdinal = 2;
        public const int ColumnIdOrdinal = 3;
        public const int KeyOrdinalOrdinal = 4;
        public const int PartitionOrdinalOrdinal = 5;
        public const int IsDescendingKeyOrdinal = 6;
        public const int IsIncludedColumnOrdinal = 7;
        public const int ColumnStoreOrderOrdinalOrdinal = 8;
        public const int ColumnNameOrdinal = 9;

        public IndexColumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true) 
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public IndexColumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public IndexColumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        public int GetObjectId()
        {
            return base.GetInt32(ObjectIdOrdinal);
        }

        public int GetIndexId()
        {
            return base.GetInt32(IndexIdOrdinal);
        }

        public int GetIndexColumnId()
        {
            return base.GetInt32(IndexColumnIdOrdinal);
        }

        public int GetColumnId()
        {
            return base.GetInt32(ColumnIdOrdinal);
        }

        public sbyte GetKeyOrdinal()
        {
            return base.GetSByte(KeyOrdinalOrdinal);
        }

        public sbyte GetPartitionOrdinal()
        {
            return base.GetSByte(PartitionOrdinalOrdinal);
        }

        public bool GetIsDescendingKey()
        {
            return base.GetBoolean(IsDescendingKeyOrdinal);
        }

        public bool GetIsIncludedColumn()
        {
            return base.GetBoolean(IsIncludedColumnOrdinal);
        }

        public Byte GetColumnStoreOrderOrdinal()
        {
            return base.GetByte(ColumnStoreOrderOrdinalOrdinal);
        }

        public string GetColumnName()
        {
            return base.GetString(ColumnNameOrdinal);
        }

        public Types.IndexColumn GetIndexColumn()
        {
            var objectId = GetObjectId();
            var indexId = GetIndexId();
            var indexColumnId = GetIndexColumnId();
            var columnId = GetColumnId();
            var keyOrdinal = GetKeyOrdinal();
            var partitionOrdinal = GetPartitionOrdinal();
            var isDescendingKey = GetIsDescendingKey();
            var isIncludedColumn = GetIsIncludedColumn();
            var columnStoreOrderOrdinal = GetColumnStoreOrderOrdinal();
            var columnName = GetColumnName();
            return new Types.IndexColumn(objectId, indexId, indexColumnId, columnId, keyOrdinal, partitionOrdinal, isDescendingKey, isIncludedColumn, columnStoreOrderOrdinal, columnName);
        }

        public IReadOnlyList<Types.IndexColumn> GetIndexColumns()
        {
            var indexColumns = new List<Types.IndexColumn>();
            while (Read())
            {
                indexColumns.Add(GetIndexColumn());
            }
            return indexColumns;
        }


    }
}

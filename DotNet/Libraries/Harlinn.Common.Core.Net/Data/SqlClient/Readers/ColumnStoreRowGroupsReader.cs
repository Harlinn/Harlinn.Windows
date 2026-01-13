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

using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{
    public class ColumnStoreRowGroupsReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT scsrg.[object_id]
                  ,scsrg.[index_id]
                  ,scsrg.[partition_number]
                  ,scsrg.[row_group_id]
                  ,scsrg.[delta_store_hobt_id]
                  ,scsrg.[state]
                  ,scsrg.[state_description]
                  ,scsrg.[total_rows]
                  ,scsrg.[deleted_rows]
                  ,scsrg.[size_in_bytes]
            FROM [sys].[column_store_row_groups] scsrg
            """;

        public const int ObjectIdOrdinal = 0;
        public const int IndexIdOrdinal = 1;
        public const int PartitionNumberOrdinal = 2;
        public const int RowGroupIdOrdinal = 3;
        public const int DeltaStoreHobtIdOrdinal = 4;
        public const int StateOrdinal = 5;
        public const int StateDescriptionOrdinal = 6;
        public const int TotalRowsOrdinal = 7;
        public const int DeletedRowsOrdinal = 8;
        public const int SizeInBytesOrdinal = 9;

        public ColumnStoreRowGroupsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public ColumnStoreRowGroupsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public ColumnStoreRowGroupsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        /// <summary>
        /// Reads the object_id column. (sys.column_store_row_groups.object_id)
        /// ID of the object that contains the columnstore index.
        /// </summary>
        public int GetObjectId()
        {
            return GetInt32(ObjectIdOrdinal);
        }

        /// <summary>
        /// Reads the index_id column. (sys.column_store_row_groups.index_id)
        /// ID of the index containing the row group.
        /// </summary>
        public int GetIndexId()
        {
            return GetInt32(IndexIdOrdinal);
        }

        /// <summary>
        /// Reads the partition_number column. (sys.column_store_row_groups.partition_number)
        /// Partition number within the index.
        /// </summary>
        public int GetPartitionNumber()
        {
            return GetInt32(PartitionNumberOrdinal);
        }

        /// <summary>
        /// Reads the row_group_id column. (sys.column_store_row_groups.row_group_id)
        /// Row group identifier.
        /// </summary>
        public int GetRowGroupId()
        {
            return GetInt32(RowGroupIdOrdinal);
        }

        /// <summary>
        /// Reads the delta_store_hobt_id column. (sys.column_store_row_groups.delta_store_hobt_id)
        /// HOBT id for the delta store that contains the delta rows for this row group; may be NULL.
        /// </summary>
        public long? GetDeltaStoreHobtId()
        {
            if (IsDBNull(DeltaStoreHobtIdOrdinal)) return null;
            return GetInt64(DeltaStoreHobtIdOrdinal);
        }

        /// <summary>
        /// Reads the state column. (sys.column_store_row_groups.state)
        /// Numeric state code for the row group.
        /// </summary>
        public byte GetState()
        {
            return GetByte(StateOrdinal);
        }

        /// <summary>
        /// Reads the state_description column. (sys.column_store_row_groups.state_description)
        /// Human readable description of the row group state.
        /// </summary>
        public string? GetStateDescription()
        {
            return GetNullableString(StateDescriptionOrdinal);
        }

        /// <summary>
        /// Reads the total_rows column. (sys.column_store_row_groups.total_rows)
        /// Total number of rows in the row group.
        /// </summary>
        public long GetTotalRows()
        {
            return GetInt64(TotalRowsOrdinal);
        }

        /// <summary>
        /// Reads the deleted_rows column. (sys.column_store_row_groups.deleted_rows)
        /// Number of deleted rows in the row group.
        /// </summary>
        public long GetDeletedRows()
        {
            return GetInt64(DeletedRowsOrdinal);
        }

        /// <summary>
        /// Reads the size_in_bytes column. (sys.column_store_row_groups.size_in_bytes)
        /// Size on disk for the row group, in bytes.
        /// </summary>
        public long GetSizeInBytes()
        {
            return GetInt64(SizeInBytesOrdinal);
        }

        /// <summary>
        /// Creates a <see cref="ColumnStoreRowGroup"/> instance populated from the current data record.
        /// </summary>
        public ColumnStoreRowGroup GetColumnStoreRowGroup()
        {
            var objectId = GetObjectId();
            var indexId = GetIndexId();
            var partitionNumber = GetPartitionNumber();
            var rowGroupId = GetRowGroupId();
            var deltaStoreHobtId = GetDeltaStoreHobtId();
            var state = GetState();
            var stateDescription = GetStateDescription();
            var totalRows = GetTotalRows();
            var deletedRows = GetDeletedRows();
            var sizeInBytes = GetSizeInBytes();

            return new ColumnStoreRowGroup(objectId, indexId, partitionNumber, rowGroupId, deltaStoreHobtId, state, stateDescription, totalRows, deletedRows, sizeInBytes);
        }

        /// <summary>
        /// Reads all rows from the reader and returns a list of <see cref="ColumnStoreRowGroup"/>.
        /// </summary>
        public IReadOnlyList<ColumnStoreRowGroup> GetColumnStoreRowGroups()
        {
            var list = new List<ColumnStoreRowGroup>();
            while (Read())
            {
                list.Add(GetColumnStoreRowGroup());
            }
            return list;
        }
    }
}
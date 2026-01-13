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
    public class ColumnStoreDictionariesReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT scsd.[partition_id]
                  ,scsd.[hobt_id]
                  ,scsd.[column_id]
                  ,scsd.[dictionary_id]
                  ,scsd.[version]
                  ,scsd.[type]
                  ,scsd.[last_id]
                  ,scsd.[entry_count]
                  ,scsd.[on_disk_size]
            FROM [AdventureWorks2019].[sys].[column_store_dictionaries] scsd
            """;

        public const int PartitionIdOrdinal = 0;
        public const int HobtIdOrdinal = 1;
        public const int ColumnIdOrdinal = 2;
        public const int DictionaryIdOrdinal = 3;
        public const int VersionOrdinal = 4;
        public const int TypeOrdinal = 5;
        public const int LastIdOrdinal = 6;
        public const int EntryCountOrdinal = 7;
        public const int OnDiskSizeOrdinal = 8;

        public ColumnStoreDictionariesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public ColumnStoreDictionariesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public ColumnStoreDictionariesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        /// <summary>
        /// Reads the partition_id column. (sys.column_store_dictionaries.partition_id)
        /// Identifies the partition that contains the dictionary.
        /// </summary>
        public int GetPartitionId()
        {
            return GetInt32(PartitionIdOrdinal);
        }

        /// <summary>
        /// Reads the hobt_id column. (sys.column_store_dictionaries.hobt_id)
        /// Identifier of the heap or B-tree (HOBT) that contains the columnstore segment.
        /// </summary>
        public long GetHobtId()
        {
            return GetInt64(HobtIdOrdinal);
        }

        /// <summary>
        /// Reads the column_id column. (sys.column_store_dictionaries.column_id)
        /// Identifies the column to which this dictionary belongs.
        /// </summary>
        public int GetColumnId()
        {
            return GetInt32(ColumnIdOrdinal);
        }

        /// <summary>
        /// Reads the dictionary_id column. (sys.column_store_dictionaries.dictionary_id)
        /// Identifier for the dictionary structure used for the column; may be NULL.
        /// </summary>
        public long? GetDictionaryId()
        {
            if (IsDBNull(DictionaryIdOrdinal)) return null;
            return GetInt64(DictionaryIdOrdinal);
        }

        /// <summary>
        /// Reads the version column. (sys.column_store_dictionaries.version)
        /// Version number of the dictionary.
        /// </summary>
        public int GetVersion()
        {
            return GetInt32(VersionOrdinal);
        }

        /// <summary>
        /// Reads the type column. (sys.column_store_dictionaries.type)
        /// Type code indicating the dictionary kind.
        /// </summary>
        public byte GetDictionaryTypeCode()
        {
            return GetByte(TypeOrdinal);
        }

        /// <summary>
        /// Reads the last_id column. (sys.column_store_dictionaries.last_id)
        /// Identifier of the last entry in the dictionary; may be NULL.
        /// </summary>
        public long? GetLastId()
        {
            if (IsDBNull(LastIdOrdinal)) return null;
            return GetInt64(LastIdOrdinal);
        }

        /// <summary>
        /// Reads the entry_count column. (sys.column_store_dictionaries.entry_count)
        /// The number of distinct entries stored in the dictionary.
        /// </summary>
        public long GetEntryCount()
        {
            return GetInt64(EntryCountOrdinal);
        }

        /// <summary>
        /// Reads the on_disk_size column. (sys.column_store_dictionaries.on_disk_size)
        /// The amount of space used on disk by the dictionary, in bytes.
        /// </summary>
        public long GetOnDiskSize()
        {
            return GetInt64(OnDiskSizeOrdinal);
        }

        /// <summary>
        /// Creates a <see cref="ColumnStoreDictionary"/> instance populated from the current data record.
        /// </summary>
        public ColumnStoreDictionary GetColumnStoreDictionary()
        {
            var partitionId = GetPartitionId();
            var hobtId = GetHobtId();
            var columnId = GetColumnId();
            var dictionaryId = GetDictionaryId();
            var version = GetVersion();
            var typeCode = GetDictionaryTypeCode();
            var lastId = GetLastId();
            var entryCount = GetEntryCount();
            var onDiskSize = GetOnDiskSize();

            return new ColumnStoreDictionary(partitionId, hobtId, columnId, dictionaryId, version, typeCode, lastId, entryCount, onDiskSize);
        }

        /// <summary>
        /// Reads all rows from the reader and returns a list of <see cref="ColumnStoreDictionary"/>.
        /// </summary>
        public IReadOnlyList<ColumnStoreDictionary> GetColumnStoreDictionaries()
        {
            var list = new List<ColumnStoreDictionary>();
            while (Read())
            {
                list.Add(GetColumnStoreDictionary());
            }
            return list;
        }
    }
}
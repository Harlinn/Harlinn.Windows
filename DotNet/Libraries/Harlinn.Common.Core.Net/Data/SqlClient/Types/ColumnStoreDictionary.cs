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
    /// Represents a row from the sys.column_store_dictionaries catalog view.
    /// Immutable type with private readonly backing fields prefixed with '_'.
    /// </summary>
    public sealed class ColumnStoreDictionary
    {
        private readonly int _partitionId;
        private readonly long _hobtId;
        private readonly int _columnId;
        private readonly long? _dictionaryId;
        private readonly int _version;
        private readonly byte _type;
        private readonly long? _lastId;
        private readonly long _entryCount;
        private readonly long _onDiskSize;

        /// <summary>
        /// Initializes a new instance of the <see cref="ColumnStoreDictionary"/> class.
        /// </summary>
        public ColumnStoreDictionary(
            int partitionId,
            long hobtId,
            int columnId,
            long? dictionaryId,
            int version,
            byte type,
            long? lastId,
            long entryCount,
            long onDiskSize)
        {
            _partitionId = partitionId;
            _hobtId = hobtId;
            _columnId = columnId;
            _dictionaryId = dictionaryId;
            _version = version;
            _type = type;
            _lastId = lastId;
            _entryCount = entryCount;
            _onDiskSize = onDiskSize;
        }

        /// <summary>
        /// Partition identifier. (sys.column_store_dictionaries.partition_id)
        /// Identifies the partition that contains the dictionary.
        /// </summary>
        public int PartitionId => _partitionId;

        /// <summary>
        /// HOBT identifier. (sys.column_store_dictionaries.hobt_id)
        /// Identifier of the heap or B-tree (HOBT) that contains the columnstore segment.
        /// </summary>
        public long HobtId => _hobtId;

        /// <summary>
        /// Column identifier within the object. (sys.column_store_dictionaries.column_id)
        /// Identifies the column to which this dictionary belongs.
        /// </summary>
        public int ColumnId => _columnId;

        /// <summary>
        /// Dictionary identifier. (sys.column_store_dictionaries.dictionary_id)
        /// Identifier for the dictionary structure used for the column; may be NULL.
        /// </summary>
        public long? DictionaryId => _dictionaryId;

        /// <summary>
        /// Dictionary version. (sys.column_store_dictionaries.version)
        /// Version number of the dictionary.
        /// </summary>
        public int Version => _version;

        /// <summary>
        /// Dictionary type. (sys.column_store_dictionaries.type)
        /// Type code indicating the dictionary kind.
        /// </summary>
        public byte Type => _type;

        /// <summary>
        /// Last dictionary entry id. (sys.column_store_dictionaries.last_id)
        /// Identifier of the last entry in the dictionary; may be NULL.
        /// </summary>
        public long? LastId => _lastId;

        /// <summary>
        /// Number of entries in the dictionary. (sys.column_store_dictionaries.entry_count)
        /// The number of distinct entries stored in the dictionary.
        /// </summary>
        public long EntryCount => _entryCount;

        /// <summary>
        /// Size on disk, in bytes. (sys.column_store_dictionaries.on_disk_size)
        /// The amount of space used on disk by the dictionary.
        /// </summary>
        public long OnDiskSize => _onDiskSize;
    }
}
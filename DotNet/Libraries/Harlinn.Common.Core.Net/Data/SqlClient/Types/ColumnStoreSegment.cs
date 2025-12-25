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
    /// Immutable representation of a row from the <c>sys.column_store_segments</c> catalog view.
    /// Backing fields are private readonly and prefixed with '_'.
    /// </summary>
    public sealed class ColumnStoreSegment
    {
        private readonly int _partitionId;
        private readonly long _hobtId;
        private readonly int _columnId;
        private readonly long _segmentId;
        private readonly int _version;
        private readonly byte _encodingType;
        private readonly long _rowCount;
        private readonly bool _hasNulls;
        private readonly long? _baseId;
        private readonly int? _magnitude;
        private readonly long? _primaryDictionaryId;
        private readonly long? _secondaryDictionaryId;
        private readonly long? _minDataId;
        private readonly long? _maxDataId;
        private readonly string? _nullValue;
        private readonly long _onDiskSize;

        /// <summary>
        /// Initializes a new instance of <see cref="ColumnStoreSegment"/>.
        /// </summary>
        public ColumnStoreSegment(
            int partitionId,
            long hobtId,
            int columnId,
            long segmentId,
            int version,
            byte encodingType,
            long rowCount,
            bool hasNulls,
            long? baseId,
            int? magnitude,
            long? primaryDictionaryId,
            long? secondaryDictionaryId,
            long? minDataId,
            long? maxDataId,
            string? nullValue,
            long onDiskSize)
        {
            _partitionId = partitionId;
            _hobtId = hobtId;
            _columnId = columnId;
            _segmentId = segmentId;
            _version = version;
            _encodingType = encodingType;
            _rowCount = rowCount;
            _hasNulls = hasNulls;
            _baseId = baseId;
            _magnitude = magnitude;
            _primaryDictionaryId = primaryDictionaryId;
            _secondaryDictionaryId = secondaryDictionaryId;
            _minDataId = minDataId;
            _maxDataId = maxDataId;
            _nullValue = nullValue;
            _onDiskSize = onDiskSize;
        }

        /// <summary>
        /// Partition identifier. (sys.column_store_segments.partition_id)
        /// Identifies the partition that contains the segment.
        /// </summary>
        public int PartitionId => _partitionId;

        /// <summary>
        /// HOBT identifier. (sys.column_store_segments.hobt_id)
        /// Identifier of the heap or B-tree (HOBT) that contains the segment.
        /// </summary>
        public long HobtId => _hobtId;

        /// <summary>
        /// Column identifier within the object. (sys.column_store_segments.column_id)
        /// Identifies the column to which the segment belongs.
        /// </summary>
        public int ColumnId => _columnId;

        /// <summary>
        /// Segment identifier. (sys.column_store_segments.segment_id)
        /// Identifier for the segment within the columnstore.
        /// </summary>
        public long SegmentId => _segmentId;

        /// <summary>
        /// Segment format version. (sys.column_store_segments.version)
        /// Version of the segment format.
        /// </summary>
        public int Version => _version;

        /// <summary>
        /// Encoding type for the segment. (sys.column_store_segments.encoding_type)
        /// Numeric code indicating the encoding used for the segment.
        /// </summary>
        public byte EncodingType => _encodingType;

        /// <summary>
        /// Number of rows stored in the segment. (sys.column_store_segments.row_count)
        /// </summary>
        public long RowCount => _rowCount;

        /// <summary>
        /// Indicates whether the segment contains NULL values. (sys.column_store_segments.has_nulls)
        /// </summary>
        public bool HasNulls => _hasNulls;

        /// <summary>
        /// Base identifier for delta/base relationships, if any. (sys.column_store_segments.base_id)
        /// </summary>
        public long? BaseId => _baseId;

        /// <summary>
        /// Magnitude of the data stored (type-specific). (sys.column_store_segments.magnitude)
        /// </summary>
        public int? Magnitude => _magnitude;

        /// <summary>
        /// Primary dictionary identifier for the segment, if applicable. (sys.column_store_segments.primary_dictionary_id)
        /// </summary>
        public long? PrimaryDictionaryId => _primaryDictionaryId;

        /// <summary>
        /// Secondary dictionary identifier for the segment, if applicable. (sys.column_store_segments.secondary_dictionary_id)
        /// </summary>
        public long? SecondaryDictionaryId => _secondaryDictionaryId;

        /// <summary>
        /// Minimum data id for the segment, if available. (sys.column_store_segments.min_data_id)
        /// </summary>
        public long? MinDataId => _minDataId;

        /// <summary>
        /// Maximum data id for the segment, if available. (sys.column_store_segments.max_data_id)
        /// </summary>
        public long? MaxDataId => _maxDataId;

        /// <summary>
        /// NULL value representation for the segment (sql_variant). (sys.column_store_segments.null_value)
        /// Returned as textual representation when available.
        /// </summary>
        public string? NullValue => _nullValue;

        /// <summary>
        /// Size on disk for the segment, in bytes. (sys.column_store_segments.on_disk_size)
        /// </summary>
        public long OnDiskSize => _onDiskSize;
    }
}
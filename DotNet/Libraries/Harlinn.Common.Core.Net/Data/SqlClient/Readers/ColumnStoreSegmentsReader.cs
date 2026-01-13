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
    public class ColumnStoreSegmentsReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT scss.[partition_id]
                  ,scss.[hobt_id]
                  ,scss.[column_id]
                  ,scss.[segment_id]
                  ,scss.[version]
                  ,scss.[encoding_type]
                  ,scss.[row_count]
                  ,scss.[has_nulls]
                  ,scss.[base_id]
                  ,scss.[magnitude]
                  ,scss.[primary_dictionary_id]
                  ,scss.[secondary_dictionary_id]
                  ,scss.[min_data_id]
                  ,scss.[max_data_id]
                  ,scss.[null_value]
                  ,scss.[on_disk_size]
            FROM [sys].[column_store_segments] scss
            """;

        public const int PartitionIdOrdinal = 0;
        public const int HobtIdOrdinal = 1;
        public const int ColumnIdOrdinal = 2;
        public const int SegmentIdOrdinal = 3;
        public const int VersionOrdinal = 4;
        public const int EncodingTypeOrdinal = 5;
        public const int RowCountOrdinal = 6;
        public const int HasNullsOrdinal = 7;
        public const int BaseIdOrdinal = 8;
        public const int MagnitudeOrdinal = 9;
        public const int PrimaryDictionaryIdOrdinal = 10;
        public const int SecondaryDictionaryIdOrdinal = 11;
        public const int MinDataIdOrdinal = 12;
        public const int MaxDataIdOrdinal = 13;
        public const int NullValueOrdinal = 14;
        public const int OnDiskSizeOrdinal = 15;

        public ColumnStoreSegmentsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public ColumnStoreSegmentsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public ColumnStoreSegmentsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        /// <summary>
        /// Reads the partition_id column. (sys.column_store_segments.partition_id)
        /// Identifies the partition that contains the segment.
        /// </summary>
        public int GetPartitionId()
        {
            return GetInt32(PartitionIdOrdinal);
        }

        /// <summary>
        /// Reads the hobt_id column. (sys.column_store_segments.hobt_id)
        /// Identifier of the heap or B-tree (HOBT) that contains the segment.
        /// </summary>
        public long GetHobtId()
        {
            return GetInt64(HobtIdOrdinal);
        }

        /// <summary>
        /// Reads the column_id column. (sys.column_store_segments.column_id)
        /// Identifies the column to which this segment belongs.
        /// </summary>
        public int GetColumnId()
        {
            return GetInt32(ColumnIdOrdinal);
        }

        /// <summary>
        /// Reads the segment_id column. (sys.column_store_segments.segment_id)
        /// Identifier for the segment within the columnstore.
        /// </summary>
        public long GetSegmentId()
        {
            return GetInt64(SegmentIdOrdinal);
        }

        /// <summary>
        /// Reads the version column. (sys.column_store_segments.version)
        /// Segment format version.
        /// </summary>
        public int GetVersion()
        {
            return GetInt32(VersionOrdinal);
        }

        /// <summary>
        /// Reads the encoding_type column. (sys.column_store_segments.encoding_type)
        /// Numeric code indicating the encoding used for the segment.
        /// </summary>
        public byte GetEncodingType()
        {
            return GetByte(EncodingTypeOrdinal);
        }

        /// <summary>
        /// Reads the row_count column. (sys.column_store_segments.row_count)
        /// Number of rows stored in the segment.
        /// </summary>
        public long GetRowCount()
        {
            return GetInt64(RowCountOrdinal);
        }

        /// <summary>
        /// Reads the has_nulls column. (sys.column_store_segments.has_nulls)
        /// Indicates whether the segment contains NULL values.
        /// </summary>
        public bool GetHasNulls()
        {
            return GetBoolean(HasNullsOrdinal);
        }

        /// <summary>
        /// Reads the base_id column. (sys.column_store_segments.base_id)
        /// Base identifier for delta/base relationships, if any.
        /// </summary>
        public long? GetBaseId()
        {
            if (IsDBNull(BaseIdOrdinal)) return null;
            return GetInt64(BaseIdOrdinal);
        }

        /// <summary>
        /// Reads the magnitude column. (sys.column_store_segments.magnitude)
        /// Magnitude of the data stored (type-specific); may be NULL.
        /// </summary>
        public int? GetMagnitude()
        {
            return GetNullableInt32(MagnitudeOrdinal);
        }

        /// <summary>
        /// Reads the primary_dictionary_id column. (sys.column_store_segments.primary_dictionary_id)
        /// Identifier of the primary dictionary used by the segment; may be NULL.
        /// </summary>
        public long? GetPrimaryDictionaryId()
        {
            if (IsDBNull(PrimaryDictionaryIdOrdinal)) return null;
            return GetInt64(PrimaryDictionaryIdOrdinal);
        }

        /// <summary>
        /// Reads the secondary_dictionary_id column. (sys.column_store_segments.secondary_dictionary_id)
        /// Identifier of the secondary dictionary used by the segment; may be NULL.
        /// </summary>
        public long? GetSecondaryDictionaryId()
        {
            if (IsDBNull(SecondaryDictionaryIdOrdinal)) return null;
            return GetInt64(SecondaryDictionaryIdOrdinal);
        }

        /// <summary>
        /// Reads the min_data_id column. (sys.column_store_segments.min_data_id)
        /// Minimum data id stored in the segment; may be NULL.
        /// </summary>
        public long? GetMinDataId()
        {
            if (IsDBNull(MinDataIdOrdinal)) return null;
            return GetInt64(MinDataIdOrdinal);
        }

        /// <summary>
        /// Reads the max_data_id column. (sys.column_store_segments.max_data_id)
        /// Maximum data id stored in the segment; may be NULL.
        /// </summary>
        public long? GetMaxDataId()
        {
            if (IsDBNull(MaxDataIdOrdinal)) return null;
            return GetInt64(MaxDataIdOrdinal);
        }

        /// <summary>
        /// Reads the null_value column. (sys.column_store_segments.null_value)
        /// NULL value representation for the segment (sql_variant). Returned as textual representation when available.
        /// </summary>
        public string? GetNullValue()
        {
            if (IsDBNull(NullValueOrdinal)) return null;
            // null_value is sql_variant; attempt to read as string representation
            var value = GetValue(NullValueOrdinal);
            return value?.ToString();
        }

        /// <summary>
        /// Reads the on_disk_size column. (sys.column_store_segments.on_disk_size)
        /// Size on disk for the segment, in bytes.
        /// </summary>
        public long GetOnDiskSize()
        {
            return GetInt64(OnDiskSizeOrdinal);
        }

        /// <summary>
        /// Creates a <see cref="ColumnStoreSegment"/> instance populated from the current data record.
        /// </summary>
        public ColumnStoreSegment GetColumnStoreSegment()
        {
            var partitionId = GetPartitionId();
            var hobtId = GetHobtId();
            var columnId = GetColumnId();
            var segmentId = GetSegmentId();
            var version = GetVersion();
            var encodingType = GetEncodingType();
            var rowCount = GetRowCount();
            var hasNulls = GetHasNulls();
            var baseId = GetBaseId();
            var magnitude = GetMagnitude();
            var primaryDictionaryId = GetPrimaryDictionaryId();
            var secondaryDictionaryId = GetSecondaryDictionaryId();
            var minDataId = GetMinDataId();
            var maxDataId = GetMaxDataId();
            var nullValue = GetNullValue();
            var onDiskSize = GetOnDiskSize();

            return new ColumnStoreSegment(
                partitionId,
                hobtId,
                columnId,
                segmentId,
                version,
                encodingType,
                rowCount,
                hasNulls,
                baseId,
                magnitude,
                primaryDictionaryId,
                secondaryDictionaryId,
                minDataId,
                maxDataId,
                nullValue,
                onDiskSize);
        }

        /// <summary>
        /// Reads all rows from the reader and returns a list of <see cref="ColumnStoreSegment"/>.
        /// </summary>
        public IReadOnlyList<ColumnStoreSegment> GetColumnStoreSegments()
        {
            var list = new List<ColumnStoreSegment>();
            while (Read())
            {
                list.Add(GetColumnStoreSegment());
            }
            return list;
        }
    }
}
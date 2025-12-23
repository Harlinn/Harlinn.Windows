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

    public class Index
    {
        readonly int _objectId;
        readonly string? _name;
        readonly int _indexId;
        readonly IndexType _indexType;
        readonly string _indexTypeDesc;
        readonly bool _isUnique;
        readonly int _dataSpaceId;
        readonly bool _ignoreDupKey;
        readonly bool _isPrimaryKey;
        readonly bool _isUniqueConstraint;
        readonly sbyte _fillFactor;
        readonly bool _isPadded;
        readonly bool _isDisabled;
        readonly bool _isHypothetical;
        readonly bool _isIgnoredInOptimization;
        readonly bool _allowRowLocks;
        readonly bool _allowPageLocks;
        readonly bool _hasFilter;
        readonly string? _filterDefinition;
        readonly int? _compressionDelay;
        readonly bool _suppressDupKeyMessages;
        readonly bool _autoCreated;
        readonly bool _optimizeForSequentialKey;

        public Index(int objectId, string? name, int indexId, sbyte indexType, string indexTypeDesc, bool isUnique, int dataSpaceId, bool ignoreDupKey, bool isPrimaryKey, bool isUniqueConstraint, sbyte fillFactor, bool isPadded, bool isDisabled, bool isHypothetical, bool isIgnoredInOptimization, bool allowRowLocks, bool allowPageLocks, bool hasFilter, string? filterDefinition, int? compressionDelay, bool suppressDupKeyMessages, bool autoCreated, bool optimizeForSequentialKey)
        {
            _objectId = objectId;
            _name = name;
            _indexId = indexId;
            _indexType = (IndexType)indexType;
            _indexTypeDesc = indexTypeDesc;
            _isUnique = isUnique;
            _dataSpaceId = dataSpaceId;
            _ignoreDupKey = ignoreDupKey;
            _isPrimaryKey = isPrimaryKey;
            _isUniqueConstraint = isUniqueConstraint;
            _fillFactor = fillFactor;
            _isPadded = isPadded;
            _isDisabled = isDisabled;
            _isHypothetical = isHypothetical;
            _isIgnoredInOptimization = isIgnoredInOptimization;
            _allowRowLocks = allowRowLocks;
            _allowPageLocks = allowPageLocks;
            _hasFilter = hasFilter;
            _filterDefinition = filterDefinition;
            _compressionDelay = compressionDelay;
            _suppressDupKeyMessages = suppressDupKeyMessages;
            _autoCreated = autoCreated;
            _optimizeForSequentialKey = optimizeForSequentialKey;
        }

        /// <summary>
        /// ID of the object to which this index belongs.
        /// </summary>
        public int ObjectId => _objectId;

        /// <summary>
        /// Name of the index. name is unique only within the object.
        /// 
        /// null if the index is unnamed (heap).
        /// </summary>
        public string? Name => _name;

        /// <summary>
        /// <para>ID of the index. index_id is unique only within the object.</para>
        /// 
        /// <list type="bullet">
        /// <item>0 = Heap</item>
        /// <item>1 = Clustered index</item>
        /// <item> &gt; 1 = Nonclustered index</item>
        /// </list>
        /// </summary>
        public int IndexId => _indexId;

        /// <summary>
        /// Type of index
        /// </summary>
        public IndexType IndexType => _indexType;

        /// <summary>
        /// Description of index type
        /// </summary>
        public string IndexTypeDesc => _indexTypeDesc;

        /// <summary>
        /// true if the index is unique; otherwise, false.
        /// </summary>
        public bool IsUnique => _isUnique;

        /// <summary>
        /// <para>ID of the data space for this index. Data space is either a filegroup or partition scheme.</para>
        /// <para>If the index is on a partitioned table or partitioned view, DataSpaceId is the ID of the partition scheme on which the index is built.</para>
        /// </summary>
        public int DataSpaceId => _dataSpaceId;

        /// <summary>
        /// true if duplicate key values are ignored when inserting data into a unique index; otherwise, false.
        /// </summary>
        public bool IgnoreDupKey => _ignoreDupKey;

        /// <summary>
        /// <para>true if the index is a PRIMARY KEY index; otherwise, false.</para>
        /// <para>Always 0 for clustered columnstore indexes.</para>
        /// </summary>
        public bool IsPrimaryKey => _isPrimaryKey;

        /// <summary>
        /// true if the index is created to enforce a UNIQUE constraint; otherwise, false.
        /// </summary>
        public bool IsUniqueConstraint => _isUniqueConstraint;

        /// <summary>
        /// <para>
        /// &gt; 0 = FILLFACTOR percentage used when the index was created or rebuilt.
        /// </para>
        /// <para>0 = default FILLFACTOR of 0 (which means 100 percent full).</para>
        /// <para>Always 0 for clustered columnstore indexes.</para>
        /// </summary>
        public sbyte FillFactor => _fillFactor;

        /// <summary>
        /// true if PADINDEX is ON; otherwise, false.
        /// </summary>
        public bool IsPadded => _isPadded;

        /// <summary>
        /// true if the index is disabled; otherwise, false.
        /// </summary>
        public bool IsDisabled => _isDisabled;

        /// <summary>
        /// true if the index is hypothetical and can't be used directly 
        /// as a data access path. Hypothetical indexes hold column-level 
        /// statistics.
        /// </summary>
        public bool IsHypothetical => _isHypothetical;


        /// <summary>
        /// true if the query optimizer ignores this index when generating query plans; otherwise, false.
        /// </summary>
        public bool IsIgnoredInOptimization => _isIgnoredInOptimization;

        /// <summary>
        /// true if row locks are allowed; otherwise, false.
        /// </summary>
        public bool AllowRowLocks => _allowRowLocks;

        /// <summary>
        /// true if page locks are allowed; otherwise, false.
        /// </summary>
        public bool AllowPageLocks => _allowPageLocks;

        /// <summary>
        /// true if the index has a filter definition; otherwise, false.
        /// </summary>
        public bool HasFilter => _hasFilter;

        /// <summary>
        /// <para>Expression for the subset of rows included in the filtered index.</para> 
        /// <para>null for heap, nonfiltered index, or insufficient permissions on the table.</para>
        /// </summary>
        public string? FilterDefinition => _filterDefinition;

        /// <summary>
        /// <para>&gt; 0 = Columnstore index compression delay specified in minutes.</para>
        /// <para>NULL = Columnstore index rowgroup compression delay is managed automatically.</para>
        /// </summary>
        public int? CompressionDelay => _compressionDelay;

        /// <summary>
        /// true if the index is configured to suppress duplicate key messages during an index rebuild operation.
        /// </summary>
        public bool SuppressDupKeyMessages => _suppressDupKeyMessages;

        /// <summary>
        /// true if the Index was created by the automatic tuning.
        /// </summary>
        public bool AutoCreated => _autoCreated;

        /// <summary>
        /// true if the index has last-page insert optimization enabled.
        /// </summary>
        public bool OptimizeForSequentialKey => _optimizeForSequentialKey;
    }

}

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
        readonly string _name;
        readonly int _indexId;
        readonly sbyte _indexType;
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

        public Index(int objectId, string name, int indexId, sbyte indexType, string indexTypeDesc, bool isUnique, int dataSpaceId, bool ignoreDupKey, bool isPrimaryKey, bool isUniqueConstraint, sbyte fillFactor, bool isPadded, bool isDisabled, bool isHypothetical, bool isIgnoredInOptimization, bool allowRowLocks, bool allowPageLocks, bool hasFilter, string? filterDefinition, int? compressionDelay, bool suppressDupKeyMessages, bool autoCreated, bool optimizeForSequentialKey)
        {
            _objectId = objectId;
            _name = name;
            _indexId = indexId;
            _indexType = indexType;
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

        public int ObjectId => _objectId;

        public string Name => _name;

        public int IndexId => _indexId;

        public sbyte IndexType => _indexType;

        public string IndexTypeDesc => _indexTypeDesc;

        public bool IsUnique => _isUnique;

        public int DataSpaceId => _dataSpaceId;

        public bool IgnoreDupKey => _ignoreDupKey;

        public bool IsPrimaryKey => _isPrimaryKey;

        public bool IsUniqueConstraint => _isUniqueConstraint;

        public sbyte FillFactor => _fillFactor;

        public bool IsPadded => _isPadded;

        public bool IsDisabled => _isDisabled;

        public bool IsHypothetical => _isHypothetical;

        public bool IsIgnoredInOptimization => _isIgnoredInOptimization;

        public bool AllowRowLocks => _allowRowLocks;

        public bool AllowPageLocks => _allowPageLocks;

        public bool HasFilter => _hasFilter;

        public string? FilterDefinition => _filterDefinition;

        public int? CompressionDelay => _compressionDelay;

        public bool SuppressDupKeyMessages => _suppressDupKeyMessages;

        public bool AutoCreated => _autoCreated;

        public bool OptimizeForSequentialKey => _optimizeForSequentialKey;
    }

}

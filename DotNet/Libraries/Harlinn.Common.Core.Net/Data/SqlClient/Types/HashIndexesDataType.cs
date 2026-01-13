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
using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class HashIndexesDataType
{
    readonly int _objectId = 0;
    readonly string? _name;
    readonly int _indexId = 0;
    readonly byte _type = 0;
    readonly string? _typeDesc;
    readonly bool? _isUnique;
    readonly int _dataSpaceId = 0;
    readonly bool? _ignoreDupKey;
    readonly bool? _isPrimaryKey;
    readonly bool? _isUniqueConstraint;
    readonly byte _fillFactor = 0;
    readonly bool? _isPadded;
    readonly bool? _isDisabled;
    readonly bool? _isHypothetical;
    readonly bool? _isIgnoredInOptimization;
    readonly bool? _allowRowLocks;
    readonly bool? _allowPageLocks;
    readonly bool? _hasFilter;
    readonly string? _filterDefinition;
    readonly int _bucketCount = 0;
    readonly bool? _autoCreated;

    public HashIndexesDataType( )
    {
    }

    public HashIndexesDataType(int objectId,
        string? name,
        int indexId,
        byte type,
        string? typeDesc,
        bool? isUnique,
        int dataSpaceId,
        bool? ignoreDupKey,
        bool? isPrimaryKey,
        bool? isUniqueConstraint,
        byte fillFactor,
        bool? isPadded,
        bool? isDisabled,
        bool? isHypothetical,
        bool? isIgnoredInOptimization,
        bool? allowRowLocks,
        bool? allowPageLocks,
        bool? hasFilter,
        string? filterDefinition,
        int bucketCount,
        bool? autoCreated)
    {
        _objectId = objectId;
        _name = name;
        _indexId = indexId;
        _type = type;
        _typeDesc = typeDesc;
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
        _bucketCount = bucketCount;
        _autoCreated = autoCreated;
    }

    public int ObjectId => _objectId;
    public string? Name => _name;
    public int IndexId => _indexId;
    public byte Type => _type;
    public string? TypeDesc => _typeDesc;
    public bool? IsUnique => _isUnique;
    public int DataSpaceId => _dataSpaceId;
    public bool? IgnoreDupKey => _ignoreDupKey;
    public bool? IsPrimaryKey => _isPrimaryKey;
    public bool? IsUniqueConstraint => _isUniqueConstraint;
    public byte FillFactor => _fillFactor;
    public bool? IsPadded => _isPadded;
    public bool? IsDisabled => _isDisabled;
    public bool? IsHypothetical => _isHypothetical;
    public bool? IsIgnoredInOptimization => _isIgnoredInOptimization;
    public bool? AllowRowLocks => _allowRowLocks;
    public bool? AllowPageLocks => _allowPageLocks;
    public bool? HasFilter => _hasFilter;
    public string? FilterDefinition => _filterDefinition;
    public int BucketCount => _bucketCount;
    public bool? AutoCreated => _autoCreated;
}

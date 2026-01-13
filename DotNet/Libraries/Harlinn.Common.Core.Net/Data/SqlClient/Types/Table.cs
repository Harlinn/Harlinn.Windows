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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{

    public class Table : ISchemaObject
    {
        readonly string _name;
        readonly int _objectId;
        readonly int? _principalId;
        readonly int _schemaId;
        readonly int? _parentObjectId;
        readonly SchemaObjectType _type;
        readonly string _typeDesc;
        readonly DateTime _createDate;
        readonly DateTime _modifyDate;
        readonly bool? _isMsShipped;
        readonly bool? _isPublished;
        readonly bool? _isSchemaPublished;
        readonly int _lobDataSpaceId;
        readonly int? _filestreamDataSpaceId;
        readonly int _maxColumnIdUsed;
        readonly bool _lockOnBulkLoad;
        readonly bool _usesAnsiNulls;
        readonly bool _isReplicated;
        readonly bool _hasReplicationFilter;
        readonly bool _isMergePublished;
        readonly bool _isSyncTranSubscribed;
        readonly bool _hasUncheckedAssemblyData;
        readonly int _textInRowLimit;
        readonly bool _largeValueTypesOutOfRow;
        readonly bool _isTrackedByCdc;
        readonly sbyte _lockEscalation;
        readonly string _lockEscalationDesc;
        readonly bool _isFiletable;
        readonly bool _isMemoryOptimized;
        readonly sbyte _durability;
        readonly string _durabilityDesc;
        readonly sbyte _temporalType;
        readonly string _temporalTypeDesc;
        readonly int? _historyTableId;
        readonly bool _isRemoteDataArchiveEnabled;
        readonly bool _isExternal;
        readonly int? _historyRetentionPeriod;
        readonly int? _historyRetentionPeriodUnit;
        readonly string? _historyRetentionPeriodUnitDesc;
        readonly bool _isNode;
        readonly bool _isEdge;

        public Table(string name, int objectId, int? principalId, int schemaId, int? parentObjectId, string type, string typeDesc, DateTime createDate, DateTime modifyDate, bool? isMsShipped, bool? isPublished, bool? isSchemaPublished, int lobDataSpaceId, int? filestreamDataSpaceId, int maxColumnIdUsed, bool lockOnBulkLoad, bool usesAnsiNulls, bool isReplicated, bool hasReplicationFilter, bool isMergePublished, bool isSyncTranSubscribed, bool hasUncheckedAssemblyData, int textInRowLimit, bool largeValueTypesOutOfRow, bool isTrackedByCdc, sbyte lockEscalation, string lockEscalationDesc, bool isFiletable, bool isMemoryOptimized, sbyte durability, string durabilityDesc, sbyte temporalType, string temporalTypeDesc, int? historyTableId, bool isRemoteDataArchiveEnabled, bool isExternal, int? historyRetentionPeriod, int? historyRetentionPeriodUnit, string? historyRetentionPeriodUnitDesc, bool isNode, bool isEdge)
        {
            _name = name;
            _objectId = objectId;
            _principalId = principalId;
            _schemaId = schemaId;
            _parentObjectId = parentObjectId;
            _type = type.ToSchemaObjectType();
            _typeDesc = typeDesc;
            _createDate = createDate;
            _modifyDate = modifyDate;
            _isMsShipped = isMsShipped;
            _isPublished = isPublished;
            _isSchemaPublished = isSchemaPublished;
            _lobDataSpaceId = lobDataSpaceId;
            _filestreamDataSpaceId = filestreamDataSpaceId;
            _maxColumnIdUsed = maxColumnIdUsed;
            _lockOnBulkLoad = lockOnBulkLoad;
            _usesAnsiNulls = usesAnsiNulls;
            _isReplicated = isReplicated;
            _hasReplicationFilter = hasReplicationFilter;
            _isMergePublished = isMergePublished;
            _isSyncTranSubscribed = isSyncTranSubscribed;
            _hasUncheckedAssemblyData = hasUncheckedAssemblyData;
            _textInRowLimit = textInRowLimit;
            _largeValueTypesOutOfRow = largeValueTypesOutOfRow;
            _isTrackedByCdc = isTrackedByCdc;
            _lockEscalation = lockEscalation;
            _lockEscalationDesc = lockEscalationDesc;
            _isFiletable = isFiletable;
            _isMemoryOptimized = isMemoryOptimized;
            _durability = durability;
            _durabilityDesc = durabilityDesc;
            _temporalType = temporalType;
            _temporalTypeDesc = temporalTypeDesc;
            _historyTableId = historyTableId;
            _isRemoteDataArchiveEnabled = isRemoteDataArchiveEnabled;
            _isExternal = isExternal;
            _historyRetentionPeriod = historyRetentionPeriod;
            _historyRetentionPeriodUnit = historyRetentionPeriodUnit;
            _historyRetentionPeriodUnitDesc = historyRetentionPeriodUnitDesc;
            _isNode = isNode;
            _isEdge = isEdge;
        }

        public string Name => _name;

        public int ObjectId => _objectId;

        public int? PrincipalId => _principalId;

        public int SchemaId => _schemaId;

        public int? ParentObjectId => _parentObjectId;

        public SchemaObjectType Type => _type;

        public string TypeDesc => _typeDesc;

        public DateTime CreateDate => _createDate;

        public DateTime ModifyDate => _modifyDate;

        public bool? IsMsShipped => _isMsShipped;

        public bool? IsPublished => _isPublished;

        public bool? IsSchemaPublished => _isSchemaPublished;

        public int LobDataSpaceId => _lobDataSpaceId;

        public int? FilestreamDataSpaceId => _filestreamDataSpaceId;

        public int MaxColumnIdUsed => _maxColumnIdUsed;

        public bool LockOnBulkLoad => _lockOnBulkLoad;

        public bool UsesAnsiNulls => _usesAnsiNulls;

        public bool IsReplicated => _isReplicated;

        public bool HasReplicationFilter => _hasReplicationFilter;

        public bool IsMergePublished => _isMergePublished;

        public bool IsSyncTranSubscribed => _isSyncTranSubscribed;

        public bool HasUncheckedAssemblyData => _hasUncheckedAssemblyData;

        public int TextInRowLimit => _textInRowLimit;

        public bool LargeValueTypesOutOfRow => _largeValueTypesOutOfRow;

        public bool IsTrackedByCdc => _isTrackedByCdc;

        public sbyte LockEscalation => _lockEscalation;

        public string LockEscalationDesc => _lockEscalationDesc;

        public bool IsFiletable => _isFiletable;

        public bool IsMemoryOptimized => _isMemoryOptimized;

        public sbyte Durability => _durability;

        public string DurabilityDesc => _durabilityDesc;

        public sbyte TemporalType => _temporalType;

        public string TemporalTypeDesc => _temporalTypeDesc;

        public int? HistoryTableId => _historyTableId;

        public bool IsRemoteDataArchiveEnabled => _isRemoteDataArchiveEnabled;

        public bool IsExternal => _isExternal;

        public int? HistoryRetentionPeriod => _historyRetentionPeriod;

        public int? HistoryRetentionPeriodUnit => _historyRetentionPeriodUnit;

        public string? HistoryRetentionPeriodUnitDesc => _historyRetentionPeriodUnitDesc;

        public bool IsNode => _isNode;

        public bool IsEdge => _isEdge;
    }

}

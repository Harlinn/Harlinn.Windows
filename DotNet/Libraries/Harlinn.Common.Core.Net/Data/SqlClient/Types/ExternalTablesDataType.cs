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

public class ExternalTablesDataType
{
    readonly string _name = string.Empty;
    readonly int _objectId = 0;
    readonly int? _principalId;
    readonly int _schemaId = 0;
    readonly int _parentObjectId = 0;
    readonly string? _type;
    readonly string? _typeDesc;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;
    readonly bool _isMsShipped = false;
    readonly bool _isPublished = false;
    readonly bool _isSchemaPublished = false;
    readonly int? _maxColumnIdUsed;
    readonly bool? _usesAnsiNulls;
    readonly int _dataSourceId = 0;
    readonly int? _fileFormatId;
    readonly string? _location;
    readonly string? _rejectType;
    readonly double? _rejectValue;
    readonly double? _rejectSampleValue;
    readonly byte? _distributionType;
    readonly string? _distributionDesc;
    readonly int? _shardingColId;
    readonly string? _remoteSchemaName;
    readonly string? _remoteObjectName;
    readonly string? _rejectedRowLocation;

    public ExternalTablesDataType( )
    {
    }

    public ExternalTablesDataType(string name,
        int objectId,
        int? principalId,
        int schemaId,
        int parentObjectId,
        string? type,
        string? typeDesc,
        DateTime createDate,
        DateTime modifyDate,
        bool isMsShipped,
        bool isPublished,
        bool isSchemaPublished,
        int? maxColumnIdUsed,
        bool? usesAnsiNulls,
        int dataSourceId,
        int? fileFormatId,
        string? location,
        string? rejectType,
        double? rejectValue,
        double? rejectSampleValue,
        byte? distributionType,
        string? distributionDesc,
        int? shardingColId,
        string? remoteSchemaName,
        string? remoteObjectName,
        string? rejectedRowLocation)
    {
        _name = name;
        _objectId = objectId;
        _principalId = principalId;
        _schemaId = schemaId;
        _parentObjectId = parentObjectId;
        _type = type;
        _typeDesc = typeDesc;
        _createDate = createDate;
        _modifyDate = modifyDate;
        _isMsShipped = isMsShipped;
        _isPublished = isPublished;
        _isSchemaPublished = isSchemaPublished;
        _maxColumnIdUsed = maxColumnIdUsed;
        _usesAnsiNulls = usesAnsiNulls;
        _dataSourceId = dataSourceId;
        _fileFormatId = fileFormatId;
        _location = location;
        _rejectType = rejectType;
        _rejectValue = rejectValue;
        _rejectSampleValue = rejectSampleValue;
        _distributionType = distributionType;
        _distributionDesc = distributionDesc;
        _shardingColId = shardingColId;
        _remoteSchemaName = remoteSchemaName;
        _remoteObjectName = remoteObjectName;
        _rejectedRowLocation = rejectedRowLocation;
    }

    public string Name => _name;
    public int ObjectId => _objectId;
    public int? PrincipalId => _principalId;
    public int SchemaId => _schemaId;
    public int ParentObjectId => _parentObjectId;
    public string? Type => _type;
    public string? TypeDesc => _typeDesc;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
    public bool IsMsShipped => _isMsShipped;
    public bool IsPublished => _isPublished;
    public bool IsSchemaPublished => _isSchemaPublished;
    public int? MaxColumnIdUsed => _maxColumnIdUsed;
    public bool? UsesAnsiNulls => _usesAnsiNulls;
    public int DataSourceId => _dataSourceId;
    public int? FileFormatId => _fileFormatId;
    public string? Location => _location;
    public string? RejectType => _rejectType;
    public double? RejectValue => _rejectValue;
    public double? RejectSampleValue => _rejectSampleValue;
    public byte? DistributionType => _distributionType;
    public string? DistributionDesc => _distributionDesc;
    public int? ShardingColId => _shardingColId;
    public string? RemoteSchemaName => _remoteSchemaName;
    public string? RemoteObjectName => _remoteObjectName;
    public string? RejectedRowLocation => _rejectedRowLocation;
}

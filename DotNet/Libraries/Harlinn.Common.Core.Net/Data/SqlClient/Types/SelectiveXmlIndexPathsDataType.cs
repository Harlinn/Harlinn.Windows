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

public class SelectiveXmlIndexPathsDataType
{
    readonly int _objectId = 0;
    readonly int _indexId = 0;
    readonly int? _pathId;
    readonly string? _path;
    readonly string? _name;
    readonly byte? _pathType;
    readonly string? _pathTypeDesc;
    readonly int? _xmlComponentId;
    readonly string? _xqueryTypeDescription;
    readonly bool? _isXqueryTypeInferred;
    readonly int? _xqueryMaxLength;
    readonly bool? _isXqueryMaxLengthInferred;
    readonly bool? _isNode;
    readonly byte? _systemTypeId;
    readonly byte? _userTypeId;
    readonly short? _maxLength;
    readonly byte? _precision;
    readonly byte? _scale;
    readonly string? _collationName;
    readonly bool? _isSingleton;

    public SelectiveXmlIndexPathsDataType( )
    {
    }

    public SelectiveXmlIndexPathsDataType(int objectId,
        int indexId,
        int? pathId,
        string? path,
        string? name,
        byte? pathType,
        string? pathTypeDesc,
        int? xmlComponentId,
        string? xqueryTypeDescription,
        bool? isXqueryTypeInferred,
        int? xqueryMaxLength,
        bool? isXqueryMaxLengthInferred,
        bool? isNode,
        byte? systemTypeId,
        byte? userTypeId,
        short? maxLength,
        byte? precision,
        byte? scale,
        string? collationName,
        bool? isSingleton)
    {
        _objectId = objectId;
        _indexId = indexId;
        _pathId = pathId;
        _path = path;
        _name = name;
        _pathType = pathType;
        _pathTypeDesc = pathTypeDesc;
        _xmlComponentId = xmlComponentId;
        _xqueryTypeDescription = xqueryTypeDescription;
        _isXqueryTypeInferred = isXqueryTypeInferred;
        _xqueryMaxLength = xqueryMaxLength;
        _isXqueryMaxLengthInferred = isXqueryMaxLengthInferred;
        _isNode = isNode;
        _systemTypeId = systemTypeId;
        _userTypeId = userTypeId;
        _maxLength = maxLength;
        _precision = precision;
        _scale = scale;
        _collationName = collationName;
        _isSingleton = isSingleton;
    }

    public int ObjectId => _objectId;
    public int IndexId => _indexId;
    public int? PathId => _pathId;
    public string? Path => _path;
    public string? Name => _name;
    public byte? PathType => _pathType;
    public string? PathTypeDesc => _pathTypeDesc;
    public int? XmlComponentId => _xmlComponentId;
    public string? XqueryTypeDescription => _xqueryTypeDescription;
    public bool? IsXqueryTypeInferred => _isXqueryTypeInferred;
    public int? XqueryMaxLength => _xqueryMaxLength;
    public bool? IsXqueryMaxLengthInferred => _isXqueryMaxLengthInferred;
    public bool? IsNode => _isNode;
    public byte? SystemTypeId => _systemTypeId;
    public byte? UserTypeId => _userTypeId;
    public short? MaxLength => _maxLength;
    public byte? Precision => _precision;
    public byte? Scale => _scale;
    public string? CollationName => _collationName;
    public bool? IsSingleton => _isSingleton;
}

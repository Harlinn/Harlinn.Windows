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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types;

public class InternalTablesDataType
{
    readonly string _name = string.Empty;
    readonly int _objectId = 0;
    readonly int? _principalId;
    readonly int _schemaId = 0;
    readonly int _parentObjectId = 0;
    readonly string _type = string.Empty;
    readonly string? _typeDesc;
    readonly DateTime _createDate;
    readonly DateTime _modifyDate;
    readonly bool? _isMsShipped;
    readonly bool? _isPublished;
    readonly bool? _isSchemaPublished;
    readonly byte? _internalType;
    readonly string? _internalTypeDesc;
    readonly int? _parentId;
    readonly int? _parentMinorId;
    readonly int _lobDataSpaceId = 0;
    readonly int? _filestreamDataSpaceId;

    public InternalTablesDataType( )
    {
    }

    public InternalTablesDataType(string name,
        int objectId,
        int? principalId,
        int schemaId,
        int parentObjectId,
        string type,
        string? typeDesc,
        DateTime createDate,
        DateTime modifyDate,
        bool? isMsShipped,
        bool? isPublished,
        bool? isSchemaPublished,
        byte? internalType,
        string? internalTypeDesc,
        int? parentId,
        int? parentMinorId,
        int lobDataSpaceId,
        int? filestreamDataSpaceId)
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
        _internalType = internalType;
        _internalTypeDesc = internalTypeDesc;
        _parentId = parentId;
        _parentMinorId = parentMinorId;
        _lobDataSpaceId = lobDataSpaceId;
        _filestreamDataSpaceId = filestreamDataSpaceId;
    }

    public string Name => _name;
    public int ObjectId => _objectId;
    public int? PrincipalId => _principalId;
    public int SchemaId => _schemaId;
    public int ParentObjectId => _parentObjectId;
    public string Type => _type;
    public string? TypeDesc => _typeDesc;
    public DateTime CreateDate => _createDate;
    public DateTime ModifyDate => _modifyDate;
    public bool? IsMsShipped => _isMsShipped;
    public bool? IsPublished => _isPublished;
    public bool? IsSchemaPublished => _isSchemaPublished;
    public byte? InternalType => _internalType;
    public string? InternalTypeDesc => _internalTypeDesc;
    public int? ParentId => _parentId;
    public int? ParentMinorId => _parentMinorId;
    public int LobDataSpaceId => _lobDataSpaceId;
    public int? FilestreamDataSpaceId => _filestreamDataSpaceId;
}

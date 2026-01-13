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

public class ExtendedProceduresDataType
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
    readonly string? _dllName;

    public ExtendedProceduresDataType( )
    {
    }

    public ExtendedProceduresDataType(string name,
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
        string? dllName)
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
        _dllName = dllName;
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
    public string? DllName => _dllName;
}

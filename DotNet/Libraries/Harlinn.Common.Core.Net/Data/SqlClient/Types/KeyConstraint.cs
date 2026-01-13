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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{
    public sealed class KeyConstraint
    {
        private readonly string _name;
        private readonly int _objectId;
        private readonly int? _principalId;
        private readonly int _schemaId;
        private readonly int _parentObjectId;
        private readonly SchemaObjectType _type;
        private readonly string _typeDesc;
        private readonly DateTime _createDate;
        private readonly DateTime _modifyDate;
        private readonly bool _isMsShipped;
        private readonly bool _isPublished;
        private readonly bool _isSchemaPublished;
        private readonly int? _uniqueIndexId;
        private readonly bool _isSystemNamed;
        private readonly bool _isEnforced;
        private readonly string? _tableName;

        public KeyConstraint(
            string name,
            int objectId,
            int? principalId,
            int schemaId,
            int parentObjectId,
            string type,
            string typeDesc,
            DateTime createDate,
            DateTime modifyDate,
            bool isMsShipped,
            bool isPublished,
            bool isSchemaPublished,
            int? uniqueIndexId,
            bool isSystemNamed,
            bool isEnforced,
            string? tableName)
        {
            _name = name ?? throw new ArgumentNullException(nameof(name));
            _objectId = objectId;
            _principalId = principalId;
            _schemaId = schemaId;
            _parentObjectId = parentObjectId;
            _type = type?.ToSchemaObjectType() ?? throw new ArgumentNullException(nameof(type));
            _typeDesc = typeDesc ?? throw new ArgumentNullException(nameof(typeDesc));
            _createDate = createDate;
            _modifyDate = modifyDate;
            _isMsShipped = isMsShipped;
            _isPublished = isPublished;
            _isSchemaPublished = isSchemaPublished;
            _uniqueIndexId = uniqueIndexId;
            _isSystemNamed = isSystemNamed;
            _isEnforced = isEnforced;
            _tableName = tableName;
        }

        public string Name => _name;
        public int ObjectId => _objectId;
        public int? PrincipalId => _principalId;
        public int SchemaId => _schemaId;
        public int ParentObjectId => _parentObjectId;
        public SchemaObjectType Type => _type;
        public string TypeDesc => _typeDesc;
        public DateTime CreateDate => _createDate;
        public DateTime ModifyDate => _modifyDate;
        public bool IsMsShipped => _isMsShipped;
        public bool IsPublished => _isPublished;
        public bool IsSchemaPublished => _isSchemaPublished;
        public int? UniqueIndexId => _uniqueIndexId;
        public bool IsSystemNamed => _isSystemNamed;
        public bool IsEnforced => _isEnforced;
        public string? TableName => _tableName;

        
    }
}
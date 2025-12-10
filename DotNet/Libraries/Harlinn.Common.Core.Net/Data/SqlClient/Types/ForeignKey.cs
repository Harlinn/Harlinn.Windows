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

    public class ForeignKey
    {
        readonly string _name;
        readonly int _objectId;
        readonly int? _principalId;
        readonly int _schemaId;
        readonly int _parentObjectId;
        readonly string _type;
        readonly string _typeDesc;
        readonly DateTime _createDate;
        readonly DateTime _modifyDate;
        readonly bool _isMsShipped;
        readonly bool _isPublished;
        readonly bool _isSchemaPublished;
        readonly int _referencedObjectId;
        readonly int _keyIndexId;
        readonly bool _isDisabled;
        readonly bool _isNotForReplication;
        readonly bool _isNotTrusted;
        readonly sbyte _deleteReferentialAction;
        readonly string _deleteReferentialActionDesc;
        readonly sbyte _updateReferentialAction;
        readonly string _updateReferentialActionDesc;
        readonly bool _isSystemNamed;

        public ForeignKey(string name, int objectId, int? principalId, int schemaId, int parentObjectId, string type, string typeDesc, DateTime createDate, DateTime modifyDate, bool isMsShipped, bool isPublished, bool isSchemaPublished, int referencedObjectId, int keyIndexId, bool isDisabled, bool isNotForReplication, bool isNotTrusted, sbyte deleteReferentialAction, string deleteReferentialActionDesc, sbyte updateReferentialAction, string updateReferentialActionDesc, bool isSystemNamed)
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
            _referencedObjectId = referencedObjectId;
            _keyIndexId = keyIndexId;
            _isDisabled = isDisabled;
            _isNotForReplication = isNotForReplication;
            _isNotTrusted = isNotTrusted;
            _deleteReferentialAction = deleteReferentialAction;
            _deleteReferentialActionDesc = deleteReferentialActionDesc;
            _updateReferentialAction = updateReferentialAction;
            _updateReferentialActionDesc = updateReferentialActionDesc;
            _isSystemNamed = isSystemNamed;
        }

        public string Name => _name;

        public int ObjectId => _objectId;

        public int? PrincipalId => _principalId;

        public int SchemaId => _schemaId;

        public int ParentObjectId => _parentObjectId;

        public string Type => _type;

        public string TypeDesc => _typeDesc;

        public DateTime CreateDate => _createDate;

        public DateTime ModifyDate => _modifyDate;

        public bool IsMsShipped => _isMsShipped;

        public bool IsPublished => _isPublished;

        public bool IsSchemaPublished => _isSchemaPublished;

        public int ReferencedObjectId => _referencedObjectId;

        public int KeyIndexId => _keyIndexId;

        public bool IsDisabled => _isDisabled;

        public bool IsNotForReplication => _isNotForReplication;

        public bool IsNotTrusted => _isNotTrusted;

        public sbyte DeleteReferentialAction => _deleteReferentialAction;

        public string DeleteReferentialActionDesc => _deleteReferentialActionDesc;

        public sbyte UpdateReferentialAction => _updateReferentialAction;

        public string UpdateReferentialActionDesc => _updateReferentialActionDesc;

        public bool IsSystemNamed => _isSystemNamed;
    }

}

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
    /// <summary>
    /// Represents a row from the sys.procedures catalog view.
    /// </summary>
    public sealed class Procedure : ISchemaObject
    {
        private readonly string _name;
        private readonly int _objectId;
        private readonly int? _principalId;
        private readonly int _schemaId;
        private readonly int? _parentObjectId;
        private readonly SchemaObjectType _type;
        private readonly string _typeDesc;
        private readonly DateTime _createDate;
        private readonly DateTime _modifyDate;
        private readonly bool? _isMsShipped;
        private readonly bool? _isPublished;
        private readonly bool? _isSchemaPublished;
        private readonly bool _isAutoExecuted;
        private readonly bool _isExecutionReplicated;
        private readonly bool _isReplSerializableOnly;
        private readonly bool _skipsReplConstraints;

        public Procedure(
            string name,
            int objectId,
            int? principalId,
            int schemaId,
            int? parentObjectId,
            string type,
            string typeDesc,
            DateTime createDate,
            DateTime modifyDate,
            bool? isMsShipped,
            bool? isPublished,
            bool? isSchemaPublished,
            bool isAutoExecuted,
            bool isExecutionReplicated,
            bool isReplSerializableOnly,
            bool skipsReplConstraints)
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
            _isAutoExecuted = isAutoExecuted;
            _isExecutionReplicated = isExecutionReplicated;
            _isReplSerializableOnly = isReplSerializableOnly;
            _skipsReplConstraints = skipsReplConstraints;
        }

        /// <summary>
        /// Gets the name of the procedure.
        /// </summary>
        public string Name => _name;

        /// <summary>
        /// Gets the object ID.
        /// The object_id is the ID of the object in sys.objects.
        /// </summary>
        public int ObjectId => _objectId;

        /// <summary>
        /// Gets the ID of the database principal that owns the object.
        /// This corresponds to the principal_id column in the system view.
        /// </summary>
        public int? PrincipalId => _principalId;

        /// <summary>
        /// Gets the schema ID that contains the object.
        /// This corresponds to the schema_id column.
        /// </summary>
        public int SchemaId => _schemaId;

        /// <summary>
        /// Gets the object_id of the parent object, if any.
        /// For procedures this is generally the same as the object_id of the parent.
        /// </summary>
        public int? ParentObjectId => _parentObjectId;

        /// <summary>
        /// Gets the object type (one-character code).
        /// This corresponds to the type column in sys.procedures.
        /// </summary>
        public SchemaObjectType Type => _type;

        /// <summary>
        /// Gets the textual description of the object type.
        /// This corresponds to the type_desc column.
        /// </summary>
        public string TypeDesc => _typeDesc;

        /// <summary>
        /// Gets the date the object was created.
        /// Corresponds to the create_date column.
        /// </summary>
        public DateTime CreateDate => _createDate;

        /// <summary>
        /// Gets the date the object was last modified.
        /// Corresponds to the modify_date column.
        /// </summary>
        public DateTime ModifyDate => _modifyDate;

        /// <summary>
        /// Gets a value that indicates whether the object was shipped with the product.
        /// Corresponds to the is_ms_shipped column.
        /// </summary>
        public bool? IsMsShipped => _isMsShipped;

        /// <summary>
        /// Gets a value that indicates whether the object is published.
        /// Corresponds to the is_published column.
        /// </summary>
        public bool? IsPublished => _isPublished;

        /// <summary>
        /// Gets a value that indicates whether the object's schema is published.
        /// Corresponds to the is_schema_published column.
        /// </summary>
        public bool? IsSchemaPublished => _isSchemaPublished;

        /// <summary>
        /// Gets a value that indicates whether the procedure is auto-executed.
        /// Corresponds to the is_auto_executed column.
        /// </summary>
        public bool IsAutoExecuted => _isAutoExecuted;

        /// <summary>
        /// Gets a value that indicates whether execution of the procedure is replicated.
        /// Corresponds to the is_execution_replicated column.
        /// </summary>
        public bool IsExecutionReplicated => _isExecutionReplicated;

        /// <summary>
        /// Gets a value that indicates whether the procedure is replication-serializable only.
        /// Corresponds to the is_repl_serializable_only column.
        /// </summary>
        public bool IsReplSerializableOnly => _isReplSerializableOnly;

        /// <summary>
        /// Gets a value that indicates whether the procedure skips replication constraint checks when executed.
        /// Corresponds to the skips_repl_constraints column.
        /// </summary>
        public bool SkipsReplConstraints => _skipsReplConstraints;

        
    }
}
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
    public class CheckConstraint : SchemaObject
    {
        readonly bool _isDisabled;
        readonly bool _isNotForReplication;
        readonly bool _isNotTrusted;
        readonly int _parentColumnId;
        readonly string _definition;
        readonly bool _usesDatabaseCollation;
        readonly bool _isSystemNamed;
        readonly string? _columnName;
        public CheckConstraint(string name, int objectId, int? principalId, int schemaId, int? parentObjectId, string type, string typeDesc, DateTime createDate, DateTime modifyDate, bool? isMsShipped, bool? isPublished, bool? isSchemaPublished, bool isDisabled,  bool isNotForReplication, bool isNotTrusted, int parentColumnId, string definition, bool usesDatabaseCollation, bool isSystemNamed, string? columnName)
            : base(name, objectId, principalId, schemaId, parentObjectId, type, typeDesc, createDate, modifyDate, isMsShipped, isPublished, isSchemaPublished)
        {
            _isDisabled = isDisabled;
            _isNotForReplication = isNotForReplication;
            _isNotTrusted = isNotTrusted;
            _parentColumnId = parentColumnId;
            _definition = definition;
            _usesDatabaseCollation = usesDatabaseCollation;
            _isSystemNamed = isSystemNamed;
            _columnName = columnName;
        }

        /// <summary>
        /// Indicates whether the CHECK constraint is currently disabled.
        /// </summary>
        public bool IsDisabled => _isDisabled;
        /// <summary>
        /// Indicates that the CHECK constraint was created with the NOT FOR REPLICATION option.
        /// </summary>
        public bool IsNotForReplication => _isNotForReplication;
        /// <summary>
        /// Indicates that the CHECK constraint has not been verified by the system for all rows.
        /// </summary>
        public bool IsNotTrusted => _isNotTrusted;
        /// <summary>
        /// If the CHECK constraint is defined on a specific column, this property contains the ID of that column; otherwise, it is 0.
        /// </summary>
        public int ParentColumnId => _parentColumnId;
        /// <summary>
        /// SQL expression that defines this CHECK constraint.
        /// </summary>
        public string Definition => _definition;
        /// <summary>
        /// true if the CHECK constraint definition depends on the default collation of the database
        /// for correct evaluation; otherwise, false. Such a dependency prevents changing the database default collation.
        /// </summary>
        public bool UsesDatabaseCollation => _usesDatabaseCollation;
        public bool IsSystemNamed => _isSystemNamed;
        /// <summary>
        /// If the check constraint is defined on a specific column, this property contains the name of that column; otherwise, it is null.
        /// </summary>
        public string? ColumnName => _columnName;
    }

}

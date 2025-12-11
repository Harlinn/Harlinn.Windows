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
    public class ForeignKeyColumn
    {
        readonly int _constraintObjectId;
        readonly int _constraintColumnId;
        readonly int _parentObjectId;
        readonly int _parentColumnId;
        readonly int _referencedObjectId;
        readonly int _referencedColumnId;
        readonly string _columnName;  
        readonly string _referencedColumnName;

        public ForeignKeyColumn(int constraintObjectId, int constraintColumnId, int parentObjectId, int parentColumnId, int referencedObjectId, int referencedColumnId, string columnName, string referencedColumnName)
        {
            _constraintObjectId = constraintObjectId;
            _constraintColumnId = constraintColumnId;
            _parentObjectId = parentObjectId;
            _parentColumnId = parentColumnId;
            _referencedObjectId = referencedObjectId;
            _referencedColumnId = referencedColumnId;
            _columnName = columnName;
            _referencedColumnName = referencedColumnName;
        }

        /// <summary>
        /// ID of the FOREIGN KEY constraint.
        /// </summary>
        public int ConstraintObjectId => _constraintObjectId;

        /// <summary>
        /// ID of the column, or set of columns, that comprise the FOREIGN KEY (1..n where n is the number of columns).
        /// </summary>
        public int ConstraintColumnId => _constraintColumnId;

        /// <summary>
        /// ID of the parent of the constraint, which is the referencing object.
        /// </summary>
        public int ParentObjectId => _parentObjectId;

        /// <summary>
        /// ID of the parent column, which is the referencing column.
        /// </summary>
        public int ParentColumnId => _parentColumnId;

        /// <summary>
        /// ID of the referenced object, which has the candidate key.
        /// </summary>
        public int ReferencedObjectId => _referencedObjectId;

        /// <summary>
        /// ID of the referenced column (candidate key column).
        /// </summary>
        public int ReferencedColumnId => _referencedColumnId;

        /// <summary>
        /// Gets the name of the referencing column.
        /// </summary>
        public string ColumnName => _columnName;               

        /// <summary>
        /// Gets the name of the referenced column.
        /// </summary>
        public string ReferencedColumnName => _referencedColumnName;
    }

}

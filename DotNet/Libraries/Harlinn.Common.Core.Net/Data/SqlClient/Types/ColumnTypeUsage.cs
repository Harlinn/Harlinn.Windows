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
    /// Represents a row from the <c>sys.column_type_usages</c> catalog view.
    /// Immutable type with private readonly backing fields prefixed with '_'.
    /// </summary>
    public sealed class ColumnTypeUsage
    {
        private readonly int _objectId;
        private readonly int _columnId;
        private readonly int _userTypeId;

        /// <summary>
        /// Initializes a new instance of <see cref="ColumnTypeUsage"/>.
        /// </summary>
        /// <param name="objectId">ID of the object that contains the column. (sys.column_type_usages.object_id)</param>
        /// <param name="columnId">ID of the column within the object. (sys.column_type_usages.column_id)</param>
        /// <param name="userTypeId">User type ID used by the column. (sys.column_type_usages.user_type_id)</param>
        public ColumnTypeUsage(int objectId, int columnId, int userTypeId)
        {
            _objectId = objectId;
            _columnId = columnId;
            _userTypeId = userTypeId;
        }

        /// <summary>
        /// ID of the object that contains the column. (sys.column_type_usages.object_id)
        /// The object_id corresponds to the object in sys.objects that owns the column.
        /// </summary>
        public int ObjectId => _objectId;

        /// <summary>
        /// ID of the column within the object. (sys.column_type_usages.column_id)
        /// Identifies the specific column that uses the user-defined type.
        /// </summary>
        public int ColumnId => _columnId;

        /// <summary>
        /// User type ID used by the column. (sys.column_type_usages.user_type_id)
        /// The user_type_id references an entry in sys.types for the user-defined type.
        /// </summary>
        public int UserTypeId => _userTypeId;
    }
}
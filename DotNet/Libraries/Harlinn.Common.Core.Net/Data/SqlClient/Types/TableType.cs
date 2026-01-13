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
    public class TableType : DatabaseType
    {
        readonly int _typeTableObjectId;
        readonly bool _isMemoryOptimized;
        public TableType(string name, byte systemTypeId, int userTypeId, int schemaId, int? principalId, short maxLength, byte precision, byte scale, string? collationName, bool isNullable, bool isUserDefined, bool isAssemblyType, int defaultObjectId, int ruleObjectId, bool isTableType, int typeTableObjectId,  bool isMemoryOptimized)
            : base(name, systemTypeId, userTypeId, schemaId, principalId, maxLength, precision, scale, collationName, isNullable, isUserDefined, isAssemblyType, defaultObjectId, ruleObjectId, isTableType)
        {
            _typeTableObjectId = typeTableObjectId;
            _isMemoryOptimized = isMemoryOptimized;
        }
        /// <summary>
        /// ID of the table object that defines the table type structure.
        /// </summary>
        public int TypeTableObjectId => _typeTableObjectId;
        /// <summary>
        /// Indicates whether the table type is memory-optimized.
        /// </summary>
        public bool IsMemoryOptimized => _isMemoryOptimized;
    }


}

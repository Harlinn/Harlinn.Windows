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
    public class ComputedColumn : Column
    {
        readonly string _definition = string.Empty;
        readonly bool _usesDatabaseCollation = false;
        readonly bool _isPersisted = false;

        public ComputedColumn(int objectId, string name, int columnId, byte systemTypeId, int userTypeId, short maxLength, byte precision, byte scale, string? collationName, bool isNullable, bool isAnsiPadded, bool isRowguidcol, bool isIdentity, bool isComputed, bool isFilestream, bool isReplicated, bool isNonSqlSubscribed, bool isMergePublished, bool isDtsReplicated, bool isXmlDocument, int xmlCollectionId, int defaultObjectId, int ruleObjectId, bool isSparse, bool isColumnSet, byte generatedAlwaysType, string generatedAlwaysTypeDesc, int? encryptionType, string? encryptionTypeDesc, string? encryptionAlgorithmName, int? columnEncryptionKeyId, string? columnEncryptionKeyDatabaseName, bool isHidden, bool isMasked, int? graphType, string? graphTypeDesc, string computedDefinition, bool usesDatabaseCollation, bool isPersisted, string typeName)
            : base(objectId, name, columnId, systemTypeId, userTypeId, maxLength, precision, scale, collationName, isNullable, isAnsiPadded, isRowguidcol, isIdentity, isComputed, isFilestream, isReplicated, isNonSqlSubscribed, isMergePublished, isDtsReplicated, isXmlDocument, xmlCollectionId, defaultObjectId, ruleObjectId, isSparse, isColumnSet, generatedAlwaysType, generatedAlwaysTypeDesc, encryptionType, encryptionTypeDesc, encryptionAlgorithmName, columnEncryptionKeyId, columnEncryptionKeyDatabaseName, isHidden, isMasked, graphType, graphTypeDesc, typeName)
        {
            _definition = computedDefinition;
            _usesDatabaseCollation = usesDatabaseCollation;
            _isPersisted = isPersisted;
        }

        /// <summary>
        /// SQL text that defines this computed-column.
        /// </summary>
        public string Definition => _definition;

        /// <summary>
        /// true if The column definition depends on the default collation 
        /// of the database for correct evaluation; otherwise, false. Such 
        /// a dependency prevents changing the database default collation.
        /// </summary>
        public bool UsesDatabaseCollation => _usesDatabaseCollation;

        /// <summary>
        /// Computed column is persisted.
        /// </summary>
        public bool IsPersisted => _isPersisted;
    }

}

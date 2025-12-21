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
    public class IdentityColumn : Column
    {
        private object _seedValue;
        private object _incrementValue;
        private object? _lastValue;
        private bool _isNotForReplication;

        public IdentityColumn(int objectId, string name, int columnId, sbyte systemTypeId, int userTypeId, short maxLength, sbyte precision, sbyte scale, string? collationName, bool isNullable, bool isAnsiPadded, bool isRowguidcol, bool isIdentity, bool isComputed, bool isFilestream, bool isReplicated, bool isNonSqlSubscribed, bool isMergePublished, bool isDtsReplicated, bool isXmlDocument, int xmlCollectionId, int defaultObjectId, int ruleObjectId, bool isSparse, bool isColumnSet, sbyte generatedAlwaysType, string generatedAlwaysTypeDesc, int? encryptionType, string? encryptionTypeDesc, string? encryptionAlgorithmName, int? columnEncryptionKeyId, string? columnEncryptionKeyDatabaseName, bool isHidden, bool isMasked, int? graphType, string? graphTypeDesc, object seedValue, object incrementValue, object lastValue, bool isNotForReplication, string typeName)
            : base(objectId, name, columnId, systemTypeId, userTypeId, maxLength, precision, scale, collationName, isNullable, isAnsiPadded, isRowguidcol, isIdentity, isComputed, isFilestream, isReplicated, isNonSqlSubscribed, isMergePublished, isDtsReplicated, isXmlDocument, xmlCollectionId, defaultObjectId, ruleObjectId, isSparse, isColumnSet, generatedAlwaysType, generatedAlwaysTypeDesc, encryptionType, encryptionTypeDesc, encryptionAlgorithmName, columnEncryptionKeyId, columnEncryptionKeyDatabaseName, isHidden, isMasked, graphType, graphTypeDesc, typeName)
        {
            _seedValue = seedValue;
            _incrementValue = incrementValue;
            _lastValue = lastValue;
            _isNotForReplication = isNotForReplication;
        }

        public object SeedValue { get => _seedValue; set => _seedValue = value; }
        public object IncrementValue { get => _incrementValue; set => _incrementValue = value; }
        public object? LastValue { get => _lastValue; set => _lastValue = value; }
        public bool IsNotForReplication { get => _isNotForReplication; set => _isNotForReplication = value; }
    }

}

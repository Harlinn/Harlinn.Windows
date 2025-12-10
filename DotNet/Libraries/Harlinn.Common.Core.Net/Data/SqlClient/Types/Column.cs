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
    public class Column
    {
        readonly int _objectId;

        readonly string _name;

        readonly int _columnId;

        readonly sbyte _systemTypeId;

        readonly int _userTypeId;

        readonly short _maxLength;

        readonly sbyte _precision;

        readonly sbyte _scale;

        readonly string? _collationName;

        readonly bool _isNullable;

        readonly bool _isAnsiPadded;

        readonly bool _isRowguidcol;

        readonly bool _isIdentity;

        readonly bool _isComputed;

        readonly bool _isFilestream;

        readonly bool _isReplicated;

        readonly bool _isNonSqlSubscribed;

        readonly bool _isMergePublished;

        readonly bool _isDtsReplicated;

        readonly bool _isXmlDocument;

        readonly int _xmlCollectionId;

        readonly int _defaultObjectId;

        readonly int _ruleObjectId;

        readonly bool _isSparse;

        readonly bool _isColumnSet;

        readonly sbyte _generatedAlwaysType;

        readonly string _generatedAlwaysTypeDesc;

        readonly int? _encryptionType;

        readonly string? _encryptionTypeDesc;

        readonly string? _encryptionAlgorithmName;

        readonly int? _columnEncryptionKeyId;

        readonly string? _columnEncryptionKeyDatabaseName;

        readonly bool _isHidden;

        readonly bool _isMasked;

        readonly int? _graphType;

        readonly string? _graphTypeDesc;

        public Column(int objectId, string name, int columnId, sbyte systemTypeId, int userTypeId, short maxLength, sbyte precision, sbyte scale, string? collationName, bool isNullable, bool isAnsiPadded, bool isRowguidcol, bool isIdentity, bool isComputed, bool isFilestream, bool isReplicated, bool isNonSqlSubscribed, bool isMergePublished, bool isDtsReplicated, bool isXmlDocument, int xmlCollectionId, int defaultObjectId, int ruleObjectId, bool isSparse, bool isColumnSet, sbyte generatedAlwaysType, string generatedAlwaysTypeDesc, int? encryptionType, string? encryptionTypeDesc, string? encryptionAlgorithmName, int? columnEncryptionKeyId, string? columnEncryptionKeyDatabaseName, bool isHidden, bool isMasked, int? graphType, string? graphTypeDesc)
        {
            _objectId = objectId;
            _name = name;
            _columnId = columnId;
            _systemTypeId = systemTypeId;
            _userTypeId = userTypeId;
            _maxLength = maxLength;
            _precision = precision;
            _scale = scale;
            _collationName = collationName;
            _isNullable = isNullable;
            _isAnsiPadded = isAnsiPadded;
            _isRowguidcol = isRowguidcol;
            _isIdentity = isIdentity;
            _isComputed = isComputed;
            _isFilestream = isFilestream;
            _isReplicated = isReplicated;
            _isNonSqlSubscribed = isNonSqlSubscribed;
            _isMergePublished = isMergePublished;
            _isDtsReplicated = isDtsReplicated;
            _isXmlDocument = isXmlDocument;
            _xmlCollectionId = xmlCollectionId;
            _defaultObjectId = defaultObjectId;
            _ruleObjectId = ruleObjectId;
            _isSparse = isSparse;
            _isColumnSet = isColumnSet;
            _generatedAlwaysType = generatedAlwaysType;
            _generatedAlwaysTypeDesc = generatedAlwaysTypeDesc;
            _encryptionType = encryptionType;
            _encryptionTypeDesc = encryptionTypeDesc;
            _encryptionAlgorithmName = encryptionAlgorithmName;
            _columnEncryptionKeyId = columnEncryptionKeyId;
            _columnEncryptionKeyDatabaseName = columnEncryptionKeyDatabaseName;
            _isHidden = isHidden;
            _isMasked = isMasked;
            _graphType = graphType;
            _graphTypeDesc = graphTypeDesc;
        }

        public int ObjectId => _objectId;

        public string Name => _name;

        public int ColumnId => _columnId;

        public sbyte SystemTypeId => _systemTypeId;

        public int UserTypeId => _userTypeId;

        public short MaxLength => _maxLength;

        public sbyte Precision => _precision;

        public sbyte Scale => _scale;

        public string? CollationName => _collationName;

        public bool IsNullable => _isNullable;

        public bool IsAnsiPadded => _isAnsiPadded;

        public bool IsRowguidcol => _isRowguidcol;

        public bool IsIdentity => _isIdentity;

        public bool IsComputed => _isComputed;

        public bool IsFilestream => _isFilestream;

        public bool IsReplicated => _isReplicated;

        public bool IsNonSqlSubscribed => _isNonSqlSubscribed;

        public bool IsMergePublished => _isMergePublished;

        public bool IsDtsReplicated => _isDtsReplicated;

        public bool IsXmlDocument => _isXmlDocument;

        public int XmlCollectionId => _xmlCollectionId;

        public int DefaultObjectId => _defaultObjectId;

        public int RuleObjectId => _ruleObjectId;

        public bool IsSparse => _isSparse;

        public bool IsColumnSet => _isColumnSet;

        public sbyte GeneratedAlwaysType => _generatedAlwaysType;

        public string GeneratedAlwaysTypeDesc => _generatedAlwaysTypeDesc;

        public int? EncryptionType => _encryptionType;

        public string? EncryptionTypeDesc => _encryptionTypeDesc;

        public string? EncryptionAlgorithmName => _encryptionAlgorithmName;

        public int? ColumnEncryptionKeyId => _columnEncryptionKeyId;

        public string? ColumnEncryptionKeyDatabaseName => _columnEncryptionKeyDatabaseName;

        public bool IsHidden => _isHidden;

        public bool IsMasked => _isMasked;

        public int? GraphType => _graphType;

        public string? GraphTypeDesc => _graphTypeDesc;
    }

}

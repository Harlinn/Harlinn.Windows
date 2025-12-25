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

using System;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Types
{
    /// <summary>
    /// Represents a row from the <c>sys.masked_columns</c> catalog view.
    /// Immutable, uses private readonly backing fields prefixed with '_'.
    /// </summary>
    public sealed class MaskedColumn
    {
        private readonly int _objectId;
        private readonly string _name;
        private readonly int _columnId;
        private readonly sbyte _systemTypeId;
        private readonly int _userTypeId;
        private readonly short _maxLength;
        private readonly sbyte _precision;
        private readonly sbyte _scale;
        private readonly string? _collationName;
        private readonly bool _isNullable;
        private readonly bool _isAnsiPadded;
        private readonly bool _isRowguidcol;
        private readonly bool _isIdentity;
        private readonly bool _isFilestream;
        private readonly bool _isReplicated;
        private readonly bool _isNonSqlSubscribed;
        private readonly bool _isMergePublished;
        private readonly bool _isDtsReplicated;
        private readonly bool _isXmlDocument;
        private readonly int? _xmlCollectionId;
        private readonly int? _defaultObjectId;
        private readonly int? _ruleObjectId;
        private readonly string? _definition;
        private readonly bool _usesDatabaseCollation;
        private readonly bool _isPersisted;
        private readonly bool _isComputed;
        private readonly bool _isSparse;
        private readonly bool _isColumnSet;
        private readonly sbyte _generatedAlwaysType;
        private readonly string? _generatedAlwaysTypeDesc;
        private readonly int? _encryptionType;
        private readonly string? _encryptionTypeDesc;
        private readonly string? _encryptionAlgorithmName;
        private readonly int? _columnEncryptionKeyId;
        private readonly string? _columnEncryptionKeyDatabaseName;
        private readonly bool _isHidden;
        private readonly bool _isMasked;
        private readonly string? _maskingFunction;
        private readonly int? _graphType;
        private readonly string? _graphTypeDesc;

        /// <summary>
        /// Initializes a new instance of the <see cref="MaskedColumn"/> class.
        /// </summary>
        public MaskedColumn(
            int objectId,
            string name,
            int columnId,
            sbyte systemTypeId,
            int userTypeId,
            short maxLength,
            sbyte precision,
            sbyte scale,
            string? collationName,
            bool isNullable,
            bool isAnsiPadded,
            bool isRowguidcol,
            bool isIdentity,
            bool isFilestream,
            bool isReplicated,
            bool isNonSqlSubscribed,
            bool isMergePublished,
            bool isDtsReplicated,
            bool isXmlDocument,
            int? xmlCollectionId,
            int? defaultObjectId,
            int? ruleObjectId,
            string? definition,
            bool usesDatabaseCollation,
            bool isPersisted,
            bool isComputed,
            bool isSparse,
            bool isColumnSet,
            sbyte generatedAlwaysType,
            string? generatedAlwaysTypeDesc,
            int? encryptionType,
            string? encryptionTypeDesc,
            string? encryptionAlgorithmName,
            int? columnEncryptionKeyId,
            string? columnEncryptionKeyDatabaseName,
            bool isHidden,
            bool isMasked,
            string? maskingFunction,
            int? graphType,
            string? graphTypeDesc)
        {
            _objectId = objectId;
            _name = name ?? throw new ArgumentNullException(nameof(name));
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
            _isFilestream = isFilestream;
            _isReplicated = isReplicated;
            _isNonSqlSubscribed = isNonSqlSubscribed;
            _isMergePublished = isMergePublished;
            _isDtsReplicated = isDtsReplicated;
            _isXmlDocument = isXmlDocument;
            _xmlCollectionId = xmlCollectionId;
            _defaultObjectId = defaultObjectId;
            _ruleObjectId = ruleObjectId;
            _definition = definition;
            _usesDatabaseCollation = usesDatabaseCollation;
            _isPersisted = isPersisted;
            _isComputed = isComputed;
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
            _maskingFunction = maskingFunction;
            _graphType = graphType;
            _graphTypeDesc = graphTypeDesc;
        }

        /// <summary>
        /// ID of the object that contains the column. (sys.masked_columns.object_id)
        /// </summary>
        public int ObjectId => _objectId;

        /// <summary>
        /// Name of the column. (sys.masked_columns.name)
        /// </summary>
        public string Name => _name;

        /// <summary>
        /// ID of the column within the object. (sys.masked_columns.column_id)
        /// </summary>
        public int ColumnId => _columnId;

        /// <summary>
        /// System-supplied type ID for the column. (sys.masked_columns.system_type_id)
        /// </summary>
        public sbyte SystemTypeId => _systemTypeId;

        /// <summary>
        /// User-defined type ID for the column. (sys.masked_columns.user_type_id)
        /// </summary>
        public int UserTypeId => _userTypeId;

        /// <summary>
        /// Maximum length, in bytes, of the column. (sys.masked_columns.max_length)
        /// </summary>
        public short MaxLength => _maxLength;

        /// <summary>
        /// Precision of the column (for numeric types). (sys.masked_columns.precision)
        /// </summary>
        public sbyte Precision => _precision;

        /// <summary>
        /// Scale of the column (for numeric types). (sys.masked_columns.scale)
        /// </summary>
        public sbyte Scale => _scale;

        /// <summary>
        /// Collation name for the column, if applicable. (sys.masked_columns.collation_name)
        /// </summary>
        public string? CollationName => _collationName;

        /// <summary>
        /// Indicates whether the column allows NULL. (sys.masked_columns.is_nullable)
        /// </summary>
        public bool IsNullable => _isNullable;

        /// <summary>
        /// Indicates whether values in the column are padded with spaces. (sys.masked_columns.is_ansi_padded)
        /// </summary>
        public bool IsAnsiPadded => _isAnsiPadded;

        /// <summary>
        /// Indicates whether the column is a ROWGUIDCOL. (sys.masked_columns.is_rowguidcol)
        /// </summary>
        public bool IsRowguidcol => _isRowguidcol;

        /// <summary>
        /// Indicates whether the column is an identity column. (sys.masked_columns.is_identity)
        /// </summary>
        public bool IsIdentity => _isIdentity;

        /// <summary>
        /// Indicates whether the column is a FILESTREAM column. (sys.masked_columns.is_filestream)
        /// </summary>
        public bool IsFilestream => _isFilestream;

        /// <summary>
        /// Indicates whether the column is replicated. (sys.masked_columns.is_replicated)
        /// </summary>
        public bool IsReplicated => _isReplicated;

        /// <summary>
        /// Indicates whether the column is non-SQL-subscriber replicated. (sys.masked_columns.is_non_sql_subscribed)
        /// </summary>
        public bool IsNonSqlSubscribed => _isNonSqlSubscribed;

        /// <summary>
        /// Indicates whether the column is published by merge replication. (sys.masked_columns.is_merge_published)
        /// </summary>
        public bool IsMergePublished => _isMergePublished;

        /// <summary>
        /// Indicates whether the column is DTS replicated. (sys.masked_columns.is_dts_replicated)
        /// </summary>
        public bool IsDtsReplicated => _isDtsReplicated;

        /// <summary>
        /// Indicates whether the column is an XML document type. (sys.masked_columns.is_xml_document)
        /// </summary>
        public bool IsXmlDocument => _isXmlDocument;

        /// <summary>
        /// ID of the XML collection if the column is xml typed. (sys.masked_columns.xml_collection_id)
        /// </summary>
        public int? XmlCollectionId => _xmlCollectionId;

        /// <summary>
        /// ID of the default object (if any). (sys.masked_columns.default_object_id)
        /// </summary>
        public int? DefaultObjectId => _defaultObjectId;

        /// <summary>
        /// ID of the rule object (if any). (sys.masked_columns.rule_object_id)
        /// </summary>
        public int? RuleObjectId => _ruleObjectId;

        /// <summary>
        /// Column definition text (for computed/expressed columns). (sys.masked_columns.definition)
        /// </summary>
        public string? Definition => _definition;

        /// <summary>
        /// Indicates whether the column uses the database collation. (sys.masked_columns.uses_database_collation)
        /// </summary>
        public bool UsesDatabaseCollation => _usesDatabaseCollation;

        /// <summary>
        /// Indicates whether the column is persisted. (sys.masked_columns.is_persisted)
        /// </summary>
        public bool IsPersisted => _isPersisted;

        /// <summary>
        /// Indicates whether the column is computed. (sys.masked_columns.is_computed)
        /// </summary>
        public bool IsComputed => _isComputed;

        /// <summary>
        /// Indicates whether the column is sparse. (sys.masked_columns.is_sparse)
        /// </summary>
        public bool IsSparse => _isSparse;

        /// <summary>
        /// Indicates whether the column is a column set. (sys.masked_columns.is_column_set)
        /// </summary>
        public bool IsColumnSet => _isColumnSet;

        /// <summary>
        /// Generated-always type value for the column. (sys.masked_columns.generated_always_type)
        /// </summary>
        public sbyte GeneratedAlwaysType => _generatedAlwaysType;

        /// <summary>
        /// Description of the generated-always type. (sys.masked_columns.generated_always_type_desc)
        /// </summary>
        public string? GeneratedAlwaysTypeDesc => _generatedAlwaysTypeDesc;

        /// <summary>
        /// Encryption type for Always Encrypted. (sys.masked_columns.encryption_type)
        /// </summary>
        public int? EncryptionType => _encryptionType;

        /// <summary>
        /// Description of the encryption type. (sys.masked_columns.encryption_type_desc)
        /// </summary>
        public string? EncryptionTypeDesc => _encryptionTypeDesc;

        /// <summary>
        /// Name of the encryption algorithm used. (sys.masked_columns.encryption_algorithm_name)
        /// </summary>
        public string? EncryptionAlgorithmName => _encryptionAlgorithmName;

        /// <summary>
        /// Column encryption key id for Always Encrypted. (sys.masked_columns.column_encryption_key_id)
        /// </summary>
        public int? ColumnEncryptionKeyId => _columnEncryptionKeyId;

        /// <summary>
        /// Database name that contains the column encryption key. (sys.masked_columns.column_encryption_key_database_name)
        /// </summary>
        public string? ColumnEncryptionKeyDatabaseName => _columnEncryptionKeyDatabaseName;

        /// <summary>
        /// Indicates whether the column is hidden. (sys.masked_columns.is_hidden)
        /// </summary>
        public bool IsHidden => _isHidden;

        /// <summary>
        /// Indicates whether the column is masked. (sys.masked_columns.is_masked)
        /// </summary>
        public bool IsMasked => _isMasked;

        /// <summary>
        /// Masking function applied to the column, if any. (sys.masked_columns.masking_function)
        /// </summary>
        public string? MaskingFunction => _maskingFunction;

        /// <summary>
        /// Graph type code for the column, if any. (sys.masked_columns.graph_type)
        /// </summary>
        public int? GraphType => _graphType;

        /// <summary>
        /// Description of the graph type for the column. (sys.masked_columns.graph_type_desc)
        /// </summary>
        public string? GraphTypeDesc => _graphTypeDesc;
    }
}
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
    /// Represents a row from the sys.parameters catalog view.
    /// Immutable, uses private readonly backing fields prefixed with '_'.
    /// </summary>
    public sealed class Parameter
    {
        private readonly int _objectId;
        private readonly string _name;
        private readonly int _parameterId;
        private readonly sbyte _systemTypeId;
        private readonly int _userTypeId;
        private readonly short _maxLength;
        private readonly sbyte _precision;
        private readonly sbyte _scale;
        private readonly bool _isOutput;
        private readonly bool _isCursorRef;
        private readonly bool _hasDefaultValue;
        private readonly bool _isXmlDocument;
        private readonly object? _defaultValue;
        private readonly int? _xmlCollectionId;
        private readonly bool _isReadOnly;
        private readonly bool _isNullable;
        private readonly int? _encryptionType;
        private readonly string? _encryptionTypeDesc;
        private readonly string? _encryptionAlgorithmName;
        private readonly int? _columnEncryptionKeyId;
        private readonly string? _columnEncryptionKeyDatabaseName;

        /// <summary>
        /// ID of the object that owns this parameter.
        /// Corresponds to the sys.parameters.[object_id] column.
        /// </summary>
        public int ObjectId => _objectId;

        /// <summary>
        /// Name of the parameter.
        /// Corresponds to the sys.parameters.[name] column.
        /// </summary>
        public string Name => _name;

        /// <summary>
        /// ID of the parameter within the object.
        /// Corresponds to the sys.parameters.[parameter_id] column.
        /// </summary>
        public int ParameterId => _parameterId;

        /// <summary>
        /// System type ID for the parameter (tinyint).
        /// Corresponds to the sys.parameters.[system_type_id] column.
        /// </summary>
        public sbyte SystemTypeId => _systemTypeId;

        /// <summary>
        /// User type ID for the parameter (user-defined type).
        /// Corresponds to the sys.parameters.[user_type_id] column.
        /// </summary>
        public int UserTypeId => _userTypeId;

        /// <summary>
        /// Maximum length of the parameter, in bytes.
        /// Corresponds to the sys.parameters.[max_length] column.
        /// </summary>
        public short MaxLength => _maxLength;

        /// <summary>
        /// Precision of the parameter (for numeric types).
        /// Corresponds to the sys.parameters.[precision] column.
        /// </summary>
        public sbyte Precision => _precision;

        /// <summary>
        /// Scale of the parameter (for numeric types).
        /// Corresponds to the sys.parameters.[scale] column.
        /// </summary>
        public sbyte Scale => _scale;

        /// <summary>
        /// Indicates whether the parameter is an output parameter.
        /// Corresponds to the sys.parameters.[is_output] column.
        /// </summary>
        public bool IsOutput => _isOutput;

        /// <summary>
        /// Indicates whether the parameter is a cursor reference.
        /// Corresponds to the sys.parameters.[is_cursor_ref] column.
        /// </summary>
        public bool IsCursorRef => _isCursorRef;

        /// <summary>
        /// Indicates whether the parameter has a default value.
        /// Corresponds to the sys.parameters.[has_default_value] column.
        /// </summary>
        public bool HasDefaultValue => _hasDefaultValue;

        /// <summary>
        /// Indicates whether the parameter is an XML document parameter.
        /// Corresponds to the sys.parameters.[is_xml_document] column.
        /// </summary>
        public bool IsXmlDocument => _isXmlDocument;

        /// <summary>
        /// Default value for the parameter (catalog shows this as sql_variant).
        /// Corresponds to the sys.parameters.[default_value] column.
        /// </summary>
        public object? DefaultValue => _defaultValue;

        /// <summary>
        /// ID of the xml collection (if parameter is xml typed).
        /// Corresponds to the sys.parameters.[xml_collection_id] column.
        /// </summary>
        public int? XmlCollectionId => _xmlCollectionId;

        /// <summary>
        /// Indicates whether the parameter is read-only.
        /// Corresponds to the sys.parameters.[is_readonly] column.
        /// </summary>
        public bool IsReadOnly => _isReadOnly;

        /// <summary>
        /// Indicates whether the parameter is nullable.
        /// Corresponds to the sys.parameters.[is_nullable] column.
        /// </summary>
        public bool IsNullable => _isNullable;

        /// <summary>
        /// Encryption type for a parameter used with Always Encrypted.
        /// Corresponds to the sys.parameters.[encryption_type] column.
        /// </summary>
        public int? EncryptionType => _encryptionType;

        /// <summary>
        /// Description of the encryption type.
        /// Corresponds to the sys.parameters.[encryption_type_desc] column.
        /// </summary>
        public string? EncryptionTypeDesc => _encryptionTypeDesc;

        /// <summary>
        /// Name of the encryption algorithm used for Always Encrypted.
        /// Corresponds to the sys.parameters.[encryption_algorithm_name] column.
        /// </summary>
        public string? EncryptionAlgorithmName => _encryptionAlgorithmName;

        /// <summary>
        /// ID of the column encryption key used for Always Encrypted.
        /// Corresponds to the sys.parameters.[column_encryption_key_id] column.
        /// </summary>
        public int? ColumnEncryptionKeyId => _columnEncryptionKeyId;

        /// <summary>
        /// Database name that contains the column encryption key.
        /// Corresponds to the sys.parameters.[column_encryption_key_database_name] column.
        /// </summary>
        public string? ColumnEncryptionKeyDatabaseName => _columnEncryptionKeyDatabaseName;

        public Parameter(
            int objectId,
            string name,
            int parameterId,
            sbyte systemTypeId,
            int userTypeId,
            short maxLength,
            sbyte precision,
            sbyte scale,
            bool isOutput,
            bool isCursorRef,
            bool hasDefaultValue,
            bool isXmlDocument,
            object? defaultValue,
            int? xmlCollectionId,
            bool isReadOnly,
            bool isNullable,
            int? encryptionType,
            string? encryptionTypeDesc,
            string? encryptionAlgorithmName,
            int? columnEncryptionKeyId,
            string? columnEncryptionKeyDatabaseName)
        {
            _objectId = objectId;
            _name = name ?? throw new ArgumentNullException(nameof(name));
            _parameterId = parameterId;
            _systemTypeId = systemTypeId;
            _userTypeId = userTypeId;
            _maxLength = maxLength;
            _precision = precision;
            _scale = scale;
            _isOutput = isOutput;
            _isCursorRef = isCursorRef;
            _hasDefaultValue = hasDefaultValue;
            _isXmlDocument = isXmlDocument;
            _defaultValue = defaultValue;
            _xmlCollectionId = xmlCollectionId;
            _isReadOnly = isReadOnly;
            _isNullable = isNullable;
            _encryptionType = encryptionType;
            _encryptionTypeDesc = encryptionTypeDesc;
            _encryptionAlgorithmName = encryptionAlgorithmName;
            _columnEncryptionKeyId = columnEncryptionKeyId;
            _columnEncryptionKeyDatabaseName = columnEncryptionKeyDatabaseName;
        }
    }
}
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

using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{
    public class MaskedColumnsReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT mc.[object_id]
                  ,mc.[name]
                  ,mc.[column_id]
                  ,mc.[system_type_id]
                  ,mc.[user_type_id]
                  ,mc.[max_length]
                  ,mc.[precision]
                  ,mc.[scale]
                  ,mc.[collation_name]
                  ,mc.[is_nullable]
                  ,mc.[is_ansi_padded]
                  ,mc.[is_rowguidcol]
                  ,mc.[is_identity]
                  ,mc.[is_filestream]
                  ,mc.[is_replicated]
                  ,mc.[is_non_sql_subscribed]
                  ,mc.[is_merge_published]
                  ,mc.[is_dts_replicated]
                  ,mc.[is_xml_document]
                  ,mc.[xml_collection_id]
                  ,mc.[default_object_id]
                  ,mc.[rule_object_id]
                  ,mc.[definition]
                  ,mc.[uses_database_collation]
                  ,mc.[is_persisted]
                  ,mc.[is_computed]
                  ,mc.[is_sparse]
                  ,mc.[is_column_set]
                  ,mc.[generated_always_type]
                  ,mc.[generated_always_type_desc]
                  ,mc.[encryption_type]
                  ,mc.[encryption_type_desc]
                  ,mc.[encryption_algorithm_name]
                  ,mc.[column_encryption_key_id]
                  ,mc.[column_encryption_key_database_name]
                  ,mc.[is_hidden]
                  ,mc.[is_masked]
                  ,mc.[masking_function]
                  ,mc.[graph_type]
                  ,mc.[graph_type_desc]
            FROM [sys].[masked_columns] mc
            """;

        public const int ObjectIdOrdinal = 0;
        public const int NameOrdinal = 1;
        public const int ColumnIdOrdinal = 2;
        public const int SystemTypeIdOrdinal = 3;
        public const int UserTypeIdOrdinal = 4;
        public const int MaxLengthOrdinal = 5;
        public const int PrecisionOrdinal = 6;
        public const int ScaleOrdinal = 7;
        public const int CollationNameOrdinal = 8;
        public const int IsNullableOrdinal = 9;
        public const int IsAnsiPaddedOrdinal = 10;
        public const int IsRowguidcolOrdinal = 11;
        public const int IsIdentityOrdinal = 12;
        public const int IsFilestreamOrdinal = 13;
        public const int IsReplicatedOrdinal = 14;
        public const int IsNonSqlSubscribedOrdinal = 15;
        public const int IsMergePublishedOrdinal = 16;
        public const int IsDtsReplicatedOrdinal = 17;
        public const int IsXmlDocumentOrdinal = 18;
        public const int XmlCollectionIdOrdinal = 19;
        public const int DefaultObjectIdOrdinal = 20;
        public const int RuleObjectIdOrdinal = 21;
        public const int DefinitionOrdinal = 22;
        public const int UsesDatabaseCollationOrdinal = 23;
        public const int IsPersistedOrdinal = 24;
        public const int IsComputedOrdinal = 25;
        public const int IsSparseOrdinal = 26;
        public const int IsColumnSetOrdinal = 27;
        public const int GeneratedAlwaysTypeOrdinal = 28;
        public const int GeneratedAlwaysTypeDescOrdinal = 29;
        public const int EncryptionTypeOrdinal = 30;
        public const int EncryptionTypeDescOrdinal = 31;
        public const int EncryptionAlgorithmNameOrdinal = 32;
        public const int ColumnEncryptionKeyIdOrdinal = 33;
        public const int ColumnEncryptionKeyDatabaseNameOrdinal = 34;
        public const int IsHiddenOrdinal = 35;
        public const int IsMaskedOrdinal = 36;
        public const int MaskingFunctionOrdinal = 37;
        public const int GraphTypeOrdinal = 38;
        public const int GraphTypeDescOrdinal = 39;

        public MaskedColumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public MaskedColumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public MaskedColumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        /// <summary>
        /// ID of the object that contains the column. (sys.masked_columns.object_id)
        /// </summary>
        public int GetObjectId()
        {
            return base.GetInt32(ObjectIdOrdinal);
        }

        /// <summary>
        /// Name of the column. (sys.masked_columns.name)
        /// </summary>
        public string GetName()
        {
            return base.GetString(NameOrdinal);
        }

        /// <summary>
        /// ID of the column within the object. (sys.masked_columns.column_id)
        /// </summary>
        public int GetColumnId()
        {
            return base.GetInt32(ColumnIdOrdinal);
        }

        /// <summary>
        /// System-supplied type ID for the column. (sys.masked_columns.system_type_id)
        /// </summary>
        public sbyte GetSystemTypeId()
        {
            return base.GetSByte(SystemTypeIdOrdinal);
        }

        /// <summary>
        /// User-defined type ID for the column. (sys.masked_columns.user_type_id)
        /// </summary>
        public int GetUserTypeId()
        {
            return base.GetInt32(UserTypeIdOrdinal);
        }

        /// <summary>
        /// Maximum length, in bytes, of the column. (sys.masked_columns.max_length)
        /// </summary>
        public short GetMaxLength()
        {
            return base.GetInt16(MaxLengthOrdinal);
        }

        /// <summary>
        /// Precision of the column (for numeric types). (sys.masked_columns.precision)
        /// </summary>
        public sbyte GetPrecision()
        {
            return base.GetSByte(PrecisionOrdinal);
        }

        /// <summary>
        /// Scale of the column (for numeric types). (sys.masked_columns.scale)
        /// </summary>
        public sbyte GetScale()
        {
            return base.GetSByte(ScaleOrdinal);
        }

        /// <summary>
        /// Collation name for the column, if applicable. (sys.masked_columns.collation_name)
        /// </summary>
        public string? GetCollationName()
        {
            return base.GetNullableString(CollationNameOrdinal);
        }

        /// <summary>
        /// Indicates whether the column allows NULL. (sys.masked_columns.is_nullable)
        /// </summary>
        public bool GetIsNullable()
        {
            return base.GetBoolean(IsNullableOrdinal);
        }

        /// <summary>
        /// Indicates whether values in the column are padded with spaces. (sys.masked_columns.is_ansi_padded)
        /// </summary>
        public bool GetIsAnsiPadded()
        {
            return base.GetBoolean(IsAnsiPaddedOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is a ROWGUIDCOL. (sys.masked_columns.is_rowguidcol)
        /// </summary>
        public bool GetIsRowguidcol()
        {
            return base.GetBoolean(IsRowguidcolOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is an identity column. (sys.masked_columns.is_identity)
        /// </summary>
        public bool GetIsIdentity()
        {
            return base.GetBoolean(IsIdentityOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is a FILESTREAM column. (sys.masked_columns.is_filestream)
        /// </summary>
        public bool GetIsFilestream()
        {
            return base.GetBoolean(IsFilestreamOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is replicated. (sys.masked_columns.is_replicated)
        /// </summary>
        public bool GetIsReplicated()
        {
            return base.GetBoolean(IsReplicatedOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is non-SQL-subscriber replicated. (sys.masked_columns.is_non_sql_subscribed)
        /// </summary>
        public bool GetIsNonSqlSubscribed()
        {
            return base.GetBoolean(IsNonSqlSubscribedOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is published by merge replication. (sys.masked_columns.is_merge_published)
        /// </summary>
        public bool GetIsMergePublished()
        {
            return base.GetBoolean(IsMergePublishedOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is DTS replicated. (sys.masked_columns.is_dts_replicated)
        /// </summary>
        public bool GetIsDtsReplicated()
        {
            return base.GetBoolean(IsDtsReplicatedOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is an XML document type. (sys.masked_columns.is_xml_document)
        /// </summary>
        public bool GetIsXmlDocument()
        {
            return base.GetBoolean(IsXmlDocumentOrdinal);
        }

        /// <summary>
        /// ID of the XML collection if the column is xml typed. (sys.masked_columns.xml_collection_id)
        /// </summary>
        public int? GetXmlCollectionId()
        {
            return base.GetNullableInt32(XmlCollectionIdOrdinal);
        }

        /// <summary>
        /// ID of the default object (if any). (sys.masked_columns.default_object_id)
        /// </summary>
        public int? GetDefaultObjectId()
        {
            return base.GetNullableInt32(DefaultObjectIdOrdinal);
        }

        /// <summary>
        /// ID of the rule object (if any). (sys.masked_columns.rule_object_id)
        /// </summary>
        public int? GetRuleObjectId()
        {
            return base.GetNullableInt32(RuleObjectIdOrdinal);
        }

        /// <summary>
        /// Column definition text (for computed/expressed columns). (sys.masked_columns.definition)
        /// </summary>
        public string? GetDefinition()
        {
            return base.GetNullableString(DefinitionOrdinal);
        }

        /// <summary>
        /// Indicates whether the column uses the database collation. (sys.masked_columns.uses_database_collation)
        /// </summary>
        public bool GetUsesDatabaseCollation()
        {
            return base.GetBoolean(UsesDatabaseCollationOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is persisted. (sys.masked_columns.is_persisted)
        /// </summary>
        public bool GetIsPersisted()
        {
            return base.GetBoolean(IsPersistedOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is computed. (sys.masked_columns.is_computed)
        /// </summary>
        public bool GetIsComputed()
        {
            return base.GetBoolean(IsComputedOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is sparse. (sys.masked_columns.is_sparse)
        /// </summary>
        public bool GetIsSparse()
        {
            return base.GetBoolean(IsSparseOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is a column set. (sys.masked_columns.is_column_set)
        /// </summary>
        public bool GetIsColumnSet()
        {
            return base.GetBoolean(IsColumnSetOrdinal);
        }

        /// <summary>
        /// Generated-always type value for the column. (sys.masked_columns.generated_always_type)
        /// </summary>
        public sbyte GetGeneratedAlwaysType()
        {
            return base.GetSByte(GeneratedAlwaysTypeOrdinal);
        }

        /// <summary>
        /// Description of the generated-always type. (sys.masked_columns.generated_always_type_desc)
        /// </summary>
        public string? GetGeneratedAlwaysTypeDesc()
        {
            return base.GetNullableString(GeneratedAlwaysTypeDescOrdinal);
        }

        /// <summary>
        /// Encryption type for Always Encrypted. (sys.masked_columns.encryption_type)
        /// </summary>
        public int? GetEncryptionType()
        {
            return base.GetNullableInt32(EncryptionTypeOrdinal);
        }

        /// <summary>
        /// Description of the encryption type. (sys.masked_columns.encryption_type_desc)
        /// </summary>
        public string? GetEncryptionTypeDesc()
        {
            return base.GetNullableString(EncryptionTypeDescOrdinal);
        }

        /// <summary>
        /// Name of the encryption algorithm used. (sys.masked_columns.encryption_algorithm_name)
        /// </summary>
        public string? GetEncryptionAlgorithmName()
        {
            return base.GetNullableString(EncryptionAlgorithmNameOrdinal);
        }

        /// <summary>
        /// Column encryption key id for Always Encrypted. (sys.masked_columns.column_encryption_key_id)
        /// </summary>
        public int? GetColumnEncryptionKeyId()
        {
            return base.GetNullableInt32(ColumnEncryptionKeyIdOrdinal);
        }

        /// <summary>
        /// Database name that contains the column encryption key. (sys.masked_columns.column_encryption_key_database_name)
        /// </summary>
        public string? GetColumnEncryptionKeyDatabaseName()
        {
            return base.GetNullableString(ColumnEncryptionKeyDatabaseNameOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is hidden. (sys.masked_columns.is_hidden)
        /// </summary>
        public bool GetIsHidden()
        {
            return base.GetBoolean(IsHiddenOrdinal);
        }

        /// <summary>
        /// Indicates whether the column is masked. (sys.masked_columns.is_masked)
        /// </summary>
        public bool GetIsMasked()
        {
            return base.GetBoolean(IsMaskedOrdinal);
        }

        /// <summary>
        /// Masking function applied to the column, if any. (sys.masked_columns.masking_function)
        /// </summary>
        public string? GetMaskingFunction()
        {
            return base.GetNullableString(MaskingFunctionOrdinal);
        }

        /// <summary>
        /// Graph type code for the column, if any. (sys.masked_columns.graph_type)
        /// </summary>
        public int? GetGraphType()
        {
            return base.GetNullableInt32(GraphTypeOrdinal);
        }

        /// <summary>
        /// Description of the graph type for the column. (sys.masked_columns.graph_type_desc)
        /// </summary>
        public string? GetGraphTypeDesc()
        {
            return base.GetNullableString(GraphTypeDescOrdinal);
        }

        public Types.MaskedColumn GetMaskedColumn()
        {
            var objectId = GetObjectId();
            var name = GetName();
            var columnId = GetColumnId();
            var systemTypeId = GetSystemTypeId();
            var userTypeId = GetUserTypeId();
            var maxLength = GetMaxLength();
            var precision = GetPrecision();
            var scale = GetScale();
            var collationName = GetCollationName();
            var isNullable = GetIsNullable();
            var isAnsiPadded = GetIsAnsiPadded();
            var isRowguidcol = GetIsRowguidcol();
            var isIdentity = GetIsIdentity();
            var isFilestream = GetIsFilestream();
            var isReplicated = GetIsReplicated();
            var isNonSqlSubscribed = GetIsNonSqlSubscribed();
            var isMergePublished = GetIsMergePublished();
            var isDtsReplicated = GetIsDtsReplicated();
            var isXmlDocument = GetIsXmlDocument();
            var xmlCollectionId = GetXmlCollectionId();
            var defaultObjectId = GetDefaultObjectId();
            var ruleObjectId = GetRuleObjectId();
            var definition = GetDefinition();
            var usesDatabaseCollation = GetUsesDatabaseCollation();
            var isPersisted = GetIsPersisted();
            var isComputed = GetIsComputed();
            var isSparse = GetIsSparse();
            var isColumnSet = GetIsColumnSet();
            var generatedAlwaysType = GetGeneratedAlwaysType();
            var generatedAlwaysTypeDesc = GetGeneratedAlwaysTypeDesc();
            var encryptionType = GetEncryptionType();
            var encryptionTypeDesc = GetEncryptionTypeDesc();
            var encryptionAlgorithmName = GetEncryptionAlgorithmName();
            var columnEncryptionKeyId = GetColumnEncryptionKeyId();
            var columnEncryptionKeyDatabaseName = GetColumnEncryptionKeyDatabaseName();
            var isHidden = GetIsHidden();
            var isMasked = GetIsMasked();
            var maskingFunction = GetMaskingFunction();
            var graphType = GetGraphType();
            var graphTypeDesc = GetGraphTypeDesc();

            return new Types.MaskedColumn(
                objectId,
                name,
                columnId,
                systemTypeId,
                userTypeId,
                maxLength,
                precision,
                scale,
                collationName,
                isNullable,
                isAnsiPadded,
                isRowguidcol,
                isIdentity,
                isFilestream,
                isReplicated,
                isNonSqlSubscribed,
                isMergePublished,
                isDtsReplicated,
                isXmlDocument,
                xmlCollectionId,
                defaultObjectId,
                ruleObjectId,
                definition,
                usesDatabaseCollation,
                isPersisted,
                isComputed,
                isSparse,
                isColumnSet,
                generatedAlwaysType,
                generatedAlwaysTypeDesc,
                encryptionType,
                encryptionTypeDesc,
                encryptionAlgorithmName,
                columnEncryptionKeyId,
                columnEncryptionKeyDatabaseName,
                isHidden,
                isMasked,
                maskingFunction,
                graphType,
                graphTypeDesc);
        }

        public IReadOnlyList<Types.MaskedColumn> GetMaskedColumns()
        {
            var list = new List<Types.MaskedColumn>();
            while (Read())
            {
                list.Add(GetMaskedColumn());
            }
            return list;
        }
    }
}
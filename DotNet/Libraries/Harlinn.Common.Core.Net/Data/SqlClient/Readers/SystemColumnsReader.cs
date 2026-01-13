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
using System.Diagnostics.CodeAnalysis;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{
    public class SystemColumnsReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT ssc.[object_id]
                ,ssc.[name]
                ,ssc.[column_id]
                ,ssc.[system_type_id]
                ,ssc.[user_type_id]
                ,ssc.[max_length]
                ,ssc.[precision]
                ,ssc.[scale]
                ,ssc.[collation_name]
                ,ssc.[is_nullable]
                ,ssc.[is_ansi_padded]
                ,ssc.[is_rowguidcol]
                ,ssc.[is_identity]
                ,ssc.[is_computed]
                ,ssc.[is_filestream]
                ,ssc.[is_replicated]
                ,ssc.[is_non_sql_subscribed]
                ,ssc.[is_merge_published]
                ,ssc.[is_dts_replicated]
                ,ssc.[is_xml_document]
                ,ssc.[xml_collection_id]
                ,ssc.[default_object_id]
                ,ssc.[rule_object_id]
                ,ssc.[is_sparse]
                ,ssc.[is_column_set]
                ,ssc.[generated_always_type]
                ,ssc.[generated_always_type_desc]
                ,ssc.[encryption_type]
                ,ssc.[encryption_type_desc]
                ,ssc.[encryption_algorithm_name]
                ,ssc.[column_encryption_key_id]
                ,ssc.[column_encryption_key_database_name]
                ,ssc.[is_hidden]
                ,ssc.[is_masked]
                ,ssc.[graph_type]
                ,ssc.[graph_type_desc]
                ,t.[name] AS TypeName
            FROM [sys].[system_columns] ssc
            INNER JOIN sys.types t ON ssc.user_type_id = t.user_type_id
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
        public const int IsComputedOrdinal = 13;
        public const int IsFilestreamOrdinal = 14;
        public const int IsReplicatedOrdinal = 15;
        public const int IsNonSqlSubscribedOrdinal = 16;
        public const int IsMergePublishedOrdinal = 17;
        public const int IsDtsReplicatedOrdinal = 18;
        public const int IsXmlDocumentOrdinal = 19;
        public const int XmlCollectionIdOrdinal = 20;
        public const int DefaultObjectIdOrdinal = 21;
        public const int RuleObjectIdOrdinal = 22;
        public const int IsSparseOrdinal = 23;
        public const int IsColumnSetOrdinal = 24;
        public const int GeneratedAlwaysTypeOrdinal = 25;
        public const int GeneratedAlwaysTypeDescOrdinal = 26;
        public const int EncryptionTypeOrdinal = 27;
        public const int EncryptionTypeDescOrdinal = 28;
        public const int EncryptionAlgorithmNameOrdinal = 29;
        public const int ColumnEncryptionKeyIdOrdinal = 30;
        public const int ColumnEncryptionKeyDatabaseNameOrdinal = 31;
        public const int IsHiddenOrdinal = 32;
        public const int IsMaskedOrdinal = 33;
        public const int GraphTypeOrdinal = 34;
        public const int GraphTypeDescOrdinal = 35;
        public const int TypeNameOrdinal = 36;

        public SystemColumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public SystemColumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public SystemColumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        public int GetObjectId()
        {
            return base.GetInt32(ObjectIdOrdinal);
        }

        public string GetName()
        {
            return base.GetString(NameOrdinal);
        }

        public int GetColumnId()
        {
            return base.GetInt32(ColumnIdOrdinal);
        }

        public byte GetSystemTypeId()
        {
            return base.GetByte(SystemTypeIdOrdinal);
        }

        public int GetUserTypeId()
        {
            return base.GetInt32(UserTypeIdOrdinal);
        }

        public short GetMaxLength()
        {
            return base.GetInt16(MaxLengthOrdinal);
        }

        public byte GetPrecision()
        {
            return base.GetByte(PrecisionOrdinal);
        }

        public byte GetScale()
        {
            return base.GetByte(ScaleOrdinal);
        }

        public string? GetCollationName()
        {
            return base.GetNullableString(CollationNameOrdinal);
        }

        public bool GetIsNullable()
        {
            return base.GetBoolean(IsNullableOrdinal);
        }

        public bool GetIsAnsiPadded()
        {
            return base.GetBoolean(IsAnsiPaddedOrdinal);
        }

        public bool GetIsRowguidcol()
        {
            return base.GetBoolean(IsRowguidcolOrdinal);
        }

        public bool GetIsIdentity()
        {
            return base.GetBoolean(IsIdentityOrdinal);
        }

        public bool GetIsComputed()
        {
            return base.GetBoolean(IsComputedOrdinal);
        }
        public bool GetIsFilestream()
        {
            return base.GetBoolean(IsFilestreamOrdinal);
        }

        public bool GetIsReplicated()
        {
            return base.GetBoolean(IsReplicatedOrdinal);
        }

        public bool GetIsNonSqlSubscribed()
        {
            return base.GetBoolean(IsNonSqlSubscribedOrdinal);
        }

        public bool GetIsMergePublished()
        {
            return base.GetBoolean(IsMergePublishedOrdinal);
        }

        public bool GetIsDtsReplicated()
        {
            return base.GetBoolean(IsDtsReplicatedOrdinal);
        }

        public bool GetIsXmlDocument()
        {
            return base.GetBoolean(IsXmlDocumentOrdinal);
        }

        public int GetXmlCollectionId()
        {
            return base.GetInt32(XmlCollectionIdOrdinal);
        }

        public int GetDefaultObjectId()
        {
            return base.GetInt32(DefaultObjectIdOrdinal);
        }

        public int GetRuleObjectId()
        {
            return base.GetInt32(RuleObjectIdOrdinal);
        }


        public bool GetIsSparse()
        {
            return base.GetBoolean(IsSparseOrdinal);
        }

        public bool GetIsColumnSet()
        {
            return base.GetBoolean(IsColumnSetOrdinal);
        }

        public byte GetGeneratedAlwaysType()
        {
            return base.GetByte(GeneratedAlwaysTypeOrdinal);
        }

        public string GetGeneratedAlwaysTypeDesc()
        {
            return base.GetString(GeneratedAlwaysTypeDescOrdinal);
        }

        public int? GetEncryptionType()
        {
            return base.GetNullableInt32(EncryptionTypeOrdinal);
        }

        public string? GetEncryptionTypeDesc()
        {
            return base.GetNullableString(EncryptionTypeDescOrdinal);
        }

        public string? GetEncryptionAlgorithmName()
        {
            return base.GetNullableString(EncryptionAlgorithmNameOrdinal);
        }

        public int? GetColumnEncryptionKeyId()
        {
            return base.GetNullableInt32(ColumnEncryptionKeyIdOrdinal);
        }

        public string? GetColumnEncryptionKeyDatabaseName()
        {
            return base.GetNullableString(ColumnEncryptionKeyDatabaseNameOrdinal);
        }

        public bool GetIsHidden()
        {
            return base.GetBoolean(IsHiddenOrdinal);
        }

        public bool GetIsMasked()
        {
            return base.GetBoolean(IsMaskedOrdinal);
        }

        public int? GetGraphType()
        {
            return base.GetNullableInt32(GraphTypeOrdinal);
        }

        public string? GetGraphTypeDesc()
        {
            return base.GetNullableString(GraphTypeDescOrdinal);
        }

        public string GetTypeName()
        {
            return base.GetString(TypeNameOrdinal);
        }

        public Types.Column GetColumn()
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
            var isComputed = GetIsComputed();
            var isFilestream = GetIsFilestream();
            var isReplicated = GetIsReplicated();
            var isNonSqlSubscribed = GetIsNonSqlSubscribed();
            var isMergePublished = GetIsMergePublished();
            var isDtsReplicated = GetIsDtsReplicated();
            var isXmlDocument = GetIsXmlDocument();
            var xmlCollectionId = GetXmlCollectionId();
            var defaultObjectId = GetDefaultObjectId();
            var ruleObjectId = GetRuleObjectId();
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
            var graphType = GetGraphType();
            var graphTypeDesc = GetGraphTypeDesc();
            var typeName = GetTypeName();
            return new Types.Column(objectId, name, columnId, systemTypeId, userTypeId, maxLength, precision, scale, collationName, isNullable, isAnsiPadded, isRowguidcol, isIdentity, isComputed, isFilestream, isReplicated, isNonSqlSubscribed, isMergePublished, isDtsReplicated, isXmlDocument, xmlCollectionId, defaultObjectId, ruleObjectId, isSparse, isColumnSet, generatedAlwaysType, generatedAlwaysTypeDesc, encryptionType, encryptionTypeDesc, encryptionAlgorithmName, columnEncryptionKeyId, columnEncryptionKeyDatabaseName, isHidden, isMasked, graphType, graphTypeDesc, typeName);
        }

        public IReadOnlyList<Types.Column> GetColumns()
        {
            var columns = new List<Types.Column>();
            while (Read())
            {
                columns.Add(GetColumn());
            }
            return columns;
        }

    }

}

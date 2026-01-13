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
    public class ParametersReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT par.[object_id]
                  ,par.[name]
                  ,par.[parameter_id]
                  ,par.[system_type_id]
                  ,par.[user_type_id]
                  ,par.[max_length]
                  ,par.[precision]
                  ,par.[scale]
                  ,par.[is_output]
                  ,par.[is_cursor_ref]
                  ,par.[has_default_value]
                  ,par.[is_xml_document]
                  ,par.[default_value]
                  ,par.[xml_collection_id]
                  ,par.[is_readonly]
                  ,par.[is_nullable]
                  ,par.[encryption_type]
                  ,par.[encryption_type_desc]
                  ,par.[encryption_algorithm_name]
                  ,par.[column_encryption_key_id]
                  ,par.[column_encryption_key_database_name]
                  ,t.[name] AS [type_name]
              FROM [sys].[parameters] par
              LEFT JOIN sys.types t ON par.user_type_id = t.user_type_id
            """;

        public const int ObjectIdOrdinal = 0;
        public const int NameOrdinal = 1;
        public const int ParameterIdOrdinal = 2;
        public const int SystemTypeIdOrdinal = 3;
        public const int UserTypeIdOrdinal = 4;
        public const int MaxLengthOrdinal = 5;
        public const int PrecisionOrdinal = 6;
        public const int ScaleOrdinal = 7;
        public const int IsOutputOrdinal = 8;
        public const int IsCursorRefOrdinal = 9;
        public const int HasDefaultValueOrdinal = 10;
        public const int IsXmlDocumentOrdinal = 11;
        public const int DefaultValueOrdinal = 12;
        public const int XmlCollectionIdOrdinal = 13;
        public const int IsReadOnlyOrdinal = 14;
        public const int IsNullableOrdinal = 15;
        public const int EncryptionTypeOrdinal = 16;
        public const int EncryptionTypeDescOrdinal = 17;
        public const int EncryptionAlgorithmNameOrdinal = 18;
        public const int ColumnEncryptionKeyIdOrdinal = 19;
        public const int ColumnEncryptionKeyDatabaseNameOrdinal = 20;
        public const int TypeNameOrdinal = 21;

        public ParametersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public ParametersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public ParametersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

        public int GetParameterId()
        {
            return base.GetInt32(ParameterIdOrdinal);
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

        public bool GetIsOutput()
        {
            return base.GetBoolean(IsOutputOrdinal);
        }

        public bool GetIsCursorRef()
        {
            return base.GetBoolean(IsCursorRefOrdinal);
        }

        public bool GetHasDefaultValue()
        {
            return base.GetBoolean(HasDefaultValueOrdinal);
        }

        public bool GetIsXmlDocument()
        {
            return base.GetBoolean(IsXmlDocumentOrdinal);
        }

        public string? GetDefaultValue()
        {
            return base.GetNullableString(DefaultValueOrdinal);
        }

        public int? GetXmlCollectionId()
        {
            return base.GetNullableInt32(XmlCollectionIdOrdinal);
        }

        public bool GetIsReadOnly()
        {
            return base.GetBoolean(IsReadOnlyOrdinal);
        }

        public bool GetIsNullable()
        {
            return base.GetBoolean(IsNullableOrdinal);
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

        public string? GetTypeName()
        {
            return base.GetNullableString(TypeNameOrdinal);
        }

        public Types.Parameter GetParameter()
        {
            return new Types.Parameter(
                GetObjectId(),
                GetName(),
                GetParameterId(),
                GetSystemTypeId(),
                GetUserTypeId(),
                GetMaxLength(),
                GetPrecision(),
                GetScale(),
                GetIsOutput(),
                GetIsCursorRef(),
                GetHasDefaultValue(),
                GetIsXmlDocument(),
                GetDefaultValue(),
                GetXmlCollectionId(),
                GetIsReadOnly(),
                GetIsNullable(),
                GetEncryptionType(),
                GetEncryptionTypeDesc(),
                GetEncryptionAlgorithmName(),
                GetColumnEncryptionKeyId(),
                GetColumnEncryptionKeyDatabaseName(),
                GetTypeName()
            );
        }

        public IReadOnlyList<Types.Parameter> GetParameters()
        {
            var list = new List<Types.Parameter>();
            while (Read())
            {
                list.Add(GetParameter());
            }
            return list;
        }
    }
}
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

using Harlinn.Common.Core.Net.Data.SqlClient.Types;
using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{
    public class TableTypesReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT st.[name]
                ,stt.[system_type_id]
                ,stt.[user_type_id]
                ,stt.[schema_id]
                ,stt.[principal_id]
                ,stt.[max_length]
                ,stt.[precision]
                ,stt.[scale]
                ,stt.[collation_name]
                ,stt.[is_nullable]
                ,stt.[is_user_defined]
                ,stt.[is_assembly_type]
                ,stt.[default_object_id]
                ,stt.[rule_object_id]
                ,stt.[is_table_type]
                ,stt.[type_table_object_id]
                ,stt.[is_memory_optimized]
            FROM [sys].[table_types] stt
            """;

        public const int NameOrdinal = 0;
        public const int SystemTypeIdOrdinal = 1;
        public const int UserTypeIdOrdinal = 2;
        public const int SchemaIdOrdinal = 3;
        public const int PrincipalIdOrdinal = 4;
        public const int MaxLengthOrdinal = 5;
        public const int PrecisionOrdinal = 6;
        public const int ScaleOrdinal = 7;
        public const int CollationNameOrdinal = 8;
        public const int IsNullableOrdinal = 9;
        public const int IsUserDefinedOrdinal = 10;
        public const int IsAssemblyTypeOrdinal = 11;
        public const int DefaultObjectIdOrdinal = 12;
        public const int RuleObjectIdOrdinal = 13;
        public const int IsTableTypeOrdinal = 14;
        public const int TypeTableObjectIdOrdinal = 15;
        public const int IsMemoryOptimizedOrdinal = 16;

        public TableTypesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public TableTypesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public TableTypesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }


        /// <summary>
        /// Retrieves the name of the type.
        /// </summary>
        /// <returns>
        /// The database type name as a non-null <see cref="string"/>.
        /// </returns>
        public string GetName()
        {
            return GetString(NameOrdinal);
        }

        /// <summary>
        /// Retrieves the system type ID.
        /// </summary>
        public byte GetSystemTypeId()
        {
            return GetByte(SystemTypeIdOrdinal);
        }

        /// <summary>
        /// Retrieves the ID of the type. Is unique within the database.
        /// </summary>
        public int GetUserTypeId()
        {
            return GetInt32(UserTypeIdOrdinal);
        }

        /// <summary>
        /// Retrieves ID of the schema to which the type belongs.
        /// </summary>
        public int GetSchemaId()
        {
            return GetInt32(SchemaIdOrdinal);
        }

        /// <summary>
        /// ID of the individual owner if different from schema owner. By default, 
        /// schema-contained objects are owned by the schema owner. However, an 
        /// alternate owner can be specified by using the ALTER AUTHORIZATION 
        /// statement to change ownership.
        /// 
        /// NULL if there is no alternate individual owner.
        /// </summary>
        public int? GetPrincipalId()
        {
            return GetNullableInt32(PrincipalIdOrdinal);
        }

        public short GetMaxLength()
        {
            return GetInt16(MaxLengthOrdinal);
        }

        public byte GetPrecision()
        {
            return GetByte(PrecisionOrdinal);
        }

        public byte GetScale()
        {
            return GetByte(ScaleOrdinal);
        }

        public string? GetCollationName()
        {
            if (IsDBNull(CollationNameOrdinal))
            {
                return null;
            }
            return GetString(CollationNameOrdinal);
        }

        public bool GetIsNullable()
        {
            return GetBoolean(IsNullableOrdinal);
        }

        public bool GetIsUserDefined()
        {
            return GetBoolean(IsUserDefinedOrdinal);
        }

        public bool GetIsAssemblyType()
        {
            return GetBoolean(IsAssemblyTypeOrdinal);
        }

        public int GetDefaultObjectId()
        {
            return GetInt32(DefaultObjectIdOrdinal);
        }

        public int GetRuleObjectId()
        {
            return GetInt32(RuleObjectIdOrdinal);
        }

        public bool GetIsTableType()
        {
            return GetBoolean(IsTableTypeOrdinal);
        }

        public int GetTypeTableObjectId()
        {
            return GetInt32(TypeTableObjectIdOrdinal);
        }

        public bool GetIsMemoryOptimized()
        {
            return GetBoolean(IsMemoryOptimizedOrdinal);
        }

        public TableType GetTableType( )
        {
            var name = GetName();
            var systemTypeId = GetSystemTypeId();
            var userTypeId = GetUserTypeId();
            var schemaId = GetSchemaId();
            var principalId = GetPrincipalId();
            var maxLength = GetMaxLength();
            var precision = GetPrecision();
            var scale = GetScale();
            var collationName = GetCollationName();
            var isNullable = GetIsNullable();
            var isUserDefined = GetIsUserDefined();
            var isAssemblyType = GetIsAssemblyType();
            var defaultObjectId = GetDefaultObjectId();
            var ruleObjectId = GetRuleObjectId();
            var isTableType = GetIsTableType();
            var typeTableObjectId = GetTypeTableObjectId();
            var isMemoryOptimized = GetIsMemoryOptimized();
            return new TableType(name, systemTypeId, userTypeId, schemaId, principalId, maxLength, precision, scale, collationName, isNullable, isUserDefined, isAssemblyType, defaultObjectId, ruleObjectId, isTableType, typeTableObjectId, isMemoryOptimized);
        }

        public IReadOnlyList<TableType> ToList()
        {
            var list = new List<TableType>();
            while (Read())
            {
                list.Add(GetTableType());
            }
            return list;
        }
    }


}

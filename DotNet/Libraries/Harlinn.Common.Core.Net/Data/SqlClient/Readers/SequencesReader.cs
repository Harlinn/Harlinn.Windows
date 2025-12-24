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

using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using Harlinn.Common.Core.Net.Data.SqlClient.Types;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{
    public class SequencesReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT s.[name]
                  ,s.[object_id]
                  ,s.[principal_id]
                  ,s.[schema_id]
                  ,s.[parent_object_id]
                  ,s.[type]
                  ,s.[type_desc]
                  ,s.[create_date]
                  ,s.[modify_date]
                  ,s.[is_ms_shipped]
                  ,s.[is_published]
                  ,s.[is_schema_published]
                  ,s.[start_value]
                  ,s.[increment]
                  ,s.[minimum_value]
                  ,s.[maximum_value]
                  ,s.[is_cycling]
                  ,s.[is_cached]
                  ,s.[cache_size]
                  ,s.[system_type_id]
                  ,s.[user_type_id]
                  ,s.[precision]
                  ,s.[scale]
                  ,s.[current_value]
                  ,s.[is_exhausted]
                  ,s.[last_used_value]
              FROM [sys].[sequences] s
            """;

        public const int NameOrdinal = 0;
        public const int ObjectIdOrdinal = 1;
        public const int PrincipalIdOrdinal = 2;
        public const int SchemaIdOrdinal = 3;
        public const int ParentObjectIdOrdinal = 4;
        public const int TypeOrdinal = 5;
        public const int TypeDescOrdinal = 6;
        public const int CreateDateOrdinal = 7;
        public const int ModifyDateOrdinal = 8;
        public const int IsMsShippedOrdinal = 9;
        public const int IsPublishedOrdinal = 10;
        public const int IsSchemaPublishedOrdinal = 11;
        public const int StartValueOrdinal = 12;
        public const int IncrementOrdinal = 13;
        public const int MinimumValueOrdinal = 14;
        public const int MaximumValueOrdinal = 15;
        public const int IsCyclingOrdinal = 16;
        public const int IsCachedOrdinal = 17;
        public const int CacheSizeOrdinal = 18;
        public const int SystemTypeIdOrdinal = 19;
        public const int UserTypeIdOrdinal = 20;
        public const int PrecisionOrdinal = 21;
        public const int ScaleOrdinal = 22;
        public const int CurrentValueOrdinal = 23;
        public const int IsExhaustedOrdinal = 24;
        public const int LastUsedValueOrdinal = 25;

        public SequencesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public SequencesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public SequencesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        public string GetName() => GetString(NameOrdinal);

        public int GetObjectId() => GetInt32(ObjectIdOrdinal);

        public int? GetPrincipalId() => GetNullableInt32(PrincipalIdOrdinal);

        public int GetSchemaId() => GetInt32(SchemaIdOrdinal);

        public int GetParentObjectId() => GetInt32(ParentObjectIdOrdinal);

        public string GetSchemaObjectType() => GetString(TypeOrdinal);

        public string GetSchemaObjectTypeDesc() => GetString(TypeDescOrdinal);

        public DateTime GetCreateDate() => GetDateTime(CreateDateOrdinal);

        public DateTime GetModifyDate() => GetDateTime(ModifyDateOrdinal);

        public bool GetIsMsShipped() => GetBoolean(IsMsShippedOrdinal);

        public bool GetIsPublished() => GetBoolean(IsPublishedOrdinal);

        public bool GetIsSchemaPublished() => GetBoolean(IsSchemaPublishedOrdinal);

        public decimal GetStartValue() => GetDecimal(StartValueOrdinal);

        public decimal GetIncrement() => GetDecimal(IncrementOrdinal);

        public decimal GetMinimumValue() => GetDecimal(MinimumValueOrdinal);

        public decimal GetMaximumValue() => GetDecimal(MaximumValueOrdinal);

        public bool GetIsCycling() => GetBoolean(IsCyclingOrdinal);

        public bool GetIsCached() => GetBoolean(IsCachedOrdinal);

        public int? GetCacheSize() => GetNullableInt32(CacheSizeOrdinal);

        public byte GetSystemTypeId() => GetByte(SystemTypeIdOrdinal);

        public int GetUserTypeId() => GetInt32(UserTypeIdOrdinal);

        public byte GetPrecision() => GetByte(PrecisionOrdinal);

        public byte GetScale() => GetByte(ScaleOrdinal);

        public decimal? GetCurrentValue()
        {
            if (IsDBNull(CurrentValueOrdinal)) return null;
            return GetDecimal(CurrentValueOrdinal);
        }

        public bool GetIsExhausted() => GetBoolean(IsExhaustedOrdinal);

        public decimal? GetLastUsedValue()
        {
            if (IsDBNull(LastUsedValueOrdinal)) return null;
            return GetDecimal(LastUsedValueOrdinal);
        }

        public Sequence GetSequence()
        {
            return new Sequence(
                GetName(),
                GetObjectId(),
                GetPrincipalId(),
                GetSchemaId(),
                GetParentObjectId(),
                GetSchemaObjectType(),
                GetSchemaObjectTypeDesc(),
                GetCreateDate(),
                GetModifyDate(),
                GetIsMsShipped(),
                GetIsPublished(),
                GetIsSchemaPublished(),
                GetStartValue(),
                GetIncrement(),
                GetMinimumValue(),
                GetMaximumValue(),
                GetIsCycling(),
                GetIsCached(),
                GetCacheSize(),
                GetSystemTypeId(),
                GetUserTypeId(),
                GetPrecision(),
                GetScale(),
                GetCurrentValue(),
                GetIsExhausted(),
                GetLastUsedValue()
            );
        }

        public IReadOnlyList<Sequence> GetSequences()
        {
            var list = new List<Sequence>();
            while (Read())
            {
                list.Add(GetSequence());
            }
            return list;
        }
    }
}
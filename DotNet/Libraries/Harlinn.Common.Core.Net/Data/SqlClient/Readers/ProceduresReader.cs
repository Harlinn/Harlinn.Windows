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
    public class ProceduresReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT sp.[name]
                  ,sp.[object_id]
                  ,sp.[principal_id]
                  ,sp.[schema_id]
                  ,sp.[parent_object_id]
                  ,sp.[type]
                  ,sp.[type_desc]
                  ,sp.[create_date]
                  ,sp.[modify_date]
                  ,sp.[is_ms_shipped]
                  ,sp.[is_published]
                  ,sp.[is_schema_published]
                  ,sp.[is_auto_executed]
                  ,sp.[is_execution_replicated]
                  ,sp.[is_repl_serializable_only]
                  ,sp.[skips_repl_constraints]
              FROM [sys].[procedures] sp
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
        public const int IsAutoExecutedOrdinal = 12;
        public const int IsExecutionReplicatedOrdinal = 13;
        public const int IsReplSerializableOnlyOrdinal = 14;
        public const int SkipsReplConstraintsOrdinal = 15;

        public ProceduresReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public ProceduresReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public ProceduresReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        public string GetName()
        {
            return GetString(NameOrdinal);
        }

        public int GetObjectId()
        {
            return GetInt32(ObjectIdOrdinal);
        }

        public int? GetPrincipalId()
        {
            return GetNullableInt32(PrincipalIdOrdinal);
        }

        public int GetSchemaId()
        {
            return GetInt32(SchemaIdOrdinal);
        }

        public int GetParentObjectId()
        {
            return GetInt32(ParentObjectIdOrdinal);
        }

        public string GetSchemaObjectType()
        {
            return GetString(TypeOrdinal);
        }

        public string GetTypeDesc()
        {
            return GetString(TypeDescOrdinal);
        }

        public DateTime GetCreateDate()
        {
            return GetDateTime(CreateDateOrdinal);
        }

        public DateTime GetModifyDate()
        {
            return GetDateTime(ModifyDateOrdinal);
        }

        public bool GetIsMsShipped()
        {
            return GetBoolean(IsMsShippedOrdinal);
        }

        public bool GetIsPublished()
        {
            return GetBoolean(IsPublishedOrdinal);
        }

        public bool GetIsSchemaPublished()
        {
            return GetBoolean(IsSchemaPublishedOrdinal);
        }

        public bool GetIsAutoExecuted()
        {
            return GetBoolean(IsAutoExecutedOrdinal);
        }

        public bool GetIsExecutionReplicated()
        {
            return GetBoolean(IsExecutionReplicatedOrdinal);
        }

        public bool GetIsReplSerializableOnly()
        {
            return GetBoolean(IsReplSerializableOnlyOrdinal);
        }

        public bool GetSkipsReplConstraints()
        {
            return GetBoolean(SkipsReplConstraintsOrdinal);
        }

        public Procedure GetProcedure()
        {
            return new Procedure(
                GetName(),
                GetObjectId(),
                GetPrincipalId(),
                GetSchemaId(),
                GetParentObjectId(),
                GetSchemaObjectType(),
                GetTypeDesc(),
                GetCreateDate(),
                GetModifyDate(),
                GetIsMsShipped(),
                GetIsPublished(),
                GetIsSchemaPublished(),
                GetIsAutoExecuted(),
                GetIsExecutionReplicated(),
                GetIsReplSerializableOnly(),
                GetSkipsReplConstraints()
            );
        }

        public IReadOnlyList<Procedure> GetProcedures()
        {
            var list = new List<Procedure>();
            while (Read())
            {
                list.Add(GetProcedure());
            }
            return list;
        }
    }
}
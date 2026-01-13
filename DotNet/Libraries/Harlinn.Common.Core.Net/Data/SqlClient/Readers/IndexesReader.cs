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

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{

    public class IndexesReader : DataReaderWrapper
    {
        public const string Sql = """
        SELECT [object_id]
            ,[name]
            ,[index_id]
            ,[type]
            ,[type_desc]
            ,[is_unique]
            ,[data_space_id]
            ,[ignore_dup_key]
            ,[is_primary_key]
            ,[is_unique_constraint]
            ,[fill_factor]
            ,[is_padded]
            ,[is_disabled]
            ,[is_hypothetical]
            ,[is_ignored_in_optimization]
            ,[allow_row_locks]
            ,[allow_page_locks]
            ,[has_filter]
            ,[filter_definition]
            ,[compression_delay]
            ,[suppress_dup_key_messages]
            ,[auto_created]
            ,[optimize_for_sequential_key]
        FROM [sys].[indexes]
        """;

        public const int ObjectIdOrdinal = 0;
        public const int NameOrdinal = 1;
        public const int IndexIdOrdinal = 2;
        public const int TypeOrdinal = 3;
        public const int TypeDescOrdinal = 4;
        public const int IsUniqueOrdinal = 5;
        public const int DataSpaceIdOrdinal = 6;
        public const int IgnoreDupKeyOrdinal = 7;
        public const int IsPrimaryKeyOrdinal = 8;
        public const int IsUniqueConstraintOrdinal = 9;
        public const int FillFactorOrdinal = 10;
        public const int IsPaddedOrdinal = 11;
        public const int IsDisabledOrdinal = 12;
        public const int IsHypotheticalOrdinal = 13;
        public const int IsIgnoredInOptimizationOrdinal = 14;
        public const int AllowRowLocksOrdinal = 15;
        public const int AllowPageLocksOrdinal = 16;
        public const int HasFilterOrdinal = 17;
        public const int FilterDefinitionOrdinal = 18;
        public const int CompressionDelayOrdinal = 19;
        public const int SuppressDupKeyMessagesOrdinal = 20;
        public const int AutoCreatedOrdinal = 21;
        public const int OptimizeForSequentialKeyOrdinal = 22;

        public IndexesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true) 
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public IndexesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public IndexesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        public int GetObjectId()
        {
            return base.GetInt32(ObjectIdOrdinal);
        }

        public string? GetName()
        {
            return base.GetNullableString(NameOrdinal);
        }

        public int GetIndexId()
        {
            return base.GetInt32(IndexIdOrdinal);
        }

        public sbyte GetIndexType()
        {
            return base.GetSByte(TypeOrdinal);
        }

        public string GetIndexTypeDesc()
        {
            return base.GetString(TypeDescOrdinal);
        }

        public bool GetIsUnique()
        {
            return base.GetBoolean(IsUniqueOrdinal);
        }

        public int GetDataSpaceId()
        {
            return base.GetInt32(DataSpaceIdOrdinal);
        }

        public bool GetIgnoreDupKey()
        {
            return base.GetBoolean(IgnoreDupKeyOrdinal);
        }

        public bool GetIsPrimaryKey()
        {
            return base.GetBoolean(IsPrimaryKeyOrdinal);
        }

        public bool GetIsUniqueConstraint()
        {
            return base.GetBoolean(IsUniqueConstraintOrdinal);
        }

        public sbyte GetFillFactor()
        {
            return base.GetSByte(FillFactorOrdinal);
        }

        public bool GetIsPadded()
        {
            return base.GetBoolean(IsPaddedOrdinal);
        }

        public bool GetIsDisabled()
        {
            return base.GetBoolean(IsDisabledOrdinal);
        }

        public bool GetIsHypothetical()
        {
            return base.GetBoolean(IsHypotheticalOrdinal);
        }

        public bool GetIsIgnoredInOptimization()
        {
            return base.GetBoolean(IsIgnoredInOptimizationOrdinal);
        }

        public bool GetAllowRowLocks()
        {
            return base.GetBoolean(AllowRowLocksOrdinal);
        }

        public bool GetAllowPageLocks()
        {
            return base.GetBoolean(AllowPageLocksOrdinal);
        }

        public bool GetHasFilter()
        {
            return base.GetBoolean(HasFilterOrdinal);
        }

        public string? GetFilterDefinition()
        {
            return base.GetNullableString(FilterDefinitionOrdinal);
        }

        public int? GetCompressionDelay()
        {
            return base.GetNullableInt32(CompressionDelayOrdinal);
        }

        public bool GetSuppressDupKeyMessages()
        {
            return base.GetBoolean(SuppressDupKeyMessagesOrdinal);
        }

        public bool GetAutoCreated()
        {
            return base.GetBoolean(AutoCreatedOrdinal);
        }

        public bool GetOptimizeForSequentialKey()
        {
            return base.GetBoolean(OptimizeForSequentialKeyOrdinal);
        }

        public Types.Index GetIndex()
        {
            var objectId = GetObjectId();
            var name = GetName();
            var indexId = GetIndexId();
            var indexType = GetIndexType();
            var indexTypeDesc = GetIndexTypeDesc();
            var isUnique = GetIsUnique();
            var dataSpaceId = GetDataSpaceId();
            var ignoreDupKey = GetIgnoreDupKey();
            var isPrimaryKey = GetIsPrimaryKey();
            var isUniqueConstraint = GetIsUniqueConstraint();
            var fillFactor = GetFillFactor();
            var isPadded = GetIsPadded();
            var isDisabled = GetIsDisabled();
            var isHypothetical = GetIsHypothetical();
            var isIgnoredInOptimization = GetIsIgnoredInOptimization();
            var allowRowLocks = GetAllowRowLocks();
            var allowPageLocks = GetAllowPageLocks();
            var hasFilter = GetHasFilter();
            var filterDefinition = GetFilterDefinition();
            var compressionDelay = GetCompressionDelay();
            var suppressDupKeyMessages = GetSuppressDupKeyMessages();
            var autoCreated = GetAutoCreated();
            var optimizeForSequentialKey = GetOptimizeForSequentialKey();
            return new Types.Index(objectId, name, indexId, indexType, indexTypeDesc, isUnique, dataSpaceId, ignoreDupKey, isPrimaryKey, isUniqueConstraint, fillFactor, isPadded, isDisabled, isHypothetical, isIgnoredInOptimization, allowRowLocks, allowPageLocks, hasFilter, filterDefinition, compressionDelay, suppressDupKeyMessages, autoCreated, optimizeForSequentialKey);
        }

        public IReadOnlyList<Types.Index> GetIndexes()
        {
            var indexes = new List<Types.Index>();
            while (Read())
            {
                indexes.Add(GetIndex());
            }
            return indexes;
        }
    }
}

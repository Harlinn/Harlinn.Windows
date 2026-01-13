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
    public class TablesReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT [name]
                ,[object_id]
                ,[principal_id]
                ,[schema_id]
                ,[parent_object_id]
                ,[type]
                ,[type_desc]
                ,[create_date]
                ,[modify_date]
                ,[is_ms_shipped]
                ,[is_published]
                ,[is_schema_published]
                ,[lob_data_space_id]
                ,[filestream_data_space_id]
                ,[max_column_id_used]
                ,[lock_on_bulk_load]
                ,[uses_ansi_nulls]
                ,[is_replicated]
                ,[has_replication_filter]
                ,[is_merge_published]
                ,[is_sync_tran_subscribed]
                ,[has_unchecked_assembly_data]
                ,[text_in_row_limit]
                ,[large_value_types_out_of_row]
                ,[is_tracked_by_cdc]
                ,[lock_escalation]
                ,[lock_escalation_desc]
                ,[is_filetable]
                ,[is_memory_optimized]
                ,[durability]
                ,[durability_desc]
                ,[temporal_type]
                ,[temporal_type_desc]
                ,[history_table_id]
                ,[is_remote_data_archive_enabled]
                ,[is_external]
                ,[history_retention_period]
                ,[history_retention_period_unit]
                ,[history_retention_period_unit_desc]
                ,[is_node]
                ,[is_edge]
            FROM [sys].[tables]
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
        public const int LobDataSpaceIdOrdinal = 12;
        public const int FilestreamDataSpaceIdOrdinal = 13;
        public const int MaxColumnIdUsedOrdinal = 14;
        public const int LockOnBulkLoadOrdinal = 15;
        public const int UsesAnsiNullsOrdinal = 16;
        public const int IsReplicatedOrdinal = 17;
        public const int HasReplicationFilterOrdinal = 18;
        public const int IsMergePublishedOrdinal = 19;
        public const int IsSyncTranSubscribedOrdinal = 20;
        public const int HasUncheckedAssemblyDataOrdinal = 21;
        public const int TextInRowLimitOrdinal = 22;
        public const int LargeValueTypesOutOfRowOrdinal = 23;
        public const int IsTrackedByCdcOrdinal = 24;
        public const int LockEscalationOrdinal = 25;
        public const int LockEscalationDescOrdinal = 26;
        public const int IsFiletableOrdinal = 27;
        public const int IsMemoryOptimizedOrdinal = 28;
        public const int DurabilityOrdinal = 29;
        public const int DurabilityDescOrdinal = 30;
        public const int TemporalTypeOrdinal = 31;
        public const int TemporalTypeDescOrdinal = 32;
        public const int HistoryTableIdOrdinal = 33;
        public const int IsRemoteDataArchiveEnabledOrdinal = 34;
        public const int IsExternalOrdinal = 35;
        public const int HistoryRetentionPeriodOrdinal = 36;
        public const int HistoryRetentionPeriodUnitOrdinal = 37;
        public const int HistoryRetentionPeriodUnitDescOrdinal = 38;
        public const int IsNodeOrdinal = 39;
        public const int IsEdgeOrdinal = 40;

        public TablesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public TablesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public TablesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(logger, sqlDataReader, ownsReader)
        {
        }

        public string GetName()
        {
            return base.GetString(NameOrdinal);
        }

        public int GetObjectId()
        {
            return base.GetInt32(ObjectIdOrdinal);
        }

        public int? GetPrincipalId()
        {
            return base.GetNullableInt32(PrincipalIdOrdinal);
        }

        public int GetSchemaId()
        {
            return base.GetInt32(SchemaIdOrdinal);
        }

        public int GetParentObjectId()
        {
            return base.GetInt32(ParentObjectIdOrdinal);
        }

        public string GetSchemaObjectType()
        {
            return base.GetString(TypeOrdinal);
        }

        public string GetSchemaObjectTypeDesc()
        {
            return base.GetString(TypeDescOrdinal);
        }

        public DateTime GetCreateDate()
        {
            return base.GetDateTime(CreateDateOrdinal);
        }

        public DateTime GetModifyDate()
        {
            return base.GetDateTime(ModifyDateOrdinal);
        }

        public bool GetIsMsShipped()
        {
            return base.GetBoolean(IsMsShippedOrdinal);
        }

        public bool GetIsPublished()
        {
            return base.GetBoolean(IsPublishedOrdinal);
        }

        public bool GetIsSchemaPublished()
        {
            return base.GetBoolean(IsSchemaPublishedOrdinal);
        }

        public int GetLobDataSpaceId()
        {
            return base.GetInt32(LobDataSpaceIdOrdinal);
        }

        public int? GetFilestreamDataSpaceId()
        {
            return base.GetNullableInt32(FilestreamDataSpaceIdOrdinal);
        }

        public int GetMaxColumnIdUsed()
        {
            return base.GetInt32(MaxColumnIdUsedOrdinal);
        }

        public bool GetLockOnBulkLoad()
        {
            return base.GetBoolean(LockOnBulkLoadOrdinal);
        }

        public bool GetUsesAnsiNulls()
        {
            return base.GetBoolean(UsesAnsiNullsOrdinal);
        }

        public bool GetIsReplicated()
        {
            return base.GetBoolean(IsReplicatedOrdinal);
        }

        public bool GetHasReplicationFilter()
        {
            return base.GetBoolean(HasReplicationFilterOrdinal);
        }

        public bool GetIsMergePublished()
        {
            return base.GetBoolean(IsMergePublishedOrdinal);
        }

        public bool GetIsSyncTranSubscribed()
        {
            return base.GetBoolean(IsSyncTranSubscribedOrdinal);
        }

        public bool GetHasUncheckedAssemblyData()
        {
            return base.GetBoolean(HasUncheckedAssemblyDataOrdinal);
        }

        public int GetTextInRowLimit()
        {
            return base.GetInt32(TextInRowLimitOrdinal);
        }

        public bool GetLargeValueTypesOutOfRow()
        {
            return base.GetBoolean(LargeValueTypesOutOfRowOrdinal);
        }

        public bool GetIsTrackedByCdc()
        {
            return base.GetBoolean(IsTrackedByCdcOrdinal);
        }

        public sbyte GetLockEscalation()
        {
            return base.GetSByte(LockEscalationOrdinal);
        }

        public string GetLockEscalationDesc()
        {
            return base.GetString(LockEscalationDescOrdinal);
        }

        public bool GetIsFiletable()
        {
            return base.GetBoolean(IsFiletableOrdinal);
        }

        public bool GetIsMemoryOptimized()
        {
            return base.GetBoolean(IsMemoryOptimizedOrdinal);
        }

        public sbyte GetDurability()
        {
            return base.GetSByte(DurabilityOrdinal);
        }

        public string GetDurabilityDesc()
        {
            return base.GetString(DurabilityDescOrdinal);
        }

        public sbyte GetTemporalType()
        {
            return base.GetSByte(TemporalTypeOrdinal);
        }

        public string GetTemporalTypeDesc()
        {
            return base.GetString(TemporalTypeDescOrdinal);
        }

        public int? GetHistoryTableId()
        {
            return base.GetNullableInt32(HistoryTableIdOrdinal);
        }

        public bool GetIsRemoteDataArchiveEnabled()
        {
            return base.GetBoolean(IsRemoteDataArchiveEnabledOrdinal);
        }

        public bool GetIsExternal()
        {
            return base.GetBoolean(IsExternalOrdinal);
        }

        public int? GetHistoryRetentionPeriod()
        {
            return base.GetNullableInt32(HistoryRetentionPeriodOrdinal);
        }

        public int? GetHistoryRetentionPeriodUnit()
        {
            return base.GetNullableInt32(HistoryRetentionPeriodUnitOrdinal);
        }

        public string? GetHistoryRetentionPeriodUnitDesc()
        {
            return base.GetNullableString(HistoryRetentionPeriodUnitDescOrdinal);
        }

        public bool GetIsNode()
        {
            return base.GetBoolean(IsNodeOrdinal);
        }

        public bool GetIsEdge()
        {
            return base.GetBoolean(IsEdgeOrdinal);
        }

        public Table GetTable()
        {
            return new Table(
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
                GetLobDataSpaceId(),
                GetFilestreamDataSpaceId(),
                GetMaxColumnIdUsed(),
                GetLockOnBulkLoad(),
                GetUsesAnsiNulls(),
                GetIsReplicated(),
                GetHasReplicationFilter(),
                GetIsMergePublished(),
                GetIsSyncTranSubscribed(),
                GetHasUncheckedAssemblyData(),
                GetTextInRowLimit(),
                GetLargeValueTypesOutOfRow(),
                GetIsTrackedByCdc(),
                GetLockEscalation(),
                GetLockEscalationDesc(),
                GetIsFiletable(),
                GetIsMemoryOptimized(),
                GetDurability(),
                GetDurabilityDesc(),
                GetTemporalType(),
                GetTemporalTypeDesc(),
                GetHistoryTableId(),
                GetIsRemoteDataArchiveEnabled(),
                GetIsExternal(),
                GetHistoryRetentionPeriod(),
                GetHistoryRetentionPeriodUnit(),
                GetHistoryRetentionPeriodUnitDesc(),
                GetIsNode(),
                GetIsEdge());
        }


        public IReadOnlyList<Table> GetTables()
        {
            var tables = new List<Table>();
            while (Read())
            {
                tables.Add(GetTable());
            }
            return tables;
        }



    }

}
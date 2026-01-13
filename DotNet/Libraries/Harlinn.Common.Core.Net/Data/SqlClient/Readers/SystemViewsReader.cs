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
    public class SystemViewsReader : DataReaderWrapper
    {
        public const string Sql = """
            SELECT ssv.[name]
                ,ssv.[object_id]
                ,ssv.[principal_id]
                ,ssv.[schema_id]
                ,ssv.[parent_object_id]
                ,ssv.[type]
                ,ssv.[type_desc]
                ,ssv.[create_date]
                ,ssv.[modify_date]
                ,ssv.[is_ms_shipped]
                ,ssv.[is_published]
                ,ssv.[is_schema_published]
                ,ssv.[is_replicated]
                ,ssv.[has_replication_filter]
                ,ssv.[has_opaque_metadata]
                ,ssv.[has_unchecked_assembly_data]
                ,ssv.[with_check_option]
                ,ssv.[is_date_correlation_view]
                ,ssv.[is_tracked_by_cdc]
                ,ssv.[has_snapshot]
                ,ss.[name] as SchemaName
            FROM [sys].[system_views] ssv
            LEFT JOIN [sys].[schemas] ss ON (ssv.[schema_id] = ss.[schema_id])
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
        public const int IsReplicatedOrdinal = 12;
        public const int HasReplicationFilterOrdinal = 13;
        public const int HasOpaqueMetadataOrdinal = 14;
        public const int HasUncheckedAssemblyDataOrdinal = 15;
        public const int WithCheckOptionOrdinal = 16;
        public const int IsDateCorrelationViewOrdinal = 17;
        public const int IsTrackedByCdcOrdinal = 18;
        public const int HasSnapshotOrdinal = 19;
        public const int SchemaNameOrdinal = 20;

        public SystemViewsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public SystemViewsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public SystemViewsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

        public string GetSchemaObjectTypeDescription()
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

        public bool GetIsReplicated()
        {
            return base.GetBoolean(IsReplicatedOrdinal);
        }

        public bool GetHasReplicationFilter()
        {
            return base.GetBoolean(HasReplicationFilterOrdinal);
        }

        public bool GetHasOpaqueMetadata()
        {
            return base.GetBoolean(HasOpaqueMetadataOrdinal);
        }

        public bool GetHasUncheckedAssemblyData()
        {
            return base.GetBoolean(HasUncheckedAssemblyDataOrdinal);
        }

        public bool GetWithCheckOption()
        {
            return base.GetBoolean(WithCheckOptionOrdinal);
        }

        public bool GetIsDateCorrelationView()
        {
            return base.GetBoolean(IsDateCorrelationViewOrdinal);
        }

        public bool GetIsTrackedByCdc()
        {
            return base.GetBoolean(IsTrackedByCdcOrdinal);
        }

        public bool GetHasSnapshot()
        {
            return base.GetBoolean(HasSnapshotOrdinal);
        }

        public string GetSchemaName()
        {
            return base.GetString(SchemaNameOrdinal);
        }

        

        public Types.SystemView GetSystemView()
        {
            string name = GetName();
            int objectId = GetObjectId();
            int? principalId = GetPrincipalId();
            int schemaId = GetSchemaId();
            int parentObjectId = GetParentObjectId();
            string type = GetSchemaObjectType();
            string typeDesc = GetSchemaObjectTypeDescription();
            DateTime createDate = GetCreateDate();
            DateTime modifyDate = GetModifyDate();
            bool isMsShipped = GetIsMsShipped();
            bool isPublished = GetIsPublished();
            bool isSchemaPublished = GetIsSchemaPublished();
            bool isReplicated = GetIsReplicated();
            bool hasReplicationFilter = GetHasReplicationFilter();
            bool hasOpaqueMetadata = GetHasOpaqueMetadata();
            bool hasUncheckedAssemblyData = GetHasUncheckedAssemblyData();
            bool withCheckOption = GetWithCheckOption();
            bool isDateCorrelationView = GetIsDateCorrelationView();
            bool isTrackedByCdc = GetIsTrackedByCdc();
            bool hasSnapshot = GetHasSnapshot();
            string schemaName = GetSchemaName();

            return new Types.SystemView(name, objectId, principalId, schemaId, parentObjectId, type, typeDesc, createDate, modifyDate, isMsShipped, isPublished, isSchemaPublished, isReplicated, hasReplicationFilter, hasOpaqueMetadata, hasUncheckedAssemblyData, withCheckOption, isDateCorrelationView, isTrackedByCdc, hasSnapshot, schemaName);



        }

        
        public IReadOnlyList<Types.SystemView> GetSystemViews()
        {
            var systemViews = new List<Types.SystemView>();
            while (Read())
            {
                systemViews.Add(GetSystemView());
            }
            return systemViews;
        }
        
    }

}

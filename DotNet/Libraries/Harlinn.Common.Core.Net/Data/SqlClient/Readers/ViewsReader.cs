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
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers
{

    public class ViewsReader : DataReaderWrapper
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
                ,[is_replicated]
                ,[has_replication_filter]
                ,[has_opaque_metadata]
                ,[has_unchecked_assembly_data]
                ,[with_check_option]
                ,[is_date_correlation_view]
                ,[is_tracked_by_cdc]
                ,[has_snapshot]
            FROM [sys].[views]
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

        public ViewsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(loggerFactory, sqlDataReader, ownsReader)
        {
        }

        public ViewsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
            : base(sqlDataReader, ownsReader)
        {
        }

        public ViewsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

        public Types.View GetView()
        {
            var name = GetName();
            var objectId = GetObjectId();
            var principalId = GetPrincipalId();
            var schemaId = GetSchemaId();
            var parentObjectId = GetParentObjectId();
            var type = GetSchemaObjectType();
            var typeDesc = GetSchemaObjectTypeDesc();
            var createDate = GetCreateDate();
            var modifyDate = GetModifyDate();
            var isMsShipped = GetIsMsShipped();
            var isPublished = GetIsPublished();
            var isSchemaPublished = GetIsSchemaPublished();
            var isReplicated = GetIsReplicated();
            var hasReplicationFilter = GetHasReplicationFilter();
            var hasOpaqueMetadata = GetHasOpaqueMetadata();
            var hasUncheckedAssemblyData = GetHasUncheckedAssemblyData();
            var withCheckOption = GetWithCheckOption();
            var isDateCorrelationView = GetIsDateCorrelationView();
            var isTrackedByCdc = GetIsTrackedByCdc();
            var hasSnapshot = GetHasSnapshot();
            return new Types.View(name, objectId, principalId, schemaId, parentObjectId, type, typeDesc, createDate, modifyDate, isMsShipped, isPublished, isSchemaPublished, isReplicated, hasReplicationFilter, hasOpaqueMetadata, hasUncheckedAssemblyData, withCheckOption, isDateCorrelationView, isTrackedByCdc, hasSnapshot);
        }


        public IReadOnlyList<Types.View> GetViews()
        {
            var views = new List<Types.View>();
            while (Read())
            {
                views.Add(GetView());
            }
            return views;
        }


    }
}

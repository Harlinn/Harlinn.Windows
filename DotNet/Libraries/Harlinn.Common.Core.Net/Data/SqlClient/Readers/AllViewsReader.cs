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
using System;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;
using Microsoft.Data.SqlClient;
using Microsoft.SqlServer.Types;
using Harlinn.Common.Core.Net.Data.SqlClient;
using Microsoft.Extensions.Logging;
using System.Diagnostics.CodeAnalysis;

namespace Harlinn.Common.Core.Net.Data.SqlClient.Readers;

public class AllViewsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[all_views]";
    public const string TableName = "all_views";
    public const string ShortName = "av";
    public const string Sql = """
        SELECT
          av.[Name],
          av.[object_id],
          av.[principal_id],
          av.[schema_id],
          av.[parent_object_id],
          av.[Type],
          av.[type_desc],
          av.[create_date],
          av.[modify_date],
          av.[is_ms_shipped],
          av.[is_published],
          av.[is_schema_published],
          av.[is_replicated],
          av.[has_replication_filter],
          av.[has_opaque_metadata],
          av.[has_unchecked_assembly_data],
          av.[with_check_option],
          av.[is_date_correlation_view],
          av.[is_tracked_by_cdc],
          av.[has_snapshot]
        FROM
          [sys].[all_views] av
        """;

    public const int NAME_FIELD_ID = 0;
    public const int OBJECTID_FIELD_ID = 1;
    public const int PRINCIPALID_FIELD_ID = 2;
    public const int SCHEMAID_FIELD_ID = 3;
    public const int PARENTOBJECTID_FIELD_ID = 4;
    public const int TYPE_FIELD_ID = 5;
    public const int TYPEDESC_FIELD_ID = 6;
    public const int CREATEDATE_FIELD_ID = 7;
    public const int MODIFYDATE_FIELD_ID = 8;
    public const int ISMSSHIPPED_FIELD_ID = 9;
    public const int ISPUBLISHED_FIELD_ID = 10;
    public const int ISSCHEMAPUBLISHED_FIELD_ID = 11;
    public const int ISREPLICATED_FIELD_ID = 12;
    public const int HASREPLICATIONFILTER_FIELD_ID = 13;
    public const int HASOPAQUEMETADATA_FIELD_ID = 14;
    public const int HASUNCHECKEDASSEMBLYDATA_FIELD_ID = 15;
    public const int WITHCHECKOPTION_FIELD_ID = 16;
    public const int ISDATECORRELATIONVIEW_FIELD_ID = 17;
    public const int ISTRACKEDBYCDC_FIELD_ID = 18;
    public const int HASSNAPSHOT_FIELD_ID = 19;


    public AllViewsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AllViewsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AllViewsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public int SchemaId
    {
        get
        {
            return base.GetInt32(SCHEMAID_FIELD_ID);
        }
    }

    public int ParentObjectId
    {
        get
        {
            return base.GetInt32(PARENTOBJECTID_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return base.GetString(TYPE_FIELD_ID);
        }
    }

    public string? TypeDesc
    {
        get
        {
            return base.GetNullableString(TYPEDESC_FIELD_ID);
        }
    }

    public DateTime CreateDate
    {
        get
        {
            return base.GetDateTime(CREATEDATE_FIELD_ID);
        }
    }

    public DateTime ModifyDate
    {
        get
        {
            return base.GetDateTime(MODIFYDATE_FIELD_ID);
        }
    }

    public bool? IsMsShipped
    {
        get
        {
            return base.GetNullableBoolean(ISMSSHIPPED_FIELD_ID);
        }
    }

    public bool? IsPublished
    {
        get
        {
            return base.GetNullableBoolean(ISPUBLISHED_FIELD_ID);
        }
    }

    public bool? IsSchemaPublished
    {
        get
        {
            return base.GetNullableBoolean(ISSCHEMAPUBLISHED_FIELD_ID);
        }
    }

    public bool? IsReplicated
    {
        get
        {
            return base.GetNullableBoolean(ISREPLICATED_FIELD_ID);
        }
    }

    public bool? HasReplicationFilter
    {
        get
        {
            return base.GetNullableBoolean(HASREPLICATIONFILTER_FIELD_ID);
        }
    }

    public bool? HasOpaqueMetadata
    {
        get
        {
            return base.GetNullableBoolean(HASOPAQUEMETADATA_FIELD_ID);
        }
    }

    public bool? HasUncheckedAssemblyData
    {
        get
        {
            return base.GetNullableBoolean(HASUNCHECKEDASSEMBLYDATA_FIELD_ID);
        }
    }

    public bool? WithCheckOption
    {
        get
        {
            return base.GetNullableBoolean(WITHCHECKOPTION_FIELD_ID);
        }
    }

    public bool? IsDateCorrelationView
    {
        get
        {
            return base.GetNullableBoolean(ISDATECORRELATIONVIEW_FIELD_ID);
        }
    }

    public bool? IsTrackedByCdc
    {
        get
        {
            return base.GetNullableBoolean(ISTRACKEDBYCDC_FIELD_ID);
        }
    }

    public bool? HasSnapshot
    {
        get
        {
            return base.GetNullableBoolean(HASSNAPSHOT_FIELD_ID);
        }
    }


    public Types.AllViewsDataType ToDataObject()
    {
        return new Types.AllViewsDataType(Name,
            ObjectId,
            PrincipalId,
            SchemaId,
            ParentObjectId,
            Type,
            TypeDesc,
            CreateDate,
            ModifyDate,
            IsMsShipped,
            IsPublished,
            IsSchemaPublished,
            IsReplicated,
            HasReplicationFilter,
            HasOpaqueMetadata,
            HasUncheckedAssemblyData,
            WithCheckOption,
            IsDateCorrelationView,
            IsTrackedByCdc,
            HasSnapshot);
    }

    public List<Types.AllViewsDataType> ToList()
    {
        var list = new List<Types.AllViewsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

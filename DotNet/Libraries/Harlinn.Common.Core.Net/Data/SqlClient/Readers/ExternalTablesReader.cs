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

public class ExternalTablesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[external_tables]";
    public const string TableName = "external_tables";
    public const string ShortName = "et";
    public const string Sql = """
        SELECT
          et.[Name],
          et.[object_id],
          et.[principal_id],
          et.[schema_id],
          et.[parent_object_id],
          et.[Type],
          et.[type_desc],
          et.[create_date],
          et.[modify_date],
          et.[is_ms_shipped],
          et.[is_published],
          et.[is_schema_published],
          et.[max_column_id_used],
          et.[uses_ansi_nulls],
          et.[data_source_id],
          et.[file_format_id],
          et.[Location],
          et.[reject_type],
          et.[reject_value],
          et.[reject_sample_value],
          et.[distribution_type],
          et.[distribution_desc],
          et.[sharding_col_id],
          et.[remote_schema_name],
          et.[remote_object_name],
          et.[rejected_row_location]
        FROM
          [sys].[external_tables] et
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
    public const int MAXCOLUMNIDUSED_FIELD_ID = 12;
    public const int USESANSINULLS_FIELD_ID = 13;
    public const int DATASOURCEID_FIELD_ID = 14;
    public const int FILEFORMATID_FIELD_ID = 15;
    public const int LOCATION_FIELD_ID = 16;
    public const int REJECTTYPE_FIELD_ID = 17;
    public const int REJECTVALUE_FIELD_ID = 18;
    public const int REJECTSAMPLEVALUE_FIELD_ID = 19;
    public const int DISTRIBUTIONTYPE_FIELD_ID = 20;
    public const int DISTRIBUTIONDESC_FIELD_ID = 21;
    public const int SHARDINGCOLID_FIELD_ID = 22;
    public const int REMOTESCHEMANAME_FIELD_ID = 23;
    public const int REMOTEOBJECTNAME_FIELD_ID = 24;
    public const int REJECTEDROWLOCATION_FIELD_ID = 25;


    public ExternalTablesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ExternalTablesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ExternalTablesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
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

    public bool IsMsShipped
    {
        get
        {
            return base.GetBoolean(ISMSSHIPPED_FIELD_ID);
        }
    }

    public bool IsPublished
    {
        get
        {
            return base.GetBoolean(ISPUBLISHED_FIELD_ID);
        }
    }

    public bool IsSchemaPublished
    {
        get
        {
            return base.GetBoolean(ISSCHEMAPUBLISHED_FIELD_ID);
        }
    }

    public int? MaxColumnIdUsed
    {
        get
        {
            return base.GetNullableInt32(MAXCOLUMNIDUSED_FIELD_ID);
        }
    }

    public bool? UsesAnsiNulls
    {
        get
        {
            return base.GetNullableBoolean(USESANSINULLS_FIELD_ID);
        }
    }

    public int DataSourceId
    {
        get
        {
            return base.GetInt32(DATASOURCEID_FIELD_ID);
        }
    }

    public int? FileFormatId
    {
        get
        {
            return base.GetNullableInt32(FILEFORMATID_FIELD_ID);
        }
    }

    public string? Location
    {
        get
        {
            return base.GetNullableString(LOCATION_FIELD_ID);
        }
    }

    public string? RejectType
    {
        get
        {
            return base.GetNullableString(REJECTTYPE_FIELD_ID);
        }
    }

    public double? RejectValue
    {
        get
        {
            return base.GetNullableDouble(REJECTVALUE_FIELD_ID);
        }
    }

    public double? RejectSampleValue
    {
        get
        {
            return base.GetNullableDouble(REJECTSAMPLEVALUE_FIELD_ID);
        }
    }

    public byte? DistributionType
    {
        get
        {
            return base.GetNullableByte(DISTRIBUTIONTYPE_FIELD_ID);
        }
    }

    public string? DistributionDesc
    {
        get
        {
            return base.GetNullableString(DISTRIBUTIONDESC_FIELD_ID);
        }
    }

    public int? ShardingColId
    {
        get
        {
            return base.GetNullableInt32(SHARDINGCOLID_FIELD_ID);
        }
    }

    public string? RemoteSchemaName
    {
        get
        {
            return base.GetNullableString(REMOTESCHEMANAME_FIELD_ID);
        }
    }

    public string? RemoteObjectName
    {
        get
        {
            return base.GetNullableString(REMOTEOBJECTNAME_FIELD_ID);
        }
    }

    public string? RejectedRowLocation
    {
        get
        {
            return base.GetNullableString(REJECTEDROWLOCATION_FIELD_ID);
        }
    }


    public Types.ExternalTablesDataType ToDataObject()
    {
        return new Types.ExternalTablesDataType(Name,
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
            MaxColumnIdUsed,
            UsesAnsiNulls,
            DataSourceId,
            FileFormatId,
            Location,
            RejectType,
            RejectValue,
            RejectSampleValue,
            DistributionType,
            DistributionDesc,
            ShardingColId,
            RemoteSchemaName,
            RemoteObjectName,
            RejectedRowLocation);
    }

    public List<Types.ExternalTablesDataType> ToList()
    {
        var list = new List<Types.ExternalTablesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

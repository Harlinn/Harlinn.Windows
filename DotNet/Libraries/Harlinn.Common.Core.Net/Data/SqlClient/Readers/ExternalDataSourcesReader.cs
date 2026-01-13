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

public class ExternalDataSourcesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[external_data_sources]";
    public const string TableName = "external_data_sources";
    public const string ShortName = "eds";
    public const string Sql = """
        SELECT
          eds.[data_source_id],
          eds.[Name],
          eds.[Location],
          eds.[type_desc],
          eds.[Type],
          eds.[resource_manager_location],
          eds.[credential_id],
          eds.[database_name],
          eds.[shard_map_name],
          eds.[connection_options],
          eds.[Pushdown]
        FROM
          [sys].[external_data_sources] eds
        """;

    public const int DATASOURCEID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int LOCATION_FIELD_ID = 2;
    public const int TYPEDESC_FIELD_ID = 3;
    public const int TYPE_FIELD_ID = 4;
    public const int RESOURCEMANAGERLOCATION_FIELD_ID = 5;
    public const int CREDENTIALID_FIELD_ID = 6;
    public const int DATABASENAME_FIELD_ID = 7;
    public const int SHARDMAPNAME_FIELD_ID = 8;
    public const int CONNECTIONOPTIONS_FIELD_ID = 9;
    public const int PUSHDOWN_FIELD_ID = 10;


    public ExternalDataSourcesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ExternalDataSourcesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ExternalDataSourcesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DataSourceId
    {
        get
        {
            return base.GetInt32(DATASOURCEID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public string Location
    {
        get
        {
            return base.GetString(LOCATION_FIELD_ID);
        }
    }

    public string? TypeDesc
    {
        get
        {
            return base.GetNullableString(TYPEDESC_FIELD_ID);
        }
    }

    public byte Type
    {
        get
        {
            return base.GetByte(TYPE_FIELD_ID);
        }
    }

    public string? ResourceManagerLocation
    {
        get
        {
            return base.GetNullableString(RESOURCEMANAGERLOCATION_FIELD_ID);
        }
    }

    public int CredentialId
    {
        get
        {
            return base.GetInt32(CREDENTIALID_FIELD_ID);
        }
    }

    public string? DatabaseName
    {
        get
        {
            return base.GetNullableString(DATABASENAME_FIELD_ID);
        }
    }

    public string? ShardMapName
    {
        get
        {
            return base.GetNullableString(SHARDMAPNAME_FIELD_ID);
        }
    }

    public string? ConnectionOptions
    {
        get
        {
            return base.GetNullableString(CONNECTIONOPTIONS_FIELD_ID);
        }
    }

    public string Pushdown
    {
        get
        {
            return base.GetString(PUSHDOWN_FIELD_ID);
        }
    }


    public Types.ExternalDataSourcesDataType ToDataObject()
    {
        return new Types.ExternalDataSourcesDataType(DataSourceId,
            Name,
            Location,
            TypeDesc,
            Type,
            ResourceManagerLocation,
            CredentialId,
            DatabaseName,
            ShardMapName,
            ConnectionOptions,
            Pushdown);
    }

    public List<Types.ExternalDataSourcesDataType> ToList()
    {
        var list = new List<Types.ExternalDataSourcesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

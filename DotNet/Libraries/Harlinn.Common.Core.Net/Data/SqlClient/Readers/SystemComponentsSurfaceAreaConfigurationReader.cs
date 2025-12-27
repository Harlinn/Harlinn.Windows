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

public class SystemComponentsSurfaceAreaConfigurationReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[system_components_surface_area_configuration]";
    public const string TableName = "system_components_surface_area_configuration";
    public const string ShortName = "scsac";
    public const string Sql = """
        SELECT
          scsac.[component_name],
          scsac.[database_name],
          scsac.[schema_name],
          scsac.[object_name],
          scsac.[State],
          scsac.[Type],
          scsac.[type_desc]
        FROM
          [sys].[system_components_surface_area_configuration] scsac
        """;

    public const int COMPONENTNAME_FIELD_ID = 0;
    public const int DATABASENAME_FIELD_ID = 1;
    public const int SCHEMANAME_FIELD_ID = 2;
    public const int OBJECTNAME_FIELD_ID = 3;
    public const int STATE_FIELD_ID = 4;
    public const int TYPE_FIELD_ID = 5;
    public const int TYPEDESC_FIELD_ID = 6;


    public SystemComponentsSurfaceAreaConfigurationReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SystemComponentsSurfaceAreaConfigurationReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SystemComponentsSurfaceAreaConfigurationReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? ComponentName
    {
        get
        {
            return base.GetNullableString(COMPONENTNAME_FIELD_ID);
        }
    }

    public string? DatabaseName
    {
        get
        {
            return base.GetNullableString(DATABASENAME_FIELD_ID);
        }
    }

    public string? SchemaName
    {
        get
        {
            return base.GetNullableString(SCHEMANAME_FIELD_ID);
        }
    }

    public string ObjectName
    {
        get
        {
            return base.GetString(OBJECTNAME_FIELD_ID);
        }
    }

    public byte? State
    {
        get
        {
            return base.GetNullableByte(STATE_FIELD_ID);
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


    public Types.SystemComponentsSurfaceAreaConfigurationDataType ToDataObject()
    {
        return new Types.SystemComponentsSurfaceAreaConfigurationDataType(ComponentName,
            DatabaseName,
            SchemaName,
            ObjectName,
            State,
            Type,
            TypeDesc);
    }

    public List<Types.SystemComponentsSurfaceAreaConfigurationDataType> ToList()
    {
        var list = new List<Types.SystemComponentsSurfaceAreaConfigurationDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

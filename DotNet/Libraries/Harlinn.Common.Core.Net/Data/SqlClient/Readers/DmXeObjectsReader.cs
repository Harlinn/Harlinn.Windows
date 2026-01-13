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

public class DmXeObjectsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_xe_objects]";
    public const string TableName = "dm_xe_objects";
    public const string ShortName = "dxo";
    public const string Sql = """
        SELECT
          dxo.[Name],
          dxo.[object_type],
          dxo.[package_guid],
          dxo.[Description],
          dxo.[Capabilities],
          dxo.[capabilities_desc],
          dxo.[type_name],
          dxo.[type_package_guid],
          dxo.[type_size]
        FROM
          [sys].[dm_xe_objects] dxo
        """;

    public const int NAME_FIELD_ID = 0;
    public const int OBJECTTYPE_FIELD_ID = 1;
    public const int PACKAGEGUID_FIELD_ID = 2;
    public const int DESCRIPTION_FIELD_ID = 3;
    public const int CAPABILITIES_FIELD_ID = 4;
    public const int CAPABILITIESDESC_FIELD_ID = 5;
    public const int TYPENAME_FIELD_ID = 6;
    public const int TYPEPACKAGEGUID_FIELD_ID = 7;
    public const int TYPESIZE_FIELD_ID = 8;


    public DmXeObjectsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmXeObjectsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmXeObjectsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public string ObjectType
    {
        get
        {
            return base.GetString(OBJECTTYPE_FIELD_ID);
        }
    }

    public Guid PackageGuid
    {
        get
        {
            return base.GetGuid(PACKAGEGUID_FIELD_ID);
        }
    }

    public string Description
    {
        get
        {
            return base.GetString(DESCRIPTION_FIELD_ID);
        }
    }

    public int? Capabilities
    {
        get
        {
            return base.GetNullableInt32(CAPABILITIES_FIELD_ID);
        }
    }

    public string? CapabilitiesDesc
    {
        get
        {
            return base.GetNullableString(CAPABILITIESDESC_FIELD_ID);
        }
    }

    public string? TypeName
    {
        get
        {
            return base.GetNullableString(TYPENAME_FIELD_ID);
        }
    }

    public Guid? TypePackageGuid
    {
        get
        {
            return base.GetNullableGuid(TYPEPACKAGEGUID_FIELD_ID);
        }
    }

    public int? TypeSize
    {
        get
        {
            return base.GetNullableInt32(TYPESIZE_FIELD_ID);
        }
    }


    public Types.DmXeObjectsDataType ToDataObject()
    {
        return new Types.DmXeObjectsDataType(Name,
            ObjectType,
            PackageGuid,
            Description,
            Capabilities,
            CapabilitiesDesc,
            TypeName,
            TypePackageGuid,
            TypeSize);
    }

    public List<Types.DmXeObjectsDataType> ToList()
    {
        var list = new List<Types.DmXeObjectsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

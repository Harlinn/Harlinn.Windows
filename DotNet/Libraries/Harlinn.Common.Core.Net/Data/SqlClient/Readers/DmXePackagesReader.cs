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

public class DmXePackagesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_xe_packages]";
    public const string TableName = "dm_xe_packages";
    public const string ShortName = "dxp";
    public const string Sql = """
        SELECT
          dxp.[Name],
          dxp.[Guid],
          dxp.[Description],
          dxp.[Capabilities],
          dxp.[capabilities_desc],
          dxp.[module_guid],
          dxp.[module_address]
        FROM
          [sys].[dm_xe_packages] dxp
        """;

    public const int NAME_FIELD_ID = 0;
    public const int GUID_FIELD_ID = 1;
    public const int DESCRIPTION_FIELD_ID = 2;
    public const int CAPABILITIES_FIELD_ID = 3;
    public const int CAPABILITIESDESC_FIELD_ID = 4;
    public const int MODULEGUID_FIELD_ID = 5;
    public const int MODULEADDRESS_FIELD_ID = 6;


    public DmXePackagesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmXePackagesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmXePackagesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public Guid Guid
    {
        get
        {
            return base.GetGuid(GUID_FIELD_ID);
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

    public string ModuleGuid
    {
        get
        {
            return base.GetString(MODULEGUID_FIELD_ID);
        }
    }

    public byte[] ModuleAddress
    {
        get
        {
            return base.GetBinary(MODULEADDRESS_FIELD_ID);
        }
    }


    public Types.DmXePackagesDataType ToDataObject()
    {
        return new Types.DmXePackagesDataType(Name,
            Guid,
            Description,
            Capabilities,
            CapabilitiesDesc,
            ModuleGuid,
            ModuleAddress);
    }

    public List<Types.DmXePackagesDataType> ToList()
    {
        var list = new List<Types.DmXePackagesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

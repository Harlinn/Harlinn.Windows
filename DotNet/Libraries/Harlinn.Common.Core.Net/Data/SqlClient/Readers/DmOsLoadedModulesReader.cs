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

public class DmOsLoadedModulesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_loaded_modules]";
    public const string TableName = "dm_os_loaded_modules";
    public const string ShortName = "dolm";
    public const string Sql = """
        SELECT
          dolm.[base_address],
          dolm.[file_version],
          dolm.[product_version],
          dolm.[Debug],
          dolm.[Patched],
          dolm.[Prerelease],
          dolm.[private_build],
          dolm.[special_build],
          dolm.[Language],
          dolm.[Company],
          dolm.[Description],
          dolm.[Name]
        FROM
          [sys].[dm_os_loaded_modules] dolm
        """;

    public const int BASEADDRESS_FIELD_ID = 0;
    public const int FILEVERSION_FIELD_ID = 1;
    public const int PRODUCTVERSION_FIELD_ID = 2;
    public const int DEBUG_FIELD_ID = 3;
    public const int PATCHED_FIELD_ID = 4;
    public const int PRERELEASE_FIELD_ID = 5;
    public const int PRIVATEBUILD_FIELD_ID = 6;
    public const int SPECIALBUILD_FIELD_ID = 7;
    public const int LANGUAGE_FIELD_ID = 8;
    public const int COMPANY_FIELD_ID = 9;
    public const int DESCRIPTION_FIELD_ID = 10;
    public const int NAME_FIELD_ID = 11;


    public DmOsLoadedModulesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsLoadedModulesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsLoadedModulesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] BaseAddress
    {
        get
        {
            return base.GetBinary(BASEADDRESS_FIELD_ID);
        }
    }

    public string? FileVersion
    {
        get
        {
            return base.GetNullableString(FILEVERSION_FIELD_ID);
        }
    }

    public string? ProductVersion
    {
        get
        {
            return base.GetNullableString(PRODUCTVERSION_FIELD_ID);
        }
    }

    public bool? Debug
    {
        get
        {
            return base.GetNullableBoolean(DEBUG_FIELD_ID);
        }
    }

    public bool? Patched
    {
        get
        {
            return base.GetNullableBoolean(PATCHED_FIELD_ID);
        }
    }

    public bool? Prerelease
    {
        get
        {
            return base.GetNullableBoolean(PRERELEASE_FIELD_ID);
        }
    }

    public bool? PrivateBuild
    {
        get
        {
            return base.GetNullableBoolean(PRIVATEBUILD_FIELD_ID);
        }
    }

    public bool? SpecialBuild
    {
        get
        {
            return base.GetNullableBoolean(SPECIALBUILD_FIELD_ID);
        }
    }

    public int? Language
    {
        get
        {
            return base.GetNullableInt32(LANGUAGE_FIELD_ID);
        }
    }

    public string? Company
    {
        get
        {
            return base.GetNullableString(COMPANY_FIELD_ID);
        }
    }

    public string? Description
    {
        get
        {
            return base.GetNullableString(DESCRIPTION_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }


    public Types.DmOsLoadedModulesDataType ToDataObject()
    {
        return new Types.DmOsLoadedModulesDataType(BaseAddress,
            FileVersion,
            ProductVersion,
            Debug,
            Patched,
            Prerelease,
            PrivateBuild,
            SpecialBuild,
            Language,
            Company,
            Description,
            Name);
    }

    public List<Types.DmOsLoadedModulesDataType> ToList()
    {
        var list = new List<Types.DmOsLoadedModulesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

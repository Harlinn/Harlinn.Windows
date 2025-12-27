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

public class CryptographicProvidersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[cryptographic_providers]";
    public const string TableName = "cryptographic_providers";
    public const string ShortName = "cp1";
    public const string Sql = """
        SELECT
          cp1.[provider_id],
          cp1.[Name],
          cp1.[Guid],
          cp1.[Version],
          cp1.[dll_path],
          cp1.[is_enabled]
        FROM
          [sys].[cryptographic_providers] cp1
        """;

    public const int PROVIDERID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int GUID_FIELD_ID = 2;
    public const int VERSION_FIELD_ID = 3;
    public const int DLLPATH_FIELD_ID = 4;
    public const int ISENABLED_FIELD_ID = 5;


    public CryptographicProvidersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public CryptographicProvidersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public CryptographicProvidersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ProviderId
    {
        get
        {
            return base.GetInt32(PROVIDERID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public Guid? Guid
    {
        get
        {
            return base.GetNullableGuid(GUID_FIELD_ID);
        }
    }

    public string? Version
    {
        get
        {
            return base.GetNullableString(VERSION_FIELD_ID);
        }
    }

    public string? DllPath
    {
        get
        {
            return base.GetNullableString(DLLPATH_FIELD_ID);
        }
    }

    public bool IsEnabled
    {
        get
        {
            return base.GetBoolean(ISENABLED_FIELD_ID);
        }
    }


    public Types.CryptographicProvidersDataType ToDataObject()
    {
        return new Types.CryptographicProvidersDataType(ProviderId,
            Name,
            Guid,
            Version,
            DllPath,
            IsEnabled);
    }

    public List<Types.CryptographicProvidersDataType> ToList()
    {
        var list = new List<Types.CryptographicProvidersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

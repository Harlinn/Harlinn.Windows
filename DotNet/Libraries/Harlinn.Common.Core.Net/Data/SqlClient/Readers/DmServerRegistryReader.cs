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

public class DmServerRegistryReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_server_registry]";
    public const string TableName = "dm_server_registry";
    public const string ShortName = "dsr";
    public const string Sql = """
        SELECT
          dsr.[registry_key],
          dsr.[value_name],
          dsr.[value_data]
        FROM
          [sys].[dm_server_registry] dsr
        """;

    public const int REGISTRYKEY_FIELD_ID = 0;
    public const int VALUENAME_FIELD_ID = 1;
    public const int VALUEDATA_FIELD_ID = 2;


    public DmServerRegistryReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmServerRegistryReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmServerRegistryReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? RegistryKey
    {
        get
        {
            return base.GetNullableString(REGISTRYKEY_FIELD_ID);
        }
    }

    public string? ValueName
    {
        get
        {
            return base.GetNullableString(VALUENAME_FIELD_ID);
        }
    }

    public object? ValueData
    {
        get
        {
            return base.GetNullableValue(VALUEDATA_FIELD_ID);
        }
    }


    public Types.DmServerRegistryDataType ToDataObject()
    {
        return new Types.DmServerRegistryDataType(RegistryKey,
            ValueName,
            ValueData);
    }

    public List<Types.DmServerRegistryDataType> ToList()
    {
        var list = new List<Types.DmServerRegistryDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

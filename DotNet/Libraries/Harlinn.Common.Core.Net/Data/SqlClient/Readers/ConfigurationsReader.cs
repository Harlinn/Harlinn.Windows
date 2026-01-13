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

public class ConfigurationsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[configurations]";
    public const string TableName = "configurations";
    public const string ShortName = "c2";
    public const string Sql = """
        SELECT
          c2.[configuration_id],
          c2.[Name],
          c2.[Value],
          c2.[Minimum],
          c2.[Maximum],
          c2.[value_in_use],
          c2.[Description],
          c2.[is_dynamic],
          c2.[is_advanced]
        FROM
          [sys].[configurations] c2
        """;

    public const int CONFIGURATIONID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int VALUE_FIELD_ID = 2;
    public const int MINIMUM_FIELD_ID = 3;
    public const int MAXIMUM_FIELD_ID = 4;
    public const int VALUEINUSE_FIELD_ID = 5;
    public const int DESCRIPTION_FIELD_ID = 6;
    public const int ISDYNAMIC_FIELD_ID = 7;
    public const int ISADVANCED_FIELD_ID = 8;


    public ConfigurationsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ConfigurationsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ConfigurationsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ConfigurationId
    {
        get
        {
            return base.GetInt32(CONFIGURATIONID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public object? Value
    {
        get
        {
            return base.GetNullableValue(VALUE_FIELD_ID);
        }
    }

    public object? Minimum
    {
        get
        {
            return base.GetNullableValue(MINIMUM_FIELD_ID);
        }
    }

    public object? Maximum
    {
        get
        {
            return base.GetNullableValue(MAXIMUM_FIELD_ID);
        }
    }

    public object? ValueInUse
    {
        get
        {
            return base.GetNullableValue(VALUEINUSE_FIELD_ID);
        }
    }

    public string Description
    {
        get
        {
            return base.GetString(DESCRIPTION_FIELD_ID);
        }
    }

    public bool IsDynamic
    {
        get
        {
            return base.GetBoolean(ISDYNAMIC_FIELD_ID);
        }
    }

    public bool IsAdvanced
    {
        get
        {
            return base.GetBoolean(ISADVANCED_FIELD_ID);
        }
    }


    public Types.ConfigurationsDataType ToDataObject()
    {
        return new Types.ConfigurationsDataType(ConfigurationId,
            Name,
            Value,
            Minimum,
            Maximum,
            ValueInUse,
            Description,
            IsDynamic,
            IsAdvanced);
    }

    public List<Types.ConfigurationsDataType> ToList()
    {
        var list = new List<Types.ConfigurationsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

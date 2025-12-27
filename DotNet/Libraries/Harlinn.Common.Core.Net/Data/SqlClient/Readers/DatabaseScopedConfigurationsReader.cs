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

public class DatabaseScopedConfigurationsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[database_scoped_configurations]";
    public const string TableName = "database_scoped_configurations";
    public const string ShortName = "dsc";
    public const string Sql = """
        SELECT
          dsc.[configuration_id],
          dsc.[Name],
          dsc.[Value],
          dsc.[value_for_secondary],
          dsc.[is_value_default]
        FROM
          [sys].[database_scoped_configurations] dsc
        """;

    public const int CONFIGURATIONID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int VALUE_FIELD_ID = 2;
    public const int VALUEFORSECONDARY_FIELD_ID = 3;
    public const int ISVALUEDEFAULT_FIELD_ID = 4;


    public DatabaseScopedConfigurationsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DatabaseScopedConfigurationsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DatabaseScopedConfigurationsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? ConfigurationId
    {
        get
        {
            return base.GetNullableInt32(CONFIGURATIONID_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public object? Value
    {
        get
        {
            return base.GetNullableValue(VALUE_FIELD_ID);
        }
    }

    public object? ValueForSecondary
    {
        get
        {
            return base.GetNullableValue(VALUEFORSECONDARY_FIELD_ID);
        }
    }

    public bool? IsValueDefault
    {
        get
        {
            return base.GetNullableBoolean(ISVALUEDEFAULT_FIELD_ID);
        }
    }


    public Types.DatabaseScopedConfigurationsDataType ToDataObject()
    {
        return new Types.DatabaseScopedConfigurationsDataType(ConfigurationId,
            Name,
            Value,
            ValueForSecondary,
            IsValueDefault);
    }

    public List<Types.DatabaseScopedConfigurationsDataType> ToList()
    {
        var list = new List<Types.DatabaseScopedConfigurationsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class DmClrPropertiesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_clr_properties]";
    public const string TableName = "dm_clr_properties";
    public const string ShortName = "dcp";
    public const string Sql = """
        SELECT
          dcp.[Name],
          dcp.[Value]
        FROM
          [sys].[dm_clr_properties] dcp
        """;

    public const int NAME_FIELD_ID = 0;
    public const int VALUE_FIELD_ID = 1;


    public DmClrPropertiesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmClrPropertiesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmClrPropertiesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public string? Value
    {
        get
        {
            return base.GetNullableString(VALUE_FIELD_ID);
        }
    }


    public Types.DmClrPropertiesDataType ToDataObject()
    {
        return new Types.DmClrPropertiesDataType(Name,
            Value);
    }

    public List<Types.DmClrPropertiesDataType> ToList()
    {
        var list = new List<Types.DmClrPropertiesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

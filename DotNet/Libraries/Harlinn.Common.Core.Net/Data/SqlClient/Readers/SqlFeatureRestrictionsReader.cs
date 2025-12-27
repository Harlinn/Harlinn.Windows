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

public class SqlFeatureRestrictionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sql_feature_restrictions]";
    public const string TableName = "sql_feature_restrictions";
    public const string ShortName = "sfr";
    public const string Sql = """
        SELECT
          sfr.[Class],
          sfr.[Object],
          sfr.[Feature]
        FROM
          [sys].[sql_feature_restrictions] sfr
        """;

    public const int CLASS_FIELD_ID = 0;
    public const int OBJECT_FIELD_ID = 1;
    public const int FEATURE_FIELD_ID = 2;


    public SqlFeatureRestrictionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SqlFeatureRestrictionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SqlFeatureRestrictionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Class
    {
        get
        {
            return base.GetString(CLASS_FIELD_ID);
        }
    }

    public string? Object
    {
        get
        {
            return base.GetNullableString(OBJECT_FIELD_ID);
        }
    }

    public string Feature
    {
        get
        {
            return base.GetString(FEATURE_FIELD_ID);
        }
    }


    public Types.SqlFeatureRestrictionsDataType ToDataObject()
    {
        return new Types.SqlFeatureRestrictionsDataType(Class,
            Object,
            Feature);
    }

    public List<Types.SqlFeatureRestrictionsDataType> ToList()
    {
        var list = new List<Types.SqlFeatureRestrictionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

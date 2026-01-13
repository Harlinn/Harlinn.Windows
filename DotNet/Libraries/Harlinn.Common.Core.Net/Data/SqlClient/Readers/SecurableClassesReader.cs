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

public class SecurableClassesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[securable_classes]";
    public const string TableName = "securable_classes";
    public const string ShortName = "sc";
    public const string Sql = """
        SELECT
          sc.[class_desc],
          sc.[Class]
        FROM
          [sys].[securable_classes] sc
        """;

    public const int CLASSDESC_FIELD_ID = 0;
    public const int CLASS_FIELD_ID = 1;


    public SecurableClassesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SecurableClassesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SecurableClassesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? ClassDesc
    {
        get
        {
            return base.GetNullableString(CLASSDESC_FIELD_ID);
        }
    }

    public int? Class
    {
        get
        {
            return base.GetNullableInt32(CLASS_FIELD_ID);
        }
    }


    public Types.SecurableClassesDataType ToDataObject()
    {
        return new Types.SecurableClassesDataType(ClassDesc,
            Class);
    }

    public List<Types.SecurableClassesDataType> ToList()
    {
        var list = new List<Types.SecurableClassesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

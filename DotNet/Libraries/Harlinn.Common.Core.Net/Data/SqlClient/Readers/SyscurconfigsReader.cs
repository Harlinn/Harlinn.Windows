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

public class SyscurconfigsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syscurconfigs]";
    public const string TableName = "syscurconfigs";
    public const string ShortName = "s21";
    public const string Sql = """
        SELECT
          s21.[Value],
          s21.[Config],
          s21.[Comment],
          s21.[Status]
        FROM
          [sys].[syscurconfigs] s21
        """;

    public const int VALUE_FIELD_ID = 0;
    public const int CONFIG_FIELD_ID = 1;
    public const int COMMENT_FIELD_ID = 2;
    public const int STATUS_FIELD_ID = 3;


    public SyscurconfigsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SyscurconfigsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SyscurconfigsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Value
    {
        get
        {
            return base.GetInt32(VALUE_FIELD_ID);
        }
    }

    public short? Config
    {
        get
        {
            return base.GetNullableInt16(CONFIG_FIELD_ID);
        }
    }

    public string Comment
    {
        get
        {
            return base.GetString(COMMENT_FIELD_ID);
        }
    }

    public short? Status
    {
        get
        {
            return base.GetNullableInt16(STATUS_FIELD_ID);
        }
    }


    public Types.SyscurconfigsDataType ToDataObject()
    {
        return new Types.SyscurconfigsDataType(Value,
            Config,
            Comment,
            Status);
    }

    public List<Types.SyscurconfigsDataType> ToList()
    {
        var list = new List<Types.SyscurconfigsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

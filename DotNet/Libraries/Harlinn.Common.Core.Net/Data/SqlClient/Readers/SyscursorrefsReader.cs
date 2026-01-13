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

public class SyscursorrefsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syscursorrefs]";
    public const string TableName = "syscursorrefs";
    public const string ShortName = "s19";
    public const string Sql = """
        SELECT
          s19.[reference_name],
          s19.[cursor_scope],
          s19.[cursor_handl]
        FROM
          [sys].[syscursorrefs] s19
        """;

    public const int REFERENCENAME_FIELD_ID = 0;
    public const int CURSORSCOPE_FIELD_ID = 1;
    public const int CURSORHANDL_FIELD_ID = 2;


    public SyscursorrefsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SyscursorrefsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SyscursorrefsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? ReferenceName
    {
        get
        {
            return base.GetNullableString(REFERENCENAME_FIELD_ID);
        }
    }

    public byte CursorScope
    {
        get
        {
            return base.GetByte(CURSORSCOPE_FIELD_ID);
        }
    }

    public int CursorHandl
    {
        get
        {
            return base.GetInt32(CURSORHANDL_FIELD_ID);
        }
    }


    public Types.SyscursorrefsDataType ToDataObject()
    {
        return new Types.SyscursorrefsDataType(ReferenceName,
            CursorScope,
            CursorHandl);
    }

    public List<Types.SyscursorrefsDataType> ToList()
    {
        var list = new List<Types.SyscursorrefsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

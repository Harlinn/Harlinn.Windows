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

public class SysopentapesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysopentapes]";
    public const string TableName = "sysopentapes";
    public const string ShortName = "s10";
    public const string Sql = """
        SELECT
          s10.[Opentape]
        FROM
          [sys].[sysopentapes] s10
        """;

    public const int OPENTAPE_FIELD_ID = 0;


    public SysopentapesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysopentapesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysopentapesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Opentape
    {
        get
        {
            return base.GetString(OPENTAPE_FIELD_ID);
        }
    }


    public Types.SysopentapesDataType ToDataObject()
    {
        return new Types.SysopentapesDataType(Opentape);
    }

    public List<Types.SysopentapesDataType> ToList()
    {
        var list = new List<Types.SysopentapesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

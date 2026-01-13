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

public class SysfulltextcatalogsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysfulltextcatalogs]";
    public const string TableName = "sysfulltextcatalogs";
    public const string ShortName = "s37";
    public const string Sql = """
        SELECT
          s37.[Ftcatid],
          s37.[Name],
          s37.[Status],
          s37.[Path]
        FROM
          [sys].[sysfulltextcatalogs] s37
        """;

    public const int FTCATID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int STATUS_FIELD_ID = 2;
    public const int PATH_FIELD_ID = 3;


    public SysfulltextcatalogsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysfulltextcatalogsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysfulltextcatalogsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short? Ftcatid
    {
        get
        {
            return base.GetNullableInt16(FTCATID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public short? Status
    {
        get
        {
            return base.GetNullableInt16(STATUS_FIELD_ID);
        }
    }

    public string? Path
    {
        get
        {
            return base.GetNullableString(PATH_FIELD_ID);
        }
    }


    public Types.SysfulltextcatalogsDataType ToDataObject()
    {
        return new Types.SysfulltextcatalogsDataType(Ftcatid,
            Name,
            Status,
            Path);
    }

    public List<Types.SysfulltextcatalogsDataType> ToList()
    {
        var list = new List<Types.SysfulltextcatalogsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

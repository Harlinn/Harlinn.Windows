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

public class SysfilegroupsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysfilegroups]";
    public const string TableName = "sysfilegroups";
    public const string ShortName = "s28";
    public const string Sql = """
        SELECT
          s28.[Groupid],
          s28.[Allocpolicy],
          s28.[Status],
          s28.[Groupname]
        FROM
          [sys].[sysfilegroups] s28
        """;

    public const int GROUPID_FIELD_ID = 0;
    public const int ALLOCPOLICY_FIELD_ID = 1;
    public const int STATUS_FIELD_ID = 2;
    public const int GROUPNAME_FIELD_ID = 3;


    public SysfilegroupsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysfilegroupsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysfilegroupsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short? Groupid
    {
        get
        {
            return base.GetNullableInt16(GROUPID_FIELD_ID);
        }
    }

    public short? Allocpolicy
    {
        get
        {
            return base.GetNullableInt16(ALLOCPOLICY_FIELD_ID);
        }
    }

    public int? Status
    {
        get
        {
            return base.GetNullableInt32(STATUS_FIELD_ID);
        }
    }

    public string Groupname
    {
        get
        {
            return base.GetString(GROUPNAME_FIELD_ID);
        }
    }


    public Types.SysfilegroupsDataType ToDataObject()
    {
        return new Types.SysfilegroupsDataType(Groupid,
            Allocpolicy,
            Status,
            Groupname);
    }

    public List<Types.SysfilegroupsDataType> ToList()
    {
        var list = new List<Types.SysfilegroupsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

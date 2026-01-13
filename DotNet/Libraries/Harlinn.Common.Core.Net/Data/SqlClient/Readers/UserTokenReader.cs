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

public class UserTokenReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[user_token]";
    public const string TableName = "user_token";
    public const string ShortName = "ut";
    public const string Sql = """
        SELECT
          ut.[principal_id],
          ut.[Sid],
          ut.[Name],
          ut.[Type],
          ut.[Usage]
        FROM
          [sys].[user_token] ut
        """;

    public const int PRINCIPALID_FIELD_ID = 0;
    public const int SID_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int TYPE_FIELD_ID = 3;
    public const int USAGE_FIELD_ID = 4;


    public UserTokenReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public UserTokenReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public UserTokenReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public byte[]? Sid
    {
        get
        {
            return base.GetNullableBinary(SID_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
        }
    }

    public string? Usage
    {
        get
        {
            return base.GetNullableString(USAGE_FIELD_ID);
        }
    }


    public Types.UserTokenDataType ToDataObject()
    {
        return new Types.UserTokenDataType(PrincipalId,
            Sid,
            Name,
            Type,
            Usage);
    }

    public List<Types.UserTokenDataType> ToList()
    {
        var list = new List<Types.UserTokenDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

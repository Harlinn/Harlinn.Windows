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

public class RemoteLoginsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[remote_logins]";
    public const string TableName = "remote_logins";
    public const string ShortName = "rl";
    public const string Sql = """
        SELECT
          rl.[server_id],
          rl.[remote_name],
          rl.[local_principal_id],
          rl.[modify_date]
        FROM
          [sys].[remote_logins] rl
        """;

    public const int SERVERID_FIELD_ID = 0;
    public const int REMOTENAME_FIELD_ID = 1;
    public const int LOCALPRINCIPALID_FIELD_ID = 2;
    public const int MODIFYDATE_FIELD_ID = 3;


    public RemoteLoginsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public RemoteLoginsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public RemoteLoginsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ServerId
    {
        get
        {
            return base.GetInt32(SERVERID_FIELD_ID);
        }
    }

    public string? RemoteName
    {
        get
        {
            return base.GetNullableString(REMOTENAME_FIELD_ID);
        }
    }

    public int? LocalPrincipalId
    {
        get
        {
            return base.GetNullableInt32(LOCALPRINCIPALID_FIELD_ID);
        }
    }

    public DateTime ModifyDate
    {
        get
        {
            return base.GetDateTime(MODIFYDATE_FIELD_ID);
        }
    }


    public Types.RemoteLoginsDataType ToDataObject()
    {
        return new Types.RemoteLoginsDataType(ServerId,
            RemoteName,
            LocalPrincipalId,
            ModifyDate);
    }

    public List<Types.RemoteLoginsDataType> ToList()
    {
        var list = new List<Types.RemoteLoginsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

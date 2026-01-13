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

public class ServerRoleMembersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[server_role_members]";
    public const string TableName = "server_role_members";
    public const string ShortName = "srm";
    public const string Sql = """
        SELECT
          srm.[role_principal_id],
          srm.[member_principal_id]
        FROM
          [sys].[server_role_members] srm
        """;

    public const int ROLEPRINCIPALID_FIELD_ID = 0;
    public const int MEMBERPRINCIPALID_FIELD_ID = 1;


    public ServerRoleMembersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServerRoleMembersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServerRoleMembersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int RolePrincipalId
    {
        get
        {
            return base.GetInt32(ROLEPRINCIPALID_FIELD_ID);
        }
    }

    public int MemberPrincipalId
    {
        get
        {
            return base.GetInt32(MEMBERPRINCIPALID_FIELD_ID);
        }
    }


    public Types.ServerRoleMembersDataType ToDataObject()
    {
        return new Types.ServerRoleMembersDataType(RolePrincipalId,
            MemberPrincipalId);
    }

    public List<Types.ServerRoleMembersDataType> ToList()
    {
        var list = new List<Types.ServerRoleMembersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

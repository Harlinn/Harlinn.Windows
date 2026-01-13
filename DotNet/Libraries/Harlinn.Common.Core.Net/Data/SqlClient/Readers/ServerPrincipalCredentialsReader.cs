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

public class ServerPrincipalCredentialsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[server_principal_credentials]";
    public const string TableName = "server_principal_credentials";
    public const string ShortName = "spc";
    public const string Sql = """
        SELECT
          spc.[principal_id],
          spc.[credential_id]
        FROM
          [sys].[server_principal_credentials] spc
        """;

    public const int PRINCIPALID_FIELD_ID = 0;
    public const int CREDENTIALID_FIELD_ID = 1;


    public ServerPrincipalCredentialsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServerPrincipalCredentialsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServerPrincipalCredentialsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int PrincipalId
    {
        get
        {
            return base.GetInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public int CredentialId
    {
        get
        {
            return base.GetInt32(CREDENTIALID_FIELD_ID);
        }
    }


    public Types.ServerPrincipalCredentialsDataType ToDataObject()
    {
        return new Types.ServerPrincipalCredentialsDataType(PrincipalId,
            CredentialId);
    }

    public List<Types.ServerPrincipalCredentialsDataType> ToList()
    {
        var list = new List<Types.ServerPrincipalCredentialsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

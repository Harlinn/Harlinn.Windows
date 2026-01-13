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

public class DatabaseCredentialsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[database_credentials]";
    public const string TableName = "database_credentials";
    public const string ShortName = "dc";
    public const string Sql = """
        SELECT
          dc.[Name],
          dc.[principal_id],
          dc.[credential_id],
          dc.[credential_identity],
          dc.[create_date],
          dc.[modify_date],
          dc.[target_type],
          dc.[target_id]
        FROM
          [sys].[database_credentials] dc
        """;

    public const int NAME_FIELD_ID = 0;
    public const int PRINCIPALID_FIELD_ID = 1;
    public const int CREDENTIALID_FIELD_ID = 2;
    public const int CREDENTIALIDENTITY_FIELD_ID = 3;
    public const int CREATEDATE_FIELD_ID = 4;
    public const int MODIFYDATE_FIELD_ID = 5;
    public const int TARGETTYPE_FIELD_ID = 6;
    public const int TARGETID_FIELD_ID = 7;


    public DatabaseCredentialsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DatabaseCredentialsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DatabaseCredentialsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
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

    public string? CredentialIdentity
    {
        get
        {
            return base.GetNullableString(CREDENTIALIDENTITY_FIELD_ID);
        }
    }

    public DateTime CreateDate
    {
        get
        {
            return base.GetDateTime(CREATEDATE_FIELD_ID);
        }
    }

    public DateTime ModifyDate
    {
        get
        {
            return base.GetDateTime(MODIFYDATE_FIELD_ID);
        }
    }

    public string? TargetType
    {
        get
        {
            return base.GetNullableString(TARGETTYPE_FIELD_ID);
        }
    }

    public int? TargetId
    {
        get
        {
            return base.GetNullableInt32(TARGETID_FIELD_ID);
        }
    }


    public Types.DatabaseCredentialsDataType ToDataObject()
    {
        return new Types.DatabaseCredentialsDataType(Name,
            PrincipalId,
            CredentialId,
            CredentialIdentity,
            CreateDate,
            ModifyDate,
            TargetType,
            TargetId);
    }

    public List<Types.DatabaseCredentialsDataType> ToList()
    {
        var list = new List<Types.DatabaseCredentialsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

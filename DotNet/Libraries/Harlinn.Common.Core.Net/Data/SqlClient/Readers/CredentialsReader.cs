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

public class CredentialsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[credentials]";
    public const string TableName = "credentials";
    public const string ShortName = "c1";
    public const string Sql = """
        SELECT
          c1.[credential_id],
          c1.[Name],
          c1.[credential_identity],
          c1.[create_date],
          c1.[modify_date],
          c1.[target_type],
          c1.[target_id]
        FROM
          [sys].[credentials] c1
        """;

    public const int CREDENTIALID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int CREDENTIALIDENTITY_FIELD_ID = 2;
    public const int CREATEDATE_FIELD_ID = 3;
    public const int MODIFYDATE_FIELD_ID = 4;
    public const int TARGETTYPE_FIELD_ID = 5;
    public const int TARGETID_FIELD_ID = 6;


    public CredentialsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public CredentialsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public CredentialsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int CredentialId
    {
        get
        {
            return base.GetInt32(CREDENTIALID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
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


    public Types.CredentialsDataType ToDataObject()
    {
        return new Types.CredentialsDataType(CredentialId,
            Name,
            CredentialIdentity,
            CreateDate,
            ModifyDate,
            TargetType,
            TargetId);
    }

    public List<Types.CredentialsDataType> ToList()
    {
        var list = new List<Types.CredentialsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

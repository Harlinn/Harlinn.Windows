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

public class SqlLoginsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sql_logins]";
    public const string TableName = "sql_logins";
    public const string ShortName = "sl";
    public const string Sql = """
        SELECT
          sl.[Name],
          sl.[principal_id],
          sl.[Sid],
          sl.[Type],
          sl.[type_desc],
          sl.[is_disabled],
          sl.[create_date],
          sl.[modify_date],
          sl.[default_database_name],
          sl.[default_language_name],
          sl.[credential_id],
          sl.[is_policy_checked],
          sl.[is_expiration_checked],
          sl.[password_hash]
        FROM
          [sys].[sql_logins] sl
        """;

    public const int NAME_FIELD_ID = 0;
    public const int PRINCIPALID_FIELD_ID = 1;
    public const int SID_FIELD_ID = 2;
    public const int TYPE_FIELD_ID = 3;
    public const int TYPEDESC_FIELD_ID = 4;
    public const int ISDISABLED_FIELD_ID = 5;
    public const int CREATEDATE_FIELD_ID = 6;
    public const int MODIFYDATE_FIELD_ID = 7;
    public const int DEFAULTDATABASENAME_FIELD_ID = 8;
    public const int DEFAULTLANGUAGENAME_FIELD_ID = 9;
    public const int CREDENTIALID_FIELD_ID = 10;
    public const int ISPOLICYCHECKED_FIELD_ID = 11;
    public const int ISEXPIRATIONCHECKED_FIELD_ID = 12;
    public const int PASSWORDHASH_FIELD_ID = 13;


    public SqlLoginsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SqlLoginsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SqlLoginsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public byte[]? Sid
    {
        get
        {
            return base.GetNullableBinary(SID_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return base.GetString(TYPE_FIELD_ID);
        }
    }

    public string? TypeDesc
    {
        get
        {
            return base.GetNullableString(TYPEDESC_FIELD_ID);
        }
    }

    public bool? IsDisabled
    {
        get
        {
            return base.GetNullableBoolean(ISDISABLED_FIELD_ID);
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

    public string? DefaultDatabaseName
    {
        get
        {
            return base.GetNullableString(DEFAULTDATABASENAME_FIELD_ID);
        }
    }

    public string? DefaultLanguageName
    {
        get
        {
            return base.GetNullableString(DEFAULTLANGUAGENAME_FIELD_ID);
        }
    }

    public int? CredentialId
    {
        get
        {
            return base.GetNullableInt32(CREDENTIALID_FIELD_ID);
        }
    }

    public bool? IsPolicyChecked
    {
        get
        {
            return base.GetNullableBoolean(ISPOLICYCHECKED_FIELD_ID);
        }
    }

    public bool? IsExpirationChecked
    {
        get
        {
            return base.GetNullableBoolean(ISEXPIRATIONCHECKED_FIELD_ID);
        }
    }

    public byte[]? PasswordHash
    {
        get
        {
            return base.GetNullableBinary(PASSWORDHASH_FIELD_ID);
        }
    }


    public Types.SqlLoginsDataType ToDataObject()
    {
        return new Types.SqlLoginsDataType(Name,
            PrincipalId,
            Sid,
            Type,
            TypeDesc,
            IsDisabled,
            CreateDate,
            ModifyDate,
            DefaultDatabaseName,
            DefaultLanguageName,
            CredentialId,
            IsPolicyChecked,
            IsExpirationChecked,
            PasswordHash);
    }

    public List<Types.SqlLoginsDataType> ToList()
    {
        var list = new List<Types.SqlLoginsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

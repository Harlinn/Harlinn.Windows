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

public class DatabasePrincipalsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[database_principals]";
    public const string TableName = "database_principals";
    public const string ShortName = "dp0";
    public const string Sql = """
        SELECT
          dp0.[Name],
          dp0.[principal_id],
          dp0.[Type],
          dp0.[type_desc],
          dp0.[default_schema_name],
          dp0.[create_date],
          dp0.[modify_date],
          dp0.[owning_principal_id],
          dp0.[Sid],
          dp0.[is_fixed_role],
          dp0.[authentication_type],
          dp0.[authentication_type_desc],
          dp0.[default_language_name],
          dp0.[default_language_lcid],
          dp0.[allow_encrypted_value_modifications]
        FROM
          [sys].[database_principals] dp0
        """;

    public const int NAME_FIELD_ID = 0;
    public const int PRINCIPALID_FIELD_ID = 1;
    public const int TYPE_FIELD_ID = 2;
    public const int TYPEDESC_FIELD_ID = 3;
    public const int DEFAULTSCHEMANAME_FIELD_ID = 4;
    public const int CREATEDATE_FIELD_ID = 5;
    public const int MODIFYDATE_FIELD_ID = 6;
    public const int OWNINGPRINCIPALID_FIELD_ID = 7;
    public const int SID_FIELD_ID = 8;
    public const int ISFIXEDROLE_FIELD_ID = 9;
    public const int AUTHENTICATIONTYPE_FIELD_ID = 10;
    public const int AUTHENTICATIONTYPEDESC_FIELD_ID = 11;
    public const int DEFAULTLANGUAGENAME_FIELD_ID = 12;
    public const int DEFAULTLANGUAGELCID_FIELD_ID = 13;
    public const int ALLOWENCRYPTEDVALUEMODIFICATIONS_FIELD_ID = 14;


    public DatabasePrincipalsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DatabasePrincipalsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DatabasePrincipalsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public string? DefaultSchemaName
    {
        get
        {
            return base.GetNullableString(DEFAULTSCHEMANAME_FIELD_ID);
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

    public int? OwningPrincipalId
    {
        get
        {
            return base.GetNullableInt32(OWNINGPRINCIPALID_FIELD_ID);
        }
    }

    public byte[]? Sid
    {
        get
        {
            return base.GetNullableBinary(SID_FIELD_ID);
        }
    }

    public bool IsFixedRole
    {
        get
        {
            return base.GetBoolean(ISFIXEDROLE_FIELD_ID);
        }
    }

    public int AuthenticationType
    {
        get
        {
            return base.GetInt32(AUTHENTICATIONTYPE_FIELD_ID);
        }
    }

    public string? AuthenticationTypeDesc
    {
        get
        {
            return base.GetNullableString(AUTHENTICATIONTYPEDESC_FIELD_ID);
        }
    }

    public string? DefaultLanguageName
    {
        get
        {
            return base.GetNullableString(DEFAULTLANGUAGENAME_FIELD_ID);
        }
    }

    public int? DefaultLanguageLcid
    {
        get
        {
            return base.GetNullableInt32(DEFAULTLANGUAGELCID_FIELD_ID);
        }
    }

    public bool AllowEncryptedValueModifications
    {
        get
        {
            return base.GetBoolean(ALLOWENCRYPTEDVALUEMODIFICATIONS_FIELD_ID);
        }
    }


    public Types.DatabasePrincipalsDataType ToDataObject()
    {
        return new Types.DatabasePrincipalsDataType(Name,
            PrincipalId,
            Type,
            TypeDesc,
            DefaultSchemaName,
            CreateDate,
            ModifyDate,
            OwningPrincipalId,
            Sid,
            IsFixedRole,
            AuthenticationType,
            AuthenticationTypeDesc,
            DefaultLanguageName,
            DefaultLanguageLcid,
            AllowEncryptedValueModifications);
    }

    public List<Types.DatabasePrincipalsDataType> ToList()
    {
        var list = new List<Types.DatabasePrincipalsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

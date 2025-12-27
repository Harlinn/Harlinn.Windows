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

public class ServerPermissionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[server_permissions]";
    public const string TableName = "server_permissions";
    public const string ShortName = "sp2";
    public const string Sql = """
        SELECT
          sp2.[Class],
          sp2.[class_desc],
          sp2.[major_id],
          sp2.[minor_id],
          sp2.[grantee_principal_id],
          sp2.[grantor_principal_id],
          sp2.[Type],
          sp2.[permission_name],
          sp2.[State],
          sp2.[state_desc]
        FROM
          [sys].[server_permissions] sp2
        """;

    public const int CLASS_FIELD_ID = 0;
    public const int CLASSDESC_FIELD_ID = 1;
    public const int MAJORID_FIELD_ID = 2;
    public const int MINORID_FIELD_ID = 3;
    public const int GRANTEEPRINCIPALID_FIELD_ID = 4;
    public const int GRANTORPRINCIPALID_FIELD_ID = 5;
    public const int TYPE_FIELD_ID = 6;
    public const int PERMISSIONNAME_FIELD_ID = 7;
    public const int STATE_FIELD_ID = 8;
    public const int STATEDESC_FIELD_ID = 9;


    public ServerPermissionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServerPermissionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServerPermissionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte Class
    {
        get
        {
            return base.GetByte(CLASS_FIELD_ID);
        }
    }

    public string? ClassDesc
    {
        get
        {
            return base.GetNullableString(CLASSDESC_FIELD_ID);
        }
    }

    public int MajorId
    {
        get
        {
            return base.GetInt32(MAJORID_FIELD_ID);
        }
    }

    public int MinorId
    {
        get
        {
            return base.GetInt32(MINORID_FIELD_ID);
        }
    }

    public int GranteePrincipalId
    {
        get
        {
            return base.GetInt32(GRANTEEPRINCIPALID_FIELD_ID);
        }
    }

    public int GrantorPrincipalId
    {
        get
        {
            return base.GetInt32(GRANTORPRINCIPALID_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return base.GetString(TYPE_FIELD_ID);
        }
    }

    public string? PermissionName
    {
        get
        {
            return base.GetNullableString(PERMISSIONNAME_FIELD_ID);
        }
    }

    public string State
    {
        get
        {
            return base.GetString(STATE_FIELD_ID);
        }
    }

    public string? StateDesc
    {
        get
        {
            return base.GetNullableString(STATEDESC_FIELD_ID);
        }
    }


    public Types.ServerPermissionsDataType ToDataObject()
    {
        return new Types.ServerPermissionsDataType(Class,
            ClassDesc,
            MajorId,
            MinorId,
            GranteePrincipalId,
            GrantorPrincipalId,
            Type,
            PermissionName,
            State,
            StateDesc);
    }

    public List<Types.ServerPermissionsDataType> ToList()
    {
        var list = new List<Types.ServerPermissionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

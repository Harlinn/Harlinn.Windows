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

public class SysusersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysusers]";
    public const string TableName = "sysusers";
    public const string ShortName = "s30";
    public const string Sql = """
        SELECT
          s30.[Uid],
          s30.[Status],
          s30.[Name],
          s30.[Sid],
          s30.[Roles],
          s30.[Createdate],
          s30.[Updatedate],
          s30.[Altuid],
          s30.[Password],
          s30.[Gid],
          s30.[Environ],
          s30.[Hasdbaccess],
          s30.[Islogin],
          s30.[Isntname],
          s30.[Isntgroup],
          s30.[Isntuser],
          s30.[Issqluser],
          s30.[Isaliased],
          s30.[Issqlrole],
          s30.[Isapprole]
        FROM
          [sys].[sysusers] s30
        """;

    public const int UID_FIELD_ID = 0;
    public const int STATUS_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int SID_FIELD_ID = 3;
    public const int ROLES_FIELD_ID = 4;
    public const int CREATEDATE_FIELD_ID = 5;
    public const int UPDATEDATE_FIELD_ID = 6;
    public const int ALTUID_FIELD_ID = 7;
    public const int PASSWORD_FIELD_ID = 8;
    public const int GID_FIELD_ID = 9;
    public const int ENVIRON_FIELD_ID = 10;
    public const int HASDBACCESS_FIELD_ID = 11;
    public const int ISLOGIN_FIELD_ID = 12;
    public const int ISNTNAME_FIELD_ID = 13;
    public const int ISNTGROUP_FIELD_ID = 14;
    public const int ISNTUSER_FIELD_ID = 15;
    public const int ISSQLUSER_FIELD_ID = 16;
    public const int ISALIASED_FIELD_ID = 17;
    public const int ISSQLROLE_FIELD_ID = 18;
    public const int ISAPPROLE_FIELD_ID = 19;


    public SysusersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysusersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysusersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short? Uid
    {
        get
        {
            return base.GetNullableInt16(UID_FIELD_ID);
        }
    }

    public short? Status
    {
        get
        {
            return base.GetNullableInt16(STATUS_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public byte[]? Sid
    {
        get
        {
            return base.GetNullableBinary(SID_FIELD_ID);
        }
    }

    public byte[]? Roles
    {
        get
        {
            return base.GetNullableBinary(ROLES_FIELD_ID);
        }
    }

    public DateTime Createdate
    {
        get
        {
            return base.GetDateTime(CREATEDATE_FIELD_ID);
        }
    }

    public DateTime Updatedate
    {
        get
        {
            return base.GetDateTime(UPDATEDATE_FIELD_ID);
        }
    }

    public short? Altuid
    {
        get
        {
            return base.GetNullableInt16(ALTUID_FIELD_ID);
        }
    }

    public byte[]? Password
    {
        get
        {
            return base.GetNullableBinary(PASSWORD_FIELD_ID);
        }
    }

    public short? Gid
    {
        get
        {
            return base.GetNullableInt16(GID_FIELD_ID);
        }
    }

    public string? Environ
    {
        get
        {
            return base.GetNullableString(ENVIRON_FIELD_ID);
        }
    }

    public int? Hasdbaccess
    {
        get
        {
            return base.GetNullableInt32(HASDBACCESS_FIELD_ID);
        }
    }

    public int? Islogin
    {
        get
        {
            return base.GetNullableInt32(ISLOGIN_FIELD_ID);
        }
    }

    public int? Isntname
    {
        get
        {
            return base.GetNullableInt32(ISNTNAME_FIELD_ID);
        }
    }

    public int? Isntgroup
    {
        get
        {
            return base.GetNullableInt32(ISNTGROUP_FIELD_ID);
        }
    }

    public int? Isntuser
    {
        get
        {
            return base.GetNullableInt32(ISNTUSER_FIELD_ID);
        }
    }

    public int? Issqluser
    {
        get
        {
            return base.GetNullableInt32(ISSQLUSER_FIELD_ID);
        }
    }

    public int? Isaliased
    {
        get
        {
            return base.GetNullableInt32(ISALIASED_FIELD_ID);
        }
    }

    public int? Issqlrole
    {
        get
        {
            return base.GetNullableInt32(ISSQLROLE_FIELD_ID);
        }
    }

    public int? Isapprole
    {
        get
        {
            return base.GetNullableInt32(ISAPPROLE_FIELD_ID);
        }
    }


    public Types.SysusersDataType ToDataObject()
    {
        return new Types.SysusersDataType(Uid,
            Status,
            Name,
            Sid,
            Roles,
            Createdate,
            Updatedate,
            Altuid,
            Password,
            Gid,
            Environ,
            Hasdbaccess,
            Islogin,
            Isntname,
            Isntgroup,
            Isntuser,
            Issqluser,
            Isaliased,
            Issqlrole,
            Isapprole);
    }

    public List<Types.SysusersDataType> ToList()
    {
        var list = new List<Types.SysusersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

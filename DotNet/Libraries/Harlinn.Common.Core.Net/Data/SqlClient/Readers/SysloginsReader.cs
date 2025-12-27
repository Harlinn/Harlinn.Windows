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

public class SysloginsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syslogins]";
    public const string TableName = "syslogins";
    public const string ShortName = "s13";
    public const string Sql = """
        SELECT
          s13.[Sid],
          s13.[Status],
          s13.[Createdate],
          s13.[Updatedate],
          s13.[Accdate],
          s13.[Totcpu],
          s13.[Totio],
          s13.[Spacelimit],
          s13.[Timelimit],
          s13.[Resultlimit],
          s13.[Name],
          s13.[Dbname],
          s13.[Password],
          s13.[Language],
          s13.[Denylogin],
          s13.[Hasaccess],
          s13.[Isntname],
          s13.[Isntgroup],
          s13.[Isntuser],
          s13.[Sysadmin],
          s13.[Securityadmin],
          s13.[Serveradmin],
          s13.[Setupadmin],
          s13.[Processadmin],
          s13.[Diskadmin],
          s13.[Dbcreator],
          s13.[Bulkadmin],
          s13.[Loginname]
        FROM
          [sys].[syslogins] s13
        """;

    public const int SID_FIELD_ID = 0;
    public const int STATUS_FIELD_ID = 1;
    public const int CREATEDATE_FIELD_ID = 2;
    public const int UPDATEDATE_FIELD_ID = 3;
    public const int ACCDATE_FIELD_ID = 4;
    public const int TOTCPU_FIELD_ID = 5;
    public const int TOTIO_FIELD_ID = 6;
    public const int SPACELIMIT_FIELD_ID = 7;
    public const int TIMELIMIT_FIELD_ID = 8;
    public const int RESULTLIMIT_FIELD_ID = 9;
    public const int NAME_FIELD_ID = 10;
    public const int DBNAME_FIELD_ID = 11;
    public const int PASSWORD_FIELD_ID = 12;
    public const int LANGUAGE_FIELD_ID = 13;
    public const int DENYLOGIN_FIELD_ID = 14;
    public const int HASACCESS_FIELD_ID = 15;
    public const int ISNTNAME_FIELD_ID = 16;
    public const int ISNTGROUP_FIELD_ID = 17;
    public const int ISNTUSER_FIELD_ID = 18;
    public const int SYSADMIN_FIELD_ID = 19;
    public const int SECURITYADMIN_FIELD_ID = 20;
    public const int SERVERADMIN_FIELD_ID = 21;
    public const int SETUPADMIN_FIELD_ID = 22;
    public const int PROCESSADMIN_FIELD_ID = 23;
    public const int DISKADMIN_FIELD_ID = 24;
    public const int DBCREATOR_FIELD_ID = 25;
    public const int BULKADMIN_FIELD_ID = 26;
    public const int LOGINNAME_FIELD_ID = 27;


    public SysloginsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysloginsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysloginsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[]? Sid
    {
        get
        {
            return base.GetNullableBinary(SID_FIELD_ID);
        }
    }

    public short? Status
    {
        get
        {
            return base.GetNullableInt16(STATUS_FIELD_ID);
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

    public DateTime Accdate
    {
        get
        {
            return base.GetDateTime(ACCDATE_FIELD_ID);
        }
    }

    public int? Totcpu
    {
        get
        {
            return base.GetNullableInt32(TOTCPU_FIELD_ID);
        }
    }

    public int? Totio
    {
        get
        {
            return base.GetNullableInt32(TOTIO_FIELD_ID);
        }
    }

    public int? Spacelimit
    {
        get
        {
            return base.GetNullableInt32(SPACELIMIT_FIELD_ID);
        }
    }

    public int? Timelimit
    {
        get
        {
            return base.GetNullableInt32(TIMELIMIT_FIELD_ID);
        }
    }

    public int? Resultlimit
    {
        get
        {
            return base.GetNullableInt32(RESULTLIMIT_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public string? Dbname
    {
        get
        {
            return base.GetNullableString(DBNAME_FIELD_ID);
        }
    }

    public string? Password
    {
        get
        {
            return base.GetNullableString(PASSWORD_FIELD_ID);
        }
    }

    public string? Language
    {
        get
        {
            return base.GetNullableString(LANGUAGE_FIELD_ID);
        }
    }

    public int? Denylogin
    {
        get
        {
            return base.GetNullableInt32(DENYLOGIN_FIELD_ID);
        }
    }

    public int? Hasaccess
    {
        get
        {
            return base.GetNullableInt32(HASACCESS_FIELD_ID);
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

    public int? Sysadmin
    {
        get
        {
            return base.GetNullableInt32(SYSADMIN_FIELD_ID);
        }
    }

    public int? Securityadmin
    {
        get
        {
            return base.GetNullableInt32(SECURITYADMIN_FIELD_ID);
        }
    }

    public int? Serveradmin
    {
        get
        {
            return base.GetNullableInt32(SERVERADMIN_FIELD_ID);
        }
    }

    public int? Setupadmin
    {
        get
        {
            return base.GetNullableInt32(SETUPADMIN_FIELD_ID);
        }
    }

    public int? Processadmin
    {
        get
        {
            return base.GetNullableInt32(PROCESSADMIN_FIELD_ID);
        }
    }

    public int? Diskadmin
    {
        get
        {
            return base.GetNullableInt32(DISKADMIN_FIELD_ID);
        }
    }

    public int? Dbcreator
    {
        get
        {
            return base.GetNullableInt32(DBCREATOR_FIELD_ID);
        }
    }

    public int? Bulkadmin
    {
        get
        {
            return base.GetNullableInt32(BULKADMIN_FIELD_ID);
        }
    }

    public string Loginname
    {
        get
        {
            return base.GetString(LOGINNAME_FIELD_ID);
        }
    }


    public Types.SysloginsDataType ToDataObject()
    {
        return new Types.SysloginsDataType(Sid,
            Status,
            Createdate,
            Updatedate,
            Accdate,
            Totcpu,
            Totio,
            Spacelimit,
            Timelimit,
            Resultlimit,
            Name,
            Dbname,
            Password,
            Language,
            Denylogin,
            Hasaccess,
            Isntname,
            Isntgroup,
            Isntuser,
            Sysadmin,
            Securityadmin,
            Serveradmin,
            Setupadmin,
            Processadmin,
            Diskadmin,
            Dbcreator,
            Bulkadmin,
            Loginname);
    }

    public List<Types.SysloginsDataType> ToList()
    {
        var list = new List<Types.SysloginsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

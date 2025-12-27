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

public class SysobjectsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysobjects]";
    public const string TableName = "sysobjects";
    public const string ShortName = "s43";
    public const string Sql = """
        SELECT
          s43.[Name],
          s43.[Id],
          s43.[Xtype],
          s43.[Uid],
          s43.[Info],
          s43.[Status],
          s43.[base_schema_ver],
          s43.[Replinfo],
          s43.[parent_obj],
          s43.[Crdate],
          s43.[Ftcatid],
          s43.[schema_ver],
          s43.[stats_schema_ver],
          s43.[Type],
          s43.[Userstat],
          s43.[Sysstat],
          s43.[Indexdel],
          s43.[Refdate],
          s43.[Version],
          s43.[Deltrig],
          s43.[Instrig],
          s43.[Updtrig],
          s43.[Seltrig],
          s43.[Category],
          s43.[Cache]
        FROM
          [sys].[sysobjects] s43
        """;

    public const int NAME_FIELD_ID = 0;
    public const int ID_FIELD_ID = 1;
    public const int XTYPE_FIELD_ID = 2;
    public const int UID_FIELD_ID = 3;
    public const int INFO_FIELD_ID = 4;
    public const int STATUS_FIELD_ID = 5;
    public const int BASESCHEMAVER_FIELD_ID = 6;
    public const int REPLINFO_FIELD_ID = 7;
    public const int PARENTOBJ_FIELD_ID = 8;
    public const int CRDATE_FIELD_ID = 9;
    public const int FTCATID_FIELD_ID = 10;
    public const int SCHEMAVER_FIELD_ID = 11;
    public const int STATSSCHEMAVER_FIELD_ID = 12;
    public const int TYPE_FIELD_ID = 13;
    public const int USERSTAT_FIELD_ID = 14;
    public const int SYSSTAT_FIELD_ID = 15;
    public const int INDEXDEL_FIELD_ID = 16;
    public const int REFDATE_FIELD_ID = 17;
    public const int VERSION_FIELD_ID = 18;
    public const int DELTRIG_FIELD_ID = 19;
    public const int INSTRIG_FIELD_ID = 20;
    public const int UPDTRIG_FIELD_ID = 21;
    public const int SELTRIG_FIELD_ID = 22;
    public const int CATEGORY_FIELD_ID = 23;
    public const int CACHE_FIELD_ID = 24;


    public SysobjectsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysobjectsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysobjectsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int Id
    {
        get
        {
            return base.GetInt32(ID_FIELD_ID);
        }
    }

    public string Xtype
    {
        get
        {
            return base.GetString(XTYPE_FIELD_ID);
        }
    }

    public short? Uid
    {
        get
        {
            return base.GetNullableInt16(UID_FIELD_ID);
        }
    }

    public short? Info
    {
        get
        {
            return base.GetNullableInt16(INFO_FIELD_ID);
        }
    }

    public int? Status
    {
        get
        {
            return base.GetNullableInt32(STATUS_FIELD_ID);
        }
    }

    public int? BaseSchemaVer
    {
        get
        {
            return base.GetNullableInt32(BASESCHEMAVER_FIELD_ID);
        }
    }

    public int? Replinfo
    {
        get
        {
            return base.GetNullableInt32(REPLINFO_FIELD_ID);
        }
    }

    public int ParentObj
    {
        get
        {
            return base.GetInt32(PARENTOBJ_FIELD_ID);
        }
    }

    public DateTime Crdate
    {
        get
        {
            return base.GetDateTime(CRDATE_FIELD_ID);
        }
    }

    public short? Ftcatid
    {
        get
        {
            return base.GetNullableInt16(FTCATID_FIELD_ID);
        }
    }

    public int? SchemaVer
    {
        get
        {
            return base.GetNullableInt32(SCHEMAVER_FIELD_ID);
        }
    }

    public int? StatsSchemaVer
    {
        get
        {
            return base.GetNullableInt32(STATSSCHEMAVER_FIELD_ID);
        }
    }

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
        }
    }

    public short? Userstat
    {
        get
        {
            return base.GetNullableInt16(USERSTAT_FIELD_ID);
        }
    }

    public short? Sysstat
    {
        get
        {
            return base.GetNullableInt16(SYSSTAT_FIELD_ID);
        }
    }

    public short? Indexdel
    {
        get
        {
            return base.GetNullableInt16(INDEXDEL_FIELD_ID);
        }
    }

    public DateTime Refdate
    {
        get
        {
            return base.GetDateTime(REFDATE_FIELD_ID);
        }
    }

    public int? Version
    {
        get
        {
            return base.GetNullableInt32(VERSION_FIELD_ID);
        }
    }

    public int? Deltrig
    {
        get
        {
            return base.GetNullableInt32(DELTRIG_FIELD_ID);
        }
    }

    public int? Instrig
    {
        get
        {
            return base.GetNullableInt32(INSTRIG_FIELD_ID);
        }
    }

    public int? Updtrig
    {
        get
        {
            return base.GetNullableInt32(UPDTRIG_FIELD_ID);
        }
    }

    public int? Seltrig
    {
        get
        {
            return base.GetNullableInt32(SELTRIG_FIELD_ID);
        }
    }

    public int? Category
    {
        get
        {
            return base.GetNullableInt32(CATEGORY_FIELD_ID);
        }
    }

    public short? Cache
    {
        get
        {
            return base.GetNullableInt16(CACHE_FIELD_ID);
        }
    }


    public Types.SysobjectsDataType ToDataObject()
    {
        return new Types.SysobjectsDataType(Name,
            Id,
            Xtype,
            Uid,
            Info,
            Status,
            BaseSchemaVer,
            Replinfo,
            ParentObj,
            Crdate,
            Ftcatid,
            SchemaVer,
            StatsSchemaVer,
            Type,
            Userstat,
            Sysstat,
            Indexdel,
            Refdate,
            Version,
            Deltrig,
            Instrig,
            Updtrig,
            Seltrig,
            Category,
            Cache);
    }

    public List<Types.SysobjectsDataType> ToList()
    {
        var list = new List<Types.SysobjectsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

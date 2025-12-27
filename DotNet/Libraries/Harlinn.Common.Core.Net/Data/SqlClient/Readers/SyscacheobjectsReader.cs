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

public class SyscacheobjectsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syscacheobjects]";
    public const string TableName = "syscacheobjects";
    public const string ShortName = "s25";
    public const string Sql = """
        SELECT
          s25.[Bucketid],
          s25.[Cacheobjtype],
          s25.[Objtype],
          s25.[Objid],
          s25.[Dbid],
          s25.[Dbidexec],
          s25.[Uid],
          s25.[Refcounts],
          s25.[Usecounts],
          s25.[Pagesused],
          s25.[Setopts],
          s25.[Langid],
          s25.[Dateformat],
          s25.[Status],
          s25.[Lasttime],
          s25.[Maxexectime],
          s25.[Avgexectime],
          s25.[Lastreads],
          s25.[Lastwrites],
          s25.[Sqlbytes],
          s25.[Sql]
        FROM
          [sys].[syscacheobjects] s25
        """;

    public const int BUCKETID_FIELD_ID = 0;
    public const int CACHEOBJTYPE_FIELD_ID = 1;
    public const int OBJTYPE_FIELD_ID = 2;
    public const int OBJID_FIELD_ID = 3;
    public const int DBID_FIELD_ID = 4;
    public const int DBIDEXEC_FIELD_ID = 5;
    public const int UID_FIELD_ID = 6;
    public const int REFCOUNTS_FIELD_ID = 7;
    public const int USECOUNTS_FIELD_ID = 8;
    public const int PAGESUSED_FIELD_ID = 9;
    public const int SETOPTS_FIELD_ID = 10;
    public const int LANGID_FIELD_ID = 11;
    public const int DATEFORMAT_FIELD_ID = 12;
    public const int STATUS_FIELD_ID = 13;
    public const int LASTTIME_FIELD_ID = 14;
    public const int MAXEXECTIME_FIELD_ID = 15;
    public const int AVGEXECTIME_FIELD_ID = 16;
    public const int LASTREADS_FIELD_ID = 17;
    public const int LASTWRITES_FIELD_ID = 18;
    public const int SQLBYTES_FIELD_ID = 19;
    public const int SQL_FIELD_ID = 20;


    public SyscacheobjectsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SyscacheobjectsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SyscacheobjectsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Bucketid
    {
        get
        {
            return base.GetInt32(BUCKETID_FIELD_ID);
        }
    }

    public string Cacheobjtype
    {
        get
        {
            return base.GetString(CACHEOBJTYPE_FIELD_ID);
        }
    }

    public string Objtype
    {
        get
        {
            return base.GetString(OBJTYPE_FIELD_ID);
        }
    }

    public int? Objid
    {
        get
        {
            return base.GetNullableInt32(OBJID_FIELD_ID);
        }
    }

    public short? Dbid
    {
        get
        {
            return base.GetNullableInt16(DBID_FIELD_ID);
        }
    }

    public short? Dbidexec
    {
        get
        {
            return base.GetNullableInt16(DBIDEXEC_FIELD_ID);
        }
    }

    public short? Uid
    {
        get
        {
            return base.GetNullableInt16(UID_FIELD_ID);
        }
    }

    public int Refcounts
    {
        get
        {
            return base.GetInt32(REFCOUNTS_FIELD_ID);
        }
    }

    public int Usecounts
    {
        get
        {
            return base.GetInt32(USECOUNTS_FIELD_ID);
        }
    }

    public int? Pagesused
    {
        get
        {
            return base.GetNullableInt32(PAGESUSED_FIELD_ID);
        }
    }

    public int? Setopts
    {
        get
        {
            return base.GetNullableInt32(SETOPTS_FIELD_ID);
        }
    }

    public short? Langid
    {
        get
        {
            return base.GetNullableInt16(LANGID_FIELD_ID);
        }
    }

    public short? Dateformat
    {
        get
        {
            return base.GetNullableInt16(DATEFORMAT_FIELD_ID);
        }
    }

    public int? Status
    {
        get
        {
            return base.GetNullableInt32(STATUS_FIELD_ID);
        }
    }

    public long? Lasttime
    {
        get
        {
            return base.GetNullableInt64(LASTTIME_FIELD_ID);
        }
    }

    public long? Maxexectime
    {
        get
        {
            return base.GetNullableInt64(MAXEXECTIME_FIELD_ID);
        }
    }

    public long? Avgexectime
    {
        get
        {
            return base.GetNullableInt64(AVGEXECTIME_FIELD_ID);
        }
    }

    public long? Lastreads
    {
        get
        {
            return base.GetNullableInt64(LASTREADS_FIELD_ID);
        }
    }

    public long? Lastwrites
    {
        get
        {
            return base.GetNullableInt64(LASTWRITES_FIELD_ID);
        }
    }

    public int? Sqlbytes
    {
        get
        {
            return base.GetNullableInt32(SQLBYTES_FIELD_ID);
        }
    }

    public string? SqlDefinition
    {
        get
        {
            return base.GetNullableString(SQL_FIELD_ID);
        }
    }


    public Types.SyscacheobjectsDataType ToDataObject()
    {
        return new Types.SyscacheobjectsDataType(Bucketid,
            Cacheobjtype,
            Objtype,
            Objid,
            Dbid,
            Dbidexec,
            Uid,
            Refcounts,
            Usecounts,
            Pagesused,
            Setopts,
            Langid,
            Dateformat,
            Status,
            Lasttime,
            Maxexectime,
            Avgexectime,
            Lastreads,
            Lastwrites,
            Sqlbytes,
            SqlDefinition);
    }

    public List<Types.SyscacheobjectsDataType> ToList()
    {
        var list = new List<Types.SyscacheobjectsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class SyscursortablesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syscursortables]";
    public const string TableName = "syscursortables";
    public const string ShortName = "s17";
    public const string Sql = """
        SELECT
          s17.[cursor_handle],
          s17.[table_owner],
          s17.[table_name],
          s17.[optimizer_hint],
          s17.[lock_type],
          s17.[server_name],
          s17.[Objectid],
          s17.[Dbid],
          s17.[Dbname]
        FROM
          [sys].[syscursortables] s17
        """;

    public const int CURSORHANDLE_FIELD_ID = 0;
    public const int TABLEOWNER_FIELD_ID = 1;
    public const int TABLENAME_FIELD_ID = 2;
    public const int OPTIMIZERHINT_FIELD_ID = 3;
    public const int LOCKTYPE_FIELD_ID = 4;
    public const int SERVERNAME_FIELD_ID = 5;
    public const int OBJECTID_FIELD_ID = 6;
    public const int DBID_FIELD_ID = 7;
    public const int DBNAME_FIELD_ID = 8;


    public SyscursortablesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SyscursortablesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SyscursortablesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int CursorHandle
    {
        get
        {
            return base.GetInt32(CURSORHANDLE_FIELD_ID);
        }
    }

    public string? TableOwner
    {
        get
        {
            return base.GetNullableString(TABLEOWNER_FIELD_ID);
        }
    }

    public string? UserTableName
    {
        get
        {
            return base.GetNullableString(TABLENAME_FIELD_ID);
        }
    }

    public short OptimizerHint
    {
        get
        {
            return base.GetInt16(OPTIMIZERHINT_FIELD_ID);
        }
    }

    public short LockType
    {
        get
        {
            return base.GetInt16(LOCKTYPE_FIELD_ID);
        }
    }

    public string? ServerName
    {
        get
        {
            return base.GetNullableString(SERVERNAME_FIELD_ID);
        }
    }

    public int Objectid
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int Dbid
    {
        get
        {
            return base.GetInt32(DBID_FIELD_ID);
        }
    }

    public string? Dbname
    {
        get
        {
            return base.GetNullableString(DBNAME_FIELD_ID);
        }
    }


    public Types.SyscursortablesDataType ToDataObject()
    {
        return new Types.SyscursortablesDataType(CursorHandle,
            TableOwner,
            UserTableName,
            OptimizerHint,
            LockType,
            ServerName,
            Objectid,
            Dbid,
            Dbname);
    }

    public List<Types.SyscursortablesDataType> ToList()
    {
        var list = new List<Types.SyscursortablesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

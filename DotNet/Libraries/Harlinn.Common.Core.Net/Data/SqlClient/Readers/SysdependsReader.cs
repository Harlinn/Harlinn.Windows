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

public class SysdependsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysdepends]";
    public const string TableName = "sysdepends";
    public const string ShortName = "s40";
    public const string Sql = """
        SELECT
          s40.[Id],
          s40.[Depid],
          s40.[Number],
          s40.[Depnumber],
          s40.[Status],
          s40.[Deptype],
          s40.[Depdbid],
          s40.[Depsiteid],
          s40.[Selall],
          s40.[Resultobj],
          s40.[Readobj]
        FROM
          [sys].[sysdepends] s40
        """;

    public const int ID_FIELD_ID = 0;
    public const int DEPID_FIELD_ID = 1;
    public const int NUMBER_FIELD_ID = 2;
    public const int DEPNUMBER_FIELD_ID = 3;
    public const int STATUS_FIELD_ID = 4;
    public const int DEPTYPE_FIELD_ID = 5;
    public const int DEPDBID_FIELD_ID = 6;
    public const int DEPSITEID_FIELD_ID = 7;
    public const int SELALL_FIELD_ID = 8;
    public const int RESULTOBJ_FIELD_ID = 9;
    public const int READOBJ_FIELD_ID = 10;


    public SysdependsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysdependsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysdependsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Id
    {
        get
        {
            return base.GetInt32(ID_FIELD_ID);
        }
    }

    public int Depid
    {
        get
        {
            return base.GetInt32(DEPID_FIELD_ID);
        }
    }

    public short? Number
    {
        get
        {
            return base.GetNullableInt16(NUMBER_FIELD_ID);
        }
    }

    public short? Depnumber
    {
        get
        {
            return base.GetNullableInt16(DEPNUMBER_FIELD_ID);
        }
    }

    public short? Status
    {
        get
        {
            return base.GetNullableInt16(STATUS_FIELD_ID);
        }
    }

    public byte Deptype
    {
        get
        {
            return base.GetByte(DEPTYPE_FIELD_ID);
        }
    }

    public short? Depdbid
    {
        get
        {
            return base.GetNullableInt16(DEPDBID_FIELD_ID);
        }
    }

    public short? Depsiteid
    {
        get
        {
            return base.GetNullableInt16(DEPSITEID_FIELD_ID);
        }
    }

    public bool Selall
    {
        get
        {
            return base.GetBoolean(SELALL_FIELD_ID);
        }
    }

    public bool Resultobj
    {
        get
        {
            return base.GetBoolean(RESULTOBJ_FIELD_ID);
        }
    }

    public bool Readobj
    {
        get
        {
            return base.GetBoolean(READOBJ_FIELD_ID);
        }
    }


    public Types.SysdependsDataType ToDataObject()
    {
        return new Types.SysdependsDataType(Id,
            Depid,
            Number,
            Depnumber,
            Status,
            Deptype,
            Depdbid,
            Depsiteid,
            Selall,
            Resultobj,
            Readobj);
    }

    public List<Types.SysdependsDataType> ToList()
    {
        var list = new List<Types.SysdependsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class SyspermissionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syspermissions]";
    public const string TableName = "syspermissions";
    public const string ShortName = "s34";
    public const string Sql = """
        SELECT
          s34.[Id],
          s34.[Grantee],
          s34.[Grantor],
          s34.[Actadd],
          s34.[Actmod],
          s34.[Seladd],
          s34.[Selmod],
          s34.[Updadd],
          s34.[Updmod],
          s34.[Refadd],
          s34.[Refmod]
        FROM
          [sys].[syspermissions] s34
        """;

    public const int ID_FIELD_ID = 0;
    public const int GRANTEE_FIELD_ID = 1;
    public const int GRANTOR_FIELD_ID = 2;
    public const int ACTADD_FIELD_ID = 3;
    public const int ACTMOD_FIELD_ID = 4;
    public const int SELADD_FIELD_ID = 5;
    public const int SELMOD_FIELD_ID = 6;
    public const int UPDADD_FIELD_ID = 7;
    public const int UPDMOD_FIELD_ID = 8;
    public const int REFADD_FIELD_ID = 9;
    public const int REFMOD_FIELD_ID = 10;


    public SyspermissionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SyspermissionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SyspermissionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public short? Grantee
    {
        get
        {
            return base.GetNullableInt16(GRANTEE_FIELD_ID);
        }
    }

    public short? Grantor
    {
        get
        {
            return base.GetNullableInt16(GRANTOR_FIELD_ID);
        }
    }

    public short? Actadd
    {
        get
        {
            return base.GetNullableInt16(ACTADD_FIELD_ID);
        }
    }

    public short? Actmod
    {
        get
        {
            return base.GetNullableInt16(ACTMOD_FIELD_ID);
        }
    }

    public byte[]? Seladd
    {
        get
        {
            return base.GetNullableBinary(SELADD_FIELD_ID);
        }
    }

    public byte[]? Selmod
    {
        get
        {
            return base.GetNullableBinary(SELMOD_FIELD_ID);
        }
    }

    public byte[]? Updadd
    {
        get
        {
            return base.GetNullableBinary(UPDADD_FIELD_ID);
        }
    }

    public byte[]? Updmod
    {
        get
        {
            return base.GetNullableBinary(UPDMOD_FIELD_ID);
        }
    }

    public byte[]? Refadd
    {
        get
        {
            return base.GetNullableBinary(REFADD_FIELD_ID);
        }
    }

    public byte[]? Refmod
    {
        get
        {
            return base.GetNullableBinary(REFMOD_FIELD_ID);
        }
    }


    public Types.SyspermissionsDataType ToDataObject()
    {
        return new Types.SyspermissionsDataType(Id,
            Grantee,
            Grantor,
            Actadd,
            Actmod,
            Seladd,
            Selmod,
            Updadd,
            Updmod,
            Refadd,
            Refmod);
    }

    public List<Types.SyspermissionsDataType> ToList()
    {
        var list = new List<Types.SyspermissionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

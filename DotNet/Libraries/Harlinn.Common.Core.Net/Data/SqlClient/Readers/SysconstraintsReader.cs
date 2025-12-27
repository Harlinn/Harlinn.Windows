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

public class SysconstraintsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysconstraints]";
    public const string TableName = "sysconstraints";
    public const string ShortName = "s38";
    public const string Sql = """
        SELECT
          s38.[Constid],
          s38.[Id],
          s38.[Colid],
          s38.[Spare1],
          s38.[Status],
          s38.[Actions],
          s38.[Error]
        FROM
          [sys].[sysconstraints] s38
        """;

    public const int CONSTID_FIELD_ID = 0;
    public const int ID_FIELD_ID = 1;
    public const int COLID_FIELD_ID = 2;
    public const int SPARE1_FIELD_ID = 3;
    public const int STATUS_FIELD_ID = 4;
    public const int ACTIONS_FIELD_ID = 5;
    public const int ERROR_FIELD_ID = 6;


    public SysconstraintsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysconstraintsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysconstraintsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Constid
    {
        get
        {
            return base.GetInt32(CONSTID_FIELD_ID);
        }
    }

    public int Id
    {
        get
        {
            return base.GetInt32(ID_FIELD_ID);
        }
    }

    public short? Colid
    {
        get
        {
            return base.GetNullableInt16(COLID_FIELD_ID);
        }
    }

    public byte? Spare1
    {
        get
        {
            return base.GetNullableByte(SPARE1_FIELD_ID);
        }
    }

    public int? Status
    {
        get
        {
            return base.GetNullableInt32(STATUS_FIELD_ID);
        }
    }

    public int? Actions
    {
        get
        {
            return base.GetNullableInt32(ACTIONS_FIELD_ID);
        }
    }

    public int? Error
    {
        get
        {
            return base.GetNullableInt32(ERROR_FIELD_ID);
        }
    }


    public Types.SysconstraintsDataType ToDataObject()
    {
        return new Types.SysconstraintsDataType(Constid,
            Id,
            Colid,
            Spare1,
            Status,
            Actions,
            Error);
    }

    public List<Types.SysconstraintsDataType> ToList()
    {
        var list = new List<Types.SysconstraintsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

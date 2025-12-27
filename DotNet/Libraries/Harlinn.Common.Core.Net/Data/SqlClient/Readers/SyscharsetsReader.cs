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

public class SyscharsetsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syscharsets]";
    public const string TableName = "syscharsets";
    public const string ShortName = "s23";
    public const string Sql = """
        SELECT
          s23.[Type],
          s23.[Id],
          s23.[Csid],
          s23.[Status],
          s23.[Name],
          s23.[Description],
          s23.[Binarydefinition],
          s23.[Definition]
        FROM
          [sys].[syscharsets] s23
        """;

    public const int TYPE_FIELD_ID = 0;
    public const int ID_FIELD_ID = 1;
    public const int CSID_FIELD_ID = 2;
    public const int STATUS_FIELD_ID = 3;
    public const int NAME_FIELD_ID = 4;
    public const int DESCRIPTION_FIELD_ID = 5;
    public const int BINARYDEFINITION_FIELD_ID = 6;
    public const int DEFINITION_FIELD_ID = 7;


    public SyscharsetsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SyscharsetsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SyscharsetsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short Type
    {
        get
        {
            return base.GetInt16(TYPE_FIELD_ID);
        }
    }

    public byte Id
    {
        get
        {
            return base.GetByte(ID_FIELD_ID);
        }
    }

    public byte Csid
    {
        get
        {
            return base.GetByte(CSID_FIELD_ID);
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

    public string Description
    {
        get
        {
            return base.GetString(DESCRIPTION_FIELD_ID);
        }
    }

    public byte[]? Binarydefinition
    {
        get
        {
            return base.GetNullableBinary(BINARYDEFINITION_FIELD_ID);
        }
    }

    public byte[]? Definition
    {
        get
        {
            return base.GetNullableBinary(DEFINITION_FIELD_ID);
        }
    }


    public Types.SyscharsetsDataType ToDataObject()
    {
        return new Types.SyscharsetsDataType(Type,
            Id,
            Csid,
            Status,
            Name,
            Description,
            Binarydefinition,
            Definition);
    }

    public List<Types.SyscharsetsDataType> ToList()
    {
        var list = new List<Types.SyscharsetsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

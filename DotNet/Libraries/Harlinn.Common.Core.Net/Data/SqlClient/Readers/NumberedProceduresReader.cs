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

public class NumberedProceduresReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[numbered_procedures]";
    public const string TableName = "numbered_procedures";
    public const string ShortName = "np";
    public const string Sql = """
        SELECT
          np.[object_id],
          np.[procedure_number],
          np.[Definition]
        FROM
          [sys].[numbered_procedures] np
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int PROCEDURENUMBER_FIELD_ID = 1;
    public const int DEFINITION_FIELD_ID = 2;


    public NumberedProceduresReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public NumberedProceduresReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public NumberedProceduresReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public short? ProcedureNumber
    {
        get
        {
            return base.GetNullableInt16(PROCEDURENUMBER_FIELD_ID);
        }
    }

    public string? Definition
    {
        get
        {
            return base.GetNullableString(DEFINITION_FIELD_ID);
        }
    }


    public Types.NumberedProceduresDataType ToDataObject()
    {
        return new Types.NumberedProceduresDataType(ObjectId,
            ProcedureNumber,
            Definition);
    }

    public List<Types.NumberedProceduresDataType> ToList()
    {
        var list = new List<Types.NumberedProceduresDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

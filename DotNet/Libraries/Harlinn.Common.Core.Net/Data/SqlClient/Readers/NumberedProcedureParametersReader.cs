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

public class NumberedProcedureParametersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[numbered_procedure_parameters]";
    public const string TableName = "numbered_procedure_parameters";
    public const string ShortName = "npp";
    public const string Sql = """
        SELECT
          npp.[object_id],
          npp.[procedure_number],
          npp.[Name],
          npp.[parameter_id],
          npp.[system_type_id],
          npp.[user_type_id],
          npp.[max_length],
          npp.[Precision],
          npp.[Scale],
          npp.[is_output],
          npp.[is_cursor_ref]
        FROM
          [sys].[numbered_procedure_parameters] npp
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int PROCEDURENUMBER_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int PARAMETERID_FIELD_ID = 3;
    public const int SYSTEMTYPEID_FIELD_ID = 4;
    public const int USERTYPEID_FIELD_ID = 5;
    public const int MAXLENGTH_FIELD_ID = 6;
    public const int PRECISION_FIELD_ID = 7;
    public const int SCALE_FIELD_ID = 8;
    public const int ISOUTPUT_FIELD_ID = 9;
    public const int ISCURSORREF_FIELD_ID = 10;


    public NumberedProcedureParametersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public NumberedProcedureParametersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public NumberedProcedureParametersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public short ProcedureNumber
    {
        get
        {
            return base.GetInt16(PROCEDURENUMBER_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public int ParameterId
    {
        get
        {
            return base.GetInt32(PARAMETERID_FIELD_ID);
        }
    }

    public byte SystemTypeId
    {
        get
        {
            return base.GetByte(SYSTEMTYPEID_FIELD_ID);
        }
    }

    public int UserTypeId
    {
        get
        {
            return base.GetInt32(USERTYPEID_FIELD_ID);
        }
    }

    public short MaxLength
    {
        get
        {
            return base.GetInt16(MAXLENGTH_FIELD_ID);
        }
    }

    public byte Precision
    {
        get
        {
            return base.GetByte(PRECISION_FIELD_ID);
        }
    }

    public byte Scale
    {
        get
        {
            return base.GetByte(SCALE_FIELD_ID);
        }
    }

    public bool IsOutput
    {
        get
        {
            return base.GetBoolean(ISOUTPUT_FIELD_ID);
        }
    }

    public bool IsCursorRef
    {
        get
        {
            return base.GetBoolean(ISCURSORREF_FIELD_ID);
        }
    }


    public Types.NumberedProcedureParametersDataType ToDataObject()
    {
        return new Types.NumberedProcedureParametersDataType(ObjectId,
            ProcedureNumber,
            Name,
            ParameterId,
            SystemTypeId,
            UserTypeId,
            MaxLength,
            Precision,
            Scale,
            IsOutput,
            IsCursorRef);
    }

    public List<Types.NumberedProcedureParametersDataType> ToList()
    {
        var list = new List<Types.NumberedProcedureParametersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

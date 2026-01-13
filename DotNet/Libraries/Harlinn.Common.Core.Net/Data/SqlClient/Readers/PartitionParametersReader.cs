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

public class PartitionParametersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[partition_parameters]";
    public const string TableName = "partition_parameters";
    public const string ShortName = "pp";
    public const string Sql = """
        SELECT
          pp.[function_id],
          pp.[parameter_id],
          pp.[system_type_id],
          pp.[max_length],
          pp.[Precision],
          pp.[Scale],
          pp.[collation_name],
          pp.[user_type_id]
        FROM
          [sys].[partition_parameters] pp
        """;

    public const int FUNCTIONID_FIELD_ID = 0;
    public const int PARAMETERID_FIELD_ID = 1;
    public const int SYSTEMTYPEID_FIELD_ID = 2;
    public const int MAXLENGTH_FIELD_ID = 3;
    public const int PRECISION_FIELD_ID = 4;
    public const int SCALE_FIELD_ID = 5;
    public const int COLLATIONNAME_FIELD_ID = 6;
    public const int USERTYPEID_FIELD_ID = 7;


    public PartitionParametersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public PartitionParametersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public PartitionParametersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int FunctionId
    {
        get
        {
            return base.GetInt32(FUNCTIONID_FIELD_ID);
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

    public string? CollationName
    {
        get
        {
            return base.GetNullableString(COLLATIONNAME_FIELD_ID);
        }
    }

    public int UserTypeId
    {
        get
        {
            return base.GetInt32(USERTYPEID_FIELD_ID);
        }
    }


    public Types.PartitionParametersDataType ToDataObject()
    {
        return new Types.PartitionParametersDataType(FunctionId,
            ParameterId,
            SystemTypeId,
            MaxLength,
            Precision,
            Scale,
            CollationName,
            UserTypeId);
    }

    public List<Types.PartitionParametersDataType> ToList()
    {
        var list = new List<Types.PartitionParametersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

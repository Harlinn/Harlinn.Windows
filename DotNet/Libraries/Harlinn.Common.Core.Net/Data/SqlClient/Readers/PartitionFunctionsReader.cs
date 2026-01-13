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

public class PartitionFunctionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[partition_functions]";
    public const string TableName = "partition_functions";
    public const string ShortName = "pf";
    public const string Sql = """
        SELECT
          pf.[Name],
          pf.[function_id],
          pf.[Type],
          pf.[type_desc],
          pf.[Fanout],
          pf.[boundary_value_on_right],
          pf.[is_system],
          pf.[create_date],
          pf.[modify_date]
        FROM
          [sys].[partition_functions] pf
        """;

    public const int NAME_FIELD_ID = 0;
    public const int FUNCTIONID_FIELD_ID = 1;
    public const int TYPE_FIELD_ID = 2;
    public const int TYPEDESC_FIELD_ID = 3;
    public const int FANOUT_FIELD_ID = 4;
    public const int BOUNDARYVALUEONRIGHT_FIELD_ID = 5;
    public const int ISSYSTEM_FIELD_ID = 6;
    public const int CREATEDATE_FIELD_ID = 7;
    public const int MODIFYDATE_FIELD_ID = 8;


    public PartitionFunctionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public PartitionFunctionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public PartitionFunctionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int FunctionId
    {
        get
        {
            return base.GetInt32(FUNCTIONID_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return base.GetString(TYPE_FIELD_ID);
        }
    }

    public string? TypeDesc
    {
        get
        {
            return base.GetNullableString(TYPEDESC_FIELD_ID);
        }
    }

    public int Fanout
    {
        get
        {
            return base.GetInt32(FANOUT_FIELD_ID);
        }
    }

    public bool BoundaryValueOnRight
    {
        get
        {
            return base.GetBoolean(BOUNDARYVALUEONRIGHT_FIELD_ID);
        }
    }

    public bool IsSystem
    {
        get
        {
            return base.GetBoolean(ISSYSTEM_FIELD_ID);
        }
    }

    public DateTime CreateDate
    {
        get
        {
            return base.GetDateTime(CREATEDATE_FIELD_ID);
        }
    }

    public DateTime ModifyDate
    {
        get
        {
            return base.GetDateTime(MODIFYDATE_FIELD_ID);
        }
    }


    public Types.PartitionFunctionsDataType ToDataObject()
    {
        return new Types.PartitionFunctionsDataType(Name,
            FunctionId,
            Type,
            TypeDesc,
            Fanout,
            BoundaryValueOnRight,
            IsSystem,
            CreateDate,
            ModifyDate);
    }

    public List<Types.PartitionFunctionsDataType> ToList()
    {
        var list = new List<Types.PartitionFunctionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

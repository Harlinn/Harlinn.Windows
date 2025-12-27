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

public class PartitionRangeValuesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[partition_range_values]";
    public const string TableName = "partition_range_values";
    public const string ShortName = "prv";
    public const string Sql = """
        SELECT
          prv.[function_id],
          prv.[boundary_id],
          prv.[parameter_id],
          prv.[Value]
        FROM
          [sys].[partition_range_values] prv
        """;

    public const int FUNCTIONID_FIELD_ID = 0;
    public const int BOUNDARYID_FIELD_ID = 1;
    public const int PARAMETERID_FIELD_ID = 2;
    public const int VALUE_FIELD_ID = 3;


    public PartitionRangeValuesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public PartitionRangeValuesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public PartitionRangeValuesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int BoundaryId
    {
        get
        {
            return base.GetInt32(BOUNDARYID_FIELD_ID);
        }
    }

    public int ParameterId
    {
        get
        {
            return base.GetInt32(PARAMETERID_FIELD_ID);
        }
    }

    public object? Value
    {
        get
        {
            return base.GetNullableValue(VALUE_FIELD_ID);
        }
    }


    public Types.PartitionRangeValuesDataType ToDataObject()
    {
        return new Types.PartitionRangeValuesDataType(FunctionId,
            BoundaryId,
            ParameterId,
            Value);
    }

    public List<Types.PartitionRangeValuesDataType> ToList()
    {
        var list = new List<Types.PartitionRangeValuesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

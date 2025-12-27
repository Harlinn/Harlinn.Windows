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

public class DmExecComputePoolsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_compute_pools]";
    public const string TableName = "dm_exec_compute_pools";
    public const string ShortName = "decp0";
    public const string Sql = """
        SELECT
          decp0.[compute_pool_id],
          decp0.[Name],
          decp0.[Location]
        FROM
          [sys].[dm_exec_compute_pools] decp0
        """;

    public const int COMPUTEPOOLID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int LOCATION_FIELD_ID = 2;


    public DmExecComputePoolsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecComputePoolsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecComputePoolsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ComputePoolId
    {
        get
        {
            return base.GetInt32(COMPUTEPOOLID_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public string Location
    {
        get
        {
            return base.GetString(LOCATION_FIELD_ID);
        }
    }


    public Types.DmExecComputePoolsDataType ToDataObject()
    {
        return new Types.DmExecComputePoolsDataType(ComputePoolId,
            Name,
            Location);
    }

    public List<Types.DmExecComputePoolsDataType> ToList()
    {
        var list = new List<Types.DmExecComputePoolsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

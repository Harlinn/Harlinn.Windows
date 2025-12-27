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

public class DmExecComputeNodesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_compute_nodes]";
    public const string TableName = "dm_exec_compute_nodes";
    public const string ShortName = "decn";
    public const string Sql = """
        SELECT
          decn.[compute_node_id],
          decn.[Type],
          decn.[Name],
          decn.[Address],
          decn.[compute_pool_id]
        FROM
          [sys].[dm_exec_compute_nodes] decn
        """;

    public const int COMPUTENODEID_FIELD_ID = 0;
    public const int TYPE_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int ADDRESS_FIELD_ID = 3;
    public const int COMPUTEPOOLID_FIELD_ID = 4;


    public DmExecComputeNodesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecComputeNodesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecComputeNodesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? ComputeNodeId
    {
        get
        {
            return base.GetNullableInt32(COMPUTENODEID_FIELD_ID);
        }
    }

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public string? Address
    {
        get
        {
            return base.GetNullableString(ADDRESS_FIELD_ID);
        }
    }

    public int ComputePoolId
    {
        get
        {
            return base.GetInt32(COMPUTEPOOLID_FIELD_ID);
        }
    }


    public Types.DmExecComputeNodesDataType ToDataObject()
    {
        return new Types.DmExecComputeNodesDataType(ComputeNodeId,
            Type,
            Name,
            Address,
            ComputePoolId);
    }

    public List<Types.DmExecComputeNodesDataType> ToList()
    {
        var list = new List<Types.DmExecComputeNodesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

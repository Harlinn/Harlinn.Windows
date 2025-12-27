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

public class DmExecDmsServicesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_dms_services]";
    public const string TableName = "dm_exec_dms_services";
    public const string ShortName = "deds";
    public const string Sql = """
        SELECT
          deds.[dms_core_id],
          deds.[compute_node_id],
          deds.[Status],
          deds.[compute_pool_id]
        FROM
          [sys].[dm_exec_dms_services] deds
        """;

    public const int DMSCOREID_FIELD_ID = 0;
    public const int COMPUTENODEID_FIELD_ID = 1;
    public const int STATUS_FIELD_ID = 2;
    public const int COMPUTEPOOLID_FIELD_ID = 3;


    public DmExecDmsServicesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecDmsServicesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecDmsServicesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? DmsCoreId
    {
        get
        {
            return base.GetNullableInt32(DMSCOREID_FIELD_ID);
        }
    }

    public int? ComputeNodeId
    {
        get
        {
            return base.GetNullableInt32(COMPUTENODEID_FIELD_ID);
        }
    }

    public string? Status
    {
        get
        {
            return base.GetNullableString(STATUS_FIELD_ID);
        }
    }

    public int ComputePoolId
    {
        get
        {
            return base.GetInt32(COMPUTEPOOLID_FIELD_ID);
        }
    }


    public Types.DmExecDmsServicesDataType ToDataObject()
    {
        return new Types.DmExecDmsServicesDataType(DmsCoreId,
            ComputeNodeId,
            Status,
            ComputePoolId);
    }

    public List<Types.DmExecDmsServicesDataType> ToList()
    {
        var list = new List<Types.DmExecDmsServicesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

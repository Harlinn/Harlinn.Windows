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

public class DmClrTasksReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_clr_tasks]";
    public const string TableName = "dm_clr_tasks";
    public const string ShortName = "dct";
    public const string Sql = """
        SELECT
          dct.[task_address],
          dct.[sos_task_address],
          dct.[appdomain_address],
          dct.[State],
          dct.[abort_state],
          dct.[Type],
          dct.[affinity_count],
          dct.[forced_yield_count]
        FROM
          [sys].[dm_clr_tasks] dct
        """;

    public const int TASKADDRESS_FIELD_ID = 0;
    public const int SOSTASKADDRESS_FIELD_ID = 1;
    public const int APPDOMAINADDRESS_FIELD_ID = 2;
    public const int STATE_FIELD_ID = 3;
    public const int ABORTSTATE_FIELD_ID = 4;
    public const int TYPE_FIELD_ID = 5;
    public const int AFFINITYCOUNT_FIELD_ID = 6;
    public const int FORCEDYIELDCOUNT_FIELD_ID = 7;


    public DmClrTasksReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmClrTasksReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmClrTasksReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[]? TaskAddress
    {
        get
        {
            return base.GetNullableBinary(TASKADDRESS_FIELD_ID);
        }
    }

    public byte[]? SosTaskAddress
    {
        get
        {
            return base.GetNullableBinary(SOSTASKADDRESS_FIELD_ID);
        }
    }

    public byte[]? AppdomainAddress
    {
        get
        {
            return base.GetNullableBinary(APPDOMAINADDRESS_FIELD_ID);
        }
    }

    public string? State
    {
        get
        {
            return base.GetNullableString(STATE_FIELD_ID);
        }
    }

    public string? AbortState
    {
        get
        {
            return base.GetNullableString(ABORTSTATE_FIELD_ID);
        }
    }

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
        }
    }

    public int? AffinityCount
    {
        get
        {
            return base.GetNullableInt32(AFFINITYCOUNT_FIELD_ID);
        }
    }

    public int? ForcedYieldCount
    {
        get
        {
            return base.GetNullableInt32(FORCEDYIELDCOUNT_FIELD_ID);
        }
    }


    public Types.DmClrTasksDataType ToDataObject()
    {
        return new Types.DmClrTasksDataType(TaskAddress,
            SosTaskAddress,
            AppdomainAddress,
            State,
            AbortState,
            Type,
            AffinityCount,
            ForcedYieldCount);
    }

    public List<Types.DmClrTasksDataType> ToList()
    {
        var list = new List<Types.DmClrTasksDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

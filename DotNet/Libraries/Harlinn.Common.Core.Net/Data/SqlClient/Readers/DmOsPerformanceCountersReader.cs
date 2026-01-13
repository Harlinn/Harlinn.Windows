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

public class DmOsPerformanceCountersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_performance_counters]";
    public const string TableName = "dm_os_performance_counters";
    public const string ShortName = "dopc";
    public const string Sql = """
        SELECT
          dopc.[object_name],
          dopc.[counter_name],
          dopc.[instance_name],
          dopc.[cntr_value],
          dopc.[cntr_type]
        FROM
          [sys].[dm_os_performance_counters] dopc
        """;

    public const int OBJECTNAME_FIELD_ID = 0;
    public const int COUNTERNAME_FIELD_ID = 1;
    public const int INSTANCENAME_FIELD_ID = 2;
    public const int CNTRVALUE_FIELD_ID = 3;
    public const int CNTRTYPE_FIELD_ID = 4;


    public DmOsPerformanceCountersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsPerformanceCountersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsPerformanceCountersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string ObjectName
    {
        get
        {
            return base.GetString(OBJECTNAME_FIELD_ID);
        }
    }

    public string CounterName
    {
        get
        {
            return base.GetString(COUNTERNAME_FIELD_ID);
        }
    }

    public string? InstanceName
    {
        get
        {
            return base.GetNullableString(INSTANCENAME_FIELD_ID);
        }
    }

    public long CntrValue
    {
        get
        {
            return base.GetInt64(CNTRVALUE_FIELD_ID);
        }
    }

    public int CntrType
    {
        get
        {
            return base.GetInt32(CNTRTYPE_FIELD_ID);
        }
    }


    public Types.DmOsPerformanceCountersDataType ToDataObject()
    {
        return new Types.DmOsPerformanceCountersDataType(ObjectName,
            CounterName,
            InstanceName,
            CntrValue,
            CntrType);
    }

    public List<Types.DmOsPerformanceCountersDataType> ToList()
    {
        var list = new List<Types.DmOsPerformanceCountersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class SysperfinfoReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysperfinfo]";
    public const string TableName = "sysperfinfo";
    public const string ShortName = "s9";
    public const string Sql = """
        SELECT
          s9.[object_name],
          s9.[counter_name],
          s9.[instance_name],
          s9.[cntr_value],
          s9.[cntr_type]
        FROM
          [sys].[sysperfinfo] s9
        """;

    public const int OBJECTNAME_FIELD_ID = 0;
    public const int COUNTERNAME_FIELD_ID = 1;
    public const int INSTANCENAME_FIELD_ID = 2;
    public const int CNTRVALUE_FIELD_ID = 3;
    public const int CNTRTYPE_FIELD_ID = 4;


    public SysperfinfoReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysperfinfoReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysperfinfoReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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


    public Types.SysperfinfoDataType ToDataObject()
    {
        return new Types.SysperfinfoDataType(ObjectName,
            CounterName,
            InstanceName,
            CntrValue,
            CntrType);
    }

    public List<Types.SysperfinfoDataType> ToList()
    {
        var list = new List<Types.SysperfinfoDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

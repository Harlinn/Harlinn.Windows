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

public class ServicesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[services]";
    public const string TableName = "services";
    public const string ShortName = "s1";
    public const string Sql = """
        SELECT
          s1.[Name],
          s1.[service_id],
          s1.[principal_id],
          s1.[service_queue_id]
        FROM
          [sys].[services] s1
        """;

    public const int NAME_FIELD_ID = 0;
    public const int SERVICEID_FIELD_ID = 1;
    public const int PRINCIPALID_FIELD_ID = 2;
    public const int SERVICEQUEUEID_FIELD_ID = 3;


    public ServicesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServicesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServicesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int ServiceId
    {
        get
        {
            return base.GetInt32(SERVICEID_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public int ServiceQueueId
    {
        get
        {
            return base.GetInt32(SERVICEQUEUEID_FIELD_ID);
        }
    }


    public Types.ServicesDataType ToDataObject()
    {
        return new Types.ServicesDataType(Name,
            ServiceId,
            PrincipalId,
            ServiceQueueId);
    }

    public List<Types.ServicesDataType> ToList()
    {
        var list = new List<Types.ServicesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class ServiceQueueUsagesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[service_queue_usages]";
    public const string TableName = "service_queue_usages";
    public const string ShortName = "squ";
    public const string Sql = """
        SELECT
          squ.[service_id],
          squ.[service_queue_id]
        FROM
          [sys].[service_queue_usages] squ
        """;

    public const int SERVICEID_FIELD_ID = 0;
    public const int SERVICEQUEUEID_FIELD_ID = 1;


    public ServiceQueueUsagesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServiceQueueUsagesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServiceQueueUsagesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ServiceId
    {
        get
        {
            return base.GetInt32(SERVICEID_FIELD_ID);
        }
    }

    public int ServiceQueueId
    {
        get
        {
            return base.GetInt32(SERVICEQUEUEID_FIELD_ID);
        }
    }


    public Types.ServiceQueueUsagesDataType ToDataObject()
    {
        return new Types.ServiceQueueUsagesDataType(ServiceId,
            ServiceQueueId);
    }

    public List<Types.ServiceQueueUsagesDataType> ToList()
    {
        var list = new List<Types.ServiceQueueUsagesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

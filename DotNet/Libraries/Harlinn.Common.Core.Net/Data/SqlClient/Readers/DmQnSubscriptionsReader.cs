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

public class DmQnSubscriptionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_qn_subscriptions]";
    public const string TableName = "dm_qn_subscriptions";
    public const string ShortName = "dqs";
    public const string Sql = """
        SELECT
          dqs.[Id],
          dqs.[database_id],
          dqs.[Sid],
          dqs.[object_id],
          dqs.[Created],
          dqs.[Timeout],
          dqs.[Status]
        FROM
          [sys].[dm_qn_subscriptions] dqs
        """;

    public const int ID_FIELD_ID = 0;
    public const int DATABASEID_FIELD_ID = 1;
    public const int SID_FIELD_ID = 2;
    public const int OBJECTID_FIELD_ID = 3;
    public const int CREATED_FIELD_ID = 4;
    public const int TIMEOUT_FIELD_ID = 5;
    public const int STATUS_FIELD_ID = 6;


    public DmQnSubscriptionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmQnSubscriptionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmQnSubscriptionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Id
    {
        get
        {
            return base.GetInt32(ID_FIELD_ID);
        }
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public byte[] Sid
    {
        get
        {
            return base.GetBinary(SID_FIELD_ID);
        }
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public DateTime Created
    {
        get
        {
            return base.GetDateTime(CREATED_FIELD_ID);
        }
    }

    public int Timeout
    {
        get
        {
            return base.GetInt32(TIMEOUT_FIELD_ID);
        }
    }

    public int Status
    {
        get
        {
            return base.GetInt32(STATUS_FIELD_ID);
        }
    }


    public Types.DmQnSubscriptionsDataType ToDataObject()
    {
        return new Types.DmQnSubscriptionsDataType(Id,
            DatabaseId,
            Sid,
            ObjectId,
            Created,
            Timeout,
            Status);
    }

    public List<Types.DmQnSubscriptionsDataType> ToList()
    {
        var list = new List<Types.DmQnSubscriptionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class DmTranGlobalTransactionsLogReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_global_transactions_log]";
    public const string TableName = "dm_tran_global_transactions_log";
    public const string ShortName = "dtgtl";
    public const string Sql = """
        SELECT
          dtgtl.[transaction_id],
          dtgtl.[time_utc],
          dtgtl.[Dropped],
          dtgtl.[resource_manager_id],
          dtgtl.[resource_manager_prepare_lsn],
          dtgtl.[resource_manager_ack_received],
          dtgtl.[commit_timestamp]
        FROM
          [sys].[dm_tran_global_transactions_log] dtgtl
        """;

    public const int TRANSACTIONID_FIELD_ID = 0;
    public const int TIMEUTC_FIELD_ID = 1;
    public const int DROPPED_FIELD_ID = 2;
    public const int RESOURCEMANAGERID_FIELD_ID = 3;
    public const int RESOURCEMANAGERPREPARELSN_FIELD_ID = 4;
    public const int RESOURCEMANAGERACKRECEIVED_FIELD_ID = 5;
    public const int COMMITTIMESTAMP_FIELD_ID = 6;


    public DmTranGlobalTransactionsLogReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranGlobalTransactionsLogReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranGlobalTransactionsLogReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid TransactionId
    {
        get
        {
            return base.GetGuid(TRANSACTIONID_FIELD_ID);
        }
    }

    public DateTime TimeUtc
    {
        get
        {
            return base.GetDateTime(TIMEUTC_FIELD_ID);
        }
    }

    public byte Dropped
    {
        get
        {
            return base.GetByte(DROPPED_FIELD_ID);
        }
    }

    public Guid ResourceManagerId
    {
        get
        {
            return base.GetGuid(RESOURCEMANAGERID_FIELD_ID);
        }
    }

    public string? ResourceManagerPrepareLsn
    {
        get
        {
            return base.GetNullableString(RESOURCEMANAGERPREPARELSN_FIELD_ID);
        }
    }

    public byte ResourceManagerAckReceived
    {
        get
        {
            return base.GetByte(RESOURCEMANAGERACKRECEIVED_FIELD_ID);
        }
    }

    public long CommitTimestamp
    {
        get
        {
            return base.GetInt64(COMMITTIMESTAMP_FIELD_ID);
        }
    }


    public Types.DmTranGlobalTransactionsLogDataType ToDataObject()
    {
        return new Types.DmTranGlobalTransactionsLogDataType(TransactionId,
            TimeUtc,
            Dropped,
            ResourceManagerId,
            ResourceManagerPrepareLsn,
            ResourceManagerAckReceived,
            CommitTimestamp);
    }

    public List<Types.DmTranGlobalTransactionsLogDataType> ToList()
    {
        var list = new List<Types.DmTranGlobalTransactionsLogDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

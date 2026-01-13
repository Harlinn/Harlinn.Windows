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

public class DmTranActiveTransactionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_active_transactions]";
    public const string TableName = "dm_tran_active_transactions";
    public const string ShortName = "dtat0";
    public const string Sql = """
        SELECT
          dtat0.[transaction_id],
          dtat0.[Name],
          dtat0.[transaction_begin_time],
          dtat0.[transaction_type],
          dtat0.[transaction_uow],
          dtat0.[transaction_state],
          dtat0.[transaction_status],
          dtat0.[transaction_status2],
          dtat0.[dtc_state],
          dtat0.[dtc_status],
          dtat0.[dtc_isolation_level],
          dtat0.[filestream_transaction_id]
        FROM
          [sys].[dm_tran_active_transactions] dtat0
        """;

    public const int TRANSACTIONID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int TRANSACTIONBEGINTIME_FIELD_ID = 2;
    public const int TRANSACTIONTYPE_FIELD_ID = 3;
    public const int TRANSACTIONUOW_FIELD_ID = 4;
    public const int TRANSACTIONSTATE_FIELD_ID = 5;
    public const int TRANSACTIONSTATUS_FIELD_ID = 6;
    public const int TRANSACTIONSTATUS2_FIELD_ID = 7;
    public const int DTCSTATE_FIELD_ID = 8;
    public const int DTCSTATUS_FIELD_ID = 9;
    public const int DTCISOLATIONLEVEL_FIELD_ID = 10;
    public const int FILESTREAMTRANSACTIONID_FIELD_ID = 11;


    public DmTranActiveTransactionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranActiveTransactionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranActiveTransactionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long TransactionId
    {
        get
        {
            return base.GetInt64(TRANSACTIONID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public DateTime TransactionBeginTime
    {
        get
        {
            return base.GetDateTime(TRANSACTIONBEGINTIME_FIELD_ID);
        }
    }

    public int TransactionType
    {
        get
        {
            return base.GetInt32(TRANSACTIONTYPE_FIELD_ID);
        }
    }

    public Guid? TransactionUow
    {
        get
        {
            return base.GetNullableGuid(TRANSACTIONUOW_FIELD_ID);
        }
    }

    public int TransactionState
    {
        get
        {
            return base.GetInt32(TRANSACTIONSTATE_FIELD_ID);
        }
    }

    public int TransactionStatus
    {
        get
        {
            return base.GetInt32(TRANSACTIONSTATUS_FIELD_ID);
        }
    }

    public int TransactionStatus2
    {
        get
        {
            return base.GetInt32(TRANSACTIONSTATUS2_FIELD_ID);
        }
    }

    public int DtcState
    {
        get
        {
            return base.GetInt32(DTCSTATE_FIELD_ID);
        }
    }

    public int DtcStatus
    {
        get
        {
            return base.GetInt32(DTCSTATUS_FIELD_ID);
        }
    }

    public int DtcIsolationLevel
    {
        get
        {
            return base.GetInt32(DTCISOLATIONLEVEL_FIELD_ID);
        }
    }

    public byte[]? FilestreamTransactionId
    {
        get
        {
            return base.GetNullableBinary(FILESTREAMTRANSACTIONID_FIELD_ID);
        }
    }


    public Types.DmTranActiveTransactionsDataType ToDataObject()
    {
        return new Types.DmTranActiveTransactionsDataType(TransactionId,
            Name,
            TransactionBeginTime,
            TransactionType,
            TransactionUow,
            TransactionState,
            TransactionStatus,
            TransactionStatus2,
            DtcState,
            DtcStatus,
            DtcIsolationLevel,
            FilestreamTransactionId);
    }

    public List<Types.DmTranActiveTransactionsDataType> ToList()
    {
        var list = new List<Types.DmTranActiveTransactionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

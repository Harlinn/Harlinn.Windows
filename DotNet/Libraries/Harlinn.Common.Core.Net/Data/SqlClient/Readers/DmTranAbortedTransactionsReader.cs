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

public class DmTranAbortedTransactionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_aborted_transactions]";
    public const string TableName = "dm_tran_aborted_transactions";
    public const string ShortName = "dtat";
    public const string Sql = """
        SELECT
          dtat.[transaction_id],
          dtat.[database_id],
          dtat.[begin_xact_lsn],
          dtat.[end_xact_lsn],
          dtat.[begin_time],
          dtat.[nest_aborted]
        FROM
          [sys].[dm_tran_aborted_transactions] dtat
        """;

    public const int TRANSACTIONID_FIELD_ID = 0;
    public const int DATABASEID_FIELD_ID = 1;
    public const int BEGINXACTLSN_FIELD_ID = 2;
    public const int ENDXACTLSN_FIELD_ID = 3;
    public const int BEGINTIME_FIELD_ID = 4;
    public const int NESTABORTED_FIELD_ID = 5;


    public DmTranAbortedTransactionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranAbortedTransactionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranAbortedTransactionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public short DatabaseId
    {
        get
        {
            return base.GetInt16(DATABASEID_FIELD_ID);
        }
    }

    public decimal? BeginXactLsn
    {
        get
        {
            return base.GetNullableDecimal(BEGINXACTLSN_FIELD_ID);
        }
    }

    public decimal? EndXactLsn
    {
        get
        {
            return base.GetNullableDecimal(ENDXACTLSN_FIELD_ID);
        }
    }

    public DateTime? BeginTime
    {
        get
        {
            return base.GetNullableDateTime(BEGINTIME_FIELD_ID);
        }
    }

    public bool? NestAborted
    {
        get
        {
            return base.GetNullableBoolean(NESTABORTED_FIELD_ID);
        }
    }


    public Types.DmTranAbortedTransactionsDataType ToDataObject()
    {
        return new Types.DmTranAbortedTransactionsDataType(TransactionId,
            DatabaseId,
            BeginXactLsn,
            EndXactLsn,
            BeginTime,
            NestAborted);
    }

    public List<Types.DmTranAbortedTransactionsDataType> ToList()
    {
        var list = new List<Types.DmTranAbortedTransactionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

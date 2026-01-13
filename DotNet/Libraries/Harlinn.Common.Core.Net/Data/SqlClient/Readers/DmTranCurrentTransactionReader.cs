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

public class DmTranCurrentTransactionReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_current_transaction]";
    public const string TableName = "dm_tran_current_transaction";
    public const string ShortName = "dtct0";
    public const string Sql = """
        SELECT
          dtct0.[transaction_id],
          dtct0.[transaction_sequence_num],
          dtct0.[transaction_is_snapshot],
          dtct0.[first_snapshot_sequence_num],
          dtct0.[last_transaction_sequence_num],
          dtct0.[first_useful_sequence_num]
        FROM
          [sys].[dm_tran_current_transaction] dtct0
        """;

    public const int TRANSACTIONID_FIELD_ID = 0;
    public const int TRANSACTIONSEQUENCENUM_FIELD_ID = 1;
    public const int TRANSACTIONISSNAPSHOT_FIELD_ID = 2;
    public const int FIRSTSNAPSHOTSEQUENCENUM_FIELD_ID = 3;
    public const int LASTTRANSACTIONSEQUENCENUM_FIELD_ID = 4;
    public const int FIRSTUSEFULSEQUENCENUM_FIELD_ID = 5;


    public DmTranCurrentTransactionReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranCurrentTransactionReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranCurrentTransactionReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long? TransactionId
    {
        get
        {
            return base.GetNullableInt64(TRANSACTIONID_FIELD_ID);
        }
    }

    public long? TransactionSequenceNum
    {
        get
        {
            return base.GetNullableInt64(TRANSACTIONSEQUENCENUM_FIELD_ID);
        }
    }

    public bool? TransactionIsSnapshot
    {
        get
        {
            return base.GetNullableBoolean(TRANSACTIONISSNAPSHOT_FIELD_ID);
        }
    }

    public long? FirstSnapshotSequenceNum
    {
        get
        {
            return base.GetNullableInt64(FIRSTSNAPSHOTSEQUENCENUM_FIELD_ID);
        }
    }

    public long? LastTransactionSequenceNum
    {
        get
        {
            return base.GetNullableInt64(LASTTRANSACTIONSEQUENCENUM_FIELD_ID);
        }
    }

    public long? FirstUsefulSequenceNum
    {
        get
        {
            return base.GetNullableInt64(FIRSTUSEFULSEQUENCENUM_FIELD_ID);
        }
    }


    public Types.DmTranCurrentTransactionDataType ToDataObject()
    {
        return new Types.DmTranCurrentTransactionDataType(TransactionId,
            TransactionSequenceNum,
            TransactionIsSnapshot,
            FirstSnapshotSequenceNum,
            LastTransactionSequenceNum,
            FirstUsefulSequenceNum);
    }

    public List<Types.DmTranCurrentTransactionDataType> ToList()
    {
        var list = new List<Types.DmTranCurrentTransactionDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

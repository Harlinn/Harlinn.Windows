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

public class DmTranTransactionsSnapshotReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_transactions_snapshot]";
    public const string TableName = "dm_tran_transactions_snapshot";
    public const string ShortName = "dtts";
    public const string Sql = """
        SELECT
          dtts.[transaction_sequence_num],
          dtts.[snapshot_id],
          dtts.[snapshot_sequence_num]
        FROM
          [sys].[dm_tran_transactions_snapshot] dtts
        """;

    public const int TRANSACTIONSEQUENCENUM_FIELD_ID = 0;
    public const int SNAPSHOTID_FIELD_ID = 1;
    public const int SNAPSHOTSEQUENCENUM_FIELD_ID = 2;


    public DmTranTransactionsSnapshotReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranTransactionsSnapshotReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranTransactionsSnapshotReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long? TransactionSequenceNum
    {
        get
        {
            return base.GetNullableInt64(TRANSACTIONSEQUENCENUM_FIELD_ID);
        }
    }

    public int? SnapshotId
    {
        get
        {
            return base.GetNullableInt32(SNAPSHOTID_FIELD_ID);
        }
    }

    public long? SnapshotSequenceNum
    {
        get
        {
            return base.GetNullableInt64(SNAPSHOTSEQUENCENUM_FIELD_ID);
        }
    }


    public Types.DmTranTransactionsSnapshotDataType ToDataObject()
    {
        return new Types.DmTranTransactionsSnapshotDataType(TransactionSequenceNum,
            SnapshotId,
            SnapshotSequenceNum);
    }

    public List<Types.DmTranTransactionsSnapshotDataType> ToList()
    {
        var list = new List<Types.DmTranTransactionsSnapshotDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

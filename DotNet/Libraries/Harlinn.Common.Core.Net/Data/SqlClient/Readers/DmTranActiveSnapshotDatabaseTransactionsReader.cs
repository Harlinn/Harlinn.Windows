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

public class DmTranActiveSnapshotDatabaseTransactionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_active_snapshot_database_transactions]";
    public const string TableName = "dm_tran_active_snapshot_database_transactions";
    public const string ShortName = "dtasdt";
    public const string Sql = """
        SELECT
          dtasdt.[transaction_id],
          dtasdt.[transaction_sequence_num],
          dtasdt.[commit_sequence_num],
          dtasdt.[session_id],
          dtasdt.[is_snapshot],
          dtasdt.[first_snapshot_sequence_num],
          dtasdt.[max_version_chain_traversed],
          dtasdt.[average_version_chain_traversed],
          dtasdt.[elapsed_time_seconds]
        FROM
          [sys].[dm_tran_active_snapshot_database_transactions] dtasdt
        """;

    public const int TRANSACTIONID_FIELD_ID = 0;
    public const int TRANSACTIONSEQUENCENUM_FIELD_ID = 1;
    public const int COMMITSEQUENCENUM_FIELD_ID = 2;
    public const int SESSIONID_FIELD_ID = 3;
    public const int ISSNAPSHOT_FIELD_ID = 4;
    public const int FIRSTSNAPSHOTSEQUENCENUM_FIELD_ID = 5;
    public const int MAXVERSIONCHAINTRAVERSED_FIELD_ID = 6;
    public const int AVERAGEVERSIONCHAINTRAVERSED_FIELD_ID = 7;
    public const int ELAPSEDTIMESECONDS_FIELD_ID = 8;


    public DmTranActiveSnapshotDatabaseTransactionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranActiveSnapshotDatabaseTransactionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranActiveSnapshotDatabaseTransactionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public long? CommitSequenceNum
    {
        get
        {
            return base.GetNullableInt64(COMMITSEQUENCENUM_FIELD_ID);
        }
    }

    public int? SessionId
    {
        get
        {
            return base.GetNullableInt32(SESSIONID_FIELD_ID);
        }
    }

    public bool? IsSnapshot
    {
        get
        {
            return base.GetNullableBoolean(ISSNAPSHOT_FIELD_ID);
        }
    }

    public long? FirstSnapshotSequenceNum
    {
        get
        {
            return base.GetNullableInt64(FIRSTSNAPSHOTSEQUENCENUM_FIELD_ID);
        }
    }

    public int? MaxVersionChainTraversed
    {
        get
        {
            return base.GetNullableInt32(MAXVERSIONCHAINTRAVERSED_FIELD_ID);
        }
    }

    public double? AverageVersionChainTraversed
    {
        get
        {
            return base.GetNullableDouble(AVERAGEVERSIONCHAINTRAVERSED_FIELD_ID);
        }
    }

    public long? ElapsedTimeSeconds
    {
        get
        {
            return base.GetNullableInt64(ELAPSEDTIMESECONDS_FIELD_ID);
        }
    }


    public Types.DmTranActiveSnapshotDatabaseTransactionsDataType ToDataObject()
    {
        return new Types.DmTranActiveSnapshotDatabaseTransactionsDataType(TransactionId,
            TransactionSequenceNum,
            CommitSequenceNum,
            SessionId,
            IsSnapshot,
            FirstSnapshotSequenceNum,
            MaxVersionChainTraversed,
            AverageVersionChainTraversed,
            ElapsedTimeSeconds);
    }

    public List<Types.DmTranActiveSnapshotDatabaseTransactionsDataType> ToList()
    {
        var list = new List<Types.DmTranActiveSnapshotDatabaseTransactionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

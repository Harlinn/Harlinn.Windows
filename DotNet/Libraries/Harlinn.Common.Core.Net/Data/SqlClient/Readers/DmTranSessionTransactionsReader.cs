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

public class DmTranSessionTransactionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_session_transactions]";
    public const string TableName = "dm_tran_session_transactions";
    public const string ShortName = "dtst";
    public const string Sql = """
        SELECT
          dtst.[session_id],
          dtst.[transaction_id],
          dtst.[transaction_descriptor],
          dtst.[enlist_count],
          dtst.[is_user_transaction],
          dtst.[is_local],
          dtst.[is_enlisted],
          dtst.[is_bound],
          dtst.[open_transaction_count]
        FROM
          [sys].[dm_tran_session_transactions] dtst
        """;

    public const int SESSIONID_FIELD_ID = 0;
    public const int TRANSACTIONID_FIELD_ID = 1;
    public const int TRANSACTIONDESCRIPTOR_FIELD_ID = 2;
    public const int ENLISTCOUNT_FIELD_ID = 3;
    public const int ISUSERTRANSACTION_FIELD_ID = 4;
    public const int ISLOCAL_FIELD_ID = 5;
    public const int ISENLISTED_FIELD_ID = 6;
    public const int ISBOUND_FIELD_ID = 7;
    public const int OPENTRANSACTIONCOUNT_FIELD_ID = 8;


    public DmTranSessionTransactionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranSessionTransactionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranSessionTransactionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int SessionId
    {
        get
        {
            return base.GetInt32(SESSIONID_FIELD_ID);
        }
    }

    public long TransactionId
    {
        get
        {
            return base.GetInt64(TRANSACTIONID_FIELD_ID);
        }
    }

    public byte[] TransactionDescriptor
    {
        get
        {
            return base.GetBinary(TRANSACTIONDESCRIPTOR_FIELD_ID);
        }
    }

    public int EnlistCount
    {
        get
        {
            return base.GetInt32(ENLISTCOUNT_FIELD_ID);
        }
    }

    public bool IsUserTransaction
    {
        get
        {
            return base.GetBoolean(ISUSERTRANSACTION_FIELD_ID);
        }
    }

    public bool IsLocal
    {
        get
        {
            return base.GetBoolean(ISLOCAL_FIELD_ID);
        }
    }

    public bool IsEnlisted
    {
        get
        {
            return base.GetBoolean(ISENLISTED_FIELD_ID);
        }
    }

    public bool IsBound
    {
        get
        {
            return base.GetBoolean(ISBOUND_FIELD_ID);
        }
    }

    public int OpenTransactionCount
    {
        get
        {
            return base.GetInt32(OPENTRANSACTIONCOUNT_FIELD_ID);
        }
    }


    public Types.DmTranSessionTransactionsDataType ToDataObject()
    {
        return new Types.DmTranSessionTransactionsDataType(SessionId,
            TransactionId,
            TransactionDescriptor,
            EnlistCount,
            IsUserTransaction,
            IsLocal,
            IsEnlisted,
            IsBound,
            OpenTransactionCount);
    }

    public List<Types.DmTranSessionTransactionsDataType> ToList()
    {
        var list = new List<Types.DmTranSessionTransactionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

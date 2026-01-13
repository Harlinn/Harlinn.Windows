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

public class DmTranGlobalRecoveryTransactionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_global_recovery_transactions]";
    public const string TableName = "dm_tran_global_recovery_transactions";
    public const string ShortName = "dtgrt";
    public const string Sql = """
        SELECT
          dtgrt.[database_id],
          dtgrt.[transaction_uow],
          dtgrt.[transaction_manager_dbid],
          dtgrt.[transaction_manager_rmid],
          dtgrt.[transaction_manager_server_name],
          dtgrt.[transaction_manager_database_name]
        FROM
          [sys].[dm_tran_global_recovery_transactions] dtgrt
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int TRANSACTIONUOW_FIELD_ID = 1;
    public const int TRANSACTIONMANAGERDBID_FIELD_ID = 2;
    public const int TRANSACTIONMANAGERRMID_FIELD_ID = 3;
    public const int TRANSACTIONMANAGERSERVERNAME_FIELD_ID = 4;
    public const int TRANSACTIONMANAGERDATABASENAME_FIELD_ID = 5;


    public DmTranGlobalRecoveryTransactionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranGlobalRecoveryTransactionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranGlobalRecoveryTransactionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public Guid TransactionUow
    {
        get
        {
            return base.GetGuid(TRANSACTIONUOW_FIELD_ID);
        }
    }

    public int TransactionManagerDbid
    {
        get
        {
            return base.GetInt32(TRANSACTIONMANAGERDBID_FIELD_ID);
        }
    }

    public Guid TransactionManagerRmid
    {
        get
        {
            return base.GetGuid(TRANSACTIONMANAGERRMID_FIELD_ID);
        }
    }

    public string? TransactionManagerServerName
    {
        get
        {
            return base.GetNullableString(TRANSACTIONMANAGERSERVERNAME_FIELD_ID);
        }
    }

    public string? TransactionManagerDatabaseName
    {
        get
        {
            return base.GetNullableString(TRANSACTIONMANAGERDATABASENAME_FIELD_ID);
        }
    }


    public Types.DmTranGlobalRecoveryTransactionsDataType ToDataObject()
    {
        return new Types.DmTranGlobalRecoveryTransactionsDataType(DatabaseId,
            TransactionUow,
            TransactionManagerDbid,
            TransactionManagerRmid,
            TransactionManagerServerName,
            TransactionManagerDatabaseName);
    }

    public List<Types.DmTranGlobalRecoveryTransactionsDataType> ToList()
    {
        var list = new List<Types.DmTranGlobalRecoveryTransactionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

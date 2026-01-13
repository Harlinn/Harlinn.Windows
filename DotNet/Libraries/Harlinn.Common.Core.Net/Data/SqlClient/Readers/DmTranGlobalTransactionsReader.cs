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

public class DmTranGlobalTransactionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_global_transactions]";
    public const string TableName = "dm_tran_global_transactions";
    public const string ShortName = "dtgt";
    public const string Sql = """
        SELECT
          dtgt.[transaction_id],
          dtgt.[database_id],
          dtgt.[transaction_state],
          dtgt.[resource_manager_id],
          dtgt.[resource_manager_server],
          dtgt.[resource_manager_database],
          dtgt.[resource_manager_dbid],
          dtgt.[resource_manager_state],
          dtgt.[resource_prepare_lsn],
          dtgt.[resource_phase_1_time],
          dtgt.[resource_phase_2_time],
          dtgt.[transaction_phase_1_time],
          dtgt.[transaction_phase_2_time],
          dtgt.[transaction_total_time],
          dtgt.[transaction_diag_status],
          dtgt.[resource_manager_diag_status],
          dtgt.[max_csn]
        FROM
          [sys].[dm_tran_global_transactions] dtgt
        """;

    public const int TRANSACTIONID_FIELD_ID = 0;
    public const int DATABASEID_FIELD_ID = 1;
    public const int TRANSACTIONSTATE_FIELD_ID = 2;
    public const int RESOURCEMANAGERID_FIELD_ID = 3;
    public const int RESOURCEMANAGERSERVER_FIELD_ID = 4;
    public const int RESOURCEMANAGERDATABASE_FIELD_ID = 5;
    public const int RESOURCEMANAGERDBID_FIELD_ID = 6;
    public const int RESOURCEMANAGERSTATE_FIELD_ID = 7;
    public const int RESOURCEPREPARELSN_FIELD_ID = 8;
    public const int RESOURCEPHASE1TIME_FIELD_ID = 9;
    public const int RESOURCEPHASE2TIME_FIELD_ID = 10;
    public const int TRANSACTIONPHASE1TIME_FIELD_ID = 11;
    public const int TRANSACTIONPHASE2TIME_FIELD_ID = 12;
    public const int TRANSACTIONTOTALTIME_FIELD_ID = 13;
    public const int TRANSACTIONDIAGSTATUS_FIELD_ID = 14;
    public const int RESOURCEMANAGERDIAGSTATUS_FIELD_ID = 15;
    public const int MAXCSN_FIELD_ID = 16;


    public DmTranGlobalTransactionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranGlobalTransactionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranGlobalTransactionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public int TransactionState
    {
        get
        {
            return base.GetInt32(TRANSACTIONSTATE_FIELD_ID);
        }
    }

    public Guid ResourceManagerId
    {
        get
        {
            return base.GetGuid(RESOURCEMANAGERID_FIELD_ID);
        }
    }

    public string? ResourceManagerServer
    {
        get
        {
            return base.GetNullableString(RESOURCEMANAGERSERVER_FIELD_ID);
        }
    }

    public string? ResourceManagerDatabase
    {
        get
        {
            return base.GetNullableString(RESOURCEMANAGERDATABASE_FIELD_ID);
        }
    }

    public int ResourceManagerDbid
    {
        get
        {
            return base.GetInt32(RESOURCEMANAGERDBID_FIELD_ID);
        }
    }

    public int ResourceManagerState
    {
        get
        {
            return base.GetInt32(RESOURCEMANAGERSTATE_FIELD_ID);
        }
    }

    public string? ResourcePrepareLsn
    {
        get
        {
            return base.GetNullableString(RESOURCEPREPARELSN_FIELD_ID);
        }
    }

    public long ResourcePhase1Time
    {
        get
        {
            return base.GetInt64(RESOURCEPHASE1TIME_FIELD_ID);
        }
    }

    public long ResourcePhase2Time
    {
        get
        {
            return base.GetInt64(RESOURCEPHASE2TIME_FIELD_ID);
        }
    }

    public long TransactionPhase1Time
    {
        get
        {
            return base.GetInt64(TRANSACTIONPHASE1TIME_FIELD_ID);
        }
    }

    public long TransactionPhase2Time
    {
        get
        {
            return base.GetInt64(TRANSACTIONPHASE2TIME_FIELD_ID);
        }
    }

    public long TransactionTotalTime
    {
        get
        {
            return base.GetInt64(TRANSACTIONTOTALTIME_FIELD_ID);
        }
    }

    public int TransactionDiagStatus
    {
        get
        {
            return base.GetInt32(TRANSACTIONDIAGSTATUS_FIELD_ID);
        }
    }

    public int ResourceManagerDiagStatus
    {
        get
        {
            return base.GetInt32(RESOURCEMANAGERDIAGSTATUS_FIELD_ID);
        }
    }

    public long MaxCsn
    {
        get
        {
            return base.GetInt64(MAXCSN_FIELD_ID);
        }
    }


    public Types.DmTranGlobalTransactionsDataType ToDataObject()
    {
        return new Types.DmTranGlobalTransactionsDataType(TransactionId,
            DatabaseId,
            TransactionState,
            ResourceManagerId,
            ResourceManagerServer,
            ResourceManagerDatabase,
            ResourceManagerDbid,
            ResourceManagerState,
            ResourcePrepareLsn,
            ResourcePhase1Time,
            ResourcePhase2Time,
            TransactionPhase1Time,
            TransactionPhase2Time,
            TransactionTotalTime,
            TransactionDiagStatus,
            ResourceManagerDiagStatus,
            MaxCsn);
    }

    public List<Types.DmTranGlobalTransactionsDataType> ToList()
    {
        var list = new List<Types.DmTranGlobalTransactionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

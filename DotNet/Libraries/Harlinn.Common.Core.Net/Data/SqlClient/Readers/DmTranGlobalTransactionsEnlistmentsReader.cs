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

public class DmTranGlobalTransactionsEnlistmentsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_global_transactions_enlistments]";
    public const string TableName = "dm_tran_global_transactions_enlistments";
    public const string ShortName = "dtgte";
    public const string Sql = """
        SELECT
          dtgte.[transaction_id],
          dtgte.[database_id],
          dtgte.[iso_level],
          dtgte.[can_commit],
          dtgte.[enlistment_state],
          dtgte.[resource_manager_id],
          dtgte.[server_name],
          dtgte.[database_name],
          dtgte.[transaction_manager_server_name],
          dtgte.[transaction_manager_database_name],
          dtgte.[transaction_manager_database_id],
          dtgte.[transaction_manager_rmid],
          dtgte.[prepare_lsn],
          dtgte.[snapshot_timestamp],
          dtgte.[oldest_active_lsn],
          dtgte.[prepare_elapsed_time],
          dtgte.[object_ref_count],
          dtgte.[transaction_timeout],
          dtgte.[diag_status]
        FROM
          [sys].[dm_tran_global_transactions_enlistments] dtgte
        """;

    public const int TRANSACTIONID_FIELD_ID = 0;
    public const int DATABASEID_FIELD_ID = 1;
    public const int ISOLEVEL_FIELD_ID = 2;
    public const int CANCOMMIT_FIELD_ID = 3;
    public const int ENLISTMENTSTATE_FIELD_ID = 4;
    public const int RESOURCEMANAGERID_FIELD_ID = 5;
    public const int SERVERNAME_FIELD_ID = 6;
    public const int DATABASENAME_FIELD_ID = 7;
    public const int TRANSACTIONMANAGERSERVERNAME_FIELD_ID = 8;
    public const int TRANSACTIONMANAGERDATABASENAME_FIELD_ID = 9;
    public const int TRANSACTIONMANAGERDATABASEID_FIELD_ID = 10;
    public const int TRANSACTIONMANAGERRMID_FIELD_ID = 11;
    public const int PREPARELSN_FIELD_ID = 12;
    public const int SNAPSHOTTIMESTAMP_FIELD_ID = 13;
    public const int OLDESTACTIVELSN_FIELD_ID = 14;
    public const int PREPAREELAPSEDTIME_FIELD_ID = 15;
    public const int OBJECTREFCOUNT_FIELD_ID = 16;
    public const int TRANSACTIONTIMEOUT_FIELD_ID = 17;
    public const int DIAGSTATUS_FIELD_ID = 18;


    public DmTranGlobalTransactionsEnlistmentsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranGlobalTransactionsEnlistmentsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranGlobalTransactionsEnlistmentsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int IsoLevel
    {
        get
        {
            return base.GetInt32(ISOLEVEL_FIELD_ID);
        }
    }

    public int CanCommit
    {
        get
        {
            return base.GetInt32(CANCOMMIT_FIELD_ID);
        }
    }

    public int EnlistmentState
    {
        get
        {
            return base.GetInt32(ENLISTMENTSTATE_FIELD_ID);
        }
    }

    public Guid ResourceManagerId
    {
        get
        {
            return base.GetGuid(RESOURCEMANAGERID_FIELD_ID);
        }
    }

    public string? ServerName
    {
        get
        {
            return base.GetNullableString(SERVERNAME_FIELD_ID);
        }
    }

    public string? DatabaseName
    {
        get
        {
            return base.GetNullableString(DATABASENAME_FIELD_ID);
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

    public int TransactionManagerDatabaseId
    {
        get
        {
            return base.GetInt32(TRANSACTIONMANAGERDATABASEID_FIELD_ID);
        }
    }

    public Guid TransactionManagerRmid
    {
        get
        {
            return base.GetGuid(TRANSACTIONMANAGERRMID_FIELD_ID);
        }
    }

    public string? PrepareLsn
    {
        get
        {
            return base.GetNullableString(PREPARELSN_FIELD_ID);
        }
    }

    public long SnapshotTimestamp
    {
        get
        {
            return base.GetInt64(SNAPSHOTTIMESTAMP_FIELD_ID);
        }
    }

    public string? OldestActiveLsn
    {
        get
        {
            return base.GetNullableString(OLDESTACTIVELSN_FIELD_ID);
        }
    }

    public long PrepareElapsedTime
    {
        get
        {
            return base.GetInt64(PREPAREELAPSEDTIME_FIELD_ID);
        }
    }

    public int ObjectRefCount
    {
        get
        {
            return base.GetInt32(OBJECTREFCOUNT_FIELD_ID);
        }
    }

    public int TransactionTimeout
    {
        get
        {
            return base.GetInt32(TRANSACTIONTIMEOUT_FIELD_ID);
        }
    }

    public int DiagStatus
    {
        get
        {
            return base.GetInt32(DIAGSTATUS_FIELD_ID);
        }
    }


    public Types.DmTranGlobalTransactionsEnlistmentsDataType ToDataObject()
    {
        return new Types.DmTranGlobalTransactionsEnlistmentsDataType(TransactionId,
            DatabaseId,
            IsoLevel,
            CanCommit,
            EnlistmentState,
            ResourceManagerId,
            ServerName,
            DatabaseName,
            TransactionManagerServerName,
            TransactionManagerDatabaseName,
            TransactionManagerDatabaseId,
            TransactionManagerRmid,
            PrepareLsn,
            SnapshotTimestamp,
            OldestActiveLsn,
            PrepareElapsedTime,
            ObjectRefCount,
            TransactionTimeout,
            DiagStatus);
    }

    public List<Types.DmTranGlobalTransactionsEnlistmentsDataType> ToList()
    {
        var list = new List<Types.DmTranGlobalTransactionsEnlistmentsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

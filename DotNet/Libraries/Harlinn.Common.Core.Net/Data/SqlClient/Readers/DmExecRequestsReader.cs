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

public class DmExecRequestsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_requests]";
    public const string TableName = "dm_exec_requests";
    public const string ShortName = "der";
    public const string Sql = """
        SELECT
          der.[session_id],
          der.[request_id],
          der.[start_time],
          der.[Status],
          der.[Command],
          der.[sql_handle],
          der.[statement_start_offset],
          der.[statement_end_offset],
          der.[plan_handle],
          der.[database_id],
          der.[user_id],
          der.[connection_id],
          der.[blocking_session_id],
          der.[wait_type],
          der.[wait_time],
          der.[last_wait_type],
          der.[wait_resource],
          der.[open_transaction_count],
          der.[open_resultset_count],
          der.[transaction_id],
          der.[context_info],
          der.[percent_complete],
          der.[estimated_completion_time],
          der.[cpu_time],
          der.[total_elapsed_time],
          der.[scheduler_id],
          der.[task_address],
          der.[Reads],
          der.[Writes],
          der.[logical_reads],
          der.[text_size],
          der.[Language],
          der.[date_format],
          der.[date_first],
          der.[quoted_identifier],
          der.[Arithabort],
          der.[ansi_null_dflt_on],
          der.[ansi_defaults],
          der.[ansi_warnings],
          der.[ansi_padding],
          der.[ansi_nulls],
          der.[concat_null_yields_null],
          der.[transaction_isolation_level],
          der.[lock_timeout],
          der.[deadlock_priority],
          der.[row_count],
          der.[prev_error],
          der.[nest_level],
          der.[granted_query_memory],
          der.[executing_managed_code],
          der.[group_id],
          der.[query_hash],
          der.[query_plan_hash],
          der.[statement_sql_handle],
          der.[statement_context_id],
          der.[Dop],
          der.[parallel_worker_count],
          der.[external_script_request_id],
          der.[is_resumable],
          der.[page_resource],
          der.[page_server_reads]
        FROM
          [sys].[dm_exec_requests] der
        """;

    public const int SESSIONID_FIELD_ID = 0;
    public const int REQUESTID_FIELD_ID = 1;
    public const int STARTTIME_FIELD_ID = 2;
    public const int STATUS_FIELD_ID = 3;
    public const int COMMAND_FIELD_ID = 4;
    public const int SQLHANDLE_FIELD_ID = 5;
    public const int STATEMENTSTARTOFFSET_FIELD_ID = 6;
    public const int STATEMENTENDOFFSET_FIELD_ID = 7;
    public const int PLANHANDLE_FIELD_ID = 8;
    public const int DATABASEID_FIELD_ID = 9;
    public const int USERID_FIELD_ID = 10;
    public const int CONNECTIONID_FIELD_ID = 11;
    public const int BLOCKINGSESSIONID_FIELD_ID = 12;
    public const int WAITTYPE_FIELD_ID = 13;
    public const int WAITTIME_FIELD_ID = 14;
    public const int LASTWAITTYPE_FIELD_ID = 15;
    public const int WAITRESOURCE_FIELD_ID = 16;
    public const int OPENTRANSACTIONCOUNT_FIELD_ID = 17;
    public const int OPENRESULTSETCOUNT_FIELD_ID = 18;
    public const int TRANSACTIONID_FIELD_ID = 19;
    public const int CONTEXTINFO_FIELD_ID = 20;
    public const int PERCENTCOMPLETE_FIELD_ID = 21;
    public const int ESTIMATEDCOMPLETIONTIME_FIELD_ID = 22;
    public const int CPUTIME_FIELD_ID = 23;
    public const int TOTALELAPSEDTIME_FIELD_ID = 24;
    public const int SCHEDULERID_FIELD_ID = 25;
    public const int TASKADDRESS_FIELD_ID = 26;
    public const int READS_FIELD_ID = 27;
    public const int WRITES_FIELD_ID = 28;
    public const int LOGICALREADS_FIELD_ID = 29;
    public const int TEXTSIZE_FIELD_ID = 30;
    public const int LANGUAGE_FIELD_ID = 31;
    public const int DATEFORMAT_FIELD_ID = 32;
    public const int DATEFIRST_FIELD_ID = 33;
    public const int QUOTEDIDENTIFIER_FIELD_ID = 34;
    public const int ARITHABORT_FIELD_ID = 35;
    public const int ANSINULLDFLTON_FIELD_ID = 36;
    public const int ANSIDEFAULTS_FIELD_ID = 37;
    public const int ANSIWARNINGS_FIELD_ID = 38;
    public const int ANSIPADDING_FIELD_ID = 39;
    public const int ANSINULLS_FIELD_ID = 40;
    public const int CONCATNULLYIELDSNULL_FIELD_ID = 41;
    public const int TRANSACTIONISOLATIONLEVEL_FIELD_ID = 42;
    public const int LOCKTIMEOUT_FIELD_ID = 43;
    public const int DEADLOCKPRIORITY_FIELD_ID = 44;
    public const int ROWCOUNT_FIELD_ID = 45;
    public const int PREVERROR_FIELD_ID = 46;
    public const int NESTLEVEL_FIELD_ID = 47;
    public const int GRANTEDQUERYMEMORY_FIELD_ID = 48;
    public const int EXECUTINGMANAGEDCODE_FIELD_ID = 49;
    public const int GROUPID_FIELD_ID = 50;
    public const int QUERYHASH_FIELD_ID = 51;
    public const int QUERYPLANHASH_FIELD_ID = 52;
    public const int STATEMENTSQLHANDLE_FIELD_ID = 53;
    public const int STATEMENTCONTEXTID_FIELD_ID = 54;
    public const int DOP_FIELD_ID = 55;
    public const int PARALLELWORKERCOUNT_FIELD_ID = 56;
    public const int EXTERNALSCRIPTREQUESTID_FIELD_ID = 57;
    public const int ISRESUMABLE_FIELD_ID = 58;
    public const int PAGERESOURCE_FIELD_ID = 59;
    public const int PAGESERVERREADS_FIELD_ID = 60;


    public DmExecRequestsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecRequestsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecRequestsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short SessionId
    {
        get
        {
            return base.GetInt16(SESSIONID_FIELD_ID);
        }
    }

    public int RequestId
    {
        get
        {
            return base.GetInt32(REQUESTID_FIELD_ID);
        }
    }

    public DateTime StartTime
    {
        get
        {
            return base.GetDateTime(STARTTIME_FIELD_ID);
        }
    }

    public string Status
    {
        get
        {
            return base.GetString(STATUS_FIELD_ID);
        }
    }

    public string Command
    {
        get
        {
            return base.GetString(COMMAND_FIELD_ID);
        }
    }

    public byte[]? SqlHandle
    {
        get
        {
            return base.GetNullableBinary(SQLHANDLE_FIELD_ID);
        }
    }

    public int? StatementStartOffset
    {
        get
        {
            return base.GetNullableInt32(STATEMENTSTARTOFFSET_FIELD_ID);
        }
    }

    public int? StatementEndOffset
    {
        get
        {
            return base.GetNullableInt32(STATEMENTENDOFFSET_FIELD_ID);
        }
    }

    public byte[]? PlanHandle
    {
        get
        {
            return base.GetNullableBinary(PLANHANDLE_FIELD_ID);
        }
    }

    public short DatabaseId
    {
        get
        {
            return base.GetInt16(DATABASEID_FIELD_ID);
        }
    }

    public int UserId
    {
        get
        {
            return base.GetInt32(USERID_FIELD_ID);
        }
    }

    public Guid? ConnectionId
    {
        get
        {
            return base.GetNullableGuid(CONNECTIONID_FIELD_ID);
        }
    }

    public short? BlockingSessionId
    {
        get
        {
            return base.GetNullableInt16(BLOCKINGSESSIONID_FIELD_ID);
        }
    }

    public string? WaitType
    {
        get
        {
            return base.GetNullableString(WAITTYPE_FIELD_ID);
        }
    }

    public int WaitTime
    {
        get
        {
            return base.GetInt32(WAITTIME_FIELD_ID);
        }
    }

    public string LastWaitType
    {
        get
        {
            return base.GetString(LASTWAITTYPE_FIELD_ID);
        }
    }

    public string WaitResource
    {
        get
        {
            return base.GetString(WAITRESOURCE_FIELD_ID);
        }
    }

    public int OpenTransactionCount
    {
        get
        {
            return base.GetInt32(OPENTRANSACTIONCOUNT_FIELD_ID);
        }
    }

    public int OpenResultsetCount
    {
        get
        {
            return base.GetInt32(OPENRESULTSETCOUNT_FIELD_ID);
        }
    }

    public long TransactionId
    {
        get
        {
            return base.GetInt64(TRANSACTIONID_FIELD_ID);
        }
    }

    public byte[]? ContextInfo
    {
        get
        {
            return base.GetNullableBinary(CONTEXTINFO_FIELD_ID);
        }
    }

    public float PercentComplete
    {
        get
        {
            return base.GetSingle(PERCENTCOMPLETE_FIELD_ID);
        }
    }

    public long EstimatedCompletionTime
    {
        get
        {
            return base.GetInt64(ESTIMATEDCOMPLETIONTIME_FIELD_ID);
        }
    }

    public int CpuTime
    {
        get
        {
            return base.GetInt32(CPUTIME_FIELD_ID);
        }
    }

    public int TotalElapsedTime
    {
        get
        {
            return base.GetInt32(TOTALELAPSEDTIME_FIELD_ID);
        }
    }

    public int? SchedulerId
    {
        get
        {
            return base.GetNullableInt32(SCHEDULERID_FIELD_ID);
        }
    }

    public byte[]? TaskAddress
    {
        get
        {
            return base.GetNullableBinary(TASKADDRESS_FIELD_ID);
        }
    }

    public long Reads
    {
        get
        {
            return base.GetInt64(READS_FIELD_ID);
        }
    }

    public long Writes
    {
        get
        {
            return base.GetInt64(WRITES_FIELD_ID);
        }
    }

    public long LogicalReads
    {
        get
        {
            return base.GetInt64(LOGICALREADS_FIELD_ID);
        }
    }

    public int TextSize
    {
        get
        {
            return base.GetInt32(TEXTSIZE_FIELD_ID);
        }
    }

    public string? Language
    {
        get
        {
            return base.GetNullableString(LANGUAGE_FIELD_ID);
        }
    }

    public string? DateFormat
    {
        get
        {
            return base.GetNullableString(DATEFORMAT_FIELD_ID);
        }
    }

    public short DateFirst
    {
        get
        {
            return base.GetInt16(DATEFIRST_FIELD_ID);
        }
    }

    public bool QuotedIdentifier
    {
        get
        {
            return base.GetBoolean(QUOTEDIDENTIFIER_FIELD_ID);
        }
    }

    public bool Arithabort
    {
        get
        {
            return base.GetBoolean(ARITHABORT_FIELD_ID);
        }
    }

    public bool AnsiNullDfltOn
    {
        get
        {
            return base.GetBoolean(ANSINULLDFLTON_FIELD_ID);
        }
    }

    public bool AnsiDefaults
    {
        get
        {
            return base.GetBoolean(ANSIDEFAULTS_FIELD_ID);
        }
    }

    public bool AnsiWarnings
    {
        get
        {
            return base.GetBoolean(ANSIWARNINGS_FIELD_ID);
        }
    }

    public bool AnsiPadding
    {
        get
        {
            return base.GetBoolean(ANSIPADDING_FIELD_ID);
        }
    }

    public bool AnsiNulls
    {
        get
        {
            return base.GetBoolean(ANSINULLS_FIELD_ID);
        }
    }

    public bool ConcatNullYieldsNull
    {
        get
        {
            return base.GetBoolean(CONCATNULLYIELDSNULL_FIELD_ID);
        }
    }

    public short TransactionIsolationLevel
    {
        get
        {
            return base.GetInt16(TRANSACTIONISOLATIONLEVEL_FIELD_ID);
        }
    }

    public int LockTimeout
    {
        get
        {
            return base.GetInt32(LOCKTIMEOUT_FIELD_ID);
        }
    }

    public int DeadlockPriority
    {
        get
        {
            return base.GetInt32(DEADLOCKPRIORITY_FIELD_ID);
        }
    }

    public long RowCount
    {
        get
        {
            return base.GetInt64(ROWCOUNT_FIELD_ID);
        }
    }

    public int PrevError
    {
        get
        {
            return base.GetInt32(PREVERROR_FIELD_ID);
        }
    }

    public int NestLevel
    {
        get
        {
            return base.GetInt32(NESTLEVEL_FIELD_ID);
        }
    }

    public int GrantedQueryMemory
    {
        get
        {
            return base.GetInt32(GRANTEDQUERYMEMORY_FIELD_ID);
        }
    }

    public bool ExecutingManagedCode
    {
        get
        {
            return base.GetBoolean(EXECUTINGMANAGEDCODE_FIELD_ID);
        }
    }

    public int GroupId
    {
        get
        {
            return base.GetInt32(GROUPID_FIELD_ID);
        }
    }

    public byte[]? QueryHash
    {
        get
        {
            return base.GetNullableBinary(QUERYHASH_FIELD_ID);
        }
    }

    public byte[]? QueryPlanHash
    {
        get
        {
            return base.GetNullableBinary(QUERYPLANHASH_FIELD_ID);
        }
    }

    public byte[]? StatementSqlHandle
    {
        get
        {
            return base.GetNullableBinary(STATEMENTSQLHANDLE_FIELD_ID);
        }
    }

    public long? StatementContextId
    {
        get
        {
            return base.GetNullableInt64(STATEMENTCONTEXTID_FIELD_ID);
        }
    }

    public int Dop
    {
        get
        {
            return base.GetInt32(DOP_FIELD_ID);
        }
    }

    public int? ParallelWorkerCount
    {
        get
        {
            return base.GetNullableInt32(PARALLELWORKERCOUNT_FIELD_ID);
        }
    }

    public Guid? ExternalScriptRequestId
    {
        get
        {
            return base.GetNullableGuid(EXTERNALSCRIPTREQUESTID_FIELD_ID);
        }
    }

    public bool IsResumable
    {
        get
        {
            return base.GetBoolean(ISRESUMABLE_FIELD_ID);
        }
    }

    public byte[]? PageResource
    {
        get
        {
            return base.GetNullableBinary(PAGERESOURCE_FIELD_ID);
        }
    }

    public long PageServerReads
    {
        get
        {
            return base.GetInt64(PAGESERVERREADS_FIELD_ID);
        }
    }


    public Types.DmExecRequestsDataType ToDataObject()
    {
        return new Types.DmExecRequestsDataType(SessionId,
            RequestId,
            StartTime,
            Status,
            Command,
            SqlHandle,
            StatementStartOffset,
            StatementEndOffset,
            PlanHandle,
            DatabaseId,
            UserId,
            ConnectionId,
            BlockingSessionId,
            WaitType,
            WaitTime,
            LastWaitType,
            WaitResource,
            OpenTransactionCount,
            OpenResultsetCount,
            TransactionId,
            ContextInfo,
            PercentComplete,
            EstimatedCompletionTime,
            CpuTime,
            TotalElapsedTime,
            SchedulerId,
            TaskAddress,
            Reads,
            Writes,
            LogicalReads,
            TextSize,
            Language,
            DateFormat,
            DateFirst,
            QuotedIdentifier,
            Arithabort,
            AnsiNullDfltOn,
            AnsiDefaults,
            AnsiWarnings,
            AnsiPadding,
            AnsiNulls,
            ConcatNullYieldsNull,
            TransactionIsolationLevel,
            LockTimeout,
            DeadlockPriority,
            RowCount,
            PrevError,
            NestLevel,
            GrantedQueryMemory,
            ExecutingManagedCode,
            GroupId,
            QueryHash,
            QueryPlanHash,
            StatementSqlHandle,
            StatementContextId,
            Dop,
            ParallelWorkerCount,
            ExternalScriptRequestId,
            IsResumable,
            PageResource,
            PageServerReads);
    }

    public List<Types.DmExecRequestsDataType> ToList()
    {
        var list = new List<Types.DmExecRequestsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

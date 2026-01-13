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

public class DmExecSessionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_sessions]";
    public const string TableName = "dm_exec_sessions";
    public const string ShortName = "des";
    public const string Sql = """
        SELECT
          des.[session_id],
          des.[login_time],
          des.[host_name],
          des.[program_name],
          des.[host_process_id],
          des.[client_version],
          des.[client_interface_name],
          des.[security_id],
          des.[login_name],
          des.[nt_domain],
          des.[nt_user_name],
          des.[Status],
          des.[context_info],
          des.[cpu_time],
          des.[memory_usage],
          des.[total_scheduled_time],
          des.[total_elapsed_time],
          des.[endpoint_id],
          des.[last_request_start_time],
          des.[last_request_end_time],
          des.[Reads],
          des.[Writes],
          des.[logical_reads],
          des.[is_user_process],
          des.[text_size],
          des.[Language],
          des.[date_format],
          des.[date_first],
          des.[quoted_identifier],
          des.[Arithabort],
          des.[ansi_null_dflt_on],
          des.[ansi_defaults],
          des.[ansi_warnings],
          des.[ansi_padding],
          des.[ansi_nulls],
          des.[concat_null_yields_null],
          des.[transaction_isolation_level],
          des.[lock_timeout],
          des.[deadlock_priority],
          des.[row_count],
          des.[prev_error],
          des.[original_security_id],
          des.[original_login_name],
          des.[last_successful_logon],
          des.[last_unsuccessful_logon],
          des.[unsuccessful_logons],
          des.[group_id],
          des.[database_id],
          des.[authenticating_database_id],
          des.[open_transaction_count],
          des.[page_server_reads]
        FROM
          [sys].[dm_exec_sessions] des
        """;

    public const int SESSIONID_FIELD_ID = 0;
    public const int LOGINTIME_FIELD_ID = 1;
    public const int HOSTNAME_FIELD_ID = 2;
    public const int PROGRAMNAME_FIELD_ID = 3;
    public const int HOSTPROCESSID_FIELD_ID = 4;
    public const int CLIENTVERSION_FIELD_ID = 5;
    public const int CLIENTINTERFACENAME_FIELD_ID = 6;
    public const int SECURITYID_FIELD_ID = 7;
    public const int LOGINNAME_FIELD_ID = 8;
    public const int NTDOMAIN_FIELD_ID = 9;
    public const int NTUSERNAME_FIELD_ID = 10;
    public const int STATUS_FIELD_ID = 11;
    public const int CONTEXTINFO_FIELD_ID = 12;
    public const int CPUTIME_FIELD_ID = 13;
    public const int MEMORYUSAGE_FIELD_ID = 14;
    public const int TOTALSCHEDULEDTIME_FIELD_ID = 15;
    public const int TOTALELAPSEDTIME_FIELD_ID = 16;
    public const int ENDPOINTID_FIELD_ID = 17;
    public const int LASTREQUESTSTARTTIME_FIELD_ID = 18;
    public const int LASTREQUESTENDTIME_FIELD_ID = 19;
    public const int READS_FIELD_ID = 20;
    public const int WRITES_FIELD_ID = 21;
    public const int LOGICALREADS_FIELD_ID = 22;
    public const int ISUSERPROCESS_FIELD_ID = 23;
    public const int TEXTSIZE_FIELD_ID = 24;
    public const int LANGUAGE_FIELD_ID = 25;
    public const int DATEFORMAT_FIELD_ID = 26;
    public const int DATEFIRST_FIELD_ID = 27;
    public const int QUOTEDIDENTIFIER_FIELD_ID = 28;
    public const int ARITHABORT_FIELD_ID = 29;
    public const int ANSINULLDFLTON_FIELD_ID = 30;
    public const int ANSIDEFAULTS_FIELD_ID = 31;
    public const int ANSIWARNINGS_FIELD_ID = 32;
    public const int ANSIPADDING_FIELD_ID = 33;
    public const int ANSINULLS_FIELD_ID = 34;
    public const int CONCATNULLYIELDSNULL_FIELD_ID = 35;
    public const int TRANSACTIONISOLATIONLEVEL_FIELD_ID = 36;
    public const int LOCKTIMEOUT_FIELD_ID = 37;
    public const int DEADLOCKPRIORITY_FIELD_ID = 38;
    public const int ROWCOUNT_FIELD_ID = 39;
    public const int PREVERROR_FIELD_ID = 40;
    public const int ORIGINALSECURITYID_FIELD_ID = 41;
    public const int ORIGINALLOGINNAME_FIELD_ID = 42;
    public const int LASTSUCCESSFULLOGON_FIELD_ID = 43;
    public const int LASTUNSUCCESSFULLOGON_FIELD_ID = 44;
    public const int UNSUCCESSFULLOGONS_FIELD_ID = 45;
    public const int GROUPID_FIELD_ID = 46;
    public const int DATABASEID_FIELD_ID = 47;
    public const int AUTHENTICATINGDATABASEID_FIELD_ID = 48;
    public const int OPENTRANSACTIONCOUNT_FIELD_ID = 49;
    public const int PAGESERVERREADS_FIELD_ID = 50;


    public DmExecSessionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecSessionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecSessionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public DateTime LoginTime
    {
        get
        {
            return base.GetDateTime(LOGINTIME_FIELD_ID);
        }
    }

    public string? HostName
    {
        get
        {
            return base.GetNullableString(HOSTNAME_FIELD_ID);
        }
    }

    public string? ProgramName
    {
        get
        {
            return base.GetNullableString(PROGRAMNAME_FIELD_ID);
        }
    }

    public int? HostProcessId
    {
        get
        {
            return base.GetNullableInt32(HOSTPROCESSID_FIELD_ID);
        }
    }

    public int? ClientVersion
    {
        get
        {
            return base.GetNullableInt32(CLIENTVERSION_FIELD_ID);
        }
    }

    public string? ClientInterfaceName
    {
        get
        {
            return base.GetNullableString(CLIENTINTERFACENAME_FIELD_ID);
        }
    }

    public byte[] SecurityId
    {
        get
        {
            return base.GetBinary(SECURITYID_FIELD_ID);
        }
    }

    public string LoginName
    {
        get
        {
            return base.GetString(LOGINNAME_FIELD_ID);
        }
    }

    public string? NtDomain
    {
        get
        {
            return base.GetNullableString(NTDOMAIN_FIELD_ID);
        }
    }

    public string? NtUserName
    {
        get
        {
            return base.GetNullableString(NTUSERNAME_FIELD_ID);
        }
    }

    public string Status
    {
        get
        {
            return base.GetString(STATUS_FIELD_ID);
        }
    }

    public byte[]? ContextInfo
    {
        get
        {
            return base.GetNullableBinary(CONTEXTINFO_FIELD_ID);
        }
    }

    public int CpuTime
    {
        get
        {
            return base.GetInt32(CPUTIME_FIELD_ID);
        }
    }

    public int MemoryUsage
    {
        get
        {
            return base.GetInt32(MEMORYUSAGE_FIELD_ID);
        }
    }

    public int TotalScheduledTime
    {
        get
        {
            return base.GetInt32(TOTALSCHEDULEDTIME_FIELD_ID);
        }
    }

    public int TotalElapsedTime
    {
        get
        {
            return base.GetInt32(TOTALELAPSEDTIME_FIELD_ID);
        }
    }

    public int EndpointId
    {
        get
        {
            return base.GetInt32(ENDPOINTID_FIELD_ID);
        }
    }

    public DateTime LastRequestStartTime
    {
        get
        {
            return base.GetDateTime(LASTREQUESTSTARTTIME_FIELD_ID);
        }
    }

    public DateTime? LastRequestEndTime
    {
        get
        {
            return base.GetNullableDateTime(LASTREQUESTENDTIME_FIELD_ID);
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

    public bool IsUserProcess
    {
        get
        {
            return base.GetBoolean(ISUSERPROCESS_FIELD_ID);
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

    public byte[] OriginalSecurityId
    {
        get
        {
            return base.GetBinary(ORIGINALSECURITYID_FIELD_ID);
        }
    }

    public string OriginalLoginName
    {
        get
        {
            return base.GetString(ORIGINALLOGINNAME_FIELD_ID);
        }
    }

    public DateTime? LastSuccessfulLogon
    {
        get
        {
            return base.GetNullableDateTime(LASTSUCCESSFULLOGON_FIELD_ID);
        }
    }

    public DateTime? LastUnsuccessfulLogon
    {
        get
        {
            return base.GetNullableDateTime(LASTUNSUCCESSFULLOGON_FIELD_ID);
        }
    }

    public long? UnsuccessfulLogons
    {
        get
        {
            return base.GetNullableInt64(UNSUCCESSFULLOGONS_FIELD_ID);
        }
    }

    public int GroupId
    {
        get
        {
            return base.GetInt32(GROUPID_FIELD_ID);
        }
    }

    public short DatabaseId
    {
        get
        {
            return base.GetInt16(DATABASEID_FIELD_ID);
        }
    }

    public int? AuthenticatingDatabaseId
    {
        get
        {
            return base.GetNullableInt32(AUTHENTICATINGDATABASEID_FIELD_ID);
        }
    }

    public int OpenTransactionCount
    {
        get
        {
            return base.GetInt32(OPENTRANSACTIONCOUNT_FIELD_ID);
        }
    }

    public long PageServerReads
    {
        get
        {
            return base.GetInt64(PAGESERVERREADS_FIELD_ID);
        }
    }


    public Types.DmExecSessionsDataType ToDataObject()
    {
        return new Types.DmExecSessionsDataType(SessionId,
            LoginTime,
            HostName,
            ProgramName,
            HostProcessId,
            ClientVersion,
            ClientInterfaceName,
            SecurityId,
            LoginName,
            NtDomain,
            NtUserName,
            Status,
            ContextInfo,
            CpuTime,
            MemoryUsage,
            TotalScheduledTime,
            TotalElapsedTime,
            EndpointId,
            LastRequestStartTime,
            LastRequestEndTime,
            Reads,
            Writes,
            LogicalReads,
            IsUserProcess,
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
            OriginalSecurityId,
            OriginalLoginName,
            LastSuccessfulLogon,
            LastUnsuccessfulLogon,
            UnsuccessfulLogons,
            GroupId,
            DatabaseId,
            AuthenticatingDatabaseId,
            OpenTransactionCount,
            PageServerReads);
    }

    public List<Types.DmExecSessionsDataType> ToList()
    {
        var list = new List<Types.DmExecSessionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

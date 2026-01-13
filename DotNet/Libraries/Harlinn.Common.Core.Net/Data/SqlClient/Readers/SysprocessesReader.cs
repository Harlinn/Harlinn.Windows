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

public class SysprocessesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sysprocesses]";
    public const string TableName = "sysprocesses";
    public const string ShortName = "s8";
    public const string Sql = """
        SELECT
          s8.[Spid],
          s8.[Kpid],
          s8.[Blocked],
          s8.[Waittype],
          s8.[Waittime],
          s8.[Lastwaittype],
          s8.[Waitresource],
          s8.[Dbid],
          s8.[Uid],
          s8.[Cpu],
          s8.[physical_io],
          s8.[Memusage],
          s8.[login_time],
          s8.[last_batch],
          s8.[Ecid],
          s8.[open_tran],
          s8.[Status],
          s8.[Sid],
          s8.[Hostname],
          s8.[program_name],
          s8.[Hostprocess],
          s8.[Cmd],
          s8.[nt_domain],
          s8.[nt_username],
          s8.[net_address],
          s8.[net_library],
          s8.[Loginame],
          s8.[context_info],
          s8.[sql_handle],
          s8.[stmt_start],
          s8.[stmt_end],
          s8.[request_id],
          s8.[page_resource]
        FROM
          [sys].[sysprocesses] s8
        """;

    public const int SPID_FIELD_ID = 0;
    public const int KPID_FIELD_ID = 1;
    public const int BLOCKED_FIELD_ID = 2;
    public const int WAITTYPE_FIELD_ID = 3;
    public const int WAITTIME_FIELD_ID = 4;
    public const int LASTWAITTYPE_FIELD_ID = 5;
    public const int WAITRESOURCE_FIELD_ID = 6;
    public const int DBID_FIELD_ID = 7;
    public const int UID_FIELD_ID = 8;
    public const int CPU_FIELD_ID = 9;
    public const int PHYSICALIO_FIELD_ID = 10;
    public const int MEMUSAGE_FIELD_ID = 11;
    public const int LOGINTIME_FIELD_ID = 12;
    public const int LASTBATCH_FIELD_ID = 13;
    public const int ECID_FIELD_ID = 14;
    public const int OPENTRAN_FIELD_ID = 15;
    public const int STATUS_FIELD_ID = 16;
    public const int SID_FIELD_ID = 17;
    public const int HOSTNAME_FIELD_ID = 18;
    public const int PROGRAMNAME_FIELD_ID = 19;
    public const int HOSTPROCESS_FIELD_ID = 20;
    public const int CMD_FIELD_ID = 21;
    public const int NTDOMAIN_FIELD_ID = 22;
    public const int NTUSERNAME_FIELD_ID = 23;
    public const int NETADDRESS_FIELD_ID = 24;
    public const int NETLIBRARY_FIELD_ID = 25;
    public const int LOGINAME_FIELD_ID = 26;
    public const int CONTEXTINFO_FIELD_ID = 27;
    public const int SQLHANDLE_FIELD_ID = 28;
    public const int STMTSTART_FIELD_ID = 29;
    public const int STMTEND_FIELD_ID = 30;
    public const int REQUESTID_FIELD_ID = 31;
    public const int PAGERESOURCE_FIELD_ID = 32;


    public SysprocessesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SysprocessesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SysprocessesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short Spid
    {
        get
        {
            return base.GetInt16(SPID_FIELD_ID);
        }
    }

    public short Kpid
    {
        get
        {
            return base.GetInt16(KPID_FIELD_ID);
        }
    }

    public short Blocked
    {
        get
        {
            return base.GetInt16(BLOCKED_FIELD_ID);
        }
    }

    public byte[] Waittype
    {
        get
        {
            return base.GetBinary(WAITTYPE_FIELD_ID);
        }
    }

    public long Waittime
    {
        get
        {
            return base.GetInt64(WAITTIME_FIELD_ID);
        }
    }

    public string Lastwaittype
    {
        get
        {
            return base.GetString(LASTWAITTYPE_FIELD_ID);
        }
    }

    public string Waitresource
    {
        get
        {
            return base.GetString(WAITRESOURCE_FIELD_ID);
        }
    }

    public short Dbid
    {
        get
        {
            return base.GetInt16(DBID_FIELD_ID);
        }
    }

    public short? Uid
    {
        get
        {
            return base.GetNullableInt16(UID_FIELD_ID);
        }
    }

    public int Cpu
    {
        get
        {
            return base.GetInt32(CPU_FIELD_ID);
        }
    }

    public long PhysicalIo
    {
        get
        {
            return base.GetInt64(PHYSICALIO_FIELD_ID);
        }
    }

    public int Memusage
    {
        get
        {
            return base.GetInt32(MEMUSAGE_FIELD_ID);
        }
    }

    public DateTime LoginTime
    {
        get
        {
            return base.GetDateTime(LOGINTIME_FIELD_ID);
        }
    }

    public DateTime LastBatch
    {
        get
        {
            return base.GetDateTime(LASTBATCH_FIELD_ID);
        }
    }

    public short Ecid
    {
        get
        {
            return base.GetInt16(ECID_FIELD_ID);
        }
    }

    public short OpenTran
    {
        get
        {
            return base.GetInt16(OPENTRAN_FIELD_ID);
        }
    }

    public string Status
    {
        get
        {
            return base.GetString(STATUS_FIELD_ID);
        }
    }

    public byte[] Sid
    {
        get
        {
            return base.GetBinary(SID_FIELD_ID);
        }
    }

    public string Hostname
    {
        get
        {
            return base.GetString(HOSTNAME_FIELD_ID);
        }
    }

    public string ProgramName
    {
        get
        {
            return base.GetString(PROGRAMNAME_FIELD_ID);
        }
    }

    public string Hostprocess
    {
        get
        {
            return base.GetString(HOSTPROCESS_FIELD_ID);
        }
    }

    public string Cmd
    {
        get
        {
            return base.GetString(CMD_FIELD_ID);
        }
    }

    public string NtDomain
    {
        get
        {
            return base.GetString(NTDOMAIN_FIELD_ID);
        }
    }

    public string NtUsername
    {
        get
        {
            return base.GetString(NTUSERNAME_FIELD_ID);
        }
    }

    public string NetAddress
    {
        get
        {
            return base.GetString(NETADDRESS_FIELD_ID);
        }
    }

    public string NetLibrary
    {
        get
        {
            return base.GetString(NETLIBRARY_FIELD_ID);
        }
    }

    public string Loginame
    {
        get
        {
            return base.GetString(LOGINAME_FIELD_ID);
        }
    }

    public byte[] ContextInfo
    {
        get
        {
            return base.GetBinary(CONTEXTINFO_FIELD_ID);
        }
    }

    public byte[] SqlHandle
    {
        get
        {
            return base.GetBinary(SQLHANDLE_FIELD_ID);
        }
    }

    public int StmtStart
    {
        get
        {
            return base.GetInt32(STMTSTART_FIELD_ID);
        }
    }

    public int StmtEnd
    {
        get
        {
            return base.GetInt32(STMTEND_FIELD_ID);
        }
    }

    public int RequestId
    {
        get
        {
            return base.GetInt32(REQUESTID_FIELD_ID);
        }
    }

    public byte[]? PageResource
    {
        get
        {
            return base.GetNullableBinary(PAGERESOURCE_FIELD_ID);
        }
    }


    public Types.SysprocessesDataType ToDataObject()
    {
        return new Types.SysprocessesDataType(Spid,
            Kpid,
            Blocked,
            Waittype,
            Waittime,
            Lastwaittype,
            Waitresource,
            Dbid,
            Uid,
            Cpu,
            PhysicalIo,
            Memusage,
            LoginTime,
            LastBatch,
            Ecid,
            OpenTran,
            Status,
            Sid,
            Hostname,
            ProgramName,
            Hostprocess,
            Cmd,
            NtDomain,
            NtUsername,
            NetAddress,
            NetLibrary,
            Loginame,
            ContextInfo,
            SqlHandle,
            StmtStart,
            StmtEnd,
            RequestId,
            PageResource);
    }

    public List<Types.SysprocessesDataType> ToList()
    {
        var list = new List<Types.SysprocessesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class DmReplTraninfoReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_repl_traninfo]";
    public const string TableName = "dm_repl_traninfo";
    public const string ShortName = "drt0";
    public const string Sql = """
        SELECT
          drt0.[fp2p_pub_exists],
          drt0.[db_ver],
          drt0.[comp_range_address],
          drt0.[textinfo_address],
          drt0.[fsinfo_address],
          drt0.[begin_lsn],
          drt0.[commit_lsn],
          drt0.[Dbid],
          drt0.[Rows],
          drt0.[Xdesid],
          drt0.[artcache_table_address],
          drt0.[Server],
          drt0.[server_len_in_bytes],
          drt0.[Database],
          drt0.[db_len_in_bytes],
          drt0.[Originator],
          drt0.[originator_len_in_bytes],
          drt0.[orig_db],
          drt0.[orig_db_len_in_bytes],
          drt0.[cmds_in_tran],
          drt0.[is_boundedupdate_singleton],
          drt0.[begin_update_lsn],
          drt0.[delete_lsn],
          drt0.[last_end_lsn],
          drt0.[Fcomplete],
          drt0.[Fcompensated],
          drt0.[Fprocessingtext],
          drt0.[max_cmds_in_tran],
          drt0.[begin_time],
          drt0.[commit_time],
          drt0.[session_id],
          drt0.[session_phase],
          drt0.[is_known_cdc_tran],
          drt0.[error_count]
        FROM
          [sys].[dm_repl_traninfo] drt0
        """;

    public const int FP2PPUBEXISTS_FIELD_ID = 0;
    public const int DBVER_FIELD_ID = 1;
    public const int COMPRANGEADDRESS_FIELD_ID = 2;
    public const int TEXTINFOADDRESS_FIELD_ID = 3;
    public const int FSINFOADDRESS_FIELD_ID = 4;
    public const int BEGINLSN_FIELD_ID = 5;
    public const int COMMITLSN_FIELD_ID = 6;
    public const int DBID_FIELD_ID = 7;
    public const int ROWS_FIELD_ID = 8;
    public const int XDESID_FIELD_ID = 9;
    public const int ARTCACHETABLEADDRESS_FIELD_ID = 10;
    public const int SERVER_FIELD_ID = 11;
    public const int SERVERLENINBYTES_FIELD_ID = 12;
    public const int DATABASE_FIELD_ID = 13;
    public const int DBLENINBYTES_FIELD_ID = 14;
    public const int ORIGINATOR_FIELD_ID = 15;
    public const int ORIGINATORLENINBYTES_FIELD_ID = 16;
    public const int ORIGDB_FIELD_ID = 17;
    public const int ORIGDBLENINBYTES_FIELD_ID = 18;
    public const int CMDSINTRAN_FIELD_ID = 19;
    public const int ISBOUNDEDUPDATESINGLETON_FIELD_ID = 20;
    public const int BEGINUPDATELSN_FIELD_ID = 21;
    public const int DELETELSN_FIELD_ID = 22;
    public const int LASTENDLSN_FIELD_ID = 23;
    public const int FCOMPLETE_FIELD_ID = 24;
    public const int FCOMPENSATED_FIELD_ID = 25;
    public const int FPROCESSINGTEXT_FIELD_ID = 26;
    public const int MAXCMDSINTRAN_FIELD_ID = 27;
    public const int BEGINTIME_FIELD_ID = 28;
    public const int COMMITTIME_FIELD_ID = 29;
    public const int SESSIONID_FIELD_ID = 30;
    public const int SESSIONPHASE_FIELD_ID = 31;
    public const int ISKNOWNCDCTRAN_FIELD_ID = 32;
    public const int ERRORCOUNT_FIELD_ID = 33;


    public DmReplTraninfoReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmReplTraninfoReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmReplTraninfoReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte? Fp2pPubExists
    {
        get
        {
            return base.GetNullableByte(FP2PPUBEXISTS_FIELD_ID);
        }
    }

    public int? DbVer
    {
        get
        {
            return base.GetNullableInt32(DBVER_FIELD_ID);
        }
    }

    public byte[]? CompRangeAddress
    {
        get
        {
            return base.GetNullableBinary(COMPRANGEADDRESS_FIELD_ID);
        }
    }

    public byte[]? TextinfoAddress
    {
        get
        {
            return base.GetNullableBinary(TEXTINFOADDRESS_FIELD_ID);
        }
    }

    public byte[]? FsinfoAddress
    {
        get
        {
            return base.GetNullableBinary(FSINFOADDRESS_FIELD_ID);
        }
    }

    public string? BeginLsn
    {
        get
        {
            return base.GetNullableString(BEGINLSN_FIELD_ID);
        }
    }

    public string? CommitLsn
    {
        get
        {
            return base.GetNullableString(COMMITLSN_FIELD_ID);
        }
    }

    public short? Dbid
    {
        get
        {
            return base.GetNullableInt16(DBID_FIELD_ID);
        }
    }

    public int? Rows
    {
        get
        {
            return base.GetNullableInt32(ROWS_FIELD_ID);
        }
    }

    public string? Xdesid
    {
        get
        {
            return base.GetNullableString(XDESID_FIELD_ID);
        }
    }

    public byte[]? ArtcacheTableAddress
    {
        get
        {
            return base.GetNullableBinary(ARTCACHETABLEADDRESS_FIELD_ID);
        }
    }

    public string? Server
    {
        get
        {
            return base.GetNullableString(SERVER_FIELD_ID);
        }
    }

    public int? ServerLenInBytes
    {
        get
        {
            return base.GetNullableInt32(SERVERLENINBYTES_FIELD_ID);
        }
    }

    public string? Database
    {
        get
        {
            return base.GetNullableString(DATABASE_FIELD_ID);
        }
    }

    public int? DbLenInBytes
    {
        get
        {
            return base.GetNullableInt32(DBLENINBYTES_FIELD_ID);
        }
    }

    public string? Originator
    {
        get
        {
            return base.GetNullableString(ORIGINATOR_FIELD_ID);
        }
    }

    public int? OriginatorLenInBytes
    {
        get
        {
            return base.GetNullableInt32(ORIGINATORLENINBYTES_FIELD_ID);
        }
    }

    public string? OrigDb
    {
        get
        {
            return base.GetNullableString(ORIGDB_FIELD_ID);
        }
    }

    public int? OrigDbLenInBytes
    {
        get
        {
            return base.GetNullableInt32(ORIGDBLENINBYTES_FIELD_ID);
        }
    }

    public int? CmdsInTran
    {
        get
        {
            return base.GetNullableInt32(CMDSINTRAN_FIELD_ID);
        }
    }

    public byte? IsBoundedupdateSingleton
    {
        get
        {
            return base.GetNullableByte(ISBOUNDEDUPDATESINGLETON_FIELD_ID);
        }
    }

    public string? BeginUpdateLsn
    {
        get
        {
            return base.GetNullableString(BEGINUPDATELSN_FIELD_ID);
        }
    }

    public string? DeleteLsn
    {
        get
        {
            return base.GetNullableString(DELETELSN_FIELD_ID);
        }
    }

    public string? LastEndLsn
    {
        get
        {
            return base.GetNullableString(LASTENDLSN_FIELD_ID);
        }
    }

    public byte? Fcomplete
    {
        get
        {
            return base.GetNullableByte(FCOMPLETE_FIELD_ID);
        }
    }

    public byte? Fcompensated
    {
        get
        {
            return base.GetNullableByte(FCOMPENSATED_FIELD_ID);
        }
    }

    public byte? Fprocessingtext
    {
        get
        {
            return base.GetNullableByte(FPROCESSINGTEXT_FIELD_ID);
        }
    }

    public int? MaxCmdsInTran
    {
        get
        {
            return base.GetNullableInt32(MAXCMDSINTRAN_FIELD_ID);
        }
    }

    public DateTime? BeginTime
    {
        get
        {
            return base.GetNullableDateTime(BEGINTIME_FIELD_ID);
        }
    }

    public DateTime? CommitTime
    {
        get
        {
            return base.GetNullableDateTime(COMMITTIME_FIELD_ID);
        }
    }

    public int? SessionId
    {
        get
        {
            return base.GetNullableInt32(SESSIONID_FIELD_ID);
        }
    }

    public string? SessionPhase
    {
        get
        {
            return base.GetNullableString(SESSIONPHASE_FIELD_ID);
        }
    }

    public byte? IsKnownCdcTran
    {
        get
        {
            return base.GetNullableByte(ISKNOWNCDCTRAN_FIELD_ID);
        }
    }

    public int? ErrorCount
    {
        get
        {
            return base.GetNullableInt32(ERRORCOUNT_FIELD_ID);
        }
    }


    public Types.DmReplTraninfoDataType ToDataObject()
    {
        return new Types.DmReplTraninfoDataType(Fp2pPubExists,
            DbVer,
            CompRangeAddress,
            TextinfoAddress,
            FsinfoAddress,
            BeginLsn,
            CommitLsn,
            Dbid,
            Rows,
            Xdesid,
            ArtcacheTableAddress,
            Server,
            ServerLenInBytes,
            Database,
            DbLenInBytes,
            Originator,
            OriginatorLenInBytes,
            OrigDb,
            OrigDbLenInBytes,
            CmdsInTran,
            IsBoundedupdateSingleton,
            BeginUpdateLsn,
            DeleteLsn,
            LastEndLsn,
            Fcomplete,
            Fcompensated,
            Fprocessingtext,
            MaxCmdsInTran,
            BeginTime,
            CommitTime,
            SessionId,
            SessionPhase,
            IsKnownCdcTran,
            ErrorCount);
    }

    public List<Types.DmReplTraninfoDataType> ToList()
    {
        var list = new List<Types.DmReplTraninfoDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

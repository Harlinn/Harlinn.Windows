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

public class SyslockinfoReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[syslockinfo]";
    public const string TableName = "syslockinfo";
    public const string ShortName = "s14";
    public const string Sql = """
        SELECT
          s14.[rsc_text],
          s14.[rsc_bin],
          s14.[rsc_valblk],
          s14.[rsc_dbid],
          s14.[rsc_indid],
          s14.[rsc_objid],
          s14.[rsc_type],
          s14.[rsc_flag],
          s14.[req_mode],
          s14.[req_status],
          s14.[req_refcnt],
          s14.[req_cryrefcnt],
          s14.[req_lifetime],
          s14.[req_spid],
          s14.[req_ecid],
          s14.[req_ownertype],
          s14.[req_transactionID],
          s14.[req_transactionUOW]
        FROM
          [sys].[syslockinfo] s14
        """;

    public const int RSCTEXT_FIELD_ID = 0;
    public const int RSCBIN_FIELD_ID = 1;
    public const int RSCVALBLK_FIELD_ID = 2;
    public const int RSCDBID_FIELD_ID = 3;
    public const int RSCINDID_FIELD_ID = 4;
    public const int RSCOBJID_FIELD_ID = 5;
    public const int RSCTYPE_FIELD_ID = 6;
    public const int RSCFLAG_FIELD_ID = 7;
    public const int REQMODE_FIELD_ID = 8;
    public const int REQSTATUS_FIELD_ID = 9;
    public const int REQREFCNT_FIELD_ID = 10;
    public const int REQCRYREFCNT_FIELD_ID = 11;
    public const int REQLIFETIME_FIELD_ID = 12;
    public const int REQSPID_FIELD_ID = 13;
    public const int REQECID_FIELD_ID = 14;
    public const int REQOWNERTYPE_FIELD_ID = 15;
    public const int REQTRANSACTIONID_FIELD_ID = 16;
    public const int REQTRANSACTIONUOW_FIELD_ID = 17;


    public SyslockinfoReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SyslockinfoReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SyslockinfoReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string RscText
    {
        get
        {
            return base.GetString(RSCTEXT_FIELD_ID);
        }
    }

    public byte[] RscBin
    {
        get
        {
            return base.GetBinary(RSCBIN_FIELD_ID);
        }
    }

    public byte[] RscValblk
    {
        get
        {
            return base.GetBinary(RSCVALBLK_FIELD_ID);
        }
    }

    public short RscDbid
    {
        get
        {
            return base.GetInt16(RSCDBID_FIELD_ID);
        }
    }

    public short RscIndid
    {
        get
        {
            return base.GetInt16(RSCINDID_FIELD_ID);
        }
    }

    public int RscObjid
    {
        get
        {
            return base.GetInt32(RSCOBJID_FIELD_ID);
        }
    }

    public byte RscType
    {
        get
        {
            return base.GetByte(RSCTYPE_FIELD_ID);
        }
    }

    public byte RscFlag
    {
        get
        {
            return base.GetByte(RSCFLAG_FIELD_ID);
        }
    }

    public byte ReqMode
    {
        get
        {
            return base.GetByte(REQMODE_FIELD_ID);
        }
    }

    public byte ReqStatus
    {
        get
        {
            return base.GetByte(REQSTATUS_FIELD_ID);
        }
    }

    public short ReqRefcnt
    {
        get
        {
            return base.GetInt16(REQREFCNT_FIELD_ID);
        }
    }

    public short ReqCryrefcnt
    {
        get
        {
            return base.GetInt16(REQCRYREFCNT_FIELD_ID);
        }
    }

    public int ReqLifetime
    {
        get
        {
            return base.GetInt32(REQLIFETIME_FIELD_ID);
        }
    }

    public int ReqSpid
    {
        get
        {
            return base.GetInt32(REQSPID_FIELD_ID);
        }
    }

    public int ReqEcid
    {
        get
        {
            return base.GetInt32(REQECID_FIELD_ID);
        }
    }

    public short ReqOwnertype
    {
        get
        {
            return base.GetInt16(REQOWNERTYPE_FIELD_ID);
        }
    }

    public long? ReqTransactionid
    {
        get
        {
            return base.GetNullableInt64(REQTRANSACTIONID_FIELD_ID);
        }
    }

    public Guid? ReqTransactionuow
    {
        get
        {
            return base.GetNullableGuid(REQTRANSACTIONUOW_FIELD_ID);
        }
    }


    public Types.SyslockinfoDataType ToDataObject()
    {
        return new Types.SyslockinfoDataType(RscText,
            RscBin,
            RscValblk,
            RscDbid,
            RscIndid,
            RscObjid,
            RscType,
            RscFlag,
            ReqMode,
            ReqStatus,
            ReqRefcnt,
            ReqCryrefcnt,
            ReqLifetime,
            ReqSpid,
            ReqEcid,
            ReqOwnertype,
            ReqTransactionid,
            ReqTransactionuow);
    }

    public List<Types.SyslockinfoDataType> ToList()
    {
        var list = new List<Types.SyslockinfoDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

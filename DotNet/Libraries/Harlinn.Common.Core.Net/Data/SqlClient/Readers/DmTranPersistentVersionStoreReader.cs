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

public class DmTranPersistentVersionStoreReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_persistent_version_store]";
    public const string TableName = "dm_tran_persistent_version_store";
    public const string ShortName = "dtpvs";
    public const string Sql = """
        SELECT
          dtpvs.[xdes_ts_push],
          dtpvs.[xdes_ts_tran],
          dtpvs.[subid_push],
          dtpvs.[subid_tran],
          dtpvs.[rowset_id],
          dtpvs.[sec_version_rid],
          dtpvs.[min_len],
          dtpvs.[seq_num],
          dtpvs.[prev_row_in_chain],
          dtpvs.[row_version]
        FROM
          [sys].[dm_tran_persistent_version_store] dtpvs
        """;

    public const int XDESTSPUSH_FIELD_ID = 0;
    public const int XDESTSTRAN_FIELD_ID = 1;
    public const int SUBIDPUSH_FIELD_ID = 2;
    public const int SUBIDTRAN_FIELD_ID = 3;
    public const int ROWSETID_FIELD_ID = 4;
    public const int SECVERSIONRID_FIELD_ID = 5;
    public const int MINLEN_FIELD_ID = 6;
    public const int SEQNUM_FIELD_ID = 7;
    public const int PREVROWINCHAIN_FIELD_ID = 8;
    public const int ROWVERSION_FIELD_ID = 9;


    public DmTranPersistentVersionStoreReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranPersistentVersionStoreReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranPersistentVersionStoreReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long XdesTsPush
    {
        get
        {
            return base.GetInt64(XDESTSPUSH_FIELD_ID);
        }
    }

    public long XdesTsTran
    {
        get
        {
            return base.GetInt64(XDESTSTRAN_FIELD_ID);
        }
    }

    public int? SubidPush
    {
        get
        {
            return base.GetNullableInt32(SUBIDPUSH_FIELD_ID);
        }
    }

    public int? SubidTran
    {
        get
        {
            return base.GetNullableInt32(SUBIDTRAN_FIELD_ID);
        }
    }

    public long RowsetId
    {
        get
        {
            return base.GetInt64(ROWSETID_FIELD_ID);
        }
    }

    public byte[] SecVersionRid
    {
        get
        {
            return base.GetBinary(SECVERSIONRID_FIELD_ID);
        }
    }

    public short? MinLen
    {
        get
        {
            return base.GetNullableInt16(MINLEN_FIELD_ID);
        }
    }

    public long? SeqNum
    {
        get
        {
            return base.GetNullableInt64(SEQNUM_FIELD_ID);
        }
    }

    public byte[] PrevRowInChain
    {
        get
        {
            return base.GetBinary(PREVROWINCHAIN_FIELD_ID);
        }
    }

    public byte[] RowVersion
    {
        get
        {
            return base.GetBinary(ROWVERSION_FIELD_ID);
        }
    }


    public Types.DmTranPersistentVersionStoreDataType ToDataObject()
    {
        return new Types.DmTranPersistentVersionStoreDataType(XdesTsPush,
            XdesTsTran,
            SubidPush,
            SubidTran,
            RowsetId,
            SecVersionRid,
            MinLen,
            SeqNum,
            PrevRowInChain,
            RowVersion);
    }

    public List<Types.DmTranPersistentVersionStoreDataType> ToList()
    {
        var list = new List<Types.DmTranPersistentVersionStoreDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class DmXtpTransactionRecentRowsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_xtp_transaction_recent_rows]";
    public const string TableName = "dm_xtp_transaction_recent_rows";
    public const string ShortName = "dxtrr";
    public const string Sql = """
        SELECT
          dxtrr.[node_id],
          dxtrr.[xtp_transaction_id],
          dxtrr.[row_address],
          dxtrr.[table_address],
          dxtrr.[before_begin],
          dxtrr.[before_end],
          dxtrr.[before_links],
          dxtrr.[before_time],
          dxtrr.[after_begin],
          dxtrr.[after_end],
          dxtrr.[after_links],
          dxtrr.[after_time],
          dxtrr.[Outcome]
        FROM
          [sys].[dm_xtp_transaction_recent_rows] dxtrr
        """;

    public const int NODEID_FIELD_ID = 0;
    public const int XTPTRANSACTIONID_FIELD_ID = 1;
    public const int ROWADDRESS_FIELD_ID = 2;
    public const int TABLEADDRESS_FIELD_ID = 3;
    public const int BEFOREBEGIN_FIELD_ID = 4;
    public const int BEFOREEND_FIELD_ID = 5;
    public const int BEFORELINKS_FIELD_ID = 6;
    public const int BEFORETIME_FIELD_ID = 7;
    public const int AFTERBEGIN_FIELD_ID = 8;
    public const int AFTEREND_FIELD_ID = 9;
    public const int AFTERLINKS_FIELD_ID = 10;
    public const int AFTERTIME_FIELD_ID = 11;
    public const int OUTCOME_FIELD_ID = 12;


    public DmXtpTransactionRecentRowsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmXtpTransactionRecentRowsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmXtpTransactionRecentRowsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short NodeId
    {
        get
        {
            return base.GetInt16(NODEID_FIELD_ID);
        }
    }

    public long XtpTransactionId
    {
        get
        {
            return base.GetInt64(XTPTRANSACTIONID_FIELD_ID);
        }
    }

    public byte[] RowAddress
    {
        get
        {
            return base.GetBinary(ROWADDRESS_FIELD_ID);
        }
    }

    public byte[] TableAddress
    {
        get
        {
            return base.GetBinary(TABLEADDRESS_FIELD_ID);
        }
    }

    public long BeforeBegin
    {
        get
        {
            return base.GetInt64(BEFOREBEGIN_FIELD_ID);
        }
    }

    public long BeforeEnd
    {
        get
        {
            return base.GetInt64(BEFOREEND_FIELD_ID);
        }
    }

    public int BeforeLinks
    {
        get
        {
            return base.GetInt32(BEFORELINKS_FIELD_ID);
        }
    }

    public long BeforeTime
    {
        get
        {
            return base.GetInt64(BEFORETIME_FIELD_ID);
        }
    }

    public long AfterBegin
    {
        get
        {
            return base.GetInt64(AFTERBEGIN_FIELD_ID);
        }
    }

    public long AfterEnd
    {
        get
        {
            return base.GetInt64(AFTEREND_FIELD_ID);
        }
    }

    public int AfterLinks
    {
        get
        {
            return base.GetInt32(AFTERLINKS_FIELD_ID);
        }
    }

    public long AfterTime
    {
        get
        {
            return base.GetInt64(AFTERTIME_FIELD_ID);
        }
    }

    public byte[] Outcome
    {
        get
        {
            return base.GetBinary(OUTCOME_FIELD_ID);
        }
    }


    public Types.DmXtpTransactionRecentRowsDataType ToDataObject()
    {
        return new Types.DmXtpTransactionRecentRowsDataType(NodeId,
            XtpTransactionId,
            RowAddress,
            TableAddress,
            BeforeBegin,
            BeforeEnd,
            BeforeLinks,
            BeforeTime,
            AfterBegin,
            AfterEnd,
            AfterLinks,
            AfterTime,
            Outcome);
    }

    public List<Types.DmXtpTransactionRecentRowsDataType> ToList()
    {
        var list = new List<Types.DmXtpTransactionRecentRowsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

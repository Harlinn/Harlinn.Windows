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

public class DmTranCommitTableReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_commit_table]";
    public const string TableName = "dm_tran_commit_table";
    public const string ShortName = "dtct";
    public const string Sql = """
        SELECT
          dtct.[commit_ts],
          dtct.[xdes_id],
          dtct.[commit_lbn],
          dtct.[commit_csn],
          dtct.[commit_time]
        FROM
          [sys].[dm_tran_commit_table] dtct
        """;

    public const int COMMITTS_FIELD_ID = 0;
    public const int XDESID_FIELD_ID = 1;
    public const int COMMITLBN_FIELD_ID = 2;
    public const int COMMITCSN_FIELD_ID = 3;
    public const int COMMITTIME_FIELD_ID = 4;


    public DmTranCommitTableReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranCommitTableReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranCommitTableReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long? CommitTs
    {
        get
        {
            return base.GetNullableInt64(COMMITTS_FIELD_ID);
        }
    }

    public long? XdesId
    {
        get
        {
            return base.GetNullableInt64(XDESID_FIELD_ID);
        }
    }

    public long CommitLbn
    {
        get
        {
            return base.GetInt64(COMMITLBN_FIELD_ID);
        }
    }

    public long CommitCsn
    {
        get
        {
            return base.GetInt64(COMMITCSN_FIELD_ID);
        }
    }

    public DateTime CommitTime
    {
        get
        {
            return base.GetDateTime(COMMITTIME_FIELD_ID);
        }
    }


    public Types.DmTranCommitTableDataType ToDataObject()
    {
        return new Types.DmTranCommitTableDataType(CommitTs,
            XdesId,
            CommitLbn,
            CommitCsn,
            CommitTime);
    }

    public List<Types.DmTranCommitTableDataType> ToList()
    {
        var list = new List<Types.DmTranCommitTableDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

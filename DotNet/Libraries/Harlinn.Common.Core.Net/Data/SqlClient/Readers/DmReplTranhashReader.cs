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

public class DmReplTranhashReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_repl_tranhash]";
    public const string TableName = "dm_repl_tranhash";
    public const string ShortName = "drt";
    public const string Sql = """
        SELECT
          drt.[Buckets],
          drt.[hashed_trans],
          drt.[completed_trans],
          drt.[compensated_trans],
          drt.[first_begin_lsn],
          drt.[last_commit_lsn]
        FROM
          [sys].[dm_repl_tranhash] drt
        """;

    public const int BUCKETS_FIELD_ID = 0;
    public const int HASHEDTRANS_FIELD_ID = 1;
    public const int COMPLETEDTRANS_FIELD_ID = 2;
    public const int COMPENSATEDTRANS_FIELD_ID = 3;
    public const int FIRSTBEGINLSN_FIELD_ID = 4;
    public const int LASTCOMMITLSN_FIELD_ID = 5;


    public DmReplTranhashReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmReplTranhashReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmReplTranhashReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? Buckets
    {
        get
        {
            return base.GetNullableInt32(BUCKETS_FIELD_ID);
        }
    }

    public int? HashedTrans
    {
        get
        {
            return base.GetNullableInt32(HASHEDTRANS_FIELD_ID);
        }
    }

    public int? CompletedTrans
    {
        get
        {
            return base.GetNullableInt32(COMPLETEDTRANS_FIELD_ID);
        }
    }

    public int? CompensatedTrans
    {
        get
        {
            return base.GetNullableInt32(COMPENSATEDTRANS_FIELD_ID);
        }
    }

    public string? FirstBeginLsn
    {
        get
        {
            return base.GetNullableString(FIRSTBEGINLSN_FIELD_ID);
        }
    }

    public string? LastCommitLsn
    {
        get
        {
            return base.GetNullableString(LASTCOMMITLSN_FIELD_ID);
        }
    }


    public Types.DmReplTranhashDataType ToDataObject()
    {
        return new Types.DmReplTranhashDataType(Buckets,
            HashedTrans,
            CompletedTrans,
            CompensatedTrans,
            FirstBeginLsn,
            LastCommitLsn);
    }

    public List<Types.DmReplTranhashDataType> ToList()
    {
        var list = new List<Types.DmReplTranhashDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

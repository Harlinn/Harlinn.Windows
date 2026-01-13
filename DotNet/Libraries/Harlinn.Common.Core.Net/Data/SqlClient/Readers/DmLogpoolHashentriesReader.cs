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

public class DmLogpoolHashentriesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_logpool_hashentries]";
    public const string TableName = "dm_logpool_hashentries";
    public const string ShortName = "dlh";
    public const string Sql = """
        SELECT
          dlh.[bucket_no],
          dlh.[database_id],
          dlh.[recovery_unit_id],
          dlh.[log_block_id],
          dlh.[cache_buffer]
        FROM
          [sys].[dm_logpool_hashentries] dlh
        """;

    public const int BUCKETNO_FIELD_ID = 0;
    public const int DATABASEID_FIELD_ID = 1;
    public const int RECOVERYUNITID_FIELD_ID = 2;
    public const int LOGBLOCKID_FIELD_ID = 3;
    public const int CACHEBUFFER_FIELD_ID = 4;


    public DmLogpoolHashentriesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmLogpoolHashentriesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmLogpoolHashentriesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int BucketNo
    {
        get
        {
            return base.GetInt32(BUCKETNO_FIELD_ID);
        }
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public int RecoveryUnitId
    {
        get
        {
            return base.GetInt32(RECOVERYUNITID_FIELD_ID);
        }
    }

    public long LogBlockId
    {
        get
        {
            return base.GetInt64(LOGBLOCKID_FIELD_ID);
        }
    }

    public byte[] CacheBuffer
    {
        get
        {
            return base.GetBinary(CACHEBUFFER_FIELD_ID);
        }
    }


    public Types.DmLogpoolHashentriesDataType ToDataObject()
    {
        return new Types.DmLogpoolHashentriesDataType(BucketNo,
            DatabaseId,
            RecoveryUnitId,
            LogBlockId,
            CacheBuffer);
    }

    public List<Types.DmLogpoolHashentriesDataType> ToList()
    {
        var list = new List<Types.DmLogpoolHashentriesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

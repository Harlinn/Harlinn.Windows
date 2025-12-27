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

public class DmDbXtpCheckpointInternalsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_xtp_checkpoint_internals]";
    public const string TableName = "dm_db_xtp_checkpoint_internals";
    public const string ShortName = "ddxci";
    public const string Sql = """
        SELECT
          ddxci.[checkpoint_id],
          ddxci.[checkpoint_timestamp],
          ddxci.[last_segment_lsn],
          ddxci.[recovery_lsn],
          ddxci.[is_synchronized]
        FROM
          [sys].[dm_db_xtp_checkpoint_internals] ddxci
        """;

    public const int CHECKPOINTID_FIELD_ID = 0;
    public const int CHECKPOINTTIMESTAMP_FIELD_ID = 1;
    public const int LASTSEGMENTLSN_FIELD_ID = 2;
    public const int RECOVERYLSN_FIELD_ID = 3;
    public const int ISSYNCHRONIZED_FIELD_ID = 4;


    public DmDbXtpCheckpointInternalsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpCheckpointInternalsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpCheckpointInternalsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long CheckpointId
    {
        get
        {
            return base.GetInt64(CHECKPOINTID_FIELD_ID);
        }
    }

    public long? CheckpointTimestamp
    {
        get
        {
            return base.GetNullableInt64(CHECKPOINTTIMESTAMP_FIELD_ID);
        }
    }

    public decimal? LastSegmentLsn
    {
        get
        {
            return base.GetNullableDecimal(LASTSEGMENTLSN_FIELD_ID);
        }
    }

    public decimal? RecoveryLsn
    {
        get
        {
            return base.GetNullableDecimal(RECOVERYLSN_FIELD_ID);
        }
    }

    public bool? IsSynchronized
    {
        get
        {
            return base.GetNullableBoolean(ISSYNCHRONIZED_FIELD_ID);
        }
    }


    public Types.DmDbXtpCheckpointInternalsDataType ToDataObject()
    {
        return new Types.DmDbXtpCheckpointInternalsDataType(CheckpointId,
            CheckpointTimestamp,
            LastSegmentLsn,
            RecoveryLsn,
            IsSynchronized);
    }

    public List<Types.DmDbXtpCheckpointInternalsDataType> ToList()
    {
        var list = new List<Types.DmDbXtpCheckpointInternalsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class DmDbXtpIndexStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_xtp_index_stats]";
    public const string TableName = "dm_db_xtp_index_stats";
    public const string ShortName = "ddxis";
    public const string Sql = """
        SELECT
          ddxis.[object_id],
          ddxis.[xtp_object_id],
          ddxis.[index_id],
          ddxis.[scans_started],
          ddxis.[scans_retries],
          ddxis.[rows_returned],
          ddxis.[rows_touched],
          ddxis.[rows_expiring],
          ddxis.[rows_expired],
          ddxis.[rows_expired_removed],
          ddxis.[phantom_scans_started],
          ddxis.[phantom_scans_retries],
          ddxis.[phantom_rows_touched],
          ddxis.[phantom_expiring_rows_encountered],
          ddxis.[phantom_expired_removed_rows_encountered],
          ddxis.[phantom_expired_rows_removed],
          ddxis.[object_address]
        FROM
          [sys].[dm_db_xtp_index_stats] ddxis
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int XTPOBJECTID_FIELD_ID = 1;
    public const int INDEXID_FIELD_ID = 2;
    public const int SCANSSTARTED_FIELD_ID = 3;
    public const int SCANSRETRIES_FIELD_ID = 4;
    public const int ROWSRETURNED_FIELD_ID = 5;
    public const int ROWSTOUCHED_FIELD_ID = 6;
    public const int ROWSEXPIRING_FIELD_ID = 7;
    public const int ROWSEXPIRED_FIELD_ID = 8;
    public const int ROWSEXPIREDREMOVED_FIELD_ID = 9;
    public const int PHANTOMSCANSSTARTED_FIELD_ID = 10;
    public const int PHANTOMSCANSRETRIES_FIELD_ID = 11;
    public const int PHANTOMROWSTOUCHED_FIELD_ID = 12;
    public const int PHANTOMEXPIRINGROWSENCOUNTERED_FIELD_ID = 13;
    public const int PHANTOMEXPIREDREMOVEDROWSENCOUNTERED_FIELD_ID = 14;
    public const int PHANTOMEXPIREDROWSREMOVED_FIELD_ID = 15;
    public const int OBJECTADDRESS_FIELD_ID = 16;


    public DmDbXtpIndexStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpIndexStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpIndexStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int XtpObjectId
    {
        get
        {
            return base.GetInt32(XTPOBJECTID_FIELD_ID);
        }
    }

    public int IndexId
    {
        get
        {
            return base.GetInt32(INDEXID_FIELD_ID);
        }
    }

    public long ScansStarted
    {
        get
        {
            return base.GetInt64(SCANSSTARTED_FIELD_ID);
        }
    }

    public long ScansRetries
    {
        get
        {
            return base.GetInt64(SCANSRETRIES_FIELD_ID);
        }
    }

    public long RowsReturned
    {
        get
        {
            return base.GetInt64(ROWSRETURNED_FIELD_ID);
        }
    }

    public long RowsTouched
    {
        get
        {
            return base.GetInt64(ROWSTOUCHED_FIELD_ID);
        }
    }

    public long RowsExpiring
    {
        get
        {
            return base.GetInt64(ROWSEXPIRING_FIELD_ID);
        }
    }

    public long RowsExpired
    {
        get
        {
            return base.GetInt64(ROWSEXPIRED_FIELD_ID);
        }
    }

    public long RowsExpiredRemoved
    {
        get
        {
            return base.GetInt64(ROWSEXPIREDREMOVED_FIELD_ID);
        }
    }

    public long PhantomScansStarted
    {
        get
        {
            return base.GetInt64(PHANTOMSCANSSTARTED_FIELD_ID);
        }
    }

    public long PhantomScansRetries
    {
        get
        {
            return base.GetInt64(PHANTOMSCANSRETRIES_FIELD_ID);
        }
    }

    public long PhantomRowsTouched
    {
        get
        {
            return base.GetInt64(PHANTOMROWSTOUCHED_FIELD_ID);
        }
    }

    public long PhantomExpiringRowsEncountered
    {
        get
        {
            return base.GetInt64(PHANTOMEXPIRINGROWSENCOUNTERED_FIELD_ID);
        }
    }

    public long PhantomExpiredRemovedRowsEncountered
    {
        get
        {
            return base.GetInt64(PHANTOMEXPIREDREMOVEDROWSENCOUNTERED_FIELD_ID);
        }
    }

    public long PhantomExpiredRowsRemoved
    {
        get
        {
            return base.GetInt64(PHANTOMEXPIREDROWSREMOVED_FIELD_ID);
        }
    }

    public byte[] ObjectAddress
    {
        get
        {
            return base.GetBinary(OBJECTADDRESS_FIELD_ID);
        }
    }


    public Types.DmDbXtpIndexStatsDataType ToDataObject()
    {
        return new Types.DmDbXtpIndexStatsDataType(ObjectId,
            XtpObjectId,
            IndexId,
            ScansStarted,
            ScansRetries,
            RowsReturned,
            RowsTouched,
            RowsExpiring,
            RowsExpired,
            RowsExpiredRemoved,
            PhantomScansStarted,
            PhantomScansRetries,
            PhantomRowsTouched,
            PhantomExpiringRowsEncountered,
            PhantomExpiredRemovedRowsEncountered,
            PhantomExpiredRowsRemoved,
            ObjectAddress);
    }

    public List<Types.DmDbXtpIndexStatsDataType> ToList()
    {
        var list = new List<Types.DmDbXtpIndexStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

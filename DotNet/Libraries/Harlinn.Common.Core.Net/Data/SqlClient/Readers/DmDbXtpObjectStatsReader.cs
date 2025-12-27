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

public class DmDbXtpObjectStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_xtp_object_stats]";
    public const string TableName = "dm_db_xtp_object_stats";
    public const string ShortName = "ddxos";
    public const string Sql = """
        SELECT
          ddxos.[object_id],
          ddxos.[xtp_object_id],
          ddxos.[row_insert_attempts],
          ddxos.[row_update_attempts],
          ddxos.[row_delete_attempts],
          ddxos.[write_conflicts],
          ddxos.[unique_constraint_violations],
          ddxos.[object_address]
        FROM
          [sys].[dm_db_xtp_object_stats] ddxos
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int XTPOBJECTID_FIELD_ID = 1;
    public const int ROWINSERTATTEMPTS_FIELD_ID = 2;
    public const int ROWUPDATEATTEMPTS_FIELD_ID = 3;
    public const int ROWDELETEATTEMPTS_FIELD_ID = 4;
    public const int WRITECONFLICTS_FIELD_ID = 5;
    public const int UNIQUECONSTRAINTVIOLATIONS_FIELD_ID = 6;
    public const int OBJECTADDRESS_FIELD_ID = 7;


    public DmDbXtpObjectStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpObjectStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbXtpObjectStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public long RowInsertAttempts
    {
        get
        {
            return base.GetInt64(ROWINSERTATTEMPTS_FIELD_ID);
        }
    }

    public long RowUpdateAttempts
    {
        get
        {
            return base.GetInt64(ROWUPDATEATTEMPTS_FIELD_ID);
        }
    }

    public long RowDeleteAttempts
    {
        get
        {
            return base.GetInt64(ROWDELETEATTEMPTS_FIELD_ID);
        }
    }

    public long WriteConflicts
    {
        get
        {
            return base.GetInt64(WRITECONFLICTS_FIELD_ID);
        }
    }

    public long UniqueConstraintViolations
    {
        get
        {
            return base.GetInt64(UNIQUECONSTRAINTVIOLATIONS_FIELD_ID);
        }
    }

    public byte[] ObjectAddress
    {
        get
        {
            return base.GetBinary(OBJECTADDRESS_FIELD_ID);
        }
    }


    public Types.DmDbXtpObjectStatsDataType ToDataObject()
    {
        return new Types.DmDbXtpObjectStatsDataType(ObjectId,
            XtpObjectId,
            RowInsertAttempts,
            RowUpdateAttempts,
            RowDeleteAttempts,
            WriteConflicts,
            UniqueConstraintViolations,
            ObjectAddress);
    }

    public List<Types.DmDbXtpObjectStatsDataType> ToList()
    {
        var list = new List<Types.DmDbXtpObjectStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

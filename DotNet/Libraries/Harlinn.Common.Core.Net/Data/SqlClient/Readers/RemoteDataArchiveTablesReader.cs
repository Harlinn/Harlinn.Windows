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

public class RemoteDataArchiveTablesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[remote_data_archive_tables]";
    public const string TableName = "remote_data_archive_tables";
    public const string ShortName = "rdat";
    public const string Sql = """
        SELECT
          rdat.[object_id],
          rdat.[remote_database_id],
          rdat.[remote_table_name],
          rdat.[filter_predicate],
          rdat.[migration_direction],
          rdat.[migration_direction_desc],
          rdat.[is_migration_paused],
          rdat.[is_reconciled]
        FROM
          [sys].[remote_data_archive_tables] rdat
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int REMOTEDATABASEID_FIELD_ID = 1;
    public const int REMOTETABLENAME_FIELD_ID = 2;
    public const int FILTERPREDICATE_FIELD_ID = 3;
    public const int MIGRATIONDIRECTION_FIELD_ID = 4;
    public const int MIGRATIONDIRECTIONDESC_FIELD_ID = 5;
    public const int ISMIGRATIONPAUSED_FIELD_ID = 6;
    public const int ISRECONCILED_FIELD_ID = 7;


    public RemoteDataArchiveTablesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public RemoteDataArchiveTablesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public RemoteDataArchiveTablesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int RemoteDatabaseId
    {
        get
        {
            return base.GetInt32(REMOTEDATABASEID_FIELD_ID);
        }
    }

    public string? RemoteTableName
    {
        get
        {
            return base.GetNullableString(REMOTETABLENAME_FIELD_ID);
        }
    }

    public string? FilterPredicate
    {
        get
        {
            return base.GetNullableString(FILTERPREDICATE_FIELD_ID);
        }
    }

    public byte? MigrationDirection
    {
        get
        {
            return base.GetNullableByte(MIGRATIONDIRECTION_FIELD_ID);
        }
    }

    public string? MigrationDirectionDesc
    {
        get
        {
            return base.GetNullableString(MIGRATIONDIRECTIONDESC_FIELD_ID);
        }
    }

    public bool? IsMigrationPaused
    {
        get
        {
            return base.GetNullableBoolean(ISMIGRATIONPAUSED_FIELD_ID);
        }
    }

    public bool? IsReconciled
    {
        get
        {
            return base.GetNullableBoolean(ISRECONCILED_FIELD_ID);
        }
    }


    public Types.RemoteDataArchiveTablesDataType ToDataObject()
    {
        return new Types.RemoteDataArchiveTablesDataType(ObjectId,
            RemoteDatabaseId,
            RemoteTableName,
            FilterPredicate,
            MigrationDirection,
            MigrationDirectionDesc,
            IsMigrationPaused,
            IsReconciled);
    }

    public List<Types.RemoteDataArchiveTablesDataType> ToList()
    {
        var list = new List<Types.RemoteDataArchiveTablesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

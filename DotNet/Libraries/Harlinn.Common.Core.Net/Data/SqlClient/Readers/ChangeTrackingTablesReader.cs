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

public class ChangeTrackingTablesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[change_tracking_tables]";
    public const string TableName = "change_tracking_tables";
    public const string ShortName = "ctt";
    public const string Sql = """
        SELECT
          ctt.[object_id],
          ctt.[is_track_columns_updated_on],
          ctt.[min_valid_version],
          ctt.[begin_version],
          ctt.[cleanup_version]
        FROM
          [sys].[change_tracking_tables] ctt
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int ISTRACKCOLUMNSUPDATEDON_FIELD_ID = 1;
    public const int MINVALIDVERSION_FIELD_ID = 2;
    public const int BEGINVERSION_FIELD_ID = 3;
    public const int CLEANUPVERSION_FIELD_ID = 4;


    public ChangeTrackingTablesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ChangeTrackingTablesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ChangeTrackingTablesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public bool IsTrackColumnsUpdatedOn
    {
        get
        {
            return base.GetBoolean(ISTRACKCOLUMNSUPDATEDON_FIELD_ID);
        }
    }

    public long? MinValidVersion
    {
        get
        {
            return base.GetNullableInt64(MINVALIDVERSION_FIELD_ID);
        }
    }

    public long? BeginVersion
    {
        get
        {
            return base.GetNullableInt64(BEGINVERSION_FIELD_ID);
        }
    }

    public long? CleanupVersion
    {
        get
        {
            return base.GetNullableInt64(CLEANUPVERSION_FIELD_ID);
        }
    }


    public Types.ChangeTrackingTablesDataType ToDataObject()
    {
        return new Types.ChangeTrackingTablesDataType(ObjectId,
            IsTrackColumnsUpdatedOn,
            MinValidVersion,
            BeginVersion,
            CleanupVersion);
    }

    public List<Types.ChangeTrackingTablesDataType> ToList()
    {
        var list = new List<Types.ChangeTrackingTablesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class AvailabilityDatabasesClusterReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[availability_databases_cluster]";
    public const string TableName = "availability_databases_cluster";
    public const string ShortName = "adc";
    public const string Sql = """
        SELECT
          adc.[group_id],
          adc.[group_database_id],
          adc.[database_name],
          adc.[truncation_lsn]
        FROM
          [sys].[availability_databases_cluster] adc
        """;

    public const int GROUPID_FIELD_ID = 0;
    public const int GROUPDATABASEID_FIELD_ID = 1;
    public const int DATABASENAME_FIELD_ID = 2;
    public const int TRUNCATIONLSN_FIELD_ID = 3;


    public AvailabilityDatabasesClusterReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AvailabilityDatabasesClusterReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AvailabilityDatabasesClusterReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid GroupId
    {
        get
        {
            return base.GetGuid(GROUPID_FIELD_ID);
        }
    }

    public Guid GroupDatabaseId
    {
        get
        {
            return base.GetGuid(GROUPDATABASEID_FIELD_ID);
        }
    }

    public string? DatabaseName
    {
        get
        {
            return base.GetNullableString(DATABASENAME_FIELD_ID);
        }
    }

    public decimal? TruncationLsn
    {
        get
        {
            return base.GetNullableDecimal(TRUNCATIONLSN_FIELD_ID);
        }
    }


    public Types.AvailabilityDatabasesClusterDataType ToDataObject()
    {
        return new Types.AvailabilityDatabasesClusterDataType(GroupId,
            GroupDatabaseId,
            DatabaseName,
            TruncationLsn);
    }

    public List<Types.AvailabilityDatabasesClusterDataType> ToList()
    {
        var list = new List<Types.AvailabilityDatabasesClusterDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

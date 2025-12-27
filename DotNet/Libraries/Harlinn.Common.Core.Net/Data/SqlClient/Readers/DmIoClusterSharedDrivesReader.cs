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

public class DmIoClusterSharedDrivesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_io_cluster_shared_drives]";
    public const string TableName = "dm_io_cluster_shared_drives";
    public const string ShortName = "dicsd";
    public const string Sql = """
        SELECT
          dicsd.[Drivename]
        FROM
          [sys].[dm_io_cluster_shared_drives] dicsd
        """;

    public const int DRIVENAME_FIELD_ID = 0;


    public DmIoClusterSharedDrivesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmIoClusterSharedDrivesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmIoClusterSharedDrivesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? Drivename
    {
        get
        {
            return base.GetNullableString(DRIVENAME_FIELD_ID);
        }
    }


    public Types.DmIoClusterSharedDrivesDataType ToDataObject()
    {
        return new Types.DmIoClusterSharedDrivesDataType(Drivename);
    }

    public List<Types.DmIoClusterSharedDrivesDataType> ToList()
    {
        var list = new List<Types.DmIoClusterSharedDrivesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

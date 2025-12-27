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

public class DmDbStoragePoolsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_storage_pools]";
    public const string TableName = "dm_db_storage_pools";
    public const string ShortName = "ddsp";
    public const string Sql = """
        SELECT
          ddsp.[storage_pool_id],
          ddsp.[Name],
          ddsp.[Location]
        FROM
          [sys].[dm_db_storage_pools] ddsp
        """;

    public const int STORAGEPOOLID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int LOCATION_FIELD_ID = 2;


    public DmDbStoragePoolsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbStoragePoolsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbStoragePoolsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int StoragePoolId
    {
        get
        {
            return base.GetInt32(STORAGEPOOLID_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public string Location
    {
        get
        {
            return base.GetString(LOCATION_FIELD_ID);
        }
    }


    public Types.DmDbStoragePoolsDataType ToDataObject()
    {
        return new Types.DmDbStoragePoolsDataType(StoragePoolId,
            Name,
            Location);
    }

    public List<Types.DmDbStoragePoolsDataType> ToList()
    {
        var list = new List<Types.DmDbStoragePoolsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

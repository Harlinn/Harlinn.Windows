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

public class DmDbFileSpaceUsageReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_file_space_usage]";
    public const string TableName = "dm_db_file_space_usage";
    public const string ShortName = "ddfsu";
    public const string Sql = """
        SELECT
          ddfsu.[database_id],
          ddfsu.[file_id],
          ddfsu.[filegroup_id],
          ddfsu.[total_page_count],
          ddfsu.[allocated_extent_page_count],
          ddfsu.[unallocated_extent_page_count],
          ddfsu.[version_store_reserved_page_count],
          ddfsu.[user_object_reserved_page_count],
          ddfsu.[internal_object_reserved_page_count],
          ddfsu.[mixed_extent_page_count],
          ddfsu.[modified_extent_page_count]
        FROM
          [sys].[dm_db_file_space_usage] ddfsu
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int FILEID_FIELD_ID = 1;
    public const int FILEGROUPID_FIELD_ID = 2;
    public const int TOTALPAGECOUNT_FIELD_ID = 3;
    public const int ALLOCATEDEXTENTPAGECOUNT_FIELD_ID = 4;
    public const int UNALLOCATEDEXTENTPAGECOUNT_FIELD_ID = 5;
    public const int VERSIONSTORERESERVEDPAGECOUNT_FIELD_ID = 6;
    public const int USEROBJECTRESERVEDPAGECOUNT_FIELD_ID = 7;
    public const int INTERNALOBJECTRESERVEDPAGECOUNT_FIELD_ID = 8;
    public const int MIXEDEXTENTPAGECOUNT_FIELD_ID = 9;
    public const int MODIFIEDEXTENTPAGECOUNT_FIELD_ID = 10;


    public DmDbFileSpaceUsageReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbFileSpaceUsageReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbFileSpaceUsageReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? DatabaseId
    {
        get
        {
            return base.GetNullableInt32(DATABASEID_FIELD_ID);
        }
    }

    public short? FileId
    {
        get
        {
            return base.GetNullableInt16(FILEID_FIELD_ID);
        }
    }

    public short? FilegroupId
    {
        get
        {
            return base.GetNullableInt16(FILEGROUPID_FIELD_ID);
        }
    }

    public long? TotalPageCount
    {
        get
        {
            return base.GetNullableInt64(TOTALPAGECOUNT_FIELD_ID);
        }
    }

    public long? AllocatedExtentPageCount
    {
        get
        {
            return base.GetNullableInt64(ALLOCATEDEXTENTPAGECOUNT_FIELD_ID);
        }
    }

    public long? UnallocatedExtentPageCount
    {
        get
        {
            return base.GetNullableInt64(UNALLOCATEDEXTENTPAGECOUNT_FIELD_ID);
        }
    }

    public long? VersionStoreReservedPageCount
    {
        get
        {
            return base.GetNullableInt64(VERSIONSTORERESERVEDPAGECOUNT_FIELD_ID);
        }
    }

    public long? UserObjectReservedPageCount
    {
        get
        {
            return base.GetNullableInt64(USEROBJECTRESERVEDPAGECOUNT_FIELD_ID);
        }
    }

    public long? InternalObjectReservedPageCount
    {
        get
        {
            return base.GetNullableInt64(INTERNALOBJECTRESERVEDPAGECOUNT_FIELD_ID);
        }
    }

    public long? MixedExtentPageCount
    {
        get
        {
            return base.GetNullableInt64(MIXEDEXTENTPAGECOUNT_FIELD_ID);
        }
    }

    public long? ModifiedExtentPageCount
    {
        get
        {
            return base.GetNullableInt64(MODIFIEDEXTENTPAGECOUNT_FIELD_ID);
        }
    }


    public Types.DmDbFileSpaceUsageDataType ToDataObject()
    {
        return new Types.DmDbFileSpaceUsageDataType(DatabaseId,
            FileId,
            FilegroupId,
            TotalPageCount,
            AllocatedExtentPageCount,
            UnallocatedExtentPageCount,
            VersionStoreReservedPageCount,
            UserObjectReservedPageCount,
            InternalObjectReservedPageCount,
            MixedExtentPageCount,
            ModifiedExtentPageCount);
    }

    public List<Types.DmDbFileSpaceUsageDataType> ToList()
    {
        var list = new List<Types.DmDbFileSpaceUsageDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class DmOsBufferDescriptorsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_buffer_descriptors]";
    public const string TableName = "dm_os_buffer_descriptors";
    public const string ShortName = "dobd";
    public const string Sql = """
        SELECT
          dobd.[database_id],
          dobd.[file_id],
          dobd.[page_id],
          dobd.[page_level],
          dobd.[allocation_unit_id],
          dobd.[page_type],
          dobd.[row_count],
          dobd.[free_space_in_bytes],
          dobd.[is_modified],
          dobd.[numa_node],
          dobd.[read_microsec],
          dobd.[is_in_bpool_extension],
          dobd.[error_code],
          dobd.[op_history]
        FROM
          [sys].[dm_os_buffer_descriptors] dobd
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int FILEID_FIELD_ID = 1;
    public const int PAGEID_FIELD_ID = 2;
    public const int PAGELEVEL_FIELD_ID = 3;
    public const int ALLOCATIONUNITID_FIELD_ID = 4;
    public const int PAGETYPE_FIELD_ID = 5;
    public const int ROWCOUNT_FIELD_ID = 6;
    public const int FREESPACEINBYTES_FIELD_ID = 7;
    public const int ISMODIFIED_FIELD_ID = 8;
    public const int NUMANODE_FIELD_ID = 9;
    public const int READMICROSEC_FIELD_ID = 10;
    public const int ISINBPOOLEXTENSION_FIELD_ID = 11;
    public const int ERRORCODE_FIELD_ID = 12;
    public const int OPHISTORY_FIELD_ID = 13;


    public DmOsBufferDescriptorsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsBufferDescriptorsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsBufferDescriptorsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int? FileId
    {
        get
        {
            return base.GetNullableInt32(FILEID_FIELD_ID);
        }
    }

    public int? PageId
    {
        get
        {
            return base.GetNullableInt32(PAGEID_FIELD_ID);
        }
    }

    public int? PageLevel
    {
        get
        {
            return base.GetNullableInt32(PAGELEVEL_FIELD_ID);
        }
    }

    public long? AllocationUnitId
    {
        get
        {
            return base.GetNullableInt64(ALLOCATIONUNITID_FIELD_ID);
        }
    }

    public string? PageType
    {
        get
        {
            return base.GetNullableString(PAGETYPE_FIELD_ID);
        }
    }

    public int? RowCount
    {
        get
        {
            return base.GetNullableInt32(ROWCOUNT_FIELD_ID);
        }
    }

    public int? FreeSpaceInBytes
    {
        get
        {
            return base.GetNullableInt32(FREESPACEINBYTES_FIELD_ID);
        }
    }

    public bool? IsModified
    {
        get
        {
            return base.GetNullableBoolean(ISMODIFIED_FIELD_ID);
        }
    }

    public int? NumaNode
    {
        get
        {
            return base.GetNullableInt32(NUMANODE_FIELD_ID);
        }
    }

    public long? ReadMicrosec
    {
        get
        {
            return base.GetNullableInt64(READMICROSEC_FIELD_ID);
        }
    }

    public bool? IsInBpoolExtension
    {
        get
        {
            return base.GetNullableBoolean(ISINBPOOLEXTENSION_FIELD_ID);
        }
    }

    public int? ErrorCode
    {
        get
        {
            return base.GetNullableInt32(ERRORCODE_FIELD_ID);
        }
    }

    public byte[]? OpHistory
    {
        get
        {
            return base.GetNullableBinary(OPHISTORY_FIELD_ID);
        }
    }


    public Types.DmOsBufferDescriptorsDataType ToDataObject()
    {
        return new Types.DmOsBufferDescriptorsDataType(DatabaseId,
            FileId,
            PageId,
            PageLevel,
            AllocationUnitId,
            PageType,
            RowCount,
            FreeSpaceInBytes,
            IsModified,
            NumaNode,
            ReadMicrosec,
            IsInBpoolExtension,
            ErrorCode,
            OpHistory);
    }

    public List<Types.DmOsBufferDescriptorsDataType> ToList()
    {
        var list = new List<Types.DmOsBufferDescriptorsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

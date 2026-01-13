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

public class DmOsMemoryObjectsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_memory_objects]";
    public const string TableName = "dm_os_memory_objects";
    public const string ShortName = "domo";
    public const string Sql = """
        SELECT
          domo.[memory_object_address],
          domo.[parent_address],
          domo.[pages_in_bytes],
          domo.[creation_options],
          domo.[bytes_used],
          domo.[Type],
          domo.[Name],
          domo.[memory_node_id],
          domo.[creation_time],
          domo.[page_size_in_bytes],
          domo.[max_pages_in_bytes],
          domo.[page_allocator_address],
          domo.[creation_stack_address],
          domo.[sequence_num],
          domo.[partition_type],
          domo.[partition_type_desc],
          domo.[contention_factor],
          domo.[waiting_tasks_count],
          domo.[exclusive_access_count]
        FROM
          [sys].[dm_os_memory_objects] domo
        """;

    public const int MEMORYOBJECTADDRESS_FIELD_ID = 0;
    public const int PARENTADDRESS_FIELD_ID = 1;
    public const int PAGESINBYTES_FIELD_ID = 2;
    public const int CREATIONOPTIONS_FIELD_ID = 3;
    public const int BYTESUSED_FIELD_ID = 4;
    public const int TYPE_FIELD_ID = 5;
    public const int NAME_FIELD_ID = 6;
    public const int MEMORYNODEID_FIELD_ID = 7;
    public const int CREATIONTIME_FIELD_ID = 8;
    public const int PAGESIZEINBYTES_FIELD_ID = 9;
    public const int MAXPAGESINBYTES_FIELD_ID = 10;
    public const int PAGEALLOCATORADDRESS_FIELD_ID = 11;
    public const int CREATIONSTACKADDRESS_FIELD_ID = 12;
    public const int SEQUENCENUM_FIELD_ID = 13;
    public const int PARTITIONTYPE_FIELD_ID = 14;
    public const int PARTITIONTYPEDESC_FIELD_ID = 15;
    public const int CONTENTIONFACTOR_FIELD_ID = 16;
    public const int WAITINGTASKSCOUNT_FIELD_ID = 17;
    public const int EXCLUSIVEACCESSCOUNT_FIELD_ID = 18;


    public DmOsMemoryObjectsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryObjectsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryObjectsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] MemoryObjectAddress
    {
        get
        {
            return base.GetBinary(MEMORYOBJECTADDRESS_FIELD_ID);
        }
    }

    public byte[]? ParentAddress
    {
        get
        {
            return base.GetNullableBinary(PARENTADDRESS_FIELD_ID);
        }
    }

    public long PagesInBytes
    {
        get
        {
            return base.GetInt64(PAGESINBYTES_FIELD_ID);
        }
    }

    public int? CreationOptions
    {
        get
        {
            return base.GetNullableInt32(CREATIONOPTIONS_FIELD_ID);
        }
    }

    public long? BytesUsed
    {
        get
        {
            return base.GetNullableInt64(BYTESUSED_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return base.GetString(TYPE_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public short MemoryNodeId
    {
        get
        {
            return base.GetInt16(MEMORYNODEID_FIELD_ID);
        }
    }

    public DateTime? CreationTime
    {
        get
        {
            return base.GetNullableDateTime(CREATIONTIME_FIELD_ID);
        }
    }

    public int PageSizeInBytes
    {
        get
        {
            return base.GetInt32(PAGESIZEINBYTES_FIELD_ID);
        }
    }

    public long MaxPagesInBytes
    {
        get
        {
            return base.GetInt64(MAXPAGESINBYTES_FIELD_ID);
        }
    }

    public byte[] PageAllocatorAddress
    {
        get
        {
            return base.GetBinary(PAGEALLOCATORADDRESS_FIELD_ID);
        }
    }

    public byte[]? CreationStackAddress
    {
        get
        {
            return base.GetNullableBinary(CREATIONSTACKADDRESS_FIELD_ID);
        }
    }

    public int? SequenceNum
    {
        get
        {
            return base.GetNullableInt32(SEQUENCENUM_FIELD_ID);
        }
    }

    public int PartitionType
    {
        get
        {
            return base.GetInt32(PARTITIONTYPE_FIELD_ID);
        }
    }

    public string PartitionTypeDesc
    {
        get
        {
            return base.GetString(PARTITIONTYPEDESC_FIELD_ID);
        }
    }

    public float? ContentionFactor
    {
        get
        {
            return base.GetNullableSingle(CONTENTIONFACTOR_FIELD_ID);
        }
    }

    public long? WaitingTasksCount
    {
        get
        {
            return base.GetNullableInt64(WAITINGTASKSCOUNT_FIELD_ID);
        }
    }

    public long? ExclusiveAccessCount
    {
        get
        {
            return base.GetNullableInt64(EXCLUSIVEACCESSCOUNT_FIELD_ID);
        }
    }


    public Types.DmOsMemoryObjectsDataType ToDataObject()
    {
        return new Types.DmOsMemoryObjectsDataType(MemoryObjectAddress,
            ParentAddress,
            PagesInBytes,
            CreationOptions,
            BytesUsed,
            Type,
            Name,
            MemoryNodeId,
            CreationTime,
            PageSizeInBytes,
            MaxPagesInBytes,
            PageAllocatorAddress,
            CreationStackAddress,
            SequenceNum,
            PartitionType,
            PartitionTypeDesc,
            ContentionFactor,
            WaitingTasksCount,
            ExclusiveAccessCount);
    }

    public List<Types.DmOsMemoryObjectsDataType> ToList()
    {
        var list = new List<Types.DmOsMemoryObjectsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

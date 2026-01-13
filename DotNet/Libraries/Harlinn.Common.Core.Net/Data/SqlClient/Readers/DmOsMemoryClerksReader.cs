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

public class DmOsMemoryClerksReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_memory_clerks]";
    public const string TableName = "dm_os_memory_clerks";
    public const string ShortName = "domc";
    public const string Sql = """
        SELECT
          domc.[memory_clerk_address],
          domc.[Type],
          domc.[Name],
          domc.[memory_node_id],
          domc.[pages_kb],
          domc.[virtual_memory_reserved_kb],
          domc.[virtual_memory_committed_kb],
          domc.[awe_allocated_kb],
          domc.[shared_memory_reserved_kb],
          domc.[shared_memory_committed_kb],
          domc.[page_size_in_bytes],
          domc.[page_allocator_address],
          domc.[host_address],
          domc.[parent_memory_broker_type]
        FROM
          [sys].[dm_os_memory_clerks] domc
        """;

    public const int MEMORYCLERKADDRESS_FIELD_ID = 0;
    public const int TYPE_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int MEMORYNODEID_FIELD_ID = 3;
    public const int PAGESKB_FIELD_ID = 4;
    public const int VIRTUALMEMORYRESERVEDKB_FIELD_ID = 5;
    public const int VIRTUALMEMORYCOMMITTEDKB_FIELD_ID = 6;
    public const int AWEALLOCATEDKB_FIELD_ID = 7;
    public const int SHAREDMEMORYRESERVEDKB_FIELD_ID = 8;
    public const int SHAREDMEMORYCOMMITTEDKB_FIELD_ID = 9;
    public const int PAGESIZEINBYTES_FIELD_ID = 10;
    public const int PAGEALLOCATORADDRESS_FIELD_ID = 11;
    public const int HOSTADDRESS_FIELD_ID = 12;
    public const int PARENTMEMORYBROKERTYPE_FIELD_ID = 13;


    public DmOsMemoryClerksReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryClerksReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryClerksReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] MemoryClerkAddress
    {
        get
        {
            return base.GetBinary(MEMORYCLERKADDRESS_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return base.GetString(TYPE_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public short MemoryNodeId
    {
        get
        {
            return base.GetInt16(MEMORYNODEID_FIELD_ID);
        }
    }

    public long PagesKb
    {
        get
        {
            return base.GetInt64(PAGESKB_FIELD_ID);
        }
    }

    public long VirtualMemoryReservedKb
    {
        get
        {
            return base.GetInt64(VIRTUALMEMORYRESERVEDKB_FIELD_ID);
        }
    }

    public long VirtualMemoryCommittedKb
    {
        get
        {
            return base.GetInt64(VIRTUALMEMORYCOMMITTEDKB_FIELD_ID);
        }
    }

    public long AweAllocatedKb
    {
        get
        {
            return base.GetInt64(AWEALLOCATEDKB_FIELD_ID);
        }
    }

    public long SharedMemoryReservedKb
    {
        get
        {
            return base.GetInt64(SHAREDMEMORYRESERVEDKB_FIELD_ID);
        }
    }

    public long SharedMemoryCommittedKb
    {
        get
        {
            return base.GetInt64(SHAREDMEMORYCOMMITTEDKB_FIELD_ID);
        }
    }

    public long PageSizeInBytes
    {
        get
        {
            return base.GetInt64(PAGESIZEINBYTES_FIELD_ID);
        }
    }

    public byte[] PageAllocatorAddress
    {
        get
        {
            return base.GetBinary(PAGEALLOCATORADDRESS_FIELD_ID);
        }
    }

    public byte[] HostAddress
    {
        get
        {
            return base.GetBinary(HOSTADDRESS_FIELD_ID);
        }
    }

    public string? ParentMemoryBrokerType
    {
        get
        {
            return base.GetNullableString(PARENTMEMORYBROKERTYPE_FIELD_ID);
        }
    }


    public Types.DmOsMemoryClerksDataType ToDataObject()
    {
        return new Types.DmOsMemoryClerksDataType(MemoryClerkAddress,
            Type,
            Name,
            MemoryNodeId,
            PagesKb,
            VirtualMemoryReservedKb,
            VirtualMemoryCommittedKb,
            AweAllocatedKb,
            SharedMemoryReservedKb,
            SharedMemoryCommittedKb,
            PageSizeInBytes,
            PageAllocatorAddress,
            HostAddress,
            ParentMemoryBrokerType);
    }

    public List<Types.DmOsMemoryClerksDataType> ToList()
    {
        var list = new List<Types.DmOsMemoryClerksDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

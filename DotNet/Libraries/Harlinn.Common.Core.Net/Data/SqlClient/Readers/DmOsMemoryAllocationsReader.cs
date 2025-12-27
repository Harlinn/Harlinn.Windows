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

public class DmOsMemoryAllocationsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_memory_allocations]";
    public const string TableName = "dm_os_memory_allocations";
    public const string ShortName = "doma";
    public const string Sql = """
        SELECT
          doma.[memory_allocation_address],
          doma.[size_in_bytes],
          doma.[creation_time],
          doma.[memory_object_address],
          doma.[memory_node_id],
          doma.[allocator_stack_address],
          doma.[source_file],
          doma.[line_num],
          doma.[sequence_num],
          doma.[Tag]
        FROM
          [sys].[dm_os_memory_allocations] doma
        """;

    public const int MEMORYALLOCATIONADDRESS_FIELD_ID = 0;
    public const int SIZEINBYTES_FIELD_ID = 1;
    public const int CREATIONTIME_FIELD_ID = 2;
    public const int MEMORYOBJECTADDRESS_FIELD_ID = 3;
    public const int MEMORYNODEID_FIELD_ID = 4;
    public const int ALLOCATORSTACKADDRESS_FIELD_ID = 5;
    public const int SOURCEFILE_FIELD_ID = 6;
    public const int LINENUM_FIELD_ID = 7;
    public const int SEQUENCENUM_FIELD_ID = 8;
    public const int TAG_FIELD_ID = 9;


    public DmOsMemoryAllocationsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryAllocationsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsMemoryAllocationsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] MemoryAllocationAddress
    {
        get
        {
            return base.GetBinary(MEMORYALLOCATIONADDRESS_FIELD_ID);
        }
    }

    public long SizeInBytes
    {
        get
        {
            return base.GetInt64(SIZEINBYTES_FIELD_ID);
        }
    }

    public DateTime CreationTime
    {
        get
        {
            return base.GetDateTime(CREATIONTIME_FIELD_ID);
        }
    }

    public byte[] MemoryObjectAddress
    {
        get
        {
            return base.GetBinary(MEMORYOBJECTADDRESS_FIELD_ID);
        }
    }

    public short MemoryNodeId
    {
        get
        {
            return base.GetInt16(MEMORYNODEID_FIELD_ID);
        }
    }

    public byte[] AllocatorStackAddress
    {
        get
        {
            return base.GetBinary(ALLOCATORSTACKADDRESS_FIELD_ID);
        }
    }

    public string? SourceFile
    {
        get
        {
            return base.GetNullableString(SOURCEFILE_FIELD_ID);
        }
    }

    public int LineNum
    {
        get
        {
            return base.GetInt32(LINENUM_FIELD_ID);
        }
    }

    public int SequenceNum
    {
        get
        {
            return base.GetInt32(SEQUENCENUM_FIELD_ID);
        }
    }

    public int Tag
    {
        get
        {
            return base.GetInt32(TAG_FIELD_ID);
        }
    }


    public Types.DmOsMemoryAllocationsDataType ToDataObject()
    {
        return new Types.DmOsMemoryAllocationsDataType(MemoryAllocationAddress,
            SizeInBytes,
            CreationTime,
            MemoryObjectAddress,
            MemoryNodeId,
            AllocatorStackAddress,
            SourceFile,
            LineNum,
            SequenceNum,
            Tag);
    }

    public List<Types.DmOsMemoryAllocationsDataType> ToList()
    {
        var list = new List<Types.DmOsMemoryAllocationsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

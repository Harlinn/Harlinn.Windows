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

public class DmXeSessionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_xe_sessions]";
    public const string TableName = "dm_xe_sessions";
    public const string ShortName = "dxs";
    public const string Sql = """
        SELECT
          dxs.[Address],
          dxs.[Name],
          dxs.[pending_buffers],
          dxs.[total_regular_buffers],
          dxs.[regular_buffer_size],
          dxs.[total_large_buffers],
          dxs.[large_buffer_size],
          dxs.[total_buffer_size],
          dxs.[buffer_policy_flags],
          dxs.[buffer_policy_desc],
          dxs.[Flags],
          dxs.[flag_desc],
          dxs.[dropped_event_count],
          dxs.[dropped_buffer_count],
          dxs.[blocked_event_fire_time],
          dxs.[create_time],
          dxs.[largest_event_dropped_size],
          dxs.[session_source],
          dxs.[buffer_processed_count],
          dxs.[buffer_full_count],
          dxs.[total_bytes_generated]
        FROM
          [sys].[dm_xe_sessions] dxs
        """;

    public const int ADDRESS_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int PENDINGBUFFERS_FIELD_ID = 2;
    public const int TOTALREGULARBUFFERS_FIELD_ID = 3;
    public const int REGULARBUFFERSIZE_FIELD_ID = 4;
    public const int TOTALLARGEBUFFERS_FIELD_ID = 5;
    public const int LARGEBUFFERSIZE_FIELD_ID = 6;
    public const int TOTALBUFFERSIZE_FIELD_ID = 7;
    public const int BUFFERPOLICYFLAGS_FIELD_ID = 8;
    public const int BUFFERPOLICYDESC_FIELD_ID = 9;
    public const int FLAGS_FIELD_ID = 10;
    public const int FLAGDESC_FIELD_ID = 11;
    public const int DROPPEDEVENTCOUNT_FIELD_ID = 12;
    public const int DROPPEDBUFFERCOUNT_FIELD_ID = 13;
    public const int BLOCKEDEVENTFIRETIME_FIELD_ID = 14;
    public const int CREATETIME_FIELD_ID = 15;
    public const int LARGESTEVENTDROPPEDSIZE_FIELD_ID = 16;
    public const int SESSIONSOURCE_FIELD_ID = 17;
    public const int BUFFERPROCESSEDCOUNT_FIELD_ID = 18;
    public const int BUFFERFULLCOUNT_FIELD_ID = 19;
    public const int TOTALBYTESGENERATED_FIELD_ID = 20;


    public DmXeSessionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmXeSessionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmXeSessionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] Address
    {
        get
        {
            return base.GetBinary(ADDRESS_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int PendingBuffers
    {
        get
        {
            return base.GetInt32(PENDINGBUFFERS_FIELD_ID);
        }
    }

    public int TotalRegularBuffers
    {
        get
        {
            return base.GetInt32(TOTALREGULARBUFFERS_FIELD_ID);
        }
    }

    public long RegularBufferSize
    {
        get
        {
            return base.GetInt64(REGULARBUFFERSIZE_FIELD_ID);
        }
    }

    public int TotalLargeBuffers
    {
        get
        {
            return base.GetInt32(TOTALLARGEBUFFERS_FIELD_ID);
        }
    }

    public long LargeBufferSize
    {
        get
        {
            return base.GetInt64(LARGEBUFFERSIZE_FIELD_ID);
        }
    }

    public long TotalBufferSize
    {
        get
        {
            return base.GetInt64(TOTALBUFFERSIZE_FIELD_ID);
        }
    }

    public int BufferPolicyFlags
    {
        get
        {
            return base.GetInt32(BUFFERPOLICYFLAGS_FIELD_ID);
        }
    }

    public string BufferPolicyDesc
    {
        get
        {
            return base.GetString(BUFFERPOLICYDESC_FIELD_ID);
        }
    }

    public int Flags
    {
        get
        {
            return base.GetInt32(FLAGS_FIELD_ID);
        }
    }

    public string FlagDesc
    {
        get
        {
            return base.GetString(FLAGDESC_FIELD_ID);
        }
    }

    public int DroppedEventCount
    {
        get
        {
            return base.GetInt32(DROPPEDEVENTCOUNT_FIELD_ID);
        }
    }

    public int DroppedBufferCount
    {
        get
        {
            return base.GetInt32(DROPPEDBUFFERCOUNT_FIELD_ID);
        }
    }

    public int BlockedEventFireTime
    {
        get
        {
            return base.GetInt32(BLOCKEDEVENTFIRETIME_FIELD_ID);
        }
    }

    public DateTime CreateTime
    {
        get
        {
            return base.GetDateTime(CREATETIME_FIELD_ID);
        }
    }

    public int LargestEventDroppedSize
    {
        get
        {
            return base.GetInt32(LARGESTEVENTDROPPEDSIZE_FIELD_ID);
        }
    }

    public string SessionSource
    {
        get
        {
            return base.GetString(SESSIONSOURCE_FIELD_ID);
        }
    }

    public long BufferProcessedCount
    {
        get
        {
            return base.GetInt64(BUFFERPROCESSEDCOUNT_FIELD_ID);
        }
    }

    public long BufferFullCount
    {
        get
        {
            return base.GetInt64(BUFFERFULLCOUNT_FIELD_ID);
        }
    }

    public long TotalBytesGenerated
    {
        get
        {
            return base.GetInt64(TOTALBYTESGENERATED_FIELD_ID);
        }
    }


    public Types.DmXeSessionsDataType ToDataObject()
    {
        return new Types.DmXeSessionsDataType(Address,
            Name,
            PendingBuffers,
            TotalRegularBuffers,
            RegularBufferSize,
            TotalLargeBuffers,
            LargeBufferSize,
            TotalBufferSize,
            BufferPolicyFlags,
            BufferPolicyDesc,
            Flags,
            FlagDesc,
            DroppedEventCount,
            DroppedBufferCount,
            BlockedEventFireTime,
            CreateTime,
            LargestEventDroppedSize,
            SessionSource,
            BufferProcessedCount,
            BufferFullCount,
            TotalBytesGenerated);
    }

    public List<Types.DmXeSessionsDataType> ToList()
    {
        var list = new List<Types.DmXeSessionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class DmPalNetStatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_pal_net_stats]";
    public const string TableName = "dm_pal_net_stats";
    public const string ShortName = "dpns";
    public const string Sql = """
        SELECT
          dpns.[Interface],
          dpns.[recv_bytes],
          dpns.[recv_packets],
          dpns.[Errors],
          dpns.[Drops],
          dpns.[Fifo],
          dpns.[Frame],
          dpns.[Compressed],
          dpns.[Multicast]
        FROM
          [sys].[dm_pal_net_stats] dpns
        """;

    public const int INTERFACE_FIELD_ID = 0;
    public const int RECVBYTES_FIELD_ID = 1;
    public const int RECVPACKETS_FIELD_ID = 2;
    public const int ERRORS_FIELD_ID = 3;
    public const int DROPS_FIELD_ID = 4;
    public const int FIFO_FIELD_ID = 5;
    public const int FRAME_FIELD_ID = 6;
    public const int COMPRESSED_FIELD_ID = 7;
    public const int MULTICAST_FIELD_ID = 8;


    public DmPalNetStatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmPalNetStatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmPalNetStatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Interface
    {
        get
        {
            return base.GetString(INTERFACE_FIELD_ID);
        }
    }

    public long RecvBytes
    {
        get
        {
            return base.GetInt64(RECVBYTES_FIELD_ID);
        }
    }

    public long RecvPackets
    {
        get
        {
            return base.GetInt64(RECVPACKETS_FIELD_ID);
        }
    }

    public long Errors
    {
        get
        {
            return base.GetInt64(ERRORS_FIELD_ID);
        }
    }

    public long Drops
    {
        get
        {
            return base.GetInt64(DROPS_FIELD_ID);
        }
    }

    public long Fifo
    {
        get
        {
            return base.GetInt64(FIFO_FIELD_ID);
        }
    }

    public long Frame
    {
        get
        {
            return base.GetInt64(FRAME_FIELD_ID);
        }
    }

    public long Compressed
    {
        get
        {
            return base.GetInt64(COMPRESSED_FIELD_ID);
        }
    }

    public long Multicast
    {
        get
        {
            return base.GetInt64(MULTICAST_FIELD_ID);
        }
    }


    public Types.DmPalNetStatsDataType ToDataObject()
    {
        return new Types.DmPalNetStatsDataType(Interface,
            RecvBytes,
            RecvPackets,
            Errors,
            Drops,
            Fifo,
            Frame,
            Compressed,
            Multicast);
    }

    public List<Types.DmPalNetStatsDataType> ToList()
    {
        var list = new List<Types.DmPalNetStatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

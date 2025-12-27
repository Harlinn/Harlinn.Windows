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

public class DmOsRingBuffersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_ring_buffers]";
    public const string TableName = "dm_os_ring_buffers";
    public const string ShortName = "dorb";
    public const string Sql = """
        SELECT
          dorb.[ring_buffer_address],
          dorb.[ring_buffer_type],
          dorb.[Timestamp],
          dorb.[Record]
        FROM
          [sys].[dm_os_ring_buffers] dorb
        """;

    public const int RINGBUFFERADDRESS_FIELD_ID = 0;
    public const int RINGBUFFERTYPE_FIELD_ID = 1;
    public const int TIMESTAMP_FIELD_ID = 2;
    public const int RECORD_FIELD_ID = 3;


    public DmOsRingBuffersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsRingBuffersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsRingBuffersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] RingBufferAddress
    {
        get
        {
            return base.GetBinary(RINGBUFFERADDRESS_FIELD_ID);
        }
    }

    public string RingBufferType
    {
        get
        {
            return base.GetString(RINGBUFFERTYPE_FIELD_ID);
        }
    }

    public long Timestamp
    {
        get
        {
            return base.GetInt64(TIMESTAMP_FIELD_ID);
        }
    }

    public string? Record
    {
        get
        {
            return base.GetNullableString(RECORD_FIELD_ID);
        }
    }


    public Types.DmOsRingBuffersDataType ToDataObject()
    {
        return new Types.DmOsRingBuffersDataType(RingBufferAddress,
            RingBufferType,
            Timestamp,
            Record);
    }

    public List<Types.DmOsRingBuffersDataType> ToList()
    {
        var list = new List<Types.DmOsRingBuffersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

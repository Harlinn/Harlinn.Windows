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

public class DmTcpListenerStatesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tcp_listener_states]";
    public const string TableName = "dm_tcp_listener_states";
    public const string ShortName = "dtls";
    public const string Sql = """
        SELECT
          dtls.[listener_id],
          dtls.[ip_address],
          dtls.[is_ipv4],
          dtls.[Port],
          dtls.[Type],
          dtls.[type_desc],
          dtls.[State],
          dtls.[state_desc],
          dtls.[start_time]
        FROM
          [sys].[dm_tcp_listener_states] dtls
        """;

    public const int LISTENERID_FIELD_ID = 0;
    public const int IPADDRESS_FIELD_ID = 1;
    public const int ISIPV4_FIELD_ID = 2;
    public const int PORT_FIELD_ID = 3;
    public const int TYPE_FIELD_ID = 4;
    public const int TYPEDESC_FIELD_ID = 5;
    public const int STATE_FIELD_ID = 6;
    public const int STATEDESC_FIELD_ID = 7;
    public const int STARTTIME_FIELD_ID = 8;


    public DmTcpListenerStatesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTcpListenerStatesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTcpListenerStatesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ListenerId
    {
        get
        {
            return base.GetInt32(LISTENERID_FIELD_ID);
        }
    }

    public string IpAddress
    {
        get
        {
            return base.GetString(IPADDRESS_FIELD_ID);
        }
    }

    public bool IsIpv4
    {
        get
        {
            return base.GetBoolean(ISIPV4_FIELD_ID);
        }
    }

    public int Port
    {
        get
        {
            return base.GetInt32(PORT_FIELD_ID);
        }
    }

    public short Type
    {
        get
        {
            return base.GetInt16(TYPE_FIELD_ID);
        }
    }

    public string TypeDesc
    {
        get
        {
            return base.GetString(TYPEDESC_FIELD_ID);
        }
    }

    public short State
    {
        get
        {
            return base.GetInt16(STATE_FIELD_ID);
        }
    }

    public string StateDesc
    {
        get
        {
            return base.GetString(STATEDESC_FIELD_ID);
        }
    }

    public DateTime StartTime
    {
        get
        {
            return base.GetDateTime(STARTTIME_FIELD_ID);
        }
    }


    public Types.DmTcpListenerStatesDataType ToDataObject()
    {
        return new Types.DmTcpListenerStatesDataType(ListenerId,
            IpAddress,
            IsIpv4,
            Port,
            Type,
            TypeDesc,
            State,
            StateDesc,
            StartTime);
    }

    public List<Types.DmTcpListenerStatesDataType> ToList()
    {
        var list = new List<Types.DmTcpListenerStatesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

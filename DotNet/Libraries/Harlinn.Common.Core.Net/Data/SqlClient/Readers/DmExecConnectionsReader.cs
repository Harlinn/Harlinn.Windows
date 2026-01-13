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

public class DmExecConnectionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_exec_connections]";
    public const string TableName = "dm_exec_connections";
    public const string ShortName = "dec";
    public const string Sql = """
        SELECT
          dec.[session_id],
          dec.[most_recent_session_id],
          dec.[connect_time],
          dec.[net_transport],
          dec.[protocol_type],
          dec.[protocol_version],
          dec.[endpoint_id],
          dec.[encrypt_option],
          dec.[auth_scheme],
          dec.[node_affinity],
          dec.[num_reads],
          dec.[num_writes],
          dec.[last_read],
          dec.[last_write],
          dec.[net_packet_size],
          dec.[client_net_address],
          dec.[client_tcp_port],
          dec.[local_net_address],
          dec.[local_tcp_port],
          dec.[connection_id],
          dec.[parent_connection_id],
          dec.[most_recent_sql_handle]
        FROM
          [sys].[dm_exec_connections] dec
        """;

    public const int SESSIONID_FIELD_ID = 0;
    public const int MOSTRECENTSESSIONID_FIELD_ID = 1;
    public const int CONNECTTIME_FIELD_ID = 2;
    public const int NETTRANSPORT_FIELD_ID = 3;
    public const int PROTOCOLTYPE_FIELD_ID = 4;
    public const int PROTOCOLVERSION_FIELD_ID = 5;
    public const int ENDPOINTID_FIELD_ID = 6;
    public const int ENCRYPTOPTION_FIELD_ID = 7;
    public const int AUTHSCHEME_FIELD_ID = 8;
    public const int NODEAFFINITY_FIELD_ID = 9;
    public const int NUMREADS_FIELD_ID = 10;
    public const int NUMWRITES_FIELD_ID = 11;
    public const int LASTREAD_FIELD_ID = 12;
    public const int LASTWRITE_FIELD_ID = 13;
    public const int NETPACKETSIZE_FIELD_ID = 14;
    public const int CLIENTNETADDRESS_FIELD_ID = 15;
    public const int CLIENTTCPPORT_FIELD_ID = 16;
    public const int LOCALNETADDRESS_FIELD_ID = 17;
    public const int LOCALTCPPORT_FIELD_ID = 18;
    public const int CONNECTIONID_FIELD_ID = 19;
    public const int PARENTCONNECTIONID_FIELD_ID = 20;
    public const int MOSTRECENTSQLHANDLE_FIELD_ID = 21;


    public DmExecConnectionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExecConnectionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExecConnectionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? SessionId
    {
        get
        {
            return base.GetNullableInt32(SESSIONID_FIELD_ID);
        }
    }

    public int? MostRecentSessionId
    {
        get
        {
            return base.GetNullableInt32(MOSTRECENTSESSIONID_FIELD_ID);
        }
    }

    public DateTime ConnectTime
    {
        get
        {
            return base.GetDateTime(CONNECTTIME_FIELD_ID);
        }
    }

    public string NetTransport
    {
        get
        {
            return base.GetString(NETTRANSPORT_FIELD_ID);
        }
    }

    public string? ProtocolType
    {
        get
        {
            return base.GetNullableString(PROTOCOLTYPE_FIELD_ID);
        }
    }

    public int? ProtocolVersion
    {
        get
        {
            return base.GetNullableInt32(PROTOCOLVERSION_FIELD_ID);
        }
    }

    public int? EndpointId
    {
        get
        {
            return base.GetNullableInt32(ENDPOINTID_FIELD_ID);
        }
    }

    public string EncryptOption
    {
        get
        {
            return base.GetString(ENCRYPTOPTION_FIELD_ID);
        }
    }

    public string AuthScheme
    {
        get
        {
            return base.GetString(AUTHSCHEME_FIELD_ID);
        }
    }

    public short NodeAffinity
    {
        get
        {
            return base.GetInt16(NODEAFFINITY_FIELD_ID);
        }
    }

    public int? NumReads
    {
        get
        {
            return base.GetNullableInt32(NUMREADS_FIELD_ID);
        }
    }

    public int? NumWrites
    {
        get
        {
            return base.GetNullableInt32(NUMWRITES_FIELD_ID);
        }
    }

    public DateTime? LastRead
    {
        get
        {
            return base.GetNullableDateTime(LASTREAD_FIELD_ID);
        }
    }

    public DateTime? LastWrite
    {
        get
        {
            return base.GetNullableDateTime(LASTWRITE_FIELD_ID);
        }
    }

    public int? NetPacketSize
    {
        get
        {
            return base.GetNullableInt32(NETPACKETSIZE_FIELD_ID);
        }
    }

    public string? ClientNetAddress
    {
        get
        {
            return base.GetNullableString(CLIENTNETADDRESS_FIELD_ID);
        }
    }

    public int? ClientTcpPort
    {
        get
        {
            return base.GetNullableInt32(CLIENTTCPPORT_FIELD_ID);
        }
    }

    public string? LocalNetAddress
    {
        get
        {
            return base.GetNullableString(LOCALNETADDRESS_FIELD_ID);
        }
    }

    public int? LocalTcpPort
    {
        get
        {
            return base.GetNullableInt32(LOCALTCPPORT_FIELD_ID);
        }
    }

    public Guid ConnectionId
    {
        get
        {
            return base.GetGuid(CONNECTIONID_FIELD_ID);
        }
    }

    public Guid? ParentConnectionId
    {
        get
        {
            return base.GetNullableGuid(PARENTCONNECTIONID_FIELD_ID);
        }
    }

    public byte[]? MostRecentSqlHandle
    {
        get
        {
            return base.GetNullableBinary(MOSTRECENTSQLHANDLE_FIELD_ID);
        }
    }


    public Types.DmExecConnectionsDataType ToDataObject()
    {
        return new Types.DmExecConnectionsDataType(SessionId,
            MostRecentSessionId,
            ConnectTime,
            NetTransport,
            ProtocolType,
            ProtocolVersion,
            EndpointId,
            EncryptOption,
            AuthScheme,
            NodeAffinity,
            NumReads,
            NumWrites,
            LastRead,
            LastWrite,
            NetPacketSize,
            ClientNetAddress,
            ClientTcpPort,
            LocalNetAddress,
            LocalTcpPort,
            ConnectionId,
            ParentConnectionId,
            MostRecentSqlHandle);
    }

    public List<Types.DmExecConnectionsDataType> ToList()
    {
        var list = new List<Types.DmExecConnectionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

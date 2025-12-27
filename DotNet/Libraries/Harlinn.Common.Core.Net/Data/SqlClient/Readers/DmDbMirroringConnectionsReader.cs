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

public class DmDbMirroringConnectionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_mirroring_connections]";
    public const string TableName = "dm_db_mirroring_connections";
    public const string ShortName = "ddmc";
    public const string Sql = """
        SELECT
          ddmc.[connection_id],
          ddmc.[transport_stream_id],
          ddmc.[State],
          ddmc.[state_desc],
          ddmc.[connect_time],
          ddmc.[login_time],
          ddmc.[authentication_method],
          ddmc.[principal_name],
          ddmc.[remote_user_name],
          ddmc.[last_activity_time],
          ddmc.[is_accept],
          ddmc.[login_state],
          ddmc.[login_state_desc],
          ddmc.[peer_certificate_id],
          ddmc.[encryption_algorithm],
          ddmc.[encryption_algorithm_desc],
          ddmc.[receives_posted],
          ddmc.[is_receive_flow_controlled],
          ddmc.[sends_posted],
          ddmc.[is_send_flow_controlled],
          ddmc.[total_bytes_sent],
          ddmc.[total_bytes_received],
          ddmc.[total_fragments_sent],
          ddmc.[total_fragments_received],
          ddmc.[total_sends],
          ddmc.[total_receives],
          ddmc.[peer_arbitration_id],
          ddmc.[Address]
        FROM
          [sys].[dm_db_mirroring_connections] ddmc
        """;

    public const int CONNECTIONID_FIELD_ID = 0;
    public const int TRANSPORTSTREAMID_FIELD_ID = 1;
    public const int STATE_FIELD_ID = 2;
    public const int STATEDESC_FIELD_ID = 3;
    public const int CONNECTTIME_FIELD_ID = 4;
    public const int LOGINTIME_FIELD_ID = 5;
    public const int AUTHENTICATIONMETHOD_FIELD_ID = 6;
    public const int PRINCIPALNAME_FIELD_ID = 7;
    public const int REMOTEUSERNAME_FIELD_ID = 8;
    public const int LASTACTIVITYTIME_FIELD_ID = 9;
    public const int ISACCEPT_FIELD_ID = 10;
    public const int LOGINSTATE_FIELD_ID = 11;
    public const int LOGINSTATEDESC_FIELD_ID = 12;
    public const int PEERCERTIFICATEID_FIELD_ID = 13;
    public const int ENCRYPTIONALGORITHM_FIELD_ID = 14;
    public const int ENCRYPTIONALGORITHMDESC_FIELD_ID = 15;
    public const int RECEIVESPOSTED_FIELD_ID = 16;
    public const int ISRECEIVEFLOWCONTROLLED_FIELD_ID = 17;
    public const int SENDSPOSTED_FIELD_ID = 18;
    public const int ISSENDFLOWCONTROLLED_FIELD_ID = 19;
    public const int TOTALBYTESSENT_FIELD_ID = 20;
    public const int TOTALBYTESRECEIVED_FIELD_ID = 21;
    public const int TOTALFRAGMENTSSENT_FIELD_ID = 22;
    public const int TOTALFRAGMENTSRECEIVED_FIELD_ID = 23;
    public const int TOTALSENDS_FIELD_ID = 24;
    public const int TOTALRECEIVES_FIELD_ID = 25;
    public const int PEERARBITRATIONID_FIELD_ID = 26;
    public const int ADDRESS_FIELD_ID = 27;


    public DmDbMirroringConnectionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbMirroringConnectionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbMirroringConnectionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid? ConnectionId
    {
        get
        {
            return base.GetNullableGuid(CONNECTIONID_FIELD_ID);
        }
    }

    public Guid? TransportStreamId
    {
        get
        {
            return base.GetNullableGuid(TRANSPORTSTREAMID_FIELD_ID);
        }
    }

    public short? State
    {
        get
        {
            return base.GetNullableInt16(STATE_FIELD_ID);
        }
    }

    public string? StateDesc
    {
        get
        {
            return base.GetNullableString(STATEDESC_FIELD_ID);
        }
    }

    public DateTime? ConnectTime
    {
        get
        {
            return base.GetNullableDateTime(CONNECTTIME_FIELD_ID);
        }
    }

    public DateTime? LoginTime
    {
        get
        {
            return base.GetNullableDateTime(LOGINTIME_FIELD_ID);
        }
    }

    public string? AuthenticationMethod
    {
        get
        {
            return base.GetNullableString(AUTHENTICATIONMETHOD_FIELD_ID);
        }
    }

    public string? PrincipalName
    {
        get
        {
            return base.GetNullableString(PRINCIPALNAME_FIELD_ID);
        }
    }

    public string? RemoteUserName
    {
        get
        {
            return base.GetNullableString(REMOTEUSERNAME_FIELD_ID);
        }
    }

    public DateTime? LastActivityTime
    {
        get
        {
            return base.GetNullableDateTime(LASTACTIVITYTIME_FIELD_ID);
        }
    }

    public bool? IsAccept
    {
        get
        {
            return base.GetNullableBoolean(ISACCEPT_FIELD_ID);
        }
    }

    public short? LoginState
    {
        get
        {
            return base.GetNullableInt16(LOGINSTATE_FIELD_ID);
        }
    }

    public string? LoginStateDesc
    {
        get
        {
            return base.GetNullableString(LOGINSTATEDESC_FIELD_ID);
        }
    }

    public int? PeerCertificateId
    {
        get
        {
            return base.GetNullableInt32(PEERCERTIFICATEID_FIELD_ID);
        }
    }

    public short? EncryptionAlgorithm
    {
        get
        {
            return base.GetNullableInt16(ENCRYPTIONALGORITHM_FIELD_ID);
        }
    }

    public string? EncryptionAlgorithmDesc
    {
        get
        {
            return base.GetNullableString(ENCRYPTIONALGORITHMDESC_FIELD_ID);
        }
    }

    public short? ReceivesPosted
    {
        get
        {
            return base.GetNullableInt16(RECEIVESPOSTED_FIELD_ID);
        }
    }

    public bool? IsReceiveFlowControlled
    {
        get
        {
            return base.GetNullableBoolean(ISRECEIVEFLOWCONTROLLED_FIELD_ID);
        }
    }

    public short? SendsPosted
    {
        get
        {
            return base.GetNullableInt16(SENDSPOSTED_FIELD_ID);
        }
    }

    public bool? IsSendFlowControlled
    {
        get
        {
            return base.GetNullableBoolean(ISSENDFLOWCONTROLLED_FIELD_ID);
        }
    }

    public long? TotalBytesSent
    {
        get
        {
            return base.GetNullableInt64(TOTALBYTESSENT_FIELD_ID);
        }
    }

    public long? TotalBytesReceived
    {
        get
        {
            return base.GetNullableInt64(TOTALBYTESRECEIVED_FIELD_ID);
        }
    }

    public long? TotalFragmentsSent
    {
        get
        {
            return base.GetNullableInt64(TOTALFRAGMENTSSENT_FIELD_ID);
        }
    }

    public long? TotalFragmentsReceived
    {
        get
        {
            return base.GetNullableInt64(TOTALFRAGMENTSRECEIVED_FIELD_ID);
        }
    }

    public long? TotalSends
    {
        get
        {
            return base.GetNullableInt64(TOTALSENDS_FIELD_ID);
        }
    }

    public long? TotalReceives
    {
        get
        {
            return base.GetNullableInt64(TOTALRECEIVES_FIELD_ID);
        }
    }

    public Guid? PeerArbitrationId
    {
        get
        {
            return base.GetNullableGuid(PEERARBITRATIONID_FIELD_ID);
        }
    }

    public string? Address
    {
        get
        {
            return base.GetNullableString(ADDRESS_FIELD_ID);
        }
    }


    public Types.DmDbMirroringConnectionsDataType ToDataObject()
    {
        return new Types.DmDbMirroringConnectionsDataType(ConnectionId,
            TransportStreamId,
            State,
            StateDesc,
            ConnectTime,
            LoginTime,
            AuthenticationMethod,
            PrincipalName,
            RemoteUserName,
            LastActivityTime,
            IsAccept,
            LoginState,
            LoginStateDesc,
            PeerCertificateId,
            EncryptionAlgorithm,
            EncryptionAlgorithmDesc,
            ReceivesPosted,
            IsReceiveFlowControlled,
            SendsPosted,
            IsSendFlowControlled,
            TotalBytesSent,
            TotalBytesReceived,
            TotalFragmentsSent,
            TotalFragmentsReceived,
            TotalSends,
            TotalReceives,
            PeerArbitrationId,
            Address);
    }

    public List<Types.DmDbMirroringConnectionsDataType> ToList()
    {
        var list = new List<Types.DmDbMirroringConnectionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

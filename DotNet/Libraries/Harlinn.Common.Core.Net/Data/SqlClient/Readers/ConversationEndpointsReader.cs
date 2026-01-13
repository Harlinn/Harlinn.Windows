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

public class ConversationEndpointsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[conversation_endpoints]";
    public const string TableName = "conversation_endpoints";
    public const string ShortName = "ce";
    public const string Sql = """
        SELECT
          ce.[conversation_handle],
          ce.[conversation_id],
          ce.[is_initiator],
          ce.[service_contract_id],
          ce.[conversation_group_id],
          ce.[service_id],
          ce.[Lifetime],
          ce.[State],
          ce.[state_desc],
          ce.[far_service],
          ce.[far_broker_instance],
          ce.[principal_id],
          ce.[far_principal_id],
          ce.[outbound_session_key_identifier],
          ce.[inbound_session_key_identifier],
          ce.[security_timestamp],
          ce.[dialog_timer],
          ce.[send_sequence],
          ce.[last_send_tran_id],
          ce.[end_dialog_sequence],
          ce.[receive_sequence],
          ce.[receive_sequence_frag],
          ce.[system_sequence],
          ce.[first_out_of_order_sequence],
          ce.[last_out_of_order_sequence],
          ce.[last_out_of_order_frag],
          ce.[is_system],
          ce.[Priority]
        FROM
          [sys].[conversation_endpoints] ce
        """;

    public const int CONVERSATIONHANDLE_FIELD_ID = 0;
    public const int CONVERSATIONID_FIELD_ID = 1;
    public const int ISINITIATOR_FIELD_ID = 2;
    public const int SERVICECONTRACTID_FIELD_ID = 3;
    public const int CONVERSATIONGROUPID_FIELD_ID = 4;
    public const int SERVICEID_FIELD_ID = 5;
    public const int LIFETIME_FIELD_ID = 6;
    public const int STATE_FIELD_ID = 7;
    public const int STATEDESC_FIELD_ID = 8;
    public const int FARSERVICE_FIELD_ID = 9;
    public const int FARBROKERINSTANCE_FIELD_ID = 10;
    public const int PRINCIPALID_FIELD_ID = 11;
    public const int FARPRINCIPALID_FIELD_ID = 12;
    public const int OUTBOUNDSESSIONKEYIDENTIFIER_FIELD_ID = 13;
    public const int INBOUNDSESSIONKEYIDENTIFIER_FIELD_ID = 14;
    public const int SECURITYTIMESTAMP_FIELD_ID = 15;
    public const int DIALOGTIMER_FIELD_ID = 16;
    public const int SENDSEQUENCE_FIELD_ID = 17;
    public const int LASTSENDTRANID_FIELD_ID = 18;
    public const int ENDDIALOGSEQUENCE_FIELD_ID = 19;
    public const int RECEIVESEQUENCE_FIELD_ID = 20;
    public const int RECEIVESEQUENCEFRAG_FIELD_ID = 21;
    public const int SYSTEMSEQUENCE_FIELD_ID = 22;
    public const int FIRSTOUTOFORDERSEQUENCE_FIELD_ID = 23;
    public const int LASTOUTOFORDERSEQUENCE_FIELD_ID = 24;
    public const int LASTOUTOFORDERFRAG_FIELD_ID = 25;
    public const int ISSYSTEM_FIELD_ID = 26;
    public const int PRIORITY_FIELD_ID = 27;


    public ConversationEndpointsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ConversationEndpointsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ConversationEndpointsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid ConversationHandle
    {
        get
        {
            return base.GetGuid(CONVERSATIONHANDLE_FIELD_ID);
        }
    }

    public Guid ConversationId
    {
        get
        {
            return base.GetGuid(CONVERSATIONID_FIELD_ID);
        }
    }

    public bool IsInitiator
    {
        get
        {
            return base.GetBoolean(ISINITIATOR_FIELD_ID);
        }
    }

    public int ServiceContractId
    {
        get
        {
            return base.GetInt32(SERVICECONTRACTID_FIELD_ID);
        }
    }

    public Guid ConversationGroupId
    {
        get
        {
            return base.GetGuid(CONVERSATIONGROUPID_FIELD_ID);
        }
    }

    public int ServiceId
    {
        get
        {
            return base.GetInt32(SERVICEID_FIELD_ID);
        }
    }

    public DateTime Lifetime
    {
        get
        {
            return base.GetDateTime(LIFETIME_FIELD_ID);
        }
    }

    public string State
    {
        get
        {
            return base.GetString(STATE_FIELD_ID);
        }
    }

    public string? StateDesc
    {
        get
        {
            return base.GetNullableString(STATEDESC_FIELD_ID);
        }
    }

    public string FarService
    {
        get
        {
            return base.GetString(FARSERVICE_FIELD_ID);
        }
    }

    public string? FarBrokerInstance
    {
        get
        {
            return base.GetNullableString(FARBROKERINSTANCE_FIELD_ID);
        }
    }

    public int PrincipalId
    {
        get
        {
            return base.GetInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public int FarPrincipalId
    {
        get
        {
            return base.GetInt32(FARPRINCIPALID_FIELD_ID);
        }
    }

    public Guid OutboundSessionKeyIdentifier
    {
        get
        {
            return base.GetGuid(OUTBOUNDSESSIONKEYIDENTIFIER_FIELD_ID);
        }
    }

    public Guid InboundSessionKeyIdentifier
    {
        get
        {
            return base.GetGuid(INBOUNDSESSIONKEYIDENTIFIER_FIELD_ID);
        }
    }

    public DateTime SecurityTimestamp
    {
        get
        {
            return base.GetDateTime(SECURITYTIMESTAMP_FIELD_ID);
        }
    }

    public DateTime DialogTimer
    {
        get
        {
            return base.GetDateTime(DIALOGTIMER_FIELD_ID);
        }
    }

    public long SendSequence
    {
        get
        {
            return base.GetInt64(SENDSEQUENCE_FIELD_ID);
        }
    }

    public byte[] LastSendTranId
    {
        get
        {
            return base.GetBinary(LASTSENDTRANID_FIELD_ID);
        }
    }

    public long EndDialogSequence
    {
        get
        {
            return base.GetInt64(ENDDIALOGSEQUENCE_FIELD_ID);
        }
    }

    public long ReceiveSequence
    {
        get
        {
            return base.GetInt64(RECEIVESEQUENCE_FIELD_ID);
        }
    }

    public int ReceiveSequenceFrag
    {
        get
        {
            return base.GetInt32(RECEIVESEQUENCEFRAG_FIELD_ID);
        }
    }

    public long SystemSequence
    {
        get
        {
            return base.GetInt64(SYSTEMSEQUENCE_FIELD_ID);
        }
    }

    public long FirstOutOfOrderSequence
    {
        get
        {
            return base.GetInt64(FIRSTOUTOFORDERSEQUENCE_FIELD_ID);
        }
    }

    public long LastOutOfOrderSequence
    {
        get
        {
            return base.GetInt64(LASTOUTOFORDERSEQUENCE_FIELD_ID);
        }
    }

    public int LastOutOfOrderFrag
    {
        get
        {
            return base.GetInt32(LASTOUTOFORDERFRAG_FIELD_ID);
        }
    }

    public bool IsSystem
    {
        get
        {
            return base.GetBoolean(ISSYSTEM_FIELD_ID);
        }
    }

    public byte Priority
    {
        get
        {
            return base.GetByte(PRIORITY_FIELD_ID);
        }
    }


    public Types.ConversationEndpointsDataType ToDataObject()
    {
        return new Types.ConversationEndpointsDataType(ConversationHandle,
            ConversationId,
            IsInitiator,
            ServiceContractId,
            ConversationGroupId,
            ServiceId,
            Lifetime,
            State,
            StateDesc,
            FarService,
            FarBrokerInstance,
            PrincipalId,
            FarPrincipalId,
            OutboundSessionKeyIdentifier,
            InboundSessionKeyIdentifier,
            SecurityTimestamp,
            DialogTimer,
            SendSequence,
            LastSendTranId,
            EndDialogSequence,
            ReceiveSequence,
            ReceiveSequenceFrag,
            SystemSequence,
            FirstOutOfOrderSequence,
            LastOutOfOrderSequence,
            LastOutOfOrderFrag,
            IsSystem,
            Priority);
    }

    public List<Types.ConversationEndpointsDataType> ToList()
    {
        var list = new List<Types.ConversationEndpointsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class TransmissionQueueReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[transmission_queue]";
    public const string TableName = "transmission_queue";
    public const string ShortName = "tq";
    public const string Sql = """
        SELECT
          tq.[conversation_handle],
          tq.[to_service_name],
          tq.[to_broker_instance],
          tq.[from_service_name],
          tq.[service_contract_name],
          tq.[enqueue_time],
          tq.[message_sequence_number],
          tq.[message_type_name],
          tq.[is_conversation_error],
          tq.[is_end_of_dialog],
          tq.[message_body],
          tq.[transmission_status],
          tq.[Priority]
        FROM
          [sys].[transmission_queue] tq
        """;

    public const int CONVERSATIONHANDLE_FIELD_ID = 0;
    public const int TOSERVICENAME_FIELD_ID = 1;
    public const int TOBROKERINSTANCE_FIELD_ID = 2;
    public const int FROMSERVICENAME_FIELD_ID = 3;
    public const int SERVICECONTRACTNAME_FIELD_ID = 4;
    public const int ENQUEUETIME_FIELD_ID = 5;
    public const int MESSAGESEQUENCENUMBER_FIELD_ID = 6;
    public const int MESSAGETYPENAME_FIELD_ID = 7;
    public const int ISCONVERSATIONERROR_FIELD_ID = 8;
    public const int ISENDOFDIALOG_FIELD_ID = 9;
    public const int MESSAGEBODY_FIELD_ID = 10;
    public const int TRANSMISSIONSTATUS_FIELD_ID = 11;
    public const int PRIORITY_FIELD_ID = 12;


    public TransmissionQueueReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public TransmissionQueueReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public TransmissionQueueReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public string? ToServiceName
    {
        get
        {
            return base.GetNullableString(TOSERVICENAME_FIELD_ID);
        }
    }

    public string? ToBrokerInstance
    {
        get
        {
            return base.GetNullableString(TOBROKERINSTANCE_FIELD_ID);
        }
    }

    public string? FromServiceName
    {
        get
        {
            return base.GetNullableString(FROMSERVICENAME_FIELD_ID);
        }
    }

    public string? ServiceContractName
    {
        get
        {
            return base.GetNullableString(SERVICECONTRACTNAME_FIELD_ID);
        }
    }

    public DateTime EnqueueTime
    {
        get
        {
            return base.GetDateTime(ENQUEUETIME_FIELD_ID);
        }
    }

    public long MessageSequenceNumber
    {
        get
        {
            return base.GetInt64(MESSAGESEQUENCENUMBER_FIELD_ID);
        }
    }

    public string? MessageTypeName
    {
        get
        {
            return base.GetNullableString(MESSAGETYPENAME_FIELD_ID);
        }
    }

    public bool IsConversationError
    {
        get
        {
            return base.GetBoolean(ISCONVERSATIONERROR_FIELD_ID);
        }
    }

    public bool IsEndOfDialog
    {
        get
        {
            return base.GetBoolean(ISENDOFDIALOG_FIELD_ID);
        }
    }

    public byte[]? MessageBody
    {
        get
        {
            return base.GetNullableBinary(MESSAGEBODY_FIELD_ID);
        }
    }

    public string? TransmissionStatus
    {
        get
        {
            return base.GetNullableString(TRANSMISSIONSTATUS_FIELD_ID);
        }
    }

    public byte Priority
    {
        get
        {
            return base.GetByte(PRIORITY_FIELD_ID);
        }
    }


    public Types.TransmissionQueue ToDataObject()
    {
        return new Types.TransmissionQueue(ConversationHandle,
            ToServiceName,
            ToBrokerInstance,
            FromServiceName,
            ServiceContractName,
            EnqueueTime,
            MessageSequenceNumber,
            MessageTypeName,
            IsConversationError,
            IsEndOfDialog,
            MessageBody,
            TransmissionStatus,
            Priority);
    }

    public List<Types.TransmissionQueue> ToList()
    {
        var list = new List<Types.TransmissionQueue>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

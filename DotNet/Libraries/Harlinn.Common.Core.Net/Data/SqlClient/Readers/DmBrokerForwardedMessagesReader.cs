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

public class DmBrokerForwardedMessagesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_broker_forwarded_messages]";
    public const string TableName = "dm_broker_forwarded_messages";
    public const string ShortName = "dbfm";
    public const string Sql = """
        SELECT
          dbfm.[conversation_id],
          dbfm.[is_initiator],
          dbfm.[to_service_name],
          dbfm.[to_broker_instance],
          dbfm.[from_service_name],
          dbfm.[from_broker_instance],
          dbfm.[adjacent_broker_address],
          dbfm.[message_sequence_number],
          dbfm.[message_fragment_number],
          dbfm.[hops_remaining],
          dbfm.[time_to_live],
          dbfm.[time_consumed],
          dbfm.[message_id]
        FROM
          [sys].[dm_broker_forwarded_messages] dbfm
        """;

    public const int CONVERSATIONID_FIELD_ID = 0;
    public const int ISINITIATOR_FIELD_ID = 1;
    public const int TOSERVICENAME_FIELD_ID = 2;
    public const int TOBROKERINSTANCE_FIELD_ID = 3;
    public const int FROMSERVICENAME_FIELD_ID = 4;
    public const int FROMBROKERINSTANCE_FIELD_ID = 5;
    public const int ADJACENTBROKERADDRESS_FIELD_ID = 6;
    public const int MESSAGESEQUENCENUMBER_FIELD_ID = 7;
    public const int MESSAGEFRAGMENTNUMBER_FIELD_ID = 8;
    public const int HOPSREMAINING_FIELD_ID = 9;
    public const int TIMETOLIVE_FIELD_ID = 10;
    public const int TIMECONSUMED_FIELD_ID = 11;
    public const int MESSAGEID_FIELD_ID = 12;


    public DmBrokerForwardedMessagesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmBrokerForwardedMessagesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmBrokerForwardedMessagesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid? ConversationId
    {
        get
        {
            return base.GetNullableGuid(CONVERSATIONID_FIELD_ID);
        }
    }

    public bool? IsInitiator
    {
        get
        {
            return base.GetNullableBoolean(ISINITIATOR_FIELD_ID);
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

    public string? FromBrokerInstance
    {
        get
        {
            return base.GetNullableString(FROMBROKERINSTANCE_FIELD_ID);
        }
    }

    public string? AdjacentBrokerAddress
    {
        get
        {
            return base.GetNullableString(ADJACENTBROKERADDRESS_FIELD_ID);
        }
    }

    public long? MessageSequenceNumber
    {
        get
        {
            return base.GetNullableInt64(MESSAGESEQUENCENUMBER_FIELD_ID);
        }
    }

    public int? MessageFragmentNumber
    {
        get
        {
            return base.GetNullableInt32(MESSAGEFRAGMENTNUMBER_FIELD_ID);
        }
    }

    public byte? HopsRemaining
    {
        get
        {
            return base.GetNullableByte(HOPSREMAINING_FIELD_ID);
        }
    }

    public int? TimeToLive
    {
        get
        {
            return base.GetNullableInt32(TIMETOLIVE_FIELD_ID);
        }
    }

    public int? TimeConsumed
    {
        get
        {
            return base.GetNullableInt32(TIMECONSUMED_FIELD_ID);
        }
    }

    public Guid? MessageId
    {
        get
        {
            return base.GetNullableGuid(MESSAGEID_FIELD_ID);
        }
    }


    public Types.DmBrokerForwardedMessagesDataType ToDataObject()
    {
        return new Types.DmBrokerForwardedMessagesDataType(ConversationId,
            IsInitiator,
            ToServiceName,
            ToBrokerInstance,
            FromServiceName,
            FromBrokerInstance,
            AdjacentBrokerAddress,
            MessageSequenceNumber,
            MessageFragmentNumber,
            HopsRemaining,
            TimeToLive,
            TimeConsumed,
            MessageId);
    }

    public List<Types.DmBrokerForwardedMessagesDataType> ToList()
    {
        var list = new List<Types.DmBrokerForwardedMessagesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

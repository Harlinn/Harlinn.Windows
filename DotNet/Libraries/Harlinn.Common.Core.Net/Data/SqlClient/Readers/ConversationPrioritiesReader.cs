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

public class ConversationPrioritiesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[conversation_priorities]";
    public const string TableName = "conversation_priorities";
    public const string ShortName = "cp";
    public const string Sql = """
        SELECT
          cp.[priority_id],
          cp.[Name],
          cp.[service_contract_id],
          cp.[local_service_id],
          cp.[remote_service_name],
          cp.[Priority]
        FROM
          [sys].[conversation_priorities] cp
        """;

    public const int PRIORITYID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int SERVICECONTRACTID_FIELD_ID = 2;
    public const int LOCALSERVICEID_FIELD_ID = 3;
    public const int REMOTESERVICENAME_FIELD_ID = 4;
    public const int PRIORITY_FIELD_ID = 5;


    public ConversationPrioritiesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ConversationPrioritiesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ConversationPrioritiesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int PriorityId
    {
        get
        {
            return base.GetInt32(PRIORITYID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int? ServiceContractId
    {
        get
        {
            return base.GetNullableInt32(SERVICECONTRACTID_FIELD_ID);
        }
    }

    public int? LocalServiceId
    {
        get
        {
            return base.GetNullableInt32(LOCALSERVICEID_FIELD_ID);
        }
    }

    public string? RemoteServiceName
    {
        get
        {
            return base.GetNullableString(REMOTESERVICENAME_FIELD_ID);
        }
    }

    public byte Priority
    {
        get
        {
            return base.GetByte(PRIORITY_FIELD_ID);
        }
    }


    public Types.ConversationPrioritiesDataType ToDataObject()
    {
        return new Types.ConversationPrioritiesDataType(PriorityId,
            Name,
            ServiceContractId,
            LocalServiceId,
            RemoteServiceName,
            Priority);
    }

    public List<Types.ConversationPrioritiesDataType> ToList()
    {
        var list = new List<Types.ConversationPrioritiesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

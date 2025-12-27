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

public class ServiceContractMessageUsagesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[service_contract_message_usages]";
    public const string TableName = "service_contract_message_usages";
    public const string ShortName = "scmu";
    public const string Sql = """
        SELECT
          scmu.[service_contract_id],
          scmu.[message_type_id],
          scmu.[is_sent_by_initiator],
          scmu.[is_sent_by_target]
        FROM
          [sys].[service_contract_message_usages] scmu
        """;

    public const int SERVICECONTRACTID_FIELD_ID = 0;
    public const int MESSAGETYPEID_FIELD_ID = 1;
    public const int ISSENTBYINITIATOR_FIELD_ID = 2;
    public const int ISSENTBYTARGET_FIELD_ID = 3;


    public ServiceContractMessageUsagesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServiceContractMessageUsagesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServiceContractMessageUsagesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ServiceContractId
    {
        get
        {
            return base.GetInt32(SERVICECONTRACTID_FIELD_ID);
        }
    }

    public int MessageTypeId
    {
        get
        {
            return base.GetInt32(MESSAGETYPEID_FIELD_ID);
        }
    }

    public bool IsSentByInitiator
    {
        get
        {
            return base.GetBoolean(ISSENTBYINITIATOR_FIELD_ID);
        }
    }

    public bool IsSentByTarget
    {
        get
        {
            return base.GetBoolean(ISSENTBYTARGET_FIELD_ID);
        }
    }


    public Types.ServiceContractMessageUsagesDataType ToDataObject()
    {
        return new Types.ServiceContractMessageUsagesDataType(ServiceContractId,
            MessageTypeId,
            IsSentByInitiator,
            IsSentByTarget);
    }

    public List<Types.ServiceContractMessageUsagesDataType> ToList()
    {
        var list = new List<Types.ServiceContractMessageUsagesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

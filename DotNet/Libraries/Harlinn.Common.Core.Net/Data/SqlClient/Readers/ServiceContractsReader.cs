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

public class ServiceContractsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[service_contracts]";
    public const string TableName = "service_contracts";
    public const string ShortName = "sc1";
    public const string Sql = """
        SELECT
          sc1.[Name],
          sc1.[service_contract_id],
          sc1.[principal_id]
        FROM
          [sys].[service_contracts] sc1
        """;

    public const int NAME_FIELD_ID = 0;
    public const int SERVICECONTRACTID_FIELD_ID = 1;
    public const int PRINCIPALID_FIELD_ID = 2;


    public ServiceContractsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServiceContractsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServiceContractsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int ServiceContractId
    {
        get
        {
            return base.GetInt32(SERVICECONTRACTID_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }


    public Types.ServiceContractsDataType ToDataObject()
    {
        return new Types.ServiceContractsDataType(Name,
            ServiceContractId,
            PrincipalId);
    }

    public List<Types.ServiceContractsDataType> ToList()
    {
        var list = new List<Types.ServiceContractsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class RemoteServiceBindingsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[remote_service_bindings]";
    public const string TableName = "remote_service_bindings";
    public const string ShortName = "rsb";
    public const string Sql = """
        SELECT
          rsb.[Name],
          rsb.[remote_service_binding_id],
          rsb.[principal_id],
          rsb.[remote_service_name],
          rsb.[service_contract_id],
          rsb.[remote_principal_id],
          rsb.[is_anonymous_on]
        FROM
          [sys].[remote_service_bindings] rsb
        """;

    public const int NAME_FIELD_ID = 0;
    public const int REMOTESERVICEBINDINGID_FIELD_ID = 1;
    public const int PRINCIPALID_FIELD_ID = 2;
    public const int REMOTESERVICENAME_FIELD_ID = 3;
    public const int SERVICECONTRACTID_FIELD_ID = 4;
    public const int REMOTEPRINCIPALID_FIELD_ID = 5;
    public const int ISANONYMOUSON_FIELD_ID = 6;


    public RemoteServiceBindingsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public RemoteServiceBindingsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public RemoteServiceBindingsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int RemoteServiceBindingId
    {
        get
        {
            return base.GetInt32(REMOTESERVICEBINDINGID_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public string? RemoteServiceName
    {
        get
        {
            return base.GetNullableString(REMOTESERVICENAME_FIELD_ID);
        }
    }

    public int ServiceContractId
    {
        get
        {
            return base.GetInt32(SERVICECONTRACTID_FIELD_ID);
        }
    }

    public int? RemotePrincipalId
    {
        get
        {
            return base.GetNullableInt32(REMOTEPRINCIPALID_FIELD_ID);
        }
    }

    public bool IsAnonymousOn
    {
        get
        {
            return base.GetBoolean(ISANONYMOUSON_FIELD_ID);
        }
    }


    public Types.RemoteServiceBindingsDataType ToDataObject()
    {
        return new Types.RemoteServiceBindingsDataType(Name,
            RemoteServiceBindingId,
            PrincipalId,
            RemoteServiceName,
            ServiceContractId,
            RemotePrincipalId,
            IsAnonymousOn);
    }

    public List<Types.RemoteServiceBindingsDataType> ToList()
    {
        var list = new List<Types.RemoteServiceBindingsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

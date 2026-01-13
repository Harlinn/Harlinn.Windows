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

public class EndpointsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[endpoints]";
    public const string TableName = "endpoints";
    public const string ShortName = "e1";
    public const string Sql = """
        SELECT
          e1.[Name],
          e1.[endpoint_id],
          e1.[principal_id],
          e1.[Protocol],
          e1.[protocol_desc],
          e1.[Type],
          e1.[type_desc],
          e1.[State],
          e1.[state_desc],
          e1.[is_admin_endpoint]
        FROM
          [sys].[endpoints] e1
        """;

    public const int NAME_FIELD_ID = 0;
    public const int ENDPOINTID_FIELD_ID = 1;
    public const int PRINCIPALID_FIELD_ID = 2;
    public const int PROTOCOL_FIELD_ID = 3;
    public const int PROTOCOLDESC_FIELD_ID = 4;
    public const int TYPE_FIELD_ID = 5;
    public const int TYPEDESC_FIELD_ID = 6;
    public const int STATE_FIELD_ID = 7;
    public const int STATEDESC_FIELD_ID = 8;
    public const int ISADMINENDPOINT_FIELD_ID = 9;


    public EndpointsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public EndpointsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public EndpointsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int EndpointId
    {
        get
        {
            return base.GetInt32(ENDPOINTID_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public byte Protocol
    {
        get
        {
            return base.GetByte(PROTOCOL_FIELD_ID);
        }
    }

    public string? ProtocolDesc
    {
        get
        {
            return base.GetNullableString(PROTOCOLDESC_FIELD_ID);
        }
    }

    public byte Type
    {
        get
        {
            return base.GetByte(TYPE_FIELD_ID);
        }
    }

    public string? TypeDesc
    {
        get
        {
            return base.GetNullableString(TYPEDESC_FIELD_ID);
        }
    }

    public byte? State
    {
        get
        {
            return base.GetNullableByte(STATE_FIELD_ID);
        }
    }

    public string? StateDesc
    {
        get
        {
            return base.GetNullableString(STATEDESC_FIELD_ID);
        }
    }

    public bool IsAdminEndpoint
    {
        get
        {
            return base.GetBoolean(ISADMINENDPOINT_FIELD_ID);
        }
    }


    public Types.EndpointsDataType ToDataObject()
    {
        return new Types.EndpointsDataType(Name,
            EndpointId,
            PrincipalId,
            Protocol,
            ProtocolDesc,
            Type,
            TypeDesc,
            State,
            StateDesc,
            IsAdminEndpoint);
    }

    public List<Types.EndpointsDataType> ToList()
    {
        var list = new List<Types.EndpointsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

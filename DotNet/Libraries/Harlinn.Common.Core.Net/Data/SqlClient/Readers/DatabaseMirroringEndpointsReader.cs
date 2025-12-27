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

public class DatabaseMirroringEndpointsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[database_mirroring_endpoints]";
    public const string TableName = "database_mirroring_endpoints";
    public const string ShortName = "dme";
    public const string Sql = """
        SELECT
          dme.[Name],
          dme.[endpoint_id],
          dme.[principal_id],
          dme.[Protocol],
          dme.[protocol_desc],
          dme.[Type],
          dme.[type_desc],
          dme.[State],
          dme.[state_desc],
          dme.[is_admin_endpoint],
          dme.[Role],
          dme.[role_desc],
          dme.[is_encryption_enabled],
          dme.[connection_auth],
          dme.[connection_auth_desc],
          dme.[certificate_id],
          dme.[encryption_algorithm],
          dme.[encryption_algorithm_desc]
        FROM
          [sys].[database_mirroring_endpoints] dme
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
    public const int ROLE_FIELD_ID = 10;
    public const int ROLEDESC_FIELD_ID = 11;
    public const int ISENCRYPTIONENABLED_FIELD_ID = 12;
    public const int CONNECTIONAUTH_FIELD_ID = 13;
    public const int CONNECTIONAUTHDESC_FIELD_ID = 14;
    public const int CERTIFICATEID_FIELD_ID = 15;
    public const int ENCRYPTIONALGORITHM_FIELD_ID = 16;
    public const int ENCRYPTIONALGORITHMDESC_FIELD_ID = 17;


    public DatabaseMirroringEndpointsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DatabaseMirroringEndpointsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DatabaseMirroringEndpointsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public byte? Role
    {
        get
        {
            return base.GetNullableByte(ROLE_FIELD_ID);
        }
    }

    public string? RoleDesc
    {
        get
        {
            return base.GetNullableString(ROLEDESC_FIELD_ID);
        }
    }

    public bool IsEncryptionEnabled
    {
        get
        {
            return base.GetBoolean(ISENCRYPTIONENABLED_FIELD_ID);
        }
    }

    public byte ConnectionAuth
    {
        get
        {
            return base.GetByte(CONNECTIONAUTH_FIELD_ID);
        }
    }

    public string? ConnectionAuthDesc
    {
        get
        {
            return base.GetNullableString(CONNECTIONAUTHDESC_FIELD_ID);
        }
    }

    public int CertificateId
    {
        get
        {
            return base.GetInt32(CERTIFICATEID_FIELD_ID);
        }
    }

    public byte EncryptionAlgorithm
    {
        get
        {
            return base.GetByte(ENCRYPTIONALGORITHM_FIELD_ID);
        }
    }

    public string? EncryptionAlgorithmDesc
    {
        get
        {
            return base.GetNullableString(ENCRYPTIONALGORITHMDESC_FIELD_ID);
        }
    }


    public Types.DatabaseMirroringEndpointsDataType ToDataObject()
    {
        return new Types.DatabaseMirroringEndpointsDataType(Name,
            EndpointId,
            PrincipalId,
            Protocol,
            ProtocolDesc,
            Type,
            TypeDesc,
            State,
            StateDesc,
            IsAdminEndpoint,
            Role,
            RoleDesc,
            IsEncryptionEnabled,
            ConnectionAuth,
            ConnectionAuthDesc,
            CertificateId,
            EncryptionAlgorithm,
            EncryptionAlgorithmDesc);
    }

    public List<Types.DatabaseMirroringEndpointsDataType> ToList()
    {
        var list = new List<Types.DatabaseMirroringEndpointsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

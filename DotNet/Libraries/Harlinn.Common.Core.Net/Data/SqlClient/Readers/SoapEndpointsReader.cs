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

public class SoapEndpointsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[soap_endpoints]";
    public const string TableName = "soap_endpoints";
    public const string ShortName = "se0";
    public const string Sql = """
        SELECT
          se0.[Name],
          se0.[endpoint_id],
          se0.[principal_id],
          se0.[Protocol],
          se0.[protocol_desc],
          se0.[Type],
          se0.[type_desc],
          se0.[State],
          se0.[state_desc],
          se0.[is_admin_endpoint],
          se0.[is_sql_language_enabled],
          se0.[wsdl_generator_procedure],
          se0.[default_database],
          se0.[default_namespace],
          se0.[default_result_schema],
          se0.[default_result_schema_desc],
          se0.[is_xml_charset_enforced],
          se0.[is_session_enabled],
          se0.[session_timeout],
          se0.[login_type],
          se0.[header_limit]
        FROM
          [sys].[soap_endpoints] se0
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
    public const int ISSQLLANGUAGEENABLED_FIELD_ID = 10;
    public const int WSDLGENERATORPROCEDURE_FIELD_ID = 11;
    public const int DEFAULTDATABASE_FIELD_ID = 12;
    public const int DEFAULTNAMESPACE_FIELD_ID = 13;
    public const int DEFAULTRESULTSCHEMA_FIELD_ID = 14;
    public const int DEFAULTRESULTSCHEMADESC_FIELD_ID = 15;
    public const int ISXMLCHARSETENFORCED_FIELD_ID = 16;
    public const int ISSESSIONENABLED_FIELD_ID = 17;
    public const int SESSIONTIMEOUT_FIELD_ID = 18;
    public const int LOGINTYPE_FIELD_ID = 19;
    public const int HEADERLIMIT_FIELD_ID = 20;


    public SoapEndpointsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SoapEndpointsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SoapEndpointsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public bool IsSqlLanguageEnabled
    {
        get
        {
            return base.GetBoolean(ISSQLLANGUAGEENABLED_FIELD_ID);
        }
    }

    public string? WsdlGeneratorProcedure
    {
        get
        {
            return base.GetNullableString(WSDLGENERATORPROCEDURE_FIELD_ID);
        }
    }

    public string? DefaultDatabase
    {
        get
        {
            return base.GetNullableString(DEFAULTDATABASE_FIELD_ID);
        }
    }

    public string? DefaultNamespace
    {
        get
        {
            return base.GetNullableString(DEFAULTNAMESPACE_FIELD_ID);
        }
    }

    public byte? DefaultResultSchema
    {
        get
        {
            return base.GetNullableByte(DEFAULTRESULTSCHEMA_FIELD_ID);
        }
    }

    public string? DefaultResultSchemaDesc
    {
        get
        {
            return base.GetNullableString(DEFAULTRESULTSCHEMADESC_FIELD_ID);
        }
    }

    public bool IsXmlCharsetEnforced
    {
        get
        {
            return base.GetBoolean(ISXMLCHARSETENFORCED_FIELD_ID);
        }
    }

    public bool IsSessionEnabled
    {
        get
        {
            return base.GetBoolean(ISSESSIONENABLED_FIELD_ID);
        }
    }

    public int SessionTimeout
    {
        get
        {
            return base.GetInt32(SESSIONTIMEOUT_FIELD_ID);
        }
    }

    public string? LoginType
    {
        get
        {
            return base.GetNullableString(LOGINTYPE_FIELD_ID);
        }
    }

    public int HeaderLimit
    {
        get
        {
            return base.GetInt32(HEADERLIMIT_FIELD_ID);
        }
    }


    public Types.SoapEndpointsDataType ToDataObject()
    {
        return new Types.SoapEndpointsDataType(Name,
            EndpointId,
            PrincipalId,
            Protocol,
            ProtocolDesc,
            Type,
            TypeDesc,
            State,
            StateDesc,
            IsAdminEndpoint,
            IsSqlLanguageEnabled,
            WsdlGeneratorProcedure,
            DefaultDatabase,
            DefaultNamespace,
            DefaultResultSchema,
            DefaultResultSchemaDesc,
            IsXmlCharsetEnforced,
            IsSessionEnabled,
            SessionTimeout,
            LoginType,
            HeaderLimit);
    }

    public List<Types.SoapEndpointsDataType> ToList()
    {
        var list = new List<Types.SoapEndpointsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class EndpointWebmethodsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[endpoint_webmethods]";
    public const string TableName = "endpoint_webmethods";
    public const string ShortName = "ew";
    public const string Sql = """
        SELECT
          ew.[endpoint_id],
          ew.[Namespace],
          ew.[method_alias],
          ew.[object_name],
          ew.[result_schema],
          ew.[result_schema_desc],
          ew.[result_format],
          ew.[result_format_desc]
        FROM
          [sys].[endpoint_webmethods] ew
        """;

    public const int ENDPOINTID_FIELD_ID = 0;
    public const int NAMESPACE_FIELD_ID = 1;
    public const int METHODALIAS_FIELD_ID = 2;
    public const int OBJECTNAME_FIELD_ID = 3;
    public const int RESULTSCHEMA_FIELD_ID = 4;
    public const int RESULTSCHEMADESC_FIELD_ID = 5;
    public const int RESULTFORMAT_FIELD_ID = 6;
    public const int RESULTFORMATDESC_FIELD_ID = 7;


    public EndpointWebmethodsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public EndpointWebmethodsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public EndpointWebmethodsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int EndpointId
    {
        get
        {
            return base.GetInt32(ENDPOINTID_FIELD_ID);
        }
    }

    public string? Namespace
    {
        get
        {
            return base.GetNullableString(NAMESPACE_FIELD_ID);
        }
    }

    public string MethodAlias
    {
        get
        {
            return base.GetString(METHODALIAS_FIELD_ID);
        }
    }

    public string? ObjectName
    {
        get
        {
            return base.GetNullableString(OBJECTNAME_FIELD_ID);
        }
    }

    public byte? ResultSchema
    {
        get
        {
            return base.GetNullableByte(RESULTSCHEMA_FIELD_ID);
        }
    }

    public string? ResultSchemaDesc
    {
        get
        {
            return base.GetNullableString(RESULTSCHEMADESC_FIELD_ID);
        }
    }

    public byte? ResultFormat
    {
        get
        {
            return base.GetNullableByte(RESULTFORMAT_FIELD_ID);
        }
    }

    public string? ResultFormatDesc
    {
        get
        {
            return base.GetNullableString(RESULTFORMATDESC_FIELD_ID);
        }
    }


    public Types.EndpointWebmethodsDataType ToDataObject()
    {
        return new Types.EndpointWebmethodsDataType(EndpointId,
            Namespace,
            MethodAlias,
            ObjectName,
            ResultSchema,
            ResultSchemaDesc,
            ResultFormat,
            ResultFormatDesc);
    }

    public List<Types.EndpointWebmethodsDataType> ToList()
    {
        var list = new List<Types.EndpointWebmethodsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

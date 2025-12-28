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

public class XmlSchemaFacetsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[xml_schema_facets]";
    public const string TableName = "xml_schema_facets";
    public const string ShortName = "xsf";
    public const string Sql = """
        SELECT
          xsf.[xml_component_id],
          xsf.[facet_id],
          xsf.[Kind],
          xsf.[kind_desc],
          xsf.[is_fixed],
          xsf.[Value]
        FROM
          [sys].[xml_schema_facets] xsf
        """;

    public const int XMLCOMPONENTID_FIELD_ID = 0;
    public const int FACETID_FIELD_ID = 1;
    public const int KIND_FIELD_ID = 2;
    public const int KINDDESC_FIELD_ID = 3;
    public const int ISFIXED_FIELD_ID = 4;
    public const int VALUE_FIELD_ID = 5;


    public XmlSchemaFacetsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaFacetsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaFacetsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int XmlComponentId
    {
        get
        {
            return base.GetInt32(XMLCOMPONENTID_FIELD_ID);
        }
    }

    public int FacetId
    {
        get
        {
            return base.GetInt32(FACETID_FIELD_ID);
        }
    }

    public string Kind
    {
        get
        {
            return base.GetString(KIND_FIELD_ID);
        }
    }

    public string? KindDesc
    {
        get
        {
            return base.GetNullableString(KINDDESC_FIELD_ID);
        }
    }

    public bool IsFixed
    {
        get
        {
            return base.GetBoolean(ISFIXED_FIELD_ID);
        }
    }

    public string? Value
    {
        get
        {
            return base.GetNullableString(VALUE_FIELD_ID);
        }
    }


    public Types.XmlSchemaFacet ToDataObject()
    {
        return new Types.XmlSchemaFacet(XmlComponentId,
            FacetId,
            Kind,
            KindDesc,
            IsFixed,
            Value);
    }

    public List<Types.XmlSchemaFacet> ToList()
    {
        var list = new List<Types.XmlSchemaFacet>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

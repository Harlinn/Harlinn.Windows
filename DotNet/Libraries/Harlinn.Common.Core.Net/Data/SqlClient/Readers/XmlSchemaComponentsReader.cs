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

public class XmlSchemaComponentsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[xml_schema_components]";
    public const string TableName = "xml_schema_components";
    public const string ShortName = "xsc0";
    public const string Sql = """
        SELECT
          xsc0.[xml_component_id],
          xsc0.[xml_collection_id],
          xsc0.[xml_namespace_id],
          xsc0.[is_qualified],
          xsc0.[Name],
          xsc0.[symbol_space],
          xsc0.[symbol_space_desc],
          xsc0.[Kind],
          xsc0.[kind_desc],
          xsc0.[Derivation],
          xsc0.[derivation_desc],
          xsc0.[base_xml_component_id],
          xsc0.[scoping_xml_component_id]
        FROM
          [sys].[xml_schema_components] xsc0
        """;

    public const int XMLCOMPONENTID_FIELD_ID = 0;
    public const int XMLCOLLECTIONID_FIELD_ID = 1;
    public const int XMLNAMESPACEID_FIELD_ID = 2;
    public const int ISQUALIFIED_FIELD_ID = 3;
    public const int NAME_FIELD_ID = 4;
    public const int SYMBOLSPACE_FIELD_ID = 5;
    public const int SYMBOLSPACEDESC_FIELD_ID = 6;
    public const int KIND_FIELD_ID = 7;
    public const int KINDDESC_FIELD_ID = 8;
    public const int DERIVATION_FIELD_ID = 9;
    public const int DERIVATIONDESC_FIELD_ID = 10;
    public const int BASEXMLCOMPONENTID_FIELD_ID = 11;
    public const int SCOPINGXMLCOMPONENTID_FIELD_ID = 12;


    public XmlSchemaComponentsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaComponentsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaComponentsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int XmlCollectionId
    {
        get
        {
            return base.GetInt32(XMLCOLLECTIONID_FIELD_ID);
        }
    }

    public int XmlNamespaceId
    {
        get
        {
            return base.GetInt32(XMLNAMESPACEID_FIELD_ID);
        }
    }

    public bool IsQualified
    {
        get
        {
            return base.GetBoolean(ISQUALIFIED_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public string SymbolSpace
    {
        get
        {
            return base.GetString(SYMBOLSPACE_FIELD_ID);
        }
    }

    public string? SymbolSpaceDesc
    {
        get
        {
            return base.GetNullableString(SYMBOLSPACEDESC_FIELD_ID);
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

    public string Derivation
    {
        get
        {
            return base.GetString(DERIVATION_FIELD_ID);
        }
    }

    public string? DerivationDesc
    {
        get
        {
            return base.GetNullableString(DERIVATIONDESC_FIELD_ID);
        }
    }

    public int? BaseXmlComponentId
    {
        get
        {
            return base.GetNullableInt32(BASEXMLCOMPONENTID_FIELD_ID);
        }
    }

    public int? ScopingXmlComponentId
    {
        get
        {
            return base.GetNullableInt32(SCOPINGXMLCOMPONENTID_FIELD_ID);
        }
    }


    public Types.XmlSchemaComponentsDataType ToDataObject()
    {
        return new Types.XmlSchemaComponentsDataType(XmlComponentId,
            XmlCollectionId,
            XmlNamespaceId,
            IsQualified,
            Name,
            SymbolSpace,
            SymbolSpaceDesc,
            Kind,
            KindDesc,
            Derivation,
            DerivationDesc,
            BaseXmlComponentId,
            ScopingXmlComponentId);
    }

    public List<Types.XmlSchemaComponentsDataType> ToList()
    {
        var list = new List<Types.XmlSchemaComponentsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

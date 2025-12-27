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

public class XmlSchemaAttributesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[xml_schema_attributes]";
    public const string TableName = "xml_schema_attributes";
    public const string ShortName = "xsa";
    public const string Sql = """
        SELECT
          xsa.[xml_component_id],
          xsa.[xml_collection_id],
          xsa.[xml_namespace_id],
          xsa.[is_qualified],
          xsa.[Name],
          xsa.[symbol_space],
          xsa.[symbol_space_desc],
          xsa.[Kind],
          xsa.[kind_desc],
          xsa.[Derivation],
          xsa.[derivation_desc],
          xsa.[base_xml_component_id],
          xsa.[scoping_xml_component_id],
          xsa.[is_default_fixed],
          xsa.[must_be_qualified],
          xsa.[default_value]
        FROM
          [sys].[xml_schema_attributes] xsa
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
    public const int ISDEFAULTFIXED_FIELD_ID = 13;
    public const int MUSTBEQUALIFIED_FIELD_ID = 14;
    public const int DEFAULTVALUE_FIELD_ID = 15;


    public XmlSchemaAttributesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaAttributesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaAttributesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public bool IsDefaultFixed
    {
        get
        {
            return base.GetBoolean(ISDEFAULTFIXED_FIELD_ID);
        }
    }

    public bool MustBeQualified
    {
        get
        {
            return base.GetBoolean(MUSTBEQUALIFIED_FIELD_ID);
        }
    }

    public string? DefaultValue
    {
        get
        {
            return base.GetNullableString(DEFAULTVALUE_FIELD_ID);
        }
    }


    public Types.XmlSchemaAttributesDataType ToDataObject()
    {
        return new Types.XmlSchemaAttributesDataType(XmlComponentId,
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
            ScopingXmlComponentId,
            IsDefaultFixed,
            MustBeQualified,
            DefaultValue);
    }

    public List<Types.XmlSchemaAttributesDataType> ToList()
    {
        var list = new List<Types.XmlSchemaAttributesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

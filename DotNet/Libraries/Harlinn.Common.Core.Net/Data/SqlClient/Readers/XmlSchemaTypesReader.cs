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

public class XmlSchemaTypesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[xml_schema_types]";
    public const string TableName = "xml_schema_types";
    public const string ShortName = "xst";
    public const string Sql = """
        SELECT
          xst.[xml_component_id],
          xst.[xml_collection_id],
          xst.[xml_namespace_id],
          xst.[is_qualified],
          xst.[Name],
          xst.[symbol_space],
          xst.[symbol_space_desc],
          xst.[Kind],
          xst.[kind_desc],
          xst.[Derivation],
          xst.[derivation_desc],
          xst.[base_xml_component_id],
          xst.[scoping_xml_component_id],
          xst.[is_abstract],
          xst.[allows_mixed_content],
          xst.[is_extension_blocked],
          xst.[is_restriction_blocked],
          xst.[is_final_extension],
          xst.[is_final_restriction],
          xst.[is_final_list_member],
          xst.[is_final_union_member]
        FROM
          [sys].[xml_schema_types] xst
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
    public const int ISABSTRACT_FIELD_ID = 13;
    public const int ALLOWSMIXEDCONTENT_FIELD_ID = 14;
    public const int ISEXTENSIONBLOCKED_FIELD_ID = 15;
    public const int ISRESTRICTIONBLOCKED_FIELD_ID = 16;
    public const int ISFINALEXTENSION_FIELD_ID = 17;
    public const int ISFINALRESTRICTION_FIELD_ID = 18;
    public const int ISFINALLISTMEMBER_FIELD_ID = 19;
    public const int ISFINALUNIONMEMBER_FIELD_ID = 20;


    public XmlSchemaTypesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaTypesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaTypesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public bool IsAbstract
    {
        get
        {
            return base.GetBoolean(ISABSTRACT_FIELD_ID);
        }
    }

    public bool AllowsMixedContent
    {
        get
        {
            return base.GetBoolean(ALLOWSMIXEDCONTENT_FIELD_ID);
        }
    }

    public bool IsExtensionBlocked
    {
        get
        {
            return base.GetBoolean(ISEXTENSIONBLOCKED_FIELD_ID);
        }
    }

    public bool IsRestrictionBlocked
    {
        get
        {
            return base.GetBoolean(ISRESTRICTIONBLOCKED_FIELD_ID);
        }
    }

    public bool IsFinalExtension
    {
        get
        {
            return base.GetBoolean(ISFINALEXTENSION_FIELD_ID);
        }
    }

    public bool IsFinalRestriction
    {
        get
        {
            return base.GetBoolean(ISFINALRESTRICTION_FIELD_ID);
        }
    }

    public bool IsFinalListMember
    {
        get
        {
            return base.GetBoolean(ISFINALLISTMEMBER_FIELD_ID);
        }
    }

    public bool IsFinalUnionMember
    {
        get
        {
            return base.GetBoolean(ISFINALUNIONMEMBER_FIELD_ID);
        }
    }


    public Types.XmlSchemaTypesDataType ToDataObject()
    {
        return new Types.XmlSchemaTypesDataType(XmlComponentId,
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
            IsAbstract,
            AllowsMixedContent,
            IsExtensionBlocked,
            IsRestrictionBlocked,
            IsFinalExtension,
            IsFinalRestriction,
            IsFinalListMember,
            IsFinalUnionMember);
    }

    public List<Types.XmlSchemaTypesDataType> ToList()
    {
        var list = new List<Types.XmlSchemaTypesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

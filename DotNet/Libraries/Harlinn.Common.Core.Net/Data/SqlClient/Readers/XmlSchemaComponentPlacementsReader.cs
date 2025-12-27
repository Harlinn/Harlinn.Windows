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

public class XmlSchemaComponentPlacementsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[xml_schema_component_placements]";
    public const string TableName = "xml_schema_component_placements";
    public const string ShortName = "xscp";
    public const string Sql = """
        SELECT
          xscp.[xml_component_id],
          xscp.[placement_id],
          xscp.[placed_xml_component_id],
          xscp.[is_default_fixed],
          xscp.[min_occurences],
          xscp.[max_occurences],
          xscp.[default_value]
        FROM
          [sys].[xml_schema_component_placements] xscp
        """;

    public const int XMLCOMPONENTID_FIELD_ID = 0;
    public const int PLACEMENTID_FIELD_ID = 1;
    public const int PLACEDXMLCOMPONENTID_FIELD_ID = 2;
    public const int ISDEFAULTFIXED_FIELD_ID = 3;
    public const int MINOCCURENCES_FIELD_ID = 4;
    public const int MAXOCCURENCES_FIELD_ID = 5;
    public const int DEFAULTVALUE_FIELD_ID = 6;


    public XmlSchemaComponentPlacementsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaComponentPlacementsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public XmlSchemaComponentPlacementsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int PlacementId
    {
        get
        {
            return base.GetInt32(PLACEMENTID_FIELD_ID);
        }
    }

    public int PlacedXmlComponentId
    {
        get
        {
            return base.GetInt32(PLACEDXMLCOMPONENTID_FIELD_ID);
        }
    }

    public bool IsDefaultFixed
    {
        get
        {
            return base.GetBoolean(ISDEFAULTFIXED_FIELD_ID);
        }
    }

    public int MinOccurences
    {
        get
        {
            return base.GetInt32(MINOCCURENCES_FIELD_ID);
        }
    }

    public int MaxOccurences
    {
        get
        {
            return base.GetInt32(MAXOCCURENCES_FIELD_ID);
        }
    }

    public string? DefaultValue
    {
        get
        {
            return base.GetNullableString(DEFAULTVALUE_FIELD_ID);
        }
    }


    public Types.XmlSchemaComponentPlacementsDataType ToDataObject()
    {
        return new Types.XmlSchemaComponentPlacementsDataType(XmlComponentId,
            PlacementId,
            PlacedXmlComponentId,
            IsDefaultFixed,
            MinOccurences,
            MaxOccurences,
            DefaultValue);
    }

    public List<Types.XmlSchemaComponentPlacementsDataType> ToList()
    {
        var list = new List<Types.XmlSchemaComponentPlacementsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class SelectiveXmlIndexPathsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[selective_xml_index_paths]";
    public const string TableName = "selective_xml_index_paths";
    public const string ShortName = "sxip";
    public const string Sql = """
        SELECT
          sxip.[object_id],
          sxip.[index_id],
          sxip.[path_id],
          sxip.[Path],
          sxip.[Name],
          sxip.[path_type],
          sxip.[path_type_desc],
          sxip.[xml_component_id],
          sxip.[xquery_type_description],
          sxip.[is_xquery_type_inferred],
          sxip.[xquery_max_length],
          sxip.[is_xquery_max_length_inferred],
          sxip.[is_node],
          sxip.[system_type_id],
          sxip.[user_type_id],
          sxip.[max_length],
          sxip.[Precision],
          sxip.[Scale],
          sxip.[collation_name],
          sxip.[is_singleton]
        FROM
          [sys].[selective_xml_index_paths] sxip
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int INDEXID_FIELD_ID = 1;
    public const int PATHID_FIELD_ID = 2;
    public const int PATH_FIELD_ID = 3;
    public const int NAME_FIELD_ID = 4;
    public const int PATHTYPE_FIELD_ID = 5;
    public const int PATHTYPEDESC_FIELD_ID = 6;
    public const int XMLCOMPONENTID_FIELD_ID = 7;
    public const int XQUERYTYPEDESCRIPTION_FIELD_ID = 8;
    public const int ISXQUERYTYPEINFERRED_FIELD_ID = 9;
    public const int XQUERYMAXLENGTH_FIELD_ID = 10;
    public const int ISXQUERYMAXLENGTHINFERRED_FIELD_ID = 11;
    public const int ISNODE_FIELD_ID = 12;
    public const int SYSTEMTYPEID_FIELD_ID = 13;
    public const int USERTYPEID_FIELD_ID = 14;
    public const int MAXLENGTH_FIELD_ID = 15;
    public const int PRECISION_FIELD_ID = 16;
    public const int SCALE_FIELD_ID = 17;
    public const int COLLATIONNAME_FIELD_ID = 18;
    public const int ISSINGLETON_FIELD_ID = 19;


    public SelectiveXmlIndexPathsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SelectiveXmlIndexPathsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SelectiveXmlIndexPathsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int IndexId
    {
        get
        {
            return base.GetInt32(INDEXID_FIELD_ID);
        }
    }

    public int? PathId
    {
        get
        {
            return base.GetNullableInt32(PATHID_FIELD_ID);
        }
    }

    public string? Path
    {
        get
        {
            return base.GetNullableString(PATH_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public byte? PathType
    {
        get
        {
            return base.GetNullableByte(PATHTYPE_FIELD_ID);
        }
    }

    public string? PathTypeDesc
    {
        get
        {
            return base.GetNullableString(PATHTYPEDESC_FIELD_ID);
        }
    }

    public int? XmlComponentId
    {
        get
        {
            return base.GetNullableInt32(XMLCOMPONENTID_FIELD_ID);
        }
    }

    public string? XqueryTypeDescription
    {
        get
        {
            return base.GetNullableString(XQUERYTYPEDESCRIPTION_FIELD_ID);
        }
    }

    public bool? IsXqueryTypeInferred
    {
        get
        {
            return base.GetNullableBoolean(ISXQUERYTYPEINFERRED_FIELD_ID);
        }
    }

    public int? XqueryMaxLength
    {
        get
        {
            return base.GetNullableInt32(XQUERYMAXLENGTH_FIELD_ID);
        }
    }

    public bool? IsXqueryMaxLengthInferred
    {
        get
        {
            return base.GetNullableBoolean(ISXQUERYMAXLENGTHINFERRED_FIELD_ID);
        }
    }

    public bool? IsNode
    {
        get
        {
            return base.GetNullableBoolean(ISNODE_FIELD_ID);
        }
    }

    public byte? SystemTypeId
    {
        get
        {
            return base.GetNullableByte(SYSTEMTYPEID_FIELD_ID);
        }
    }

    public byte? UserTypeId
    {
        get
        {
            return base.GetNullableByte(USERTYPEID_FIELD_ID);
        }
    }

    public short? MaxLength
    {
        get
        {
            return base.GetNullableInt16(MAXLENGTH_FIELD_ID);
        }
    }

    public byte? Precision
    {
        get
        {
            return base.GetNullableByte(PRECISION_FIELD_ID);
        }
    }

    public byte? Scale
    {
        get
        {
            return base.GetNullableByte(SCALE_FIELD_ID);
        }
    }

    public string? CollationName
    {
        get
        {
            return base.GetNullableString(COLLATIONNAME_FIELD_ID);
        }
    }

    public bool? IsSingleton
    {
        get
        {
            return base.GetNullableBoolean(ISSINGLETON_FIELD_ID);
        }
    }


    public Types.SelectiveXmlIndexPathsDataType ToDataObject()
    {
        return new Types.SelectiveXmlIndexPathsDataType(ObjectId,
            IndexId,
            PathId,
            Path,
            Name,
            PathType,
            PathTypeDesc,
            XmlComponentId,
            XqueryTypeDescription,
            IsXqueryTypeInferred,
            XqueryMaxLength,
            IsXqueryMaxLengthInferred,
            IsNode,
            SystemTypeId,
            UserTypeId,
            MaxLength,
            Precision,
            Scale,
            CollationName,
            IsSingleton);
    }

    public List<Types.SelectiveXmlIndexPathsDataType> ToList()
    {
        var list = new List<Types.SelectiveXmlIndexPathsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

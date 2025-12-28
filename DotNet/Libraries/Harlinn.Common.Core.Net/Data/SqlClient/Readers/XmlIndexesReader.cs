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

public class XmlIndexesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[xml_indexes]";
    public const string TableName = "xml_indexes";
    public const string ShortName = "xi";
    public const string Sql = """
        SELECT
          xi.[object_id],
          xi.[Name],
          xi.[index_id],
          xi.[Type],
          xi.[type_desc],
          xi.[is_unique],
          xi.[data_space_id],
          xi.[ignore_dup_key],
          xi.[is_primary_key],
          xi.[is_unique_constraint],
          xi.[fill_factor],
          xi.[is_padded],
          xi.[is_disabled],
          xi.[is_hypothetical],
          xi.[is_ignored_in_optimization],
          xi.[allow_row_locks],
          xi.[allow_page_locks],
          xi.[using_xml_index_id],
          xi.[secondary_type],
          xi.[secondary_type_desc],
          xi.[has_filter],
          xi.[filter_definition],
          xi.[xml_index_type],
          xi.[xml_index_type_description],
          xi.[path_id],
          xi.[auto_created]
        FROM
          [sys].[xml_indexes] xi
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int INDEXID_FIELD_ID = 2;
    public const int TYPE_FIELD_ID = 3;
    public const int TYPEDESC_FIELD_ID = 4;
    public const int ISUNIQUE_FIELD_ID = 5;
    public const int DATASPACEID_FIELD_ID = 6;
    public const int IGNOREDUPKEY_FIELD_ID = 7;
    public const int ISPRIMARYKEY_FIELD_ID = 8;
    public const int ISUNIQUECONSTRAINT_FIELD_ID = 9;
    public const int FILLFACTOR_FIELD_ID = 10;
    public const int ISPADDED_FIELD_ID = 11;
    public const int ISDISABLED_FIELD_ID = 12;
    public const int ISHYPOTHETICAL_FIELD_ID = 13;
    public const int ISIGNOREDINOPTIMIZATION_FIELD_ID = 14;
    public const int ALLOWROWLOCKS_FIELD_ID = 15;
    public const int ALLOWPAGELOCKS_FIELD_ID = 16;
    public const int USINGXMLINDEXID_FIELD_ID = 17;
    public const int SECONDARYTYPE_FIELD_ID = 18;
    public const int SECONDARYTYPEDESC_FIELD_ID = 19;
    public const int HASFILTER_FIELD_ID = 20;
    public const int FILTERDEFINITION_FIELD_ID = 21;
    public const int XMLINDEXTYPE_FIELD_ID = 22;
    public const int XMLINDEXTYPEDESCRIPTION_FIELD_ID = 23;
    public const int PATHID_FIELD_ID = 24;
    public const int AUTOCREATED_FIELD_ID = 25;


    public XmlIndexesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public XmlIndexesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public XmlIndexesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public int IndexId
    {
        get
        {
            return base.GetInt32(INDEXID_FIELD_ID);
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

    public bool? IsUnique
    {
        get
        {
            return base.GetNullableBoolean(ISUNIQUE_FIELD_ID);
        }
    }

    public int DataSpaceId
    {
        get
        {
            return base.GetInt32(DATASPACEID_FIELD_ID);
        }
    }

    public bool? IgnoreDupKey
    {
        get
        {
            return base.GetNullableBoolean(IGNOREDUPKEY_FIELD_ID);
        }
    }

    public bool? IsPrimaryKey
    {
        get
        {
            return base.GetNullableBoolean(ISPRIMARYKEY_FIELD_ID);
        }
    }

    public bool? IsUniqueConstraint
    {
        get
        {
            return base.GetNullableBoolean(ISUNIQUECONSTRAINT_FIELD_ID);
        }
    }

    public byte FillFactor
    {
        get
        {
            return base.GetByte(FILLFACTOR_FIELD_ID);
        }
    }

    public bool? IsPadded
    {
        get
        {
            return base.GetNullableBoolean(ISPADDED_FIELD_ID);
        }
    }

    public bool? IsDisabled
    {
        get
        {
            return base.GetNullableBoolean(ISDISABLED_FIELD_ID);
        }
    }

    public bool? IsHypothetical
    {
        get
        {
            return base.GetNullableBoolean(ISHYPOTHETICAL_FIELD_ID);
        }
    }

    public bool? IsIgnoredInOptimization
    {
        get
        {
            return base.GetNullableBoolean(ISIGNOREDINOPTIMIZATION_FIELD_ID);
        }
    }

    public bool? AllowRowLocks
    {
        get
        {
            return base.GetNullableBoolean(ALLOWROWLOCKS_FIELD_ID);
        }
    }

    public bool? AllowPageLocks
    {
        get
        {
            return base.GetNullableBoolean(ALLOWPAGELOCKS_FIELD_ID);
        }
    }

    public int? UsingXmlIndexId
    {
        get
        {
            return base.GetNullableInt32(USINGXMLINDEXID_FIELD_ID);
        }
    }

    public string? SecondaryType
    {
        get
        {
            return base.GetNullableString(SECONDARYTYPE_FIELD_ID);
        }
    }

    public string? SecondaryTypeDesc
    {
        get
        {
            return base.GetNullableString(SECONDARYTYPEDESC_FIELD_ID);
        }
    }

    public bool HasFilter
    {
        get
        {
            return base.GetBoolean(HASFILTER_FIELD_ID);
        }
    }

    public string? FilterDefinition
    {
        get
        {
            return base.GetNullableString(FILTERDEFINITION_FIELD_ID);
        }
    }

    public byte? XmlIndexType
    {
        get
        {
            return base.GetNullableByte(XMLINDEXTYPE_FIELD_ID);
        }
    }

    public string? XmlIndexTypeDescription
    {
        get
        {
            return base.GetNullableString(XMLINDEXTYPEDESCRIPTION_FIELD_ID);
        }
    }

    public int? PathId
    {
        get
        {
            return base.GetNullableInt32(PATHID_FIELD_ID);
        }
    }

    public bool? AutoCreated
    {
        get
        {
            return base.GetNullableBoolean(AUTOCREATED_FIELD_ID);
        }
    }


    public Types.XmlIndex ToDataObject()
    {
        return new Types.XmlIndex(ObjectId,
            Name,
            IndexId,
            Type,
            TypeDesc,
            IsUnique,
            DataSpaceId,
            IgnoreDupKey,
            IsPrimaryKey,
            IsUniqueConstraint,
            FillFactor,
            IsPadded,
            IsDisabled,
            IsHypothetical,
            IsIgnoredInOptimization,
            AllowRowLocks,
            AllowPageLocks,
            UsingXmlIndexId,
            SecondaryType,
            SecondaryTypeDesc,
            HasFilter,
            FilterDefinition,
            XmlIndexType,
            XmlIndexTypeDescription,
            PathId,
            AutoCreated);
    }

    public List<Types.XmlIndex> ToList()
    {
        var list = new List<Types.XmlIndex>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class SynonymsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[synonyms]";
    public const string TableName = "synonyms";
    public const string ShortName = "s3";
    public const string Sql = """
        SELECT
          s3.[Name],
          s3.[object_id],
          s3.[principal_id],
          s3.[schema_id],
          s3.[parent_object_id],
          s3.[Type],
          s3.[type_desc],
          s3.[create_date],
          s3.[modify_date],
          s3.[is_ms_shipped],
          s3.[is_published],
          s3.[is_schema_published],
          s3.[base_object_name]
        FROM
          [sys].[synonyms] s3
        """;

    public const int NAME_FIELD_ID = 0;
    public const int OBJECTID_FIELD_ID = 1;
    public const int PRINCIPALID_FIELD_ID = 2;
    public const int SCHEMAID_FIELD_ID = 3;
    public const int PARENTOBJECTID_FIELD_ID = 4;
    public const int TYPE_FIELD_ID = 5;
    public const int TYPEDESC_FIELD_ID = 6;
    public const int CREATEDATE_FIELD_ID = 7;
    public const int MODIFYDATE_FIELD_ID = 8;
    public const int ISMSSHIPPED_FIELD_ID = 9;
    public const int ISPUBLISHED_FIELD_ID = 10;
    public const int ISSCHEMAPUBLISHED_FIELD_ID = 11;
    public const int BASEOBJECTNAME_FIELD_ID = 12;


    public SynonymsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SynonymsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SynonymsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public int SchemaId
    {
        get
        {
            return base.GetInt32(SCHEMAID_FIELD_ID);
        }
    }

    public int ParentObjectId
    {
        get
        {
            return base.GetInt32(PARENTOBJECTID_FIELD_ID);
        }
    }

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
        }
    }

    public string? TypeDesc
    {
        get
        {
            return base.GetNullableString(TYPEDESC_FIELD_ID);
        }
    }

    public DateTime CreateDate
    {
        get
        {
            return base.GetDateTime(CREATEDATE_FIELD_ID);
        }
    }

    public DateTime ModifyDate
    {
        get
        {
            return base.GetDateTime(MODIFYDATE_FIELD_ID);
        }
    }

    public bool IsMsShipped
    {
        get
        {
            return base.GetBoolean(ISMSSHIPPED_FIELD_ID);
        }
    }

    public bool IsPublished
    {
        get
        {
            return base.GetBoolean(ISPUBLISHED_FIELD_ID);
        }
    }

    public bool IsSchemaPublished
    {
        get
        {
            return base.GetBoolean(ISSCHEMAPUBLISHED_FIELD_ID);
        }
    }

    public string? BaseObjectName
    {
        get
        {
            return base.GetNullableString(BASEOBJECTNAME_FIELD_ID);
        }
    }


    public Types.SynonymsDataType ToDataObject()
    {
        return new Types.SynonymsDataType(Name,
            ObjectId,
            PrincipalId,
            SchemaId,
            ParentObjectId,
            Type,
            TypeDesc,
            CreateDate,
            ModifyDate,
            IsMsShipped,
            IsPublished,
            IsSchemaPublished,
            BaseObjectName);
    }

    public List<Types.SynonymsDataType> ToList()
    {
        var list = new List<Types.SynonymsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

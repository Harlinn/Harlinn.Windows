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

public class ExtendedProceduresReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[extended_procedures]";
    public const string TableName = "extended_procedures";
    public const string ShortName = "ep0";
    public const string Sql = """
        SELECT
          ep0.[Name],
          ep0.[object_id],
          ep0.[principal_id],
          ep0.[schema_id],
          ep0.[parent_object_id],
          ep0.[Type],
          ep0.[type_desc],
          ep0.[create_date],
          ep0.[modify_date],
          ep0.[is_ms_shipped],
          ep0.[is_published],
          ep0.[is_schema_published],
          ep0.[dll_name]
        FROM
          [sys].[extended_procedures] ep0
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
    public const int DLLNAME_FIELD_ID = 12;


    public ExtendedProceduresReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ExtendedProceduresReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ExtendedProceduresReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public string? DllName
    {
        get
        {
            return base.GetNullableString(DLLNAME_FIELD_ID);
        }
    }


    public Types.ExtendedProceduresDataType ToDataObject()
    {
        return new Types.ExtendedProceduresDataType(Name,
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
            DllName);
    }

    public List<Types.ExtendedProceduresDataType> ToList()
    {
        var list = new List<Types.ExtendedProceduresDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

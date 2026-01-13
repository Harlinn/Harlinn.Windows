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

public class PlanGuidesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[plan_guides]";
    public const string TableName = "plan_guides";
    public const string ShortName = "pg";
    public const string Sql = """
        SELECT
          pg.[plan_guide_id],
          pg.[Name],
          pg.[create_date],
          pg.[modify_date],
          pg.[is_disabled],
          pg.[query_text],
          pg.[scope_type],
          pg.[scope_type_desc],
          pg.[scope_object_id],
          pg.[scope_batch],
          pg.[Parameters],
          pg.[Hints]
        FROM
          [sys].[plan_guides] pg
        """;

    public const int PLANGUIDEID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int CREATEDATE_FIELD_ID = 2;
    public const int MODIFYDATE_FIELD_ID = 3;
    public const int ISDISABLED_FIELD_ID = 4;
    public const int QUERYTEXT_FIELD_ID = 5;
    public const int SCOPETYPE_FIELD_ID = 6;
    public const int SCOPETYPEDESC_FIELD_ID = 7;
    public const int SCOPEOBJECTID_FIELD_ID = 8;
    public const int SCOPEBATCH_FIELD_ID = 9;
    public const int PARAMETERS_FIELD_ID = 10;
    public const int HINTS_FIELD_ID = 11;


    public PlanGuidesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public PlanGuidesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public PlanGuidesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int PlanGuideId
    {
        get
        {
            return base.GetInt32(PLANGUIDEID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
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

    public bool IsDisabled
    {
        get
        {
            return base.GetBoolean(ISDISABLED_FIELD_ID);
        }
    }

    public string? QueryText
    {
        get
        {
            return base.GetNullableString(QUERYTEXT_FIELD_ID);
        }
    }

    public byte ScopeType
    {
        get
        {
            return base.GetByte(SCOPETYPE_FIELD_ID);
        }
    }

    public string? ScopeTypeDesc
    {
        get
        {
            return base.GetNullableString(SCOPETYPEDESC_FIELD_ID);
        }
    }

    public int? ScopeObjectId
    {
        get
        {
            return base.GetNullableInt32(SCOPEOBJECTID_FIELD_ID);
        }
    }

    public string? ScopeBatch
    {
        get
        {
            return base.GetNullableString(SCOPEBATCH_FIELD_ID);
        }
    }

    public string? Parameters
    {
        get
        {
            return base.GetNullableString(PARAMETERS_FIELD_ID);
        }
    }

    public string? Hints
    {
        get
        {
            return base.GetNullableString(HINTS_FIELD_ID);
        }
    }


    public Types.PlanGuidesDataType ToDataObject()
    {
        return new Types.PlanGuidesDataType(PlanGuideId,
            Name,
            CreateDate,
            ModifyDate,
            IsDisabled,
            QueryText,
            ScopeType,
            ScopeTypeDesc,
            ScopeObjectId,
            ScopeBatch,
            Parameters,
            Hints);
    }

    public List<Types.PlanGuidesDataType> ToList()
    {
        var list = new List<Types.PlanGuidesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

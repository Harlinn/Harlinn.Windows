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

public class TriggersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[triggers]";
    public const string TableName = "triggers";
    public const string ShortName = "t1";
    public const string Sql = """
        SELECT
          t1.[Name],
          t1.[object_id],
          t1.[parent_class],
          t1.[parent_class_desc],
          t1.[parent_id],
          t1.[Type],
          t1.[type_desc],
          t1.[create_date],
          t1.[modify_date],
          t1.[is_ms_shipped],
          t1.[is_disabled],
          t1.[is_not_for_replication],
          t1.[is_instead_of_trigger]
        FROM
          [sys].[triggers] t1
        """;

    public const int NAME_FIELD_ID = 0;
    public const int OBJECTID_FIELD_ID = 1;
    public const int PARENTCLASS_FIELD_ID = 2;
    public const int PARENTCLASSDESC_FIELD_ID = 3;
    public const int PARENTID_FIELD_ID = 4;
    public const int TYPE_FIELD_ID = 5;
    public const int TYPEDESC_FIELD_ID = 6;
    public const int CREATEDATE_FIELD_ID = 7;
    public const int MODIFYDATE_FIELD_ID = 8;
    public const int ISMSSHIPPED_FIELD_ID = 9;
    public const int ISDISABLED_FIELD_ID = 10;
    public const int ISNOTFORREPLICATION_FIELD_ID = 11;
    public const int ISINSTEADOFTRIGGER_FIELD_ID = 12;


    public TriggersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public TriggersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public TriggersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public byte ParentClass
    {
        get
        {
            return base.GetByte(PARENTCLASS_FIELD_ID);
        }
    }

    public string? ParentClassDesc
    {
        get
        {
            return base.GetNullableString(PARENTCLASSDESC_FIELD_ID);
        }
    }

    public int ParentId
    {
        get
        {
            return base.GetInt32(PARENTID_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return base.GetString(TYPE_FIELD_ID);
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

    public bool IsDisabled
    {
        get
        {
            return base.GetBoolean(ISDISABLED_FIELD_ID);
        }
    }

    public bool IsNotForReplication
    {
        get
        {
            return base.GetBoolean(ISNOTFORREPLICATION_FIELD_ID);
        }
    }

    public bool IsInsteadOfTrigger
    {
        get
        {
            return base.GetBoolean(ISINSTEADOFTRIGGER_FIELD_ID);
        }
    }


    public Types.Trigger ToDataObject()
    {
        return new Types.Trigger(Name,
            ObjectId,
            ParentClass,
            ParentClassDesc,
            ParentId,
            Type,
            TypeDesc,
            CreateDate,
            ModifyDate,
            IsMsShipped,
            IsDisabled,
            IsNotForReplication,
            IsInsteadOfTrigger);
    }

    public List<Types.Trigger> ToList()
    {
        var list = new List<Types.Trigger>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

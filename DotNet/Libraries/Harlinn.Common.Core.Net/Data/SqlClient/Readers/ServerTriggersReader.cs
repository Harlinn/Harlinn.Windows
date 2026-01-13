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

public class ServerTriggersReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[server_triggers]";
    public const string TableName = "server_triggers";
    public const string ShortName = "st";
    public const string Sql = """
        SELECT
          st.[Name],
          st.[object_id],
          st.[parent_class],
          st.[parent_class_desc],
          st.[parent_id],
          st.[Type],
          st.[type_desc],
          st.[create_date],
          st.[modify_date],
          st.[is_ms_shipped],
          st.[is_disabled]
        FROM
          [sys].[server_triggers] st
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


    public ServerTriggersReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServerTriggersReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServerTriggersReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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


    public Types.ServerTriggersDataType ToDataObject()
    {
        return new Types.ServerTriggersDataType(Name,
            ObjectId,
            ParentClass,
            ParentClassDesc,
            ParentId,
            Type,
            TypeDesc,
            CreateDate,
            ModifyDate,
            IsMsShipped,
            IsDisabled);
    }

    public List<Types.ServerTriggersDataType> ToList()
    {
        var list = new List<Types.ServerTriggersDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

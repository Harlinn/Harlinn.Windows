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

public class SecurityPoliciesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[security_policies]";
    public const string TableName = "security_policies";
    public const string ShortName = "sp0";
    public const string Sql = """
        SELECT
          sp0.[Name],
          sp0.[object_id],
          sp0.[principal_id],
          sp0.[schema_id],
          sp0.[parent_object_id],
          sp0.[Type],
          sp0.[type_desc],
          sp0.[create_date],
          sp0.[modify_date],
          sp0.[is_ms_shipped],
          sp0.[is_enabled],
          sp0.[is_not_for_replication],
          sp0.[uses_database_collation],
          sp0.[is_schema_bound]
        FROM
          [sys].[security_policies] sp0
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
    public const int ISENABLED_FIELD_ID = 10;
    public const int ISNOTFORREPLICATION_FIELD_ID = 11;
    public const int USESDATABASECOLLATION_FIELD_ID = 12;
    public const int ISSCHEMABOUND_FIELD_ID = 13;


    public SecurityPoliciesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SecurityPoliciesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SecurityPoliciesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public bool IsEnabled
    {
        get
        {
            return base.GetBoolean(ISENABLED_FIELD_ID);
        }
    }

    public bool IsNotForReplication
    {
        get
        {
            return base.GetBoolean(ISNOTFORREPLICATION_FIELD_ID);
        }
    }

    public bool? UsesDatabaseCollation
    {
        get
        {
            return base.GetNullableBoolean(USESDATABASECOLLATION_FIELD_ID);
        }
    }

    public bool IsSchemaBound
    {
        get
        {
            return base.GetBoolean(ISSCHEMABOUND_FIELD_ID);
        }
    }


    public Types.SecurityPoliciesDataType ToDataObject()
    {
        return new Types.SecurityPoliciesDataType(Name,
            ObjectId,
            PrincipalId,
            SchemaId,
            ParentObjectId,
            Type,
            TypeDesc,
            CreateDate,
            ModifyDate,
            IsMsShipped,
            IsEnabled,
            IsNotForReplication,
            UsesDatabaseCollation,
            IsSchemaBound);
    }

    public List<Types.SecurityPoliciesDataType> ToList()
    {
        var list = new List<Types.SecurityPoliciesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

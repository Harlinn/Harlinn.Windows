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

public class DmAuditActionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_audit_actions]";
    public const string TableName = "dm_audit_actions";
    public const string ShortName = "daa";
    public const string Sql = """
        SELECT
          daa.[action_id],
          daa.[Name],
          daa.[class_desc],
          daa.[covering_action_name],
          daa.[parent_class_desc],
          daa.[covering_parent_action_name],
          daa.[configuration_level],
          daa.[containing_group_name],
          daa.[action_in_log]
        FROM
          [sys].[dm_audit_actions] daa
        """;

    public const int ACTIONID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int CLASSDESC_FIELD_ID = 2;
    public const int COVERINGACTIONNAME_FIELD_ID = 3;
    public const int PARENTCLASSDESC_FIELD_ID = 4;
    public const int COVERINGPARENTACTIONNAME_FIELD_ID = 5;
    public const int CONFIGURATIONLEVEL_FIELD_ID = 6;
    public const int CONTAININGGROUPNAME_FIELD_ID = 7;
    public const int ACTIONINLOG_FIELD_ID = 8;


    public DmAuditActionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmAuditActionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmAuditActionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? ActionId
    {
        get
        {
            return base.GetNullableString(ACTIONID_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public string? ClassDesc
    {
        get
        {
            return base.GetNullableString(CLASSDESC_FIELD_ID);
        }
    }

    public string? CoveringActionName
    {
        get
        {
            return base.GetNullableString(COVERINGACTIONNAME_FIELD_ID);
        }
    }

    public string? ParentClassDesc
    {
        get
        {
            return base.GetNullableString(PARENTCLASSDESC_FIELD_ID);
        }
    }

    public string? CoveringParentActionName
    {
        get
        {
            return base.GetNullableString(COVERINGPARENTACTIONNAME_FIELD_ID);
        }
    }

    public string? ConfigurationLevel
    {
        get
        {
            return base.GetNullableString(CONFIGURATIONLEVEL_FIELD_ID);
        }
    }

    public string? ContainingGroupName
    {
        get
        {
            return base.GetNullableString(CONTAININGGROUPNAME_FIELD_ID);
        }
    }

    public bool ActionInLog
    {
        get
        {
            return base.GetBoolean(ACTIONINLOG_FIELD_ID);
        }
    }


    public Types.DmAuditActionsDataType ToDataObject()
    {
        return new Types.DmAuditActionsDataType(ActionId,
            Name,
            ClassDesc,
            CoveringActionName,
            ParentClassDesc,
            CoveringParentActionName,
            ConfigurationLevel,
            ContainingGroupName,
            ActionInLog);
    }

    public List<Types.DmAuditActionsDataType> ToList()
    {
        var list = new List<Types.DmAuditActionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

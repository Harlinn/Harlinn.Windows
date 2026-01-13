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

public class DmDbScriptLevelReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_script_level]";
    public const string TableName = "dm_db_script_level";
    public const string ShortName = "ddsl";
    public const string Sql = """
        SELECT
          ddsl.[database_id],
          ddsl.[script_id],
          ddsl.[script_name],
          ddsl.[Version],
          ddsl.[script_level],
          ddsl.[downgrade_start_level],
          ddsl.[downgrade_target_level],
          ddsl.[upgrade_start_level],
          ddsl.[upgrade_target_level]
        FROM
          [sys].[dm_db_script_level] ddsl
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int SCRIPTID_FIELD_ID = 1;
    public const int SCRIPTNAME_FIELD_ID = 2;
    public const int VERSION_FIELD_ID = 3;
    public const int SCRIPTLEVEL_FIELD_ID = 4;
    public const int DOWNGRADESTARTLEVEL_FIELD_ID = 5;
    public const int DOWNGRADETARGETLEVEL_FIELD_ID = 6;
    public const int UPGRADESTARTLEVEL_FIELD_ID = 7;
    public const int UPGRADETARGETLEVEL_FIELD_ID = 8;


    public DmDbScriptLevelReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbScriptLevelReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbScriptLevelReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DatabaseId
    {
        get
        {
            return base.GetInt32(DATABASEID_FIELD_ID);
        }
    }

    public int ScriptId
    {
        get
        {
            return base.GetInt32(SCRIPTID_FIELD_ID);
        }
    }

    public string? ScriptName
    {
        get
        {
            return base.GetNullableString(SCRIPTNAME_FIELD_ID);
        }
    }

    public int Version
    {
        get
        {
            return base.GetInt32(VERSION_FIELD_ID);
        }
    }

    public int ScriptLevel
    {
        get
        {
            return base.GetInt32(SCRIPTLEVEL_FIELD_ID);
        }
    }

    public int DowngradeStartLevel
    {
        get
        {
            return base.GetInt32(DOWNGRADESTARTLEVEL_FIELD_ID);
        }
    }

    public int DowngradeTargetLevel
    {
        get
        {
            return base.GetInt32(DOWNGRADETARGETLEVEL_FIELD_ID);
        }
    }

    public int? UpgradeStartLevel
    {
        get
        {
            return base.GetNullableInt32(UPGRADESTARTLEVEL_FIELD_ID);
        }
    }

    public int? UpgradeTargetLevel
    {
        get
        {
            return base.GetNullableInt32(UPGRADETARGETLEVEL_FIELD_ID);
        }
    }


    public Types.DmDbScriptLevelDataType ToDataObject()
    {
        return new Types.DmDbScriptLevelDataType(DatabaseId,
            ScriptId,
            ScriptName,
            Version,
            ScriptLevel,
            DowngradeStartLevel,
            DowngradeTargetLevel,
            UpgradeStartLevel,
            UpgradeTargetLevel);
    }

    public List<Types.DmDbScriptLevelDataType> ToList()
    {
        var list = new List<Types.DmDbScriptLevelDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

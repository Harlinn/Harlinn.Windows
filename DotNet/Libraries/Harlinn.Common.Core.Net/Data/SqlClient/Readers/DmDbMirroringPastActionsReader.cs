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

public class DmDbMirroringPastActionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_db_mirroring_past_actions]";
    public const string TableName = "dm_db_mirroring_past_actions";
    public const string ShortName = "ddmpa";
    public const string Sql = """
        SELECT
          ddmpa.[mirroring_guid],
          ddmpa.[state_machine_name],
          ddmpa.[action_type],
          ddmpa.[Name],
          ddmpa.[current_state],
          ddmpa.[action_sequence]
        FROM
          [sys].[dm_db_mirroring_past_actions] ddmpa
        """;

    public const int MIRRORINGGUID_FIELD_ID = 0;
    public const int STATEMACHINENAME_FIELD_ID = 1;
    public const int ACTIONTYPE_FIELD_ID = 2;
    public const int NAME_FIELD_ID = 3;
    public const int CURRENTSTATE_FIELD_ID = 4;
    public const int ACTIONSEQUENCE_FIELD_ID = 5;


    public DmDbMirroringPastActionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmDbMirroringPastActionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmDbMirroringPastActionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid? MirroringGuid
    {
        get
        {
            return base.GetNullableGuid(MIRRORINGGUID_FIELD_ID);
        }
    }

    public string? StateMachineName
    {
        get
        {
            return base.GetNullableString(STATEMACHINENAME_FIELD_ID);
        }
    }

    public string? ActionType
    {
        get
        {
            return base.GetNullableString(ACTIONTYPE_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public string? CurrentState
    {
        get
        {
            return base.GetNullableString(CURRENTSTATE_FIELD_ID);
        }
    }

    public int ActionSequence
    {
        get
        {
            return base.GetInt32(ACTIONSEQUENCE_FIELD_ID);
        }
    }


    public Types.DmDbMirroringPastActionsDataType ToDataObject()
    {
        return new Types.DmDbMirroringPastActionsDataType(MirroringGuid,
            StateMachineName,
            ActionType,
            Name,
            CurrentState,
            ActionSequence);
    }

    public List<Types.DmDbMirroringPastActionsDataType> ToList()
    {
        var list = new List<Types.DmDbMirroringPastActionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

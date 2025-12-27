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

public class DatabaseAutomaticTuningOptionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[database_automatic_tuning_options]";
    public const string TableName = "database_automatic_tuning_options";
    public const string ShortName = "dato";
    public const string Sql = """
        SELECT
          dato.[Name],
          dato.[desired_state],
          dato.[desired_state_desc],
          dato.[actual_state],
          dato.[actual_state_desc],
          dato.[Reason],
          dato.[reason_desc]
        FROM
          [sys].[database_automatic_tuning_options] dato
        """;

    public const int NAME_FIELD_ID = 0;
    public const int DESIREDSTATE_FIELD_ID = 1;
    public const int DESIREDSTATEDESC_FIELD_ID = 2;
    public const int ACTUALSTATE_FIELD_ID = 3;
    public const int ACTUALSTATEDESC_FIELD_ID = 4;
    public const int REASON_FIELD_ID = 5;
    public const int REASONDESC_FIELD_ID = 6;


    public DatabaseAutomaticTuningOptionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DatabaseAutomaticTuningOptionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DatabaseAutomaticTuningOptionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public short? DesiredState
    {
        get
        {
            return base.GetNullableInt16(DESIREDSTATE_FIELD_ID);
        }
    }

    public string? DesiredStateDesc
    {
        get
        {
            return base.GetNullableString(DESIREDSTATEDESC_FIELD_ID);
        }
    }

    public short? ActualState
    {
        get
        {
            return base.GetNullableInt16(ACTUALSTATE_FIELD_ID);
        }
    }

    public string? ActualStateDesc
    {
        get
        {
            return base.GetNullableString(ACTUALSTATEDESC_FIELD_ID);
        }
    }

    public short? Reason
    {
        get
        {
            return base.GetNullableInt16(REASON_FIELD_ID);
        }
    }

    public string? ReasonDesc
    {
        get
        {
            return base.GetNullableString(REASONDESC_FIELD_ID);
        }
    }


    public Types.DatabaseAutomaticTuningOptionsDataType ToDataObject()
    {
        return new Types.DatabaseAutomaticTuningOptionsDataType(Name,
            DesiredState,
            DesiredStateDesc,
            ActualState,
            ActualStateDesc,
            Reason,
            ReasonDesc);
    }

    public List<Types.DatabaseAutomaticTuningOptionsDataType> ToList()
    {
        var list = new List<Types.DatabaseAutomaticTuningOptionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

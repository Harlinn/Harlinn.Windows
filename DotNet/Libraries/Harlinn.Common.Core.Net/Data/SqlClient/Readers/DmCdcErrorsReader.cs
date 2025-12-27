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

public class DmCdcErrorsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_cdc_errors]";
    public const string TableName = "dm_cdc_errors";
    public const string ShortName = "dce";
    public const string Sql = """
        SELECT
          dce.[session_id],
          dce.[phase_number],
          dce.[entry_time],
          dce.[error_number],
          dce.[error_severity],
          dce.[error_state],
          dce.[error_message],
          dce.[start_lsn],
          dce.[begin_lsn],
          dce.[sequence_value]
        FROM
          [sys].[dm_cdc_errors] dce
        """;

    public const int SESSIONID_FIELD_ID = 0;
    public const int PHASENUMBER_FIELD_ID = 1;
    public const int ENTRYTIME_FIELD_ID = 2;
    public const int ERRORNUMBER_FIELD_ID = 3;
    public const int ERRORSEVERITY_FIELD_ID = 4;
    public const int ERRORSTATE_FIELD_ID = 5;
    public const int ERRORMESSAGE_FIELD_ID = 6;
    public const int STARTLSN_FIELD_ID = 7;
    public const int BEGINLSN_FIELD_ID = 8;
    public const int SEQUENCEVALUE_FIELD_ID = 9;


    public DmCdcErrorsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmCdcErrorsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmCdcErrorsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? SessionId
    {
        get
        {
            return base.GetNullableInt32(SESSIONID_FIELD_ID);
        }
    }

    public int? PhaseNumber
    {
        get
        {
            return base.GetNullableInt32(PHASENUMBER_FIELD_ID);
        }
    }

    public DateTime? EntryTime
    {
        get
        {
            return base.GetNullableDateTime(ENTRYTIME_FIELD_ID);
        }
    }

    public int? ErrorNumber
    {
        get
        {
            return base.GetNullableInt32(ERRORNUMBER_FIELD_ID);
        }
    }

    public int? ErrorSeverity
    {
        get
        {
            return base.GetNullableInt32(ERRORSEVERITY_FIELD_ID);
        }
    }

    public int? ErrorState
    {
        get
        {
            return base.GetNullableInt32(ERRORSTATE_FIELD_ID);
        }
    }

    public string? ErrorMessage
    {
        get
        {
            return base.GetNullableString(ERRORMESSAGE_FIELD_ID);
        }
    }

    public string? StartLsn
    {
        get
        {
            return base.GetNullableString(STARTLSN_FIELD_ID);
        }
    }

    public string? BeginLsn
    {
        get
        {
            return base.GetNullableString(BEGINLSN_FIELD_ID);
        }
    }

    public string? SequenceValue
    {
        get
        {
            return base.GetNullableString(SEQUENCEVALUE_FIELD_ID);
        }
    }


    public Types.DmCdcErrorsDataType ToDataObject()
    {
        return new Types.DmCdcErrorsDataType(SessionId,
            PhaseNumber,
            EntryTime,
            ErrorNumber,
            ErrorSeverity,
            ErrorState,
            ErrorMessage,
            StartLsn,
            BeginLsn,
            SequenceValue);
    }

    public List<Types.DmCdcErrorsDataType> ToList()
    {
        var list = new List<Types.DmCdcErrorsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

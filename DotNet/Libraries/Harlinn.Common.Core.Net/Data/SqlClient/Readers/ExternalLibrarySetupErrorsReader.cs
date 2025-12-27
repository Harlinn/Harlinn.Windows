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

public class ExternalLibrarySetupErrorsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[external_library_setup_errors]";
    public const string TableName = "external_library_setup_errors";
    public const string ShortName = "else";
    public const string Sql = """
        SELECT
          else.[db_id],
          else.[principal_id],
          else.[external_library_id],
          else.[error_code],
          else.[error_timestamp],
          else.[error_message]
        FROM
          [sys].[external_library_setup_errors] else
        """;

    public const int DBID_FIELD_ID = 0;
    public const int PRINCIPALID_FIELD_ID = 1;
    public const int EXTERNALLIBRARYID_FIELD_ID = 2;
    public const int ERRORCODE_FIELD_ID = 3;
    public const int ERRORTIMESTAMP_FIELD_ID = 4;
    public const int ERRORMESSAGE_FIELD_ID = 5;


    public ExternalLibrarySetupErrorsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ExternalLibrarySetupErrorsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ExternalLibrarySetupErrorsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DbId
    {
        get
        {
            return base.GetInt32(DBID_FIELD_ID);
        }
    }

    public int PrincipalId
    {
        get
        {
            return base.GetInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public int ExternalLibraryId
    {
        get
        {
            return base.GetInt32(EXTERNALLIBRARYID_FIELD_ID);
        }
    }

    public int ErrorCode
    {
        get
        {
            return base.GetInt32(ERRORCODE_FIELD_ID);
        }
    }

    public DateTime ErrorTimestamp
    {
        get
        {
            return base.GetDateTime(ERRORTIMESTAMP_FIELD_ID);
        }
    }

    public string? ErrorMessage
    {
        get
        {
            return base.GetNullableString(ERRORMESSAGE_FIELD_ID);
        }
    }


    public Types.ExternalLibrarySetupErrorsDataType ToDataObject()
    {
        return new Types.ExternalLibrarySetupErrorsDataType(DbId,
            PrincipalId,
            ExternalLibraryId,
            ErrorCode,
            ErrorTimestamp,
            ErrorMessage);
    }

    public List<Types.ExternalLibrarySetupErrorsDataType> ToList()
    {
        var list = new List<Types.ExternalLibrarySetupErrorsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

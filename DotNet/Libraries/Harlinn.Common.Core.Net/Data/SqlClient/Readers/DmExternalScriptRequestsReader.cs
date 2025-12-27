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

public class DmExternalScriptRequestsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_external_script_requests]";
    public const string TableName = "dm_external_script_requests";
    public const string ShortName = "desr";
    public const string Sql = """
        SELECT
          desr.[external_script_request_id],
          desr.[Language],
          desr.[degree_of_parallelism],
          desr.[external_user_name]
        FROM
          [sys].[dm_external_script_requests] desr
        """;

    public const int EXTERNALSCRIPTREQUESTID_FIELD_ID = 0;
    public const int LANGUAGE_FIELD_ID = 1;
    public const int DEGREEOFPARALLELISM_FIELD_ID = 2;
    public const int EXTERNALUSERNAME_FIELD_ID = 3;


    public DmExternalScriptRequestsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmExternalScriptRequestsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmExternalScriptRequestsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid ExternalScriptRequestId
    {
        get
        {
            return base.GetGuid(EXTERNALSCRIPTREQUESTID_FIELD_ID);
        }
    }

    public string? Language
    {
        get
        {
            return base.GetNullableString(LANGUAGE_FIELD_ID);
        }
    }

    public int DegreeOfParallelism
    {
        get
        {
            return base.GetInt32(DEGREEOFPARALLELISM_FIELD_ID);
        }
    }

    public string ExternalUserName
    {
        get
        {
            return base.GetString(EXTERNALUSERNAME_FIELD_ID);
        }
    }


    public Types.DmExternalScriptRequestsDataType ToDataObject()
    {
        return new Types.DmExternalScriptRequestsDataType(ExternalScriptRequestId,
            Language,
            DegreeOfParallelism,
            ExternalUserName);
    }

    public List<Types.DmExternalScriptRequestsDataType> ToList()
    {
        var list = new List<Types.DmExternalScriptRequestsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

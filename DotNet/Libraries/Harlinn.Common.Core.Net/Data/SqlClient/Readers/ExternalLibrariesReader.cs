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

public class ExternalLibrariesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[external_libraries]";
    public const string TableName = "external_libraries";
    public const string ShortName = "el0";
    public const string Sql = """
        SELECT
          el0.[external_library_id],
          el0.[Name],
          el0.[principal_id],
          el0.[Language],
          el0.[Scope],
          el0.[scope_desc]
        FROM
          [sys].[external_libraries] el0
        """;

    public const int EXTERNALLIBRARYID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int PRINCIPALID_FIELD_ID = 2;
    public const int LANGUAGE_FIELD_ID = 3;
    public const int SCOPE_FIELD_ID = 4;
    public const int SCOPEDESC_FIELD_ID = 5;


    public ExternalLibrariesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ExternalLibrariesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ExternalLibrariesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ExternalLibraryId
    {
        get
        {
            return base.GetInt32(EXTERNALLIBRARYID_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public string? Language
    {
        get
        {
            return base.GetNullableString(LANGUAGE_FIELD_ID);
        }
    }

    public int Scope
    {
        get
        {
            return base.GetInt32(SCOPE_FIELD_ID);
        }
    }

    public string ScopeDesc
    {
        get
        {
            return base.GetString(SCOPEDESC_FIELD_ID);
        }
    }


    public Types.ExternalLibrariesDataType ToDataObject()
    {
        return new Types.ExternalLibrariesDataType(ExternalLibraryId,
            Name,
            PrincipalId,
            Language,
            Scope,
            ScopeDesc);
    }

    public List<Types.ExternalLibrariesDataType> ToList()
    {
        var list = new List<Types.ExternalLibrariesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

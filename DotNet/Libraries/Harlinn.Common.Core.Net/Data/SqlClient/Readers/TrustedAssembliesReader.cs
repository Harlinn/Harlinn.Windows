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

public class TrustedAssembliesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[trusted_assemblies]";
    public const string TableName = "trusted_assemblies";
    public const string ShortName = "ta";
    public const string Sql = """
        SELECT
          ta.[Hash],
          ta.[Description],
          ta.[create_date],
          ta.[created_by]
        FROM
          [sys].[trusted_assemblies] ta
        """;

    public const int HASH_FIELD_ID = 0;
    public const int DESCRIPTION_FIELD_ID = 1;
    public const int CREATEDATE_FIELD_ID = 2;
    public const int CREATEDBY_FIELD_ID = 3;


    public TrustedAssembliesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public TrustedAssembliesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public TrustedAssembliesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[]? Hash
    {
        get
        {
            return base.GetNullableBinary(HASH_FIELD_ID);
        }
    }

    public string? Description
    {
        get
        {
            return base.GetNullableString(DESCRIPTION_FIELD_ID);
        }
    }

    public DateTime CreateDate
    {
        get
        {
            return base.GetDateTime(CREATEDATE_FIELD_ID);
        }
    }

    public string CreatedBy
    {
        get
        {
            return base.GetString(CREATEDBY_FIELD_ID);
        }
    }


    public Types.TrustedAssembly ToDataObject()
    {
        return new Types.TrustedAssembly(Hash,
            Description,
            CreateDate,
            CreatedBy);
    }

    public List<Types.TrustedAssembly> ToList()
    {
        var list = new List<Types.TrustedAssembly>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

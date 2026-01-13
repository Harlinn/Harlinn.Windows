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

public class DatabaseFilestreamOptionsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[database_filestream_options]";
    public const string TableName = "database_filestream_options";
    public const string ShortName = "dfo";
    public const string Sql = """
        SELECT
          dfo.[database_id],
          dfo.[non_transacted_access],
          dfo.[non_transacted_access_desc],
          dfo.[directory_name]
        FROM
          [sys].[database_filestream_options] dfo
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int NONTRANSACTEDACCESS_FIELD_ID = 1;
    public const int NONTRANSACTEDACCESSDESC_FIELD_ID = 2;
    public const int DIRECTORYNAME_FIELD_ID = 3;


    public DatabaseFilestreamOptionsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DatabaseFilestreamOptionsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DatabaseFilestreamOptionsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public byte NonTransactedAccess
    {
        get
        {
            return base.GetByte(NONTRANSACTEDACCESS_FIELD_ID);
        }
    }

    public string NonTransactedAccessDesc
    {
        get
        {
            return base.GetString(NONTRANSACTEDACCESSDESC_FIELD_ID);
        }
    }

    public string? DirectoryName
    {
        get
        {
            return base.GetNullableString(DIRECTORYNAME_FIELD_ID);
        }
    }


    public Types.DatabaseFilestreamOptionsDataType ToDataObject()
    {
        return new Types.DatabaseFilestreamOptionsDataType(DatabaseId,
            NonTransactedAccess,
            NonTransactedAccessDesc,
            DirectoryName);
    }

    public List<Types.DatabaseFilestreamOptionsDataType> ToList()
    {
        var list = new List<Types.DatabaseFilestreamOptionsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class FiletablesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[filetables]";
    public const string TableName = "filetables";
    public const string ShortName = "f";
    public const string Sql = """
        SELECT
          f.[object_id],
          f.[is_enabled],
          f.[directory_name],
          f.[filename_collation_id],
          f.[filename_collation_name]
        FROM
          [sys].[filetables] f
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int ISENABLED_FIELD_ID = 1;
    public const int DIRECTORYNAME_FIELD_ID = 2;
    public const int FILENAMECOLLATIONID_FIELD_ID = 3;
    public const int FILENAMECOLLATIONNAME_FIELD_ID = 4;


    public FiletablesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FiletablesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FiletablesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public bool IsEnabled
    {
        get
        {
            return base.GetBoolean(ISENABLED_FIELD_ID);
        }
    }

    public string DirectoryName
    {
        get
        {
            return base.GetString(DIRECTORYNAME_FIELD_ID);
        }
    }

    public int FilenameCollationId
    {
        get
        {
            return base.GetInt32(FILENAMECOLLATIONID_FIELD_ID);
        }
    }

    public string FilenameCollationName
    {
        get
        {
            return base.GetString(FILENAMECOLLATIONNAME_FIELD_ID);
        }
    }


    public Types.FiletablesDataType ToDataObject()
    {
        return new Types.FiletablesDataType(ObjectId,
            IsEnabled,
            DirectoryName,
            FilenameCollationId,
            FilenameCollationName);
    }

    public List<Types.FiletablesDataType> ToList()
    {
        var list = new List<Types.FiletablesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

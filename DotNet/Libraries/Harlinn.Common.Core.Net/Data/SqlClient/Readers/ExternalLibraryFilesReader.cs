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

public class ExternalLibraryFilesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[external_library_files]";
    public const string TableName = "external_library_files";
    public const string ShortName = "elf0";
    public const string Sql = """
        SELECT
          elf0.[external_library_id],
          elf0.[Content],
          elf0.[Platform],
          elf0.[platform_desc]
        FROM
          [sys].[external_library_files] elf0
        """;

    public const int EXTERNALLIBRARYID_FIELD_ID = 0;
    public const int CONTENT_FIELD_ID = 1;
    public const int PLATFORM_FIELD_ID = 2;
    public const int PLATFORMDESC_FIELD_ID = 3;


    public ExternalLibraryFilesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ExternalLibraryFilesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ExternalLibraryFilesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public byte[]? Content
    {
        get
        {
            return base.GetNullableBinary(CONTENT_FIELD_ID);
        }
    }

    public byte? Platform
    {
        get
        {
            return base.GetNullableByte(PLATFORM_FIELD_ID);
        }
    }

    public string? PlatformDesc
    {
        get
        {
            return base.GetNullableString(PLATFORMDESC_FIELD_ID);
        }
    }


    public Types.ExternalLibraryFilesDataType ToDataObject()
    {
        return new Types.ExternalLibraryFilesDataType(ExternalLibraryId,
            Content,
            Platform,
            PlatformDesc);
    }

    public List<Types.ExternalLibraryFilesDataType> ToList()
    {
        var list = new List<Types.ExternalLibraryFilesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

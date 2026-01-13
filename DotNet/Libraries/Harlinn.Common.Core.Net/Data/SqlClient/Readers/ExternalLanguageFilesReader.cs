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

public class ExternalLanguageFilesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[external_language_files]";
    public const string TableName = "external_language_files";
    public const string ShortName = "elf";
    public const string Sql = """
        SELECT
          elf.[external_language_id],
          elf.[Content],
          elf.[file_name],
          elf.[Platform],
          elf.[platform_desc],
          elf.[Parameters],
          elf.[environment_variables]
        FROM
          [sys].[external_language_files] elf
        """;

    public const int EXTERNALLANGUAGEID_FIELD_ID = 0;
    public const int CONTENT_FIELD_ID = 1;
    public const int FILENAME_FIELD_ID = 2;
    public const int PLATFORM_FIELD_ID = 3;
    public const int PLATFORMDESC_FIELD_ID = 4;
    public const int PARAMETERS_FIELD_ID = 5;
    public const int ENVIRONMENTVARIABLES_FIELD_ID = 6;


    public ExternalLanguageFilesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ExternalLanguageFilesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ExternalLanguageFilesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ExternalLanguageId
    {
        get
        {
            return base.GetInt32(EXTERNALLANGUAGEID_FIELD_ID);
        }
    }

    public byte[]? Content
    {
        get
        {
            return base.GetNullableBinary(CONTENT_FIELD_ID);
        }
    }

    public string? FileName
    {
        get
        {
            return base.GetNullableString(FILENAME_FIELD_ID);
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

    public string? Parameters
    {
        get
        {
            return base.GetNullableString(PARAMETERS_FIELD_ID);
        }
    }

    public string? EnvironmentVariables
    {
        get
        {
            return base.GetNullableString(ENVIRONMENTVARIABLES_FIELD_ID);
        }
    }


    public Types.ExternalLanguageFilesDataType ToDataObject()
    {
        return new Types.ExternalLanguageFilesDataType(ExternalLanguageId,
            Content,
            FileName,
            Platform,
            PlatformDesc,
            Parameters,
            EnvironmentVariables);
    }

    public List<Types.ExternalLanguageFilesDataType> ToList()
    {
        var list = new List<Types.ExternalLanguageFilesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class ExternalFileFormatsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[external_file_formats]";
    public const string TableName = "external_file_formats";
    public const string ShortName = "eff";
    public const string Sql = """
        SELECT
          eff.[file_format_id],
          eff.[Name],
          eff.[format_type],
          eff.[field_terminator],
          eff.[string_delimiter],
          eff.[date_format],
          eff.[use_type_default],
          eff.[serde_method],
          eff.[row_terminator],
          eff.[Encoding],
          eff.[data_compression],
          eff.[first_row]
        FROM
          [sys].[external_file_formats] eff
        """;

    public const int FILEFORMATID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int FORMATTYPE_FIELD_ID = 2;
    public const int FIELDTERMINATOR_FIELD_ID = 3;
    public const int STRINGDELIMITER_FIELD_ID = 4;
    public const int DATEFORMAT_FIELD_ID = 5;
    public const int USETYPEDEFAULT_FIELD_ID = 6;
    public const int SERDEMETHOD_FIELD_ID = 7;
    public const int ROWTERMINATOR_FIELD_ID = 8;
    public const int ENCODING_FIELD_ID = 9;
    public const int DATACOMPRESSION_FIELD_ID = 10;
    public const int FIRSTROW_FIELD_ID = 11;


    public ExternalFileFormatsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ExternalFileFormatsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ExternalFileFormatsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int FileFormatId
    {
        get
        {
            return base.GetInt32(FILEFORMATID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public string FormatType
    {
        get
        {
            return base.GetString(FORMATTYPE_FIELD_ID);
        }
    }

    public string? FieldTerminator
    {
        get
        {
            return base.GetNullableString(FIELDTERMINATOR_FIELD_ID);
        }
    }

    public string? StringDelimiter
    {
        get
        {
            return base.GetNullableString(STRINGDELIMITER_FIELD_ID);
        }
    }

    public string? DateFormat
    {
        get
        {
            return base.GetNullableString(DATEFORMAT_FIELD_ID);
        }
    }

    public bool? UseTypeDefault
    {
        get
        {
            return base.GetNullableBoolean(USETYPEDEFAULT_FIELD_ID);
        }
    }

    public string? SerdeMethod
    {
        get
        {
            return base.GetNullableString(SERDEMETHOD_FIELD_ID);
        }
    }

    public string? RowTerminator
    {
        get
        {
            return base.GetNullableString(ROWTERMINATOR_FIELD_ID);
        }
    }

    public string? Encoding
    {
        get
        {
            return base.GetNullableString(ENCODING_FIELD_ID);
        }
    }

    public string? DataCompression
    {
        get
        {
            return base.GetNullableString(DATACOMPRESSION_FIELD_ID);
        }
    }

    public int? FirstRow
    {
        get
        {
            return base.GetNullableInt32(FIRSTROW_FIELD_ID);
        }
    }


    public Types.ExternalFileFormatsDataType ToDataObject()
    {
        return new Types.ExternalFileFormatsDataType(FileFormatId,
            Name,
            FormatType,
            FieldTerminator,
            StringDelimiter,
            DateFormat,
            UseTypeDefault,
            SerdeMethod,
            RowTerminator,
            Encoding,
            DataCompression,
            FirstRow);
    }

    public List<Types.ExternalFileFormatsDataType> ToList()
    {
        var list = new List<Types.ExternalFileFormatsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

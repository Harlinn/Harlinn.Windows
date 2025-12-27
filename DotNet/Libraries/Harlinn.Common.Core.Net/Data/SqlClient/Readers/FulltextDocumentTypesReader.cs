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

public class FulltextDocumentTypesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[fulltext_document_types]";
    public const string TableName = "fulltext_document_types";
    public const string ShortName = "fdt";
    public const string Sql = """
        SELECT
          fdt.[document_type],
          fdt.[class_id],
          fdt.[Path],
          fdt.[Version],
          fdt.[Manufacturer]
        FROM
          [sys].[fulltext_document_types] fdt
        """;

    public const int DOCUMENTTYPE_FIELD_ID = 0;
    public const int CLASSID_FIELD_ID = 1;
    public const int PATH_FIELD_ID = 2;
    public const int VERSION_FIELD_ID = 3;
    public const int MANUFACTURER_FIELD_ID = 4;


    public FulltextDocumentTypesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FulltextDocumentTypesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FulltextDocumentTypesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string DocumentType
    {
        get
        {
            return base.GetString(DOCUMENTTYPE_FIELD_ID);
        }
    }

    public Guid ClassId
    {
        get
        {
            return base.GetGuid(CLASSID_FIELD_ID);
        }
    }

    public string? Path
    {
        get
        {
            return base.GetNullableString(PATH_FIELD_ID);
        }
    }

    public string Version
    {
        get
        {
            return base.GetString(VERSION_FIELD_ID);
        }
    }

    public string? Manufacturer
    {
        get
        {
            return base.GetNullableString(MANUFACTURER_FIELD_ID);
        }
    }


    public Types.FulltextDocumentTypesDataType ToDataObject()
    {
        return new Types.FulltextDocumentTypesDataType(DocumentType,
            ClassId,
            Path,
            Version,
            Manufacturer);
    }

    public List<Types.FulltextDocumentTypesDataType> ToList()
    {
        var list = new List<Types.FulltextDocumentTypesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

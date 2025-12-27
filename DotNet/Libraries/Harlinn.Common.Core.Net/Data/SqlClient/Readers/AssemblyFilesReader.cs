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

public class AssemblyFilesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[assembly_files]";
    public const string TableName = "assembly_files";
    public const string ShortName = "af";
    public const string Sql = """
        SELECT
          af.[assembly_id],
          af.[Name],
          af.[file_id],
          af.[Content]
        FROM
          [sys].[assembly_files] af
        """;

    public const int ASSEMBLYID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int FILEID_FIELD_ID = 2;
    public const int CONTENT_FIELD_ID = 3;


    public AssemblyFilesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public AssemblyFilesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public AssemblyFilesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int AssemblyId
    {
        get
        {
            return base.GetInt32(ASSEMBLYID_FIELD_ID);
        }
    }

    public string? Name
    {
        get
        {
            return base.GetNullableString(NAME_FIELD_ID);
        }
    }

    public int FileId
    {
        get
        {
            return base.GetInt32(FILEID_FIELD_ID);
        }
    }

    public byte[]? Content
    {
        get
        {
            return base.GetNullableBinary(CONTENT_FIELD_ID);
        }
    }


    public Types.AssemblyFilesDataType ToDataObject()
    {
        return new Types.AssemblyFilesDataType(AssemblyId,
            Name,
            FileId,
            Content);
    }

    public List<Types.AssemblyFilesDataType> ToList()
    {
        var list = new List<Types.AssemblyFilesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

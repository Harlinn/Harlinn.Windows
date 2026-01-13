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

public class ExternalLibrariesInstalledReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[external_libraries_installed]";
    public const string TableName = "external_libraries_installed";
    public const string ShortName = "eli";
    public const string Sql = """
        SELECT
          eli.[db_id],
          eli.[principal_id],
          eli.[language_id],
          eli.[external_library_id],
          eli.[Name],
          eli.[Mdversion]
        FROM
          [sys].[external_libraries_installed] eli
        """;

    public const int DBID_FIELD_ID = 0;
    public const int PRINCIPALID_FIELD_ID = 1;
    public const int LANGUAGEID_FIELD_ID = 2;
    public const int EXTERNALLIBRARYID_FIELD_ID = 3;
    public const int NAME_FIELD_ID = 4;
    public const int MDVERSION_FIELD_ID = 5;


    public ExternalLibrariesInstalledReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ExternalLibrariesInstalledReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ExternalLibrariesInstalledReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DbId
    {
        get
        {
            return base.GetInt32(DBID_FIELD_ID);
        }
    }

    public int PrincipalId
    {
        get
        {
            return base.GetInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public int LanguageId
    {
        get
        {
            return base.GetInt32(LANGUAGEID_FIELD_ID);
        }
    }

    public int ExternalLibraryId
    {
        get
        {
            return base.GetInt32(EXTERNALLIBRARYID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public byte[] Mdversion
    {
        get
        {
            return base.GetBinary(MDVERSION_FIELD_ID);
        }
    }


    public Types.ExternalLibrariesInstalledDataType ToDataObject()
    {
        return new Types.ExternalLibrariesInstalledDataType(DbId,
            PrincipalId,
            LanguageId,
            ExternalLibraryId,
            Name,
            Mdversion);
    }

    public List<Types.ExternalLibrariesInstalledDataType> ToList()
    {
        var list = new List<Types.ExternalLibrariesInstalledDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

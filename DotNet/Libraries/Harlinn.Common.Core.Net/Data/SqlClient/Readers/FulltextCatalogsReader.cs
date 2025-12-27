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

public class FulltextCatalogsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[fulltext_catalogs]";
    public const string TableName = "fulltext_catalogs";
    public const string ShortName = "fc";
    public const string Sql = """
        SELECT
          fc.[fulltext_catalog_id],
          fc.[Name],
          fc.[Path],
          fc.[is_default],
          fc.[is_accent_sensitivity_on],
          fc.[data_space_id],
          fc.[file_id],
          fc.[principal_id],
          fc.[is_importing]
        FROM
          [sys].[fulltext_catalogs] fc
        """;

    public const int FULLTEXTCATALOGID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int PATH_FIELD_ID = 2;
    public const int ISDEFAULT_FIELD_ID = 3;
    public const int ISACCENTSENSITIVITYON_FIELD_ID = 4;
    public const int DATASPACEID_FIELD_ID = 5;
    public const int FILEID_FIELD_ID = 6;
    public const int PRINCIPALID_FIELD_ID = 7;
    public const int ISIMPORTING_FIELD_ID = 8;


    public FulltextCatalogsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FulltextCatalogsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FulltextCatalogsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int FulltextCatalogId
    {
        get
        {
            return base.GetInt32(FULLTEXTCATALOGID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public string? Path
    {
        get
        {
            return base.GetNullableString(PATH_FIELD_ID);
        }
    }

    public bool IsDefault
    {
        get
        {
            return base.GetBoolean(ISDEFAULT_FIELD_ID);
        }
    }

    public bool IsAccentSensitivityOn
    {
        get
        {
            return base.GetBoolean(ISACCENTSENSITIVITYON_FIELD_ID);
        }
    }

    public int? DataSpaceId
    {
        get
        {
            return base.GetNullableInt32(DATASPACEID_FIELD_ID);
        }
    }

    public int? FileId
    {
        get
        {
            return base.GetNullableInt32(FILEID_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public bool IsImporting
    {
        get
        {
            return base.GetBoolean(ISIMPORTING_FIELD_ID);
        }
    }


    public Types.FulltextCatalogsDataType ToDataObject()
    {
        return new Types.FulltextCatalogsDataType(FulltextCatalogId,
            Name,
            Path,
            IsDefault,
            IsAccentSensitivityOn,
            DataSpaceId,
            FileId,
            PrincipalId,
            IsImporting);
    }

    public List<Types.FulltextCatalogsDataType> ToList()
    {
        var list = new List<Types.FulltextCatalogsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

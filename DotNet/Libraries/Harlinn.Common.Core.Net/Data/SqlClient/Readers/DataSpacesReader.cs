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

public class DataSpacesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[data_spaces]";
    public const string TableName = "data_spaces";
    public const string ShortName = "ds";
    public const string Sql = """
        SELECT
          ds.[Name],
          ds.[data_space_id],
          ds.[Type],
          ds.[type_desc],
          ds.[is_default],
          ds.[is_system]
        FROM
          [sys].[data_spaces] ds
        """;

    public const int NAME_FIELD_ID = 0;
    public const int DATASPACEID_FIELD_ID = 1;
    public const int TYPE_FIELD_ID = 2;
    public const int TYPEDESC_FIELD_ID = 3;
    public const int ISDEFAULT_FIELD_ID = 4;
    public const int ISSYSTEM_FIELD_ID = 5;


    public DataSpacesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DataSpacesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DataSpacesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int DataSpaceId
    {
        get
        {
            return base.GetInt32(DATASPACEID_FIELD_ID);
        }
    }

    public string Type
    {
        get
        {
            return base.GetString(TYPE_FIELD_ID);
        }
    }

    public string? TypeDesc
    {
        get
        {
            return base.GetNullableString(TYPEDESC_FIELD_ID);
        }
    }

    public bool IsDefault
    {
        get
        {
            return base.GetBoolean(ISDEFAULT_FIELD_ID);
        }
    }

    public bool? IsSystem
    {
        get
        {
            return base.GetNullableBoolean(ISSYSTEM_FIELD_ID);
        }
    }


    public Types.DataSpacesDataType ToDataObject()
    {
        return new Types.DataSpacesDataType(Name,
            DataSpaceId,
            Type,
            TypeDesc,
            IsDefault,
            IsSystem);
    }

    public List<Types.DataSpacesDataType> ToList()
    {
        var list = new List<Types.DataSpacesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

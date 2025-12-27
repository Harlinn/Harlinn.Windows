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

public class FilegroupsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[filegroups]";
    public const string TableName = "filegroups";
    public const string ShortName = "f0";
    public const string Sql = """
        SELECT
          f0.[Name],
          f0.[data_space_id],
          f0.[Type],
          f0.[type_desc],
          f0.[is_default],
          f0.[is_system],
          f0.[filegroup_guid],
          f0.[log_filegroup_id],
          f0.[is_read_only],
          f0.[is_autogrow_all_files]
        FROM
          [sys].[filegroups] f0
        """;

    public const int NAME_FIELD_ID = 0;
    public const int DATASPACEID_FIELD_ID = 1;
    public const int TYPE_FIELD_ID = 2;
    public const int TYPEDESC_FIELD_ID = 3;
    public const int ISDEFAULT_FIELD_ID = 4;
    public const int ISSYSTEM_FIELD_ID = 5;
    public const int FILEGROUPGUID_FIELD_ID = 6;
    public const int LOGFILEGROUPID_FIELD_ID = 7;
    public const int ISREADONLY_FIELD_ID = 8;
    public const int ISAUTOGROWALLFILES_FIELD_ID = 9;


    public FilegroupsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FilegroupsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FilegroupsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public bool? IsDefault
    {
        get
        {
            return base.GetNullableBoolean(ISDEFAULT_FIELD_ID);
        }
    }

    public bool? IsSystem
    {
        get
        {
            return base.GetNullableBoolean(ISSYSTEM_FIELD_ID);
        }
    }

    public Guid? FilegroupGuid
    {
        get
        {
            return base.GetNullableGuid(FILEGROUPGUID_FIELD_ID);
        }
    }

    public int? LogFilegroupId
    {
        get
        {
            return base.GetNullableInt32(LOGFILEGROUPID_FIELD_ID);
        }
    }

    public bool? IsReadOnly
    {
        get
        {
            return base.GetNullableBoolean(ISREADONLY_FIELD_ID);
        }
    }

    public bool? IsAutogrowAllFiles
    {
        get
        {
            return base.GetNullableBoolean(ISAUTOGROWALLFILES_FIELD_ID);
        }
    }


    public Types.FilegroupsDataType ToDataObject()
    {
        return new Types.FilegroupsDataType(Name,
            DataSpaceId,
            Type,
            TypeDesc,
            IsDefault,
            IsSystem,
            FilegroupGuid,
            LogFilegroupId,
            IsReadOnly,
            IsAutogrowAllFiles);
    }

    public List<Types.FilegroupsDataType> ToList()
    {
        var list = new List<Types.FilegroupsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

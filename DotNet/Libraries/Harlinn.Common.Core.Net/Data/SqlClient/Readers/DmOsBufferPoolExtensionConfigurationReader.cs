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

public class DmOsBufferPoolExtensionConfigurationReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_buffer_pool_extension_configuration]";
    public const string TableName = "dm_os_buffer_pool_extension_configuration";
    public const string ShortName = "dobpec";
    public const string Sql = """
        SELECT
          dobpec.[Path],
          dobpec.[file_id],
          dobpec.[State],
          dobpec.[state_description],
          dobpec.[current_size_in_kb]
        FROM
          [sys].[dm_os_buffer_pool_extension_configuration] dobpec
        """;

    public const int PATH_FIELD_ID = 0;
    public const int FILEID_FIELD_ID = 1;
    public const int STATE_FIELD_ID = 2;
    public const int STATEDESCRIPTION_FIELD_ID = 3;
    public const int CURRENTSIZEINKB_FIELD_ID = 4;


    public DmOsBufferPoolExtensionConfigurationReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsBufferPoolExtensionConfigurationReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsBufferPoolExtensionConfigurationReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? Path
    {
        get
        {
            return base.GetNullableString(PATH_FIELD_ID);
        }
    }

    public int? FileId
    {
        get
        {
            return base.GetNullableInt32(FILEID_FIELD_ID);
        }
    }

    public int? State
    {
        get
        {
            return base.GetNullableInt32(STATE_FIELD_ID);
        }
    }

    public string StateDescription
    {
        get
        {
            return base.GetString(STATEDESCRIPTION_FIELD_ID);
        }
    }

    public long? CurrentSizeInKb
    {
        get
        {
            return base.GetNullableInt64(CURRENTSIZEINKB_FIELD_ID);
        }
    }


    public Types.DmOsBufferPoolExtensionConfigurationDataType ToDataObject()
    {
        return new Types.DmOsBufferPoolExtensionConfigurationDataType(Path,
            FileId,
            State,
            StateDescription,
            CurrentSizeInKb);
    }

    public List<Types.DmOsBufferPoolExtensionConfigurationDataType> ToList()
    {
        var list = new List<Types.DmOsBufferPoolExtensionConfigurationDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

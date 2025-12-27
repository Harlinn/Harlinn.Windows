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

public class DmOsServerDiagnosticsLogConfigurationsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_server_diagnostics_log_configurations]";
    public const string TableName = "dm_os_server_diagnostics_log_configurations";
    public const string ShortName = "dosdlc";
    public const string Sql = """
        SELECT
          dosdlc.[is_enabled],
          dosdlc.[Path],
          dosdlc.[max_size],
          dosdlc.[max_files]
        FROM
          [sys].[dm_os_server_diagnostics_log_configurations] dosdlc
        """;

    public const int ISENABLED_FIELD_ID = 0;
    public const int PATH_FIELD_ID = 1;
    public const int MAXSIZE_FIELD_ID = 2;
    public const int MAXFILES_FIELD_ID = 3;


    public DmOsServerDiagnosticsLogConfigurationsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsServerDiagnosticsLogConfigurationsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsServerDiagnosticsLogConfigurationsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? IsEnabled
    {
        get
        {
            return base.GetNullableInt32(ISENABLED_FIELD_ID);
        }
    }

    public string Path
    {
        get
        {
            return base.GetString(PATH_FIELD_ID);
        }
    }

    public int? MaxSize
    {
        get
        {
            return base.GetNullableInt32(MAXSIZE_FIELD_ID);
        }
    }

    public int? MaxFiles
    {
        get
        {
            return base.GetNullableInt32(MAXFILES_FIELD_ID);
        }
    }


    public Types.DmOsServerDiagnosticsLogConfigurationsDataType ToDataObject()
    {
        return new Types.DmOsServerDiagnosticsLogConfigurationsDataType(IsEnabled,
            Path,
            MaxSize,
            MaxFiles);
    }

    public List<Types.DmOsServerDiagnosticsLogConfigurationsDataType> ToList()
    {
        var list = new List<Types.DmOsServerDiagnosticsLogConfigurationsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

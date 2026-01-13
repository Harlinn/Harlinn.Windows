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

public class DmXeSessionTargetsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_xe_session_targets]";
    public const string TableName = "dm_xe_session_targets";
    public const string ShortName = "dxst";
    public const string Sql = """
        SELECT
          dxst.[event_session_address],
          dxst.[target_name],
          dxst.[target_package_guid],
          dxst.[execution_count],
          dxst.[execution_duration_ms],
          dxst.[target_data],
          dxst.[bytes_written]
        FROM
          [sys].[dm_xe_session_targets] dxst
        """;

    public const int EVENTSESSIONADDRESS_FIELD_ID = 0;
    public const int TARGETNAME_FIELD_ID = 1;
    public const int TARGETPACKAGEGUID_FIELD_ID = 2;
    public const int EXECUTIONCOUNT_FIELD_ID = 3;
    public const int EXECUTIONDURATIONMS_FIELD_ID = 4;
    public const int TARGETDATA_FIELD_ID = 5;
    public const int BYTESWRITTEN_FIELD_ID = 6;


    public DmXeSessionTargetsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmXeSessionTargetsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmXeSessionTargetsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] EventSessionAddress
    {
        get
        {
            return base.GetBinary(EVENTSESSIONADDRESS_FIELD_ID);
        }
    }

    public string TargetName
    {
        get
        {
            return base.GetString(TARGETNAME_FIELD_ID);
        }
    }

    public Guid TargetPackageGuid
    {
        get
        {
            return base.GetGuid(TARGETPACKAGEGUID_FIELD_ID);
        }
    }

    public long ExecutionCount
    {
        get
        {
            return base.GetInt64(EXECUTIONCOUNT_FIELD_ID);
        }
    }

    public long ExecutionDurationMs
    {
        get
        {
            return base.GetInt64(EXECUTIONDURATIONMS_FIELD_ID);
        }
    }

    public string? TargetData
    {
        get
        {
            return base.GetNullableString(TARGETDATA_FIELD_ID);
        }
    }

    public long BytesWritten
    {
        get
        {
            return base.GetInt64(BYTESWRITTEN_FIELD_ID);
        }
    }


    public Types.DmXeSessionTargetsDataType ToDataObject()
    {
        return new Types.DmXeSessionTargetsDataType(EventSessionAddress,
            TargetName,
            TargetPackageGuid,
            ExecutionCount,
            ExecutionDurationMs,
            TargetData,
            BytesWritten);
    }

    public List<Types.DmXeSessionTargetsDataType> ToList()
    {
        var list = new List<Types.DmXeSessionTargetsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

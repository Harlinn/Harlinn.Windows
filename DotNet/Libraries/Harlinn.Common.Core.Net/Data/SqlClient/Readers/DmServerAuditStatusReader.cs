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

public class DmServerAuditStatusReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_server_audit_status]";
    public const string TableName = "dm_server_audit_status";
    public const string ShortName = "dsas";
    public const string Sql = """
        SELECT
          dsas.[audit_id],
          dsas.[Name],
          dsas.[Status],
          dsas.[status_desc],
          dsas.[status_time],
          dsas.[event_session_address],
          dsas.[audit_file_path],
          dsas.[audit_file_size]
        FROM
          [sys].[dm_server_audit_status] dsas
        """;

    public const int AUDITID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int STATUS_FIELD_ID = 2;
    public const int STATUSDESC_FIELD_ID = 3;
    public const int STATUSTIME_FIELD_ID = 4;
    public const int EVENTSESSIONADDRESS_FIELD_ID = 5;
    public const int AUDITFILEPATH_FIELD_ID = 6;
    public const int AUDITFILESIZE_FIELD_ID = 7;


    public DmServerAuditStatusReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmServerAuditStatusReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmServerAuditStatusReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int AuditId
    {
        get
        {
            return base.GetInt32(AUDITID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public short Status
    {
        get
        {
            return base.GetInt16(STATUS_FIELD_ID);
        }
    }

    public string StatusDesc
    {
        get
        {
            return base.GetString(STATUSDESC_FIELD_ID);
        }
    }

    public DateTime StatusTime
    {
        get
        {
            return base.GetDateTime(STATUSTIME_FIELD_ID);
        }
    }

    public byte[]? EventSessionAddress
    {
        get
        {
            return base.GetNullableBinary(EVENTSESSIONADDRESS_FIELD_ID);
        }
    }

    public string? AuditFilePath
    {
        get
        {
            return base.GetNullableString(AUDITFILEPATH_FIELD_ID);
        }
    }

    public long? AuditFileSize
    {
        get
        {
            return base.GetNullableInt64(AUDITFILESIZE_FIELD_ID);
        }
    }


    public Types.DmServerAuditStatusDataType ToDataObject()
    {
        return new Types.DmServerAuditStatusDataType(AuditId,
            Name,
            Status,
            StatusDesc,
            StatusTime,
            EventSessionAddress,
            AuditFilePath,
            AuditFileSize);
    }

    public List<Types.DmServerAuditStatusDataType> ToList()
    {
        var list = new List<Types.DmServerAuditStatusDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

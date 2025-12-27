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

public class ServerAuditSpecificationsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[server_audit_specifications]";
    public const string TableName = "server_audit_specifications";
    public const string ShortName = "sas";
    public const string Sql = """
        SELECT
          sas.[server_specification_id],
          sas.[Name],
          sas.[create_date],
          sas.[modify_date],
          sas.[audit_guid],
          sas.[is_state_enabled]
        FROM
          [sys].[server_audit_specifications] sas
        """;

    public const int SERVERSPECIFICATIONID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int CREATEDATE_FIELD_ID = 2;
    public const int MODIFYDATE_FIELD_ID = 3;
    public const int AUDITGUID_FIELD_ID = 4;
    public const int ISSTATEENABLED_FIELD_ID = 5;


    public ServerAuditSpecificationsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServerAuditSpecificationsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServerAuditSpecificationsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int ServerSpecificationId
    {
        get
        {
            return base.GetInt32(SERVERSPECIFICATIONID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public DateTime CreateDate
    {
        get
        {
            return base.GetDateTime(CREATEDATE_FIELD_ID);
        }
    }

    public DateTime ModifyDate
    {
        get
        {
            return base.GetDateTime(MODIFYDATE_FIELD_ID);
        }
    }

    public Guid? AuditGuid
    {
        get
        {
            return base.GetNullableGuid(AUDITGUID_FIELD_ID);
        }
    }

    public bool? IsStateEnabled
    {
        get
        {
            return base.GetNullableBoolean(ISSTATEENABLED_FIELD_ID);
        }
    }


    public Types.ServerAuditSpecificationsDataType ToDataObject()
    {
        return new Types.ServerAuditSpecificationsDataType(ServerSpecificationId,
            Name,
            CreateDate,
            ModifyDate,
            AuditGuid,
            IsStateEnabled);
    }

    public List<Types.ServerAuditSpecificationsDataType> ToList()
    {
        var list = new List<Types.ServerAuditSpecificationsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

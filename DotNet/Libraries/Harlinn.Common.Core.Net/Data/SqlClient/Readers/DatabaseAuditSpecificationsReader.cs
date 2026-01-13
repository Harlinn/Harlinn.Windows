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

public class DatabaseAuditSpecificationsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[database_audit_specifications]";
    public const string TableName = "database_audit_specifications";
    public const string ShortName = "das";
    public const string Sql = """
        SELECT
          das.[database_specification_id],
          das.[Name],
          das.[create_date],
          das.[modify_date],
          das.[audit_guid],
          das.[is_state_enabled]
        FROM
          [sys].[database_audit_specifications] das
        """;

    public const int DATABASESPECIFICATIONID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int CREATEDATE_FIELD_ID = 2;
    public const int MODIFYDATE_FIELD_ID = 3;
    public const int AUDITGUID_FIELD_ID = 4;
    public const int ISSTATEENABLED_FIELD_ID = 5;


    public DatabaseAuditSpecificationsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DatabaseAuditSpecificationsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DatabaseAuditSpecificationsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int DatabaseSpecificationId
    {
        get
        {
            return base.GetInt32(DATABASESPECIFICATIONID_FIELD_ID);
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


    public Types.DatabaseAuditSpecificationsDataType ToDataObject()
    {
        return new Types.DatabaseAuditSpecificationsDataType(DatabaseSpecificationId,
            Name,
            CreateDate,
            ModifyDate,
            AuditGuid,
            IsStateEnabled);
    }

    public List<Types.DatabaseAuditSpecificationsDataType> ToList()
    {
        var list = new List<Types.DatabaseAuditSpecificationsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

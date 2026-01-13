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

public class ServerAuditsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[server_audits]";
    public const string TableName = "server_audits";
    public const string ShortName = "sa";
    public const string Sql = """
        SELECT
          sa.[audit_id],
          sa.[Name],
          sa.[audit_guid],
          sa.[create_date],
          sa.[modify_date],
          sa.[principal_id],
          sa.[Type],
          sa.[type_desc],
          sa.[on_failure],
          sa.[on_failure_desc],
          sa.[is_state_enabled],
          sa.[queue_delay],
          sa.[Predicate]
        FROM
          [sys].[server_audits] sa
        """;

    public const int AUDITID_FIELD_ID = 0;
    public const int NAME_FIELD_ID = 1;
    public const int AUDITGUID_FIELD_ID = 2;
    public const int CREATEDATE_FIELD_ID = 3;
    public const int MODIFYDATE_FIELD_ID = 4;
    public const int PRINCIPALID_FIELD_ID = 5;
    public const int TYPE_FIELD_ID = 6;
    public const int TYPEDESC_FIELD_ID = 7;
    public const int ONFAILURE_FIELD_ID = 8;
    public const int ONFAILUREDESC_FIELD_ID = 9;
    public const int ISSTATEENABLED_FIELD_ID = 10;
    public const int QUEUEDELAY_FIELD_ID = 11;
    public const int PREDICATE_FIELD_ID = 12;


    public ServerAuditsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServerAuditsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServerAuditsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public Guid? AuditGuid
    {
        get
        {
            return base.GetNullableGuid(AUDITGUID_FIELD_ID);
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

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
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

    public byte? OnFailure
    {
        get
        {
            return base.GetNullableByte(ONFAILURE_FIELD_ID);
        }
    }

    public string? OnFailureDesc
    {
        get
        {
            return base.GetNullableString(ONFAILUREDESC_FIELD_ID);
        }
    }

    public bool? IsStateEnabled
    {
        get
        {
            return base.GetNullableBoolean(ISSTATEENABLED_FIELD_ID);
        }
    }

    public int? QueueDelay
    {
        get
        {
            return base.GetNullableInt32(QUEUEDELAY_FIELD_ID);
        }
    }

    public string? Predicate
    {
        get
        {
            return base.GetNullableString(PREDICATE_FIELD_ID);
        }
    }


    public Types.ServerAuditsDataType ToDataObject()
    {
        return new Types.ServerAuditsDataType(AuditId,
            Name,
            AuditGuid,
            CreateDate,
            ModifyDate,
            PrincipalId,
            Type,
            TypeDesc,
            OnFailure,
            OnFailureDesc,
            IsStateEnabled,
            QueueDelay,
            Predicate);
    }

    public List<Types.ServerAuditsDataType> ToList()
    {
        var list = new List<Types.ServerAuditsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class ServerEventNotificationsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[server_event_notifications]";
    public const string TableName = "server_event_notifications";
    public const string ShortName = "sen";
    public const string Sql = """
        SELECT
          sen.[Name],
          sen.[object_id],
          sen.[parent_class],
          sen.[parent_class_desc],
          sen.[parent_id],
          sen.[create_date],
          sen.[modify_date],
          sen.[service_name],
          sen.[broker_instance],
          sen.[creator_sid],
          sen.[principal_id]
        FROM
          [sys].[server_event_notifications] sen
        """;

    public const int NAME_FIELD_ID = 0;
    public const int OBJECTID_FIELD_ID = 1;
    public const int PARENTCLASS_FIELD_ID = 2;
    public const int PARENTCLASSDESC_FIELD_ID = 3;
    public const int PARENTID_FIELD_ID = 4;
    public const int CREATEDATE_FIELD_ID = 5;
    public const int MODIFYDATE_FIELD_ID = 6;
    public const int SERVICENAME_FIELD_ID = 7;
    public const int BROKERINSTANCE_FIELD_ID = 8;
    public const int CREATORSID_FIELD_ID = 9;
    public const int PRINCIPALID_FIELD_ID = 10;


    public ServerEventNotificationsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServerEventNotificationsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServerEventNotificationsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public byte ParentClass
    {
        get
        {
            return base.GetByte(PARENTCLASS_FIELD_ID);
        }
    }

    public string? ParentClassDesc
    {
        get
        {
            return base.GetNullableString(PARENTCLASSDESC_FIELD_ID);
        }
    }

    public int ParentId
    {
        get
        {
            return base.GetInt32(PARENTID_FIELD_ID);
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

    public string? ServiceName
    {
        get
        {
            return base.GetNullableString(SERVICENAME_FIELD_ID);
        }
    }

    public string? BrokerInstance
    {
        get
        {
            return base.GetNullableString(BROKERINSTANCE_FIELD_ID);
        }
    }

    public byte[]? CreatorSid
    {
        get
        {
            return base.GetNullableBinary(CREATORSID_FIELD_ID);
        }
    }

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }


    public Types.ServerEventNotificationsDataType ToDataObject()
    {
        return new Types.ServerEventNotificationsDataType(Name,
            ObjectId,
            ParentClass,
            ParentClassDesc,
            ParentId,
            CreateDate,
            ModifyDate,
            ServiceName,
            BrokerInstance,
            CreatorSid,
            PrincipalId);
    }

    public List<Types.ServerEventNotificationsDataType> ToList()
    {
        var list = new List<Types.ServerEventNotificationsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

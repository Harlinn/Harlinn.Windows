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

public class ServiceQueuesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[service_queues]";
    public const string TableName = "service_queues";
    public const string ShortName = "sq";
    public const string Sql = """
        SELECT
          sq.[Name],
          sq.[object_id],
          sq.[principal_id],
          sq.[schema_id],
          sq.[parent_object_id],
          sq.[Type],
          sq.[type_desc],
          sq.[create_date],
          sq.[modify_date],
          sq.[is_ms_shipped],
          sq.[is_published],
          sq.[is_schema_published],
          sq.[max_readers],
          sq.[activation_procedure],
          sq.[execute_as_principal_id],
          sq.[is_activation_enabled],
          sq.[is_receive_enabled],
          sq.[is_enqueue_enabled],
          sq.[is_retention_enabled],
          sq.[is_poison_message_handling_enabled]
        FROM
          [sys].[service_queues] sq
        """;

    public const int NAME_FIELD_ID = 0;
    public const int OBJECTID_FIELD_ID = 1;
    public const int PRINCIPALID_FIELD_ID = 2;
    public const int SCHEMAID_FIELD_ID = 3;
    public const int PARENTOBJECTID_FIELD_ID = 4;
    public const int TYPE_FIELD_ID = 5;
    public const int TYPEDESC_FIELD_ID = 6;
    public const int CREATEDATE_FIELD_ID = 7;
    public const int MODIFYDATE_FIELD_ID = 8;
    public const int ISMSSHIPPED_FIELD_ID = 9;
    public const int ISPUBLISHED_FIELD_ID = 10;
    public const int ISSCHEMAPUBLISHED_FIELD_ID = 11;
    public const int MAXREADERS_FIELD_ID = 12;
    public const int ACTIVATIONPROCEDURE_FIELD_ID = 13;
    public const int EXECUTEASPRINCIPALID_FIELD_ID = 14;
    public const int ISACTIVATIONENABLED_FIELD_ID = 15;
    public const int ISRECEIVEENABLED_FIELD_ID = 16;
    public const int ISENQUEUEENABLED_FIELD_ID = 17;
    public const int ISRETENTIONENABLED_FIELD_ID = 18;
    public const int ISPOISONMESSAGEHANDLINGENABLED_FIELD_ID = 19;


    public ServiceQueuesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ServiceQueuesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ServiceQueuesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
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

    public int? PrincipalId
    {
        get
        {
            return base.GetNullableInt32(PRINCIPALID_FIELD_ID);
        }
    }

    public int SchemaId
    {
        get
        {
            return base.GetInt32(SCHEMAID_FIELD_ID);
        }
    }

    public int ParentObjectId
    {
        get
        {
            return base.GetInt32(PARENTOBJECTID_FIELD_ID);
        }
    }

    public string? Type
    {
        get
        {
            return base.GetNullableString(TYPE_FIELD_ID);
        }
    }

    public string? TypeDesc
    {
        get
        {
            return base.GetNullableString(TYPEDESC_FIELD_ID);
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

    public bool IsMsShipped
    {
        get
        {
            return base.GetBoolean(ISMSSHIPPED_FIELD_ID);
        }
    }

    public bool IsPublished
    {
        get
        {
            return base.GetBoolean(ISPUBLISHED_FIELD_ID);
        }
    }

    public bool IsSchemaPublished
    {
        get
        {
            return base.GetBoolean(ISSCHEMAPUBLISHED_FIELD_ID);
        }
    }

    public short? MaxReaders
    {
        get
        {
            return base.GetNullableInt16(MAXREADERS_FIELD_ID);
        }
    }

    public string? ActivationProcedure
    {
        get
        {
            return base.GetNullableString(ACTIVATIONPROCEDURE_FIELD_ID);
        }
    }

    public int? ExecuteAsPrincipalId
    {
        get
        {
            return base.GetNullableInt32(EXECUTEASPRINCIPALID_FIELD_ID);
        }
    }

    public bool IsActivationEnabled
    {
        get
        {
            return base.GetBoolean(ISACTIVATIONENABLED_FIELD_ID);
        }
    }

    public bool IsReceiveEnabled
    {
        get
        {
            return base.GetBoolean(ISRECEIVEENABLED_FIELD_ID);
        }
    }

    public bool IsEnqueueEnabled
    {
        get
        {
            return base.GetBoolean(ISENQUEUEENABLED_FIELD_ID);
        }
    }

    public bool IsRetentionEnabled
    {
        get
        {
            return base.GetBoolean(ISRETENTIONENABLED_FIELD_ID);
        }
    }

    public bool? IsPoisonMessageHandlingEnabled
    {
        get
        {
            return base.GetNullableBoolean(ISPOISONMESSAGEHANDLINGENABLED_FIELD_ID);
        }
    }


    public Types.ServiceQueuesDataType ToDataObject()
    {
        return new Types.ServiceQueuesDataType(Name,
            ObjectId,
            PrincipalId,
            SchemaId,
            ParentObjectId,
            Type,
            TypeDesc,
            CreateDate,
            ModifyDate,
            IsMsShipped,
            IsPublished,
            IsSchemaPublished,
            MaxReaders,
            ActivationProcedure,
            ExecuteAsPrincipalId,
            IsActivationEnabled,
            IsReceiveEnabled,
            IsEnqueueEnabled,
            IsRetentionEnabled,
            IsPoisonMessageHandlingEnabled);
    }

    public List<Types.ServiceQueuesDataType> ToList()
    {
        var list = new List<Types.ServiceQueuesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

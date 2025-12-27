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

public class ConversationGroupsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[conversation_groups]";
    public const string TableName = "conversation_groups";
    public const string ShortName = "cg";
    public const string Sql = """
        SELECT
          cg.[conversation_group_id],
          cg.[service_id],
          cg.[is_system]
        FROM
          [sys].[conversation_groups] cg
        """;

    public const int CONVERSATIONGROUPID_FIELD_ID = 0;
    public const int SERVICEID_FIELD_ID = 1;
    public const int ISSYSTEM_FIELD_ID = 2;


    public ConversationGroupsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public ConversationGroupsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public ConversationGroupsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid ConversationGroupId
    {
        get
        {
            return base.GetGuid(CONVERSATIONGROUPID_FIELD_ID);
        }
    }

    public int ServiceId
    {
        get
        {
            return base.GetInt32(SERVICEID_FIELD_ID);
        }
    }

    public bool? IsSystem
    {
        get
        {
            return base.GetNullableBoolean(ISSYSTEM_FIELD_ID);
        }
    }


    public Types.ConversationGroupsDataType ToDataObject()
    {
        return new Types.ConversationGroupsDataType(ConversationGroupId,
            ServiceId,
            IsSystem);
    }

    public List<Types.ConversationGroupsDataType> ToList()
    {
        var list = new List<Types.ConversationGroupsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

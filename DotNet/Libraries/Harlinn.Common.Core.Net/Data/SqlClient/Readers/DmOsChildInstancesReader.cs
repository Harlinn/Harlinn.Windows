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

public class DmOsChildInstancesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_child_instances]";
    public const string TableName = "dm_os_child_instances";
    public const string ShortName = "doci";
    public const string Sql = """
        SELECT
          doci.[owning_principal_name],
          doci.[owning_principal_sid],
          doci.[owning_principal_sid_binary],
          doci.[instance_name],
          doci.[instance_pipe_name],
          doci.[OS_process_id],
          doci.[OS_process_creation_date],
          doci.[heart_beat]
        FROM
          [sys].[dm_os_child_instances] doci
        """;

    public const int OWNINGPRINCIPALNAME_FIELD_ID = 0;
    public const int OWNINGPRINCIPALSID_FIELD_ID = 1;
    public const int OWNINGPRINCIPALSIDBINARY_FIELD_ID = 2;
    public const int INSTANCENAME_FIELD_ID = 3;
    public const int INSTANCEPIPENAME_FIELD_ID = 4;
    public const int OSPROCESSID_FIELD_ID = 5;
    public const int OSPROCESSCREATIONDATE_FIELD_ID = 6;
    public const int HEARTBEAT_FIELD_ID = 7;


    public DmOsChildInstancesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsChildInstancesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsChildInstancesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string? OwningPrincipalName
    {
        get
        {
            return base.GetNullableString(OWNINGPRINCIPALNAME_FIELD_ID);
        }
    }

    public string? OwningPrincipalSid
    {
        get
        {
            return base.GetNullableString(OWNINGPRINCIPALSID_FIELD_ID);
        }
    }

    public byte[]? OwningPrincipalSidBinary
    {
        get
        {
            return base.GetNullableBinary(OWNINGPRINCIPALSIDBINARY_FIELD_ID);
        }
    }

    public string? InstanceName
    {
        get
        {
            return base.GetNullableString(INSTANCENAME_FIELD_ID);
        }
    }

    public string? InstancePipeName
    {
        get
        {
            return base.GetNullableString(INSTANCEPIPENAME_FIELD_ID);
        }
    }

    public int? OsProcessId
    {
        get
        {
            return base.GetNullableInt32(OSPROCESSID_FIELD_ID);
        }
    }

    public DateTime? OsProcessCreationDate
    {
        get
        {
            return base.GetNullableDateTime(OSPROCESSCREATIONDATE_FIELD_ID);
        }
    }

    public string? HeartBeat
    {
        get
        {
            return base.GetNullableString(HEARTBEAT_FIELD_ID);
        }
    }


    public Types.DmOsChildInstancesDataType ToDataObject()
    {
        return new Types.DmOsChildInstancesDataType(OwningPrincipalName,
            OwningPrincipalSid,
            OwningPrincipalSidBinary,
            InstanceName,
            InstancePipeName,
            OsProcessId,
            OsProcessCreationDate,
            HeartBeat);
    }

    public List<Types.DmOsChildInstancesDataType> ToList()
    {
        var list = new List<Types.DmOsChildInstancesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

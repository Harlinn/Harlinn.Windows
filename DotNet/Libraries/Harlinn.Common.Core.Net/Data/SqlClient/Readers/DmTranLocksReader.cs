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

public class DmTranLocksReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_locks]";
    public const string TableName = "dm_tran_locks";
    public const string ShortName = "dtl";
    public const string Sql = """
        SELECT
          dtl.[resource_type],
          dtl.[resource_subtype],
          dtl.[resource_database_id],
          dtl.[resource_description],
          dtl.[resource_associated_entity_id],
          dtl.[resource_lock_partition],
          dtl.[request_mode],
          dtl.[request_type],
          dtl.[request_status],
          dtl.[request_reference_count],
          dtl.[request_lifetime],
          dtl.[request_session_id],
          dtl.[request_exec_context_id],
          dtl.[request_request_id],
          dtl.[request_owner_type],
          dtl.[request_owner_id],
          dtl.[request_owner_guid],
          dtl.[request_owner_lockspace_id],
          dtl.[lock_owner_address]
        FROM
          [sys].[dm_tran_locks] dtl
        """;

    public const int RESOURCETYPE_FIELD_ID = 0;
    public const int RESOURCESUBTYPE_FIELD_ID = 1;
    public const int RESOURCEDATABASEID_FIELD_ID = 2;
    public const int RESOURCEDESCRIPTION_FIELD_ID = 3;
    public const int RESOURCEASSOCIATEDENTITYID_FIELD_ID = 4;
    public const int RESOURCELOCKPARTITION_FIELD_ID = 5;
    public const int REQUESTMODE_FIELD_ID = 6;
    public const int REQUESTTYPE_FIELD_ID = 7;
    public const int REQUESTSTATUS_FIELD_ID = 8;
    public const int REQUESTREFERENCECOUNT_FIELD_ID = 9;
    public const int REQUESTLIFETIME_FIELD_ID = 10;
    public const int REQUESTSESSIONID_FIELD_ID = 11;
    public const int REQUESTEXECCONTEXTID_FIELD_ID = 12;
    public const int REQUESTREQUESTID_FIELD_ID = 13;
    public const int REQUESTOWNERTYPE_FIELD_ID = 14;
    public const int REQUESTOWNERID_FIELD_ID = 15;
    public const int REQUESTOWNERGUID_FIELD_ID = 16;
    public const int REQUESTOWNERLOCKSPACEID_FIELD_ID = 17;
    public const int LOCKOWNERADDRESS_FIELD_ID = 18;


    public DmTranLocksReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranLocksReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranLocksReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string ResourceType
    {
        get
        {
            return base.GetString(RESOURCETYPE_FIELD_ID);
        }
    }

    public string ResourceSubtype
    {
        get
        {
            return base.GetString(RESOURCESUBTYPE_FIELD_ID);
        }
    }

    public int ResourceDatabaseId
    {
        get
        {
            return base.GetInt32(RESOURCEDATABASEID_FIELD_ID);
        }
    }

    public string ResourceDescription
    {
        get
        {
            return base.GetString(RESOURCEDESCRIPTION_FIELD_ID);
        }
    }

    public long? ResourceAssociatedEntityId
    {
        get
        {
            return base.GetNullableInt64(RESOURCEASSOCIATEDENTITYID_FIELD_ID);
        }
    }

    public int? ResourceLockPartition
    {
        get
        {
            return base.GetNullableInt32(RESOURCELOCKPARTITION_FIELD_ID);
        }
    }

    public string RequestMode
    {
        get
        {
            return base.GetString(REQUESTMODE_FIELD_ID);
        }
    }

    public string RequestType
    {
        get
        {
            return base.GetString(REQUESTTYPE_FIELD_ID);
        }
    }

    public string RequestStatus
    {
        get
        {
            return base.GetString(REQUESTSTATUS_FIELD_ID);
        }
    }

    public short RequestReferenceCount
    {
        get
        {
            return base.GetInt16(REQUESTREFERENCECOUNT_FIELD_ID);
        }
    }

    public int RequestLifetime
    {
        get
        {
            return base.GetInt32(REQUESTLIFETIME_FIELD_ID);
        }
    }

    public int RequestSessionId
    {
        get
        {
            return base.GetInt32(REQUESTSESSIONID_FIELD_ID);
        }
    }

    public int RequestExecContextId
    {
        get
        {
            return base.GetInt32(REQUESTEXECCONTEXTID_FIELD_ID);
        }
    }

    public int RequestRequestId
    {
        get
        {
            return base.GetInt32(REQUESTREQUESTID_FIELD_ID);
        }
    }

    public string RequestOwnerType
    {
        get
        {
            return base.GetString(REQUESTOWNERTYPE_FIELD_ID);
        }
    }

    public long? RequestOwnerId
    {
        get
        {
            return base.GetNullableInt64(REQUESTOWNERID_FIELD_ID);
        }
    }

    public Guid? RequestOwnerGuid
    {
        get
        {
            return base.GetNullableGuid(REQUESTOWNERGUID_FIELD_ID);
        }
    }

    public string RequestOwnerLockspaceId
    {
        get
        {
            return base.GetString(REQUESTOWNERLOCKSPACEID_FIELD_ID);
        }
    }

    public byte[] LockOwnerAddress
    {
        get
        {
            return base.GetBinary(LOCKOWNERADDRESS_FIELD_ID);
        }
    }


    public Types.DmTranLocksDataType ToDataObject()
    {
        return new Types.DmTranLocksDataType(ResourceType,
            ResourceSubtype,
            ResourceDatabaseId,
            ResourceDescription,
            ResourceAssociatedEntityId,
            ResourceLockPartition,
            RequestMode,
            RequestType,
            RequestStatus,
            RequestReferenceCount,
            RequestLifetime,
            RequestSessionId,
            RequestExecContextId,
            RequestRequestId,
            RequestOwnerType,
            RequestOwnerId,
            RequestOwnerGuid,
            RequestOwnerLockspaceId,
            LockOwnerAddress);
    }

    public List<Types.DmTranLocksDataType> ToList()
    {
        var list = new List<Types.DmTranLocksDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

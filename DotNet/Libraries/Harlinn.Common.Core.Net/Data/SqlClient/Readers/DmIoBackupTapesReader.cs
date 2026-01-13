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

public class DmIoBackupTapesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_io_backup_tapes]";
    public const string TableName = "dm_io_backup_tapes";
    public const string ShortName = "dibt";
    public const string Sql = """
        SELECT
          dibt.[physical_device_name],
          dibt.[logical_device_name],
          dibt.[Status],
          dibt.[status_desc],
          dibt.[mount_request_time],
          dibt.[mount_expiration_time],
          dibt.[database_name],
          dibt.[Spid],
          dibt.[Command],
          dibt.[command_desc],
          dibt.[media_family_id],
          dibt.[media_set_name],
          dibt.[media_set_guid],
          dibt.[media_sequence_number],
          dibt.[tape_operation],
          dibt.[tape_operation_desc],
          dibt.[mount_request_type],
          dibt.[mount_request_type_desc]
        FROM
          [sys].[dm_io_backup_tapes] dibt
        """;

    public const int PHYSICALDEVICENAME_FIELD_ID = 0;
    public const int LOGICALDEVICENAME_FIELD_ID = 1;
    public const int STATUS_FIELD_ID = 2;
    public const int STATUSDESC_FIELD_ID = 3;
    public const int MOUNTREQUESTTIME_FIELD_ID = 4;
    public const int MOUNTEXPIRATIONTIME_FIELD_ID = 5;
    public const int DATABASENAME_FIELD_ID = 6;
    public const int SPID_FIELD_ID = 7;
    public const int COMMAND_FIELD_ID = 8;
    public const int COMMANDDESC_FIELD_ID = 9;
    public const int MEDIAFAMILYID_FIELD_ID = 10;
    public const int MEDIASETNAME_FIELD_ID = 11;
    public const int MEDIASETGUID_FIELD_ID = 12;
    public const int MEDIASEQUENCENUMBER_FIELD_ID = 13;
    public const int TAPEOPERATION_FIELD_ID = 14;
    public const int TAPEOPERATIONDESC_FIELD_ID = 15;
    public const int MOUNTREQUESTTYPE_FIELD_ID = 16;
    public const int MOUNTREQUESTTYPEDESC_FIELD_ID = 17;


    public DmIoBackupTapesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmIoBackupTapesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmIoBackupTapesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string PhysicalDeviceName
    {
        get
        {
            return base.GetString(PHYSICALDEVICENAME_FIELD_ID);
        }
    }

    public string? LogicalDeviceName
    {
        get
        {
            return base.GetNullableString(LOGICALDEVICENAME_FIELD_ID);
        }
    }

    public int Status
    {
        get
        {
            return base.GetInt32(STATUS_FIELD_ID);
        }
    }

    public string StatusDesc
    {
        get
        {
            return base.GetString(STATUSDESC_FIELD_ID);
        }
    }

    public DateTime? MountRequestTime
    {
        get
        {
            return base.GetNullableDateTime(MOUNTREQUESTTIME_FIELD_ID);
        }
    }

    public DateTime? MountExpirationTime
    {
        get
        {
            return base.GetNullableDateTime(MOUNTEXPIRATIONTIME_FIELD_ID);
        }
    }

    public string? DatabaseName
    {
        get
        {
            return base.GetNullableString(DATABASENAME_FIELD_ID);
        }
    }

    public int? Spid
    {
        get
        {
            return base.GetNullableInt32(SPID_FIELD_ID);
        }
    }

    public int? Command
    {
        get
        {
            return base.GetNullableInt32(COMMAND_FIELD_ID);
        }
    }

    public string? CommandDesc
    {
        get
        {
            return base.GetNullableString(COMMANDDESC_FIELD_ID);
        }
    }

    public int? MediaFamilyId
    {
        get
        {
            return base.GetNullableInt32(MEDIAFAMILYID_FIELD_ID);
        }
    }

    public string? MediaSetName
    {
        get
        {
            return base.GetNullableString(MEDIASETNAME_FIELD_ID);
        }
    }

    public Guid? MediaSetGuid
    {
        get
        {
            return base.GetNullableGuid(MEDIASETGUID_FIELD_ID);
        }
    }

    public int? MediaSequenceNumber
    {
        get
        {
            return base.GetNullableInt32(MEDIASEQUENCENUMBER_FIELD_ID);
        }
    }

    public int? TapeOperation
    {
        get
        {
            return base.GetNullableInt32(TAPEOPERATION_FIELD_ID);
        }
    }

    public string? TapeOperationDesc
    {
        get
        {
            return base.GetNullableString(TAPEOPERATIONDESC_FIELD_ID);
        }
    }

    public int? MountRequestType
    {
        get
        {
            return base.GetNullableInt32(MOUNTREQUESTTYPE_FIELD_ID);
        }
    }

    public string? MountRequestTypeDesc
    {
        get
        {
            return base.GetNullableString(MOUNTREQUESTTYPEDESC_FIELD_ID);
        }
    }


    public Types.DmIoBackupTapesDataType ToDataObject()
    {
        return new Types.DmIoBackupTapesDataType(PhysicalDeviceName,
            LogicalDeviceName,
            Status,
            StatusDesc,
            MountRequestTime,
            MountExpirationTime,
            DatabaseName,
            Spid,
            Command,
            CommandDesc,
            MediaFamilyId,
            MediaSetName,
            MediaSetGuid,
            MediaSequenceNumber,
            TapeOperation,
            TapeOperationDesc,
            MountRequestType,
            MountRequestTypeDesc);
    }

    public List<Types.DmIoBackupTapesDataType> ToList()
    {
        var list = new List<Types.DmIoBackupTapesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

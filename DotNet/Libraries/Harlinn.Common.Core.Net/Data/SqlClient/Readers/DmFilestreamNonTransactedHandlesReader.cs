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

public class DmFilestreamNonTransactedHandlesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_filestream_non_transacted_handles]";
    public const string TableName = "dm_filestream_non_transacted_handles";
    public const string ShortName = "dfnth";
    public const string Sql = """
        SELECT
          dfnth.[database_id],
          dfnth.[object_id],
          dfnth.[handle_id],
          dfnth.[file_object_type],
          dfnth.[file_object_type_desc],
          dfnth.[correlation_process_id],
          dfnth.[correlation_thread_id],
          dfnth.[file_context],
          dfnth.[State],
          dfnth.[state_desc],
          dfnth.[current_workitem_type],
          dfnth.[current_workitem_type_desc],
          dfnth.[fcb_id],
          dfnth.[item_id],
          dfnth.[is_directory],
          dfnth.[item_name],
          dfnth.[opened_file_name],
          dfnth.[database_directory_name],
          dfnth.[table_directory_name],
          dfnth.[remaining_file_name],
          dfnth.[open_time],
          dfnth.[Flags],
          dfnth.[login_id],
          dfnth.[login_name],
          dfnth.[login_sid],
          dfnth.[read_access],
          dfnth.[write_access],
          dfnth.[delete_access],
          dfnth.[share_read],
          dfnth.[share_write],
          dfnth.[share_delete],
          dfnth.[create_disposition]
        FROM
          [sys].[dm_filestream_non_transacted_handles] dfnth
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int OBJECTID_FIELD_ID = 1;
    public const int HANDLEID_FIELD_ID = 2;
    public const int FILEOBJECTTYPE_FIELD_ID = 3;
    public const int FILEOBJECTTYPEDESC_FIELD_ID = 4;
    public const int CORRELATIONPROCESSID_FIELD_ID = 5;
    public const int CORRELATIONTHREADID_FIELD_ID = 6;
    public const int FILECONTEXT_FIELD_ID = 7;
    public const int STATE_FIELD_ID = 8;
    public const int STATEDESC_FIELD_ID = 9;
    public const int CURRENTWORKITEMTYPE_FIELD_ID = 10;
    public const int CURRENTWORKITEMTYPEDESC_FIELD_ID = 11;
    public const int FCBID_FIELD_ID = 12;
    public const int ITEMID_FIELD_ID = 13;
    public const int ISDIRECTORY_FIELD_ID = 14;
    public const int ITEMNAME_FIELD_ID = 15;
    public const int OPENEDFILENAME_FIELD_ID = 16;
    public const int DATABASEDIRECTORYNAME_FIELD_ID = 17;
    public const int TABLEDIRECTORYNAME_FIELD_ID = 18;
    public const int REMAININGFILENAME_FIELD_ID = 19;
    public const int OPENTIME_FIELD_ID = 20;
    public const int FLAGS_FIELD_ID = 21;
    public const int LOGINID_FIELD_ID = 22;
    public const int LOGINNAME_FIELD_ID = 23;
    public const int LOGINSID_FIELD_ID = 24;
    public const int READACCESS_FIELD_ID = 25;
    public const int WRITEACCESS_FIELD_ID = 26;
    public const int DELETEACCESS_FIELD_ID = 27;
    public const int SHAREREAD_FIELD_ID = 28;
    public const int SHAREWRITE_FIELD_ID = 29;
    public const int SHAREDELETE_FIELD_ID = 30;
    public const int CREATEDISPOSITION_FIELD_ID = 31;


    public DmFilestreamNonTransactedHandlesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmFilestreamNonTransactedHandlesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmFilestreamNonTransactedHandlesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? DatabaseId
    {
        get
        {
            return base.GetNullableInt32(DATABASEID_FIELD_ID);
        }
    }

    public int? ObjectId
    {
        get
        {
            return base.GetNullableInt32(OBJECTID_FIELD_ID);
        }
    }

    public int? HandleId
    {
        get
        {
            return base.GetNullableInt32(HANDLEID_FIELD_ID);
        }
    }

    public int? FileObjectType
    {
        get
        {
            return base.GetNullableInt32(FILEOBJECTTYPE_FIELD_ID);
        }
    }

    public string? FileObjectTypeDesc
    {
        get
        {
            return base.GetNullableString(FILEOBJECTTYPEDESC_FIELD_ID);
        }
    }

    public byte[]? CorrelationProcessId
    {
        get
        {
            return base.GetNullableBinary(CORRELATIONPROCESSID_FIELD_ID);
        }
    }

    public byte[]? CorrelationThreadId
    {
        get
        {
            return base.GetNullableBinary(CORRELATIONTHREADID_FIELD_ID);
        }
    }

    public byte[]? FileContext
    {
        get
        {
            return base.GetNullableBinary(FILECONTEXT_FIELD_ID);
        }
    }

    public int? State
    {
        get
        {
            return base.GetNullableInt32(STATE_FIELD_ID);
        }
    }

    public string? StateDesc
    {
        get
        {
            return base.GetNullableString(STATEDESC_FIELD_ID);
        }
    }

    public int? CurrentWorkitemType
    {
        get
        {
            return base.GetNullableInt32(CURRENTWORKITEMTYPE_FIELD_ID);
        }
    }

    public string? CurrentWorkitemTypeDesc
    {
        get
        {
            return base.GetNullableString(CURRENTWORKITEMTYPEDESC_FIELD_ID);
        }
    }

    public long? FcbId
    {
        get
        {
            return base.GetNullableInt64(FCBID_FIELD_ID);
        }
    }

    public byte[]? ItemId
    {
        get
        {
            return base.GetNullableBinary(ITEMID_FIELD_ID);
        }
    }

    public bool? IsDirectory
    {
        get
        {
            return base.GetNullableBoolean(ISDIRECTORY_FIELD_ID);
        }
    }

    public string? ItemName
    {
        get
        {
            return base.GetNullableString(ITEMNAME_FIELD_ID);
        }
    }

    public string? OpenedFileName
    {
        get
        {
            return base.GetNullableString(OPENEDFILENAME_FIELD_ID);
        }
    }

    public string? DatabaseDirectoryName
    {
        get
        {
            return base.GetNullableString(DATABASEDIRECTORYNAME_FIELD_ID);
        }
    }

    public string? TableDirectoryName
    {
        get
        {
            return base.GetNullableString(TABLEDIRECTORYNAME_FIELD_ID);
        }
    }

    public string? RemainingFileName
    {
        get
        {
            return base.GetNullableString(REMAININGFILENAME_FIELD_ID);
        }
    }

    public DateTime OpenTime
    {
        get
        {
            return base.GetDateTime(OPENTIME_FIELD_ID);
        }
    }

    public int? Flags
    {
        get
        {
            return base.GetNullableInt32(FLAGS_FIELD_ID);
        }
    }

    public int? LoginId
    {
        get
        {
            return base.GetNullableInt32(LOGINID_FIELD_ID);
        }
    }

    public string? LoginName
    {
        get
        {
            return base.GetNullableString(LOGINNAME_FIELD_ID);
        }
    }

    public byte[]? LoginSid
    {
        get
        {
            return base.GetNullableBinary(LOGINSID_FIELD_ID);
        }
    }

    public bool? ReadAccess
    {
        get
        {
            return base.GetNullableBoolean(READACCESS_FIELD_ID);
        }
    }

    public bool? WriteAccess
    {
        get
        {
            return base.GetNullableBoolean(WRITEACCESS_FIELD_ID);
        }
    }

    public bool? DeleteAccess
    {
        get
        {
            return base.GetNullableBoolean(DELETEACCESS_FIELD_ID);
        }
    }

    public bool? ShareRead
    {
        get
        {
            return base.GetNullableBoolean(SHAREREAD_FIELD_ID);
        }
    }

    public bool? ShareWrite
    {
        get
        {
            return base.GetNullableBoolean(SHAREWRITE_FIELD_ID);
        }
    }

    public bool? ShareDelete
    {
        get
        {
            return base.GetNullableBoolean(SHAREDELETE_FIELD_ID);
        }
    }

    public int? CreateDisposition
    {
        get
        {
            return base.GetNullableInt32(CREATEDISPOSITION_FIELD_ID);
        }
    }


    public Types.DmFilestreamNonTransactedHandlesDataType ToDataObject()
    {
        return new Types.DmFilestreamNonTransactedHandlesDataType(DatabaseId,
            ObjectId,
            HandleId,
            FileObjectType,
            FileObjectTypeDesc,
            CorrelationProcessId,
            CorrelationThreadId,
            FileContext,
            State,
            StateDesc,
            CurrentWorkitemType,
            CurrentWorkitemTypeDesc,
            FcbId,
            ItemId,
            IsDirectory,
            ItemName,
            OpenedFileName,
            DatabaseDirectoryName,
            TableDirectoryName,
            RemainingFileName,
            OpenTime,
            Flags,
            LoginId,
            LoginName,
            LoginSid,
            ReadAccess,
            WriteAccess,
            DeleteAccess,
            ShareRead,
            ShareWrite,
            ShareDelete,
            CreateDisposition);
    }

    public List<Types.DmFilestreamNonTransactedHandlesDataType> ToList()
    {
        var list = new List<Types.DmFilestreamNonTransactedHandlesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

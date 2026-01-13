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

public class DmFilestreamFileIoHandlesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_filestream_file_io_handles]";
    public const string TableName = "dm_filestream_file_io_handles";
    public const string ShortName = "dffih";
    public const string Sql = """
        SELECT
          dffih.[handle_context_address],
          dffih.[creation_request_id],
          dffih.[creation_irp_id],
          dffih.[handle_id],
          dffih.[creation_client_thread_id],
          dffih.[creation_client_process_id],
          dffih.[filestream_transaction_id],
          dffih.[access_type],
          dffih.[logical_path],
          dffih.[physical_path]
        FROM
          [sys].[dm_filestream_file_io_handles] dffih
        """;

    public const int HANDLECONTEXTADDRESS_FIELD_ID = 0;
    public const int CREATIONREQUESTID_FIELD_ID = 1;
    public const int CREATIONIRPID_FIELD_ID = 2;
    public const int HANDLEID_FIELD_ID = 3;
    public const int CREATIONCLIENTTHREADID_FIELD_ID = 4;
    public const int CREATIONCLIENTPROCESSID_FIELD_ID = 5;
    public const int FILESTREAMTRANSACTIONID_FIELD_ID = 6;
    public const int ACCESSTYPE_FIELD_ID = 7;
    public const int LOGICALPATH_FIELD_ID = 8;
    public const int PHYSICALPATH_FIELD_ID = 9;


    public DmFilestreamFileIoHandlesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmFilestreamFileIoHandlesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmFilestreamFileIoHandlesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[]? HandleContextAddress
    {
        get
        {
            return base.GetNullableBinary(HANDLECONTEXTADDRESS_FIELD_ID);
        }
    }

    public int CreationRequestId
    {
        get
        {
            return base.GetInt32(CREATIONREQUESTID_FIELD_ID);
        }
    }

    public int CreationIrpId
    {
        get
        {
            return base.GetInt32(CREATIONIRPID_FIELD_ID);
        }
    }

    public int HandleId
    {
        get
        {
            return base.GetInt32(HANDLEID_FIELD_ID);
        }
    }

    public byte[]? CreationClientThreadId
    {
        get
        {
            return base.GetNullableBinary(CREATIONCLIENTTHREADID_FIELD_ID);
        }
    }

    public byte[]? CreationClientProcessId
    {
        get
        {
            return base.GetNullableBinary(CREATIONCLIENTPROCESSID_FIELD_ID);
        }
    }

    public byte[]? FilestreamTransactionId
    {
        get
        {
            return base.GetNullableBinary(FILESTREAMTRANSACTIONID_FIELD_ID);
        }
    }

    public string AccessType
    {
        get
        {
            return base.GetString(ACCESSTYPE_FIELD_ID);
        }
    }

    public string? LogicalPath
    {
        get
        {
            return base.GetNullableString(LOGICALPATH_FIELD_ID);
        }
    }

    public string? PhysicalPath
    {
        get
        {
            return base.GetNullableString(PHYSICALPATH_FIELD_ID);
        }
    }


    public Types.DmFilestreamFileIoHandlesDataType ToDataObject()
    {
        return new Types.DmFilestreamFileIoHandlesDataType(HandleContextAddress,
            CreationRequestId,
            CreationIrpId,
            HandleId,
            CreationClientThreadId,
            CreationClientProcessId,
            FilestreamTransactionId,
            AccessType,
            LogicalPath,
            PhysicalPath);
    }

    public List<Types.DmFilestreamFileIoHandlesDataType> ToList()
    {
        var list = new List<Types.DmFilestreamFileIoHandlesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

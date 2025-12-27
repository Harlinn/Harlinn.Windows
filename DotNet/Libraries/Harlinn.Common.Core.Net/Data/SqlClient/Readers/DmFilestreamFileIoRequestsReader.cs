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

public class DmFilestreamFileIoRequestsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_filestream_file_io_requests]";
    public const string TableName = "dm_filestream_file_io_requests";
    public const string ShortName = "dffir";
    public const string Sql = """
        SELECT
          dffir.[request_context_address],
          dffir.[current_spid],
          dffir.[request_type],
          dffir.[request_state],
          dffir.[request_id],
          dffir.[irp_id],
          dffir.[handle_id],
          dffir.[client_thread_id],
          dffir.[client_process_id],
          dffir.[handle_context_address],
          dffir.[filestream_transaction_id]
        FROM
          [sys].[dm_filestream_file_io_requests] dffir
        """;

    public const int REQUESTCONTEXTADDRESS_FIELD_ID = 0;
    public const int CURRENTSPID_FIELD_ID = 1;
    public const int REQUESTTYPE_FIELD_ID = 2;
    public const int REQUESTSTATE_FIELD_ID = 3;
    public const int REQUESTID_FIELD_ID = 4;
    public const int IRPID_FIELD_ID = 5;
    public const int HANDLEID_FIELD_ID = 6;
    public const int CLIENTTHREADID_FIELD_ID = 7;
    public const int CLIENTPROCESSID_FIELD_ID = 8;
    public const int HANDLECONTEXTADDRESS_FIELD_ID = 9;
    public const int FILESTREAMTRANSACTIONID_FIELD_ID = 10;


    public DmFilestreamFileIoRequestsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmFilestreamFileIoRequestsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmFilestreamFileIoRequestsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] RequestContextAddress
    {
        get
        {
            return base.GetBinary(REQUESTCONTEXTADDRESS_FIELD_ID);
        }
    }

    public short CurrentSpid
    {
        get
        {
            return base.GetInt16(CURRENTSPID_FIELD_ID);
        }
    }

    public string RequestType
    {
        get
        {
            return base.GetString(REQUESTTYPE_FIELD_ID);
        }
    }

    public string RequestState
    {
        get
        {
            return base.GetString(REQUESTSTATE_FIELD_ID);
        }
    }

    public int RequestId
    {
        get
        {
            return base.GetInt32(REQUESTID_FIELD_ID);
        }
    }

    public int IrpId
    {
        get
        {
            return base.GetInt32(IRPID_FIELD_ID);
        }
    }

    public int HandleId
    {
        get
        {
            return base.GetInt32(HANDLEID_FIELD_ID);
        }
    }

    public byte[]? ClientThreadId
    {
        get
        {
            return base.GetNullableBinary(CLIENTTHREADID_FIELD_ID);
        }
    }

    public byte[]? ClientProcessId
    {
        get
        {
            return base.GetNullableBinary(CLIENTPROCESSID_FIELD_ID);
        }
    }

    public byte[]? HandleContextAddress
    {
        get
        {
            return base.GetNullableBinary(HANDLECONTEXTADDRESS_FIELD_ID);
        }
    }

    public byte[]? FilestreamTransactionId
    {
        get
        {
            return base.GetNullableBinary(FILESTREAMTRANSACTIONID_FIELD_ID);
        }
    }


    public Types.DmFilestreamFileIoRequestsDataType ToDataObject()
    {
        return new Types.DmFilestreamFileIoRequestsDataType(RequestContextAddress,
            CurrentSpid,
            RequestType,
            RequestState,
            RequestId,
            IrpId,
            HandleId,
            ClientThreadId,
            ClientProcessId,
            HandleContextAddress,
            FilestreamTransactionId);
    }

    public List<Types.DmFilestreamFileIoRequestsDataType> ToList()
    {
        var list = new List<Types.DmFilestreamFileIoRequestsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

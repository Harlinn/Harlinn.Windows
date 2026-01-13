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

public class DmPalProcessesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_pal_processes]";
    public const string TableName = "dm_pal_processes";
    public const string ShortName = "dpp";
    public const string Sql = """
        SELECT
          dpp.[process_id],
          dpp.[process_name],
          dpp.[processor_time],
          dpp.[user_time],
          dpp.[privileged_time],
          dpp.[virtual_bytes_peak],
          dpp.[virtual_bytes],
          dpp.[working_set_peak],
          dpp.[working_set],
          dpp.[page_file_bytes_peak],
          dpp.[page_file_bytes],
          dpp.[private_bytes],
          dpp.[thread_count],
          dpp.[elapsed_time],
          dpp.[pool_paged_bytes],
          dpp.[handle_count],
          dpp.[io_read_operations],
          dpp.[io_write_operations],
          dpp.[io_read_bytes],
          dpp.[io_write_bytes],
          dpp.[working_set_private]
        FROM
          [sys].[dm_pal_processes] dpp
        """;

    public const int PROCESSID_FIELD_ID = 0;
    public const int PROCESSNAME_FIELD_ID = 1;
    public const int PROCESSORTIME_FIELD_ID = 2;
    public const int USERTIME_FIELD_ID = 3;
    public const int PRIVILEGEDTIME_FIELD_ID = 4;
    public const int VIRTUALBYTESPEAK_FIELD_ID = 5;
    public const int VIRTUALBYTES_FIELD_ID = 6;
    public const int WORKINGSETPEAK_FIELD_ID = 7;
    public const int WORKINGSET_FIELD_ID = 8;
    public const int PAGEFILEBYTESPEAK_FIELD_ID = 9;
    public const int PAGEFILEBYTES_FIELD_ID = 10;
    public const int PRIVATEBYTES_FIELD_ID = 11;
    public const int THREADCOUNT_FIELD_ID = 12;
    public const int ELAPSEDTIME_FIELD_ID = 13;
    public const int POOLPAGEDBYTES_FIELD_ID = 14;
    public const int HANDLECOUNT_FIELD_ID = 15;
    public const int IOREADOPERATIONS_FIELD_ID = 16;
    public const int IOWRITEOPERATIONS_FIELD_ID = 17;
    public const int IOREADBYTES_FIELD_ID = 18;
    public const int IOWRITEBYTES_FIELD_ID = 19;
    public const int WORKINGSETPRIVATE_FIELD_ID = 20;


    public DmPalProcessesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmPalProcessesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmPalProcessesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long ProcessId
    {
        get
        {
            return base.GetInt64(PROCESSID_FIELD_ID);
        }
    }

    public string ProcessName
    {
        get
        {
            return base.GetString(PROCESSNAME_FIELD_ID);
        }
    }

    public long ProcessorTime
    {
        get
        {
            return base.GetInt64(PROCESSORTIME_FIELD_ID);
        }
    }

    public long UserTime
    {
        get
        {
            return base.GetInt64(USERTIME_FIELD_ID);
        }
    }

    public long PrivilegedTime
    {
        get
        {
            return base.GetInt64(PRIVILEGEDTIME_FIELD_ID);
        }
    }

    public long VirtualBytesPeak
    {
        get
        {
            return base.GetInt64(VIRTUALBYTESPEAK_FIELD_ID);
        }
    }

    public long VirtualBytes
    {
        get
        {
            return base.GetInt64(VIRTUALBYTES_FIELD_ID);
        }
    }

    public long WorkingSetPeak
    {
        get
        {
            return base.GetInt64(WORKINGSETPEAK_FIELD_ID);
        }
    }

    public long WorkingSet
    {
        get
        {
            return base.GetInt64(WORKINGSET_FIELD_ID);
        }
    }

    public long PageFileBytesPeak
    {
        get
        {
            return base.GetInt64(PAGEFILEBYTESPEAK_FIELD_ID);
        }
    }

    public long PageFileBytes
    {
        get
        {
            return base.GetInt64(PAGEFILEBYTES_FIELD_ID);
        }
    }

    public long PrivateBytes
    {
        get
        {
            return base.GetInt64(PRIVATEBYTES_FIELD_ID);
        }
    }

    public long ThreadCount
    {
        get
        {
            return base.GetInt64(THREADCOUNT_FIELD_ID);
        }
    }

    public long ElapsedTime
    {
        get
        {
            return base.GetInt64(ELAPSEDTIME_FIELD_ID);
        }
    }

    public long PoolPagedBytes
    {
        get
        {
            return base.GetInt64(POOLPAGEDBYTES_FIELD_ID);
        }
    }

    public long HandleCount
    {
        get
        {
            return base.GetInt64(HANDLECOUNT_FIELD_ID);
        }
    }

    public long IoReadOperations
    {
        get
        {
            return base.GetInt64(IOREADOPERATIONS_FIELD_ID);
        }
    }

    public long IoWriteOperations
    {
        get
        {
            return base.GetInt64(IOWRITEOPERATIONS_FIELD_ID);
        }
    }

    public long IoReadBytes
    {
        get
        {
            return base.GetInt64(IOREADBYTES_FIELD_ID);
        }
    }

    public long IoWriteBytes
    {
        get
        {
            return base.GetInt64(IOWRITEBYTES_FIELD_ID);
        }
    }

    public long WorkingSetPrivate
    {
        get
        {
            return base.GetInt64(WORKINGSETPRIVATE_FIELD_ID);
        }
    }


    public Types.DmPalProcessesDataType ToDataObject()
    {
        return new Types.DmPalProcessesDataType(ProcessId,
            ProcessName,
            ProcessorTime,
            UserTime,
            PrivilegedTime,
            VirtualBytesPeak,
            VirtualBytes,
            WorkingSetPeak,
            WorkingSet,
            PageFileBytesPeak,
            PageFileBytes,
            PrivateBytes,
            ThreadCount,
            ElapsedTime,
            PoolPagedBytes,
            HandleCount,
            IoReadOperations,
            IoWriteOperations,
            IoReadBytes,
            IoWriteBytes,
            WorkingSetPrivate);
    }

    public List<Types.DmPalProcessesDataType> ToList()
    {
        var list = new List<Types.DmPalProcessesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

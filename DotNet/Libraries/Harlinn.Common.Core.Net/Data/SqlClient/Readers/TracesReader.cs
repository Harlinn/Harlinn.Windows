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

public class TracesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[traces]";
    public const string TableName = "traces";
    public const string ShortName = "t";
    public const string Sql = """
        SELECT
          t.[Id],
          t.[Status],
          t.[Path],
          t.[max_size],
          t.[stop_time],
          t.[max_files],
          t.[is_rowset],
          t.[is_rollover],
          t.[is_shutdown],
          t.[is_default],
          t.[buffer_count],
          t.[buffer_size],
          t.[file_position],
          t.[reader_spid],
          t.[start_time],
          t.[last_event_time],
          t.[event_count],
          t.[dropped_event_count]
        FROM
          [sys].[traces] t
        """;

    public const int ID_FIELD_ID = 0;
    public const int STATUS_FIELD_ID = 1;
    public const int PATH_FIELD_ID = 2;
    public const int MAXSIZE_FIELD_ID = 3;
    public const int STOPTIME_FIELD_ID = 4;
    public const int MAXFILES_FIELD_ID = 5;
    public const int ISROWSET_FIELD_ID = 6;
    public const int ISROLLOVER_FIELD_ID = 7;
    public const int ISSHUTDOWN_FIELD_ID = 8;
    public const int ISDEFAULT_FIELD_ID = 9;
    public const int BUFFERCOUNT_FIELD_ID = 10;
    public const int BUFFERSIZE_FIELD_ID = 11;
    public const int FILEPOSITION_FIELD_ID = 12;
    public const int READERSPID_FIELD_ID = 13;
    public const int STARTTIME_FIELD_ID = 14;
    public const int LASTEVENTTIME_FIELD_ID = 15;
    public const int EVENTCOUNT_FIELD_ID = 16;
    public const int DROPPEDEVENTCOUNT_FIELD_ID = 17;


    public TracesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public TracesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public TracesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int Id
    {
        get
        {
            return base.GetInt32(ID_FIELD_ID);
        }
    }

    public int Status
    {
        get
        {
            return base.GetInt32(STATUS_FIELD_ID);
        }
    }

    public string? Path
    {
        get
        {
            return base.GetNullableString(PATH_FIELD_ID);
        }
    }

    public long? MaxSize
    {
        get
        {
            return base.GetNullableInt64(MAXSIZE_FIELD_ID);
        }
    }

    public DateTime? StopTime
    {
        get
        {
            return base.GetNullableDateTime(STOPTIME_FIELD_ID);
        }
    }

    public int? MaxFiles
    {
        get
        {
            return base.GetNullableInt32(MAXFILES_FIELD_ID);
        }
    }

    public bool? IsRowset
    {
        get
        {
            return base.GetNullableBoolean(ISROWSET_FIELD_ID);
        }
    }

    public bool? IsRollover
    {
        get
        {
            return base.GetNullableBoolean(ISROLLOVER_FIELD_ID);
        }
    }

    public bool? IsShutdown
    {
        get
        {
            return base.GetNullableBoolean(ISSHUTDOWN_FIELD_ID);
        }
    }

    public bool? IsDefault
    {
        get
        {
            return base.GetNullableBoolean(ISDEFAULT_FIELD_ID);
        }
    }

    public int? BufferCount
    {
        get
        {
            return base.GetNullableInt32(BUFFERCOUNT_FIELD_ID);
        }
    }

    public int? BufferSize
    {
        get
        {
            return base.GetNullableInt32(BUFFERSIZE_FIELD_ID);
        }
    }

    public long? FilePosition
    {
        get
        {
            return base.GetNullableInt64(FILEPOSITION_FIELD_ID);
        }
    }

    public int? ReaderSpid
    {
        get
        {
            return base.GetNullableInt32(READERSPID_FIELD_ID);
        }
    }

    public DateTime? StartTime
    {
        get
        {
            return base.GetNullableDateTime(STARTTIME_FIELD_ID);
        }
    }

    public DateTime? LastEventTime
    {
        get
        {
            return base.GetNullableDateTime(LASTEVENTTIME_FIELD_ID);
        }
    }

    public long? EventCount
    {
        get
        {
            return base.GetNullableInt64(EVENTCOUNT_FIELD_ID);
        }
    }

    public int? DroppedEventCount
    {
        get
        {
            return base.GetNullableInt32(DROPPEDEVENTCOUNT_FIELD_ID);
        }
    }


    public Types.Trace ToDataObject()
    {
        return new Types.Trace(Id,
            Status,
            Path,
            MaxSize,
            StopTime,
            MaxFiles,
            IsRowset,
            IsRollover,
            IsShutdown,
            IsDefault,
            BufferCount,
            BufferSize,
            FilePosition,
            ReaderSpid,
            StartTime,
            LastEventTime,
            EventCount,
            DroppedEventCount);
    }

    public List<Types.Trace> ToList()
    {
        var list = new List<Types.Trace>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

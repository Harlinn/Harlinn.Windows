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

public class DmHadrDbThreadsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_hadr_db_threads]";
    public const string TableName = "dm_hadr_db_threads";
    public const string ShortName = "dhdt";
    public const string Sql = """
        SELECT
          dhdt.[group_id],
          dhdt.[ag_db_id],
          dhdt.[Name],
          dhdt.[num_capture_threads],
          dhdt.[num_redo_threads],
          dhdt.[num_parallel_redo_threads]
        FROM
          [sys].[dm_hadr_db_threads] dhdt
        """;

    public const int GROUPID_FIELD_ID = 0;
    public const int AGDBID_FIELD_ID = 1;
    public const int NAME_FIELD_ID = 2;
    public const int NUMCAPTURETHREADS_FIELD_ID = 3;
    public const int NUMREDOTHREADS_FIELD_ID = 4;
    public const int NUMPARALLELREDOTHREADS_FIELD_ID = 5;


    public DmHadrDbThreadsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmHadrDbThreadsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmHadrDbThreadsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public Guid GroupId
    {
        get
        {
            return base.GetGuid(GROUPID_FIELD_ID);
        }
    }

    public Guid AgDbId
    {
        get
        {
            return base.GetGuid(AGDBID_FIELD_ID);
        }
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public int? NumCaptureThreads
    {
        get
        {
            return base.GetNullableInt32(NUMCAPTURETHREADS_FIELD_ID);
        }
    }

    public int? NumRedoThreads
    {
        get
        {
            return base.GetNullableInt32(NUMREDOTHREADS_FIELD_ID);
        }
    }

    public int? NumParallelRedoThreads
    {
        get
        {
            return base.GetNullableInt32(NUMPARALLELREDOTHREADS_FIELD_ID);
        }
    }


    public Types.DmHadrDbThreadsDataType ToDataObject()
    {
        return new Types.DmHadrDbThreadsDataType(GroupId,
            AgDbId,
            Name,
            NumCaptureThreads,
            NumRedoThreads,
            NumParallelRedoThreads);
    }

    public List<Types.DmHadrDbThreadsDataType> ToList()
    {
        var list = new List<Types.DmHadrDbThreadsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

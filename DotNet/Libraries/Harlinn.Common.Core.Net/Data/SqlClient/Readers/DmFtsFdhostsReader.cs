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

public class DmFtsFdhostsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_fts_fdhosts]";
    public const string TableName = "dm_fts_fdhosts";
    public const string ShortName = "dff";
    public const string Sql = """
        SELECT
          dff.[fdhost_id],
          dff.[fdhost_name],
          dff.[fdhost_process_id],
          dff.[fdhost_type],
          dff.[max_thread],
          dff.[batch_count]
        FROM
          [sys].[dm_fts_fdhosts] dff
        """;

    public const int FDHOSTID_FIELD_ID = 0;
    public const int FDHOSTNAME_FIELD_ID = 1;
    public const int FDHOSTPROCESSID_FIELD_ID = 2;
    public const int FDHOSTTYPE_FIELD_ID = 3;
    public const int MAXTHREAD_FIELD_ID = 4;
    public const int BATCHCOUNT_FIELD_ID = 5;


    public DmFtsFdhostsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmFtsFdhostsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmFtsFdhostsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int FdhostId
    {
        get
        {
            return base.GetInt32(FDHOSTID_FIELD_ID);
        }
    }

    public string? FdhostName
    {
        get
        {
            return base.GetNullableString(FDHOSTNAME_FIELD_ID);
        }
    }

    public int FdhostProcessId
    {
        get
        {
            return base.GetInt32(FDHOSTPROCESSID_FIELD_ID);
        }
    }

    public string? FdhostType
    {
        get
        {
            return base.GetNullableString(FDHOSTTYPE_FIELD_ID);
        }
    }

    public int MaxThread
    {
        get
        {
            return base.GetInt32(MAXTHREAD_FIELD_ID);
        }
    }

    public int BatchCount
    {
        get
        {
            return base.GetInt32(BATCHCOUNT_FIELD_ID);
        }
    }


    public Types.DmFtsFdhostsDataType ToDataObject()
    {
        return new Types.DmFtsFdhostsDataType(FdhostId,
            FdhostName,
            FdhostProcessId,
            FdhostType,
            MaxThread,
            BatchCount);
    }

    public List<Types.DmFtsFdhostsDataType> ToList()
    {
        var list = new List<Types.DmFtsFdhostsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

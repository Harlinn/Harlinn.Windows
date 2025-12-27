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

public class FulltextIndexFragmentsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[fulltext_index_fragments]";
    public const string TableName = "fulltext_index_fragments";
    public const string ShortName = "fif";
    public const string Sql = """
        SELECT
          fif.[table_id],
          fif.[fragment_id],
          fif.[fragment_object_id],
          fif.[Timestamp],
          fif.[Status],
          fif.[data_size],
          fif.[row_count]
        FROM
          [sys].[fulltext_index_fragments] fif
        """;

    public const int TABLEID_FIELD_ID = 0;
    public const int FRAGMENTID_FIELD_ID = 1;
    public const int FRAGMENTOBJECTID_FIELD_ID = 2;
    public const int TIMESTAMP_FIELD_ID = 3;
    public const int STATUS_FIELD_ID = 4;
    public const int DATASIZE_FIELD_ID = 5;
    public const int ROWCOUNT_FIELD_ID = 6;


    public FulltextIndexFragmentsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public FulltextIndexFragmentsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public FulltextIndexFragmentsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int TableId
    {
        get
        {
            return base.GetInt32(TABLEID_FIELD_ID);
        }
    }

    public int FragmentId
    {
        get
        {
            return base.GetInt32(FRAGMENTID_FIELD_ID);
        }
    }

    public int FragmentObjectId
    {
        get
        {
            return base.GetInt32(FRAGMENTOBJECTID_FIELD_ID);
        }
    }

    public byte[] Timestamp
    {
        get
        {
            return base.GetBinary(TIMESTAMP_FIELD_ID);
        }
    }

    public int Status
    {
        get
        {
            return base.GetInt32(STATUS_FIELD_ID);
        }
    }

    public long DataSize
    {
        get
        {
            return base.GetInt64(DATASIZE_FIELD_ID);
        }
    }

    public long RowCount
    {
        get
        {
            return base.GetInt64(ROWCOUNT_FIELD_ID);
        }
    }


    public Types.FulltextIndexFragmentsDataType ToDataObject()
    {
        return new Types.FulltextIndexFragmentsDataType(TableId,
            FragmentId,
            FragmentObjectId,
            Timestamp,
            Status,
            DataSize,
            RowCount);
    }

    public List<Types.FulltextIndexFragmentsDataType> ToList()
    {
        var list = new List<Types.FulltextIndexFragmentsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

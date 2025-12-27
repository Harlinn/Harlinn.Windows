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

public class DmTranTopVersionGeneratorsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_tran_top_version_generators]";
    public const string TableName = "dm_tran_top_version_generators";
    public const string ShortName = "dttvg";
    public const string Sql = """
        SELECT
          dttvg.[database_id],
          dttvg.[rowset_id],
          dttvg.[aggregated_record_length_in_bytes]
        FROM
          [sys].[dm_tran_top_version_generators] dttvg
        """;

    public const int DATABASEID_FIELD_ID = 0;
    public const int ROWSETID_FIELD_ID = 1;
    public const int AGGREGATEDRECORDLENGTHINBYTES_FIELD_ID = 2;


    public DmTranTopVersionGeneratorsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmTranTopVersionGeneratorsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmTranTopVersionGeneratorsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public short? DatabaseId
    {
        get
        {
            return base.GetNullableInt16(DATABASEID_FIELD_ID);
        }
    }

    public long? RowsetId
    {
        get
        {
            return base.GetNullableInt64(ROWSETID_FIELD_ID);
        }
    }

    public int? AggregatedRecordLengthInBytes
    {
        get
        {
            return base.GetNullableInt32(AGGREGATEDRECORDLENGTHINBYTES_FIELD_ID);
        }
    }


    public Types.DmTranTopVersionGeneratorsDataType ToDataObject()
    {
        return new Types.DmTranTopVersionGeneratorsDataType(DatabaseId,
            RowsetId,
            AggregatedRecordLengthInBytes);
    }

    public List<Types.DmTranTopVersionGeneratorsDataType> ToList()
    {
        var list = new List<Types.DmTranTopVersionGeneratorsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

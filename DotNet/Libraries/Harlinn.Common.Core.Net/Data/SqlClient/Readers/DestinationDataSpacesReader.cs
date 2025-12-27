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

public class DestinationDataSpacesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[destination_data_spaces]";
    public const string TableName = "destination_data_spaces";
    public const string ShortName = "dds";
    public const string Sql = """
        SELECT
          dds.[partition_scheme_id],
          dds.[destination_id],
          dds.[data_space_id]
        FROM
          [sys].[destination_data_spaces] dds
        """;

    public const int PARTITIONSCHEMEID_FIELD_ID = 0;
    public const int DESTINATIONID_FIELD_ID = 1;
    public const int DATASPACEID_FIELD_ID = 2;


    public DestinationDataSpacesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DestinationDataSpacesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DestinationDataSpacesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int PartitionSchemeId
    {
        get
        {
            return base.GetInt32(PARTITIONSCHEMEID_FIELD_ID);
        }
    }

    public int DestinationId
    {
        get
        {
            return base.GetInt32(DESTINATIONID_FIELD_ID);
        }
    }

    public int DataSpaceId
    {
        get
        {
            return base.GetInt32(DATASPACEID_FIELD_ID);
        }
    }


    public Types.DestinationDataSpacesDataType ToDataObject()
    {
        return new Types.DestinationDataSpacesDataType(PartitionSchemeId,
            DestinationId,
            DataSpaceId);
    }

    public List<Types.DestinationDataSpacesDataType> ToList()
    {
        var list = new List<Types.DestinationDataSpacesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

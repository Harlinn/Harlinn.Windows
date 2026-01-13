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

public class DmOsSublatchesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_sublatches]";
    public const string TableName = "dm_os_sublatches";
    public const string ShortName = "dos0";
    public const string Sql = """
        SELECT
          dos0.[superlatch_address],
          dos0.[sublatch_address],
          dos0.[partition_id]
        FROM
          [sys].[dm_os_sublatches] dos0
        """;

    public const int SUPERLATCHADDRESS_FIELD_ID = 0;
    public const int SUBLATCHADDRESS_FIELD_ID = 1;
    public const int PARTITIONID_FIELD_ID = 2;


    public DmOsSublatchesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsSublatchesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsSublatchesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[]? SuperlatchAddress
    {
        get
        {
            return base.GetNullableBinary(SUPERLATCHADDRESS_FIELD_ID);
        }
    }

    public byte[] SublatchAddress
    {
        get
        {
            return base.GetBinary(SUBLATCHADDRESS_FIELD_ID);
        }
    }

    public int PartitionId
    {
        get
        {
            return base.GetInt32(PARTITIONID_FIELD_ID);
        }
    }


    public Types.DmOsSublatchesDataType ToDataObject()
    {
        return new Types.DmOsSublatchesDataType(SuperlatchAddress,
            SublatchAddress,
            PartitionId);
    }

    public List<Types.DmOsSublatchesDataType> ToList()
    {
        var list = new List<Types.DmOsSublatchesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

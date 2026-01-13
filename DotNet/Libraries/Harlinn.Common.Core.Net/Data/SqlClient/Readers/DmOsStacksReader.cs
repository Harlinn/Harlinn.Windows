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

public class DmOsStacksReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_stacks]";
    public const string TableName = "dm_os_stacks";
    public const string ShortName = "dos1";
    public const string Sql = """
        SELECT
          dos1.[stack_address],
          dos1.[frame_index],
          dos1.[frame_address]
        FROM
          [sys].[dm_os_stacks] dos1
        """;

    public const int STACKADDRESS_FIELD_ID = 0;
    public const int FRAMEINDEX_FIELD_ID = 1;
    public const int FRAMEADDRESS_FIELD_ID = 2;


    public DmOsStacksReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsStacksReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsStacksReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] StackAddress
    {
        get
        {
            return base.GetBinary(STACKADDRESS_FIELD_ID);
        }
    }

    public int FrameIndex
    {
        get
        {
            return base.GetInt32(FRAMEINDEX_FIELD_ID);
        }
    }

    public byte[] FrameAddress
    {
        get
        {
            return base.GetBinary(FRAMEADDRESS_FIELD_ID);
        }
    }


    public Types.DmOsStacksDataType ToDataObject()
    {
        return new Types.DmOsStacksDataType(StackAddress,
            FrameIndex,
            FrameAddress);
    }

    public List<Types.DmOsStacksDataType> ToList()
    {
        var list = new List<Types.DmOsStacksDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

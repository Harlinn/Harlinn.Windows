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

public class DmOsVirtualAddressDumpReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_os_virtual_address_dump]";
    public const string TableName = "dm_os_virtual_address_dump";
    public const string ShortName = "dovad";
    public const string Sql = """
        SELECT
          dovad.[region_base_address],
          dovad.[region_allocation_base_address],
          dovad.[region_allocation_protection],
          dovad.[region_size_in_bytes],
          dovad.[region_state],
          dovad.[region_current_protection],
          dovad.[region_type]
        FROM
          [sys].[dm_os_virtual_address_dump] dovad
        """;

    public const int REGIONBASEADDRESS_FIELD_ID = 0;
    public const int REGIONALLOCATIONBASEADDRESS_FIELD_ID = 1;
    public const int REGIONALLOCATIONPROTECTION_FIELD_ID = 2;
    public const int REGIONSIZEINBYTES_FIELD_ID = 3;
    public const int REGIONSTATE_FIELD_ID = 4;
    public const int REGIONCURRENTPROTECTION_FIELD_ID = 5;
    public const int REGIONTYPE_FIELD_ID = 6;


    public DmOsVirtualAddressDumpReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmOsVirtualAddressDumpReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmOsVirtualAddressDumpReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] RegionBaseAddress
    {
        get
        {
            return base.GetBinary(REGIONBASEADDRESS_FIELD_ID);
        }
    }

    public byte[] RegionAllocationBaseAddress
    {
        get
        {
            return base.GetBinary(REGIONALLOCATIONBASEADDRESS_FIELD_ID);
        }
    }

    public byte[] RegionAllocationProtection
    {
        get
        {
            return base.GetBinary(REGIONALLOCATIONPROTECTION_FIELD_ID);
        }
    }

    public long RegionSizeInBytes
    {
        get
        {
            return base.GetInt64(REGIONSIZEINBYTES_FIELD_ID);
        }
    }

    public byte[] RegionState
    {
        get
        {
            return base.GetBinary(REGIONSTATE_FIELD_ID);
        }
    }

    public byte[] RegionCurrentProtection
    {
        get
        {
            return base.GetBinary(REGIONCURRENTPROTECTION_FIELD_ID);
        }
    }

    public byte[] RegionType
    {
        get
        {
            return base.GetBinary(REGIONTYPE_FIELD_ID);
        }
    }


    public Types.DmOsVirtualAddressDumpDataType ToDataObject()
    {
        return new Types.DmOsVirtualAddressDumpDataType(RegionBaseAddress,
            RegionAllocationBaseAddress,
            RegionAllocationProtection,
            RegionSizeInBytes,
            RegionState,
            RegionCurrentProtection,
            RegionType);
    }

    public List<Types.DmOsVirtualAddressDumpDataType> ToList()
    {
        var list = new List<Types.DmOsVirtualAddressDumpDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

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

public class SystemInternalsAllocationUnitsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[system_internals_allocation_units]";
    public const string TableName = "system_internals_allocation_units";
    public const string ShortName = "siau";
    public const string Sql = """
        SELECT
          siau.[allocation_unit_id],
          siau.[Type],
          siau.[type_desc],
          siau.[container_id],
          siau.[filegroup_id],
          siau.[total_pages],
          siau.[used_pages],
          siau.[data_pages],
          siau.[first_page],
          siau.[root_page],
          siau.[first_iam_page]
        FROM
          [sys].[system_internals_allocation_units] siau
        """;

    public const int ALLOCATIONUNITID_FIELD_ID = 0;
    public const int TYPE_FIELD_ID = 1;
    public const int TYPEDESC_FIELD_ID = 2;
    public const int CONTAINERID_FIELD_ID = 3;
    public const int FILEGROUPID_FIELD_ID = 4;
    public const int TOTALPAGES_FIELD_ID = 5;
    public const int USEDPAGES_FIELD_ID = 6;
    public const int DATAPAGES_FIELD_ID = 7;
    public const int FIRSTPAGE_FIELD_ID = 8;
    public const int ROOTPAGE_FIELD_ID = 9;
    public const int FIRSTIAMPAGE_FIELD_ID = 10;


    public SystemInternalsAllocationUnitsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SystemInternalsAllocationUnitsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SystemInternalsAllocationUnitsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public long AllocationUnitId
    {
        get
        {
            return base.GetInt64(ALLOCATIONUNITID_FIELD_ID);
        }
    }

    public byte Type
    {
        get
        {
            return base.GetByte(TYPE_FIELD_ID);
        }
    }

    public string? TypeDesc
    {
        get
        {
            return base.GetNullableString(TYPEDESC_FIELD_ID);
        }
    }

    public long ContainerId
    {
        get
        {
            return base.GetInt64(CONTAINERID_FIELD_ID);
        }
    }

    public short FilegroupId
    {
        get
        {
            return base.GetInt16(FILEGROUPID_FIELD_ID);
        }
    }

    public long TotalPages
    {
        get
        {
            return base.GetInt64(TOTALPAGES_FIELD_ID);
        }
    }

    public long UsedPages
    {
        get
        {
            return base.GetInt64(USEDPAGES_FIELD_ID);
        }
    }

    public long DataPages
    {
        get
        {
            return base.GetInt64(DATAPAGES_FIELD_ID);
        }
    }

    public byte[] FirstPage
    {
        get
        {
            return base.GetBinary(FIRSTPAGE_FIELD_ID);
        }
    }

    public byte[] RootPage
    {
        get
        {
            return base.GetBinary(ROOTPAGE_FIELD_ID);
        }
    }

    public byte[] FirstIamPage
    {
        get
        {
            return base.GetBinary(FIRSTIAMPAGE_FIELD_ID);
        }
    }


    public Types.SystemInternalsAllocationUnitsDataType ToDataObject()
    {
        return new Types.SystemInternalsAllocationUnitsDataType(AllocationUnitId,
            Type,
            TypeDesc,
            ContainerId,
            FilegroupId,
            TotalPages,
            UsedPages,
            DataPages,
            FirstPage,
            RootPage,
            FirstIamPage);
    }

    public List<Types.SystemInternalsAllocationUnitsDataType> ToList()
    {
        var list = new List<Types.SystemInternalsAllocationUnitsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

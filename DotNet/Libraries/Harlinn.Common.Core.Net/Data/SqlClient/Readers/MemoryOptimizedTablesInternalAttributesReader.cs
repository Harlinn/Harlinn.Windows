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

public class MemoryOptimizedTablesInternalAttributesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[memory_optimized_tables_internal_attributes]";
    public const string TableName = "memory_optimized_tables_internal_attributes";
    public const string ShortName = "motia";
    public const string Sql = """
        SELECT
          motia.[object_id],
          motia.[xtp_object_id],
          motia.[Type],
          motia.[type_desc],
          motia.[minor_id]
        FROM
          [sys].[memory_optimized_tables_internal_attributes] motia
        """;

    public const int OBJECTID_FIELD_ID = 0;
    public const int XTPOBJECTID_FIELD_ID = 1;
    public const int TYPE_FIELD_ID = 2;
    public const int TYPEDESC_FIELD_ID = 3;
    public const int MINORID_FIELD_ID = 4;


    public MemoryOptimizedTablesInternalAttributesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public MemoryOptimizedTablesInternalAttributesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public MemoryOptimizedTablesInternalAttributesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public int? ObjectId
    {
        get
        {
            return base.GetNullableInt32(OBJECTID_FIELD_ID);
        }
    }

    public int XtpObjectId
    {
        get
        {
            return base.GetInt32(XTPOBJECTID_FIELD_ID);
        }
    }

    public int? Type
    {
        get
        {
            return base.GetNullableInt32(TYPE_FIELD_ID);
        }
    }

    public string TypeDesc
    {
        get
        {
            return base.GetString(TYPEDESC_FIELD_ID);
        }
    }

    public int MinorId
    {
        get
        {
            return base.GetInt32(MINORID_FIELD_ID);
        }
    }


    public Types.MemoryOptimizedTablesInternalAttributesDataType ToDataObject()
    {
        return new Types.MemoryOptimizedTablesInternalAttributesDataType(ObjectId,
            XtpObjectId,
            Type,
            TypeDesc,
            MinorId);
    }

    public List<Types.MemoryOptimizedTablesInternalAttributesDataType> ToList()
    {
        var list = new List<Types.MemoryOptimizedTablesInternalAttributesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

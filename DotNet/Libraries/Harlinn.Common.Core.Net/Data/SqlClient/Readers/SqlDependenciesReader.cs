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

public class SqlDependenciesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[sql_dependencies]";
    public const string TableName = "sql_dependencies";
    public const string ShortName = "sd";
    public const string Sql = """
        SELECT
          sd.[Class],
          sd.[class_desc],
          sd.[object_id],
          sd.[column_id],
          sd.[referenced_major_id],
          sd.[referenced_minor_id],
          sd.[is_selected],
          sd.[is_updated],
          sd.[is_select_all]
        FROM
          [sys].[sql_dependencies] sd
        """;

    public const int CLASS_FIELD_ID = 0;
    public const int CLASSDESC_FIELD_ID = 1;
    public const int OBJECTID_FIELD_ID = 2;
    public const int COLUMNID_FIELD_ID = 3;
    public const int REFERENCEDMAJORID_FIELD_ID = 4;
    public const int REFERENCEDMINORID_FIELD_ID = 5;
    public const int ISSELECTED_FIELD_ID = 6;
    public const int ISUPDATED_FIELD_ID = 7;
    public const int ISSELECTALL_FIELD_ID = 8;


    public SqlDependenciesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public SqlDependenciesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public SqlDependenciesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte Class
    {
        get
        {
            return base.GetByte(CLASS_FIELD_ID);
        }
    }

    public string? ClassDesc
    {
        get
        {
            return base.GetNullableString(CLASSDESC_FIELD_ID);
        }
    }

    public int ObjectId
    {
        get
        {
            return base.GetInt32(OBJECTID_FIELD_ID);
        }
    }

    public int ColumnId
    {
        get
        {
            return base.GetInt32(COLUMNID_FIELD_ID);
        }
    }

    public int ReferencedMajorId
    {
        get
        {
            return base.GetInt32(REFERENCEDMAJORID_FIELD_ID);
        }
    }

    public int ReferencedMinorId
    {
        get
        {
            return base.GetInt32(REFERENCEDMINORID_FIELD_ID);
        }
    }

    public bool IsSelected
    {
        get
        {
            return base.GetBoolean(ISSELECTED_FIELD_ID);
        }
    }

    public bool IsUpdated
    {
        get
        {
            return base.GetBoolean(ISUPDATED_FIELD_ID);
        }
    }

    public bool IsSelectAll
    {
        get
        {
            return base.GetBoolean(ISSELECTALL_FIELD_ID);
        }
    }


    public Types.SqlDependenciesDataType ToDataObject()
    {
        return new Types.SqlDependenciesDataType(Class,
            ClassDesc,
            ObjectId,
            ColumnId,
            ReferencedMajorId,
            ReferencedMinorId,
            IsSelected,
            IsUpdated,
            IsSelectAll);
    }

    public List<Types.SqlDependenciesDataType> ToList()
    {
        var list = new List<Types.SqlDependenciesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

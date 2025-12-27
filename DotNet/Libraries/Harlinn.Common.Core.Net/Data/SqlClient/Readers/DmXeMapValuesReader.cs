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

public class DmXeMapValuesReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_xe_map_values]";
    public const string TableName = "dm_xe_map_values";
    public const string ShortName = "dxmv";
    public const string Sql = """
        SELECT
          dxmv.[Name],
          dxmv.[object_package_guid],
          dxmv.[map_key],
          dxmv.[map_value]
        FROM
          [sys].[dm_xe_map_values] dxmv
        """;

    public const int NAME_FIELD_ID = 0;
    public const int OBJECTPACKAGEGUID_FIELD_ID = 1;
    public const int MAPKEY_FIELD_ID = 2;
    public const int MAPVALUE_FIELD_ID = 3;


    public DmXeMapValuesReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmXeMapValuesReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmXeMapValuesReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public string Name
    {
        get
        {
            return base.GetString(NAME_FIELD_ID);
        }
    }

    public Guid ObjectPackageGuid
    {
        get
        {
            return base.GetGuid(OBJECTPACKAGEGUID_FIELD_ID);
        }
    }

    public int MapKey
    {
        get
        {
            return base.GetInt32(MAPKEY_FIELD_ID);
        }
    }

    public string MapValue
    {
        get
        {
            return base.GetString(MAPVALUE_FIELD_ID);
        }
    }


    public Types.DmXeMapValuesDataType ToDataObject()
    {
        return new Types.DmXeMapValuesDataType(Name,
            ObjectPackageGuid,
            MapKey,
            MapValue);
    }

    public List<Types.DmXeMapValuesDataType> ToList()
    {
        var list = new List<Types.DmXeMapValuesDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}

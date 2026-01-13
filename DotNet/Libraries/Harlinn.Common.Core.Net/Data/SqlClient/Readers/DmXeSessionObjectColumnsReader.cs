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

public class DmXeSessionObjectColumnsReader : DataReaderWrapper
{
    public const string QualifiedTableName = "[sys].[dm_xe_session_object_columns]";
    public const string TableName = "dm_xe_session_object_columns";
    public const string ShortName = "dxsoc";
    public const string Sql = """
        SELECT
          dxsoc.[event_session_address],
          dxsoc.[column_name],
          dxsoc.[column_id],
          dxsoc.[column_value],
          dxsoc.[object_type],
          dxsoc.[object_name],
          dxsoc.[object_package_guid]
        FROM
          [sys].[dm_xe_session_object_columns] dxsoc
        """;

    public const int EVENTSESSIONADDRESS_FIELD_ID = 0;
    public const int COLUMNNAME_FIELD_ID = 1;
    public const int COLUMNID_FIELD_ID = 2;
    public const int COLUMNVALUE_FIELD_ID = 3;
    public const int OBJECTTYPE_FIELD_ID = 4;
    public const int OBJECTNAME_FIELD_ID = 5;
    public const int OBJECTPACKAGEGUID_FIELD_ID = 6;


    public DmXeSessionObjectColumnsReader([DisallowNull] ILoggerFactory loggerFactory, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(loggerFactory, sqlDataReader, ownsReader)
    {
    }

    public DmXeSessionObjectColumnsReader([DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(sqlDataReader, ownsReader)
    {
    }

    public DmXeSessionObjectColumnsReader([DisallowNull] ILogger logger, [DisallowNull] SqlDataReader sqlDataReader, bool ownsReader = true)
        : base(logger, sqlDataReader, ownsReader)
    {
    }

    public byte[] EventSessionAddress
    {
        get
        {
            return base.GetBinary(EVENTSESSIONADDRESS_FIELD_ID);
        }
    }

    public string ColumnName
    {
        get
        {
            return base.GetString(COLUMNNAME_FIELD_ID);
        }
    }

    public int ColumnId
    {
        get
        {
            return base.GetInt32(COLUMNID_FIELD_ID);
        }
    }

    public string? ColumnValue
    {
        get
        {
            return base.GetNullableString(COLUMNVALUE_FIELD_ID);
        }
    }

    public string ObjectType
    {
        get
        {
            return base.GetString(OBJECTTYPE_FIELD_ID);
        }
    }

    public string ObjectName
    {
        get
        {
            return base.GetString(OBJECTNAME_FIELD_ID);
        }
    }

    public Guid ObjectPackageGuid
    {
        get
        {
            return base.GetGuid(OBJECTPACKAGEGUID_FIELD_ID);
        }
    }


    public Types.DmXeSessionObjectColumnsDataType ToDataObject()
    {
        return new Types.DmXeSessionObjectColumnsDataType(EventSessionAddress,
            ColumnName,
            ColumnId,
            ColumnValue,
            ObjectType,
            ObjectName,
            ObjectPackageGuid);
    }

    public List<Types.DmXeSessionObjectColumnsDataType> ToList()
    {
        var list = new List<Types.DmXeSessionObjectColumnsDataType>();
        while (Read())
        {
            list.Add(ToDataObject());
        }
        return list;
    }

}
